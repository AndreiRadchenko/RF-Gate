const char OWERLOAD = 'O';
const char NORMAL = 'N';
float owerloadCurr = 8;

void TaskAnalogRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
   struct sensor mySensor;
   char value;

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    
    // Read current from sensor
    float current = sensor.getCurrentDC();
    if (current > owerloadCurr) { value = OWERLOAD; }
    else { value = NORMAL; };

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      // We were able to obtain or "Take" the semaphore and can now access the shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the value you read:
      Serial.println(sensorValue);
      Serial.println(current);

      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }

    mySensor.TaskType = TASKANALOG;
    mySensor.value =  value;  
    xQueueSend(structQueue, &mySensor, portMAX_DELAY);
    vTaskDelay(100);  // Wait a second before the new measurement
  }
}
