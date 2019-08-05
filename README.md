# WonderSkates V2.0
#### NodeMCU powered Skate shoes that Track your workout and Uploads to the cloud on your routine Using Wolfram Cloud and Displays on the 8x8 Led Matrix and the 4 digit groove display.
_______________________________________________________________________________________________________________________


### Prerequisites
 \
ESP8266 board configurations and Libraries to your IDE: \
(https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/) \
 \
Wolfram Cloud Access: \
(https://www.wolframcloud.com) \
 \
Wolfram Mathematica 10 or Later: \
(http://www.wolfram.com/mathematica)
 
______________________________________________________________________________________________________________________

#### AP CLOUD Edition
This is Edition of the project can Export your workout details to your Wolfram Cloud and also display specific data to the LED Boards (__Current Revolutions Per Minute__ on the Groove 4 bit Display and Factor of the RPM calculated on the LED matrix: "1" for RPMs in range of 100 and so on)
 \
#### Server Edition (Non-Cloud Edition)
This Edition Does not perform the Cloud funtion but rather creates an AP and does all other functions \
(Goto the File "WonderSkatesV2 Server Edition" and clone it) 
______________________________________________________________________________________________________________________
#### Libraries Used
 \

LedControl (https://www.arduinolibraries.info/libraries/led-control) \
binary (Its Already in the Arduino IDE) \
TM1637Display (https://github.com/avishorp/TM1637) \
WiFiClient (https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/WiFiClient.h) \
ESP8266WiFi (https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi) \
ESP8266WebServer (https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/src/ESP8266WebServer.h) 

________________________________________________________________________________

Connections:
Signal Pin of IR sensor -> D0 (GPIO16) \
 \
CLK pin of Matrix 1 -> D6 (GPIO12)  \
CS pin of Matrix 1 -> D7 (GPIO13)   \
DIN pin of Matrix 1 -> D8 (GPIO15)  \
 \
CLK Groove 4 Digit Display -> D1 (GPIO05) \
DIO of Groove 4 Digit Display -> D2 (GPIO04) 
