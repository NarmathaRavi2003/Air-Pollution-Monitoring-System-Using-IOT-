#include <ESP8266WiFi.h>
#include <Wire.h>
#include "MQ135.h"

// Pin definitions
#define LM35_PIN A0         // LM35 connected to A0
#define SOIL_PIN A0        // Soil Moisture Sensor connected to A1 (changed to avoid conflict)
#define MQ135_PIN A0        // MQ135 Gas Sensor connected to A2 (changed to avoid conflict)

MQ135 gasSensor(MQ135_PIN); // MQ135 gas sensor initialization

const char* ssid = "SSN";
const char* password = "Ssn1!Som2@Sase3#";

const char* server = "api.thingspeak.com";
const String apiKey = "ZUCOKBJQF9D4LDYP";

WiFiClient client;

// Calibrated Ro value for clean air (in kΩ)
float Ro = 10.0;

// Calibration offsets for LM35 temperature sensor
float lm35Offset = -22.5; // Adjust as per calibration

// Calibration factor for air quality readings
float airQualityCalibrationFactor = 65.0; // Adjust as needed

// Function to calibrate air quality readings
float calibrateAirQuality(float rawAirQuality) {
    // Apply calibration factor
    return rawAirQuality * (airQualityCalibrationFactor / 100.0);
}

void setup() {
  Serial.begin(9600);

  pinMode(LM35_PIN, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  float t = readLM35Temperature() + lm35Offset; // Apply calibration offset
  float soilMoisture = (100-((readSoilMoisture()/1023.0)*100));
  float air_quality = calibrateAirQuality(readAirQuality());
  float nh3 = calculateNH3Concentration();
  float benzene = calculateBenzeneConcentration();
  float co2 = calculateCO2Concentration();
  float so2 = calculateSO2Concentration();
   // Calculate saturation vapor pressure (e_s) at the given temperature
  float e_s = 6.11 * pow(10, (7.5 * t) / (237.3 + t));

  // Estimate actual vapor pressure (e_a) based on soil moisture
  float e_a = e_s * (soilMoisture / 100.0);

  // Calculate relative humidity (RH)
  float relativeHumidity = (e_a / e_s) * 100.0;


  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Soil Moisture: ");
  Serial.println(relativeHumidity);
  Serial.print("Air Quality: ");
  Serial.print(air_quality);
  Serial.println(" PPM");
  Serial.print("NH3: ");
  Serial.println(nh3);
  Serial.print("Benzene: ");
  Serial.println(benzene);
  Serial.print("CO2: ");
  Serial.println(co2);
  Serial.print("SO2: ");
  Serial.println(so2);

  if (client.connect(server, 80)) {
    String postStr = "api_key=" + apiKey;
    postStr += "&field1=" + String(t);
    postStr += "&field2=" + String(relativeHumidity);
    postStr += "&field3=" + String(air_quality);
    postStr += "&field4=" + String(nh3);
    postStr += "&field5=" + String(benzene);
    postStr += "&field6=" + String(co2);
    postStr += "&field7=" + String(so2);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();

  delay(200); // Wait 2 seconds before sending the next set of data
}

float readLM35Temperature() {
  // Switch to LM35 and read temperature
  pinMode(LM35_PIN, INPUT);
  int rawValue = analogRead(LM35_PIN);
  float millivolts = (rawValue / 1024.0) * 3300; // Convert the analog reading to millivolts
  float temperatureC = millivolts / 10; // 10 mV per degree Celsius
  return temperatureC;
}

float readSoilMoisture() {
  // Switch to Soil Moisture Sensor and read value
  pinMode(SOIL_PIN, INPUT);
  return analogRead(SOIL_PIN);
}

float readAirQuality() {
  // Switch to MQ135 and read air quality
  pinMode(MQ135_PIN, INPUT);
  return gasSensor.getPPM();
}

float calculateNH3Concentration() {
  float Rs = gasSensor.getResistance();
  float ratio = Rs / Ro;
  float concentration = 1 / (pow(10, ((log10(ratio) - 0.4) / -0.67)));
  return concentration;
}

float calculateBenzeneConcentration() {
  float Rs = gasSensor.getResistance();
  float ratio = Rs / Ro;
  float concentration = 1 / (pow(10, ((log10(ratio) - 0.5) / -1.52)));
  return concentration;
}

float calculateCO2Concentration() {
  float Rs = gasSensor.getResistance();
  float ratio = Rs / Ro;
  float concentration = 1 / (pow(10, ((log10(ratio) - 0.2) / -0.64)));
  return concentration;
}

float calculateSO2Concentration() {
  float Rs = gasSensor.getResistance();
  float ratio = Rs / Ro;
  // Assuming a similar sensitivity relationship as for other gases
  float concentration = 1 / (pow(10, ((log10(ratio) - 0.3) / -0.72)));
  return concentration;
}
