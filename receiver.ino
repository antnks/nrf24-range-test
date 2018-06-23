#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);

const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};
typedef enum {role_ping_out = 1, role_pong_back} role_e;
const char* role_friendly_name[] = {"invalid", "Ping out", "Pong back"};
role_e role = role_pong_back;

void setup(void)
{
  Serial.begin (57600);
  Serial.println ("Radio begin");

  radio.begin();
  radio.setRetries (15, 15);
  radio.setAutoAck (false);
  radio.setPALevel (RF24_PA_MAX);
  radio.openReadingPipe (1, pipes[1]);
  radio.startListening();
  radio.printDetails();
  radio.openWritingPipe (pipes[1]);
  radio.openReadingPipe (1,pipes[0]);
  radio.startListening();
  Serial.println ("Started receiver");

  pinMode (5, OUTPUT);
  tone (5, 1000);
  delay (500);
  noTone (5);
}

void loop(void)
{
  if (radio.available())
  {
    unsigned long data = 0;
    radio.read (&data, sizeof(unsigned long));
    if (data == 123456)
    {
      Serial.println (data);
      tone (5, 1000);
      delay (10);
      noTone (5);
      delay (100);
    }
  }
}

