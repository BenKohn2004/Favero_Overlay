void Button_Toggle ()

// https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce

{

  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        // toggles the use of delay with the ledState
        if (ledState == HIGH)
        {
          use_delay = true;
          // Resets the Time Received Queue
          for (int i = 0; i < queue_length - 1; i++)
          {
            time_received[i] = 0;
          }
          queue_position = 0;
          newRxData = false;
        }
        else {
          use_delay = false;
          newRxData = false;
        }
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
