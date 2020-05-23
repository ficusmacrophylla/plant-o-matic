//Plant-o-matic, TOPSOILER By TheTimeVoyager
//GPL v3.0 licensed
//version 0.2
//checks terrain every CHECKINGHOURS hours and after delivers 10 seconds of water, startup with wiring check, 

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DEBUG
#define PROGVERSION 0.2
#define GOOD 0
#define NORMAL 1
#define BAD 2
#define OLED_RESET 4
#define CHECKINGHOURS 4 //number of hours between checks
#define ONEHOUR 3600000 //placeholder for one hour in millisecond  //12h LEGENDA: 1h = 3 600 000 milliseconds
Adafruit_SSD1306 display(OLED_RESET);
// #if (SSD1306_LCDHEIGHT != 32)
// #error("Height incorrect, please fix Adafruit_SSD1306.h!");
// #endif

//input
int sensorPin = A0;
//output

//control
int sensorCtrlPort =2;
int motorCtrlPort = 7;
//parameters
int wateringTime = 10000; //10seconds
int moistureValue = 0; //value of water percentage into the ground
int moistureOld[2] = {-1,-1}; //old values
//service
int watered = 0;
boolean wiring = false;
//interface
int remainingTimeHrs = CHECKINGHOURS;
int plantStatus = -1;


/*---UTILITY FUNCTIONS---*/
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
   display.println("TOPSOILER");
   display.setCursor(93,1);
   display.println("V");
   display.setCursor(100,1);
   display.println(PROGVERSION);
   //line2
   display.setCursor(0,15);
   display.println("Moisture:");
   display.setCursor(60,15);
   display.println(moistureValue);
   display.setCursor(85,15);
   display.println(moistureOld[0]);
   display.setCursor(110,15);
   display.println(moistureOld[1]);
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
   display.println(remainingTimeHrs);
   
   #ifdef DEBUG
   Serial.println("displaying MainView");
   #endif
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
   stdDisplPrint("Checked", true);
   #ifdef DEBUG
   Serial.println("Checked with value ");
   Serial.println(moistureValue);
   #endif
   if(moistureValue < 0)
      return false;
   return true;
}

void readingMoisture(){
   stdDisplPrint("Reading Moisture...", true);
   moistureOld[1] = moistureOld[0];
   moistureOld[0] = moistureValue;
   digitalWrite(sensorCtrlPort, HIGH);
   delay(10000); //necessary to let sensor have enough time to initialize.
   moistureValue= analogRead(sensorPin);
   digitalWrite(sensorCtrlPort, LOW);
   moistureValue = map(moistureValue,550,0,0,100);
   //moistureValue = moistureValue +22; //strange offset?!

   #ifdef DEBUG
   Serial.print("Moisture : ");
   Serial.print(moistureValue);
   Serial.print(" ");
   Serial.print(moistureOld[0]);
   Serial.print(" ");
   Serial.print(moistureOld[1]);
   Serial.println(" %");
   #endif
}

void watering(){
   stdDisplPrint("Watering...", true);
   digitalWrite(motorCtrlPort, HIGH);
   delay(wateringTime);
   digitalWrite(motorCtrlPort, LOW);
   watered++;
}

void timer(int hours){
   // Serial.println("timer");
   // Serial.println(remainingTimeHrs);
   // Serial.println("hrs");
   remainingTimeHrs = hours;
   while(remainingTimeHrs!=0){
      delay(ONEHOUR); //1h 
      //delay(15000); //15sec 
      remainingTimeHrs--;
      mainDispView();
   } 
   Serial.println("endtimer");
}

/*---SETUP AND LOOP---*/

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
         plantStatus=BAD;
         watering();
      }else if((moistureValue >= 30) && (moistureValue<80)){
         plantStatus=NORMAL;
         watering();
      }else if(moistureValue >= 80){
         //signalStatus(ledPinGreen);
         plantStatus=GOOD;
      }
      mainDispView();
      timer(CHECKINGHOURS);
      
   }else{
      Serial.println("Wrong wiring or sensor disabled");
   }
    

}
