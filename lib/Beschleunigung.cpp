
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
#include "Beschleunigung.h"
#include <M5Stack.h>

Beschleunigung::Beschleunigung(){
  //Quelle: http://www.esp32learning.com/code/esp32-and-mpu-9250-sensor-example.php
  //Wire.begin();
  this->mpu.initMPU9250();
  this->mpu.initAK8963(this->mpu.magCalibration);
  this->mpu.calibrateMPU9250(this->mpu.gyroBias, this->mpu.accelBias);
}

//Quelle: https://docs.m5stack.com/en/api/mpu9250 -> readAccelData()
void Beschleunigung::update(){
  if (this->mpu.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01){
    this->mpu.readAccelData(this->mpu.accelCount);
    
    this->mpu.getAres();
    
    this->mpu.ax = (float)this->mpu.accelCount[0] * this->mpu.aRes;
    this->mpu.ay = (float)this->mpu.accelCount[1] * this->mpu.aRes;
    this->mpu.az = (float)this->mpu.accelCount[2] * this->mpu.aRes;
    
    //Display X-Acceleration
    M5.Lcd.setCursor(0, 220);
    this->accX = this->mpu.ax * 1000;
    M5.Lcd.print(this->accX);
    
    //Display Y-Acceleration
    M5.Lcd.setCursor(100, 220);
    this->accY = this->mpu.ay * 1000;
    M5.Lcd.print(this->accY);

    //Display Z-Acceleration
    M5.Lcd.setCursor(200, 220);
    this->accZ = this->mpu.az * 1000;
    M5.Lcd.print(this->accZ);
  }
}






