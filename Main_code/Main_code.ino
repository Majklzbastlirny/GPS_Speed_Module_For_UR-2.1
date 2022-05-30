//This code gets speed data from GPS and translates it to frequency
//Made by Michal Basler @Majklzbastlirny
//Created: 30.5.2022
//Codename: UR 4.20

//Libraries
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

//Software serial definition
#define TX 3
#define RX 4
SoftwareSerial swSerial(RX, TX);

//GPS
const int GPSBaud = 115200;
TinyGPSPlus gps;

//Output
#define Out1 1
#define Out2 2
#define Debug 13
#define DutyCycle 50 //Percent

//Remaining
float Speed = 0;
float Frequency = 0;
void setup() {
  pinMode(Out1, OUTPUT);
  pinMode(Out2, OUTPUT);
  pinMode(Debug, OUTPUT);

  //Start serial communication
  Serial.begin(115200);
  //Start communication with GPS module
  swSerial.begin(GPSBaud);






}

void loop() {
  // put your main code here, to run repeatedly:

}

void SpeedToFrequency(float SpeedFromGPS, int multiplier) {
  float freq;
  freq = (SpeedFromGPS * multiplier) * 11.9;
  return freq;
}


void Loading() {

}


//200 km/h  = 2380HZ
//1 km/h = 11,9 HZ
