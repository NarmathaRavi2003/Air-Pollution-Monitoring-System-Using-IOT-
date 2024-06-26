# Air-Pollution-Monitoring-System-Using-IOT-

The Smart Air Pollution Monitoring System is designed to provide real-time data on air quality and environmental conditions using advanced sensing technology. The system employs an MQ135 sensor to detect air pollutants such as ammonia (NH3), benzene, sulfur compounds, and carbon dioxide (CO2). Additionally, it integrates temperature and moisture sensors to monitor ambient temperature and humidity levels. The core of the system is powered by the NodeMCU ESP8266, a microcontroller board that facilitates data transmission to the cloud.

Collected data is sent to ThingSpeak, an IoT analytics platform, where it is stored and processed. To enhance accessibility and user interaction, we developed a dedicated website that displays the monitored values in an intuitive and user-friendly interface. Users can register on the website to receive timely alerts via email when the air quality index falls below acceptable levels, ensuring prompt awareness and response to potential health hazards.

**Components Used**:

NodeMCU-ES8266<br>
Temperature Sensor(LM35)<br>
Moisture Sensor<br>
MQ135 Sensor-For detecting the air quality in ppm<br>
Jumper Wires<br>
Bread Board<br>
USB Cable<br>


**Reqiurements**:

•	Set up email services for sending alerts.<br>
More details refer requirement.txt

**Connections**:

LM35 Temperature:<br>
VCC -> 3.3V (NodeMCU's 3.3V pin)<br>
GND -> GND<br>
Data -> Analog pin (A0)<br>

Moisture Sensor:<br>
VCC -> 3.3V (NodeMCU's 3.3V pin)<br>
GND -> GND<br>
Data -> Analog pin (A0)<br>

MQ135 Gas Sensor:<br>
VCC -> 3.3V or 5V (Use NodeMCU's 3.3V pin)<br>
GND -> GND<br>
Data -> Analog pin (A0)<br>

NodeMCU:<br>
Connect NodeMCU to laptop via USB.<br>

After all the above process run app.py
Make sure that should login to the page so that get an email alert when air quality is bad
In command prompt run the alir_quality_alert.py file
