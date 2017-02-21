#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 15 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define PWM_MOTOR_PIN 6
#define MOTOR_PIN1 5
#define MOTOR_PIN2 4

// #define STOP_TIME    5000

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(PWM_MOTOR_PIN, OUTPUT);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int dist = sonar.ping_cm();// If the ping receives a response, it sends an OFF signal to the DC, otherwise it keeps sending HIGH signals. The stop time depends on how long the can is detected by the ultrasound.
  if (dist > 0)
  {
   digitalWrite(MOTOR_PIN1, LOW);
   digitalWrite(MOTOR_PIN2, LOW);
   Serial.println(dist);  
  }
  else
  {
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, LOW);
    analogWrite(PWM_MOTOR_PIN, 100);
  }
}
