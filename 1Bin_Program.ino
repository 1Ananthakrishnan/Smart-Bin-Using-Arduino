#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

const int triggerDistance = 20; 

const int closedAngle = 90; 
const int openAngle = 0;    

const int speedDelay = 15; 

Servo binServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  binServo.attach(servoPin);
  
  binServo.write(closedAngle);
  delay(1000); 

  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();


  if (distance > 2 && distance <= triggerDistance) {
    
    for (int pos = closedAngle; pos >= openAngle; pos -= 1) {
      binServo.write(pos);
      delay(speedDelay);
    }
    
    delay(2000); 


    for (int pos = openAngle; pos <= closedAngle; pos += 1) {
      binServo.write(pos);
      delay(speedDelay); 
    }
    

    delay(1500);              
  }

  delay(60);
}


int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); 
  
  if (duration == 0) {
    return 999; 
  }
  
  return duration * 0.034 / 2;
}