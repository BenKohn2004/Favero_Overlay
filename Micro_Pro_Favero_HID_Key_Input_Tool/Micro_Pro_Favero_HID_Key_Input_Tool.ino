// Arduino Leonardo

#include <Keyboard.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Starting!");

  Serial.println("Setup Complete!");
}

void loop() {

  Serial.println("Commencing Key Input...");

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F13);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F13);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F14);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F14);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F15);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F15);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F16);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F16);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F17);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F17);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F18);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F18);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F19);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F19);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F20);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F20);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F21);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F21);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F22);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F22);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F23);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F23);
  delay(1000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_F24);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_F24);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F13);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F13);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F14);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F14);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F15);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F15);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F16);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F16);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F17);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F17);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F18);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F18);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F19);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F19);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F20);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F20);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F21);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F21);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F22);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F22);
  delay(1000);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F23);
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_F23);
  delay(1000);

  Keyboard.press(KEY_RIGHT_CTRL);
  Keyboard.press(KEY_F24);
  Keyboard.release(KEY_RIGHT_CTRL);
  Keyboard.release(KEY_F24);
  delay(1000);

}
