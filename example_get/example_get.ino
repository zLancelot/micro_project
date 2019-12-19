#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

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

    HTTPClient http;  //Declare an object of class HTTPClient

    http.begin("http://d47acae1.ngrok.io/consumptions");  //Specify request destination
    int httpCode = http.GET();  //Send the request
  
    Serial.println(httpCode);


    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }

    http.end();   //Close connection

  }

  delay(30000);    //Send a request every 30 seconds

}
