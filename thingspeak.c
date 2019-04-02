
#include <ESP8266.h>
#include <SoftwareSerial.h>

#define SSID        "KMU_SW"
#define PASSWORD    "kookminsw"
#define HOST_NAME   "api.thingspeak.com"
#define HOST_PORT   (80)
#define API_KEY     "1KMV7AZNGQI6EX2H"
#define WAIT        (600000)

SoftwareSerial mySerial(2, 3); /* RX:D3, TX:D2 */
ESP8266 wifi(mySerial);

void setup(void)
{
  Serial.begin(9600);
  Serial.print("setup begin\r\n");

  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print("to station + softap ok\r\n");
  } else {
    Serial.print("to station + softap err\r\n");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print("Join AP success\r\n");
    Serial.print("IP:\r\n");
    Serial.println( wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }

  if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
  } else {
    Serial.print("single err\r\n");
  }

  Serial.print("setup end\r\n");
}

void loop(void)
{
  uint8_t buffer[128] = {0};

  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.print("create tcp ok\r\n");
  } else {
    Serial.print("create tcp err\r\n");
  }


    int temp = 40;
    int humid = 50;
    int pm25 = 10;
    int pm10 = 100;
    
    char *paramTpl = "?api_key=%s&field1=%d&field2=%d&field3=%d&field4=%d";
    char param[80];
    sprintf(param, paramTpl, API_KEY, temp, humid, pm25, pm10);
    
      // This will send the request to the server
    char *headerTpl = "GET /update%s HTTP/1.1\r\n"
                 "Host: %s\r\n"
                 "Cache-Control: no-cache\r\n"
                 "Content-length: 0\r\n\r\n";
    char header[200];
    sprintf(header, headerTpl, param, HOST_NAME);
  
    wifi.send((const uint8_t*)header, strlen(header));


  uint32_t len = wifi.recv(buffer, sizeof(buffer), 256);
  if (len > 0) {
    Serial.print("Received:[");
    for (uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print("]\r\n");
  }

  if (wifi.releaseTCP()) {
    Serial.print("release tcp ok\r\n");
  } else {
    Serial.print("release tcp err\r\n");
  }
  delay(WAIT);
}
