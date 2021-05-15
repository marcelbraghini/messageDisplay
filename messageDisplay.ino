/*
 * The application shows messages sent by an http request on display
 *
 * curl --location --request POST '192.168.0.1/message' \
 * --header 'Content-Type: application/json' \
 * --data-raw '{"headerText":"Dollar", "bodyText":"R$ 5.80", "key":"myKey"}'
 */
#include <Wire.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>

//Lib to the display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//Necessary changes in environment variables
String key = "xxx";
const char* ssid = "xxx";
const char* password = "xxx";

//Set to the webservice response in port 80
ESP8266WebServer server(80);

void setup(void){

  //Call conection
  connectIn();

  //Health check
  server.on("/", [](){
    server.send(200, "text/html", "OK");
  });

  //Port to receive messages
  server.on("/message", bodyMessage);

  server.begin();
  showMessage(ssid, WiFi.localIP().toString());
  Serial.println("Message system started!");
}

void loop(void){
  server.handleClient();
}

void bodyMessage() {
      if (server.hasArg("plain") == false){
            server.send(422, "application/json", "{'message':'Body not received'}");
            return;
      }

      DynamicJsonDocument doc(1024);
      deserializeJson(doc, server.arg("plain"));

      const char* keyReceived = doc["key"];

      if (String(keyReceived) == key) {

            String headerText = doc["headerText"];
            String bodyText = doc["bodyText"];

            Serial.println(server.arg("plain"));

            showMessage(headerText, bodyText);

            server.send(200, "application/json", server.arg("plain"));
      } else {
            server.send(401, "application/json", "{'message':'Not authorized'}");
            return;
      }
}

void showMessage(String headerText, String bodyText) {
      lcd.init();
      lcd.backlight();
      lcd.setCursor(0, 0);
      lcd.print(headerText);
      lcd.setCursor(0, 1);
      lcd.print(bodyText);
}

void connectIn() {
      delay(1000);
      Serial.begin(115200);
      WiFi.begin(ssid, password);
      Serial.println("");

      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(". ");
      }

      Serial.println("");
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
}
