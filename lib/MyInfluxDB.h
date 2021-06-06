/**
 * Hochschule Osnabrück - Modul: Internet of Things / Industrie 4.0 (Praktikum)
 * Versuch 3: Road Condition Monitoring
 * 
 * @file MyInfluxDB.h
 *
 * @brief Ziele sind das Erkennen von Straßenanomalien wie Schlaglöcher 
 * und das Ermitteln verschiedenen Straßenoberflächen unter Nutzung vom Beschleunigungssensor des M5Stacks in Kombination mit dem GPS-Modul.
 *
 * @author Maik Proba, Mat-Nr. 886125
 * Contact: maik.proba@hs-osnabrueck.de
 * 
 *  
 */


#ifndef MYINFLUXDB_H
#define MYINFLUXDB_H

#include "Arduino.h"
#include <M5Stack.h>

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include <Options.h>
#include <Point.h>
#include <WritePrecision.h>

//Quelle: https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino
// InfluxDB 2 server or cloud url, e.g. https://eu-central-1-1.aws.cloud2.influxdata.com (Use: InfluxDB UI -> Load Data -> Client Libraries)
#define INFLUXDB_URL "http://131.173.110.147:8086"
// InfluxDB 2 server or cloud API authentication token (Use: InfluxDB UI -> Load Data -> Tokens -> <select token>)
#define INFLUXDB_TOKEN "h5b-1iTf7Ur81R6PaXwzmiN2By6jTMMEjpx83zPHW9F7SHc2CeygZrFBfMafhHyA_sxtVf7p5A606LQJL0Vv7g=="
// InfluxDB 2 organization name or id (Use: InfluxDB UI -> Settings -> Profile -> <name under tile> )
#define INFLUXDB_ORG "hsos"
// InfluxDB 2 bucket name (Use: InfluxDB UI -> Load Data -> Buckets)
#define INFLUXDB_BUCKET "iot-bucket"

class MyInfluxDB {
    private:
        // Single InfluxDB instance
        //InfluxDBClient client;
        
    public:
        //Constructor
        MyInfluxDB();

        //getter
        InfluxDBClient getClient();

        void writeData(String tagName, String tagValue, String fieldName, int fieldValue);

};

#endif