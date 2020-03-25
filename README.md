# CoronavirusAnalogMonitor
Analog monitor with SG90 servo and ESP8266

Complete instructions can be found at https://www.hackster.io/roni-bandini 

Requirements:
. ESP8266
. SG90 Servo
. Web server with PHP

To avoid issues with https, the ESP8266 code will get Coronavirus cases with http from the PHP web. The php script must be placed there. SSID and web server must be edited before uploading

const char* ssid = "YourSSIDHere";
const char* password = "YourPassHere";

http.begin("http://YourPHPServerHere/coronaFeed.php");   
