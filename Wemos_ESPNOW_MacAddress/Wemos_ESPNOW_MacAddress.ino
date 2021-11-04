  
/****************************************************************************************************************************************************
 *  TITLE: ESP-NOW Getting Started Examples
 *
 *  By Frenoy Osburn
 *  YouTube Video: https://youtu.be/_cNAsTB5JpM
 ****************************************************************************************************************************************************/

 /********************************************************************************************************************
  * Please make sure that you install the board support package for the ESP8266 boards.
  * You will need to add the following URL to your Arduino preferences.
  * Boards Manager URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
 ********************************************************************************************************************/
 
 /********************************************************************************************************************
 *  Board Settings:
 *  Board: "WeMos D1 R1 or Mini"
 *  Upload Speed: "921600"
 *  CPU Frequency: "80MHz"
 *  Flash Size: "4MB (FS:@MB OTA:~1019KB)"
 *  Debug Port: "Disabled"
 *  Debug Level: "None"
 *  VTables: "Flash"
 *  IwIP Variant: "v2 Lower Memory"
 *  Exception: "Legacy (new can return nullptr)"
 *  Erase Flash: "Only Sketch"
 *  SSL Support: "All SSL ciphers (most compatible)"
 *  COM Port: Depends *On Your System*
 *********************************************************************************************************************/
 #include<ESP8266WiFi.h>

void setup() 
{  
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("This is my address: ");
  Serial.println(WiFi.macAddress());
}

void loop() 
{
  delay(1000);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("This is my address: ");
  Serial.println(WiFi.macAddress());
}
