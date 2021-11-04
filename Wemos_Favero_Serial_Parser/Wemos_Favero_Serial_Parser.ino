#include<ESP8266WiFi.h>
#include<espnow.h>
#include <FastLED.h>

#define MY_NAME         "CONTROLLER_NODE"
#define MY_ROLE         ESP_NOW_ROLE_CONTROLLER         // set the role of this device: CONTROLLER, SLAVE, COMBO
#define RECEIVER_ROLE   ESP_NOW_ROLE_SLAVE              // set the role of the receiver
#define WIFI_CHANNEL    1

//uint8_t receiverAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};   // please update this with the MAC address of the receiver
uint8_t receiverAddress[] = {0xBC, 0xFF, 0x4D, 0x18, 0xF7, 0x1C};

const unsigned int MAX_MESSAGE_LENGTH = 10;
const unsigned int MAX_SERIAL_BUFFER_BYTES = 512;
//const byte STARTING_BYTE = 11111111;
//const char STARTING_BYTE = FF;
const char STARTING_BYTE = 255;

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

// Shows if new data is available for display
bool new_data = false;

// Initializes Message_Position
unsigned int message_pos = 0;

void setup() {
  Serial.setRxBufferSize(1024);
  Serial.begin(2400); // initialize serial port
  delay(10);
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

  EVERY_N_MILLISECONDS(200) {
    wdt_reset();
  }

  dataPacket packet;

  //  Check to see if anything is available in the serial receive buffer
  while (Serial.available() > 0) {

    EVERY_N_MILLISECONDS(5000) {
      Serial.println("Checking available Serial Data.");
    }

    // Create a place to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static char prev_message[MAX_MESSAGE_LENGTH];

    char inByte = Serial.read();

    // Message coming in (check if starting character)
    if (inByte == STARTING_BYTE) {
      // Resets message position
      message_pos = 0;
      // Stores the Byte in the message position
      message[message_pos] = inByte;
      //increments message position
      message_pos++;
    }
    else if (message_pos < (MAX_MESSAGE_LENGTH - 1))
    {
      // Stores the Byte in the message position
      message[message_pos] = inByte;
      //increments message position
      message_pos++;
    }
    else if (message_pos == (MAX_MESSAGE_LENGTH - 1))
    {

      // Prints the Message if different from previous
      // Excudes the internal use byte in position 7 or check sum.
      if (message[1] != prev_message[1] or message[2] != prev_message[2] or message[3] != prev_message[3] or message[4] != prev_message[4] or
          message[5] != prev_message[5] or message[6] != prev_message[6] or message[8] != prev_message[8])
      {
        // Sets New Data to True
        new_data = true;

        Serial.print("The message in HEX is: ");
        for (int i = 0; i < MAX_MESSAGE_LENGTH ; i++) {
          Serial.print(message[i], HEX);
          Serial.print(",");
        }
        Serial.println("");

        // Assigns values from message to packet
        packet.Green_Light = bitRead(message[5], 3);
        packet.Red_Light = bitRead(message[5], 2);
        packet.White_Green_Light = bitRead(message[5], 1);
        packet.White_Red_Light = bitRead(message[5], 0);
        packet.Yellow_Green_Light = bitRead(message[5], 4);
        packet.Yellow_Red_Light = bitRead(message[5], 5);

        packet.Yellow_Card_Green = bitRead(message[8], 2);
        packet.Yellow_Card_Red = bitRead(message[8], 3);
        packet.Red_Card_Green = bitRead(message[8], 0);
        packet.Red_Card_Red = bitRead(message[8], 1);

        packet.Priority_Right = bitRead(message[6], 2);
        packet.Priority_Left = bitRead(message[6], 3);

        // Stores the Score and Time
        packet.Right_Score = hex_string_to_int(message[1]);
        packet.Left_Score = hex_string_to_int(message[2]);
        packet.Seconds_Remaining = hex_string_to_int(message[3]);
        packet.Minutes_Remaining = hex_string_to_int(message[4]);

        // Sets Previous Message to Current Message
        for (int i = 0; i < MAX_MESSAGE_LENGTH ; i++) {
          prev_message[i] = message[i];
        }

        // Resets Message Position
        message_pos = 0;

        // Clears the Serial Buffer if more than Max Buffer Bytes bytes in the buffer
        if (Serial.available() > MAX_SERIAL_BUFFER_BYTES)
        {
          Serial.println("...............Clearing the Serial Buffer...............");
          while (Serial.available() > 0)
          {
            char inByte = Serial.read();
          }
        }
      }
    } else {
      Serial.println("Unexpected Message Position, Reseting to zero.");
      message_pos = 0;
    }
  }

  //   Only transmits when new data is available
  if (new_data == true) {
    esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));
    // Sets New Data to False
    new_data = false;
  }
}

void transmissionComplete(uint8_t *receiver_mac, uint8_t transmissionStatus) {
  if (transmissionStatus == 0) {
    //    Serial.println("Data sent successfully");
  } else {
    Serial.print("Error code: ");
    Serial.println(transmissionStatus);
  }
}
