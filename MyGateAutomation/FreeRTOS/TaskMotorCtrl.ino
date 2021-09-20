
const int LEAFDELAY = 4000; //ms delay beetvin leaf opening
const int LEAFDELAY1 = 4000; //ms delay beetvin leaf closing
//const int MOTORSTARTDELAY = 3000; //ms delay beetvin leaf opening

void TaskMotorCtrl( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  struct sensor element;
  //struct sensor mySensor;
  //char value;  
  //mySensor.TaskType = TASKMOTORCTRL;
  
  //char currentState = STOPED;
  currentState = CLOSED;
  Leaf1State = MOVING;
  Leaf2State = MOVING;
  int led = LOW;
  TickType_t xRemainingTime;
  
  for (;;)
  {
    xQueueReceive(structQueue, &element, portMAX_DELAY);
    
    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      // We were able to obtain or "Take" the semaphore and can now access the shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the value you read:
      Serial.print("TaskMotorCtrl currentState: ");
      Serial.println(currentState);
      
      Serial.print("motor1OpenTimer: ");
      Serial.println(OPENTIME1*portTICK_PERIOD_MS);
      Serial.print("motor1CloseTimer: ");
      Serial.println(CLOSETIME1*portTICK_PERIOD_MS);
      
      Serial.print("motor2OpenTimer: ");
      Serial.println(OPENTIME2*portTICK_PERIOD_MS);
      Serial.print("motor2CloseTimer: ");
      Serial.println(CLOSETIME2*portTICK_PERIOD_MS);
      Serial.println("----------------");
      
    xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    };

     // if (digitalRead(LED_BUILTIN) == LOW)
     //     digitalWrite(LED_BUILTIN, HIGH);
     // else 
     //     digitalWrite(LED_BUILTIN, LOW);  
    
    if (element.TaskType == TASKRF) {

      if (digitalRead(LED_BUILTIN) == LOW)
          digitalWrite(LED_BUILTIN, HIGH);
      else 
          digitalWrite(LED_BUILTIN, LOW);    
      
      if (element.value == START && currentState == CLOSED){
 
        openMotor1();
        //xTimerStart(motor1OpenTimer, 0);
        xTimerChangePeriod(motor1OpenTimer, OPENTIME1, 10);
        //start_time1 = millis();
        lampON();
        Leaf1State = MOVING;
        currentState = OPENING;
        vTaskDelay(LEAFDELAY / portTICK_PERIOD_MS); //mast be replaced by timer
        xQueueReset(structQueue);
        openMotor2();
        xTimerChangePeriod(motor2OpenTimer, OPENTIME2, 10);
        //xTimerStart(motor2OpenTimer, 0);
        //start_time2 = millis();             
        Leaf2State = MOVING;
        //vTaskDelay(MOTORSTARTDELAY / portTICK_PERIOD_MS);
        xQueueReset(structQueue);
      }
      else if (element.value == START && currentState == OPENING) {

        xRemainingTime = xTimerGetExpiryTime( motor1OpenTimer ) - xTaskGetTickCount();
        OPENTIME1 = xRemainingTime;
        CLOSETIME1 = (MOTOR1PERIOD - OPENTIME1)*CLOSECOEF1;//we should calculate closing time, that is longer then was open time
        xTimerStop (motor1OpenTimer, 10);
        stopMotor1();

        xRemainingTime = xTimerGetExpiryTime( motor2OpenTimer ) - xTaskGetTickCount();
        OPENTIME2 = xRemainingTime;
        CLOSETIME2 = (MOTOR2PERIOD - OPENTIME2)*CLOSECOEF2;
        xTimerStop (motor2OpenTimer, 10);
        stopMotor2();
        
        lampOFF();
        currentState = STOPED;
      }
      else if (element.value == START && currentState == STOPED) {
        xTimerChangePeriod(motor1OpenTimer, OPENTIME1, 10);
        openMotor1();
        xTimerChangePeriod(motor2OpenTimer, OPENTIME2, 10);
        openMotor2();
        lampON();
        currentState = OPENING;
        Leaf1State = MOVING;
        Leaf2State = MOVING;
        //vTaskDelay(MOTORSTARTDELAY / portTICK_PERIOD_MS);
        xQueueReset(structQueue);
      }
      else if (element.value == START && currentState == OPENED) {
        
      }
      else if (element.value == START && currentState == CLOSING) {
        xRemainingTime = xTimerGetExpiryTime( motor1CloseTimer ) - xTaskGetTickCount();
        CLOSETIME1 = xRemainingTime;
        OPENTIME1 = (MOTOR1CLOSEPERIOD - CLOSETIME1)/CLOSECOEF1;
        xTimerStop (motor1CloseTimer, 10);
        stopMotor1();

        xRemainingTime = xTimerGetExpiryTime( motor2CloseTimer ) - xTaskGetTickCount();
        CLOSETIME2 = xRemainingTime;
        OPENTIME2 = (MOTOR2CLOSEPERIOD - CLOSETIME2)/CLOSECOEF2;
        xTimerStop (motor2CloseTimer, 10);
        stopMotor2();
        lampOFF();
        currentState = STOPED;
      }
      else if (element.value == REVERS && currentState == CLOSED){
        
      }
      else if (element.value == REVERS && currentState == STOPED){
        xTimerChangePeriod(motor1CloseTimer, CLOSETIME1, 10);
        closeMotor1();
        xTimerChangePeriod(motor2CloseTimer, CLOSETIME2, 10);
        closeMotor2();
        lampON();
        currentState = CLOSING;
        Leaf1State = MOVING;
        Leaf2State = MOVING;
        //vTaskDelay(MOTORSTARTDELAY / portTICK_PERIOD_MS);  //replace by timer
        xQueueReset(structQueue);
      }
      else if (element.value == REVERS && currentState == OPENING) {
        xRemainingTime = xTimerGetExpiryTime( motor1OpenTimer ) - xTaskGetTickCount();
        OPENTIME1 = xRemainingTime;
        CLOSETIME1 = (MOTOR1PERIOD - OPENTIME1)*CLOSECOEF1;
        xTimerStop (motor1OpenTimer, 10);
        stopMotor1();

        xRemainingTime = xTimerGetExpiryTime( motor2OpenTimer ) - xTaskGetTickCount();
        OPENTIME2 = xRemainingTime;
        CLOSETIME2 = (MOTOR2PERIOD - OPENTIME2)*CLOSECOEF2;
        xTimerStop (motor2OpenTimer, 10);
        stopMotor2();
        lampOFF();
        currentState = STOPED;
      }
      else if (element.value == REVERS && currentState == OPENED) {
        xTimerChangePeriod(motor2CloseTimer, CLOSETIME2, 10);
        closeMotor2();
        lampON();
        currentState = CLOSING;
        vTaskDelay(LEAFDELAY1 / portTICK_PERIOD_MS);// replace by timer
        xQueueReset(structQueue);

        xTimerChangePeriod(motor1CloseTimer, CLOSETIME1, 10);
        closeMotor1();    
        Leaf1State = MOVING;
        Leaf2State = MOVING;
        //vTaskDelay(MOTORSTARTDELAY / portTICK_PERIOD_MS);
        xQueueReset(structQueue);
      }
      else if (element.value == REVERS && currentState == CLOSING) {
        xRemainingTime = xTimerGetExpiryTime( motor1CloseTimer ) - xTaskGetTickCount();
        CLOSETIME1 = xRemainingTime;
        OPENTIME1 = (MOTOR1CLOSEPERIOD - CLOSETIME1)/CLOSECOEF1;
        xTimerStop (motor1CloseTimer, 10);
        stopMotor1();

        xRemainingTime = xTimerGetExpiryTime( motor2CloseTimer ) - xTaskGetTickCount();
        CLOSETIME2 = xRemainingTime;
        OPENTIME2 = (MOTOR2CLOSEPERIOD - CLOSETIME2)/CLOSECOEF2;
        xTimerStop (motor2CloseTimer, 10);
        stopMotor2();
        lampOFF();
        currentState = STOPED;
      }

      else if (element.value == OPEN_LEFT) {
        openMotor1();
      }
      else if (element.value == CLOSE_LEFT) {
        closeMotor1();
      }
      else if (element.value == STOP_LEFT) {
        stopMotor1();
      }

      else if (element.value == OPEN_RIGHT) {
        openMotor2();
      } 
      else if (element.value == CLOSE_RIGHT) {
        closeMotor2();
      }
      else if (element.value == STOP_RIGHT) {
        stopMotor2();
      };
    }
    else if (element.TaskType == TASKTIMER) {
      
/*      switch (element.value) {
              case OWERLOAD12:          // owercurrent due to obstacle
                         
                    digitalWrite(MOTOR1PIN1, HIGH);
                    digitalWrite(MOTOR1PIN2, HIGH);
                    digitalWrite(MOTOR2PIN1, HIGH);
                    digitalWrite(MOTOR2PIN2, HIGH);
                    digitalWrite(LAMPPIN, HIGH);
                    Leaf1State = STOPED;
                    Leaf2State = STOPED;
                    if ( currentState == OPENING ) {
                      currentState = OPENED;
                    }
                    else if ( currentState == CLOSING ) {
                      currentState = CLOSED;
                    };
              break;
              
              case OWERLOAD1:          // owercurrent due to obstacle
                         
                    digitalWrite(MOTOR1PIN1, HIGH);
                    digitalWrite(MOTOR1PIN2, HIGH);
                    Leaf1State = STOPED;
                    if ( currentState == OPENING && Leaf2State == STOPED ) {
                      currentState = OPENED;
                      digitalWrite(LAMPPIN, HIGH);
                    }
                    else if ( currentState == CLOSING && Leaf2State == STOPED ) {
                      currentState = CLOSED;
                      digitalWrite(LAMPPIN, HIGH);
                    };
                    
              break;
              
              case OWERLOAD2:          // owercurrent due to obstacle
                         
                    digitalWrite(MOTOR2PIN1, HIGH);
                    digitalWrite(MOTOR2PIN2, HIGH);
                    Leaf2State = STOPED;
                    if ( currentState == OPENING && Leaf1State == STOPED) {
                      currentState = OPENED;
                      digitalWrite(LAMPPIN, HIGH);
                    }
                    else if ( currentState == CLOSING && Leaf1State == STOPED ) {
                      currentState = CLOSED;
                      digitalWrite(LAMPPIN, HIGH);
                    };
              break;
                
              case NORMAL:          // 
              break;
      }
*/      
    };
    
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}
