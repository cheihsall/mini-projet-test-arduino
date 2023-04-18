#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <UrlEncode.h>
// Replace with your network credentials
const char* ssid = "Flybox-BB4A-guest";
const char* password = "orange123";

// Initialize Telegram BOT
#define BOTtoken "5991425659:AAFEAch85BgYkjsFNcJ5Rk_m7e_118yhBkQ"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "953174704"

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif


String phoneNumber = "+221764121691";
String apiKey = "5907422";

void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);    
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}


WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
const int ledPinn = 27;
const int ledPin = 26;
bool ledState = LOW;

bool ledStat = LOW;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Utilise les commandes suivantes pour controller vos lamps.\n\n";
      welcome += "/Allumer \n";
      welcome += "/Eteindre \n";
      welcome += "/Allumer2 \n";
      welcome += "/Eteindre2 \n";
      welcome += "/Etat pour savoir l etat du systeme \n";
      bot.sendMessage(chat_id, welcome, "");
       sendMessage("systeme activé");
    }

    if (text == "/Allumer") {
      sendMessage("lamp allumé");
      bot.sendMessage(chat_id, "L'etat de la lamp est allumé", "");
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
    }
    
    if (text == "/Eteindre") {
       sendMessage("lamp eteinte");
      bot.sendMessage(chat_id, "L'etat de la lamp est eteinte", "");
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    }

if (text == "/Allumer2") {
      sendMessage("lamp2 allumé");
      bot.sendMessage(chat_id, "L'etat de la lamp2 est allumé", "");
      ledStat = HIGH;
      digitalWrite(ledPinn, ledStat);
    }

if (text == "/Eteindre2") {
      sendMessage("lamp2 eteinte");
      bot.sendMessage(chat_id, "L'etat de la lamp2 est eteinte", "");
      ledStat = LOW;
      digitalWrite(ledPinn, ledStat);
    }
    
    if (text == "/Etat") {
      if (digitalRead(ledPin)){
        bot.sendMessage(chat_id, "LED is ON", "");
         sendMessage(" etat de lamp allumé");
      }
      else{
        bot.sendMessage(chat_id, "LED is OFF", "");
         sendMessage(" etat de lamp off");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
    client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  #endif

  pinMode(ledPin, OUTPUT);
  pinMode(ledPinn, OUTPUT);
  digitalWrite(ledPin, ledState);
   digitalWrite(ledPinn, ledStat);
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  sendMessage("bonjour je suis connecté!");
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
