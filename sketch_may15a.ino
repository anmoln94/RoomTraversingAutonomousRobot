//Created by Anmol Nayak on 15 May 2016

//Libraries
#include <NewPing.h>
#include <VarSpeedServo.h>

//Pin Declarations
#define USTrigger 12
#define USEcho 7
#define MaxDistance 70
#define hUSTrigger 8
#define hUSEcho 13
#define hMaxDistance 50

unsigned int Time;
unsigned int hTime;
int motor1f = 6;
int motor1r = 11;
int motor2f = 10;
int motor2r = 5;
int distance,leftdis,rightdis,frontdist,hdistance,hdist;
int flag;
int fwd;
int analogpin = 4;
int val=0;
int metal;
int buzzerpin=2;

VarSpeedServo myservo;
NewPing sonar(USTrigger, USEcho, MaxDistance);
NewPing hsonar(hUSTrigger, hUSEcho, hMaxDistance);


void moveforward()
{
  analogWrite(motor1f,255); 
  analogWrite(motor1r,0);
  analogWrite(motor2f,255);
  analogWrite(motor2r,0); 
}

void moveleftwall()
{
  analogWrite(motor1f,0); 
  analogWrite(motor1r,210); 
  analogWrite(motor2f,0); 
  analogWrite(motor2r,0); 
  delay(900);
  for(int wall=0;wall<18000;wall++)
  {
      moveforward();
  }
  analogWrite(motor1f,0);
  analogWrite(motor1r,210);
  analogWrite(motor2f,0);
  analogWrite(motor2r,0);
  delay(900);
}

void moveright()
{
   analogWrite(motor1f,140); 
   analogWrite(motor1r,0);
   analogWrite(motor2f,0);
   analogWrite(motor2r,0); 
   delay(3000);
}

void moverightless()
{
   analogWrite(motor1f,140); 
   analogWrite(motor1r,0);
   analogWrite(motor2f,0);
   analogWrite(motor2r,0); 
   delay(1950);
}

void moverightfinal()
{
   analogWrite(motor1f,140); 
   analogWrite(motor1r,0);
   analogWrite(motor2f,0);
   analogWrite(motor2r,0); 
   delay(1450);
}

void moverightalter()
{
   analogWrite(motor1f,140); 
   analogWrite(motor1r,0);
   analogWrite(motor2f,0);
   analogWrite(motor2r,0);
}


void moveleft()
{
  analogWrite(motor1f,0);
  analogWrite(motor1r,210);
  analogWrite(motor2f,0); 
  analogWrite(motor2r,0);
  delay(850);
}

void moveleftlast()
{
  analogWrite(motor1f,0);
  analogWrite(motor1r,210);
  analogWrite(motor2f,0); 
  analogWrite(motor2r,0);
  delay(1000);
}
void moveleftalter()
{
  analogWrite(motor1f,0);
  analogWrite(motor1r,210);
  analogWrite(motor2f,0); 
  analogWrite(motor2r,0);
}

void movestopalter()
{
  analogWrite(motor1f,0);
  analogWrite(motor1r,0); 
  analogWrite(motor2f,0); 
  analogWrite(motor2r,0);
  delay(1000);
}
void movestop()
{
  analogWrite(motor1f,0);
  analogWrite(motor1r,0); 
  analogWrite(motor2f,0); 
  analogWrite(motor2r,0);
  delay(2000);
}



void setup() 
{
  flag=0;
  myservo.attach(9);
  pinMode(motor1f, OUTPUT);
  pinMode(motor1r, OUTPUT);
  pinMode(motor2f, OUTPUT);
  pinMode(motor2r, OUTPUT);
  pinMode(buzzerpin,OUTPUT);
  
}

long distcalc()                             //Ultrasonic sensor calculation
{
  Time = sonar.ping(); 
  distance = Time / US_ROUNDTRIP_CM;
  delay(100);
  return distance;
}

long hdistcalc()
{
  hTime = hsonar.ping(); 
  hdistance = hTime / US_ROUNDTRIP_CM;
  delay(100);
  return hdistance;
}


void rllr()                                 //Turns the robot in Right-Left-Left-Right orientation
{
  myservo.write(180,100,true);              // Moves servo to 180 degrees at a speed of 100
  moverightless(); 
  do
  {
    leftdis = distcalc();
    if(leftdis<20)
    {
      do
      {
        moverightalter();
        leftdis = distcalc();
      }while(leftdis==20);
    }
    else if(leftdis>20)
    {
      do
      {
        moveleftalter();
        leftdis = distcalc();
      }while(leftdis==20);
       }    
    else if(leftdis==20)
    {
      movestop();
  
    }
    moveforward();
    delay(250);
    movestopalter();
    
  }while(leftdis!=0);

    for(fwd=0;fwd<10000;fwd++)
  {
      moveforward();
  }

  moveleft();
  
  for(fwd=0;fwd<15000;fwd++)
  {
      moveforward();
  }

  movestop();

  moveleftalter();
  delay(100);
  do
  {
    leftdis = distcalc();
    if(leftdis<20)
    {
      do
      {
        moverightalter();
        leftdis = distcalc();
      }while(leftdis==20);
    }
    else if(leftdis>20)
    {
      do
      {
        moveleftalter();
        leftdis = distcalc();
      }while(leftdis==20);
      
    }
    else if(leftdis==20)
    {
      movestop();
  
    }
    moveforward();
    delay(250);
    movestopalter();
  }while(leftdis!=0);

  for(fwd=0;fwd<7250;fwd++)
  {
      moveforward();
  }

  moveleftlast();
  for(fwd=0;fwd<16000;fwd++)
  {
      moveforward();
  }
  
  do
  {
    leftdis = distcalc();
    if(leftdis<20)
    {
      do
      {
        moverightalter();
        leftdis = distcalc();
      }while(leftdis==20);
    }
    else if(leftdis>15)
    {
      do
      {
        moveleftalter();
        leftdis = distcalc();
      }while(leftdis==20);
      
    }
    else if(leftdis==20)
    {
      movestop();
  
    }    
    moveforward();
    delay(250);
    movestopalter();
  }while(leftdis!=0);
  movestop();
  moverightfinal();
}

void movestopmetal()                    //Robot stops for 2 seconds when a metal object is detected
{
  analogWrite(motor1f,0);
  analogWrite(motor1r,0); 
  analogWrite(motor2f,0); 
  analogWrite(motor2r,0);
  digitalWrite(buzzerpin,HIGH);
  delay(2000);  
}
void loop() 
{
  myservo.write(90,100,true); 
  frontdist = distcalc();
  if(frontdist > 25 || frontdist==0)      //Robot moves forward till no hindrance detected at 25 cm range
  {
    val  = analogRead(analogpin);
    if(val>500)
    {
      do
      {
        metal = 0;
        movestopmetal();
        digitalWrite(buzzerpin,LOW);
        metal++;
        moveforward();
        delay(1000);
      }while(metal==0);  
    }
    
    else
      moveforward();
  }
  else
  {
    movestop();
    hdist = hdistcalc();                  //If height sensor also detects a hindrance, means the hindrance is wall
    if(hdist!=0)
    {
      flag =!(flag);
      if(flag==1)
      {
        moveright();   
      }
      else
      {
        moveleftwall();
      } 
 
    }
    else                                  //If the hindrance is an obstacle
    {
      rllr();     
    }
  } 
}



