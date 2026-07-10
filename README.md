# NEXUS TEAM - WRO FUTUROS INGENIEROS 2026 #

<p>¡Bienvenido a nuestro repositorio de la WRO! En este espacio encontraras el proceso de diseño, desarrollo y construcción de nuestro robot, (Robot), construido por el Team Nexus.<p>
<p>Foto del muneco<p>

<p> Indice <p>
1. Introduccion al Repositorio <p>
- a. Introducción y Propósito <p>
- b. Miembros del Equipo y Roles <p>
2. Diseño mecanica y estructura <p>
- a. Diseño y Chasis <p>
- b. Fotos de (Nombre del robot )<p>
3. Componentes electronicos <p>
- a. Lista de Materiales <p>
- b. Diagramas de conexiones <p>
4. Logica de cotrol <p>
- a. Aquitectura del Codigo <p>
- b- Explicacion de Algoritmos <p>
5.Pruebas y Estrategias <p>
- a. Videos Anclados <p>
- b. Estrategias <p>
        
# 1. Introduccion al Repositorio #
## a. Introduccion y Proposito ##
Como **Team Nexus**, nuestro propósito en esta temporada es diseñar un vehículo verdaderamente autónomo, robusto y altamente eficiente, capaz de superar con éxito tanto los retos de la **etapa cerrada** (navegación precisa, evasión de obstáculos fijos y gestión de tráfico simulado) como los de la **etapa abierta** (adaptación dinámica a cambios en el entorno y optimización de tiempos en pista). Buscamos consolidar nuestra experiencia técnica previa para clasificar a la Final Nacional y representar con orgullo a nuestro país.
## b. Miembros del equipo y Roles ##
El **Team Nexus** está conformado por tres apasionados de la robótica y la ingeniería, uniendo trayectorias individuales en la WRO y una sólida experiencia conjunta en competencias internacionales de alto nivel como la **FTC (First Tech Challenge) Championship en Italia**, donde alcanzamos la semifinal con nuestro antiguo equipo *Pakupai*.<p>

## David Ocando ##
Holaa, soy David Estudiante de Ingeniería Eléctrica en la Universidad Rafael Urdaneta (URU), desde muy pequeño con mucho interés en los sistemas de generación, fuentes de energía y redes de distribución eléctrica. Razón a la cual me llevo a estudiar esta carrera. Este es mi segundo año de competencia, participando con Jairo el año 2025 en la categoria de Robot Esport
Soy el encargado de toda la arquitectura electrónica de nuestro robot. Mi objetivo en **Nexus** es que todo funcione a la perfección en la pista.

## Domingo Nuñez ##

## Jairo Cruz ##

## Wender Sanchez ##
Hoy, bajo la identidad de **Nexus**, fusionamos nuestros aprendizajes en mecánica, electrónica y control de sistemas autónomos para afrontar juntos el desafío de *Futuros Ingenieros*.

# 2. Diseño mecanica y estructura #
## a. Diseño y Chasis ##
La concepción estructural de nuestro robot se rige bajo el principio de **optimización de espacio y modularidad**. Diseñado íntegramente mediante impresión 3D, el chasis se distribuye en una configuración vertical de **tres niveles (pisos)**. Esta arquitectura nos permitió crear un vehículo sumamente compacto, asegurando que cumpla estrictamente con las dimensiones límite de la competencia WRO sin comprometer la accesibilidad ni la distribución de los componentes.

Elegimos un sistema de propulsión y dirección mecánica híbrido, combinando la flexibilidad del chasis impreso en 3D con la seguridad geométrica de componentes LEGO Technic para los sistemas de transmisión. Optamos por esta solución al ser la más robusta, eficiente y adecuada para los objetivos de navegación autónoma planteados desde el inicio del proyecto.

###  Sistema de Tracción y Dirección ###

El movimiento del vehículo emula el comportamiento de un sistema automotriz real, dividiendo las tareas de tracción y dirección de la siguiente manera:

*   **Tren Trasero (Tracción y Diferencial):** La propulsión es generada por el motor principal, el cual transmite la potencia a las ruedas traseras a través de un **sistema de diferencial mecánico** (mecanismo y ejes de acople LEGO). El uso del diferencial es crítico, ya que permite que las ruedas traseras giren a diferentes velocidades al tomar las curvas, evitando el derrape, reduciendo el consumo de corriente y mejorando drásticamente la estabilidad.
*   **Tren Delantero (Dirección Ackermann):** El guiado del robot se realiza mediante un servomotor que controla un mecanismo de **dirección tipo Ackermann** armado con piezas de LEGO. Esta geometría asegura que las ruedas interiores y exteriores giren con el ángulo correcto en las curvas de la pista, ofreciendo un radio de giro preciso y suave tanto a la izquierda como a la derecha.

### Distribución de Componentes por Niveles ###

Para garantizar un centro de masa equilibrado y un flujo de conexiones, los componentes se distribuyeron estratégicamente en tres plantas:

- PISO 3: Cerebro del Sistema (ESP32, PCA9685, Switch)  <p>
- PISO 2: Energía y Visión (Baterías, Reguladores, Cam) <p>
- PISO 1: Mecánica y Actuadores (Motores, Dirección)    <p>

**Primer Piso (Base Mecánica y Actuación):** Alberga los actuadores principales: el motor de tracción trasera con su conjunto diferencial y el servomotor delantero de dirección. Asimismo, en este nivel se encuentran fijados los dos **sensores ultrasónicos laterales**, posicionados estratégicamente a ras de chasis para medir la proximidad de las paredes de la pista. <p>
**Segundo Piso (Gestión de Potencia y Visión Artificial):** Dedicado exclusivamente al sistema de energía y la percepción frontal. Contiene el portabaterías principal y dos reguladores de voltaje Step-Down **LM2596** calibrados con precisión a $5\text{ V}$ para alimentar de forma estable los sistemas lógicos y de control. En la parte frontal se ubica la cámara inteligente **HuskyLens**, posicionada a la altura ideal para el reconocimiento de elementos en la pista. <p>
**Tercer Piso (Unidad Central de Procesamiento):** En la cúspide se encuentra el "cerebro" del robot para protegerlo de vibraciones y facilitar la programación. Aquí se aloja el microcontrolador **ESP32**, el controlador de servos/PWM **PCA9685**, el TB6612FNG para el motor y el interruptor general de encendido.

### Integración y Fijación de Sensores ###

Con el propósito de mantener el peso al mínimo y evitar la necesidad de diseñar soportes mecánicos adicionales que aumentaran el volumen del robot, se optó por un método de **fijación directa**. Los sensores ultrasónicos se encuentran adheridos firmemente a los laterales del chasis utilizando silicona de alta densidad. Este enfoque proporciona una sujeción estructural sólida, absorbe las vibraciones mecánicas del chasis durante la marcha y mantiene los sensores perfectamente alineados con los ejes de lectura del vehículo.

# 3. Componentes Electrónicos

## a. Lista de Materiales 

A continuación, se detallan los componentes de hardware y materiales utilizados para el ensamblaje y funcionamiento óptimo del robot. La selección de estos componentes se realizó bajo criterios de eficiencia energética, compatibilidad de voltajes y ligereza estructural.

| Componente | Categoría | Cantidad | Descripción / Función en el Robot |
| :--- | :--- | :---: | :--- |
| **ESP32 DevKit V1** | Cerebro / MCU | 1 | Unidad de procesamiento central. Se encarga de ejecutar los algoritmos de navegación y control. |
| **HuskyLens (DFRobot)** | Visión Artificial | 1 | Cámara inteligente encargada del reconocimiento de objetos y procesamiento visual en la pista. |
| **Módulo PCA9685** | Controlador PWM | 1 | Expansor de canales PWM mediante protocolo I2C. Controla el servomotor y el puente H de forma eficiente. |
| **Puente H TB6612FNG** | Controlador de Motor | 1 | Driver de motor dual basado en MOSFETs de alta eficiencia. Recibe las señales del PCA9685 para controlar el sentido y velocidad del motor principal. |
| **Regulador Step-Down LM2596** | Gestión de Potencia | 2 | Reduce y estabiliza el voltaje de las baterías a un valor seguro de 5 V para la electrónica lógica. |
| **Sensores Ultrasónicos (ej: HC-SR04)** | Sensores | 2 | Ubicados a los laterales para medir la distancia respecto a las paredes y evitar colisiones. |
| **Servomotor** | Actuador | 1 | Encargado de accionar mecánicamente el sistema de dirección tipo Ackermann en el tren delantero. |
| **Motor Principal** | Actuador | 1 | Motor de corriente continua encargado de la propulsión general del vehículo a través del diferencial. |
| **Portabaterías (4 celdas)** | Energía | 1 | Soporte para el banco de baterías encargado de alimentar todo el sistema energético del robot. |
| **Botón Interruptor (Switch)** | Electrónica | 1 | Switch mecánico general encargado del corte físico de energía para los sistemas de potencia y control. |
| **Cables Jumper (Macho-Hembra / Hembra-Hembra)** | Conectividad | - | Cableado flexible utilizado para la interconexión de señales lógicas entre sensores, controladores y el MCU. |
| **Tornillería M3 (Pernos y tuercas)** | Fijación Mecánica | - | Utilizados para el ensamblaje estructural rígido entre los tres niveles del chasis impreso en 3D. |
| **Filamento de Impresión 3D** | Mecánica | - | Material termoplástico (PLA/PETG) utilizado para la manufactura aditiva de los tres niveles del chasis. |
| **Kits de LEGO Technic** | Mecánica | - | Componentes estructurales de precisión: engranajes del diferencial, ejes de transmisión y ruedas. |

---

###  Arquitectura de Potencia y Señal (Breve Introducción) ###

Para garantizar la estabilidad del sistema, la electrónica se divide en dos etapas críticas:
1.  **Etapa de Potencia:** Gestionada desde el portabaterías directo hacia el driver **TB6612FNG** y el servomotor, pasando previamente por el botón interruptor general para un corte de energía seguro.
2.  **Etapa Lógica:** Alimentada a través de los dos reguladores **LM2596** regulados a $5\text{ V}$, garantizando que las caídas de voltaje de los motores no reinicien el microcontrolador **ESP32** ni la cámara **HuskyLens**.

 ## a. Diagrama de conexiones

 ACTUALIZAR 1/7
