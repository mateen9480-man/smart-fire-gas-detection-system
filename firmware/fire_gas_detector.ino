// Arduino Firmware for Smart Fire and Gas Leak Detection System

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Define parameters for sensors
#define FIRE_SENSOR_PIN A0
#define GAS_SENSOR_PIN A1

// Define thresholds
const int FIRE_THRESHOLD = 400; // Adjust as necessary
const int GAS_THRESHOLD = 300; // Adjust as necessary

// Wi-Fi Credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Firebase credentials
#define FIREBASE_HOST "yourproject.firebaseio.com"
#define FIREBASE_AUTH "your_firebase_database_secret"

FirebaseData firebaseData;

void setup() {
  // Start Serial Communication
  Serial.begin(115200);
  
  // Initialize WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  // Setup Sensor Pins
  pinMode(FIRE_SENSOR_PIN, INPUT);
  pinMode(GAS_SENSOR_PIN, INPUT);
}

void loop() {
  int fireValue = analogRead(FIRE_SENSOR_PIN);
  int gasValue = analogRead(GAS_SENSOR_PIN);
  
  // Detect Fire
  if (fireValue > FIRE_THRESHOLD) {
    triggerAlarm("Fire detected!");
  }
  
  // Detect Gas Leak
  if (gasValue > GAS_THRESHOLD) {
    triggerAlarm("Gas leak detected!");
  }
  
  delay(2000); // Delay before next reading
}

void triggerAlarm(String message) {
  Serial.println(message);
  Firebase.setString(firebaseData, "/alerts/lastAlert", message);
}
