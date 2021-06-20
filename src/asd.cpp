#include <SPI.h>
#include <FreeRTOS_SAMD21.h>

#include <wifi_functions.cpp>

#include "mcu_setup.cpp"
#include "initialize.cpp"
#include "Tasks.h"

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
  SYSTEM_INITIALIZE();

}

void loop() {
}


