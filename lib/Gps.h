/**
 * Hochschule Osnabrück - Modul: Internet of Things / Industrie 4.0 (Praktikum)
 * Versuch 3: Road Condition Monitoring
 * 
 * @file Gps.h
 *
 * @brief Ziele sind das Erkennen von Straßenanomalien wie Schlaglöcher 
 * und das Ermitteln verschiedenen Straßenoberflächen unter Nutzung vom Beschleunigungssensor des M5Stacks in Kombination mit dem GPS-Modul.
 *
 * @author Maik Proba, Mat-Nr. 886125
 * Contact: maik.proba@hs-osnabrueck.de
 * 
 *  
 */


#ifndef GPS_H
#define GPS_H



#include "Arduino.h"
#include <M5Stack.h>
#include <TinyGPS++.h>
#include "Uhr.h"

class Gps {
    private:
        TinyGPSPlus tinyGPSPlus;
        Uhr uhr;
        HardwareSerial GPSRaw; /* By default, GPS is connected with M5Core through UART2 */
        
        //Dauer
        uint32_t startTime;
        uint32_t endTime;

        //aktuelle Position
        double latPosA; 
        double lngPosA;
        
        //nächste Position
        double latPosB;
        double lngPosB;

        //ist Distanzmodus an?
        bool isDistanceMode=false;
        
        int dauer=-99;
        double distance=-99;

        
    public:
        //Constructor
        Gps();

        //getter
        int getDauer(){return this->dauer;};
        double getDistance(){return this->distance;};

        //display
        void displayAnzSatelliten(int posX, int posY);
        void displayHDOP(int posX, int posY);
        void displayLat(int posX, int posY);
        void displayLng(int posX, int posY);
        void displayTime(int posX, int posY);
        void displayDate(int posX, int posY);
        void updateDisplay(int posX, int posY);

        //Distanz berechnen
        void setPosition();
        void displayDistance();
};

#endif