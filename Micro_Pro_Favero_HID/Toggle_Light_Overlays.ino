void Toggle_Light_Overlays ()
{
  // Toggles the Green Light
  if (data_received.Green_Light != prev_Green_Light)
  { if (data_received.Green_Light == 1)
    { // Turns on Green Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F13);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F13);
    }
    if (data_received.Green_Light == 0)
    { // Hides Green Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F14);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F14);
    }
  }

  // Toggles the Red Light
  if (data_received.Red_Light != prev_Red_Light)
  { if (data_received.Red_Light == 1)
    { // Turns on Red Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F15);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F15);
    }
    if (data_received.Red_Light == 0)
    { // Hides Red Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F16);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F16);
    }
  }

  // Toggles the White Green Light
  if (data_received.White_Green_Light != prev_White_Green_Light)
  { if (data_received.White_Green_Light == 1)
    { // Turns on White Green Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F17);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F17);
    }
    if (data_received.White_Green_Light == 0)
    { // Hides White Green Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F18);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F18);
    }
  }

  // Toggles the White Red Light
  if (data_received.White_Red_Light != prev_White_Red_Light)
  { if (data_received.White_Red_Light == 1)
    { // Turns on White Red Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F19);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F19);
    }
    if (data_received.White_Red_Light == 0)
    { // Hides White Red Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F20);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F20);
    }
  }

  // Toggles the Yellow Green Light
  if (data_received.Yellow_Green_Light != prev_Yellow_Green_Light)
  { if (data_received.Yellow_Green_Light == 1)
    { // Turns on Yellow Green Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F21);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F21);
    }
    if (data_received.Yellow_Green_Light == 0)
    { // Hides Yellow Green Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F22);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F22);
    }
  }

  // Toggles the Yellow Red Light
  if (data_received.Yellow_Red_Light != prev_Yellow_Red_Light)
  { if (data_received.Yellow_Red_Light == 1)
    { // Turns on Yellow Red Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F23);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F23);
    }
    if (data_received.Yellow_Red_Light == 0)
    { // Hides Yellow Red Light Overlay
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_F24);
      Keyboard.release(KEY_LEFT_CTRL);
      Keyboard.release(KEY_F24);
    }
  }

  if (data_received.Yellow_Card_Green != prev_Yellow_Card_Green)
  {
    if (data_received.Yellow_Card_Green == 1)
    { // Turns on Yellow Card Green Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F13);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F13);

    }
    if (data_received.Yellow_Card_Green == 0)
    { // Hides Yellow Card Green Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F14);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F14);
    }
  }

  if (data_received.Yellow_Card_Red != prev_Yellow_Card_Red)
  {
    if (data_received.Yellow_Card_Red == 1)
    { // Turns on Yellow Card Red Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F15);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F15);
    }
    if (data_received.Yellow_Card_Red == 0)
    { // Hides Yellow Card Red Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F16);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F16);
    }
  }

  if (data_received.Red_Card_Green != prev_Red_Card_Green)
  {
    if (data_received.Red_Card_Green == 1)
    { // Turns on Red Card Green Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F17);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F17);
    }
    if (data_received.Red_Card_Green == 0)
    { // Hides Red Card Green Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F18);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F18);
    }
  }

  if (data_received.Red_Card_Red != prev_Red_Card_Red)
  {
    if (data_received.Red_Card_Red == 1)
    { // Turns on Red Card Red Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F19);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F19);
    }
    if (data_received.Red_Card_Red == 0)
    { // Hides Red Card Red Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F20);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F20);
    }
  }

  if (data_received.Priority_Left != prev_Priority_Left)
  {
    if (data_received.Priority_Left == 1)
    { // Turns on Priority Left Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F21);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F21);
    }
    if (data_received.Priority_Left == 0)
    { // Hides Priority Left Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F22);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F22);
    }
  }

  if (data_received.Priority_Right != prev_Priority_Right)
  {
    if (data_received.Priority_Right == 1)
    { // Turns on Priority Right Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F23);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F23);
    }
    if (data_received.Priority_Right == 0)
    { // Hides Priority Right Overlay
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F24);
      Keyboard.release(KEY_LEFT_ALT);
      Keyboard.release(KEY_F24);
    }
  }
}
