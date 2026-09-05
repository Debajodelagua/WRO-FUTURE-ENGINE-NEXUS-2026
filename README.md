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
Para facilitar la auditoría técnica de los jueces y la reproducibilidad internacional, el repositorio se organiza de forma estricta según las directrices de la WRO:
```plaintext
├── models/         # Archivos CAD de manufactura (.stl, .step) de piezas impresas en Bambu Lab
├── schemes/        # Diagramas de conexión eléctrica, distribución de buses y esquemáticos
├── src/            # Código fuente en C++ para ESP32-S3 (Ronda Abierta y Ronda Cerrada)
├── v-photos/       # Galería de inspección técnica 360° del vehículo autónomo
├── t-photos/       # Fotografías oficiales de los integrantes y sesiones de trabajo en INIAR
├── video/          # Registro audiovisual de pruebas dinámicas y esquiva de obstáculos
└── Otro/           # Logotipos oficiales, hojas de datos complementarias y recursos visuales
