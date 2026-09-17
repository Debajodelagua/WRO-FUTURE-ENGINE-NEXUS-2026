#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <DFRobot_HuskylensV2.h> 

Adafruit_MPU6050 mpu;
HuskylensV2 huskylens;           
SET_LOOP_TASK_STACK_SIZE(16384);

// --- Pines ---
const int PIN_SERVO     = 8;
const int PIN_MOTOR_PWM = 15;
const int PIN_MOTOR_IN1 = 5;
const int PIN_MOTOR_IN2 = 6;
const int PIN_INICIO    = 21;

const int PIN_SDA = 16;
const int PIN_SCL = 17;

const int RX_HUSKY = 13;
const int TX_HUSKY = 12;

// Pines Ultrasónicos
const int PIN_TRIG_FRONTAL   = 42;
const int PIN_ECHO_FRONTAL   = 41;
const int PIN_TRIG_DERECHO   = 38;
const int PIN_ECHO_DERECHO   = 37;
const int PIN_TRIG_IZQUIERDO = 39;
const int PIN_ECHO_IZQUIERDO = 40;

// --- Panel de Tiempos Generales ---
const unsigned long TIEMPO_LECTURA_MS    = 1;
const unsigned long TIEMPO_CAMARA_MS     = 30; // ~33 fps para leer cámara
const unsigned long TIEMPO_SONAR_MS      = 50; 
const unsigned long TIEMPO_SERIAL_MS     = 100;

// --- Configuración Motor y Servo ---
const int SERVO_CENTRO  = 96;
const int MAX_DEFLEXION = 31;
int VELOCIDAD_MOTOR     = 110;  // 0 a 255

// =========================================================
// ---> CONTROL DE CAZADOR Y COREOGRAFÍA (BLOQUES) <---
// =========================================================
int ANCHO_DISPARO_ESQUIVE     = 180;    // Gatillo: A este tamaño FRENA y evalúa
float KP_CENTRAR              = 0.05;  // Fuerza con la que centra el bloque de lejos
float GRADOS_ESQUIVE          = 55.0;   // Grados de inclinación para la diagonal

// LÍMITES PARA IGNORAR BLOQUES YA LIBRADOS (Asumiendo centro en X=320)
int LIMITE_IGNORAR_ROJO       = 10;     // Si el Rojo (Firma 1) está en X < 240 (Izquierda), lo ignora.
int LIMITE_IGNORAR_VERDE      = 630;    // Si el Verde (Firma 2) está en X > 400 (Derecha), lo ignora.

// Tiempos de Coreografía
unsigned long TIEMPO_FRENO         = 500;   
unsigned long TIEMPO_DIAG_SALIDA   = 900;  
unsigned long TIEMPO_RECTO_REBASE  = 100;   
unsigned long TIEMPO_DIAG_REGRESO  = 1200;  
unsigned long TIEMPO_REVERSA_FINAL = 1000;  // NUEVO: ms moviéndose hacia atrás al terminar el esquive
int VELOCIDAD_REVERSA_FINAL        = 100;  // NUEVO: Velocidad del motor en la reversa final

unsigned long TIMEOUT_MEMORIA_CAMARA = 400; 

// =========================================================
// ---> NUEVO: ENDEREZADO PRE-ESQUIVE (MANIOBRA EN S) <---
// =========================================================
float TOLERANCIA_DIAGONAL               = 200.0; 
unsigned long TIEMPO_REVERSA_ALIN_PASO1 = 800;  
unsigned long TIEMPO_REVERSA_ALIN_PASO2 = 400;  
int VELOCIDAD_REVERSA_ALINEACION        = 150;  

// =========================================================
// ---> CONTROL DE ESQUINAS Y ACOMODO (PAREDES) <---
// =========================================================
float DISTANCIA_GIRO          = 18.0;  
unsigned long TIEMPO_REVERSA  = 1500;  
int VELOCIDAD_REVERSA         = 200;   
float GRADOS_GIRO             = 88.0;  
unsigned long COOLDOWN_GIRO   = 3000;  

// --- Variables MPU ---
volatile float yaw_actual = 0.0;
volatile float gz_offset = 0.0;
unsigned long tiempo_anterior_mpu = 0;
TaskHandle_t TareaMPU;

// --- Variables de Control PD ---
float setpoint_yaw = 0.0;
float setpoint_base = 0.0; 
float error_anterior = 0.0;
int angulo_servo_actual = SERVO_CENTRO;

float Kp = 1.0;
float Kd = 0.0;

// --- Variables Lógica de Cámara (Bloques) ---
bool en_coreografia = false;
int paso_coreografia = 0;
unsigned long tiempo_inicio_coreo = 0;
float setpoint_previo_coreo = 0.0;
int tipo_esquive = 0; 

bool viendo_bloque = false;
unsigned long tiempo_ultima_vista = 0;

// --- Variables Nueva Táctica Enderezado ---
bool en_alineacion_pre_esquive = false;
int paso_alineacion = 0;
unsigned long tiempo_inicio_alineacion = 0;
int direccion_alineacion = 0; 

// --- Variables Ultrasónico (Paredes) ---
float dist_frontal = 999.0, dist_derecha = 999.0, dist_izquierda = 999.0;
int turno_sensor = 0;

// ---> BLOQUEO DE PISTA WRO <---
int direccion_global_pista = 0; // 0 = Indeciso, 1 = Izquierda, -1 = Derecha

bool en_acomodo = false;
unsigned long tiempo_inicio_acomodo = 0;
unsigned long tiempo_fin_esquina = 0;
int direccion_esquina = 0; 

// --- Tiempos base ---
unsigned long tiempo_anterior = 0;
unsigned long tiempo_camara = 0;
unsigned long tiempo_sonar = 0;
unsigned long tiempo_serial = 0;
bool motor_encendido = false;

// ==========================================
// FUNCIONES
// ==========================================
void escribirServoGrados(int grados) {
  grados = constrain(grados, 0, 180);
  int duty = map(grados, 0, 180, 102, 491);
  ledcWrite(PIN_SERVO, duty);
}

float medirDistancia(int pinTrig, int pinEcho) {
  digitalWrite(pinTrig, LOW); delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH); delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  long duracion = pulseIn(pinEcho, HIGH, 15000); 
  if (duracion == 0) return 999.0;
  return (duracion * 0.0343) / 2.0;
}

void rescatarBusI2C() {
  Wire.end();
  pinMode(PIN_SDA, INPUT_PULLUP); pinMode(PIN_SCL, OUTPUT);
  for (int i = 0; i < 9; i++) {
    digitalWrite(PIN_SCL, LOW); delayMicroseconds(10);
    digitalWrite(PIN_SCL, HIGH); delayMicroseconds(10);
    if (digitalRead(PIN_SDA) == HIGH) break;
  }
  pinMode(PIN_SDA, OUTPUT);
  digitalWrite(PIN_SDA, LOW); delayMicroseconds(10);
  digitalWrite(PIN_SCL, HIGH); delayMicroseconds(10);
  digitalWrite(PIN_SDA, HIGH); delayMicroseconds(10);
  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(100000);
  Wire.setTimeout(50);
  mpu.begin(0x68, &Wire);
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

bool leerMPUSeguro(float &gz_out) {
  Wire.beginTransmission(0x68);
  if (Wire.endTransmission(true) != 0) { rescatarBusI2C(); return false; }
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  gz_out = (g.gyro.z - gz_offset) * (180.0 / PI);
  return true;
}

void tareaLeerMPU(void * parameter) {
  for (;;) {
    unsigned long tiempo_ahora = millis();
    float dt = (tiempo_ahora - tiempo_anterior_mpu) / 1000.0;
    tiempo_anterior_mpu = tiempo_ahora;
    if (dt <= 0) dt = 0.002;
    if (dt > 0.05) dt = 0.05;
    float gz = 0.0;
    if (leerMPUSeguro(gz)) {
      if (abs(gz) > 0.3) yaw_actual += gz * dt;
    }
    vTaskDelay(2 / portTICK_PERIOD_MS);
  }
}

void setup() {
  pinMode(PIN_MOTOR_IN1, OUTPUT); 
  pinMode(PIN_MOTOR_IN2, OUTPUT);
  digitalWrite(PIN_MOTOR_IN1, LOW); 
  digitalWrite(PIN_MOTOR_IN2, LOW);
  
  ledcAttach(PIN_MOTOR_PWM, 1000, 8); 
  ledcWrite(PIN_MOTOR_PWM, 0); 
  
  ledcAttach(PIN_SERVO, 50, 12); 
  escribirServoGrados(SERVO_CENTRO); 

  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RX_HUSKY, TX_HUSKY); 
  
  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(100000);
  Wire.setTimeout(50);

  pinMode(PIN_INICIO, INPUT_PULLDOWN);
  pinMode(PIN_TRIG_FRONTAL, OUTPUT); pinMode(PIN_ECHO_FRONTAL, INPUT);
  pinMode(PIN_TRIG_DERECHO, OUTPUT); pinMode(PIN_ECHO_DERECHO, INPUT);
  pinMode(PIN_TRIG_IZQUIERDO, OUTPUT); pinMode(PIN_ECHO_IZQUIERDO, INPUT);
  
  // ---> SISTEMA DE CONEXIÓN DE CÁMARA (5 INTENTOS) <---
  Serial.println("Conectando HuskyLens 2...");
  int intentos_camara = 0;
  while (!huskylens.begin(Serial1) && intentos_camara < 5) {
    Serial.println("Fallo al conectar con HuskyLens. Reintentando...");
    intentos_camara++;
    delay(500);
  }
  if (intentos_camara < 5) {
    Serial.println("HuskyLens conectada exitosamente!");
    huskylens.switchAlgorithm(ALGORITHM_COLOR_RECOGNITION);
  } else {
    Serial.println("HuskyLens NO detectada tras 5 intentos. Continuando sin cámara...");
  }

  Serial.println("Iniciando MPU6050...");
  mpu.begin(0x68, &Wire);
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG); 
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); 
  
  Serial.println("PULSA EL BOTON PARA ARRANCAR...");
  while (digitalRead(PIN_INICIO) == LOW) { delay(100); }

  Serial.println("Calibrando MPU...");
  delay(100); 
  float suma_gz = 0;
  for (int i = 0; i < 50; i++) { 
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    suma_gz += g.gyro.z;
    delay(10);
  }
  gz_offset = suma_gz / 50.0; 
  tiempo_anterior_mpu = millis();

  xTaskCreatePinnedToCore(tareaLeerMPU, "TareaMPU", 4096, NULL, 2, &TareaMPU, 0);
  
  delay(10);
  digitalWrite(PIN_MOTOR_IN1, HIGH); digitalWrite(PIN_MOTOR_IN2, LOW);
  ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_MOTOR);
  motor_encendido = true;
  tiempo_anterior = millis();
  tiempo_camara = millis();
  tiempo_sonar = millis();
  
  setpoint_base = 0.0; 
  direccion_global_pista = 0; // Se resetea en cada arranque
  
  Serial.println(">>> MODO TOTAL INICIADO (CAZADOR + PAREDES) <<<");
}

void loop() {
  unsigned long tiempo_actual = millis();

  // ========================================================
  // 0. MANIOBRA DE ALINEACIÓN PRE-ESQUIVE EN DOS PASOS ("S")
  // ========================================================
  if (en_alineacion_pre_esquive) {
    unsigned long tiempo_en_paso = tiempo_actual - tiempo_inicio_alineacion;

    if (paso_alineacion == 1) {
      if (tiempo_en_paso >= TIEMPO_REVERSA_ALIN_PASO1) {
        paso_alineacion = 2;
        tiempo_inicio_alineacion = tiempo_actual;
        
        if (direccion_alineacion == 1) escribirServoGrados(SERVO_CENTRO - MAX_DEFLEXION);
        else escribirServoGrados(SERVO_CENTRO + MAX_DEFLEXION);
      }
    }
    else if (paso_alineacion == 2) {
      if (tiempo_en_paso >= TIEMPO_REVERSA_ALIN_PASO2) {
        digitalWrite(PIN_MOTOR_IN1, HIGH); 
        digitalWrite(PIN_MOTOR_IN2, LOW); 
        ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_MOTOR);

        setpoint_yaw = setpoint_base; 
        
        en_alineacion_pre_esquive = false;
        paso_alineacion = 0;
        viendo_bloque = false; 
      }
    }
  }

  // ========================================================
  // 1. MANIOBRA DE ACOMODO EN REVERSA (PAREDES)
  // ========================================================
  else if (en_acomodo) {
    if (tiempo_actual - tiempo_inicio_acomodo >= TIEMPO_REVERSA) {
      digitalWrite(PIN_MOTOR_IN1, HIGH); 
      digitalWrite(PIN_MOTOR_IN2, LOW); 
      ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_MOTOR);

      if (direccion_esquina == 1) {
        setpoint_yaw -= GRADOS_GIRO;
        setpoint_base -= GRADOS_GIRO;
      } else {
        setpoint_yaw += GRADOS_GIRO;
        setpoint_base += GRADOS_GIRO;
      }

      en_acomodo = false;
      tiempo_fin_esquina = tiempo_actual;
    }
  }

  // ========================================================
  // 2. CÁMARA: CENTRAR Y COREOGRAFÍA DE BLOQUES (Cada 30 ms)
  // ========================================================
  else if (motor_encendido && !en_acomodo && !en_alineacion_pre_esquive && (tiempo_actual - tiempo_camara >= TIEMPO_CAMARA_MS)) {
    tiempo_camara = tiempo_actual;
    
    // --- ESTAMOS EN COREOGRAFÍA ---
    if (en_coreografia) {
      unsigned long tiempo_en_paso = tiempo_actual - tiempo_inicio_coreo;

      if (paso_coreografia == 1) { // FRENO
        if (tiempo_en_paso >= TIEMPO_FRENO) {
          ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_MOTOR);
          if (tipo_esquive == 1) setpoint_yaw -= GRADOS_ESQUIVE; 
          else setpoint_yaw += GRADOS_ESQUIVE;                   
          paso_coreografia = 2;
          tiempo_inicio_coreo = tiempo_actual;
        }
      }
      else if (paso_coreografia == 2) { // DIAGONAL SALIDA
        if (tiempo_en_paso >= TIEMPO_DIAG_SALIDA) {
          setpoint_yaw = setpoint_previo_coreo;
          paso_coreografia = 3;
          tiempo_inicio_coreo = tiempo_actual;
        }
      }
      else if (paso_coreografia == 3) { // RECTO
        if (tiempo_en_paso >= TIEMPO_RECTO_REBASE) {
          if (tipo_esquive == 1) setpoint_yaw += GRADOS_ESQUIVE; 
          else setpoint_yaw -= GRADOS_ESQUIVE;                   
          paso_coreografia = 4;
          tiempo_inicio_coreo = tiempo_actual;
        }
      }
      else if (paso_coreografia == 4) { // DIAGONAL REGRESO
        if (tiempo_en_paso >= TIEMPO_DIAG_REGRESO) {
          setpoint_yaw = setpoint_previo_coreo;
          
          // NUEVO: PASO 5 - REVERSA AL FINAL DEL ESQUIVE
          paso_coreografia = 5;
          tiempo_inicio_coreo = tiempo_actual;
          
          digitalWrite(PIN_MOTOR_IN1, LOW); 
          digitalWrite(PIN_MOTOR_IN2, HIGH); 
          ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_REVERSA_FINAL);
        }
      }
      else if (paso_coreografia == 5) { // REVERSA FINAL
        if (tiempo_en_paso >= TIEMPO_REVERSA_FINAL) {
          
          // Restauramos marcha hacia adelante
          digitalWrite(PIN_MOTOR_IN1, HIGH); 
          digitalWrite(PIN_MOTOR_IN2, LOW); 
          ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_MOTOR);
          
          paso_coreografia = 0;
          en_coreografia = false;
        }
      }
    } 
    // --- MODO CAZADOR ---
    else {
      bool bloque_visto_ahora = false;
      if (huskylens.getResult(ALGORITHM_COLOR_RECOGNITION)) {
        int x_actual = -1;
        int width_actual = -1;
        int id_actual = -1;
        
        while (huskylens.available(ALGORITHM_COLOR_RECOGNITION)) {
          Result *result = static_cast<Result *>(huskylens.popCachedResult(ALGORITHM_COLOR_RECOGNITION));
          
          bool ignorar = false;
          if (result->ID == 1 && result->xCenter < LIMITE_IGNORAR_ROJO) ignorar = true;
          if (result->ID == 2 && result->xCenter > LIMITE_IGNORAR_VERDE) ignorar = true;

          if (!ignorar && (result->ID == 1 || result->ID == 2) && result->width > width_actual) {
            width_actual = result->width;
            x_actual = result->xCenter;
            id_actual = result->ID;
            bloque_visto_ahora = true;
          }
        }

        if (bloque_visto_ahora) {
          viendo_bloque = true;
          tiempo_ultima_vista = tiempo_actual;

          float error_x = 320.0 - (float)x_actual;
          setpoint_yaw += (error_x * KP_CENTRAR); 

          if (width_actual >= ANCHO_DISPARO_ESQUIVE) {
            ledcWrite(PIN_MOTOR_PWM, 0); // FRENAMOS
            
            float desviacion = setpoint_yaw - setpoint_base;
            
            if (abs(desviacion) > TOLERANCIA_DIAGONAL) {
              en_alineacion_pre_esquive = true;
              paso_alineacion = 1;
              tiempo_inicio_alineacion = tiempo_actual;
              
              direccion_alineacion = (desviacion > 0) ? 1 : -1; 
              
              digitalWrite(PIN_MOTOR_IN1, LOW); 
              digitalWrite(PIN_MOTOR_IN2, HIGH); 
              ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_REVERSA_ALINEACION);

              if (direccion_alineacion == 1) escribirServoGrados(SERVO_CENTRO + MAX_DEFLEXION); 
              else escribirServoGrados(SERVO_CENTRO - MAX_DEFLEXION); 
              
            } else {
              en_coreografia = true;
              paso_coreografia = 1;
              tiempo_inicio_coreo = tiempo_actual;
              setpoint_previo_coreo = setpoint_base; 
              tipo_esquive = id_actual;
            }
          }
        }
      }
      
      if (!bloque_visto_ahora && viendo_bloque) {
        if (tiempo_actual - tiempo_ultima_vista > TIMEOUT_MEMORIA_CAMARA) {
          viendo_bloque = false; 
        }
      }
    }
  }

  // ========================================================
  // 3. SENSORES ULTRASÓNICOS (PAREDES) (Cada 50 ms)
  // ========================================================
  if (motor_encendido && !en_acomodo && !en_alineacion_pre_esquive && (tiempo_actual - tiempo_sonar >= TIEMPO_SONAR_MS)) {
    tiempo_sonar = tiempo_actual;
    
    if (turno_sensor == 0) dist_frontal = medirDistancia(PIN_TRIG_FRONTAL, PIN_ECHO_FRONTAL);
    else if (turno_sensor == 1) dist_derecha = medirDistancia(PIN_TRIG_DERECHO, PIN_ECHO_DERECHO);
    else dist_izquierda = medirDistancia(PIN_TRIG_IZQUIERDO, PIN_ECHO_IZQUIERDO);
    
    turno_sensor = (turno_sensor + 1) % 3;

    bool cooldown_pasado = (tiempo_actual - tiempo_fin_esquina > COOLDOWN_GIRO);

    if (cooldown_pasado && !en_coreografia && !viendo_bloque && dist_frontal <= DISTANCIA_GIRO) {
      
      // >>> AQUÍ ESTÁ EL BLINDAJE DE DIRECCIÓN (REGLA WRO) <<<
      // Si es la primera esquina de la carrera, decidimos y guardamos el sentido
      if (direccion_global_pista == 0) {
        if (dist_izquierda >= dist_derecha) {
          direccion_global_pista = 1;  // Pista de Izquierdas
          Serial.println("\n[PISTA DETECTADA] ¡Circuito de IZQUIERDAS! Bloqueando giros a la derecha.");
        } else {
          direccion_global_pista = -1; // Pista de Derechas
          Serial.println("\n[PISTA DETECTADA] ¡Circuito de DERECHAS! Bloqueando giros a la izquierda.");
        }
      }
      
      // Obligamos al carro a usar SIEMPRE la dirección global, ignorando qué sensor lea más espacio ahora
      direccion_esquina = direccion_global_pista; 
      
      en_acomodo = true;
      tiempo_inicio_acomodo = tiempo_actual;
      dist_frontal = 999.0; 

      digitalWrite(PIN_MOTOR_IN1, LOW); 
      digitalWrite(PIN_MOTOR_IN2, HIGH); 
      ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_REVERSA);

      if (direccion_esquina == 1) escribirServoGrados(SERVO_CENTRO - MAX_DEFLEXION); 
      else escribirServoGrados(SERVO_CENTRO + MAX_DEFLEXION); 
    }
  }

  // ========================================================
  // 4. CONTROL DE DIRECCIÓN MPU (Cada 1 ms)
  // ========================================================
  if (motor_encendido && !en_acomodo && !en_alineacion_pre_esquive && (tiempo_actual - tiempo_anterior >= TIEMPO_LECTURA_MS)) {
    float dt = (tiempo_actual - tiempo_anterior) / 1000.0;
    if (dt == 0) dt = 0.001;
    tiempo_anterior = tiempo_actual;

    float error = setpoint_yaw - yaw_actual;
    if (abs(error) < 2.0) { 
      error = 0.0; 
      error_anterior = 0.0; 
    }

    float derivada = (error - error_anterior) / dt;
    error_anterior = error;

    float correccion = (Kp * error) + (Kd * derivada);
    correccion = constrain(correccion, -MAX_DEFLEXION, MAX_DEFLEXION);
    
    angulo_servo_actual = SERVO_CENTRO - (int)correccion;
    escribirServoGrados(angulo_servo_actual);
  }
}