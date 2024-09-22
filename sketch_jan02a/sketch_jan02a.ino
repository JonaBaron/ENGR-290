#include <Adafruit_SSD1331.h>
void setup() {
  // put your setup code here, to run once:
pinMode(7, OUTPUT);
pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(2)){
  
  digitalWrite(7,HIGH);
   delay(2000);
     digitalWrite(7,LOW);
  }


 
  

}
