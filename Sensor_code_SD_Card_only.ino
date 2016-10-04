#include <SPI.h>
#include <SD.h>
File dataFile;
int lightPin0 = 0;//define a pin for Photo resistor
int lightPin1 = 1;
int lightPin2 = 2;
int lightPin3 = 3;
int Rled0 = 9;
int Rled1 = 6;
int Rled2 = 4;
int Rled3 = 2;
int Bled0 = 7;
int Bled1 = 5;
int Bled2 = 3;
int Bled3 = 10;
int Tr0=0; //percent transmission
int Tr1=0;
int Tr2=0;
int Tr3=0;
int off=0;
int j = 0;
const int chipSelect = 8;
String Filename = "lilly.txt"; //whatever you want the file containing all the data from the run to be called NO CAPITALS!!!!!!
#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  pinMode(Rled0, OUTPUT);
  pinMode(Rled1, OUTPUT);
  pinMode(Rled2, OUTPUT);
  pinMode(Rled3, OUTPUT);
  
  pinMode(Bled0, OUTPUT);
  pinMode(Bled1, OUTPUT);
  pinMode(Bled2, OUTPUT);
  pinMode(Bled3, OUTPUT);

    if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
    }
}

int BlueIntens[] = {0,2500,10,2500}; // Intensity out of 3000
int CycleTimes[] = {120,120,120,120}; // Times depends on the duration set in blueon below. default - minutes
int Cycles = sizeof(CycleTimes)/sizeof(CycleTimes[0]);

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i <=Cycles; i++){ // number of different light intensities
    for (int z=0; z <=CycleTimes[i]; z++){ // number of minutes at the chosen intensity
      blueon(BlueIntens[i], 20000); // blueon(intesity, duration) duration 20000 = 60 seconds
      measure();
     }
   }
 }



 
void blueon(int intensity, int duration) {
        j = 0;
        while (j <=duration)  { 
        if (intensity>0)
        {
        digitalWrite(Bled0, HIGH);
        digitalWrite(Bled1, HIGH);
        digitalWrite(Bled2, HIGH);
        digitalWrite(Bled3, HIGH);
        delayMicroseconds(intensity); // Approximately .05% duty cycle @ 1KHz
        digitalWrite(Bled0, LOW);
        digitalWrite(Bled1, LOW);
        digitalWrite(Bled2, LOW);
        digitalWrite(Bled3, LOW);
        delayMicroseconds(3000-intensity);
        }
                else
        {
          digitalWrite(Bled0, LOW);
          digitalWrite(Bled1, LOW);
          digitalWrite(Bled2, LOW);
          digitalWrite(Bled3, LOW);
          delayMicroseconds(3000);
        }
        j=j+1;
    }
}

void measure() {
  if (digitalRead(Bled0) == 1) {
      digitalWrite(Bled0, LOW);
      digitalWrite(Bled1, LOW);
      digitalWrite(Bled2, LOW);
      digitalWrite(Bled3, LOW);
      }
      delay(90);
      digitalWrite(Rled0, HIGH);
      digitalWrite(Rled1, HIGH);
      digitalWrite(Rled2, HIGH);
      digitalWrite(Rled3, HIGH);
      delayMicroseconds(100);
      Tr0=analogRead(lightPin0);
      Tr1=analogRead(lightPin1);
      Tr2=analogRead(lightPin2);
      Tr3=analogRead(lightPin3);
      digitalWrite(Rled0, LOW);
      digitalWrite(Rled1, LOW);
      digitalWrite(Rled2, LOW);
      digitalWrite(Rled3, LOW);
      dataFile = SD.open(Filename, FILE_WRITE);
      dataFile.print(float(millis())/float(60000));
      dataFile.print(',');
      dataFile.print(Tr0);
      dataFile.print(',');
      dataFile.print(Tr1);
      dataFile.print(',');
      dataFile.print(Tr2);
      dataFile.print(',');
      dataFile.println(Tr3);
      dataFile.close();
      Serial.print("done");
}