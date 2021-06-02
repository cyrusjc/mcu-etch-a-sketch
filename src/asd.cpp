#include <SPI.h>
#include <WiFiNINA.h>

#include "wifi_functions.h"

void postRequest(String);
void displayResponse();

//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
//char server[] = "192.168.1.106";    // name address for Google (using DNS)
// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):

void setup(){
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  //diag.checkWifiStatus();
  //diag.checkWifiVersion();

  wifiConnect();
  //Serial.println("Connected to WiFi");
  //diag.printWifiStatus();
  //Serial.println("\nStarting connection to server...")

}

void loop() {
  postRequest("swag=swag, cyrus=cyrus");

}






