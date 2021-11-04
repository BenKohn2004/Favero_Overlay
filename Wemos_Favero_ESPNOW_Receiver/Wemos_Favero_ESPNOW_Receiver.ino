// Receives Data via ESPNOW (Wifi) from Favero Decoder Arduino
// Transmits it Micro Pro HID to act as Keyboard input through i2c


//===================
// Using I2C to send and receive structs between two Arduinos
//   SDA is the data connection and SCL is the clock connection
//   On an Uno  SDA is A4 and SCL is A5
//   On an Mega SDA is 20 and SCL is 21
//   GNDs must also be connected
//===================

#include<ESP8266WiFi.h>
#include<espnow.h>
#include <FastLED.h>
#include <Wire.h> // i2c

#define MY_NAME   "SLAVE_NODE"

const byte thisAddress = 8; // these need to be swapped for the other Arduino
const byte otherAddress = 9;

// timing variables
unsigned long prevUpdateTime = 0;
unsigned long updateInterval = 2;

struct __attribute__((packed)) dataPacket {
  int unsigned Right_Score;
  int unsigned Left_Score;
  int unsigned Seconds_Remaining;
  int unsigned Minutes_Remaining;
  bool Green_Light;
  bool Red_Light;
  bool White_Green_Light;
  bool White_Red_Light;
  bool Yellow_Green_Light;
  bool Yellow_Red_Light;
  bool Yellow_Card_Green;
  bool Yellow_Card_Red;
  bool Red_Card_Green;
  bool Red_Card_Red;
  bool Priority_Left;
  bool Priority_Right;
};

// data to be sent
struct I2cTxStruct {
  uint8_t Right_Score;        // 1
  uint8_t Left_Score;         // 1
  uint8_t Seconds_Remaining;  // 1
  uint8_t Minutes_Remaining;  // 1
  bool Green_Light;                // 1
  bool Red_Light;                  // 1
  bool White_Green_Light;          // 1
  bool White_Red_Light;            // 1
  bool Yellow_Green_Light;         // 1
  bool Yellow_Red_Light;           // 1
  bool Yellow_Card_Green;          // 1
  bool Yellow_Card_Red;            // 1
  bool Red_Card_Green;             // 1
  bool Red_Card_Red;               // 1
  bool Priority_Left;              // 1
  bool Priority_Right;             // 1
};

I2cTxStruct txData = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {

  Serial.begin(115200);     // initialize serial port
//  Serial.begin(2400);


  Serial.println("");
  Serial.println("");
  Serial.println("");
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

  esp_now_register_recv_cb(dataReceived);   // this function will get called once all data is sent

  Serial.println("ESP-NOW Initialized.");

  Wire.begin(thisAddress); // join i2c bus

  Serial.println("i2c Initialized.");

  Serial.println("Setup Complete");
}

void loop() {
  // Loop waits, dataReceived is called when data is received
  EVERY_N_MILLISECONDS(3000) {
    Serial.print(".");
  }
}

void dataReceived(uint8_t *senderMac, uint8_t *data, uint8_t dataLength)
// Called when data is received. Data is sent from Favero Parser only if it is new data
{
  char macStr[18];
  dataPacket packet;

  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", senderMac[0], senderMac[1], senderMac[2], senderMac[3], senderMac[4], senderMac[5]);

  Serial.println();
  Serial.print("Received data from: ");
  Serial.println(macStr);

  memcpy(&packet, data, sizeof(packet));

  // Copies Data to i2c structure
  txData = {packet.Right_Score,
            packet.Left_Score,
            packet.Seconds_Remaining,
            packet.Minutes_Remaining,
            packet.Green_Light,
            packet.Red_Light,
            packet.White_Green_Light,
            packet.White_Red_Light,
            packet.Yellow_Green_Light,
            packet.Yellow_Red_Light,
            packet.Yellow_Card_Green,
            packet.Yellow_Card_Red,
            packet.Red_Card_Green,
            packet.Red_Card_Red,
            packet.Priority_Left,
            packet.Priority_Right
           };

  // Calls function to transmit data
  transmitData();
}

void transmitData() {
  Wire.beginTransmission(otherAddress);
  Wire.write((byte*) &txData, sizeof(txData));
  Wire.endTransmission();    // This is what actually sends the data
}
