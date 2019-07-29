/* 
A simple temperature reporter to Adafruit IO cloud 
using a DHT22 temperature/humidity sensor
and a ESP32 Dev Kit board from http://bit.ly/2LM2lix

By AD6DM Dennis 7/29/2019
*/


#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>

#include "DHT.h"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "[yourusername]"
#define AIO_KEY  "[youradafruitio_key]"
#define DHTPIN 4
#define DHTTYPE DHT22
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

boolean MQTT_connect();

boolean MQTT_connect() {  int8_t ret; if (mqtt.connected()) {    return true; }  uint8_t retries = 3;  while ((ret = mqtt.connect()) != 0) { mqtt.disconnect(); delay(2000);  retries--;if (retries == 0) { return false; }} return true;}

DHT dht4(DHTPIN, DHTTYPE);

// Make an Adafruit IO feed for each of these: garagetemp, garagehumid

Adafruit_MQTT_Publish garagetemp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/garagetemp");
Adafruit_MQTT_Publish garagehumid = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/garagehumid");
void setup()
{
Serial.begin(9600);

  dht4.begin();

  WiFi.disconnect();
  delay(3000);
  Serial.println("START");

  // Enter your network wifi SSID and Password below
  WiFi.begin("[SSID]","[WIFI_PASSWORD]");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is ");
  Serial.println((WiFi.localIP()));

}


void loop()
{
  float h = dht4.readHumidity();
  float f = dht4.readTemperature(true);
  if (isnan(h) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(5000); // Allow things to settle down
    return;
  }
  
    if (MQTT_connect()) {
      if (garagetemp.publish((f))) {
        Serial.println("Published temperature: ");
        Serial.println(f);
      } else {
        Serial.println("Failure to publish temperature.");
      }

      if (garagehumid.publish((h))) {
        Serial.println("Published humidity: ");
        Serial.println(h);
      } else {
        Serial.println("Failure to publish humidity.");
      }

      // Updates every minute. The Adafruit free account allows 30 data points a minute
      // and stores 30 days worth of data.
      delay(60000);

    }

}

