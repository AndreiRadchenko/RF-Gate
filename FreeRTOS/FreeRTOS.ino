#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
#include <RCSwitch.h>

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
void TaskDigitalRead( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
void TaskRfRead( void *pvParameters );
void TaskMotorCtrl( void *pvParameters );

struct sensor {  //struct for transfer data from poll tasks to TaskMotorCtrl
  char TaskType;
  char value;
};

QueueHandle_t structQueue;

#define MOTOR1PIN1 4
#define MOTOR1PIN2 5
#define MOTOR2PIN1 6
#define MOTOR2PIN2 7

#define SW_OPENED1 8
#define SW_CLOSED1 9
#define SW_OPENED2 10
#define SW_CLOSED2 11

const char TASKRF = '1';
const char TASKDIGITAL = '2';
const char TASKANALOG = '3';
const char START = 'a'; //00001010
const char STOP = 'b';
const char REVERS = 'c'; //00000101

// the setup function runs once when you press reset or power the board
void setup() {

  pinMode(MOTOR1PIN1, OUTPUT); //control pin1 motor1
  pinMode(MOTOR1PIN2, OUTPUT); //control pin2 motor1
  pinMode(MOTOR2PIN1, OUTPUT); //control pin1 motor2
  pinMode(MOTOR2PIN2, OUTPUT); //control pin2 motor2
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, HIGH);
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, HIGH);

  // make the pushbutton's pin an input:
  pinMode(SW_OPENED1, INPUT_PULLUP);
  pinMode(SW_CLOSED1, INPUT_PULLUP);
  pinMode(SW_OPENED2, INPUT_PULLUP);
  pinMode(SW_CLOSED2, INPUT_PULLUP);
  
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

    /**
   * Create a queue.
   * https://www.freertos.org/a00116.html
   */
  structQueue = xQueueCreate(10, // Queue length
                              sizeof(struct sensor) // Queue item size
                              );
  if (structQueue != NULL) { // Create task that consumes the queue if it was created.
    
  // Now set up two Tasks to run independently.
  xTaskCreate(
    TaskDigitalRead
    ,  (const portCHAR *) "DigitalRead"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskAnalogRead
    ,  (const portCHAR *) "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL );

  xTaskCreate(
    TaskRfRead
    ,  (const portCHAR *) "RfRead"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskMotorCtrl
    ,  (const portCHAR *) "MotorCtrl"  // A name just for humans
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