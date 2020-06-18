/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int RELAY_ENABLE=9;// Analog output pin that the RELAY is attached to
int sensorValue=0;
int flag = 0;        // flag for loop altenrating
float EMA_a = 0.1;      //initialization of EMA alpha
int EMA_S = 0;          //initialization of EMA S
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  pinMode(RELAY_ENABLE,OUTPUT);
  Serial.begin(115200);
  EMA_S = (float)analogRead(sensorValue);  //set EMA S for t=1
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  EMA_S = (EMA_a*sensorValue) + ((1-EMA_a)*EMA_S);    //run the EMA
 // Serial.println(EMA_S);                              //print digital value to serial
    


  // print the results to the Serial Monitor:
 
  Serial.print("\t output = ");
  Serial.println(outputValue);
  if (flag <1)
  {
    if(EMA_S > 120 && EMA_S <150)
    {
     //Serial.println("Relay ON");
     digitalWrite(RELAY_ENABLE,LOW);
     delay(100);
       flag= flag-1;
    }
  }
  else
  flag= flag+1;
  //Serial.println("Relay OFF");
  digitalWrite(RELAY_ENABLE,HIGH);
  delay(100);

  
}
