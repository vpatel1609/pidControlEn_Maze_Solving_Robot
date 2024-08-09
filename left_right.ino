#define lm1 16
#define lm2 27
#define rm1 12
#define rm2 13
#include "Wire.h"
#include <MPU6050_light.h>
MPU6050 mpu(Wire);
float spt,sp,cp,pe = 0,er;//forward :::: sp = centre point  cp = current position  er = error  pe = previous error
float p = 0.5,i = 0,d = 0;//PID turns //5.5 0 0.5  //L 0.85 0 1
int pwr,pwl,base = 120;
void setup() 
{  pinMode(14,OUTPUT);
  digitalWrite(14,LOW);
  delay(1000);
  ledcSetup(0,250,8);  ledcAttachPin(rm1,0);
  ledcSetup(1,250,8);  ledcAttachPin(rm2,1);
  ledcSetup(2,250,8);  ledcAttachPin(lm1,2);
  ledcSetup(3,250,8);  ledcAttachPin(lm2,3);
  ledcWrite(0,0); ledcWrite(1,0);//right
  ledcWrite(2,0); ledcWrite(3,0);//left
  Wire.begin();
  byte status = mpu.begin();
  while(status!=0){}
  mpu.calcOffsets();
  delay(10);
  mpu.update();
  sp = mpu.getAngleZ();
  delay(1);
  Serial.begin(9600);

  right();
} 
//right turn -90
//left turn +90

void loop()
{
//  right();
// right();
  
}

void right() //right
{ spt = sp - 79;  //82
while(cp>spt) {   
  mpu.update();
  cp = mpu.getAngleZ();
  er = spt - cp;
  pwr = base - (er*p + d*(pe - er));
  pwl = base  - (er*p + d*(pe - er));
  pe  = er;
  ledcWrite(0,pwr);
  ledcWrite(3,pwl);
  Serial.print("pwm = ");
  Serial.println(pwr);
  Serial.println(pwl);
  Serial.print("current = ");
  Serial.println(cp);
}
  ledcWrite(0,0);
  ledcWrite(3,0);
}

void left() //left
{ spt = sp + 80;
while(cp<spt) {   
  mpu.update();
  cp = mpu.getAngleZ();
  er = spt - cp;
  pwr = base  -  (er*p + d*(pe - er));
  pwl = base  - (er*p + d*(pe - er));
  pe  = er;
  ledcWrite(1,pwr);
  ledcWrite(2,pwl);
}
  ledcWrite(1,0);
  ledcWrite(2,0);
}

void leftu() //Right U turn
{ spt = sp + 167;
while(cp<spt) {   
  mpu.update();
  cp = mpu.getAngleZ();
  er = spt - cp;
  pwr = base  - (er*p + d*(pe - er));
  pwl = base  - (er*p + d*(pe - er));
  pe  = er;
  ledcWrite(1,pwr);
  ledcWrite(2,pwl+8);
}
  ledcWrite(1,0);
  ledcWrite(2,0);
}

void rightu()//Left U turn
{ spt = sp - 120;
while(cp>spt) {   
  mpu.update();
  cp = mpu.getAngleZ();
  er = spt - cp;
  pwr = base  + (er*p + d*(pe - er));
  pwl = base  - (er*p + d*(pe - er));
  pe  = er;
  ledcWrite(0,pwr);
  ledcWrite(3,pwl);
}
  ledcWrite(0,0);
  ledcWrite(3,0);
}