// This program provides basic control over an RC car using a two channel motor shield
// 8 pins are used, as listed below
// The program will ramp up speed and turning angle from 0% to 100% then start over

const int 
PWM_LR   = 3,
DIR_LR   = 12,
BRAKE_LR = 9,
SNS_LR   = A0,
PWM_FB   = 11,
DIR_FB   = 13,
BRAKE_FB = 8,
SNS_FB   = A1,
FORWARD  = HIGH,
BACKWARD = LOW,
LEFT     = HIGH,
RIGHT    = LOW;

int speed;

void setup() {
  pinMode(BRAKE_LR, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_LR, OUTPUT);    // Direction pin on channel A
  pinMode(BRAKE_FB, OUTPUT);  // Brake pin on channel B
  pinMode(DIR_FB, OUTPUT);    // Direction pin on channel B

  // Open Serial communication
  Serial.begin(9600);
  Serial.println("Motor shield DC motor Test:\n");
  speed = 0;
}

void loop() {
  speed = speed + 20;
  Serial.println(speed);
  if (speed > 255) {
    speed = 0;
  }

  move(FORWARD, speed);
  turn(LEFT, speed);
  delay(200);
}

void move(int direction, int speed) {
  digitalWrite(DIR_FB, direction);
  analogWrite(PWM_FB, speed);
}

void turn(int direction, int speed) {
  digitalWrite(DIR_LR, direction);
  analogWrite(PWM_LR, speed);
}

void brake() {
  digitalWrite(BRAKE_FB, HIGH);
  delay(500);
  digitalWrite(BRAKE_FB, LOW);
}
