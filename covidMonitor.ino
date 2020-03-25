
// CovidMonitor.ino
// Roni Bandini
// @RoniBandini

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>

 
const char* ssid = "YourSSIDHere";
const char* password = "YourPassHere";

String pCases="";
String pDegrees="";
String pDeaths="";
String pDRate="";

Servo servo;

void setup () { 
      
      servo.attach(2); //D4

      // move to zero position
      servo.write(180);     
  

      Serial.begin(115200);
      WiFi.begin(ssid, password);
       
      while (WiFi.status() != WL_CONNECTED) {
       
      delay(1000);
      Serial.print("Connecting..");
       
}
 
}
 
void loop() {
 
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    Serial.print("Servo 0");
    servo.write(180);
     
    HTTPClient http;   
     
    http.begin("http://YourPHPServerHere/coronaFeed.php");   
    int httpCode = http.GET();                                                                   
     
    if (httpCode > 0) { //Check the returning code
     
        String payload = http.getString();    
        Serial.println(payload);             

        pCases         = getValue(payload, '#', 0); 
        pDegrees       = getValue(payload, '#', 4); 
        pDeaths       = getValue(payload, '#', 2);
        pDRate        = getValue(payload, '#', 3); 

        Serial.print("Cases: ");
        Serial.println(pCases);

        Serial.print("Degrees: ");
        Serial.println(pDegrees);

        
        Serial.print("Move servo");
        servo.write(pDegrees.toInt());               
        
         
    }
     
    http.end();   //Close connection
     
    }

     
    delay(120000);    //Send a request every 30 seconds
 
}

String getValue(String data, char separator, int index)
{  
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
} 
