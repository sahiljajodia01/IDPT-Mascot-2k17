#include <Servo.h>

Servo sh;
Servo sv;
int shPin = 9;
int svPin = 10;
int pick_up = 5000;
int drop = 5000;
int jar_1 = 45;
int jar_2 = 0;
int vcc=5;

void setup()
{
  sh.attach(shPin);
  sv.attach(svPin);
  //pinMode(vcc,OUTPUT);
}

void loop()
{
  //digitalWrite(vcc,HIGH);
  h_motion_1();
  v_motion_2();
  h_motion_3(jar_2); // enter jar_1 or jar_2 as input
  v_motion_4();
  delay(5000);
}

void h_motion_1()
{
  for (int pos = 0; pos <= 90; pos += 1)
  {
    sh.write(pos);
    delay(15);
  }
}

void v_motion_2()
{
  for (int pos = 0; pos <= 90; pos += 1)
  {
    sv.write(pos);
    delay(15);
  }
  delay(pick_up);
  for (int pos = 90; pos > 45; pos -= 1)
  {
    sv.write(pos);
    delay(15);
  }
}

void h_motion_3(int jar)
{
  for (int pos = 90; pos > jar; pos -= 1)
  {
    sh.write(pos);
    delay(15);
  }
}

void v_motion_4()
{
  for (int pos = 45; pos < 90; pos += 1)
  {
    sv.write(pos);
    delay(15);
  }
  delay(drop);
  for (int pos = 90; pos > 0; pos -= 1)
  {
    sv.write(pos);
    delay(15);
  }
}

