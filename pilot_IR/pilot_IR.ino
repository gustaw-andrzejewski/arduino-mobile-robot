#include <RC5.h>

// Motor driver pins
#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165

// IR receiver pin
#define TSOP_PIN 3

// Additional components
#define BUZZER 10
#define LED 13

// Remote control button codes
#define BUTTON_POWER 12
#define BUTTON_LEFT 85
#define BUTTON_RIGHT 86
#define BUTTON_UP 80
#define BUTTON_DOWN 81
#define BUTTON_STOP 87

// RC5 object and vars
RC5 rc5(TSOP_PIN);
byte address; 
byte command;
byte toggle;
 
void setup() {
  // Configure motor driver pins
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);

  // Configure buzzer and LED
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

int speed = 30;
byte lastToggle = 0;

void loop() {

  if (rc5.read(&toggle, &address, &command)){
    switch(command) {
      case BUTTON_POWER:
        buzzerBeater();
      break;

      case BUTTON_TOP:
        goForward(speed);
      break;

      case BUTTON_BOTTOM:
        goBackwards(speed);
      break;

      case BUTTON_LEFT:
        turnLeft(speed);
      break;

      case BUTTON_RIGHT:
        turnRight(speed);
      break;

      case BUTTON_OK:
        stopMotors();
      break;
    }

    if (toggle == lastToggle) {
      speed++;

      if (speed >= 90) {
        speed = 30;
      }
    }
    else {
      speed = 30;
    }
    lastToggle = toggle;
    }
  }

// Flash LED
void flashLed() {
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
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

// Stop motors
void stopMotors() {
  analogWrite(L_PWM, 0);
  analogWrite(R_PWM, 0);
}

// Move directions
void moveForward(int speed) {
  moveLeftMotor(speed);
  moveRightMotor(speed);
}

void moveBackward(int speed) {
  moveLeftMotor(-speed);
  moveRightMotor(-speed);
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