#include <Arduino.h>
#include <SPI.h>

#define SR_CLK 2      // shift data
#define SR_LATCH 3    // storage register
#define SR_DATA 4     // data in
#define SR_CLEAR 5    // clear registers

byte data = 0b11001100;

SPISettings settings(1000000, MSBFIRST, SPI_MODE0);

void setup() {
  SPI.begin();
  pinMode(SR_LATCH, OUTPUT);

  
}

// the loop function runs over and over again forever
void loop() {
  for (int i; i < 256; i++) {
    SPI.beginTransaction(settings);
    SPI.transfer(i);
    SPI.endTransaction();

    digitalWrite(SR_LATCH, LOW);
    digitalWrite(SR_LATCH, HIGH);

    delay(50);
  }                    // wait for a second
}