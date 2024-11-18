#include <ESP8266WiFi.h>

const char* ssid = "car";
const char* password = "123456789";
bool firstConnect = true;
IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

WiFiServer server(80);
WiFiClient persistentClient;

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);
  
  server.begin();
}

void loop() {
  if (!persistentClient.connected()) {
    persistentClient = server.available();
  }
  
  if (persistentClient && persistentClient.available()) {
    if(firstConnect){
      Serial.println("Ready");
      firstConnect = false;
    }

    String data = persistentClient.readStringUntil('\n');
    data.trim();
    
    if (data.length() > 0 && !data.startsWith("GET") && !data.startsWith("User")&& !data.startsWith("Host")&& !data.startsWith("Accept")&& !data.startsWith("Connection")) {
      Serial.println(data);
    }
  }
}