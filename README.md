# Favero_Overlay

The Favero Full Arm scoring machines use serial data output that can be interpreted through an Arduino and then relayed to Open Broadcast Software (OBS) where the data is overlayed onto a live stream of the fencing.

This uses three Arduinos, two Wemos D1 minis and an Arduino Pro Mini.

<h2>Parsing and Transmitting the Favero Data</h2>

The first Wemos is connected to the output port of the Favero machine and runs Wemos_Favero_Serial_Parser which retrieves and parses the data from the Favero. The Wemos then transmits the data via wifi to the Wemos running Wemos_Favero_ESPNOW_Receiver.

<h2>Receiving the Favero Data</h2>

The Wemos running Wemos_Favero_ESPNOW_Receiver, is connected by I2C to the Arduino Pro Mini which is running Micro_Pro_Favero_HID.

<h2>Displaying the Favero Data</h2>

The Pro Mini acts as a human input device, i.e. a Keyboard, and presses keys that correlate to the data received from the Favero. The keys are associated with Hotkey in OBS and toggle the visibility of the displays such as the Red/Green/White Lights as well as the grounding light and priority. The Keys chosen are similar to F13 through F24 with CTRL or ALT pressed. The Micro_Pro_Favero_HID_Key_Input can be used to aid in inputting these keys as Hotkeys in OBS.

The Pro Mini also transmits serial data relating to the Time and Score. This is displayed using Putty. Putty is then displayed in OBS through a Window Capture Source using a Chroma Key filter.

In Putty, find the port that is listening to the Pro Mini and adjust the ‘Default Background’ color to Green (0,255,0). Adjust text size as desired and then create duplicates in OBS and crop to fit in desired boxes. Alternatively, you can run the putty-sessions.reg to create a Favero Input session in Putty that will work.

<h2>Adjusting OBS</h2>

Import the OBS Profile Favero Overlay. Change the Fencing_Camera source to your camera and link the image files for the lights. Make sure the Putty sources are linked. I have found that Putty needs to be fullscreen in the background to properly work. The OBS window should also be active for the hotkeys to be detected by OBS.

