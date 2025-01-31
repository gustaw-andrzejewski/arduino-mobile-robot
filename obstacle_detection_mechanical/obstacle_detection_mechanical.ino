// Motor driver pins
#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165

// Mechanical obstacle sensors
#define L_SIDE_SENSOR A0
#define R_SIDE_SENSOR A1

// Buzzer
#define BUZZER 10

void setup() {
  // Configure motor driver pins
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);

  // Configure mechanical sensor pins
  pinMode(L_SIDE_SENSOR, INPUT_PULLUP);
  pinMode(R_SIDE_SENSOR, INPUT_PULLUP);

  // Configure buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW); // Turn off buzzer

  // Seed random number generator
  randomSeed(analogRead(5));   
}

void loop() {

  // Move forward
  moveForward(40);
  int randomTurnTime  = random(5, 20) * 10;

  // If left sensor detects an obstacle
  if (digitalRead(L_SIDE_SENSOR) == LOW) {
    gradualBackOff();
    digitalWrite(BUZZER, 1);
    delay(500);
    // turn right
    leftMotor(40);
    rightMotor(-40);
    digitalWrite(BUZZER, 0);
    delay(140+randomTurnTime );
}
  // If right sensor detects an obstacle
  if (digitalRead(R_SIDE_SENSOR) == LOW) {
    gradualBackOff();
    digitalWrite(BUZZER, 1);
    delay(500);
    // turn left
    leftMotor(-40);
    rightMotor(40);
    digitalWrite(BUZZER, 0);
    delay(140+randomTurnTime );

  }

}

// Move both motors forward at a given speed
void moveForward(int speed) {
  moveLeftMotor(speed);
  moveRightMotor(speed);
}

// Gradual backoff when an obstacle is detected
void gradualBackOff() {
  for (int speed = 0; speed <= 40; speed += 10) {
    moveLeftMotor(-speed);
    moveRightMotor(-speed);
    delay(50);
  }
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