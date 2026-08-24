# 🏎️ WRO 2026 Future Engineers – Team Nexus

<div align="center">
  <img src="./Otro/NEXUS_LOGO.jpg" alt="Team Nexus Autonomous Vehicle" width="600" style="border-radius: 15px;">

  [![Instagram](https://img.shields.io/badge/Instagram-%23E4405F.svg?style=for-the-badge&logo=Instagram&logoColor=white)](https://www.instagram.com/iniar_zulia/)
  [![Team](https://img.shields.io/badge/Team-Nexus-blue?style=for-the-badge)](https://github.com/)
</div>

---

## 🏆 **REPRESENTANDO A TEAM NEXUS – RUMBO A WRO 2026**

Bienvenidos al repositorio oficial del **Team Nexus**, compitiendo en la categoría **Future Engineers** de la **World Robot Olympiad™ (WRO)**. En este espacio encontrarás el proceso de diseño, desarrollo y construcción de nuestro vehículo autónomo.

Nuestra filosofía combina la innovación práctica con la resolución de retos complejos. El propósito en esta temporada es diseñar un vehículo verdaderamente autónomo, robusto y altamente eficiente, capaz de superar exitosamente tanto los retos de la **etapa cerrada** como los de la **etapa abierta**, buscando clasificar a la Final Nacional y representar con orgullo a nuestro país.

> 💡 **Estado del Proyecto:** Integración de sistemas electrónicos, calibración de visión artificial y pruebas de control de movimiento en pista.

---

## 📚 **Tabla de Contenidos**
- [📂 Estructura de Documentación](#-estructura-de-documentación)
- [👥 El Equipo](#-el-equipo)
- [🛠️ Stack Tecnológico](#-stack-tecnológico)
- [🔧 Sistema Electrónico](#-sistema-electrónico)
- [🚀 Instalación y Uso](#-instalación-y-uso)

---

## 📂 **Estructura de Documentación**

<div align="center">

| 📁 Carpeta | 🎯 Contenido Técnico | 📖 Link |
|-----------|----------------------|-----------|
| **📂 planes** | **Hardware & Componentes**<br>• Fichas técnicas detalladas<br>• Lista de materiales y esquemáticos | [🔗 Ver Documentación](./planes/README.md) |
| **💻 src** | **Firmware & Algoritmos**<br>• Lógica de navegación<br>• Controladores de sensores y visión | [🔗 Próximamente](#) |
| **⚙️ models** | **Diseño Mecánico**<br>• Modelos CAD 3D y chasis modular | [🔗 Próximamente](#) |

</div>

---

## 👥 **El Equipo** <a id="the-team"></a>

Un equipo interdisciplinario que une trayectorias individuales en la WRO y una sólida experiencia conjunta en competencias internacionales de alto nivel como la **FTC Championship en Italia**.

### **Members**

* **José Montiel**
    * **Background:** Estudiante de Ing. Electrónica (Automatización y Control).
    * **Role:** *Software Architecture & Vision Strategy*.
    * **Focus:** Firmware en C++, control de velocidad y procesamiento de visión artificial.

* **David Ocando**
    * **Background:** Estudiante de Ing. Eléctrica (URU) | 2º año en WRO (Robot Sport 2025).
    * **Role:** *Electrical Architecture & Power Management*.
    * **Focus:** Arquitectura electrónica, distribución de energía y alimentación estable.

* **Jairo Cruz**
    * **Background:** Competidor WRO (Robot Sport 2025).
    * **Role:** *Control Strategy & Algorithmic Optimization*.
    * **Focus:** Desarrollo algorítmico y optimización de trayectorias.

* **Wender Sanchez**
    * **Background:** Ing. Mecánico.
    * **Role:** *Coach*.

---

## 🛠️ **Stack Tecnológico**

* **Cerebro:** ESP32-S3 para la ejecución central de algoritmos de navegación y control.
* **Percepción Visual y Orientación:** Cámara inteligente HuskyLens para reconocimiento de pista y sensor IMU BMI160 para orientación.
* **Control de Dirección:** Servomotor controlado directamente mediante GPIO 7 con la librería `ESP32Servo`.
* **Actuación y Tracción:** Puente H L298N operado con GPIOs directos (GPIO 4 para PWM/ENA, GPIO 5 y 6 para dirección) para propulsión.

---

## 🔧 **Sistema Electrónico (Componentes Principales)**

| Componente | Vista Previa | Función Crítica | Pinout / Asignación GPIO |
|-----------|:-----------:|-------------------|---------------------------|
| **ESP32-S3** | <img src="./Esquemas/ESP32-S3.jpeg" width="100"> | Unidad de procesamiento central. | MCU Principal |
| **HuskyLens** | <img src="./Esquemas/Huskylens.jpg" width="100"> | Reconocimiento visual y seguimiento. | Cámara inteligente |
| **BMI160** | <img src="./Esquemas/bmi160.jpg" width="100"> | Unidad de medición inercial (IMU). | Bus I2C |
| **L298N** | <img src="./Esquemas/L298N.jpg" width="100"> | Controlador de motor principal (Puente H). | **ENA:** GPIO 4 (PWM)<br>**IN1:** GPIO 5<br>**IN2:** GPIO 6 |

---

## 🚀 **Instalación y Uso**

```bash
# Clonar el repositorio oficial
git clone [https://github.com/TU_USUARIO/WRO2026-FE-TEAM-NEXUS.git](https://github.com/TU_USUARIO/WRO2026-FE-TEAM-NEXUS.git)

# Acceder a la documentación de hardware
cd planes
