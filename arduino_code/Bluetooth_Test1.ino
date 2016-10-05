#include <SPI.h>
#include "Adafruit_BLE_UART.h"

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 4     //chip select
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Print echo demo"));

  // BTLEserial.setDeviceName("NEWNAME"); /* 7 characters max! */

  BTLEserial.begin();
}

aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;


void loop() {
  // put your main code here, to run repeatedly:
  lengths = getlength();
  blueintens = getintensity[lengths];
  cycletimes = gettimes[lengths];
  ///TAKEDATAHERE
  while(1) {
    if (sendbutton = 1) {
      senddata();
    }
  }
 
  

}









char gettimes[lengths] {
char c;
digitalWrite(4, LOW);
 
  
  // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();

  // Ask what is our current status
  aci_evt_opcode_t status = BTLEserial.getState();
  // If the status changed....
  if (status != laststatus) {
    // print it out!
    if (status == ACI_EVT_DEVICE_STARTED) {
        Serial.println(F("* Advertising started"));
    }
      if (status == ACI_EVT_CONNECTED) {
        // Lets see if there's any data for us!
        if (BTLEserial.available()) {
          Serial.print("* "); Serial.print(BTLEserial.available()); Serial.println(F(" bytes available from BTLE"));
        }
        // OK while we still have something to read, get a character and print it out
        while (BTLEserial.available()) {
          c = BTLEserial.read();
          Serial.print(c);
        }
       
      }

  }
      laststatus = status;
      return c;
}
