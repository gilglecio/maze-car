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

Ultrasonic ultrasonic(ULTRASON_TRIGGER, ULTRASON_ECHO);
Servo servo;

void setSpeedMotors(int val) {
  analogWrite(MOTOR1_SPEED, val);
  analogWrite(MOTOR2_SPEED, val);
}

void breakMotors(int time = 0) {
  setSpeedMotors(0);
  
  delay(time);
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

void toTheRight(int time = 0) {
  motor1_CCW();
  motor2_CW();
  delay(time);
}

void toTheLeft(int time = 0) {
  motor1_CW();
  motor2_CCW();
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
  digitalWrite(MOTOR2_IN1, LOW);
  digitalWrite(MOTOR2_IN2, HIGH);
}

void motor2_CCW() {
  digitalWrite(MOTOR2_IN1, HIGH);
  digitalWrite(MOTOR2_IN2, LOW);
}

void setup () {
  
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
  pinMode(SERVO_PIN, OUTPUT);
  
  digitalWrite(SERVO_GND, LOW);
  digitalWrite(SERVO_VCC, HIGH);
  
  servo.attach(SERVO_PIN);
  servo.write(90);
  
  breakMotors(0);
  
  setSpeedMotors(150);
  
  Serial.begin(9600);
}

void moveServo(int angle = 0, int time = 0) {
  if(angle >= 0 || angle <= 180) {
    servo.write(angle);
  }
}

float getDistance() {
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  return cmMsec; 
}

// int servoAngles[] = {175, 127, 80, 47, 0};

void loop () {
 setSpeedMotors(115);
 forward();
 moveServo(80);

  if(getDistance() < 20) {
    breakMotors();
    moveServo(175, 0);
    float dLeft = getDistance();
    delay(500);
    moveServo(0, 0);
    float dRight = getDistance();
    delay(500);
    
    if(dLeft > dRight) {
      Serial.println("Esquerda");
        setSpeedMotors(115);
       toTheLeft(400);
    } else {
        setSpeedMotors(115);
       toTheRight(400);
      Serial.println("Direita");
    }
  }
}
