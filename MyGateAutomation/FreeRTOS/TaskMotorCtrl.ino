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
const int LEAFDELAY = 3000; //ms delay beetvin leaf opening
const int LEAFDELAY1 = 3000; //ms delay beetvin leaf closing
const int MOTORSTARTDELAY = 3000; //ms delay beetvin leaf opening

void TaskMotorCtrl( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  struct sensor element;
  //struct sensor mySensor;
  //char value;  
  //mySensor.TaskType = TASKMOTORCTRL;
  
  char currentState = STOPED;
  char Leaf1State = MOVING;
  char Leaf2State = MOVING;
  int led = LOW;
  
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
      //Serial.print("currentState: ");
      Serial.println(currentState);
 
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
        
        digitalWrite(MOTOR1PIN1, LOW);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(LAMPPIN, LOW);
        Leaf1State = MOVING;
        currentState = OPENING;
        vTaskDelay(LEAFDELAY / portTICK_PERIOD_MS);
        xQueueReset(structQueue);
        digitalWrite(MOTOR2PIN1, LOW);
        digitalWrite(MOTOR2PIN2, HIGH);             
        Leaf2State = MOVING;
        vTaskDelay(MOTORSTARTDELAY / portTICK_PERIOD_MS);
        xQueueReset(structQueue);
      }
      else if (element.value == START && currentState == OPENING) {
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, HIGH);
        digitalWrite(LAMPPIN, HIGH);
        currentState = STOPED;
      }
      else if (element.value == START && currentState == STOPED) {
        digitalWrite(MOTOR1PIN1, LOW);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, LOW);
        digitalWrite(MOTOR2PIN2, HIGH);
        digitalWrite(LAMPPIN, LOW);
        currentState = OPENING;
        Leaf1State = MOVING;
        Leaf2State = MOVING;
        vTaskDelay(MOTORSTARTDELAY / portTICK_PERIOD_MS);
        xQueueReset(structQueue);
      }
      else if (element.value == START && currentState == OPENED) {
        
      }
      else if (element.value == START && currentState == CLOSING) {
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, HIGH);
        digitalWrite(LAMPPIN, HIGH);
        currentState = STOPED;
      }
      else if (element.value == REVERS && currentState == CLOSED){
        
      }
      else if (element.value == REVERS && currentState == STOPED){
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, LOW);
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, LOW);
        digitalWrite(LAMPPIN, LOW);
        currentState = CLOSING;
        Leaf1State = MOVING;
        Leaf2State = MOVING;
        vTaskDelay(MOTORSTARTDELAY / portTICK_PERIOD_MS);
        xQueueReset(structQueue);
      }
      else if (element.value == REVERS && currentState == OPENING) {
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, HIGH);
        digitalWrite(LAMPPIN, HIGH);
        currentState = STOPED;
      }
      else if (element.value == REVERS && currentState == OPENED) {
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, LOW);
        digitalWrite(LAMPPIN, LOW);
        currentState = CLOSING;
        vTaskDelay(LEAFDELAY1 / portTICK_PERIOD_MS);
        xQueueReset(structQueue);
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, LOW);        
        Leaf1State = MOVING;
        Leaf2State = MOVING;
        vTaskDelay(MOTORSTARTDELAY / portTICK_PERIOD_MS);
        xQueueReset(structQueue);
      }
      else if (element.value == REVERS && currentState == CLOSING) {
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, HIGH);
        digitalWrite(LAMPPIN, HIGH);
        currentState = STOPED;
      };             
    }
    else if (element.TaskType == TASKANALOG) {
      
      switch (element.value) {
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
      
    };
    
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}
