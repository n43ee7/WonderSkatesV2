/*
WonderSkates V2.0S (ESP Server Edition)
By Nabeel Ur Rehman Nayyar
https://github.com/n43ee7/WonderSkatesV2

[!] Mark or change the AP details from Line 61 and 62 and Connect it
[>] Connect the Local IP of the Server for getting Detailed Data.
[>] All serial Messages are for Debgging and can be deleted from the Code

*/
#include <LedControl.h> 
#include <TM1637Display.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <time.h>

//Matrix Phases
byte zero[8] = { B00000000,B01111110,B01000010,B01000010,B01000010,B01000010,B01111110,B00000000 };
byte one[8] = { B00011000,B00111000,B01011000,B00011000,B00011000,B00011000,B00011000,B01111110 };
byte two[8] = { B01111110,B01111110,B00000010,B01111110,B01111110,B01000000,B01111110,B01111110 };
byte three[8] = { B01111110,B01111110,B00000010,B01111110,B01111110,B00000010,B01111110,B01111110 };
byte four[8] = { B01100110,B01100110,B01100110,B01111110,B01111110,B00000110,B00000110,B00000110 };
byte five[8] = { B01111110,B01111110,B01000000,B01111110,B01111110,B00000010,B01111110,B01111110 };
byte six[8] = { B01111110,B01111110,B01000000,B01111110,B01111110,B01000010,B01111110,B01111110 };
byte seven[8] = { B01111110,B01111110,B00000110,B00000110,B00000110,B00000110,B00000110,B00000110 };
byte eight[8] = { B01111110,B01111110,B01000010,B01111110,B01111110,B01000010,B01111110,B01111110 };
byte nine[8] = { B01111110,B01111110,B01100110,B01100110,B01111110,B00000110,B00000110,B00000110 };
byte ten[8] = { B11001111,B11001001,B11001001,B11001001,B11001001,B11001001,B11001001,B11001111 };
byte eleven[8] = { B11000011,B11000011,B11000011,B11000011,B11000011,B11000011,B11000011,B11000011 };
byte twelve[8] = { B11001111,B11001001,B11001001,B11000001,B11001111,B11001000,B11001000,B11001111 };
byte thirteen[8] = { B11001111,B11001001,B11001001,B11000001,B11001111,B11000001,B11001001,B11001111 };

byte greaterPRIM[8] = { B01000010,B11000011,B00100100,B00011000,B00011000,B00100100,B11000011,B01000010 };
byte greaterSEC[8] = { B00000000,B00000000,B00100100,B00011000,B00011000,B00100100,B00000000,B00000000 };

byte WifiAnim1[] = { B00000000,B00000000,B00000000,B00000000,B01111110,B01000010,B01011010,B00000000 };
byte WifiAnim2[] = { B00000000,B00000000,B00000000,B11111111,B10000001,B10000001,B10011001,B00000000 };

//IR Sensor and Other related elements
const int dataIN = 16;  //D0 -> GPIO16
unsigned long prevmillis;
unsigned long duration;
int rpm;
bool currentstate;
bool prevstate;
float WheelDiameter = 0.063; //Wheel Diameter of the Wheels (NORMALLY BETWEEN 62-65mm)(INPUT IN Meter)
float linearSpeed;
unsigned long timea = 0;
unsigned long curTime = 0;
float distance = 0;

//Matrix 
int CLK = 12; //D6 -> GPIO12
int CS = 13;  //D7 -> GPIO13
int DIN = 15; //D8 -> GPIO15

//Grove
int Dclk = 5; //D1 -> GPIO05
int Ddio = 4; //D2 -> GPIO04

//Wireless Configurations
const char* ssid = "N43EE7 Skates MK.2";  // The SSID
const char* password = "12345678";  //The Password
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
ESP8266WebServer server(80);
String page = "";


//_________________inits______________________
LedControl lft = LedControl(DIN, CLK, CS, 1);
TM1637Display Disp(Dclk, Ddio);

void setup()
{
    pinMode(dataIN, INPUT);
    prevmillis = 0;
    prevstate = LOW;

    //Matrix Configurations
    Disp.setBrightness(0x0a);
    lft.shutdown(0, false);
    lft.setIntensity(0, 8);
    lft.clearDisplay(0);
    Serial.begin(9600);

    //Wifi AP & Server Configurations
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);

    Serial.println("AP#SSID: " + String(ssid) + "| AP#Password: " + String(password)); //DBGB
    Serial.println("AP#IP: 192.168.1.1 | AP#Gateway: 192.168.1.1"); //DBGB
    for (int a = 0; a < 4; a = a + 1) {
        delay(500);
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, WifiAnim1[a]);
        }
        delay(1000);
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, WifiAnim1[a]);
        }
        delay(100);
    }
}
void loop()
{
    timea = millis();
    currentstate = digitalRead(dataIN);
    if (prevstate != currentstate)
    {
        if (currentstate == HIGH)
        {
            duration = (micros() - prevmillis);
            rpm = (60000000 / duration);
            prevmillis = micros();
        }
    }
    prevstate = currentstate;
    Serial.println(rpm); //DBGB
    server.handleClient();
    DeltaDisp(rpm);
    MatrixDisplay(rpm);
    DataExport(rpm);
    server.begin();
    Serial.println("Web server started!"); //DBGB
}

//Groove Display
int DeltaDisp(int RPM) {

    Disp.showNumberDec(RPM);
    delay(50);
}

//Matrix Display 
int MatrixDisplay(int RPM) {

    if (rpm <= 100) {
        if (rpm = 0) {
            for (int a = 0; a < 8; a = a + 1)
            {
                lft.setRow(0, a, zero[a]);
            }
        }
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, one[a]);
        }
    }
    if (rpm >= 200) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, two[a]);
        }
    }
    if (rpm >= 300) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, three[a]);
        }
    }
    if (rpm >= 400) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, four[a]);
        }
    }
    if (rpm >= 500) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, five[a]);
        }
    }
    if (rpm >= 600) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, six[a]);
        }
    }
    if (rpm >= 700) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, seven[a]);
        }
    }
    if (rpm >= 800) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, eight[a]);
        }
    }
    if (rpm >= 900) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, nine[a]);
        }
    }
    if (rpm >= 1000) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, ten[a]);
        }
    }
    if (rpm >= 1100) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, eleven[a]);
        }
    }
    if (rpm >= 1200) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, twelve[a]);
        }
    }
    if (rpm >= 1300) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, thirteen[a]);
        }
    }
    if (rpm >= 1400) {
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, greaterPRIM[a]);
            DeltaDisp(rpm);
        }
        delay(100);
        for (int a = 0; a < 8; a = a + 1)
        {
            lft.setRow(0, a, greaterSEC[a]);
        }
    }

}

//Exporting Results
int DataExport(int RPM) {

    linearSpeed = (WheelDiameter / 2) * RPM * 0.10472; //LinearSpeed in m/s
    linearSpeed = linearSpeed * 3.6; //Comment this line to get final value in m/s instead of km/h

    curTime = timea;
    distance = (linearSpeed * curTime) / 1000;

    server.on("/", []() {
        page = "<h1 style = ""text-align: center;""><strong><span style = ""text-decoration: underline;"">N43EE7</span> Skates MK.2</strong></h1><p><strong>Current RPM : " + String(rpm) + " </strong></p><p><strong>Current Speed : " + String(linearSpeed) + " </strong></p><p><strong>Total Distance Traveled : " + String(distance) + " </strong></p><p><strong>Total Average Speed : &nbsp; </strong></p><p><strong>Total Workout time : " + String(curTime) + "</strong></p>";
        server.send(200, "text/html", page);
    });
}

