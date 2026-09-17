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
const unsigned long TIEMPO_CAMARA_MS     = 30; 
const unsigned long TIEMPO_SONAR_MS      = 50; 
const unsigned long TIEMPO_SERIAL_MS     = 100;

// --- Configuración Motor y Servo ---
const int SERVO_CENTRO  = 96;
const int MAX_DEFLEXION = 21;   
int VELOCIDAD_MOTOR     = 80;  

// =========================================================
// ---> PARAMETROS DE CABECEO (BÚSQUEDA DE CUBOS) <---
// =========================================================
bool HABILITAR_CABECEO       = true;    // Activa o desactiva la función
unsigned long TIEMPO_CABECEO = 1500;    // ms que dura haciendo el cabeceo al terminar maniobras
float AMPLITUD_CABECEO       = 40.0;    // Grados máximos hacia los que girará (amplitud del barrido)
float VELOCIDAD_CABECEO      = 0.006;   // Velocidad del vaivén (mayor = más rápido)
unsigned long TIEMPO_ESTABILIZACION = 300; // ms para calmar inercia antes de atacar el cubo

// =========================================================
// ---> CONTROL DE ESQUIVE VISUAL FLUIDO (CAZADOR) <---
// =========================================================
// FUERZAS INDEPENDIENTES (CENTRAR vs ESQUIVAR)
float KP_CENTRAR        = 0.005;  // Fuerza para perseguir y centrar el cubo desde lejos
float KP_ESQUIVE_ROJO   = 0.009;  // Fuerza del latigazo para esquivar ROJO
float KP_ESQUIVE_VERDE  = 0.010;  // Fuerza del latigazo para esquivar VERDE

// PARÁMETROS DE DISTANCIA (TAMAÑO)
int MIN_WIDTH_ESQUIVE    = 70;   // Menor a esto = lo ignora.
int WIDTH_INICIO_ESQUIVE = 180;  // Entre 60 y 150 SOLO LO CENTRA. A partir de 150 da el latigazo.
int WIDTH_CERCA          = 200;  
int BORDE_IZQ            = -100; // Objetivo extremo izquierdo
int BORDE_DER            = 740;  // Objetivo extremo derecho

unsigned long TIEMPO_ESCAPE = 100; // ms extra en diagonal para librar llantas traseras

// --- RETORNO CONSCIENTE Y SIMÉTRICO (POR COLORES) ---
// RETORNO BLOQUE ROJO (Pasa por Derecha, regresa a Izquierda)
float MULTIPLICADOR_ANGULO_RETORNO_ROJO = 2.0; 
float MULTIPLICADOR_TIEMPO_RETORNO_ROJO = 1.0; 
unsigned long MAX_TIEMPO_RETORNO_ROJO   = 2000; // <-- NUEVO: Tope máximo para el tiempo de regreso ROJO

// RETORNO BLOQUE VERDE (Pasa por Izquierda, regresa a Derecha)
float MULTIPLICADOR_ANGULO_RETORNO_VERDE = 2.0; 
float MULTIPLICADOR_TIEMPO_RETORNO_VERDE = 0.7; 
unsigned long MAX_TIEMPO_RETORNO_VERDE   = 2000; // <-- NUEVO: Tope máximo para el tiempo de regreso VERDE

// Memoria interna del robot para el cálculo
unsigned long tiempo_inicio_arrastre = 0;
unsigned long duracion_arrastre = 0;
float desviacion_memoria = 0.0;
unsigned long tiempo_retorno_dinamico = 0;

// --- FASES DESPUÉS DE ESQUIVAR (ALINEAR Y REVERSA) ---
unsigned long TIEMPO_ALINEACION           = 1000; // ms avanza recto permitiendo al PID enderezar el chasis
unsigned long TIEMPO_REVERSA_POST_ESQUIVE = 1300; // ms de reversa (después de alinear)
int VELOCIDAD_REVERSA_ESQUIVE             = 90;   // Velocidad de la reversa post-esquive

// --- COOLDOWNS POST-ESQUIVE Y POST-ESQUINA ---
unsigned long COOLDOWN_ENTRE_BLOQUES       = 400;  // ms de ceguera de CÁMARA tras esquivar un bloque
unsigned long COOLDOWN_POST_ESQUIVE        = 2000; // ms de ceguera de ULTRASONIDO tras esquivar
unsigned long COOLDOWN_CAMARA_POST_ESQUINA = 700;  // ms de ceguera de CÁMARA tras doblar esquina

// LÍMITES PARA IGNORAR BLOQUES YA LIBRADOS
int LIMITE_IGNORAR_ROJO       = 80;     
int LIMITE_IGNORAR_VERDE      = 560;   
unsigned long TIMEOUT_MEMORIA_CAMARA = 400; 

// =========================================================
// ---> CONTROL DE ESQUINAS Y ACOMODO (PAREDES) <---
// =========================================================
float DISTANCIA_GIRO          = 12.0;  
unsigned long TIEMPO_REVERSA  = 1900;  
int VELOCIDAD_REVERSA         = 140;   
float GRADOS_GIRO             = 89.8;  
unsigned long COOLDOWN_GIRO   = 3000;  
int MAX_DEFLEXION_ESQUINA     = 32;    

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

// --- Variables Lógica de Cámara Fluida ---
bool viendo_bloque = false;
unsigned long tiempo_ultima_vista = 0;
bool camara_conectada = false; 

bool en_escape = false;
unsigned long tiempo_inicio_escape = 0;
unsigned long tiempo_fin_escape = 0; 

bool en_retorno = false;
unsigned long tiempo_inicio_retorno = 0;

bool en_alineacion = false; 
unsigned long tiempo_inicio_alineacion = 0;

bool en_reversa_post_esquive = false;
unsigned long tiempo_inicio_reversa_esquive = 0;
unsigned long tiempo_fin_retorno = 0; 
int ultimo_id_visto = 0; 

int ancho_telemetria = 0;      
int target_x_telemetria = 320; 

// --- Variables de Cabeceo ---
bool en_cabeceo = false;
unsigned long tiempo_inicio_cabeceo = 0;
bool en_centrado_cabeceo = false;          
unsigned long tiempo_inicio_centrado = 0; 

// --- Variables Ultrasónico (Paredes) ---
float dist_frontal = 999.0, dist_derecha = 999.0, dist_izquierda = 999.0;
int turno_sensor = 0;

int direccion_global_pista = 0; 

bool en_acomodo = false;
bool esquina_alcanzada = false;
unsigned long tiempo_inicio_acomodo = 0;
unsigned long tiempo_fin_esquina = 0;
int direccion_esquina = 0; 

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
  
  Serial.println("Iniciando MPU6050...");
  mpu.begin(0x68, &Wire);
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG); 
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); 
  
  Serial.println("PULSA EL BOTON PARA ARRANCAR...");
  Serial.println("(Buscando cámara HuskyLens en segundo plano...)");
  
  unsigned long t_reintento = 0;
  while (digitalRead(PIN_INICIO) == LOW) { 
    if (!camara_conectada && millis() - t_reintento > 500) {
      t_reintento = millis();
      if (huskylens.begin(Serial1)) {
        Serial.println("¡HuskyLens CONECTADA exitosamente!");
        huskylens.switchAlgorithm(ALGORITHM_OBJECT_TRACKING);
        camara_conectada = true;
      }
    }
    delay(10); 
  }

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
  tiempo_serial = millis();
  
  setpoint_base = 0.0; 
  direccion_global_pista = 0; 
  
  Serial.println(">>> MODO ARRASTRE FLUIDO (CAZADOR + PAREDES) <<<");
}

void loop() {
  unsigned long tiempo_actual = millis();

  // ========================================================
  // 1. MANIOBRA DE ACOMODO EN REVERSA (PAREDES)
  // ========================================================
  if (en_acomodo) {
    
    if (!esquina_alcanzada) {
      float error_esquina = setpoint_yaw - yaw_actual; 
      if (abs(error_esquina) < 7.0) { 
        esquina_alcanzada = true;
      }
    }

    if (esquina_alcanzada) {
      escribirServoGrados(SERVO_CENTRO);
    } else {
      if (direccion_esquina == 1) escribirServoGrados(SERVO_CENTRO - MAX_DEFLEXION_ESQUINA); 
      else escribirServoGrados(SERVO_CENTRO + MAX_DEFLEXION_ESQUINA); 
    }

    if (tiempo_actual - tiempo_inicio_acomodo >= TIEMPO_REVERSA) {
      digitalWrite(PIN_MOTOR_IN1, HIGH); 
      digitalWrite(PIN_MOTOR_IN2, LOW); 
      ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_MOTOR);

      en_acomodo = false;
      tiempo_fin_esquina = tiempo_actual;

      // Iniciar el cabeceo al terminar la esquina
      if (HABILITAR_CABECEO) {
        en_cabeceo = true;
        tiempo_inicio_cabeceo = tiempo_actual;
      }
    }
  }

  // ========================================================
  // 2. CÁMARA: ARRASTRE FLUIDO (Cada 30 ms)
  // ========================================================
  else if (motor_encendido && !en_acomodo && (tiempo_actual - tiempo_camara >= TIEMPO_CAMARA_MS)) {
    tiempo_camara = tiempo_actual;
    
    // --- FASE 4: REVERSA POST-ESQUIVE ---
    if (en_reversa_post_esquive) {
      escribirServoGrados(SERVO_CENTRO); 
      
      if (tiempo_actual - tiempo_inicio_reversa_esquive >= TIEMPO_REVERSA_POST_ESQUIVE) {
        en_reversa_post_esquive = false;
        tiempo_fin_retorno = tiempo_actual; 
        
        digitalWrite(PIN_MOTOR_IN1, HIGH); 
        digitalWrite(PIN_MOTOR_IN2, LOW); 
        ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_MOTOR);

        // Iniciar el cabeceo al terminar de esquivar
        if (HABILITAR_CABECEO) {
          en_cabeceo = true;
          tiempo_inicio_cabeceo = tiempo_actual;
        }
      }
    }

    // --- FASE 3: ALINEACIÓN PRE-REVERSA ---
    if (en_alineacion) {
      if (tiempo_actual - tiempo_inicio_alineacion >= TIEMPO_ALINEACION) {
        en_alineacion = false;
        
        en_reversa_post_esquive = true;
        tiempo_inicio_reversa_esquive = tiempo_actual;
        
        digitalWrite(PIN_MOTOR_IN1, LOW); 
        digitalWrite(PIN_MOTOR_IN2, HIGH); 
        ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_REVERSA_ESQUIVE);
      }
    }

    // --- FASE 2: RETORNO CONSCIENTE ---
    if (en_retorno && !en_alineacion && !en_reversa_post_esquive) {
      if (tiempo_actual - tiempo_inicio_retorno >= tiempo_retorno_dinamico) {
        en_retorno = false;
        
        setpoint_yaw = setpoint_base; 
        
        en_alineacion = true;
        tiempo_inicio_alineacion = tiempo_actual;
      }
    }

    // --- FASE 1: ESCAPE DE SEGURIDAD ---
    if (en_escape) {
      if (tiempo_actual - tiempo_inicio_escape >= TIEMPO_ESCAPE) {
        en_escape = false;
        en_retorno = true;
        tiempo_inicio_retorno = tiempo_actual;
        tiempo_fin_escape = tiempo_actual; 
        
        // ¡LA MAGIA SEPARADA POR COLORES (Y CON LÍMITES)!
        if (ultimo_id_visto == 1) { // ROJO
          setpoint_yaw = setpoint_base - (desviacion_memoria * MULTIPLICADOR_ANGULO_RETORNO_ROJO);
          tiempo_retorno_dinamico = (duracion_arrastre + TIEMPO_ESCAPE) * MULTIPLICADOR_TIEMPO_RETORNO_ROJO;
          if (tiempo_retorno_dinamico > MAX_TIEMPO_RETORNO_ROJO) {
            tiempo_retorno_dinamico = MAX_TIEMPO_RETORNO_ROJO;
          }
        } else if (ultimo_id_visto == 2) { // VERDE
          setpoint_yaw = setpoint_base - (desviacion_memoria * MULTIPLICADOR_ANGULO_RETORNO_VERDE);
          tiempo_retorno_dinamico = (duracion_arrastre + TIEMPO_ESCAPE) * MULTIPLICADOR_TIEMPO_RETORNO_VERDE;
          if (tiempo_retorno_dinamico > MAX_TIEMPO_RETORNO_VERDE) {
            tiempo_retorno_dinamico = MAX_TIEMPO_RETORNO_VERDE;
          }
        }
      }
    }

    // --- FASE DE CABECEO (BÚSQUEDA) ---
    if (en_cabeceo && !en_reversa_post_esquive) {
      unsigned long tiempo_transcurrido = tiempo_actual - tiempo_inicio_cabeceo;
      
      if (tiempo_transcurrido >= TIEMPO_CABECEO) {
        en_cabeceo = false;
        setpoint_yaw = setpoint_base; // Retorna a ruta recta
      } else {
        // Genera el vaivén usando la función matemática seno
        float desviacion = sin(tiempo_transcurrido * VELOCIDAD_CABECEO) * AMPLITUD_CABECEO;
        setpoint_yaw = setpoint_base + desviacion;
      }
    }

    // --- NUEVO: FASE DE ESTABILIZACIÓN POST-CABECEO ---
    if (en_centrado_cabeceo) {
      if (tiempo_actual - tiempo_inicio_centrado >= TIEMPO_ESTABILIZACION) {
        en_centrado_cabeceo = false;
      } else {
        setpoint_yaw = setpoint_base; // Obliga al volante a estar centrado para matar inercia
      }
    }
    
    bool bloque_visto_ahora = false;
    int x_actual = -1;
    int width_actual = -1;
    int id_actual = -1;
    
    bool cooldown_bloques_pasado = (tiempo_actual - tiempo_fin_retorno > COOLDOWN_ENTRE_BLOQUES);
    bool cooldown_camara_esquina_pasado = (tiempo_actual - tiempo_fin_esquina > COOLDOWN_CAMARA_POST_ESQUINA);

    // OJO: Permitimos que la cámara lea aunque estemos en cabeceo, esa es la meta
    if (camara_conectada && !en_escape && !en_retorno && !en_alineacion && !en_reversa_post_esquive && cooldown_bloques_pasado && cooldown_camara_esquina_pasado && huskylens.getResult(ALGORITHM_OBJECT_TRACKING)) {
      while (huskylens.available(ALGORITHM_OBJECT_TRACKING)) {
        Result *result = static_cast<Result *>(huskylens.popCachedResult(ALGORITHM_OBJECT_TRACKING));
        
        bool ignorar = false;
        
        if (result->width < MIN_WIDTH_ESQUIVE) ignorar = true; // Si está muy lejos, se ignora por completo
        
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
        
        // --- INTERRUPCIÓN DE CABECEO Y ACTIVACIÓN DE ESTABILIZACIÓN ---
        if (en_cabeceo) {
          en_cabeceo = false;
          en_centrado_cabeceo = true;
          tiempo_inicio_centrado = tiempo_actual;
          setpoint_yaw = setpoint_base;
        }

        // Siempre registramos que vimos el bloque para no perder memoria
        tiempo_ultima_vista = tiempo_actual;
        ultimo_id_visto = id_actual; 
        ancho_telemetria = width_actual; 
        
        // SOLO iniciamos el control visual si NO estamos estabilizando la inercia
        if (!en_centrado_cabeceo) {

          if (!viendo_bloque) {
            viendo_bloque = true;
            tiempo_inicio_arrastre = tiempo_actual; // Inicia el cronómetro visual
          }

          // --- FASE 1: CENTRAR (Cazar) vs FASE 2: ESQUIVAR (Latigazo) ---
          int target_x = 320;
          float kp_actual = KP_CENTRAR; 
          
          if (width_actual <= WIDTH_INICIO_ESQUIVE) {
            // MODO CENTRAR: Fija la mira exactamente en el centro (320)
            target_x = 320;
            kp_actual = KP_CENTRAR;
          } else {
            // MODO ESQUIVAR: Empieza a aventarlo hacia los bordes
            int width_mapeado = constrain(width_actual, WIDTH_INICIO_ESQUIVE, WIDTH_CERCA);
            if (id_actual == 1) { 
              target_x = map(width_mapeado, WIDTH_INICIO_ESQUIVE, WIDTH_CERCA, 320, BORDE_IZQ);
              kp_actual = KP_ESQUIVE_ROJO;
            } else if (id_actual == 2) { 
              target_x = map(width_mapeado, WIDTH_INICIO_ESQUIVE, WIDTH_CERCA, 320, BORDE_DER);
              kp_actual = KP_ESQUIVE_VERDE;
            }
          }
          
          target_x_telemetria = target_x; 

          float error_x = target_x - (float)x_actual;
          setpoint_yaw += (error_x * kp_actual); 
        }
      }
    }
    
    if (!bloque_visto_ahora) {
      ancho_telemetria = 0; 
      
      if (viendo_bloque) {
        if (tiempo_actual - tiempo_ultima_vista > TIMEOUT_MEMORIA_CAMARA) {
          viendo_bloque = false; 

          // --- GUARDAR MEMORIA FINAL DEL ESQUIVE ANTES DE ESCAPAR ---
          duracion_arrastre = tiempo_actual - tiempo_inicio_arrastre; // Cuánto tiempo duró abierto
          desviacion_memoria = setpoint_yaw - setpoint_base; // Cuántos grados se alejó del carril original

          en_escape = true; 
          tiempo_inicio_escape = tiempo_actual;
        }
      }
    }
  }

  // ========================================================
  // 3. SENSORES ULTRASÓNICOS (PAREDES) (Cada 50 ms)
  // ========================================================
  if (motor_encendido && !en_acomodo && (tiempo_actual - tiempo_sonar >= TIEMPO_SONAR_MS)) {
    tiempo_sonar = tiempo_actual;
    
    if (turno_sensor == 0) dist_frontal = medirDistancia(PIN_TRIG_FRONTAL, PIN_ECHO_FRONTAL);
    else if (turno_sensor == 1) dist_derecha = medirDistancia(PIN_TRIG_DERECHO, PIN_ECHO_DERECHO);
    else dist_izquierda = medirDistancia(PIN_TRIG_IZQUIERDO, PIN_ECHO_IZQUIERDO);
    
    turno_sensor = (turno_sensor + 1) % 3;

    bool cooldown_pasado = (tiempo_actual - tiempo_fin_esquina > COOLDOWN_GIRO);
    bool cooldown_post_esquive_pasado = (tiempo_actual - tiempo_fin_escape > COOLDOWN_POST_ESQUIVE);

    if (cooldown_pasado && cooldown_post_esquive_pasado && !viendo_bloque && !en_escape && !en_retorno && !en_alineacion && !en_reversa_post_esquive && dist_frontal <= DISTANCIA_GIRO) {
      
      if (direccion_global_pista == 0) {
        if (dist_izquierda >= dist_derecha) {
          direccion_global_pista = 1;  
          Serial.println("\n[PISTA] IZQUIERDAS.");
        } else {
          direccion_global_pista = -1; 
          Serial.println("\n[PISTA] DERECHAS.");
        }
      }
      
      direccion_esquina = direccion_global_pista; 
      
      en_acomodo = true;
      esquina_alcanzada = false; 
      tiempo_inicio_acomodo = tiempo_actual;
      dist_frontal = 999.0; 

      if (direccion_esquina == 1) {
        setpoint_yaw -= GRADOS_GIRO;
        setpoint_base -= GRADOS_GIRO;
      } else {
        setpoint_yaw += GRADOS_GIRO;
        setpoint_base += GRADOS_GIRO;
      }

      digitalWrite(PIN_MOTOR_IN1, LOW); 
      digitalWrite(PIN_MOTOR_IN2, HIGH); 
      ledcWrite(PIN_MOTOR_PWM, VELOCIDAD_REVERSA);
      
      if (direccion_esquina == 1) escribirServoGrados(SERVO_CENTRO - MAX_DEFLEXION_ESQUINA); 
      else escribirServoGrados(SERVO_CENTRO + MAX_DEFLEXION_ESQUINA); 
    }
  }

  // ========================================================
  // 4. CONTROL DE DIRECCIÓN MPU (Cada 1 ms)
  // ========================================================
  if (motor_encendido && !en_acomodo && !en_reversa_post_esquive && (tiempo_actual - tiempo_anterior >= TIEMPO_LECTURA_MS)) {
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

  // ========================================================
  // 5. TELEMETRÍA (Cada 100 ms)
  // ========================================================
  if (motor_encendido && (tiempo_actual - tiempo_serial >= TIEMPO_SERIAL_MS)) {
    tiempo_serial = tiempo_actual;
    
    bool cooldown_bloques_pasado = (tiempo_actual - tiempo_fin_retorno > COOLDOWN_ENTRE_BLOQUES);
    bool cooldown_camara_esquina_pasado = (tiempo_actual - tiempo_fin_esquina > COOLDOWN_CAMARA_POST_ESQUINA);

    Serial.print("Yaw:"); Serial.print(yaw_actual, 1);
    Serial.print(" | SP:"); Serial.print(setpoint_yaw, 1);
    Serial.print(" | AnchoObj:"); Serial.print(ancho_telemetria);
    Serial.print(" | TargetX:"); Serial.print(target_x_telemetria);
    
    if (viendo_bloque) Serial.println(" [ARRASTRANDO]");
    else if (en_escape) Serial.println(" [ESCAPANDO]");
    else if (en_retorno) Serial.println(" [RETORNANDO SIMÉTRICO]");
    else if (en_alineacion) Serial.println(" [ALINEANDO PRE-REVERSA]");
    else if (en_reversa_post_esquive) Serial.println(" [REVERSA POST-ESQUIVE]");
    else if (en_cabeceo) Serial.println(" [CABECEO / BUSCANDO]");
    else if (en_centrado_cabeceo) Serial.println(" [ESTABILIZANDO INERCIA]");
    else if (!cooldown_bloques_pasado || !cooldown_camara_esquina_pasado) Serial.println(" [IGNORANDO BLOQUES (COOLDOWN)]");
    else if (en_acomodo) {
      if (esquina_alcanzada) Serial.println(" [ESQUINA - RETROCEDIENDO RECTO]");
      else Serial.println(" [ESQUINA - CRUZADO]");
    }
    else Serial.println(" [RECTO / BUSCANDO]");
  }
}