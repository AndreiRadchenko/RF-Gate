const char OWERLOAD1 = 'O';
const char OWERLOAD2 = 'P';
const char OWERLOAD12 = 'R';
const char NORMAL = 'N';
const float NORMALCURR1 = 4.5;
const float NORMALCURR2 = 4.5;
//const float NORMALCURR1 = 6;
//const float NORMALCURR2 = 6;
//const float STARTCURR = 10;

void TaskAnalogRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
   struct sensor mySensor;
   char value;
   float owerloadCurr1 = NORMALCURR1;
   float owerloadCurr2 = NORMALCURR2;
   
  for (;;)
  {
    // read the input on analog pin 0:
    int sensor1Value = analogRead(A0);
    //delay(1);
    int sensor2Value = analogRead(A1);
    
    // Read current from sensor
    float current1 = currentSensor1.getCurrentDC();
    delay(5);
    float current2 = currentSensor2.getCurrentDC();
    //delay(50);
    if (current1 > owerloadCurr1 && current2 > owerloadCurr2) { value = OWERLOAD12; }
       else if (current1 > owerloadCurr1) { value = OWERLOAD1; }
       else if (current2 > owerloadCurr2) { value = OWERLOAD2; }
       else { value = NORMAL; };

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      // We were able to obtain or "Take" the semaphore and can now access the shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the value you read:
      Serial.print("owerloadCurr1 = ");
      Serial.print(owerloadCurr1);
      Serial.print("; sensor1Value = ");
      Serial.print(sensor1Value);
      Serial.print("; owerloadCurr2 = ");
      Serial.println(owerloadCurr2);
      Serial.print("Current1 = ");
      Serial.print(current1);
      Serial.print("; Current2 = ");
      Serial.println(current2);
      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
    
    if (value != NORMAL) {
      
      mySensor.TaskType = TASKANALOG;
      mySensor.value =  value;  
      xQueueSend(structQueue, &mySensor, portMAX_DELAY);
    };
    
    vTaskDelay(500/portTICK_PERIOD_MS);  // Wait a 0.5 second before the new measurement
  }
}
