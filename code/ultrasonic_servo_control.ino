#include <Servo.h>

Servo myServo;

// Pin Configuration
const int trigPin = 4;
const int echoPin = 3;
const int servoPin = 9;
const int ledPin = 8;

// Adjustable Parameters
const int triggerDistance = 10;  // Activation distance in cm
const int activeAngle = 90;      // Servo angle when object is detected
const int restAngle = 0;         // Default servo position

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  myServo.attach(servoPin);

  myServo.write(restAngle);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
}

void loop() {

  // Generate ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Measure echo duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  float distance = duration * 0.0343 / 2;

  // Display distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Object detected within threshold
  if (distance <= triggerDistance) {
    myServo.write(activeAngle);
    digitalWrite(ledPin, HIGH);
  }

  // Object outside threshold
  else {
    myServo.write(restAngle);
    digitalWrite(ledPin, LOW);
  }

  delay(200);
}
