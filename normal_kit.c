// In Arduino

#include <SoftwareSerial.h> 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

SoftwareSerial mySerial(10, 11); // RX, TX 
unsigned long delayTime;
unsigned int pms[32]; 

void setup() {
    pinMode(LED_BUILTIN, OUTPUT); 
    Serial.begin(115200);
    mySerial.begin(9600); 
    Serial.println(F("Sensing Start"));

    bool status;
    
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
}

void loop() { 
      if(mySerial.available()>=32){
        pms[0]=mySerial.read();
        while(pms[0]!=66){
          pms[0]=mySerial.read(); 
        }
        for(int k=1; k<32; k++){
          pms[k]=mySerial.read();
        }

    int PM1_0=(pms[10]<<8)   | pms[11]; 
    int PM2_5=(pms[12]<<8)  | pms[13];
    int PM10 =(pms[14]<<8)  | pms[15];
//    Serial.print("PM1.0 : ");
//    Serial.println(PM1_0);
//    Serial.print("PM2.5 : ");
//    Serial.println(PM2_5); 
//    Serial.print("PM10.0 : ");
//    Serial.println(PM10);
//    Serial.print("Temperature = ");
//    Serial.print(bme.readTemperature());
//    Serial.println(" *C");
//    Serial.print("Pressure = ");
//    Serial.print(bme.readPressure() / 100.0F);
//    Serial.println(" hPa");
//    Serial.print("Approx. Altitude = ");
//    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
//    Serial.println(" m");
//    Serial.print("Humidity = ");
//    Serial.print(bme.readHumidity());
//    Serial.println(" %");

    String jsondata = "";
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["temp"] = int(bme.readTemperature());
    root["humid"] = int(bme.readHumidity());
    root["PM2.5"] = PM2_5;
    root["PM10.0"] = PM10;

    root.printTo(jsondata);
    Serial.println(jsondata);
  } 
}
