#include <Shieldbot.h>
#include "Ultrasonic.h"

#define Range   10   // cm
#define Delayms 200   
#define Sensor6      2
Shieldbot shieldbot = Shieldbot();
Ultrasonic ultrasonicRight(5);
Ultrasonic ultrasonicLeft(6);
unsigned char Status;
unsigned char s1,s2,s3,s4,s5,s6;
uint8_t OutDeskFlag = 0;
int RangeInCentimetersLeft;
int RangeInCentimetersRight;
void setup(){
  Serial.begin(9600);
  shieldbot.setMaxSpeed(255);//255 is max
  pinMode(2,INPUT);
  Status = 0;
}

void loop(){
  //leftSquare();  
  //leftCircle();
  //infinity();

  switch(Status){
  case 0:
  if((RangeInCentimetersRight > Range) || (RangeInCentimetersLeft > Range)) {
    turnBack();
    OutDeskFlag = 1;
    turnLeft();
  }else if((OutDeskFlag == 1) && (RangeInCentimetersRight <= Range && RangeInCentimetersLeft <= Range)) {
    OutDeskFlag = 0;
    turnBack();
    turnLeft();
  } else if ((s1*s2*s3*s4*s5) == 0){
    Status  = 1;
  } else {
    leftCircle(8);
  }
  break;
  case 1:
  s6 = digitalRead(Sensor6);
  if((s1*s2 == 0) && (s5 ==1)) {
    turnRight();
    turnForward();
  }
  if((s4*s5 == 0) && (s1 == 1)) {
    turnLeft();
    turnForward();
  }
  if((s1 == 0)&&(s2==0)&&(s3==0)&&(s4==0)&&(s5==0) &&(s6 == 0)) {
    shieldbot.drive(30,30);   //turn left on a dime
  } 
  if((s1 == 0)&&(s2==0)&&(s3==0)&&(s4==0)&&(s5==0) &&(s6 == 1)) {
    shieldbot.stop();
  }
  
  if((s1*s2*s3*s4*s5 == 1) && (s6 == 1)){
    shieldbot.stop();
    delay(1000);
    turnBack();
    turnBack();
    shieldbot.stop();
  }
  if((s1*s2*s3*s4*s5 == 1) && (s6 == 0)){
    Status = 0;
  }
  break;
  case 2:  
  break;
  default:
  break;
  
  
  }
  RangeInCentimetersRight = ultrasonicRight.MeasureInCentimeters(); // two measurements should keep an interval
 
  Serial.println(" Right");
  Serial.print(RangeInCentimetersRight);//0~400cm
  
  RangeInCentimetersLeft = ultrasonicLeft.MeasureInCentimeters(); // two measurements should keep an interval
  
  Serial.println(" Left");
  Serial.print(RangeInCentimetersLeft);//0~400cm
  
  s1 = shieldbot.readS1();
  s2 = shieldbot.readS2();
  s3 = shieldbot.readS3();
  s4 = shieldbot.readS4();
  s5 = shieldbot.readS5();
  
//  Serial.print("s1");
//  Serial.println(s1);
//  
//  Serial.print("s2");
//  Serial.println(s2);
//  
//  Serial.print("s3");
//  Serial.println(s3);
//  
//  Serial.print("s4");
//  Serial.println(s4);
//  
//  Serial.print("s5");
//  Serial.println(s5);
//  delay(1000);
  
 /* 
  turnLeft();
  delay(5000);
  turnRight();
  delay(5000); 
  */
  
  
}
void turnLeft()
{  
  shieldbot.drive(-100,100);   //turn left on a dime
  delay(Delayms);
  shieldbot.stop();
}

void turnRight()
{
  shieldbot.drive(100,-100);   //turn left on a dime
  delay(Delayms);
  shieldbot.stop();
}
void turnBack()
{
  shieldbot.drive(-50,-80);
  delay(100);
}
/*
void infinity()
{
  leftCircle();
  delay(4800);
  rightCircle();
  delay(4800);
}
*/
void leftCircle(unsigned char radius)
{
  shieldbot.drive(80,127);
}

void turnForward()
{
  shieldbot.forward();
  delay(Delayms);
}







