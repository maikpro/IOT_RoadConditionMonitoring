
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

#include "MyInfluxDB.h"

MyInfluxDB::MyInfluxDB(){
  //InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
  //this->client=client;
}

void MyInfluxDB::writeData(String tagName, String tagValue, String fieldName, int fieldValue){
  InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);
  
  // Define data point with measurement name 'device_status`
  Point pointDevice("probaM5Stack");
  
  // Set tags
  pointDevice.addTag(tagName, tagValue);
  
  // Add data
  pointDevice.addField(fieldName, fieldValue);

  // Write data
  client.writePoint(pointDevice);
}





