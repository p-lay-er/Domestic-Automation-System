
#define BLYNK_TEMPLATE_NAME "Temp Sensor"
#define BLYNK_AUTH_TOKEN "cZjHy1qRUAaCXDo1XGlYdBS4HjhC7q2r"
#define BLYNK_TEMPLATE_ID "TMPL3eg88JbkP"
#define BLYNK_PRINT Serial

#include <DHT.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include <BlynkSimpleEsp32.h>

DHT dht(25, DHT11);
const int buzzer = 5; 

Servo myServo;
int servoPin = 14;
int servoSpeed = 1000;

bool signUpOK = false;

char ssid[] = "OnePlus";
char password[] = "password";

void setup() {
  
  dht.begin();
  myServo.write(0);
  delay(2000);  
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  Serial.println("Hello World");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to Wi-Fi with IP: ");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  myServo.attach(servoPin);
  myServo.setPeriodHertz(50); 

  Serial.println("loop started.");
}

float temperature, humidity;
float lower_thr = 30, higher_thr = 50;

void loop() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if(WiFi.status() != WL_CONNECTED)
    WiFi.begin(ssid, password);

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V2, humidity);

  Serial.print("Temp: ");
  Serial.println(temperature);
  Serial.print("Humid: ");
  Serial.println(humidity);

  // if(temperature > lower_thr) rotateServo();

  if (temperature > lower_thr) digitalWrite(buzzer, HIGH);
  else digitalWrite(buzzer, LOW);
  
  delay(500);
}

void rotateServo() {
  myServo.write(0);
  delay(400);
  myServo.write(180);
  delay(400);
  myServo.write(0);
  delay(400);
}