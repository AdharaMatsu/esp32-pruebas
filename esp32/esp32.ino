#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "***********";
const char* password = "*****";
const int id = 1;
void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://apigps-f8eb80530580.herokuapp.com/api/location?id="+id;
    http.begin(url); 
    
    http.addHeader("Content-Type", "application/json");
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["lat"] = "**.*******";
    root["lon"] = "**.*******";
    char json_str[100];
    root.prettyPrintTo(json_str,sizeof(json_str));

    int httpCode = http.POST(json_str);
    
    if (httpCode > 0) {
      Serial.println("Envío exitoso");
    } else {
      Serial.println("Error en la solicitud HTTP");
    }
  
    http.end();
  }
  delay(5000); 
}
