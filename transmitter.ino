#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
unsigned long Command = 123456;

void setup()
{
  Serial.begin(57600);
  Serial.println ("Radio begin");

  radio.begin();
  radio.setRetries (15,15);
  radio.setAutoAck (false);
  radio.setPALevel (RF24_PA_MAX);
  radio.openReadingPipe (1,pipes[1]);
  radio.startListening();
  radio.printDetails();
  radio.openWritingPipe (pipes[0]);
  radio.openReadingPipe (1,pipes[1]);
  radio.stopListening();
  Serial.println ("Started transmitter");
}

void loop(void)
{
  radio.stopListening();
  radio.write (&Command, sizeof(unsigned long));
  radio.startListening();
  delay (100);
}

