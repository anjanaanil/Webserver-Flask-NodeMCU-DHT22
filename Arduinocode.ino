#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>;
#include <ArduinoJson.h>

#define DHTPIN 5     // what pin we're connected to
#define DHTTYPE DHT22

const char* ssid = "*****";//enter your wifi name
const char* password = "*****"; //enter your wifi password
 
DHT dht(DHTPIN, DHTTYPE);

StaticJsonDocument<100> jsonDoc;
JsonObject payload = jsonDoc.to<JsonObject>();
JsonObject status = payload.createNestedObject("d");
static char msg[50];

float hum = 0.0;  //Stores humidity value
float temp = 0.0; //Stores temperature value

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
 
  }
  Serial.println("Connected to WiFi Network");
  dht.begin();
}

void loop() {
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
    
    HTTPClient http;  //Declare an object of class HTTPClient
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");

    status["temperature"] = temp;
    status["humidity"] = hum;
    serializeJson(jsonDoc, msg, 50);
    Serial.println(msg);
    
    http.begin("http://(your ip address):8090"); //Specify request destination
    http.addHeader("Content-Type", "application/json"); 
    
    int httpCode = http.POST(msg);
    Serial.println(httpCode);
    //String payload = http.getString();
    //Serial.println(payload);
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
 
    }
    else {
    Serial.println("An error occurred");}
 
    http.end();   //Close connection
 
  }

  delay(10000);

}
