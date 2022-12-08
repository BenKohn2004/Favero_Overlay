# Favero_Overlay

The Favero Full Arm scoring machines use serial data output that can be interpreted through an Arduino and then relayed to Open Broadcast Software (OBS) where the data is overlayed onto a live stream of the fencing.

This uses three Arduinos, two [Wemos D1 minis](https://www.amazon.com/Organizer-ESP8266-Internet-Development-Compatible/dp/B081PX9YFV/ref=sr_1_3?crid=3HISM104Q8NMO&keywords=wemos+d1+mini&qid=1636054524&qsid=133-6299387-8119633&sprefix=wemos%2Caps%2C400&sr=8-3&sres=B081PX9YFV%2CB08C7FYM5T%2CB08QZ2887K%2CB07W8ZQY62%2CB07RBNJLK4%2CB08FZ9YDGS%2CB07BK435ZW%2CB07V84VWSM%2CB07PF3NK12%2CB08H1YRN4M%2CB08FQYZX37%2CB073CQVFLK%2CB07VN328FS%2CB0899N647N%2CB07G9HZ5LM%2CB08MKLRSNH&srpt=SINGLE_BOARD_COMPUTER) and an [Arduino Pro Mini](https://www.amazon.com/HiLetgo-Atmega32U4-Bootloadered-Development-Microcontroller/dp/B01MTU9GOB/ref=sr_1_3?crid=3C3TLK308IDQC&keywords=arduino+micro+pro&qid=1636054557&qsid=133-6299387-8119633&sprefix=arduino+micro+pro%2Caps%2C146&sr=8-3&sres=B01MTU9GOB%2CB08BJNV1J3%2CB084KPT7MH%2CB08HCYL8RW%2CB012FOV17O%2CB07FXCTVQP%2CB08THVMQ46%2CB01HCXMBOU%2CB08H85MM9M%2CB09C5H78BP%2CB08DD2G9D8%2CB07Y88754S%2CB07J55YWKZ%2CB08D11Q94H%2CB07PHK8SMR%2CB07R9VWD39). The hardware is assembled as shown in the [schematic](https://github.com/BenKohn2004/Favero_Overlay/blob/main/Schematic_Favero_Overlay.pdf)

<h2>Libraries</h2>

The Libraries used for the Arduino are FastLED, ESPNOW, Wire.h, ESP8266WiFi. The libraries ESPNOW and Wire.h are included by default with the Arduino IDE.

<h2>Parsing and Transmitting the Favero Data</h2>

The MAC addresses for the Wemos can be found by loading and running [Wemos_ESPNOW_MacAddress](https://github.com/BenKohn2004/Favero_Overlay/tree/main/Wemos_ESPNOW_MacAddress).

The first Wemos is connected to the output port of the Favero machine and runs [Wemos_Favero_Serial_Parser_Rev_1]( https://github.com/BenKohn2004/Favero_Overlay/tree/main/Wemos_Favero_Serial_Parser) which retrieves and parses the data from the Favero. The Wemos then transmits the data via wifi to the Wemos running [Wemos_Favero_ESPNOW_Receiver](https://github.com/BenKohn2004/Favero_Overlay/tree/main/Wemos_Favero_ESPNOW_Receiver).

<h2>Receiving the Favero Data</h2>

The Wemos running Wemos_Favero_ESPNOW_Receiver, is connected by I2C to the Arduino Pro Mini which is running [Micro_Pro_Favero_HID](https://github.com/BenKohn2004/Favero_Overlay/tree/main/Micro_Pro_Favero_HID).

<h2>Displaying the Favero Data</h2>

The Pro Mini acts as a human input device, i.e. a Keyboard, and presses keys that correlate to the data received from the Favero. The keys are associated with Hotkey in OBS and toggle the visibility of the displays such as the Red/Green/White Lights as well as the grounding light and priority. The Keys chosen are similar to F13 through F24 with CTRL or ALT pressed. The [Micro_Pro_Favero_HID_Key_Input](https://github.com/BenKohn2004/Favero_Overlay/tree/main/Micro_Pro_Favero_HID_Key_Input_Tool) can be used to aid in inputting these keys as Hotkeys in OBS.

The Pro Mini also transmits serial data relating to the Time and Score. This is displayed using Putty. Putty is then displayed in OBS through a Window Capture Source using a Chroma Key filter.

In Putty, find the port that is listening to the Pro Mini and adjust the ‘Default Background’ color to Green (0,255,0). In OBS add a filter to the Putty Window Capture, by default the Green will be filtered out. Adjust text size as desired and then create duplicates in OBS and crop to fit in desired boxes. Alternatively, you can run the [putty-sessions.reg](https://github.com/BenKohn2004/Favero_Overlay/blob/main/putty-sessions.reg) to create a Favero Input session in Putty that will work.

The nameplastes are created using the [Lower Third](https://www.youtube.com/watch?v=pg_CwgwWmGA&t=660s&ab_channel=ScottFichter) plugin.

<h2>Adjusting OBS</h2>

Import [Favero_Overlay.json](https://github.com/BenKohn2004/Favero_Overlay/blob/main/Favero_Overlay.json) and link the image files for the lights.
Change the Fencing_Camera source to your camera. Check that the Putty Sources are referencing the window displaying Putty. I have found that it helps if Putty is fullscreen in the background. The OBS window should also be active for the hotkeys to be detected by OBS. Putty will appear blank until new data is received from the Favero Scorebox.

The hotkeys are assigned in the OBS Settings using [HID Key Input Tool](https://github.com/BenKohn2004/Favero_Overlay/tree/main/Micro_Pro_Favero_HID_Key_Input_Tool). The arduino program is loaded onto a Micro Pro and then the Micro Pro sends a new keystroke each second to the computer through a connected USB cord, which can be captured in the OBS Settings Hotkeys. This process can be a bit tedious and frustrating to get correct. [Here](https://github.com/BenKohn2004/Favero_Overlay/blob/main/HotKey%20Settings%20Screen%20Shot.jpg) is an example of how the hotkeys will look when assigned in OBS and shows the correlation between the hotkeys and the data sent from the Favero. The OBS screen has to be active for the hotkeys to toggle the visibility of the lights.

<h2>Using the Time Delay</h2>

Using a camera that has a lag such as a Real Time Streaming Protocol (RTSP) can be mitigated by adding in a delay to the data received by the Micro Pro Mini HID. This is done with the button and potentiometer. When the button is depressed, the Micro Pro Mini will read the [potentiometer](https://www.amazon.com/Swpeet-Potentiometer-Assortment-Multiturn-HighPrecision/dp/B07ZKK6T8S/ref=sr_1_2_sspa?crid=3EAID0WHGA32X&keywords=potentiometer&qid=1636919931&sprefix=potentiometer%2Caps%2C306&sr=8-2-spons&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyODdaRTdLOFRWWVA5JmVuY3J5cHRlZElkPUEwNjI0NDU2MlJCMU1FSDdaNloxTSZlbmNyeXB0ZWRBZElkPUEwMzU5MzAyMVdIODY3WDM3SzhUOSZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU&th=1) (a value from 0 to 1024) and delay the receipt of the received data by the potentiometer value in milliseconds. The Red LED will also light indicating when the delay is active and when it is not. The value of the delay is shown as the last value displayed on the Putty window.

I found this useful when using [iVcam](https://www.e2esoft.com/ivcam/), where a delay of 350 milliseconds allowed the data and video to nearly sync up. The potentiometer makes it possible to quickly adjust the delay without reloading data and the push button allows to easily change between cameras with little lag, such as webcams, and cameras with more lag.

Use of the Time Delay isn't necessary and the program will work as if there is no delay if the associated hardware (Button, Potentiometer and LED) is not hooked up to the Micro Pro Mini. I have found that when used with a USB [webcam](https://www.amazon.com/Logitech-C920x-Pro-HD-Webcam/dp/B085TFF7M1/ref=sxts_rp_s1_0?cv_ct_cx=c920&keywords=c920&pd_rd_i=B085TFF7M1&pd_rd_r=2dd28e3f-243d-4de9-848e-c2083a5fb0f5&pd_rd_w=9dGTY&pd_rd_wg=cu0PH&pf_rd_p=6dd352dd-2180-4fb8-a818-63c42d6c6824&pf_rd_r=1DHEZTJ848RZCG1NHBXK&psc=1&qid=1637070630&sr=1-1-5e1b2986-06e6-4004-a85e-73bfa3ee44fe), a delay is not needed to sync up the video and the lights.
