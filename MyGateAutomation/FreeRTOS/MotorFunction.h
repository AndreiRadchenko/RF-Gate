#define MOTOR1PIN1 4
#define MOTOR1PIN2 5
#define MOTOR2PIN1 6
#define MOTOR2PIN2 7

#define LAMPPIN 8

void openMotor1() {
  digitalWrite(MOTOR1PIN1, LOW);
  digitalWrite(MOTOR1PIN2, HIGH);
};
void closeMotor1() {
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, LOW);
};
void stopMotor1() {
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, HIGH);
};

void openMotor2() {
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, HIGH);
};
void closeMotor2() {
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, LOW);
};
void stopMotor2() {
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, HIGH);
};

void lampON() {
  digitalWrite(LAMPPIN, LOW);
};
void lampOFF() {
  digitalWrite(LAMPPIN, HIGH);
};
