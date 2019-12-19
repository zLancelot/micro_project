//Programa: Bot Telegram com ESP8266 NodeMCU
//Autor: Arduino e Cia

#include "CTBot.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>


CTBot myBot;

//Definicoes da rede wifi e conexao
String ssid  = "Lancelot"; //Nome da sua rede wifi
String pass  = "87654321"; //Senha da sua rede wifi
String token = "978440572:AAHqTNTN79X_VyLjgu7f230vVuC5VsICfMQ"; //Token bot Telegram

//Pinos dos leds
uint8_t lamp = D0;
bool acesa = false;
unsigned long int tempo;


void setup()
{
  Serial.begin(115200);
  Serial.println("Inicializando bot Telegram...");

  //Conexao na rede wifi
  myBot.wifiConnect(ssid, pass);

  //Define o token
  myBot.setTelegramToken(token);

  //Verifica a conexao
  if (myBot.testConnection())
    Serial.println("nConexao Ok!");
  else
    Serial.println("nFalha na conexao!");

  //Define os pinos dos leds como saida e apaga os leds
  pinMode(lamp, OUTPUT);
  digitalWrite(lamp, HIGH);

}

void loop()
{
  
  HTTPClient http;  //Declare an object of class HTTPClient

  //Variavel que armazena a mensagem recebida
  TBMessage msg;

  //Verifica se chegou alguma mensagem
  if (myBot.getNewMessage(msg))
  {

    //Verifica se foi recebia a mensagem "Liga 1"
    if (msg.text.equalsIgnoreCase("acender"))
    {
      if (not acesa){
          tempo = millis();
          acesa = true;
          
          digitalWrite(lamp, LOW);
          //Retorna uma pensagem informando que o led foi aceso
          myBot.sendMessage(msg.sender.id, "Lampada acendeu!");
      
      }

    }
    else if (msg.text.equalsIgnoreCase("apagar"))
    {
      if (acesa){
          acesa = false;
          
          digitalWrite(lamp, HIGH);
          myBot.sendMessage(msg.sender.id, "Lampada apagou!");
          
           StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
          JsonObject& JSONencoder = JSONbuffer.createObject(); 
       
          JSONencoder["consumption"] = tempo/1000;

          Serial.println(tempo);
       
          char JSONmessageBuffer[300];
          JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      
      
          http.begin("http://8900b621.ngrok.io/consumptions");  //Specify request destination
      
          http.addHeader("Content-Type", "application/json");  //Specify content-type header
      
          int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    
          if (httpCode > 0) { //Check the returning code
            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);                     //Print the response payload
    
          } 
      
      }


    }
    else if (msg.text.equalsIgnoreCase("consumo")) {
      http.begin("http://8900b621.ngrok.io/consumptions");  //Specify request destination
      int httpCode = http.GET();  //Send the request

      if (httpCode > 0) { //Check the returning code
        // Parsing  
        String payload = http.getString();
        
        
        myBot.sendMessage(msg.sender.id, (String)payload);
      }

    }
    else
    {
      //Caso receba qualquer outro comando, envia uma
      //mensagem generica/informativa
      String reply;
      reply = (String)"Ola " + msg.sender.username + (String)". Tente os comandos: [acender, apagar, consumo]";

    }
  }
  delay(500);
}
