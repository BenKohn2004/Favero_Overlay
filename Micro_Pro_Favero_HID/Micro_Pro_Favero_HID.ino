// Arduino Leonardo
// Receives inputs and acts as a Human Input Device (HID)
// Sends HotKeys to computer as a keyboard to change visibility
// of overlay lights

// data to be received
struct I2cRxStruct {
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

int unsigned prev_Right_Score = 0;
int unsigned prev_Left_Score = 0;
int unsigned prev_Seconds_Remaining = 0;
int unsigned prev_Minutes_Remaining = 0;
bool prev_Green_Light = 0;
bool prev_Red_Light = 0;
bool prev_White_Green_Light = 0;
bool prev_White_Red_Light = 0;
bool prev_Yellow_Green_Light = 0;
bool prev_Yellow_Red_Light = 0;
bool prev_Yellow_Card_Green = 0;
bool prev_Yellow_Card_Red = 0;
bool prev_Red_Card_Green = 0;
bool prev_Red_Card_Red = 0;
bool prev_Priority_Left = 0;
bool prev_Priority_Right = 0;

bool newRxData = false;

I2cRxStruct data_received;
//I2cRxStruct rxData;

#include <Keyboard.h>
#include <Wire.h> // i2c

const byte thisAddress = 9; // these need to be swapped for the other Arduino
const byte otherAddress = 8;

void setup() {
  Serial.begin(115200);
  //  Serial.begin(2400);
  Serial.println("Starting!");
  Serial.println("Setting up i2c.");

  // set up I2C
  Wire.begin(thisAddress); // join i2c bus
  Wire.onReceive(receiveEvent); // register event

  Serial.println("Setup Complete!");
}

void loop() {

  // this bit checks if a message has been received
  if (newRxData == true ) {

    Toggle_Light_Overlays();

    // Only Adjusts the Score or Time when there is information to update
    if (prev_Right_Score != data_received.Right_Score or
        prev_Left_Score != data_received.Left_Score or
        prev_Seconds_Remaining != data_received.Seconds_Remaining or
        prev_Minutes_Remaining != data_received.Minutes_Remaining
       )

    {
      // Serial Output for Putty
      // Adds a space to maintain spacing for Numbers Less than 10
      // Feed Forward Creates a New Page for the Serial Monitor
      Serial.print('\f');
      if (data_received.Left_Score < 10) {
        Serial.print(' ');
        Serial.print(data_received.Left_Score, DEC);
      } else {
        Serial.print(data_received.Left_Score, DEC);
      }
      if (data_received.Right_Score < 10) {
        Serial.print(' ');
        Serial.print(data_received.Right_Score, DEC);
      } else {
        Serial.print(data_received.Right_Score, DEC);
      }
      Serial.print(' ');
      Serial.print(data_received.Minutes_Remaining);
      Serial.print(':');
      if (data_received.Seconds_Remaining < 10) {
        Serial.print('0');
        Serial.print(data_received.Seconds_Remaining, DEC);
      } else {
        Serial.print(data_received.Seconds_Remaining, DEC);
      }
    }

    // Set Previous Data
    prev_Right_Score = data_received.Right_Score;
    prev_Left_Score = data_received.Left_Score;
    prev_Seconds_Remaining = data_received.Seconds_Remaining;
    prev_Minutes_Remaining = data_received.Minutes_Remaining;
    prev_Green_Light = data_received.Green_Light;
    prev_Red_Light = data_received.Red_Light;
    prev_White_Green_Light = data_received.White_Green_Light;
    prev_White_Red_Light = data_received.White_Red_Light;
    prev_Yellow_Green_Light = data_received.Yellow_Green_Light;
    prev_Yellow_Red_Light = data_received.Yellow_Red_Light;
    prev_Yellow_Card_Green = data_received.Yellow_Card_Green;
    prev_Yellow_Card_Red = data_received.Yellow_Card_Red;
    prev_Red_Card_Green = data_received.Red_Card_Green;
    prev_Red_Card_Red = data_received.Red_Card_Red;
    prev_Priority_Left = data_received.Priority_Left;
    prev_Priority_Right = data_received.Priority_Right;

    newRxData = false;

  }
}

// This function is called by the Wire library when a message is received
void receiveEvent(int numBytesReceived) {

  if (newRxData == false) {
    // copy the data to data_received
    Wire.readBytes( (byte*) &data_received, numBytesReceived);
    newRxData = true;
  }
  else {
    // dump the data
    while (Wire.available() > 0) {
      byte c = Wire.read();
    }
  }
}
