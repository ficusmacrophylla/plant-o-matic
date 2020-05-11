//Plant-o-matic By TheTimeVoyager
//GPL v3.0 licensed
//version 0.1

int sensorPin = A0;
int ledPinGreen = 4;
int ledPinYellow = 5;
int ledPinRed = 6;
//int sensorCtrlPort =2;
int outputValue ;

void setup() {

   Serial.begin(9600);
   outputValue=0;
   pinMode(ledPinGreen, OUTPUT);
   pinMode(ledPinYellow, OUTPUT);
   pinMode(ledPinRed, OUTPUT);
   Serial.println("Reading From the Sensor ...");
   delay(2000);
   

   }

void loop() {
   //digitalWrite(sensorCtrlPort, HIGH);
   //delay(6000);
   outputValue= analogRead(sensorPin);
   //delay(2000);
   //digitalWrite(sensorCtrlPort, LOW);
   outputValue = map(outputValue,550,0,0,100);
   Serial.print("Mositure : ");
   outputValue= outputValue +22; //strange offset?!
   Serial.print(outputValue);
   Serial.println("%");
   if(outputValue < 30){
    digitalWrite(ledPinRed, HIGH);
    delay(300000); //5min
    digitalWrite(ledPinRed, LOW);
   }else if((outputValue >= 30) && (outputValue<80)){
    digitalWrite(ledPinYellow, HIGH);
    delay(300000); //5min
    digitalWrite(ledPinYellow, LOW);
   }else if(outputValue >= 80){
    digitalWrite(ledPinGreen, HIGH);
    delay(300000); //5min
    digitalWrite(ledPinGreen, LOW);
   }
   delay(3600000); //aspetta 1h

   }
