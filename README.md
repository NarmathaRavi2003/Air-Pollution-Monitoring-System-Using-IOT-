# Air-Pollution-Monitoring-System-Using-IOT-

The Smart Air Pollution Monitoring System is designed to provide real-time data on air quality and environmental conditions using advanced sensing technology. The system employs an MQ135 sensor to detect air pollutants such as ammonia (NH3), benzene, sulfur compounds, and carbon dioxide (CO2). Additionally, it integrates temperature and moisture sensors to monitor ambient temperature and humidity levels. The core of the system is powered by the NodeMCU ESP8266, a microcontroller board that facilitates data transmission to the cloud.

Collected data is sent to ThingSpeak, an IoT analytics platform, where it is stored and processed. To enhance accessibility and user interaction, we developed a dedicated website that displays the monitored values in an intuitive and user-friendly interface. Users can register on the website to receive timely alerts via email when the air quality index falls below acceptable levels, ensuring prompt awareness and response to potential health hazards.

#Components Used:

NodeMCU-ES8266.
Temperature Sensor(LM 35).
Moisture Sensor.
MQ135 Sensor-For detecting the air quality in ppm.
Jumper Wires.
Bread Board.
USB Cable.


#Reqiurements:

1.	Hardware Setup:
•	Connect the NodeMCU ESP8266 with MQ135 and other sensors.
•	Program the NodeMCU using Arduino IDE to read sensor data and send it to ThingSpeak.
2.	Cloud Integration:
•	Create ThingSpeak account.
•	Set up ThingSpeak channels for data collection.
•	Configure the NodeMCU to transmit data to ThingSpeak.
4.	Web Development:
•	Develop the frontend for the web application.
•	Implement backend services for data fetching, user authentication, and alert management.
•	Integrate ThingSpeak API to fetch and display data.
5.	User Alerts:
•	Set up email services for sending alerts.
•	Implement backend logic to monitor data and trigger alerts.

#Connections:

LM35 Temperature:
VCC -> 3.3V (NodeMCU's 3.3V pin)
GND -> GND
Data -> Analog pin (A0)

Moisture Sensor:
VCC -> 3.3V (NodeMCU's 3.3V pin)
GND -> GND
Data -> Analog pin (A0)

MQ135 Gas Sensor:
VCC -> 3.3V or 5V (Use NodeMCU's 3.3V pin)
GND -> GND
Data -> Analog pin (A0)

NodeMCU:
Connect NodeMCU to laptop via USB.


