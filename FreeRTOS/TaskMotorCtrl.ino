const char OPENING = 'd';
const char OPENED = 'e';
const char CLOSING = 'f';
const char CLOSED = 'g';
const char STOPED = 'j';
const char STOPED1 = 'k';
const char STOPED2 = 'l';
const char MOVING = 'l';
const int LEAFDELAY = 3000; //ms delay beetvin leaf opening

void TaskMotorCtrl( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  struct sensor element;
  
  char currentState = STOPED;
  char Leaf1State = MOVING;
  char Leaf2State = MOVING;
  
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
      Serial.println("TaskMotorCtrl");
      Serial.print("currentState: ");
      Serial.println(currentState);
 
      Serial.println("----------------");
      
    xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    };
    
    if (element.TaskType == TASKRF) {
      if (element.value == START && currentState == CLOSED){
        digitalWrite(MOTOR1PIN1, LOW);
        digitalWrite(MOTOR1PIN2, HIGH);
        vTaskDelay(LEAFDELAY / portTICK_PERIOD_MS);
        digitalWrite(MOTOR2PIN1, LOW);
        digitalWrite(MOTOR2PIN2, HIGH);
        currentState = OPENING;
        Leaf1State = MOVING;
        Leaf2State = MOVING;
      }
      else if (element.value == START && currentState == OPENING) {
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, HIGH);
        currentState = STOPED;
      }
      else if (element.value == START && currentState == STOPED) {
        digitalWrite(MOTOR1PIN1, LOW);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, LOW);
        digitalWrite(MOTOR2PIN2, HIGH);
        currentState = OPENING;
        Leaf1State = MOVING;
        Leaf2State = MOVING;
      }
      else if (element.value == START && currentState == OPENED) {
        
      }
      else if (element.value == START && currentState == CLOSING) {
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, HIGH);
        currentState = STOPED;
      }
      else if (element.value == REVERS && currentState == CLOSED){
        
      }
      else if (element.value == REVERS && currentState == STOPED){
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, LOW);
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, LOW);
        currentState = CLOSING;
        Leaf1State = MOVING;
        Leaf2State = MOVING;
      }
      else if (element.value == REVERS && currentState == OPENING) {
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, HIGH);
        currentState = STOPED;
      }
      else if (element.value == REVERS && currentState == OPENED) {
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, LOW);
        vTaskDelay(LEAFDELAY / portTICK_PERIOD_MS);
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, LOW);
        currentState = CLOSING;
        Leaf1State = MOVING;
        Leaf2State = MOVING;
      }
      else if (element.value == REVERS && currentState == CLOSING) {
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, HIGH);
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
                    }
                    else if ( currentState == CLOSING && Leaf2State == STOPED ) {
                      currentState = CLOSED;
                    };
                    
              break;
              
              case OWERLOAD2:          // owercurrent due to obstacle
                         
                    digitalWrite(MOTOR2PIN1, HIGH);
                    digitalWrite(MOTOR2PIN2, HIGH);
                    Leaf2State = STOPED;
                    if ( currentState == OPENING && Leaf1State == STOPED) {
                      currentState = OPENED;
                    }
                    else if ( currentState == CLOSING && Leaf1State == STOPED ) {
                      currentState = CLOSED;
                    };
              break;
                
              case NORMAL:          // 
              break;
      }
      
    };
    
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}
