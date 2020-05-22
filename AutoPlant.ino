//Plant-o-matic By TheTimeVoyager
//GPL v3.0 licensed
//version 0.2
//checks terrain everi 12 hours and after delivers 10 seconds of water, startup wiring check

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PROGVERSION 0.2
#define GOOD 0
#define NORMAL 1
#define BAD 2
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
// #if (SSD1306_LCDHEIGHT != 32)
// #error("Height incorrect, please fix Adafruit_SSD1306.h!");
// #endif

//input
int sensorPin = A0;
//output
int ledPinGreen = 4;
int ledPinYellow = 5;
int ledPinRed = 6;

//control
int sensorCtrlPort =2;
int motorCtrlPort = 7;
//parameters
int timeBtwReadings = 43200000; //12h LEGENDA: 1h = 3 600 000 milliseconds
int blinkingTime = 300000; //5min
int wateringTime = 10000; //10seconds
int moistureValue = 0; //value of water percentage into the ground
//service
int watered = 0;
boolean wiring = false;
//interface
int checkingHour = timeBtwReadings / 360000;
int plantStatus = -1;

void stdDisplPrint(String s, boolean res){
   if (res)
      display.clearDisplay();
   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(0,15);
   display.println(s);
   display.display();
}

void mainDispView(){
   //128x32 size
   display.clearDisplay();
   display.setTextColor(WHITE);
   display.setTextSize(1);
   //line1
   display.setCursor(0,1); //(x,y)
   display.println("Plant-O-Matic");
   display.setCursor(93,1);
   display.println("V");
   display.setCursor(100,1);
   display.println(PROGVERSION);
   //line2
   display.setCursor(0,15);
   display.println("Moisture:");
   display.setCursor(60,15);
   display.println(moistureValue);
   
   // display.setCursor(6,1);
   // display.println("WaterTime (sec):");
   // display.setCursor(6,20);
   // display.println(wateringTime/1000);
   //line3
   display.setCursor(0,25);
   display.println("Status ");
   display.setCursor(40,25);
   if(plantStatus == GOOD)
      display.println(":)");
   else if(plantStatus == NORMAL)
      display.println(":|");
   else if(plantStatus == BAD)
      display.println(":(");
   else display.println("ND");

   display.setCursor(80,25);
   display.println("Freq:");
   display.setCursor(110,25);
   display.println(checkingHour);
   
   Serial.println("displaying");
   display.display();
}

boolean wiringCheck(){
   Serial.println("Checking Wiring");
   stdDisplPrint("Checking Wiring", true);
   //powering
   digitalWrite(sensorCtrlPort, HIGH);
   digitalWrite(motorCtrlPort, HIGH);
   delay(1000);
   readingMoisture();
   delay(1000);
   digitalWrite(motorCtrlPort, LOW);
   digitalWrite(sensorCtrlPort,LOW);
   Serial.println("Checked with value ");
   Serial.println(moistureValue);
   stdDisplPrint("Checked", true);
   if(moistureValue < 0)
      return false;
   return true;
}

void readingMoisture(){
   stdDisplPrint("Reading Moisture...", true);
   digitalWrite(sensorCtrlPort, HIGH);
   delay(10000); //necessary to let sensor have enough time to initialize.
   moistureValue= analogRead(sensorPin);
   digitalWrite(sensorCtrlPort, LOW);
   moistureValue = map(moistureValue,550,0,0,100);
   moistureValue = moistureValue +22; //strange offset?!
   Serial.print("Moisture : ");
   Serial.print(moistureValue);
   Serial.println("%");
}


void watering(){
   digitalWrite(motorCtrlPort, HIGH);
   delay(wateringTime);
   digitalWrite(motorCtrlPort, LOW);
   watered++;
}

void setup() {
   
   Serial.begin(9600);
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
   stdDisplPrint("Hello, starting...", true);
   moistureValue=0;
   pinMode(sensorCtrlPort, OUTPUT);
   pinMode(motorCtrlPort, OUTPUT);
   Serial.println("Reading From the Sensor CHECK...");
   delay(2000);
   wiring = wiringCheck();
   if(!wiring){
      Serial.println("Bad Wiring");
      stdDisplPrint("Bad Wiring", true);
   }

   }

void loop() {
   if(wiring){
      Serial.println("readfromLoop");
      readingMoisture();
      if((moistureValue < 30)){
         //signalStatus(ledPinRed);
         plantStatus=BAD;
         watering();
      }else if((moistureValue >= 30) && (moistureValue<80)){
         //signalStatus(ledPinYellow);
         plantStatus=NORMAL;
      }else if(moistureValue >= 80){
         //signalStatus(ledPinGreen);
         plantStatus=GOOD;
      }
      mainDispView();
      Serial.println("timer");
      delay(43200000); //aspetta 
      Serial.println("endtimer");
   }else{
      Serial.println("Wrong wiring or sensor disabled");
   }
    

}
