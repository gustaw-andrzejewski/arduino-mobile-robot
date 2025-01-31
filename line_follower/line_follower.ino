// Motor driver pins
#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165

// Line sensors
#define R_LINE_SENSOR A0
#define L_LINE_SENSOR A1
#define BORDERLINE 900


void setup() {
  // Configure motor driver pins
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);

  // Initialize serial monitor
  Serial.begin(9600);
}

void loop() {
  if (!leftSensorDetectsLine() && !rightSensorDetectsLine()) {
    moveForward(40);
  } 
  else if (leftSensorDetectsLine()) {
    curveLeft(40);
  } 
  else if (rightSensorDetectsLine()) {
    curveRight(40);
  }
}


// Check if left sensor detects the line
bool leftSensorDetectsLine() {
  return analogRead(L_LINE_SENSOR) > BORDERLINE;
}

// Check if right sensor detects the line
bool rightSensorDetectsLine() {
  return analogRead(R_LINE_SENSOR) > BORDERLINE;
}

// Curve movements
void curveRight(int speed) {
  moveLeftMotor(speed);
  moveRightMotor(0);
}

void curveLeft(int speed) {
  moveLeftMotor(0);
  moveRightMotor(speed);
}

// Move forward
void moveForward(int speed) {
  moveLeftMotor(speed);
  moveRightMotor(speed);
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