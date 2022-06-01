//This code gets speed data from GPS and translates it to frequency
//Made by Michal Basler @Majklzbastlirny
//Created: 30.5.2022
//Codename: UR 4.20

//Libraries
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>


//GPS
const int GPSBaud = 115200;
TinyGPSPlus gps;

//Software serial
const int RX = 4, TX = 5;
SoftwareSerial ss(RX, TX);


//Output
#define Out1 2
#define Debug 13
#define DutyCycle 128 //range 0-255

//Remaining
float Speed = 0;
float Frequency = 0;
unsigned long last = 0UL;
float counter = 0;


void setup() {
  pinMode(Out1, OUTPUT);

  //Start serial communication
  Serial.begin(GPSBaud);
  //Start communication with GPS module
  ss.begin(9600);
  ss.println("start");

}

void loop() {
  while (Serial.available() > 0)
    gps.encode(Serial.read());
   counter++;
  if (gps.speed.isUpdated()) {
    counter = 0;
    ss.println("");
    ss.print(gps.speed.age());
    ss.println(F("AGE"));
    ss.print(gps.speed.mps());
    ss.println(F(" m/s"));
    ss.print(gps.speed.kmph());
    ss.println(F(" km/h"));
    Frequency = (gps.speed.kmph() * 11.9);
    ss.print(Frequency);
    ss.println(" HZ");
    
    if (Frequency < 10) {
      digitalWrite(Out1, LOW);
    }
    else {
      //analogWrite(Out1, 0);
      analogWriteFreq(Frequency);
      analogWrite(Out1, DutyCycle);
    }
  }

  if (counter > 60) {
    analogWrite(Out1, 0);
    analogWriteFreq(counter);
    analogWrite(Out1, DutyCycle);
    if (counter > 2380) {
      counter = 6;}
    ss.println(counter);
  }
  delay(20);

  if (gps.charsProcessed() < 10)
    ss.println(F("WARNING: No GPS data.  Check wiring."));

  last = millis();
}




void Loading() {

}


//200 km/h  = 2380HZ
//8,4 km/h = 100 Hz
//1 km/h = 11,9 HZ
