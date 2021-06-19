#include "arduino_secrets.h" 
#include <WiFiNINA.h>

#define SERVER "192.168.1.106"
#define SERVER_PORT 5000
#define CONTENT_TYPE "Content-type: application/x-www-form-urlencoded"

WiFiClient client;

class diagnostic{
    public:
        void checkWifiStatus();
        bool isWifiConnected();
        void printWifiStatus();
        void checkWifiVersion();
} diag;

bool diagnostic::isWifiConnected(){
  if(WiFi.status() == WL_CONNECTED){
    return true;
  }
  else
    return false;
}

void diagnostic::checkWifiStatus(){
    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        // don't continue
         //diag.checkWifiStatus();
    }
}

void diagnostic::printWifiStatus(){
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your board's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
} 

void diagnostic::checkWifiVersion(){
    String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
}

void wifiConnect(){
    int status = WL_IDLE_STATUS;
    Serial.println("Connecting...");
     // attempt to connect to WiFi network:
    while (status != WL_CONNECTED) {
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(SECRET_SSID, SECRET_PASS);
    }
    Serial.println("Connected to WiFi");
}

void postRequest(String postData){

    if (client.connect(SERVER, SERVER_PORT)) {
    
    String dataLength = String("Content-Length: ") + postData.length() + "\r\n";
    // Make a HTTP request:
    client.println("POST / HTTP/1.1");
    client.println("Host: 192.168.1.106");    
    client.println("Connection: close");

    client.println(CONTENT_TYPE);
    client.println(dataLength);
    client.print(postData);
  }
  else{

  } 
}

void displayResponse(){

  // if there are incoming bytes available
  // from the server, read them and print them:
  
  //Serial.println("=================================");
  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }
  //Serial.println("\n=================================");
  
}

