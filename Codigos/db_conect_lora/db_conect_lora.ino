#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "Arduino.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(D3, D2);
//#include <Wire.h>

const char* ssid     = "Mateus";
const char* password = "gts5830c";



//const char* ssid     = "Vivo-Internet-1257";
//const char* password = "FF6E7D60";



//const char* ssid     = "iPhone do Tui";
//const char* password = "123456788";




const char* serverName = "http://tensiometro.artechengenharia.com.br/post-sensor-data.php";
// Example: http://xxx.com/esp_hcsr04_php_post.php
String apiKeyValue = "tPmAT5Ab3j7F9";


void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  Serial.begin(115200);
  mySerial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}
void loop() {



  if (WiFi.status() == WL_CONNECTED) {
    if (mySerial.available())
    {
      //Serial.println((char)mySerial.read());

      /* String conteudo = "";
        char caractere;

        while (mySerial.available() > 0) {
         // Lê byte da serial
         caractere = mySerial.read();
         // Ignora caractere de quebra de linha
         if (caractere != '\n') {
           // Concatena valores
           conteudo.concat(caractere);
         }
        }*/
      String pressao = "";

      String dados[3];
      String msg_serial = mySerial.readString();
      char myString[50];
      msg_serial.toCharArray(myString, 50);
      if (myString[0] == '#' && myString[msg_serial.length() - 3] == '#')
      {
        int str_ind = 0;
        for ( int l = 1; l < msg_serial.length() - 3; l++)
        {
          if (myString[l] == '*')
          {
            str_ind++;
          }
          else if (myString[l] == '#')
          {
            break;
          }
          else
          {
            dados[str_ind].concat(myString[l]);
          }
        }



      }


      String pressao1 = (String)dados[0];
      String pressao2 = (String)dados[1];
      String v_bat = (String)dados[2];


      //Serial.println(pressao1);
      //Serial.println(pressao2);
      //Serial.println(v_bat);
      // Serial.println("");
      //radio.read(&pressao, sizeof(pressao));
      //Serial.print(msg_serial.length());
      //Serial.println(msg_serial);


      WiFiClient client;
      HTTPClient http;
      http.begin( client, serverName);

      //http.addHeader("Content-Type", "application/json");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Prepare your HTTP POST request data
      String httpRequestData = "api_key=" + apiKeyValue + "&data_leitura=" + "1610/2021" + "&hora_leitura=" + "10:20:30" +
                               "&pressao_leitura_1=" + pressao1 + "&pressao_leitura_2=" + pressao2 + "&V_bat=" + v_bat ;
      //String httpRequestData = "api_key=theiotprojects&sensor=HC-SR04&location=Home&distance=24.75";
      Serial.print("httpRequestData: ");
      Serial.println(httpRequestData);
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();

    }
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 20 seconds
  delay(1);
}
