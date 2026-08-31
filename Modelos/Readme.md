# ⚙️ Modelos 3D y Diseño Mecánico – Team Nexus
En esta sección se encuentran todos los componentes mecánicos diseñados y modelados en 3D para el vehículo autónomo de **Team Nexus (WRO 2026)**.
---
## 🏎️ **Filosofía del Diseño Mecánico y Arquitectura por Capas**
Para optimizar el centro de masa, el aislamiento eléctrico y facilitar el mantenimiento rápido durante la competencia, el chasis se estructuró en una **arquitectura vertical de 3 niveles**:
| Nivel / Piso | Componentes Instalados | Propósito de Ingeniería y Justificación |
| :--- | :--- | :--- |
| **🏢 Nivel 3**<br>*(Techo / Superior)* | • Portabaterías<br>• Regulador Buck (Step-Down 5V)<br>• *Futuro módulo Step-Up (Boost)* | **Gestión de Potencia:**<br>• Acceso rápido para reemplazo de baterías entre rondas.<br>• Aislamiento térmico y eléctrico de la fuente de poder principal.<br>• Separación de líneas para evitar caídas de tensión en el microcontrolador. |
| **🧠 Nivel 2**<br>*(Intermedio / Lógica)* | • Microcontrolador ESP32<br>• Cámara HuskyLens<br>• Giroscopio / IMU *(en el centro de masa)*<br>• Driver de motor DC<br>• Protoboard de desarrollo | **Cerebro y Navegación:**<br>• **IMU en el centro geométrico** para evitar aceleraciones tangenciales y lecturas de giro erróneas.<br>• **HuskyLens** con línea de visión despejada y altura ideal para detección de bloques.<br>• Centralización de señales de control. |
| **⚙️ Nivel 1**<br>*(Base / Inferior)* | • Motor DC de tracción trasera<br>• Servomotor de dirección + brazo impreso<br>• 3x Sensores Ultrasónicos (1 frontal, 2 laterales) | **Tracción, Dirección y Sensado Perimetral:**<br>• **Centro de gravedad bajo** que otorga máxima estabilidad en curvas y evita volcadas.<br>• Transmisión mecánica directa y precisa en la dirección.<br>• Ultrasónicos a baja altura para detección exacta de paredes y límites de pista. |
---
## 🛠️ **Herramientas de Diseño y Fabricación Digital**
* **Software de Modelado CAD:** Autodesk Fusion 360 *(diseño paramétrico, ensamblaje virtual y verificación de tolerancias)*.
* **Tecnología de Fabricación:** Impresión 3D FDM de alta precisión en impresora **Bambu Lab** *(utilizando Bambu Studio)*.
* **Material Principal:** [PETG] *(alta rigidez estructural, resistencia a impactos y estabilidad térmica)*.

### 🎯 **Hoja de Ruta de Mejoras (Planes Futuros)**
* 🔄 **Independización de Potencia:** Integración de un regulador Step-Up dedicado exclusivamente al motor DC para que la demanda de corriente no afecte el voltaje del ESP32.
* 🔄 **Calibración de IMU:** Sustitución y calibración del giroscopio actual por uno de menor deriva (*drift*) para mayor precisión en la odometría de rumbo.
