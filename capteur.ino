#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;


void setup(void){
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(1,pipe);
radio.startListening();
pinMode(LED_BUILTIN, OUTPUT);}

void loop(void){
  delay(1000);
if (radio.available())
{
  bool done = false;
  while (!done){
    delay(500);
    done = radio.read(msg, 1);
    Serial.println(msg[0]);
    if (msg[0] == 111)
      {delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("OK");}
    else 
      {digitalWrite(LED_BUILTIN, LOW);}
    delay(500);
  }
}
    else
      {Serial.println("No radio available");}
}
