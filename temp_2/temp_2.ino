#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 3
/*
This sketch sends a string to a corresponding Arduino
with nrf24 attached.  It appends a specific value 
(2 in this case) to the end to signify the end of the
message.
*/

int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int loo = 0; //0 read the information from the temperature
int temperature;
void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);}
////////////////////////////////////////////
void loop(void){    
  if (loo == 0){
    loo = 1;
    int chk = DHT.read11(DHT11_PIN);
    Serial.print("Temperature = ");
    Serial.println(DHT.temperature);
    temperature = DHT.temperature;
    delay(1000);
  }
  else{
    loo = 0;
    String theMessage = "";
    int messageSize = theMessage.length();
    for (int i = 0; i < messageSize; i++) {
      int charToSend[1];
      charToSend[0] = theMessage.charAt(i);
      radio.write(charToSend,1);
    }
      msg[0] = temperature;  
      radio.write(msg,1);  
      radio.powerDown(); 
      delay(1000);
      radio.powerUp();
  }
}
