#include <Servo.h>

// Servo motor
Servo servo;
#define SERVO_PIN 11

// Motor driver pins
#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165
 
// Additional components
#define BUZZER 10

// Ultrasonic sensor pins
#define TRIG_PIN 7
#define ECHO_PIN 8
 
void setup() {
  // Configure motor driver pins
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);

  // Configure buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  // Configure ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 
  // Initialize servo and set it to front position
  servo.attach(SERVO_PIN);
  servo.write(90);
}

void loop() {
  // Move forward if no obstacle detected
  if (checkDistance() > 40) {
    goForward(40);
  }
  // if obstacle
  else{
    stopMotors();
    scanAndReact();    
    }
  }


// Scan left and right to find a clear path
void scanAndReact() {
  servo.write(20); // Turn sensor to the right
  delay(800);

  if (checkDistance() > 40) {
    turnRight(40);
    delay(400);
  } 
  else {
    servo.write(160); // Turn sensor to the left
    delay(800);

    if (checkDistance() > 40) {
      turnLeft(40);
      delay(400);
    } 
    else {
      buzzerBeater();
      gradualReverse();
    }
  }

  servo.write(90); // Reset sensor position to front
}

// Function to measure distance using the ultrasonic sensor
int checkDistance() {
  long time, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  time = pulseIn(echoPin, HIGH);
  distance = time / 58;

  return distance;
}

// Gradual reverse movement
void gradualReverse() {
  for (int speed = 0; speed <= 40; speed += 10) {
    moveLeftMotor(-speed);
    moveRightMotor(-speed);
  }
}

// Activate buzzer
void buzzerBeater() {
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(100);
}

// Turning movements
void turnRight(int speed) {
  moveLeftMotor(speed);
  moveRightMotor(-speed);
}

void turnLeft(int speed) {
  moveLeftMotor(-speed);
  moveRightMotor(speed);
}


// Move forward
void moveForward(int speed) {
  moveLeftMotor(speed);
  moveRightMotor(speed);
}

// Stop motors
void stopMotors() {
  analogWrite(L_PWM, 0);
  analogWrite(R_PWM, 0);
}


// Control the left motor
void moveLeftMotor(int speed) {
  if (speed > 0) { // Move forward
    speed = map(speed, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, LOW); 
    analogWrite(L_PWM, speed);
  } else { // Move backward
    speed = abs(speed);
    speed = map(speed, 0, 100, 0, PWM_MAX);
    digitalWrite(L_DIR, HIGH);
    analogWrite(L_PWM, speed);
  }
}

// Control the right motor
void moveRightMotor(int speed) {
  if (speed > 0) { // Move forward
    speed = map(speed, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, LOW); 
    analogWrite(R_PWM, speed);
  } else { // Move backward
    speed = abs(speed);
    speed = map(speed, 0, 100, 0, PWM_MAX);
    digitalWrite(R_DIR, HIGH);
    analogWrite(R_PWM, speed);
  }
}

// Stop both motors
void stopMotors() {
  analogWrite(L_PWM, 0);
  analogWrite(R_PWM, 0);
}