
/**
 * Hochschule Osnabrück - Modul: Internet of Things / Industrie 4.0 (Praktikum)
 * Versuch 3: Road Condition Monitoring
 * 
 * @file Gps.cpp
 *
 * @brief Ziele sind das Erkennen von Straßenanomalien wie Schlaglöcher 
 * und das Ermitteln verschiedenen Straßenoberflächen unter Nutzung vom Beschleunigungssensor des M5Stacks in Kombination mit dem GPS-Modul.
 *
 * @author Maik Proba, Mat-Nr. 886125
 * Contact: maik.proba@hs-osnabrueck.de
 * 
 *  
 */

//#include "Arduino.h"
#include "Gps.h"

//Constructor member initializer list -> ein anderes Objekt initialisieren innerhalb der Klasse
Gps::Gps(): GPSRaw{ 2 }{
  this->GPSRaw.begin(9600);
};

/*zeigt die Anzahl der Satelliten auf dem Display an.*/
void Gps::displayAnzSatelliten(int posX, int posY){
  M5.Lcd.setCursor(posX, posY);
  uint32_t satAnz = this->tinyGPSPlus.satellites.value();
  M5.Lcd.printf("%d", satAnz);
}

/*zeigt den HDOP-Wert auf dem Display an.
HDOP: Horizontal Dilution Of Precision
für die Positionsbestimmung -> die Entfernungen zu mehreren Satelliten durch Signallaufzeitmessung */
void Gps::displayHDOP(int posX, int posY){
  //HDOP = Bei Satellitennavigationssystemen ein Maß für die Streubreite der Messwerte. Da DOP von der relativen Position der Satelliten zueinander
  // H = Horizontal
  M5.Lcd.setCursor( posX, posY);
  int32_t hdop = this->tinyGPSPlus.hdop.value();
  M5.Lcd.printf("%d", hdop);
}

/*zeigt die aktuelle Position auf dem Breitengrad an.*/
void Gps::displayLat(int posX, int posY){
  if( this->tinyGPSPlus.location.isValid() ){
    //latitude = Breitengrad
    //uint16_t lat = this->tinyGPSPlus.location.rawLat().deg;
    double lat = this->tinyGPSPlus.location.lat();
    M5.Lcd.setCursor(posX, posY);
    M5.Lcd.printf("%.6f", lat);
  } else{
    double testLat = 52.2163121111111;
    M5.Lcd.setCursor(posX, posY);
    M5.Lcd.printf("%.6f", testLat);
  }
}

/*zeigt die aktuelle Position auf dem Längengrad an.*/
void Gps::displayLng(int posX, int posY){
  if( this->tinyGPSPlus.location.isValid() ){
    //longitude = Längengrad
    M5.Lcd.setCursor( posX, posY);
    //uint16_t lng = this->tinyGPSPlus.location.rawLng().deg;
    double lng = this->tinyGPSPlus.location.lng();
    M5.Lcd.printf("%.6f", lng);
  } else{
    double testLng = 7.943018;
    M5.Lcd.setCursor(posX, posY);
    M5.Lcd.printf("%.6f", testLng);
  }
}

/*zeigt die aktuelle Uhrzeit an.*/
void Gps::displayTime(int posX, int posY){
  //Uhrzeit
  M5.Lcd.setCursor(posX, posY);
  uint8_t h = this->tinyGPSPlus.time.hour();
  uint8_t min = this->tinyGPSPlus.time.minute();
  uint8_t sec = this->tinyGPSPlus.time.second();
  M5.Lcd.printf("%02d:%02d:%02d", h+2, min, sec);
}

/*zeigt das aktuelle Datum an.*/
void Gps::displayDate(int posX, int posY){
  //Datum
  M5.Lcd.setCursor(posX, posY);
  uint8_t tag = this->tinyGPSPlus.date.day();
  uint8_t monat = this->tinyGPSPlus.date.month();
  uint16_t jahr = this->tinyGPSPlus.date.year();
  M5.Lcd.printf("%02d.%02d.%02d ", tag, monat, jahr);
}

/*
die Anzahl der Satelliten,
- den HDOP-Wert,
- den Breiten- (Latitude) und Längengrad (Longitude),
- sowie das Datum und die Uhrzeit
auf dem Bildschirm des M5Stacks anzeigen
*/
void Gps::updateDisplay(int posX, int posY){
  //wird jede Sekunde ausgeführt
  if( this->uhr.getExecTime() < millis() ){
    this->uhr.updateTime();

    M5.Lcd.clearDisplay(); 
    //Quelle: https://m5stack.hackster.io/ptschulik/simple-gps-tracker-d3500e
    while (GPSRaw.available() > 0){/* Check if new GP data is available */
      this->tinyGPSPlus.encode(GPSRaw.read()); /* Read until no more data is available */
      M5.Lcd.setCursor(10, 200);
    }
    //Auf dem Display Anzahl Satelliten, HDOP, Latitude, Longitude, Uhrzeit und Datum anzeigen
    //Anzahl Satelliten
    int abstand=30;
    displayAnzSatelliten(posX, posY);
    displayHDOP(posX+abstand*1, posY);
    
    displayLat(posX+abstand*2, posY);
    displayLng(posX+abstand*4, posY);
    
    displayDate(posX+abstand*6, posY);
    displayTime(posX+abstand*9, posY);

    //Jede Sekunde
    this->uhr.setExecTime(millis() + 1000);
  }
}



void Gps::setPosition(){
  if( this->isDistanceMode == false ){
    //Start
    this->latPosA = this->tinyGPSPlus.location.lat();
    this->lngPosA = this->tinyGPSPlus.location.lng();
    this->startTime = this->uhr.getExecTime(); //speicher die Startzeit
    this->endTime = 0;
    this->isDistanceMode = true;
    this->dauer=-1;
  } else{
    //Ende
    this->latPosB = this->tinyGPSPlus.location.lat();
    this->lngPosB = this->tinyGPSPlus.location.lng();
    this->endTime = this->uhr.getExecTime(); //speicher die Endzeit
    this->dauer = this->endTime - this->startTime;
    this->distance = this->tinyGPSPlus.distanceBetween(this->latPosA, this->lngPosA, this->latPosB, this->lngPosB);
    this->isDistanceMode = false;
  }
}

void Gps::displayDistance(){
  M5.Lcd.setCursor(0, 140);
  M5.Lcd.printf("%.6f", this->latPosA);

  M5.Lcd.setCursor(100, 140);
  M5.Lcd.printf("%.6f", this->lngPosA);

  M5.Lcd.setCursor(200, 140);
  M5.Lcd.printf("%d", this->dauer/1000);

  M5.Lcd.setCursor(260, 140);
  M5.Lcd.printf("%.5f", this->distance);

  //AUFNAHME MODUS AN ODER AUS?
  M5.Lcd.setCursor(0, 160);
  M5.Lcd.printf("Aufnahme: %s", this->isDistanceMode ? "ON" : "OFF");
  
}






