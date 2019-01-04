// header url : https://github.com/bblanchon/ArduinoJson
#include <MECHA_PMS5003ST.h>
#include <SoftwareSerial.h>

SoftwareSerial dust(2,3);

MECHA_PMS5003ST pms(&dust);

void setup() {
  Serial.begin(115200);
  pms.begin();
//  pms.wakeUp();
  pms.setMode(PASSIVE);
}

void loop() {
  pms.request();
  if(!pms.read()){
    return;
  }

  String jsondata = "";
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["tempvalue"] = pms.getTemp();
  root["humivalue"] = pms.getHumi();
  root["PM1.0(ATO)"] = pms.getPmAto(1.0);
  root["PM2.5(ATO)"] = pms.getPmAto(2.5);
  root["PM10.0(ATO)"] = pms.getPmAto(10);

  root.printTo(jsondata);
  Serial.println(jsondata);
  delay(1000);
}
