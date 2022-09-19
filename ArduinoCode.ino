#include <Arduino_FreeRTOS.h>
#include<LiquidCrystal.h>
//Define LCD pins
LiquidCrystal lcd (7,6,5,4,3,2); //RS, E, D4, D5, D6, D7

//global variables
int counter = 0;

// Tasks declaration
void TaskBlink1( void *pvParameters );
void TaskBlink2( void *pvParameters );
void TaskBlink3( void *pvParameters );
void TaskLcd( void *pvParameters );
void Taskprint( void *pvParameters );

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  lcd.begin(20, 4);  // Enable LCD library

  xTaskCreate(

    TaskBlink1

    ,  "task1"   
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );

  xTaskCreate(

    TaskBlink2
    ,  "task2"
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );

  xTaskCreate(

    TaskBlink3
    ,  "task3"
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );

  xTaskCreate(      // Dodan dispay data task

    TaskLcd
    ,  "Displaydata"
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );
    
    xTaskCreate(

    Taskprint
    ,  "task3"
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );
vTaskStartScheduler();
}

void loop(){}

// Tasks implementation

void TaskBlink1(void *pvParameters)  {

  pinMode(13, OUTPUT);
  while(1)
  {
    Serial.println("Task1");
    digitalWrite(13, HIGH);   
    vTaskDelay( 200 / portTICK_PERIOD_MS ); 
    digitalWrite(13, LOW);    
    vTaskDelay( 200 / portTICK_PERIOD_MS ); 
  }
}

void TaskBlink2(void *pvParameters)  
{
  pinMode(12, OUTPUT);
  while(1)
  {
    Serial.println("Task2");
    digitalWrite(12, HIGH);   
    vTaskDelay( 300 / portTICK_PERIOD_MS ); 
    digitalWrite(12, LOW);   
    vTaskDelay( 300 / portTICK_PERIOD_MS ); 
  }
}

void TaskBlink3(void *pvParameters)  
{
  pinMode(11, OUTPUT);
  while(1)
  {
    Serial.println("Task3");
    digitalWrite(11, HIGH);   
    vTaskDelay( 300 / portTICK_PERIOD_MS ); 
    digitalWrite(11, LOW);   
    vTaskDelay( 300 / portTICK_PERIOD_MS ); 
  }
}

void TaskLcd(void * pvParameters)
{
  (void) pvParameters;
  
  for (;;) 
  {
    lcd.setCursor(0, 0);        // Za 1 task
    lcd.print("Task1,blue light");

    lcd.setCursor(0, 1);        // Za 2 task
    lcd.print("Task2,green light");
    
    lcd.setCursor(0, 2);        // Za 3 task
    lcd.print("Task3,yellow light");

    lcd.setCursor(0, 3);        // Za 4 task
    lcd.print("Counter : ");
    lcd.print(counter);

    lcd.clear();
  }
}

void Taskprint(void *pvParameters)  {

  while(1)
  {
counter++;
  Serial.println(counter); 
  vTaskDelay(500 / portTICK_PERIOD_MS);    }
}
