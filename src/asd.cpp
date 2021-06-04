#include <SPI.h>
#include <FreeRTOS_SAMD21.h>

#include <wifi_functions.cpp>

#include "mcu_setup.cpp"
#include "initialize.cpp"

void readAnalogStick(void* parameters){
  int x1 = 0;
  int y1 = 0;
  int count = 0;
  String data ="x=";
  while(true){
    x1 += (analogRead(A1));//*100)/1023;
    //int y1 = (analogRead(A2));//*100)/1023;
    //int x2 = (analogRead(A1));//*100)/1023;
    y1 += (analogRead(A2));//*100)/1023;
    count++;
    if (count > 3){
        x1 = (int)x1/4;
        y1 = (int)y1/4;
        data = ((String("x1=")) + x1 + "&" +"y1=" + y1);

        // Serial.print(x1);
        // Serial.print("% ");
        // Serial.print(y1);
        // Serial.println("% ");
        //Serial.println(data);
        postRequest(data);
        x1 = y1 = 0;
        count = 0;
        

    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void wifiCheck(void* parameters){
  while(true){

    if(diag.isWifiConnected()){
      Serial.println("Wifi Still here:)");
      vTaskDelay(10000/portTICK_PERIOD_MS);
      continue;
    }

    wifiConnect();
      
  }
}

void FreeRTOS_INITIALIZE(){

  xTaskCreate(
        readAnalogStick, // Function to be called
        "Read Analog",   // Name of task
        1024,            // Size of stack
        NULL,            // Parameters for function
        1,               // Task Priority
        NULL             // Task Handle (pointer)
    );

    xTaskCreate(
        wifiCheck, // Function to be called
        "Wifi Check",   // Name of task
        1024,            // Size of stack
        NULL,            // Parameters for function
        1,               // Task Priority
        NULL             // Task Handle (pointer)
    );

    vTaskStartScheduler();
}

void SYSTEM_INITIALIZE(){

    //adc.setup();
    //adc.configure();
    //analogPinSetup();

    wifiConnect();
    FreeRTOS_INITIALIZE();
}

void setup(){
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  while(!Serial){
  }

  Serial.println("Initializing");
  SYSTEM_INITIALIZE();
  Serial.println("Initialized");

}

void loop() {
  
}


