//Andrii Balbat keychain codes:
const int OPENCOD1 = 13201570;
const int CLOSECOD1 = 13201576;

const int OPENCOD2 = 13452930;
const int CLOSECOD2 = 13452936;

void TaskRfRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  /*
    DigitalReadSerial
    Reads a digital input on pin 2, prints the result to the serial monitor

    This example code is in the public domain.
  */

  // Receiver on interrupt 0 => that is pin #2
  mySwitch.enableReceive(0);
  struct sensor mySensor;

  for (;;) // A Task shall never return or exit.
  {

    if (mySwitch.available()) {
      
    int value = mySwitch.getReceivedValue();

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      // We were able to obtain or "Take" the semaphore and can now access the shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the state of the button:
      if (value == 0) {
        Serial.print("Unknown encoding");
        } 
      else {
        Serial.print("Received ");
        Serial.print( mySwitch.getReceivedValue() );
        Serial.print(" / ");
        Serial.print( mySwitch.getReceivedBitlength() );
        Serial.print("bit ");
        Serial.print("Protocol: ");
        Serial.println( mySwitch.getReceivedProtocol() );
      };
          
    if (value == OPENCOD1 || value == OPENCOD2) {
          mySensor.TaskType = TASKRF;
          mySensor.value =  START;  
          xQueueSend(structQueue, &mySensor, portMAX_DELAY);
          vTaskDelay(1000 / portTICK_PERIOD_MS);      
        };
    if (value == CLOSECOD1 || value == CLOSECOD2) {
          mySensor.TaskType = TASKRF;
          mySensor.value =  REVERS;
          xQueueSend(structQueue, &mySensor, portMAX_DELAY);
          vTaskDelay(1000 / portTICK_PERIOD_MS);        
        };
        
    //vTaskDelay(1000 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
    };
    
    xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
    //vTaskDelay(1000 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
      mySwitch.resetAvailable();
      vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
   
}
