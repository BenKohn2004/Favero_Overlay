/****************************************************************************************************************************************************
    TITLE: ESP-NOW Getting Started Examples

    By Frenoy Osburn
    YouTube Video: https://youtu.be/_cNAsTB5JpM
 ****************************************************************************************************************************************************/

/********************************************************************************************************************
   Please make sure that you install the board support package for the ESP8266 boards.
   You will need to add the following URL to your Arduino preferences.
   Boards Manager URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
********************************************************************************************************************/

/********************************************************************************************************************
   Board Settings:
   Board: "WeMos D1 R1 or Mini"
   Upload Speed: "921600"
   CPU Frequency: "80MHz"
   Flash Size: "4MB (FS:@MB OTA:~1019KB)"
   Debug Port: "Disabled"
   Debug Level: "None"
   VTables: "Flash"
   IwIP Variant: "v2 Lower Memory"
   Exception: "Legacy (new can return nullptr)"
   Erase Flash: "Only Sketch"
   SSL Support: "All SSL ciphers (most compatible)"
   COM Port: Depends *On Your System
*********************************************************************************************************************/

#include<ESP8266WiFi.h>
#include<espnow.h>
#include <FastLED.h>

#define MY_NAME         "CONTROLLER_NODE"
#define MY_ROLE         ESP_NOW_ROLE_CONTROLLER         // set the role of this device: CONTROLLER, SLAVE, COMBO
#define RECEIVER_ROLE   ESP_NOW_ROLE_SLAVE              // set the role of the receiver
#define WIFI_CHANNEL    1

// NodeMCU has internal Pull-Up resistors
// These are the inputs from Leon Paul/SG Light Extensions Relays
#define btn0 4  //D2
#define btn1 5  //D1
#define btn2 12  //D6
#define btn3 13  //D7


//uint8_t receiverAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};   // please update this with the MAC address of the receiver
uint8_t receiverAddress[] = {0xE8, 0xDB, 0x84, 0xC5, 0x63, 0x03};

struct __attribute__((packed)) dataPacket {
  bool sensor1;
  bool sensor2;
  bool sensor3;
  bool sensor4;
};

bool sensor1_prev = false;
bool sensor2_prev = false;
bool sensor3_prev = false;
bool sensor4_prev = false;

// Shows if new data is available for display
bool new_data = false;

void transmissionComplete(uint8_t *receiver_mac, uint8_t transmissionStatus) {
  if (transmissionStatus == 0) {
    Serial.println("Data sent successfully");
  } else {
    Serial.print("Error code: ");
    Serial.println(transmissionStatus);
  }
}

void setup() {
  Serial.begin(115200);     // initialize serial port

  delay(10);

  // Sets the inputs from the Light Extension Relays
  pinMode(btn0, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);

  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("Initializing...");
  Serial.println(MY_NAME);
  Serial.print("My MAC address is: ");
  Serial.println(WiFi.macAddress());

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();        // we do not want to connect to a WiFi network

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_set_self_role(MY_ROLE);
  esp_now_register_send_cb(transmissionComplete);   // this function will get called once all data is sent
  esp_now_add_peer(receiverAddress, RECEIVER_ROLE, WIFI_CHANNEL, NULL, 0);

  Serial.println("Initialized.");
}

void loop() {

  EVERY_N_MILLISECONDS(3000) {
    Serial.print(".");
  }

  dataPacket packet;

  // Detects Touches on Signal Low
  if (digitalRead(btn0) == LOW) packet.sensor1 = 1;
  if (digitalRead(btn1) == LOW) packet.sensor2 = 1;
  if (digitalRead(btn2) == LOW) packet.sensor3 = 1;
  if (digitalRead(btn3) == LOW) packet.sensor4 = 1;

  if (digitalRead(btn0) == HIGH) packet.sensor1 = 0;
  if (digitalRead(btn1) == HIGH) packet.sensor2 = 0;
  if (digitalRead(btn2) == HIGH) packet.sensor3 = 0;
  if (digitalRead(btn3) == HIGH) packet.sensor4 = 0;

  // Tests if the previous data is the same as the current data
  if (sensor1_prev == packet.sensor1 && sensor2_prev == packet.sensor2 && sensor3_prev == packet.sensor3 && sensor4_prev == packet.sensor4) {
    new_data = false;
  } else {
    new_data = true;
    Serial.println("New Data Received");
    // Tests if the New Data is going from No Lights to Lights
  }

  // Only transmits when new data is available
  if (new_data == true) {

    Serial.print("Sensor Data: ");
    Serial.print(packet.sensor1);
    Serial.print(packet.sensor2);
    Serial.print(packet.sensor3);
    Serial.println(packet.sensor4);

    esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));
    new_data = false;
  }

  sensor1_prev = packet.sensor1;
  sensor2_prev = packet.sensor2;
  sensor3_prev = packet.sensor3;
  sensor4_prev = packet.sensor4;

}
