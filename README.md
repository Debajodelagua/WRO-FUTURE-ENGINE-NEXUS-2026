# 🏎️ WRO 2026 Future Engineers – Team Nexus
<div align="center">
  <img src="./Otro/NEXUS_LOGO.jpg" alt="Team Nexus Autonomous Vehicle" width="650" style="border-radius: 15px; box-shadow: 0 4px 15px rgba(0,0,0,0.3);">
  <br> <br>
  
  [![WRO](https://img.shields.io/badge/WRO-Future_Engineers_2026-0052CC.svg?style=for-the-badge&logo=target)](https://wro-association.org/)
  [![Location](https://img.shields.io/badge/Location-Zulia%2C_Venezuela-FFD700.svg?style=for-the-badge&logo=googlemaps&logoColor=black)](https://www.instagram.com/iniar_zulia/)
  [![Institution](https://img.shields.io/badge/Institution-INIAR-008080.svg?style=for-the-badge)](https://www.instagram.com/iniar_zulia/)
  <br>
  [![MCU](https://img.shields.io/badge/MCU-ESP32--S3-E7352C.svg?style=for-the-badge&logo=espressif&logoColor=white)](https://www.espressif.com/)
  [![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
  [![CAD](https://img.shields.io/badge/CAD-Autodesk_Fusion_360-E51B24.svg?style=for-the-badge&logo=autodesk)](https://www.autodesk.com/)
  [![3D Printer](https://img.shields.io/badge/3D_Printer-Bambu_Lab_PETG-00AE42.svg?style=for-the-badge)](https://bambulab.com/)
  <br>
  [![YouTube](https://img.shields.io/badge/YouTube-@NEXUSTEAM--e3d-FF0000.svg?style=for-the-badge&logo=youtube&logoColor=white)](https://www.youtube.com/@NEXUSTEAM-e3d)
  [![Instagram](https://img.shields.io/badge/Instagram-@iniar__zulia-%23E4405F.svg?style=for-the-badge&logo=Instagram&logoColor=white)](https://www.instagram.com/iniar_zulia/)

<a name="inicio"></a>
</div>

# 📑 Índice 

- [1. Nuestro Equipo & Plataforma "Smoke"](#1-nuestro-equipo--plataforma-smoke) 
  - [1.1 Integrantes y Asesoría Técnica](#11-integrantes-y-asesoría-técnica)
  - [1.2 Origen del Robot y Filosofía ("Smoke")](#12-origen-del-robot-y-filosofía-smoke)
  - [1.3 Estado Actual del Proyecto y Roadmap](#13-estado-actual-del-proyecto-y-roadmap)
- [2. Videos y Desempeño en Pista](#2-videos-y-desempeño-en-pista)
  - [2.1 Ronda Abierta (Open Challenge)](#21-ronda-abierta-open-challenge)
  - [2.2 Ronda de Obstáculos (Obstacle Challenge)](#22-ronda-de-obstáculos-obstacle-challenge)
- [3. Estructura del Repositorio](#3-estructura-del-repositorio)
- [4. Lista Maestra de Materiales y Componentes (BOM)](#4-lista-maestra-de-materiales-y-componentes-bom)
  - [4.1 Electrónica, Potencia y Control](#41-electrónica-potencia-y-control)
  - [4.2 Mecánica, Actuadores y Chasis](#42-mecánica-actuadores-y-chasis)
- [5. Apartado Mecánico y Cinemática](#5-apartado-mecánico-y-cinemática)
  - [5.1 Filosofía de Chasis Modular y Manufactura Aditiva (PETG)](#51-filosofía-de-chasis-modular-y-manufactura-aditiva-petg)
  - [5.2 Geometría de Dirección Ackermann Híbrida (Servo MG90S)](#52-geometría-de-dirección-ackermann-híbrida-servo-mg90s)
  - [5.3 Tren de Potencia Trasero (RWD) y Diferencial de Engranajes Cónicos](#53-tren-de-potencia-trasero-rwd-y-diferencial-de-engranajes-cónicos)
- [6. Apartado Electrónico y Distribución de Potencia](#6-apartado-electrónico-y-distribución-de-potencia)
  - [6.1 Banco de Baterías LiFePO4 (Configuración 2S2P)](#61-banco-de-baterías-lifepo4-configuración-2s2p)
  - [6.2 Topología de Tres Ramas de Regulación y Filtrado](#62-topología-de-tres-ramas-de-regulación-y-filtrado)
  - [6.3 Etapa de Tracción y Compensación de Caída de Tensión (XL6009 + L298N)](#63-etapa-de-tracción-y-compensación-de-caída-de-tensión-xl6009--l298n)
  - [6.4 Diagrama Esquemático General](#64-diagrama-esquemático-general)
- [7. Percepción Sensorial y Visión Artificial](#7-percepción-sensorial-y-visión-artificial)
  - [7.1 Visión Artificial por IA (HuskyLens)](#71-visión-artificial-por-ia-huskylens)
  - [7.2 Red de Sensores Ultrasónicos HC-SR04](#72-red-de-sensores-ultrasónicos-hc-sr04)
- [8. Arquitectura de Firmware y Software](#8-arquitectura-de-firmware-y-software)
  - [8.1 Máquina de Estados Finitos (FSM)](#81-máquina-de-estados-finitos-fsm)
  - [8.2 Estrategia de Ronda Abierta vs. Ronda de Obstáculos](#82-estrategia-de-ronda-abierta-vs-ronda-de-obstáculos)
- [9. Diario de Ingeniería, Iteraciones y Solución de Fallas](#9-diario-de-ingeniería-iteraciones-y-solución-de-fallas)


## 1. Nuestro Equipo & Plataforma "Smoke"
Bienvenidos al repositorio técnico oficial de **Team Nexus**, representantes del **Instituto de Inteligencia Artificial y Robótica del estado Zulia "Dr. Héctor Rafael Rojas" (INIAR)** para la categoría **Future Engineers** de la **World Robot Olympiad™ (WRO) 2026**.
Este espacio documenta de manera transparente, rigurosa y reproducible el ciclo completo de diseño, manufactura aditiva en PETG, arquitectura de potencia desacoplada y algoritmos de control de nuestra plataforma autónoma **"Smoke"**, desarrollada para superar tanto la **Ronda Abierta (Open Challenge)** como la **Ronda de Obstáculos (Obstacle Challenge)**.
### 1.1 Integrantes y Asesoría Técnica
<div align="center">
  <img src="./t-fotos/FOTO%20GRUPAL%20DE%20TEAM%20NEXUS.jpg" alt="Foto Grupal Team Nexus" width="700" style="border-radius: 12px; box-shadow: 0 4px 10px rgba(0,0,0,0.2);">
</div>
<br>
<table>
  <tr>
    <td width="30%" align="center" style="vertical-align: top;">
      <img src="./t-fotos/DAVID%20PERFIL.jpeg" width="100%" style="border-radius: 10px;">
      <br><b>David Ocando</b>
    </td>
    <td width="70%" style="vertical-align: top;">
      <h4>⚡ Arquitectura Eléctrica, Gestión de Potencia & Documentación</h4>
      <p><b>🎓 Formación:</b> Estudiante de Ingeniería Eléctrica (URU).</p>
      <p><b>🛠️ Responsabilidades:</b></p>
      <ul>
        <li>Diseño de la topología de distribución eléctrica de 3 ramas (Buck / Boost).</li>
        <li>Selección del banco de baterías LiFePO4, cálculo de caídas de tensión y aislamiento de ruido electromecánico.</li>
        <li>Estructuración de ingeniería, esquemáticos y mantenimiento del repositorio en GitHub.</li>
      </ul>
      <p><b>🏆 Trayectoria:</b> Copa KAI (2023), FTC Championship (Italia, 2024), WRO Venezuela RoboSports (2025).</p>
    </td>
  </tr>
  <tr>
    <td width="30%" align="center" style="vertical-align: top;">
      <img src="./t-fotos/JOSE%20PERFIL.jpeg" width="100%" style="border-radius: 10px;">
      <br><b>José Montiel</b>
    </td>
    <td width="70%" style="vertical-align: top;">
      <h4>💻 Firmware, Visión Artificial & Control Autónomo</h4>
      <p><b>🎓 Formación:</b> Estudiante de Ingeniería Electrónica (URBE).</p>
      <p><b>🛠️ Responsabilidades:</b></p>
      <ul>
        <li>Desarrollo de firmware en C++ sobre ESP32-S3 mediante temporización no bloqueante.</li>
        <li>Entrenamiento y calibración de visión artificial por hardware con HuskyLens (detección colorimétrica en Obstacle Challenge).</li>
        <li>Fusión sensorial ultrasónica y lógica de la máquina de estados finitos (FSM).</li>
      </ul>
      <p><b>🏆 Trayectoria:</b> WRO Venezuela Regional Future Engineers (2025).</p>
    </td>
  </tr>
  <tr>
    <td width="30%" align="center" style="vertical-align: top;">
      <img src="./t-fotos/JAIRO%20PERFIL.jpeg" width="100%" style="border-radius: 10px;">
      <br><b>Jairo Cruz</b>
    </td>
    <td width="70%" style="vertical-align: top;">
      <h4>⚙️ Diseño CAD Mecánico, Dinámica & Manufactura Aditiva</h4>
      <p><b>🎓 Formación:</b> Estudiante de Ingeniería Electrónica.</p>
      <p><b>🛠️ Responsabilidades:</b></p>
      <ul>
        <li>Modelado paramétrico en Autodesk Fusion 360 del chasis modular de tres niveles.</li>
        <li>Optimización de impresión 3D en Bambu Lab con PETG estructural (orientación de esfuerzo y relleno).</li>
        <li>Diseño cinemático de dirección Ackermann híbrida y diferencial trasero con piñonería cónica.</li>
      </ul>
      <p><b>🏆 Trayectoria:</b> Copa KAI (2023), FTC Championship (Italia, 2024), WRO Venezuela RoboSports (2025).</p>
    </td>
  </tr>
  <tr>
    <td width="30%" align="center" style="vertical-align: top;">
      <img src="./t-fotos/MENTOR%20PERFIL.jpeg" width="100%" style="border-radius: 10px;">
      <br><b>Ing. Wender Sánchez</b>
    </td>
    <td width="70%" style="vertical-align: top;">
      <h4>📐 Mentor Líder & Asesor de Ingeniería Mecánica</h4>
      <p><b>🎓 Formación:</b> Ingeniero Mecánico – Universidad del Zulia (LUZ).</p>
      <p><b>🛠️ Rol:</b> Supervisión metodológica en cinemática automotriz, cálculo de relaciones de transmisión, tolerancias mecánicas y validación de seguridad de sistemas en competencia.</p>
    </td>
  </tr>
</table>

### 1.2 Origen del Robot y Filosofía ("Smoke")
> [!NOTE]
> **El Bautizo de "Smoke":**
> En las etapas iniciales de pruebas dinámicas en el banco de trabajo, el prototipo experimentó severos picos de sobretensión y corrientes parásitas generadas por el frenado inductivo del motor y ruidos en la conmutación. Esto provocó que tres módulos reguladores (*Step-Down*) consecutivos se quemaran, despidiendo una densa nube de humo en el laboratorio.
> 
> Lejos de ser un fallo desalentador, este suceso definió el nombre de batalla de nuestro vehículo: **"Smoke"**. Nos impulsó a rediseñar de forma radical la distribución eléctrica, separando la lógica de control de las cargas de alta potencia y migrando hacia una arquitectura robusta de tres etapas de regulación independiente.
---

### 1.3 Estado Actual del Proyecto y Roadmap
| Módulo / Fase | Estado | Descripción Técnica y Avance Real |
| :--- | :---: | :--- |
| **Diseño y Fabricación Chasis** | `🟢 COMPLETADO` | Estructura modular 100% impresa en PETG en Bambu Lab. Geometría Ackermann y diferencial RWD acoplados. |
| **Desafío Abierto (Open Challenge)** | `🟢 COMPLETADO` | Navegación autónoma fluida de 3 vueltas completada y validada en pista reglamentaria usando la red ultrasónica. |
| **Desafío de Obstáculos (Obstacle Challenge)** | `🟡 EN DESARROLLO` | Algoritmo de detección colorimétrica con HuskyLens funcional en pruebas de banco y clips de esquiva; optimizando el firmware para el recorrido continuo de competencia. |
---

## 2. Videos y Desempeño en Pista
### 2.1 Ronda Abierta (Open Challenge)
Demostración técnica del vehículo **"Smoke"** completando el recorrido reglamentario de 3 vueltas completas de manera 100% autónoma. En esta ronda, la navegación se basa exclusivamente en el algoritmo de seguimiento y estabilización ultrasónica (la cámara HuskyLens permanece montada y alimentada pero su lógica de control está desactivada en el firmware de la abierta).
<div align="center">
  <a href="https://youtu.be/ooOyRUvQE2Y" target="_blank">
    <img src="https://img.youtube.com/vi/ooOyRUvQE2Y/maxresdefault.jpg" alt="Video Open Challenge Team Nexus" width="550" style="border-radius: 10px; box-shadow: 0 4px 12px rgba(0,0,0,0.3); border: 1px solid #444;">
    <br>
    <b>▶️ Ver en YouTube: Ronda Abierta Oficial - Team Nexus (WRO 2026)</b>
  </a>
</div>
<br>

### 2.2 Ronda de Obstáculos (Obstacle Challenge)
Demostración de la detección e interpretación en tiempo real de los bloques de tráfico (rojos) mediante el procesador de visión integrado de la **HuskyLens**, activando las maniobras de esquiva lateral.
> 📹 *El clip técnico de prueba de esquiva de bloques se encuentra disponible en la carpeta local [`./video/`](./video/) y actualmente se está integrando al flujo de competencia continuo.*
<p align="right"><a href="#inicio">⬆️ Volver al Inicio</a></p>
---

## 3. Estructura del Repositorio
Para agilizar la revisión técnica de los jueces y garantizar la reproducibilidad internacional del proyecto, el repositorio se organiza en los siguientes directorios dedicados:

| Directorio / Carpeta | Contenido Técnico | Acceso Directo |
| :--- | :--- | :---: |
| **📁 `models/`** | Archivos de diseño y fabricación CAD (`.stl`, `.step`) para impresión 3D en Bambu Lab. | [🔗 Explorar Archivos CAD](./models/) |
| **📁 `schemes/`** | Diagramas de conexiones eléctricas, buses de potencia y esquemáticos generales. | [🔗 Ver Esquemáticos](./schemes/) |
| **📁 `src/`** | Firmware y código fuente en C++ para ESP32-S3 (Open y Obstacle Challenge). | [🔗 Revisar Código Fuente](./src/) |
| **📁 `v-photos/`** | Registro fotográfico de inspección técnica ortogonal 360° del vehículo "Smoke". | [🔗 Ver Galería del Vehículo](./v-photos/) |
| **📁 `t-photos/`** | Fotografías oficiales de los miembros del equipo y trabajo en laboratorio INIAR. | [🔗 Ver Galería del Equipo](./t-photos/) |
| **📁 `video/`** | Clips de pruebas dinámicas en pista reglamentaria y maniobras de esquiva. | [🔗 Ver Grabaciones](./video/) |
| **📁 `Otro/`** | Logotipos oficiales, recursos gráficos complementarios y documentación de apoyo. | [🔗 Abrir Recursos](./Otro/) |
---

## 4. Lista Maestra de Materiales y Componentes (BOM)
A continuación se detalla la lista completa de componentes integrados en **"Smoke"**, documentando su función técnica, vista previa, hoja de datos y enlace de adquisición:
### 4.1 Electrónica, Potencia y Control
| Componente | Vista Previa | Especificaciones Clave | Función en "Smoke" | Datasheet | Compra |
| :--- | :---: | :--- | :--- | :---: | :---: |
| **ESP32-S3 DevKit** | <img src="https://m.media-amazon.com/images/I/61N9xZ3mYdL._AC_SL1500_.jpg" width="80" style="border-radius: 6px;"> | • Dual-Core Xtensa LX7 @ 240MHz<br>• Wi-Fi & Bluetooth 5 (LE)<br>• 44 Pines GPIO programables | Cerebro central; administra la máquina de estados finitos, lectura de sensores y control PWM. | [📄 PDF](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf) | [🛒 Link](https://es.aliexpress.com/item/1005005086873539.html) |
| **HuskyLens 2** | <img src="https://image.dfrobot.com/image/cache/catalog/SEN0305/SEN0305-6-800x800.jpg" width="80" style="border-radius: 6px;"> | • Procesador AI KPU integrado<br>• Pantalla IPS a color<br>• Algoritmo de visión colorimétrica | Procesamiento de visión artificial por hardware para detección y clasificación de bloques en el Obstacle Challenge. | [📄 Wiki](https://wiki.dfrobot.com/HUSKYLENS_V1.0_SKU_SEN0305_SEN0336) | [🛒 Link](https://www.dfrobot.com/product-1922.html) |
| **Driver L298N** | <img src="https://m.media-amazon.com/images/I/71csm1kQx7L._AC_SL1500_.jpg" width="80" style="border-radius: 6px;"> | • Doble puente H (Darlington BJT)<br>• 2A pico por canal<br>• Disipador térmico de aluminio | Control de avance, retroceso y velocidad del motor de tracción (jumper de 5V retirado). | [📄 PDF](https://www.sparkfun.com/datasheets/Robotics/L298_H_Bridge.pdf) | [🛒 Link](https://es.aliexpress.com/item/1005003118671408.html) |
| **Step-Down XL4015E1** | <img src="https://m.media-amazon.com/images/I/61jC7K0h4CL._AC_SL1001_.jpg" width="80" style="border-radius: 6px;"> | • Regulador Buck 5A máx.<br>• Salida ajustada a **5.0V DC**<br>• Alta eficiencia (>90%) | Línea limpia de alimentación para ESP32-S3, sensores HC-SR04 y lógica del driver L298N. | [📄 PDF](https://www.xlsemi.com/datasheet/XL4015%20datasheet.pdf) | [🛒 Link](https://es.aliexpress.com/item/32832049185.html) |
| **Step-Down LM2596** | <img src="https://m.media-amazon.com/images/I/61FfI8iB-kL._AC_SL1200_.jpg" width="80" style="border-radius: 6px;"> | • Regulador Buck 3A máx.<br>• Salida ajustada a **5.0V DC**<br>• Filtro de rizado | Rama aislada exclusiva para absorber los picos dinámicos de corriente del servo MG90S y la HuskyLens 2. | [📄 PDF](https://www.ti.com/lit/ds/symlink/lm2596.pdf) | [🛒 Link](https://es.aliexpress.com/item/1005001636544837.html) |
| **Step-Up XL6009** | <img src="https://m.media-amazon.com/images/I/61r5T0vGgQL._AC_SL1001_.jpg" width="80" style="border-radius: 6px;"> | • Regulador Boost 4A máx.<br>• Salida ajustada a **14.0V DC**<br>• Frecuencia de 400KHz | Eleva los 7V del banco a 14V para compensar la caída de 2V en el L298N y entregar 12V netos al motor de tracción. | [📄 PDF](https://www.xlsemi.com/datasheet/XL6009%20datasheet.pdf) | [🛒 Link](https://es.aliexpress.com/item/1005002880590858.html) |
| **HC-SR04 Ultrasónico** | <img src="https://m.media-amazon.com/images/I/61Y0+38oIuL._AC_SL1500_.jpg" width="80" style="border-radius: 6px;"> | • Rango: 2 cm a 400 cm<br>• Ángulo de apertura: 15°<br>• Resolución: 0.3 cm | Sensado perimetral de distancia a muros laterales para estabilización de trayectoria y centrado. | [📄 PDF](https://www.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf) | [🛒 Link](https://es.aliexpress.com/item/32713520550.html) |
| **Celdas LiFePO4 IFR32140** | <img src="./schemes/baterias_lifepo4.png" width="80" style="border-radius: 6px;"> | • Química LiFePO4 de alta seguridad<br>• Configuración **2S2P** (~7.0V bus)<br>• Capacidad: `[__]` Ah | Fuente primaria de energía del vehículo; máxima estabilidad térmica, alta tasa de descarga y descarga plana. | [📄 Info](https://en.wikipedia.org/wiki/Lithium_iron_phosphate_battery) | [🛒 Link](https://es.aliexpress.com/) |
### 4.2 Mecánica, Actuadores y Chasis
| Componente | Vista Previa | Especificaciones Clave | Función en "Smoke" | Enlace Técnico / Modelo |
| :--- | :---: | :--- | :--- | :---: |
| **Servo TowerPro MG90S** | <img src="https://m.media-amazon.com/images/I/61I2H7P8JvL._AC_SL1000_.jpg" width="80" style="border-radius: 6px;"> | • Piñonería metálica reforzada<br>• Torque: 2.2 kg·cm @ 6V<br>• Velocidad: 0.10s / 60° | Acciona la timonería del sistema de dirección Ackermann con alta resistencia a esfuerzos mecánicos. | [📄 PDF](https://www.electronicoscaldas.com/datasheet/MG90S_Tower-Pro.pdf) |
| **Motor Makeblock DC** | <img src="https://m.media-amazon.com/images/I/61k8wD57VbL._AC_SL1000_.jpg" width="80" style="border-radius: 6px;"> | • Tensión nominal: 9V - 12V<br>• Velocidad eje: 185 RPM<br>• Caja reductora cilíndrica metálica | Motor de tracción longitudinal; acoplado al diferencial trasero para propulsión RWD. | [🌐 Web](https://www.makeblock.com/) |
| **Diferencial Lego Technic** | <img src="https://m.media-amazon.com/images/I/41K-j71vWTL.jpg" width="80" style="border-radius: 6px;"> | • Caja diferencial de 3 satélites cónicos<br>• Plástico técnico de bajo rozamiento | Distribuye la velocidad angular entre las ruedas traseras izquierda y derecha para un giro limpio sin derrape. | [🔗 Lego Spec](https://www.bricklink.com/) |
| **Engranajes Cónicos de Ángulo Recto** | <img src="./models/pinon_conico_preview.png" width="80" style="border-radius: 6px;"> | • Reducción cónica 90°<br>• Fabricación aditiva en Bambu Lab | Transfiere el giro longitudinal del motor Makeblock hacia el eje transversal del diferencial trasero. | [⚙️ Ver Modelo](./models/) |
| **Chasis Modular de 3 Pisos** | <img src="./models/chasis_render.png" width="80" style="border-radius: 6px;"> | • 100% manufactura en **PETG**<br>• Arquitectura vertical desacoplada | Aloja y protege los subsistemas de tracción (Piso 1), control (Piso 2) y potencia/visión (Piso 3). | [⚙️ Ver CAD](./models/) |
<p align="right"><a href="#inicio">⬆️ Volver al Inicio</a></p>
