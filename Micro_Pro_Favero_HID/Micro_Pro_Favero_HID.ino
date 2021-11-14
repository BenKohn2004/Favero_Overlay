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

I2cRxStruct data_received_initial = (I2cRxStruct) {
  .Right_Score = 0, .Left_Score = 0, .Seconds_Remaining = 0, .Minutes_Remaining = 0,
   .Green_Light = 0, .Red_Light = 0, .White_Green_Light = 0, .White_Red_Light = 0, .Yellow_Green_Light = 0, .Yellow_Red_Light = 0,
    .Yellow_Card_Green = 0, .Yellow_Card_Red = 0, .Red_Card_Green = 0, .Red_Card_Red = 0, .Priority_Left = 0, .Priority_Right = 0
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

// Potentiometer Variables
bool use_delay = false;
const int potentiometer = 18; //A0
unsigned long int delay_time = 0;
unsigned int total_time = 0;

// Creates two arrays for the delay. One for times, one for data
const int queue_length = 20;
unsigned long int time_received[queue_length];
I2cRxStruct data_received_queue[queue_length];
int queue_position = 0;

// Button Toggle Variables
const int buttonPin = 4;    // the number of the pushbutton pin
const int ledPin = 5;      // the number of the LED pin
int ledState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

I2cRxStruct data_received;

#include <Keyboard.h>
#include <Wire.h> // i2c
#include <FastLED.h>

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

  //Toggle Button Setup
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);

  Serial.println("Setup Complete!");
}

void loop() {


  // Allows for changing use_delay
  Button_Toggle();

  // Reads the potentiometer
  EVERY_N_MILLISECONDS(100) {
    delay_time = analogRead(potentiometer);  // Number Between 0 and 1024
  }

  // Delays the New Received Data by delay_time
  if (use_delay == true)
  {
    if ((time_received[0] + delay_time) < millis() and time_received[0] != 0)
    {
      // Sets the Received Data to first data in Queue
      data_received = data_received_queue[0];

      // Removes an element from the time and data queue FIFO
      for (int i = 0; i < queue_length - 2; i++)
      {
        time_received[i] = time_received[i + 1];
        data_received_queue[i] = data_received_queue[i + 1];
      }
      // Sets the last element as zero
      time_received[queue_length - 1] = 0;
      data_received_queue[queue_length - 1] = data_received_initial;
      queue_position--;
      // Set New Received Data to True so that the overlay will update
      newRxData = true;
    }
  }


  // Checks if a message has been received
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
      // Prints the Left Score
      if (data_received.Left_Score < 10) {
        Serial.print(' ');
        Serial.print(data_received.Left_Score, DEC);
      } else {
        Serial.print(data_received.Left_Score, DEC);
      }
      // Prints the Right Score
      if (data_received.Right_Score < 10) {
        Serial.print("  ");
        Serial.print(data_received.Right_Score, DEC);
      } else {
        Serial.print(' ');
        Serial.print(data_received.Right_Score, DEC);
      }
      Serial.print(' ');
      // Prints the Time
      Serial.print(data_received.Minutes_Remaining);
      Serial.print(':');
      if (data_received.Seconds_Remaining < 10) {
        Serial.print('0');
        Serial.print(data_received.Seconds_Remaining, DEC);
      } else {
        Serial.print(data_received.Seconds_Remaining, DEC);
      }
      // Prints the delay_time
      Serial.print(' ');
      if (use_delay == true) {
        Serial.print(delay_time);
      } else {
        Serial.print('0');
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
    if (use_delay == true)
    {
      time_received[queue_position] = millis();
      data_received_queue[queue_position] = data_received;
      queue_position++;
    } else {
      newRxData = true;
    }
  }
  else {
    // dump the data
    while (Wire.available() > 0) {
      byte c = Wire.read();
    }
  }
}
