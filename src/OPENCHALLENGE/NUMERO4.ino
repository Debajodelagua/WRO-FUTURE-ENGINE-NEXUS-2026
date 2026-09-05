#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
SET_LOOP_TASK_STACK_SIZE(16384);

// --- Pines ---
const int PIN_SERVO     = 8;
const int PIN_MOTOR_PWM = 15;
const int PIN_MOTOR_IN1 = 5;
const int PIN_MOTOR_IN2 = 6;
const int PIN_INICIO    = 21;

const int PIN_SDA = 16;
const int PIN_SCL = 17;

const int PIN_TRIG_FRONTAL   = 42;
const int PIN_ECHO_FRONTAL   = 41;
const int PIN_TRIG_DERECHO   = 38;
const int PIN_ECHO_DERECHO   = 37;
const int PIN_TRIG_IZQUIERDO = 39;
const int PIN_ECHO_IZQUIERDO = 40;

// --- Panel de Tiempos ---
const unsigned long TIEMPO_LECTURA_MS    = 1;
const unsigned long TIEMPO_SONAR_MS      = 50;
const unsigned long TIEMPO_SERIAL_MS     = 100;
const unsigned long TIEMPO_ESPERA_MOTOR  = 10;

// --- Configuración Servo ---
const int SERVO_CENTRO  = 96;
const int MAX_DEFLEXION = 21;

// =========================================================
// VARIABLES AJUSTABLES PARA CALIBRAR
// =========================================================
float DISTANCIA_GIRO          = 70.0;  
float GRADOS_GIRO             = 89.0;  
unsigned long COOLDOWN_GIRO_MS = 500; 

// ---> DISTANCIA LIBRE LATERAL (Aplica para el lado que elija) <---
float DISTANCIA_LIBRE_LATERAL = 70.0;  

float DISTANCIA_MIN_LATERAL   = 25.0;  
float ANGULO_ESCAPE           = 25.0;  

// ---> CONTROL DE TIEMPOS DE ARRANQUE Y MANIOBRAS <---
int MUESTRAS_CALIBRACION_MPU         = 50;   // Cantidad de lecturas para calibrar
unsigned long TIEMPO_PRE_CALIBRACION = 100;  // ms: Pausa ANTES de calibrar el MPU
unsigned long TIEMPO_CEGUERA_INICIAL = 500;  // ms: Tiempo rodando sin detectar esquinas al arrancar
unsigned long TIMEOUT_GIRO           = 2500; // ms: Tiempo máximo que puede durar un giro
unsigned long TIEMPO_PARO_FIN        = 1500; // ms: Tiempo para apagar motores tras la esquina 12
// =========================================================

// --- Variables MPU ---
volatile float yaw_actual = 0.0;
volatile float gz_offset = 0.0;
unsigned long tiempo_anterior_mpu = 0;
TaskHandle_t TareaMPU;

// --- Variables de Control PD ---
float setpoint_yaw = 0.0;
float offset_lateral = 0.0;
float error_anterior = 0.0;
int angulo_servo_actual = SERVO_CENTRO;

float Kp = 1.0;
float Kd = 0.0;
const float ZONA_MUERTA = 2.0;

// --- Variables Ultrasónico ---
float dist_frontal   = 999.0;
float dist_derecha   = 999.0;
float dist_izquierda = 999.0;
int turno_sensor = 0;

bool en_maniobra = false;
unsigned long tiempo_inicio_giro = 0;
unsigned long tiempo_fin_maniobra = 0;

// --- Variables de Carrera y Dirección ---
int esquinas_contadas = 0;
int direccion_giro = 0; 
bool carrera_terminada = false;
bool motor_frenado = false;
unsigned long tiempo_fin_carrera = 0;

unsigned long tiempo_anterior = 0;
unsigned long tiempo_sonar = 0;
unsigned long tiempo_serial = 0;
unsigned long tiempo_inicio_motor = 0;
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
  // 1. BLOQUE DE EMERGENCIA: APAGAR TODO ANTES DE HACER CUALQUIER OTRA COSA
  pinMode(PIN_MOTOR_IN1, OUTPUT); 
  pinMode(PIN_MOTOR_IN2, OUTPUT);
  digitalWrite(PIN_MOTOR_IN1, LOW); 
  digitalWrite(PIN_MOTOR_IN2, LOW);
  
  ledcAttach(PIN_MOTOR_PWM, 1000, 8); 
  ledcWrite(PIN_MOTOR_PWM, 0); // Forzar motor a velocidad cero
  
  ledcAttach(PIN_SERVO, 50, 12); 
  escribirServoGrados(SERVO_CENTRO); // Clavar el servo al centro inmediatamente

  // 2. INICIAR COMUNICACIONES (Ahora es seguro porque los motores ya están bloqueados)
  Serial.begin(115200);
  Wire.begin(PIN_SDA, PIN_SCL);
  Wire.setClock(100000);
  Wire.setTimeout(50);

  // 3. INICIAR SENSORES Y BOTÓN
  pinMode(PIN_INICIO, INPUT_PULLDOWN);
  pinMode(PIN_TRIG_FRONTAL, OUTPUT); pinMode(PIN_ECHO_FRONTAL, INPUT);
  pinMode(PIN_TRIG_DERECHO, OUTPUT); pinMode(PIN_ECHO_DERECHO, INPUT);
  pinMode(PIN_TRIG_IZQUIERDO, OUTPUT); pinMode(PIN_ECHO_IZQUIERDO, INPUT);
  
  Serial.println("Iniciando MPU6050...");
  mpu.begin(0x68, &Wire);
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG); 
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); 
  
  Serial.println("Esperando senal pin 21 para arrancar...");
  while (digitalRead(PIN_INICIO) == LOW) { delay(100); }

  Serial.println("Calibrando MPU... NO TOQUES EL CARRO!");
  delay(TIEMPO_PRE_CALIBRACION); 
  
  float suma_gz = 0;
  for (int i = 0; i < MUESTRAS_CALIBRACION_MPU; i++) { 
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    suma_gz += g.gyro.z;
    delay(10);
  }
  gz_offset = suma_gz / (float)MUESTRAS_CALIBRACION_MPU; 
  tiempo_anterior_mpu = millis();

  xTaskCreatePinnedToCore(tareaLeerMPU, "TareaMPU", 4096, NULL, 2, &TareaMPU, 0);
  
  delay(TIEMPO_ESPERA_MOTOR);
  
  digitalWrite(PIN_MOTOR_IN1, HIGH); digitalWrite(PIN_MOTOR_IN2, LOW);
  ledcWrite(PIN_MOTOR_PWM, 255);
  motor_encendido = true;
  tiempo_inicio_motor = millis();
  tiempo_anterior = millis();
  
  Serial.println("SISTEMA ACTIVO: DETECCIÓN INTELIGENTE DE 1RA ESQUINA (12 VUELTAS)");
}

void loop() {
  unsigned long tiempo_actual = millis();

  // ========================================================
  // 0. CONTROL DE FIN DE CARRERA
  // ========================================================
  if (carrera_terminada && !motor_frenado) {
    if (tiempo_actual - tiempo_fin_carrera >= TIEMPO_PARO_FIN) {
      digitalWrite(PIN_MOTOR_IN1, LOW);
      digitalWrite(PIN_MOTOR_IN2, LOW);
      ledcWrite(PIN_MOTOR_PWM, 0);
      escribirServoGrados(SERVO_CENTRO);
      motor_frenado = true;
      Serial.println("\n=== 12 ESQUINAS COMPLETADAS - MOTOR APAGADO ===");
    }
  }

  // ========================================================
  // 1. CONTROL DE DIRECCIÓN Y MANIOBRA (Cada 1 ms)
  // ========================================================
  if (motor_encendido && !motor_frenado && (tiempo_actual - tiempo_anterior >= TIEMPO_LECTURA_MS)) {
    float dt = (tiempo_actual - tiempo_anterior) / 1000.0;
    if (dt == 0) dt = 0.001;
    tiempo_anterior = tiempo_actual;

    if (en_maniobra) {
      bool giro_completado = abs(setpoint_yaw - yaw_actual) < 8.0; 
      bool tiempo_agotado = (tiempo_actual - tiempo_inicio_giro > TIMEOUT_GIRO); 

      if (giro_completado || tiempo_agotado) {
        en_maniobra = false;
        if (tiempo_agotado) {
           setpoint_yaw = yaw_actual; 
           Serial.println(">>> GIRO ABORTADO POR TIMEOUT");
        } else {
           Serial.println(">>> GIRO COMPLETADO AL SETPOINT");
        }
        tiempo_fin_maniobra = tiempo_actual; 
        dist_frontal = 999.0; 
      }
    }

    float setpoint_efectivo = setpoint_yaw + offset_lateral;
    float error = setpoint_efectivo - yaw_actual;
    if (abs(error) < ZONA_MUERTA) { 
      error = 0.0; 
      error_anterior = 0.0; 
    }

    float derivada = (error - error_anterior) / dt;
    error_anterior = error;

    float correccion = (Kp * error) + (Kd * derivada);
    correccion = constrain(correccion, -MAX_DEFLEXION, MAX_DEFLEXION);
    
    // --- DECISIÓN DEL SERVO ---
    if (en_maniobra) {
      if (error < 0) { 
        angulo_servo_actual = SERVO_CENTRO + MAX_DEFLEXION; 
      } else {         
        angulo_servo_actual = SERVO_CENTRO - MAX_DEFLEXION; 
      }
    } else {
      angulo_servo_actual = SERVO_CENTRO - (int)correccion;
    }
    
    escribirServoGrados(angulo_servo_actual);
  }

  // ========================================================
  // 2. SENSORES ULTRASÓNICOS (Cada 50 ms)
  // ========================================================
  if (motor_encendido && !motor_frenado && (tiempo_actual - tiempo_sonar >= TIEMPO_SONAR_MS)) {
    tiempo_sonar = tiempo_actual;
    
    if (turno_sensor == 0 || turno_sensor == 2) {
      dist_frontal = medirDistancia(PIN_TRIG_FRONTAL, PIN_ECHO_FRONTAL);
    } else if (turno_sensor == 1) {
      dist_derecha = medirDistancia(PIN_TRIG_DERECHO, PIN_ECHO_DERECHO);
    } else {
      dist_izquierda = medirDistancia(PIN_TRIG_IZQUIERDO, PIN_ECHO_IZQUIERDO);
    }
    turno_sensor = (turno_sensor + 1) % 4;

    offset_lateral = 0.0; 
    
    if (!en_maniobra) {
      bool cooldown_pasado = (tiempo_actual - tiempo_fin_maniobra > COOLDOWN_GIRO_MS);
      bool arranque_pasado = (tiempo_actual - tiempo_inicio_motor > TIEMPO_CEGUERA_INICIAL);
      
      // 2A. DETECCIÓN DE ESQUINA INTELIGENTE Y CONTEO
      if (cooldown_pasado && arranque_pasado) {
        if (dist_frontal <= DISTANCIA_GIRO) {
          
          if (direccion_giro == 0) {
            if (dist_izquierda >= dist_derecha) {
              direccion_giro = 1; // Izquierda
              Serial.println(">>> PRIMERA ESQUINA: MÁS ESPACIO A LA IZQ. GUARDANDO GIRO A LA IZQUIERDA.");
            } else {
              direccion_giro = -1; // Derecha
              Serial.println(">>> PRIMERA ESQUINA: MÁS ESPACIO A LA DER. GUARDANDO GIRO A LA DERECHA.");
            }
          }

          bool espacio_seguro = false;
          if (direccion_giro == 1 && dist_izquierda >= DISTANCIA_LIBRE_LATERAL) espacio_seguro = true;
          if (direccion_giro == -1 && dist_derecha >= DISTANCIA_LIBRE_LATERAL) espacio_seguro = true;

          if (espacio_seguro) {
            if (direccion_giro == 1) {
              setpoint_yaw -= GRADOS_GIRO; 
              angulo_servo_actual = SERVO_CENTRO + MAX_DEFLEXION;
            } else {
              setpoint_yaw += GRADOS_GIRO; 
              angulo_servo_actual = SERVO_CENTRO - MAX_DEFLEXION;
            }
            
            en_maniobra = true;
            tiempo_inicio_giro = tiempo_actual; 
            
            escribirServoGrados(angulo_servo_actual); 
            
            esquinas_contadas++;
            Serial.print(">>> PARED DETECTADA. Esquina #"); Serial.print(esquinas_contadas);
            Serial.print(" | Nuevo SP: "); Serial.println(setpoint_yaw, 0);

            if (esquinas_contadas >= 12 && !carrera_terminada) {
              carrera_terminada = true;
              tiempo_fin_carrera = tiempo_actual;
              Serial.println(">>> 12 ESQUINAS ALCANZADAS. APAGANDO EN EL TIEMPO SETEADO...");
            }
          }
        }
      }

      // 2B. ESCAPE LATERAL
      if (cooldown_pasado) {
        if (dist_derecha < DISTANCIA_MIN_LATERAL) {
          offset_lateral -= ANGULO_ESCAPE; 
        }
        if (dist_izquierda < DISTANCIA_MIN_LATERAL) {
          offset_lateral += ANGULO_ESCAPE; 
        }
      }
    }
  }

  // ========================================================
  // 3. TELEMETRÍA (Cada 100 ms)
  // ========================================================
  if (tiempo_actual - tiempo_serial >= TIEMPO_SERIAL_MS) {
    tiempo_serial = tiempo_actual;
    
    if (motor_frenado) {
      Serial.println("[CARRERA FINALIZADA - MOTOR APAGADO]");
    } else {
      Serial.print("Esquinas:"); Serial.print(esquinas_contadas);
      Serial.print(" | F:"); if (dist_frontal > 250) Serial.print("---"); else Serial.print(dist_frontal, 0);
      Serial.print(" D:"); if (dist_derecha > 250) Serial.print("---"); else Serial.print(dist_derecha, 0);
      Serial.print(" I:"); if (dist_izquierda > 250) Serial.print("---"); else Serial.print(dist_izquierda, 0);
      
      Serial.print(" | Yaw:"); Serial.print(yaw_actual, 1);
      Serial.print(" SP:"); Serial.print(setpoint_yaw, 1);
      Serial.print(" Servo:"); Serial.print(angulo_servo_actual);
      
      if (en_maniobra) Serial.println(" [GIRANDO]");
      else if (offset_lateral != 0.0) Serial.println(" [ESCAPE LATERAL]");
      else Serial.println(" [RECTO]");
    }
  }
}