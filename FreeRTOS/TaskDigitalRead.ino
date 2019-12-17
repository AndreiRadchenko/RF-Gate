void TaskDigitalRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  /*
    DigitalReadSerial
    Reads a digital input on pin 2, prints the result to the serial monitor

    This example code is in the public domain.
  */
    struct sensor mySensor;
    char value;

  for (;;) // A Task shall never return or exit.
  {
    value = char(0x4F);
    // read the input pin:
    int sw_opened1 = digitalRead(SW_OPENED1);
    int sw_closed1 = digitalRead(SW_CLOSED1);
    int sw_opened2 = digitalRead(SW_OPENED2);
    int sw_closed2 = digitalRead(SW_CLOSED2);
    
    if (sw_opened1 == 0) bitWrite(value, 3, 0);
    if (sw_closed1 == 0) bitWrite(value, 2, 0);
    if (sw_opened2 == 0) bitWrite(value, 1, 0);
    if (sw_closed2 == 0) bitWrite(value, 0, 0);

    mySensor.TaskType = TASKDIGITAL;
    mySensor.value =  value;  
    xQueueSend(structQueue, &mySensor, portMAX_DELAY);
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}
