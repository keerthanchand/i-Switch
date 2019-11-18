#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "AIO_USERNAME"
#define AIO_KEY         "YOUR_API_KEY"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Subscribe relay1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/light");
Adafruit_MQTT_Subscribe relay2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/fan");

int lightpin = 4;
int lightstate = LOW;
int fanpin = 5;
int ind = 16;
int fanstate = LOW;





void MQTT_connect();
void setup() {
  Serial.begin(115200);
  pinMode(ind, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.beginSmartConfig();
  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("SmartConfig done.");
  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(ind, LOW);
    delay(50);
    digitalWrite(ind, HIGH);
    delay(20);
  }
  Serial.println();
  Serial.println("WiFi connected");
  digitalWrite(ind, HIGH);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt.subscribe(&relay1);
  mqtt.subscribe(&relay2);
  pinMode(lightpin, OUTPUT);
  pinMode(fanpin, OUTPUT);

}
void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &relay1) {
      Serial.print(F("Got A: "));
      Serial.println((char *)relay1.lastread);
      int num = atoi((char *)relay1.lastread);
      digitalWrite(lightpin, num);
    }
    if (subscription == &relay2) {
      Serial.print(F("Got B: "));
      Serial.println((char *)relay2.lastread);
      int num2 = atoi((char *)relay1.lastread);
      digitalWrite(fanpin, num2);
    }
  }

  delay(5000);
}
void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }
  Serial.println("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    digitalWrite(ind, LOW);
    delay(1000);
    digitalWrite(ind, HIGH);
    delay(1000);
    mqtt.disconnect();
    delay(3000);
    retries--;
    if (retries == 0) {
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  digitalWrite(ind, LOW);
  delay(100);
  digitalWrite(ind, HIGH);
    delay(100);

   digitalWrite(ind, LOW);
     delay(100);

  digitalWrite(ind, HIGH);
    delay(300);
    digitalWrite(ind, LOW);
  delay(100);
  digitalWrite(ind, HIGH);
    delay(100);

   digitalWrite(ind, LOW);
     delay(100);

  digitalWrite(ind, HIGH);
    delay(300);
    digitalWrite(ind, LOW);
  delay(100);
  digitalWrite(ind, HIGH);
    delay(100);

   digitalWrite(ind, LOW);
     delay(100);

  digitalWrite(ind, HIGH);
    delay(300);

   
  
}
