//Programa: Bot Telegram com ESP8266 NodeMCU
//Autor: Arduino e Cia

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//Definicoes da rede wifi e conexao
String ssid  = "Lancelot"; //Nome da sua rede wifi
String pass  = "87654321"; //Senha da sua rede wifi
String token = "978440572:AAHqTNTN79X_VyLjgu7f230vVuC5VsICfMQ"; //Token bot Telegram

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }
  Serial.print("Successful Conection");
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject(); 
 
    JSONencoder["consumption"] = 840;
 
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
    

    HTTPClient http;  //Declare an object of class HTTPClient

    http.begin("http://d47acae1.ngrok.io/consumptions");  //Specify request destination
  //int httpCode = http.GET();  //Send the request

    http.addHeader("Content-Type", "application/json");  //Specify content-type header

    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
 

    Serial.println(httpCode);


    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }

    http.end();   //Close connection

  }

  delay(30000);    //Send a request every 30 seconds

}
