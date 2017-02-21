#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 40 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define PWM_MOTOR_PIN 6
#define MOTOR_PIN1 4
#define MOTOR_PIN2 5   
#define IR 8
#define em 7
#define shPin 9
#define svPin 10
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

Servo sh;
Servo sv;

int pick_up = 2000;
int drop = 1000;
int jar_1 = 45;
int jar_2 = 0;

int dist,detection=0;

void setup()
{
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(PWM_MOTOR_PIN, OUTPUT);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  sh.attach(shPin);
  sv.attach(svPin);
  pinMode(em,OUTPUT);
  pinMode(IR,INPUT);
}

void loop()
{
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  // If the ping receives a response, it sends an OFF signal to the DC, otherwise it keeps sending HIGH signals. The stop time depends on how long the can is detected by the ultrasound.
  dist=(int)(sonar.ping_cm());
  if (dist>0 && dist<20)
  {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);//conveyor belt
    if(!digitalRead(IR))//Reads Black
    {
      h_motion_1();
      v_motion_2();
      h_motion_3(jar_1); // enter jar_1 for black or jar_2 for red 
      v_motion_4(jar_1); 
    }
    else if(digitalRead(IR))
    {
      h_motion_1();
      v_motion_2();
      h_motion_3(jar_2); // enter jar_1 for black or jar_2 for red 
      v_motion_4(jar_2);
    }
    
  }
  else
  {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, HIGH);
    digitalWrite(PWM_MOTOR_PIN, 100);
  }
  
}

void h_motion_1()//turning shoulder
{
  for (int pos = 0; pos <= 90; pos += 1)
  {
    sh.write(pos);
    delay(40);
  }
}

void v_motion_2()//elbow down,parallel to ground & pickup
{
  for (int pos = 0; pos <= 90; pos += 1)
  {
    sv.write(pos);
    delay(40);
  }
  delay(1000);
  digitalWrite(em,HIGH); //LOW is for turning it on
  delay(pick_up);
  for (int pos = 90; pos > 45; pos -= 1)
  {
    sv.write(pos);
    delay(40);
  }
}

void h_motion_3(int jar)//shoulder rotate according to color detected
{
  for (int pos = 90; pos > jar; pos -= 1)
  {
    sh.write(pos);
    delay(40);
  }
}

void v_motion_4(int jar)//dropping and returning to original stage
{
  for (int pos = 45; pos < 90; pos += 1)
  {
    sv.write(pos);
    delay(40);
  }
  delay(1000);
  digitalWrite(em,LOW);
  delay(drop);
  for (int pos = 90; pos > 0; pos -= 1)
  {
    sv.write(pos);
    delay(40);
  }
   if (jar == jar_1)
  {
    for (int pos = 45; pos > 0; pos -= 1)
    {
      sh.write(pos);
      delay(40);
    }
  }
}

