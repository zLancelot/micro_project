//Programa: Bot Telegram com ESP8266 NodeMCU
//Autor: Arduino e Cia

#include "CTBot.h"
CTBot myBot;

//Definicoes da rede wifi e conexao
String ssid  = "Lancelot"; //Nome da sua rede wifi
String pass  = "87654321"; //Senha da sua rede wifi
String token = "978440572:AAHqTNTN79X_VyLjgu7f230vVuC5VsICfMQ"; //Token bot Telegram

//Pinos dos leds
uint8_t lamp = D0;

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
  pinMode(led1, OUTPUT);
  digitalWrite(led1, HIGH);
 
}

void loop()
{  
   unsigned long int tempo = 0;

    Serial.println(tempo);

  //Variavel que armazena a mensagem recebida
  TBMessage msg;

  //Verifica se chegou alguma mensagem
  if (myBot.getNewMessage(msg))
  {

    //Verifica se foi recebia a mensagem "Liga 1"
    if (msg.text.equalsIgnoreCase("acender"))
    {
      tempo = millis();
      Serial.println(tempo);
      
      digitalWrite(lamp, LOW);
      //Retorna uma pensagem informando que o led foi aceso
      myBot.sendMessage(msg.sender.id, "Lampada acendeu!");
    }
    else if (msg.text.equalsIgnoreCase("apagar"))
    {
      Serial.println(millis());
      Serial.println(tempo/60000);
      
      digitalWrite(lamp, HIGH);
      myBot.sendMessage(msg.sender.id, "Lampada apagou!");
    }
    else if (msg.txt.equalsIgnoreCase("consumo")){
        
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
