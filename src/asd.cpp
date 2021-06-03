#include <SPI.h>
#include <WiFiNINA.h>

#include <FreeRTOS_SAMD21.h>

#include "mcu_setup.h"
#include "wifi_functions.h"

void setup(){
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while(!Serial){

  }
  //diag.checkWifiStatus();
  //diag.checkWifiVersion();

  wifiConnect();
  //diag.printWifiStatus();

  //adc.setup();
  //adc.configure();

  //analogPinSetup();

}

void loop() {

  readAnalog();

  delay(100);

}






