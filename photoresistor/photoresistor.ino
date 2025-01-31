// Motor driver pins
#define L_PWM 5
#define L_DIR 4
#define R_PWM 6
#define R_DIR 9
#define PWM_MAX 165

// Light sensors
#define R_LIGHT_SENSOR A0
#define L_LIGHT_SENSOR A1

// Thresholds
#define MAX_DIFFERENCE 300
#define MIN_DIFFERENCE -300
#define LIGHT_THRESHOLD 50

// Additional components
#define BUZZER 10
#define LED 13

void setup() {
  //Konfiguracja pinow od mostka H
  pinMode(L_DIR, OUTPUT);
  pinMode(R_DIR, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);
 
  //Konfiguracja pozostalych elementow
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, 0); //Wylaczenie buzzera  
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0); // wylaczenie ledu 
}

void loop() {
  static bool initializationDone = false;

  int leftRead = analogRead(L_LIGHT_SENSOR);
  int rightRead = analogRead(R_LIGHT_SENSOR);
  int difference = leftRead - rightRead;

  if (difference < MIN_DIFFERENCE) {
    difference = MIN_DIFFERENCE;
  }
  else if (difference > MAX_DIFFERENCE) {
    difference = MAX_DIFFERENCE;
  }

  int velocityChange = map(difference, MIN_DIFFERENCE, MAX_DIFFERENCE, -40, 40);

  if (abs(difference) > LIGHT_THRESHOLD) {
    if (!initializationDone) {
      initializeRobot();
      initializationDone = true;
    } else if (difference > 0) {
      turnRight(30 + velocityChange);
    } else {
      turnLeft(30 - velocityChange);
    }
  } else if (initializationDone) {
    moveForward(40);
  }
}

// Initialize robot with LED and buzzer signals
void initializeRobot() {
  for (int i = 0; i < 3; i++) {
    flashLed();
    flashLed();
    buzzerBeep();
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
void buzzerBeep() {
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