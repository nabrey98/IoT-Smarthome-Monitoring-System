#include <ESP8266WiFi.h>
//versi nodemcu yg digunakan harus 5.13.5 atau dibawahnya
#include "CTBot.h"
CTBot myBot;
 
String ssid  = "padmono";
String pass  = "Reyhan1904";
String token = "1019053438:AAFqkg3K9YHnDLk1v2Bam5SRU1shhpMweZM";
const int id = 1268562154; 

const int relay[4]={14,12,13,15};
bool On = LOW;
bool Off = HIGH;
String orderOn[4] = {"relay 1 on", "relay 2 on", "relay 3 on", "relay 4 on"};
String orderOff[4] = {"relay 1 off", "relay 2 off", "relay 3 off", "relay 4 off"};
 
void setup() {
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");
 
  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);
 
  // set the telegram bot token
  myBot.setTelegramToken(token);
 
  // check if all things are ok
  if (myBot.testConnection()){
    Serial.println("\ntestConnection OK");
    myBot.sendMessage(id, "Connection OK");
  }
  else {
    Serial.println("\ntestConnection NOK");
    myBot.sendMessage(id, "Connection NOK");
  }
 
  // set the pin connected to the RELAY to act as output pin turn off condition
  for(int i=0; i<=3; i++){
    pinMode(relay[i], OUTPUT);
  }
  for(int i=0; i<=3; i++){
    digitalWrite(relay[i], Off);
  }
}
 
void loop() {
    
  // a variable to store telegram message data
  TBMessage msg;
  if (myBot.getNewMessage(msg)){
    for (int i=0; i<=3; i++){
      if (msg.text.equalsIgnoreCase(orderOn[i])) {
        digitalWrite(relay[i], On);
        myBot.sendMessage(msg.sender.id, orderOn[i] );
      }
      else if (msg.text.equalsIgnoreCase(orderOff[i])){
        digitalWrite(relay[i], Off);
        myBot.sendMessage(msg.sender.id, orderOff[i] );
      }
      else if (msg.text.equalsIgnoreCase("all on")){
        digitalWrite(relay[i], On);
        myBot.sendMessage(msg.sender.id, orderOn[i] );
      }
      else if (msg.text.equalsIgnoreCase("all Off")){
        digitalWrite(relay[i], Off);
        myBot.sendMessage(msg.sender.id, orderOff[i] );
      }    
      else {                                                
  // generate the message for the sender
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". Try LIGHT ON or LIGHT OFF.";
      myBot.sendMessage(msg.sender.id, reply);

    }
  }
   // wait 10 milliseconds
  delay(10);
  }
}
