# Favero_Overlay

The Favero Full Arm scoring machines use serial data output that can be interpreted through an Arduino and then relayed to Open Broadcast Software (OBS) where the data is overlayed onto a live stream of the fencing.

This uses three Arduinos, two [Wemos D1 minis](https://www.amazon.com/Organizer-ESP8266-Internet-Development-Compatible/dp/B081PX9YFV/ref=sr_1_3?crid=3HISM104Q8NMO&keywords=wemos+d1+mini&qid=1636054524&qsid=133-6299387-8119633&sprefix=wemos%2Caps%2C400&sr=8-3&sres=B081PX9YFV%2CB08C7FYM5T%2CB08QZ2887K%2CB07W8ZQY62%2CB07RBNJLK4%2CB08FZ9YDGS%2CB07BK435ZW%2CB07V84VWSM%2CB07PF3NK12%2CB08H1YRN4M%2CB08FQYZX37%2CB073CQVFLK%2CB07VN328FS%2CB0899N647N%2CB07G9HZ5LM%2CB08MKLRSNH&srpt=SINGLE_BOARD_COMPUTER) and an [Arduino Pro Mini](https://www.amazon.com/HiLetgo-Atmega32U4-Bootloadered-Development-Microcontroller/dp/B01MTU9GOB/ref=sr_1_3?crid=3C3TLK308IDQC&keywords=arduino+micro+pro&qid=1636054557&qsid=133-6299387-8119633&sprefix=arduino+micro+pro%2Caps%2C146&sr=8-3&sres=B01MTU9GOB%2CB08BJNV1J3%2CB084KPT7MH%2CB08HCYL8RW%2CB012FOV17O%2CB07FXCTVQP%2CB08THVMQ46%2CB01HCXMBOU%2CB08H85MM9M%2CB09C5H78BP%2CB08DD2G9D8%2CB07Y88754S%2CB07J55YWKZ%2CB08D11Q94H%2CB07PHK8SMR%2CB07R9VWD39). The hardware is assembled as shown in the [schematic](https://github.com/BenKohn2004/Favero_Overlay/blob/main/Schematic_Favero_Overlay.pdf)

<h2>Parsing and Transmitting the Favero Data</h2>

The MAC addresses for the Wemos can be found by loading and running [Wemos_ESPNOW_MacAddress](https://github.com/BenKohn2004/Favero_Overlay/tree/main/Wemos_ESPNOW_MacAddress)

The first Wemos is connected to the output port of the Favero machine and runs [Wemos_Favero_Serial_Parser]( https://github.com/BenKohn2004/Favero_Overlay/tree/main/Wemos_Favero_Serial_Parser) which retrieves and parses the data from the Favero. The Wemos then transmits the data via wifi to the Wemos running [Wemos_Favero_ESPNOW_Receiver](https://github.com/BenKohn2004/Favero_Overlay/tree/main/Wemos_Favero_ESPNOW_Receiver).

<h2>Receiving the Favero Data</h2>

The Wemos running Wemos_Favero_ESPNOW_Receiver, is connected by I2C to the Arduino Pro Mini which is running [Micro_Pro_Favero_HID](https://github.com/BenKohn2004/Favero_Overlay/tree/main/Micro_Pro_Favero_HID).

<h2>Displaying the Favero Data</h2>

The Pro Mini acts as a human input device, i.e. a Keyboard, and presses keys that correlate to the data received from the Favero. The keys are associated with Hotkey in OBS and toggle the visibility of the displays such as the Red/Green/White Lights as well as the grounding light and priority. The Keys chosen are similar to F13 through F24 with CTRL or ALT pressed. The [Micro_Pro_Favero_HID_Key_Input](https://github.com/BenKohn2004/Favero_Overlay/tree/main/Micro_Pro_Favero_HID_Key_Input_Tool) can be used to aid in inputting these keys as Hotkeys in OBS.

The Pro Mini also transmits serial data relating to the Time and Score. This is displayed using Putty. Putty is then displayed in OBS through a Window Capture Source using a Chroma Key filter.

In Putty, find the port that is listening to the Pro Mini and adjust the ‘Default Background’ color to Green (0,255,0). Adjust text size as desired and then create duplicates in OBS and crop to fit in desired boxes. Alternatively, you can run the [putty-sessions.reg](https://github.com/BenKohn2004/Favero_Overlay/blob/main/putty-sessions.reg) to create a Favero Input session in Putty that will work.

The nameplastes are created using the [Lower Third](https://www.youtube.com/watch?v=pg_CwgwWmGA&t=660s&ab_channel=ScottFichter) plugin.

<h2>Adjusting OBS</h2>

Import [Favero_Overlay_Scenes.json]()
Change the Fencing_Camera source to your camera and link the image files for the lights. Make sure the Putty sources are linked. I have found that it helps if Putty is fullscreen in the background. The OBS window should also be active for the hotkeys to be detected by OBS. The hotkeys are assigned in settings using [HID Key Input Tool](https://github.com/BenKohn2004/Favero_Overlay/tree/main/Micro_Pro_Favero_HID_Key_Input_Tool). Program is loaded onto a Micro Pro and then sends a new keystroke each second to the computer, which can be captured in the OBS Settings Hotkeys. [Here](https://github.com/BenKohn2004/Favero_Overlay/blob/main/HotKey%20Settings%20Screen%20Shot.JPG) is an example of how the hotkeys will look when assigned in OBS.

