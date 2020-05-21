//Plant-o-matic By TheTimeVoyager
//GPL v3.0 licensed
//version 0.1

//input
int sensorPin = A0;
//output
int ledPinGreen = 4;
int ledPinYellow = 5;
int ledPinRed = 6;
int outputValue = 0;
//control
int sensorCtrlPort =2;
int motorCtrlPort = 1;
//service
int blinkingTime = 300000; //5min
int watered = 0;
int timeBtwReadings = 43200000; //12h LEGENDA: 1h = 3 600 000 milliseconds
int wiring = 0;

int wiringCheck(){
   Serial.println("Checking Wiring");
   digitalWrite(sensorCtrlPort, HIGH );
   delay(2000);
   digitalWrite(ledPinGreen, HIGH);
   digitalWrite(ledPinRed, HIGH);
   digitalWrite(ledPinYellow, HIGH);
   digitalWrite(motorCtrlPort, HIGH);
   delay(1000);
   digitalWrite(sensorCtrlPort, HIGH);
   delay(2000);
   digitalWrite(ledPinGreen, LOW);
   digitalWrite(ledPinRed,LOW);
   digitalWrite(ledPinYellow,LOW);
   digitalWrite(motorCtrlPort,LOW);
   delay(1000);
   digitalWrite(sensorCtrlPort, LOW);
   return 1;
}

void readingMoisture(){
   digitalWrite(sensorCtrlPort, HIGH);
   delay(10000); //necessary to let sensor have enough time to initialize.
   outputValue= analogRead(sensorPin);
   digitalWrite(sensorCtrlPort, LOW);
   outputValue = map(outputValue,550,0,0,100);
   outputValue= outputValue +22; //strange offset?!
   Serial.print("Moisture : ");
   Serial.print(outputValue);
   Serial.println("%");
}

void signalStatus(int ledPin){
   digitalWrite(ledPin, HIGH);
   delay(blinkingTime);
   digitalWrite(ledPin, LOW);
}

void watering(){
   digitalWrite(motorCtrlPort, HIGH);
   delay(5000);
   digitalWrite(motorCtrlPort, LOW);
   watered++;
}

void setup() {
   
   Serial.begin(9600);
   outputValue=0;
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
      readingMoisture();
      if((outputValue < 30)){
         signalStatus(ledPinRed);
         watering();
      }else if((outputValue >= 30) && (outputValue<80)){
         signalStatus(ledPinYellow);
      }else if(outputValue >= 80){
         signalStatus(ledPinGreen);
      }
      delay(timeBtwReadings); //aspetta 12h
    

}
