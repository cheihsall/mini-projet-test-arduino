/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp32-http-post-ifttt-thingspeak-arduino/ 

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "itel A25 Pr";
const char* password1 = "123456789";

// Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://192.168.43.10:2000/tech/post/";
// Service API Key
String prenom = "cheikh";
String nom = "sall";
String email = "200@gmail.sn";
String matricule = "cheikh2";
String password = "c123";
String role = "Administrateur";
boolean etat = "true";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Set timer to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Timer set to 10 seconds (10000)
unsigned long timerDelay = 10000;
String donnee = "{\"nom\":\"" + nom + "\",\"prenom\":\"" + prenom + "\",\"email\":\"" + email + "\",\"password\":\"" + password + "\",\"matricule\":\"" + matricule + "\",\"role\":\"" + role + "\",\"etat\":\"" + etat + "\"}";
void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password1);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");

  // Random seed is a number used to initialize a pseudorandom number generator
  randomSeed(analogRead(33));
}

void loop() {
  //Send an HTTP POST request every 10 seconds
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      
    /*  // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "nom=" + prenom + "prenom=" + nom + "email=" + email + "matricule=" + matricule + "password=" + password + "role=" + role + "etat=" + etat;           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);*/
      
      
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      // JSON data to send with HTTP POST
      String httpRequestData = "{\"nom\":\"" + nom + "\",\"prenom\":\"" + prenom + "\",\"email\":\"" + email + "\",\"password\":\"" + password + "\",\"matricule\":\"" + matricule + "\",\"role\":\"" + role + "\",\"etat\":\"" + etat + "\"}";           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
    Serial.println(donnee);
  }
}
