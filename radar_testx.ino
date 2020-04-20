#include <LiquidCrystal.h>



//#include"serial.h"

void setup() {

pinMode(PH6,INPUT);
pinMode(3,INPUT);
pinMode(PE2,INPUT);
}
void loop()
{
    int X;
 Serial.begin(4800);
  Serial.print("0"); 
  //x=digitalRead(3);
 // Serial.print(x=analogRead(PH6));
  //Serial.print(digitalRead(3));
  Serial.print(X=analogRead(3));
  
  Serial.println(",2500");
  delay(10);
  if(X==168)
  digitalWrite (13,HIGH);
  //digitalWrite (3,HIGH);
  
  
    
  
}
