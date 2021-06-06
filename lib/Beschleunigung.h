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


#ifndef BESCHLEUNIGUNG_H
#define BESCHLEUNIGUNG_H



#include "Arduino.h"
#include <M5Stack.h>
#include <../M5Stack/src/utility/MPU9250.h>

class Beschleunigung {
    private:
        MPU9250 mpu;

        //X-,Y- und Z-Koordinaten für Beschleunigung
        float accX;
        float accY;
        float accZ;
        
    public:
        //Constructor
        Beschleunigung();

        //display
        void update();

        //getter
        float getAccX(){return this->accX;}
        float getAccY(){return this->accY;}
        float getAccZ(){return this->accZ;}
};

#endif