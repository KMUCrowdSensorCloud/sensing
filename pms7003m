// for Arduino nano
#include <SoftwareSerial.h> 

SoftwareSerial mySerial(10, 11); // RX, TX 
unsigned int pms[32]; 
void setup() { 
  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.begin(115200); 
   mySerial.begin(9600); 
} 

void loop() { 
 
}

void printdust() {
    if(mySerial.available()>=32){ 
    for(int k=0; k<32; k++){
       pms[k]=mySerial.read();
    }
        
    int PM1_0=(pms[10]<<8)   | pms[11]; 
    int PM2_5=(pms[12]<<8)  | pms[13];
    int PM10 =(pms[14]<<8)  | pms[15];
    Serial.print("PM1.0 : ");
    Serial.println(PM1_0);
    Serial.print("PM2.5 : ");
    Serial.println(PM2_5); 
    Serial.print("PM10.0 : ");
    Serial.println(PM10);

    Serial.println("-----------------------------------");
  }
}
