# The application shows messages sent by an http request on display

<!-- ![alt text](pic.png "Title") -->

<img src="pic.png" style="width:700px;height:500px;"><br><br>

## Can be used with

[microservice-investiment](https://github.com/marcelbraghini/microservice-investiment)

## Post example

```bash
curl --location --request POST 'http://1.1.1.1/message' \
--header 'Content-Type: application/json' \
--data-raw '{"headerText":"Boa Noite!", "bodyText":"=)", "key":"myKey"}'
```

## Requirements

* NodeMCU
* Display LCD 16×2
* Interface de I2C para Display LCD (16X2 / 20X4)
* IDE for development (https://www.arduino.cc/en/software)
* Check and install necessary libs
<br><Wire.h>
<br><WiFiClient.h>
<br><ArduinoJson.h>
<br><ESP8266WiFi.h>
<br><ESP8266WebServer.h>
<br><LiquidCrystal_I2C.h>

## Scheme

<br><img src="nodemcu_display_lcd_16x2_interface_i2c.png" style="width:700px;height:500px;"><br><br>
