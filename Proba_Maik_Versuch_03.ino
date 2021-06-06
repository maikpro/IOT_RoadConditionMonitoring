

/**
 * Hochschule Osnabrück - Modul: Internet of Things / Industrie 4.0 (Praktikum)
 * Versuch 3: Road Condition Monitoring
 * 
 * @file Proba_Maik_Versuch_3.ino
 *
 * @brief Ziele sind das Erkennen von Straßenanomalien wie Schlaglöcher 
 * und das Ermitteln verschiedenen Straßenoberflächen unter Nutzung vom Beschleunigungssensor des M5Stacks in Kombination mit dem GPS-Modul.
 *
 * @author Maik Proba, Mat-Nr. 886125
 * Contact: maik.proba@hs-osnabrueck.de
 * 
 *  
 */


#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "Gps.h"
#include "Beschleunigung.h"
#include "MyInfluxDB.h"

//WLAN Zugang
const char* ssid = "ssid";
const char* password = "123456789";

Gps gps;
Beschleunigung beschleunigung;
MyInfluxDB myInfluxDB;
uint8_t buttonC = GPIO_NUM_37; 

void drawTable(){
  //Tabelle 1:
  M5.Lcd.drawString("Sats\tHDOP\tLatitude\tLongitude\t\tDate\t\t\t\t\t\t\t\tTime", 0, 0);
  M5.Lcd.drawString("-----------------------------------------------------", 0, 20);

  //Tabelle 2: Distanz ermitteln
  M5.Lcd.drawString("Latitude\t\t\t\t\t\t\t\tLongitude\t\t\t\t\t\t\tDauer\t\t\t\t\t\tDistanz", 0, 100);
  M5.Lcd.drawString("-----------------------------------------------------", 0, 120);

  //Tabelle 3: Beschleunigung
  M5.Lcd.drawString("x-Acceleration\ty-Acceleration\tz-Acceleration", 0, 180);
  M5.Lcd.drawString("-----------------------------------------------------", 0, 200);

}

void waitForWifi(){
  //2. Warten auf erfolgreiche WiFi-Verbindung 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected :)");  
}

void setup(){
  //M5 init
  M5.begin();
  
  //21 => SDA, 22 => SCL
  Wire.begin(GPIO_NUM_21, GPIO_NUM_22);
  
  WiFi.begin(ssid, password);

  configTzTime("pool.ntp.org", "2.europe.pool.ntp.org");
  //Battery nutzen
  M5.Power.begin();
}

void setPosition(){
  gps.setPosition();
}

//sendet die Sensordaten an die InfluxDB der Hochschule
void sendDataToInfluxDB(){
  int dauer = gps.getDauer();
  myInfluxDB.writeData("testmp", "tagMaik2", "Dauer", dauer);

  int distance = gps.getDistance();
  myInfluxDB.writeData("testmp", "tagMaik2", "Distanz", distance);

  float accX = beschleunigung.getAccX();
  myInfluxDB.writeData("testmp", "tagMaik2", "x-Acceleration", accX);

  float accY = beschleunigung.getAccY();
  myInfluxDB.writeData("testmp", "tagMaik2", "y-Acceleration", accY);
  
  float accZ = beschleunigung.getAccZ();
  myInfluxDB.writeData("testmp", "tagMaik2", "z-Acceleration", accZ);
}

void loop() {
  M5.update();

  waitForWifi();
  gps.updateDisplay(0, 40);
  beschleunigung.update();
  
  gps.displayDistance();
  drawTable();

  //Daten an die InfluxDB schicken:
  sendDataToInfluxDB();

  //Wenn Button C gedrückt wird:
  attachInterrupt(buttonC, setPosition, RISING);
}

