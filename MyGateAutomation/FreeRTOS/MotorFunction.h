#define MOTOR1PIN1 4
#define MOTOR1PIN2 5
#define MOTOR2PIN1 6
#define MOTOR2PIN2 7

#define LAMPPIN 8

const char OPENING = 'd';
const char OPENED = 'e';
const char CLOSING = 'f';
const char CLOSED = 'g';
const char STOPED = 'j';
const char STOPED1 = 'k';
const char STOPED2 = 'l';
const char MOVING = 'm';
const char STARTMOTOR1 = 'n';
const char STARTMOTOR2 = 'o';

char currentState;
char Leaf1State;
char Leaf2State;

TickType_t MOTOR1PERIOD = pdMS_TO_TICKS ( 50000 ); //time (ms converted to TICS) of motor1 open/close
TickType_t MOTOR2PERIOD = pdMS_TO_TICKS ( 38500 ); //time of motor2 open/close
TickType_t MOTOR1CLOSEPERIOD = MOTOR1PERIOD + pdMS_TO_TICKS ( 800 );
TickType_t MOTOR2CLOSEPERIOD = MOTOR2PERIOD + pdMS_TO_TICKS ( 1200 );
float CLOSECOEF1 = MOTOR1CLOSEPERIOD/MOTOR1PERIOD;
float CLOSECOEF2 = MOTOR2CLOSEPERIOD/MOTOR2PERIOD;

uint32_t start_time1; // = millis();
uint32_t start_time2;

/* on reset assumed that gate are closed */
TickType_t OPENTIME1 = MOTOR1PERIOD; //timer period in TICKS
TickType_t OPENTIME2 = MOTOR2PERIOD;
TickType_t CLOSETIME1 = 1;
TickType_t CLOSETIME2 = 1;


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
