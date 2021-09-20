#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
#include <RCSwitch.h>
#include "ACS712.h"
#include "MotorFunction.h"
#include <timers.h>

// Include queue support
#include <queue.h>

/* 
 * Declaring a global variable of type QueueHandle_t 
 * 
 */
QueueHandle_t integerQueue;

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at any time.
SemaphoreHandle_t xSerialSemaphore;
RCSwitch mySwitch = RCSwitch();

// define four Tasks for DigitalRead & AnalogRead
void TaskTimers( void *pvParameters );
void TaskRfRead( void *pvParameters );
void TaskMotorCtrl( void *pvParameters );

struct sensor {  //struct for transfer data from poll tasks to TaskMotorCtrl
  char TaskType;
  char value;
};

QueueHandle_t structQueue;

const char TASKRF = '1';
const char TASKDIGITAL = '2';
const char TASKTIMER = '3';
const char TASKMOTORCTRL = '4';
const char START = 'a'; //00001010
const char STOP = 'b';
const char REVERS = 'c'; //00000101

const char OPEN_LEFT = 'd';
const char CLOSE_LEFT = 'e';
const char STOP_LEFT = 'f';
const char OPEN_RIGHT = 'g';
const char CLOSE_RIGHT = 'h';
const char STOP_RIGHT = 'k';

TimerHandle_t motor1OpenTimer, motor2OpenTimer, motor1CloseTimer, motor2CloseTimer;
//void motor1TimerCallback(TimerHandle_t xTimer);
//void motor2TimerCallback(TimerHandle_t xTimer);

// the setup function runs once when you press reset or power the board
void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MOTOR1PIN1, OUTPUT); //control pin1 motor1
  pinMode(MOTOR1PIN2, OUTPUT); //control pin2 motor1
  pinMode(MOTOR2PIN1, OUTPUT); //control pin1 motor2
  pinMode(MOTOR2PIN2, OUTPUT); //control pin2 motor2
  pinMode(LAMPPIN, OUTPUT); //control signal lamp
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, HIGH);
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, HIGH);
  digitalWrite(LAMPPIN, HIGH);
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if ( xSerialSemaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }


  motor1OpenTimer = xTimerCreate("OpenTimerMotor1", OPENTIME1, pdFALSE, 0, motor1TimerCallback);
  motor2OpenTimer = xTimerCreate("OpenTimerMotor2", OPENTIME2, pdFALSE, 0, motor2TimerCallback);
  motor1CloseTimer = xTimerCreate("CloseTimerMotor1", CLOSETIME1, pdFALSE, 0, motor1TimerCallback);
  motor2CloseTimer = xTimerCreate("CloseTimerMotor2", CLOSETIME2, pdFALSE, 0, motor2TimerCallback);
    /**
   * Create a queue.
   * https://www.freertos.org/a00116.html
   */
  structQueue = xQueueCreate(10, // Queue length
                              sizeof(struct sensor) // Queue item size
                              );
  if (structQueue != NULL) { // Create task that consumes the queue if it was created.

/*  xTaskCreate(
    TaskTimers
    ,  "Timers"
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL );
*/
  xTaskCreate(
    TaskRfRead
    ,  "RfRead"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskMotorCtrl
    ,  "MotorCtrl"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );    

  }

  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

void motor1TimerCallback(TimerHandle_t xTimer) {
  stopMotor1();
  Leaf1State = STOPED;
  if ( currentState == OPENING ) {
    OPENTIME1 = 1;
    CLOSETIME1 = MOTOR1CLOSEPERIOD;
    if ( Leaf2State == STOPED ) {
      currentState = OPENED;
      lampOFF();
    };
  }
  else if ( currentState == CLOSING ) {
    OPENTIME1 = MOTOR1PERIOD;
    CLOSETIME1 = 1;
    if ( Leaf2State == STOPED ) {
      currentState = CLOSED;
      lampOFF();               
    };
  };
};

void motor2TimerCallback(TimerHandle_t xTimer) {
  stopMotor2();
  Leaf2State = STOPED;
  if ( currentState == OPENING ) {
    OPENTIME2 = 1;
    CLOSETIME2 = MOTOR2CLOSEPERIOD;
    if ( Leaf1State == STOPED ) {
       currentState = OPENED;
       lampOFF();
    };
  }
  else if ( currentState == CLOSING ) {
    OPENTIME2 = MOTOR2PERIOD;
    CLOSETIME2 = 1;
    if ( Leaf1State == STOPED ){
       currentState = CLOSED;
       lampOFF();
    };
  };
};
