#include <FreeRTOS_SAMD21.h>

#define READ_ANALOG_DELAY_MS 100
#define PROCESS_DATA_DELAY 50
#define UPLOAD_DATA_DELAY 50

QueueHandle_t Global_Queue_Handle = 0;
QueueHandle_t Message_Queue = 0;

void readAnalogStick(void* parameters){
  int values[2];

  while(true){
    values[0] = (analogRead(A1)*100)/1023;
    values[1] = (analogRead(A2)*100)/1023;
    xQueueSend(Global_Queue_Handle, &values, 1000);

    vTaskDelay(READ_ANALOG_DELAY_MS / portTICK_PERIOD_MS);
  }
}

void processData(void* parameters){
  String data;
  int rx_value[2];
  while(true){
    
    xQueueReceive(Global_Queue_Handle, &rx_value, 500);
    
    data = ((String("x1=")) + rx_value[0] + "&" +"y1=" + rx_value[1]);

    xQueueSend(Message_Queue, &data, 500);
    
    vTaskDelay( PROCESS_DATA_DELAY / portTICK_PERIOD_MS);
  }
}

void uploadData(void* parameters){
  String data = "Initial String";

  while(true){
    
    if(!diag.isWifiConnected()){
      wifiConnect();
    }
    xQueueReceive(Message_Queue, &data, 500);
    Serial.println(data);
    postRequest(data);


    vTaskDelay( UPLOAD_DATA_DELAY /portTICK_PERIOD_MS);  
  }
}

void FreeRTOS_INITIALIZE(){

  Global_Queue_Handle = xQueueCreate(5, 2*sizeof(int));
  Message_Queue = xQueueCreate(5, 20*sizeof(char));

  xTaskCreate(
        readAnalogStick, // Function to be called
        "Read Analog",   // Name of task
        512,            // Size of stack
        NULL,            // Parameters for function
        1,               // Task Priority
        NULL             // Task Handle (pointer)
    );

    xTaskCreate(
        uploadData,      // Function to be called
        "Uploading Data",   // Name of task
        512,            // Size of stack
        NULL,            // Parameters for function
        3,               // Task Priority
        NULL             // Task Handle (pointer)
    );

    xTaskCreate(
        processData, // Function to be called
        "Data Process",   // Name of task
        512,            // Size of stacOHk
        NULL,            // Parameters for function
        2,               // Task Priority
        NULL             // Task Handle (pointer)
    );

    vTaskStartScheduler();
}