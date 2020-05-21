//Plant-o-matic By TheTimeVoyager
//GPL v3.0 licensed
//version 0.2
//checks terrain everi 12 hours and after delivers 10 seconds of water, startup wiring check

//input
int sensorPin = A0;
//output
int ledPinGreen = 4;
int ledPinYellow = 5;
int ledPinRed = 6;
int moistureValue = 0;
//control
int sensorCtrlPort =2;
int motorCtrlPort = 7;
//parameters
int timeBtwReadings = 43200000; //12h LEGENDA: 1h = 3 600 000 milliseconds
int blinkingTime = 300000; //5min
int wateringTime = 10000; //10seconds
//service
int watered = 0;
int wiring = 0;


int wiringCheck(){
   Serial.println("Checking Wiring");
   //powering
   digitalWrite(sensorCtrlPort, HIGH);
   digitalWrite(ledPinGreen, HIGH);
   digitalWrite(ledPinRed, HIGH);
   digitalWrite(ledPinYellow, HIGH);
   digitalWrite(motorCtrlPort, HIGH);
   delay(1000);
   readingMoisture();
   delay(1000);
   digitalWrite(motorCtrlPort, LOW);
   digitalWrite(ledPinGreen, LOW);
   digitalWrite(ledPinRed,LOW);
   digitalWrite(ledPinYellow,LOW);
   digitalWrite(sensorCtrlPort,LOW);
   Serial.println("Checked");
   return 1;
}

void readingMoisture(){
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

void signalStatus(int ledPin){
   digitalWrite(ledPin, HIGH);
   delay(blinkingTime);
   digitalWrite(ledPin, LOW);
}

void watering(){
   digitalWrite(motorCtrlPort, HIGH);
   delay(wateringTime);
   digitalWrite(motorCtrlPort, LOW);
   watered++;
}

void setup() {
   
   Serial.begin(9600);
   moistureValue=0;
   pinMode(ledPinGreen, OUTPUT);
   pinMode(ledPinYellow, OUTPUT);
   pinMode(ledPinRed, OUTPUT);
   pinMode(sensorCtrlPort, OUTPUT);
   pinMode(motorCtrlPort, OUTPUT);
   Serial.println("Reading From the Sensor ...");
   delay(2000);
   wiring = wiringCheck();
   if(wiring == 0 ){
      Serial.println("Bad Wiring");
   }

   }

void loop() {
   if(wiring){
      readingMoisture();
      if((moistureValue < 30)){
         signalStatus(ledPinRed);
         watering();
      }else if((moistureValue >= 30) && (moistureValue<80)){
         signalStatus(ledPinYellow);
      }else if(moistureValue >= 80){
         signalStatus(ledPinGreen);
      }
      delay(timeBtwReadings); //aspetta 
   }else{
      Serial.println("Wrong wiring or sensor disabled");
   }
    

}
