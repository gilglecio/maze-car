#include <Ultrasonic.h>
#include <Servo.h>

const int MOTOR1_SPEED = 6;
const int MOTOR1_IN1 = 4;
const int MOTOR1_IN2 = 7;

const int MOTOR2_SPEED = 5;
const int MOTOR2_IN1 = 2;
const int MOTOR2_IN2 = 3;

const int ULTRASON_VCC = 13;
const int ULTRASON_ECHO = 12;
const int ULTRASON_TRIGGER = 11;

const int SERVO_GND = 8;
const int SERVO_VCC = 9;
const int SERVO_PIN = 10;

const float MIN_DISTANCE_CM = 2;

int servoAngles[] = {0, 45, 90, 135, 180};

Ultrasonic ultrasonic(ULTRASON_TRIGGER, ULTRASON_ECHO);
Servo servo;

void setup () {
  
  servo.attach(SERVO_PIN);
  servo.write(90);
  
  pinMode(MOTOR1_SPEED, OUTPUT);
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  
  pinMode(MOTOR2_SPEED, OUTPUT);
  pinMode(MOTOR2_IN1, OUTPUT);
  pinMode(MOTOR2_IN2, OUTPUT);
  
  pinMode(ULTRASON_VCC, OUTPUT);
  pinMode(ULTRASON_ECHO, INPUT);
  pinMode(ULTRASON_TRIGGER, OUTPUT);
  
  digitalWrite(ULTRASON_VCC, HIGH);
  
  pinMode(SERVO_GND, OUTPUT);
  pinMode(SERVO_VCC, OUTPUT);
  pinMode(SERVO_PIN, INPUT);
  
  digitalWrite(SERVO_GND, LOW);
  digitalWrite(SERVO_VCC, HIGH);
  
  breakMotors();
  
  setSpeedMotors(100);
}

void loop () {
  
  float distance = getDistance();
  
  if (distance <= MIN_DISTANCE_CM) {
    breakMotors();
    toTheLeft(2000);
  }
  
  forward();
}

float getDistanceByAngle() {

  int array_length = sizeof(servoAngles) -1;
  float distances[array_length];
  
  for (int i = 0; i = array_length; i++) {
    servo.attach(servoAngles[i]);
    distances[servoAngles[i]] = getDistance();
  }
}

float getDistance() {
  return ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM)
}

void setSpeedMotors(int val) {
  analogWrite(MOTOR1_SPEED, val);
  analogWrite(MOTOR2_SPEED, val);
}

void breakMotors() {
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, HIGH);
  
  digitalWrite(MOTOR2_IN1, HIGH);
  digitalWrite(MOTOR2_IN2, HIGH);
}

void forward(int time = 0) {
  motor1_CW();
  motor2_CW();
  delay(time);
}

void backward(int time = 0) {
  motor1_CCW();
  motor2_CCW();
  delay(time);
}

void toTheLeft(int time = 0) {
  motor1_CW();
  motor2_CCW();
  delay(time);
}

void toTheRight(int time = 0) {
  motor1_CCW();
  motor2_CW();
  delay(time);
}

void motor1_CW() {
  digitalWrite(MOTOR1_IN1, HIGH);
  digitalWrite(MOTOR1_IN2, LOW);
}

void motor1_CCW() {
  digitalWrite(MOTOR1_IN1, LOW);
  digitalWrite(MOTOR1_IN2, HIGH);
}

void motor2_CW() {
  digitalWrite(MOTOR2_IN1, HIGH);
  digitalWrite(MOTOR2_IN2, LOW);
}

void motor2_CCW() {
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, HIGH);
}