# 🏎️ WRO 2026 Future Engineers – Team Nexus

<div align="center">
  <img src="./Otro/NEXUS_LOGO.jpg" alt="Team Nexus Autonomous Vehicle" width="600" style="border-radius: 15px;">

 <br><br>
   [![WRO](https://img.shields.io/badge/WRO-Future_Engineers_2026-0052CC.svg?style=for-the-badge&logo=target)](https://wro-association.org/)
  [![Country](https://img.shields.io/badge/Location-Zulia%2C_Venezuela-FFD700.svg?style=for-the-badge&logo=googlemaps&logoColor=black)](https://www.instagram.com/iniar_zulia/)
  [![Institution](https://img.shields.io/badge/Institution-INIAR-008080.svg?style=for-the-badge)](https://www.instagram.com/iniar_zulia/)
  <br>
  [![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
  [![Arduino IDE](https://img.shields.io/badge/IDE-Arduino_IDE-00979D.svg?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
  [![Instagram](https://img.shields.io/badge/Instagram-@iniar__zulia-%23E4405F.svg?style=for-the-badge&logo=Instagram&logoColor=white)](https://www.instagram.com/iniar_zulia/)
  <br><br>
  
</div>

## 🏆 **REPRESENTANDO A TEAM NEXUS – RUMBO A WRO 2026**
</div>
Bienvenidos al repositorio oficial de ingeniería de **Team Nexus**, equipo representante del **Instituto de Inteligencia Artificial y Robótica del estado Zulia "Dr. Héctor Rafael Rojas" (INIAR)** en la categoría **Future Engineers** de la **World Robot Olympiad™ (WRO) 2026**.
Este espacio documenta de manera transparente, rigurosa y reproducible el ciclo completo de diseño, manufactura aditiva, arquitectura eléctrica y algoritmos de control de nuestra plataforma autónoma **"Smoke"**, diseñada para solventar los desafíos de la **Ronda Abierta (Open Challenge)** y la **Ronda de Obstáculos (Obstacle Challenge)**.
---

> 💡 **Estado del Proyecto:** Integración de sistemas electrónicos, calibración de visión artificial y pruebas de control de movimiento en pista.

---

## 🤖 **Plataforma Oficial: "Smoke"**
* **Categoría:** WRO Future Engineers 2026.
* **Arquitectura General:** Estructura modular vertical de tres niveles (Three-Tier Chassis) con centro de gravedad bajo y aislamiento galvánico de potencia.
* **Percepción Sensorial:** Visión por computador basada en IA (**HuskyLens**) + Red perimetral de ultrasonido + IMU central.
* **Cinemática:** Dirección delantera **Ackermann** mediante servomotor con piñonería metálica + Tracción trasera **RWD**.
> [!NOTE]
> **Origen del Nombre "Smoke":** 
> Durante las primeras fases de pruebas en banco de potencia, un error fortuito en la conexión cruzada de las líneas de salida de un convertidor elevador (*Step-Up*) causó una sobretensión inversa en los capacitores electrolíticos, provocando una densa columna de humo en el taller. Bautizar al vehículo como **"Smoke"** rinde tributo a la resiliencia en el laboratorio, recordándonos que cada falla es un aprendizaje indispensable en el camino hacia la fiabilidad técnica.

# 👥 **Miembros de Team Nexus (INIAR)**
---
## <a id="equipo"></a>👥 **El Equipo**

<p align="center">
  <img src="./t-fotos/FOTO%20GRUPAL%20DE%20TEAM%20NEXUS.jpg" alt="Nuestro Equipo" width="600"/>
</p>

### 👤 **David Ocando**
**Rol:** *Líder de Arquitectura Eléctrica, Gestión de Potencia y Co-administrador Digital.*
* **Formación Académica:** Estudiante de Ingeniería Eléctrica (Mención en Generación y Distribución de Potencia) – Universidad Rafael Urdaneta (URU).
* **Responsabilidades Técnicas:**
  * Diseño del sistema de distribución y aislamiento de potencia (líneas de 5V y tracción).
  * Selección y conexionado de fuentes de alimentación, convertidores Buck/Boost y cableado de señales.
  * Análisis de balance de carga (*Power Budget*) y telemetría eléctrica.
  * Gestión, estructura y estandarización del repositorio técnico en GitHub.
<div align="center">
  <!-- Reemplaza este enlace con la foto oficial cuando la tomes -->
  <i>[📸 Foto Oficial - David Ocando]</i>
</div>

#### **Historial y Trayectoria Competitiva:**
* 🏆 **Copa KAI (2023):** Participación y desempeño destacado en robótica de competencia.
* 🇮🇹 **FTC Championship (Italia, 2024):** Representación internacional en robótica avanzada con sistemas de potencia y control de alto rendimiento.
* 🤖 **WRO Venezuela (2025):** Participación oficial en la categoría **RoboSports**, optimizando la respuesta dinámica en pista.
---


### 👤 **José Montiel**
**Rol:** *Ingeniero Líder de Software, Visión Artificial y Control Autónomo.*
* **Formación Académica:** Estudiante de Ingeniería Electrónica – Universidad Dr. Rafael Belloso Chacín (URBE).
* **Responsabilidades Técnicas:**
  * Desarrollo del firmware en C++ y estructuración en Arduino IDE.
  * Implementación de la máquina de estados finitos (FSM) para la navegación autónoma.
  * Calibración de la cámara inteligente **HuskyLens** para reconocimiento colorimétrico de bloques.
  * Fusión de datos sensoriales (Giroscopio/IMU y sensores ultrasónicos).
<div align="center">
  <!-- Reemplaza este enlace con la foto oficial cuando la tomes -->
  <i>[📸 Foto Oficial - José Montiel]</i>
</div>

#### **Historial y Trayectoria Competitiva:**
* 🤖 **WRO Venezuela (2025):** Participación en la categoría **Futuros Ingenieros (Future Engineers)** en la eliminatoria regional, acumulando experiencia en las dinámicas de pista y visión de carriles.
---

### 👤 **Jairo Cruz**
**Rol:** *Ingeniero de Diseño Mecánico, Manufactura Aditiva y Soporte Digital.*
* **Formación Académica:** Estudiante de Ingeniería Electrónica (Mención en Automatización y Control).
* **Responsabilidades Técnicas:**
  * Modelado paramétrico 3D del chasis modular y soportes en **Autodesk Fusion 360**.
  * Optimización de manufactura e impresión 3D en **Bambu Lab** (orientación de capas, densidades de relleno e interpolación dimensional).
  * Ensamble del sistema de dirección Ackermann híbrido y reducción de holguras (*backlash*).
  * Co-desarrollo y mantenimiento de la documentación en GitHub.
<div align="center">
  <!-- Reemplaza este enlace con la foto oficial cuando la tomes -->
  <i>[📸 Foto Oficial - Jairo Cruz]</i>
</div>

#### **Historial y Trayectoria Competitiva:**
* 🏆 **Copa KAI (2023):** Competidor en desafíos de robótica móvil.
* 🇮🇹 **FTC Championship (Italia, 2024):** Integrante de la delegación internacional en FIRST Tech Challenge, trabajando en mecanismos de tracción e integración de sistemas.
* 🤖 **WRO Venezuela (2025):** Competidor en la categoría **RoboSports**, especializándose en resistencia estructural y dinámica de choque.
---

### 👤 **Ing. Wender Sánchez**
**Rol:** *Tutor Principal y Asesor de Ingeniería Mecánica.*
* **Formación y Perfil:** Ingeniero Mecánico egresado de la **Universidad del Zulia (LUZ)**, con amplia trayectoria profesional en cinemática de mecanismos, dinámica de vehículos y sistemas de tracción.
* **Acompañamiento:** Mentoría estratégica en diseño mecánico, validación de cálculos de transmisión, distribución de momentos torsionales y metodología del ciclo de ingeniería.
<div align="center">
  <!-- Reemplaza este enlace con la foto oficial cuando la tomes -->
  <i>[📸 Foto Oficial - Ing. Wender Sánchez]</i>
</div>

# 📚 **Índice General de Documentación**
1. [🏆 Identidad del Equipo y Plataforma "Smoke"](#-representando-a-team-nexus--rumbo-a-wro-2026)
2. [👥 Miembros de Team Nexus](#-miembros-de-team-nexus-iniar)
3. [📂 Mapa del Repositorio](#-mapa-del-repositorio-repository-directory-map)
4. [📸 Matriz de Inspección Técnica 360°](#-matriz-de-inspección-técnica-360-smoke)
5. [🚗 Movilidad, Cinemática Ackermann y Diseño Mecánico](#-movilidad-cinemática-ackermann-y-diseño-mecánico)
6. [⚡ Arquitectura Eléctrica, Power Budget y Sensado](#-arquitectura-eléctrica-power-budget-y-sensado)
7. [💻 Arquitectura de Software, Visión y Algoritmos de Navegación](#-arquitectura-de-software-visión-y-algoritmos-de-navegación)
8. [📓 Diario de Ingeniería, Iteraciones y Solución de Fallas](#-diario-de-ingeniería-iteraciones-y-solución-de-fallas)
9. [🚀 Guía de Instalación, Compilación y Reproducibilidad](#-guía-de-instalación-compilación-y-reproducibilidad)
---


## 📂 **Mapa del Repositorio (Repository Directory Map)**
Para agilizar la revisión técnica de los jueces y garantizar la total reproducibilidad del proyecto, se estructuraron los siguientes directorios dedicados:
<div align="center">
  
| Directorio | Contenido Técnico | Enlace |
| :--- | :--- | :---: |
| **`⚙️ models/`** | **Diseño Mecánico y CAD:** Archivos de fabricación (`.stl`, `.step`), tolerancias y parámetros de laminado en Bambu Studio. | [🔗 Ver Modelos](./models/) |
| **`⚡ schemes/`** | **Ingeniería Eléctrica:** Diagramas de conexión, distribución de potencia, esquemáticos y mapeo de pines del ESP32. | [🔗 Ver Planos](./schemes/) |
| **`💻 src/`** | **Firmware y Algoritmos:** Código fuente en C++ para Arduino IDE, lógica de la máquina de estados y controladores. | [🔗 Ver Código](./src/) |
| **`📸 v-photos/`** | **Galería del Vehículo:** Fotografías técnicas oficiales en alta resolución de la plataforma "Smoke". | [🔗 Ver Fotos](./v-photos/) |
| **`👥 t-photos/`** | **Galería del Equipo:** Registro del equipo Nexus y sesiones de trabajo en el laboratorio de INIAR. | [🔗 Ver Equipo](./t-photos/) |
| **`🎥 video/`** | **Registro en Pista:** Enlace oficial al video de demostración de navegación autónoma continua. | [🔗 Ver Video](./video/) |
| **`📁 Otro/`** | **Recursos Gráficos:** Identidad visual, diagramas de principios físicos y material complementario. | [🔗 Ver Recursos](./Otro/) |
</div>


## 📸 **Matriz de Inspección Técnica 360° ("Smoke")**
Para comprobar la simetría, la distribución espacial del chasis modular de tres pisos y el despeje libre sobre la pista, se documenta la plataforma en sus **6 perfiles de inspección ortogonal**:
| Perfil de Inspección | Registro Visual | Justificación e Inspección Técnica |
| :--- | :---: | :--- |
| **Vista Superior<br>(Top View)** | <img src="./v-photos/top.jpg" width="320" alt="Vista Superior Smoke" style="border-radius: 6px;"> | **Inspección de Simetría y Centro:**<br>• Permite verificar la posición concéntrica de la **IMU en el centro geométrico**.<br>• Muestra la distribución equilibrada de masas en el piso intermedio. |
| **Vista Frontal<br>(Front View)** | <img src="./v-photos/front.jpg" width="320" alt="Vista Frontal Smoke" style="border-radius: 6px;"> | **Inspección del Sistema de Visión:**<br>• Campo de visión libre e inclinación angular de la **HuskyLens**.<br>• Orientación axial del sensor ultrasónico central delantero. |
| **Vista Lateral Derecha<br>(Right Profile)** | <img src="./v-photos/right.jpg" width="320" alt="Vista Lateral Derecha" style="border-radius: 6px;"> | **Inspección de Despeje y Altura:**<br>• Verificación del *Ground Clearance* (despeje al suelo) para evitar roces.<br>• Separación vertical entre el piso de potencia (Nivel 3) y lógica (Nivel 2). |
| **Vista Lateral Izquierda<br>(Left Profile)** | <img src="./v-photos/left.jpg" width="320" alt="Vista Lateral Izquierda" style="border-radius: 6px;"> | **Inspección de Ruteo Eléctrico:**<br>• Separación física del cableado de potencia y señales lógicas.<br>• Ubicación del sensor ultrasónico lateral para control de carril. |
| **Vista Trasera<br>(Rear View)** | <img src="./v-photos/rear.jpg" width="320" alt="Vista Trasera Smoke" style="border-radius: 6px;"> | **Inspección del Tren de Tracción:**<br>• Montaje rígido del motor DC principal y alineación del eje de transmisión trasera. |
| **Vista Inferior<br>(Underbody View)** | <img src="./v-photos/bottom.jpg" width="320" alt="Vista Inferior Chasis" style="border-radius: 6px;"> | **Inspección Estructural del Chasis:**<br>• Comprobación de las nervaduras de refuerzo impresas en PETG/PLA+.<br>• Área de barrido libre para el recorrido angular del brazo del servo. |



## <a id="stack"></a>🛠️ **Stack Tecnológico**

* **Cerebro:** ESP32-S3 para la ejecución central de algoritmos de navegación y control.
* **Percepción Visual, Distancia e Inercia:** Cámara inteligente HuskyLens para reconocimiento de pista, sensor ultrasónico HC-SR04 para detección de proximidad y sensor IMU BMI160 para orientación.
* **Control de Dirección:** Servomotor controlado directamente mediante GPIO 7 con la librería `ESP32Servo`.
* **Actuación y Tracción:** Puente H L298N operado con GPIOs directos (GPIO 4 para PWM/ENA, GPIO 5 y 6 para dirección) para propulsión.

---


# 🚗 **Movilidad, Cinemática Ackermann y Diseño Mecánico**
</div>
La plataforma autónoma **"Smoke"** fue desarrollada bajo los principios de la dinámica vehicular aplicada a robótica móvil de alta velocidad. El sistema integra una estructura modular en tres niveles, cinemática de dirección **Ackermann híbrida** de tolerancia cero y un tren de tracción trasera optimizado para responder con agilidad a las curvas cerradas y cambios de carril de la pista oficial WRO.
---

## 📐 1. Cinemática de la Dirección: Geometría Ackermann
En un vehículo de cuatro ruedas, trazar una curva sin derrape exige que todas las ruedas describan arcos concéntricos alrededor de un único **Centro Instantáneo de Rotación (CIR)**. Si las dos ruedas delanteras giraran con el mismo ángulo ($\delta$), la rueda interna sufriría arrastre lateral (*tire scrubbing*), aumentando la fricción, perdiendo precisión en la trayectoria y consumiendo corriente innecesaria.
<div align="center">
  
  <img src="./Otro/ackermann_teoria.png" alt="Geometría Cinemática Ackermann" width="550" style="border-radius: 8px;">
</div>
# Acceder a la documentación de hardware
cd planes
