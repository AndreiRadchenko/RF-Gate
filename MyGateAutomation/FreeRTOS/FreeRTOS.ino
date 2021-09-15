#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
#include <RCSwitch.h>
#include "ACS712.h"
#include "MotorFunction.h"

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

// We have 30 amps version sensor connected to A0 pin of arduino
// Replace with your version if necessary
ACS712 currentSensor1(ACS712_30A, A0);
ACS712 currentSensor2(ACS712_30A, A1);

// define four Tasks for DigitalRead & AnalogRead
void TaskAnalogRead( void *pvParameters );
void TaskRfRead( void *pvParameters );
void TaskMotorCtrl( void *pvParameters );

struct sensor {  //struct for transfer data from poll tasks to TaskMotorCtrl
  char TaskType;
  char value;
};

QueueHandle_t structQueue;

const char TASKRF = '1';
const char TASKDIGITAL = '2';
const char TASKANALOG = '3';
const char TASKMOTORCTRL = '4';
const char START = 'a'; //00001010
const char STOP = 'b';
const char REVERS = 'c'; //00000101

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

  // calibrate() method calibrates zero point of sensor,
  // It is not necessary, but may positively affect the accuracy
  // Ensure that no current flows through the sensor at this moment
  // If you are not sure that the current through the sensor will not leak during calibration - comment out this method
  currentSensor1.calibrate();
  delay(10);
  currentSensor2.calibrate();
  delay(10);
  
  
  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if ( xSerialSemaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

    /**
   * Create a queue.
   * https://www.freertos.org/a00116.html
   */
  structQueue = xQueueCreate(10, // Queue length
                              sizeof(struct sensor) // Queue item size
                              );
  if (structQueue != NULL) { // Create task that consumes the queue if it was created.

  xTaskCreate(
    TaskAnalogRead
    ,  "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL );

  xTaskCreate(
    TaskTimers
    ,  "Timers"
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL );

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

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/
