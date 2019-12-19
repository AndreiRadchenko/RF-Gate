const char OPENING = 'd';
const char OPENED = 'e';
const char CLOSING = 'f';
const char CLOSED = 'g';
const char STOPED = 'j';
const int LEAFDELAY = 3000; //ms delay beetvin leaf opening
char prevGateState = 'J';

void TaskMotorCtrl( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  struct sensor element;
  char currentState = STOPED;
  bool motor_1_ForwardEnable;
  bool motor_1_ReversEnable;
  bool motor_2_ForwardEnable;
  bool motor_2_ReversEnable;

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
 
      Serial.print("GPIO: ");
      Serial.println(prevGateState);
 
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
      }
      else if (element.value == REVERS && currentState == CLOSING) {
        digitalWrite(MOTOR1PIN1, HIGH);
        digitalWrite(MOTOR1PIN2, HIGH);
        digitalWrite(MOTOR2PIN1, HIGH);
        digitalWrite(MOTOR2PIN2, HIGH);
        currentState = STOPED;
      };             
    }
    else if (element.TaskType == TASKDIGITAL) {
      
/*          if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
            {
              Serial.println("TaskMotorCtrl");
              Serial.print("TaskType: ");
              Serial.println(element.TaskType);
         
              Serial.print("Value: ");
              Serial.println(element.value);
         
              Serial.println("----------------");
              
            xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
            };
*/            
          switch (element.value) {
              case 'J':          // gate closed
                    
                if ( currentState == CLOSING) {            
                    digitalWrite(MOTOR1PIN1, HIGH);
                    digitalWrite(MOTOR1PIN2, HIGH);
                    digitalWrite(MOTOR2PIN1, HIGH);
                    digitalWrite(MOTOR2PIN2, HIGH);
                    currentState = CLOSED;
                };
                break;
                
              case 'E':          // gate opened
              
                if ( currentState == OPENING) {            
                    digitalWrite(MOTOR1PIN1, HIGH);
                    digitalWrite(MOTOR1PIN2, HIGH);
                    digitalWrite(MOTOR2PIN1, HIGH);
                    digitalWrite(MOTOR2PIN2, HIGH);
                    currentState = OPENED;
                };
                break;
                
              case 'N':          // first leaf opening, second closed
              
                if ( currentState == CLOSING) {
                    digitalWrite(MOTOR2PIN1, HIGH);
                    digitalWrite(MOTOR2PIN2, HIGH);
                };
                break;
                
              case 'O':          // gate opening
                // statements
                break;
                
              case 'G':          // first leaf opened, second opening 
              
                if ( currentState == OPENING) {            
                    digitalWrite(MOTOR1PIN1, HIGH);
                    digitalWrite(MOTOR1PIN2, HIGH);
                };
                break;
                        
              default:
                // statements
                break;
            };
            
          prevGateState = element.value;    
    }
    else if (element.TaskType == TASKANALOG) {
      
      switch (element.value) {
              case OWERLOAD:          // owercurrent due to obstacle
                         
                    digitalWrite(MOTOR1PIN1, HIGH);
                    digitalWrite(MOTOR1PIN2, HIGH);
                    digitalWrite(MOTOR2PIN1, HIGH);
                    digitalWrite(MOTOR2PIN2, HIGH);
                    currentState = STOPED;
              break;
                
              case NORMAL:          // 
              break;
      }
      
    };
    
    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}
