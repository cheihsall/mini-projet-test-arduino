#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 #include <SPI.h> // SPI
#include <MFRC522.h> // RFID

#define SS_PIN 10
#define RST_PIN 9
    
// Déclaration 
MFRC522 rfid(SS_PIN, RST_PIN); 

// Tableau contentent l'ID
static String RFID;
byte nuidPICC[4];
static String RFIDD ;
String g = "ff";  
// Déclaration 


// Tableau contentent l'ID


// Definit le type de capteur utilise
#define DHTTYPE DHT11
int digitalPin = 5; // pour le relais
int analogPin = A7; // pour le capteur de l'humidité du sol
int digitalVal; // digital readings
int analogVal; //analog readings
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A4, A5, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal_I2C lcd(0x27, 16, 2);
String password = "1234";
String mypassword;
Servo myservo;
int redled = 1;
//int lock = 13;
String json;
int counter = 0;
int attempts = 0;
int max_attempts = 3;
int humidity, temperature;
int ventilo = 0;
int pos = 0;

Servo servo1;
int lightValue;

void setup(){
  Serial.begin(9600);
    SPI.begin(); 

  // Init MFRC522 
  rfid.PCD_Init();
  dht.begin();
   
  servo1.attach(8);
 
  pinMode(ventilo, OUTPUT);
 pinMode(digitalPin, OUTPUT);
digitalWrite(digitalPin, LOW);
  // set up the LCD's number of columns and rows:
  lcd.init();
 
  pinMode(redled, OUTPUT);
  //pinMode(lock, OUTPUT);
  myservo.attach(3);
  digitalWrite(redled, LOW);
  myservo.write(-90);
  lcd.setBacklight(1);
 // Serial.println("enter password");
    lcd.print("Enter Password:");
     servo1.write(0);
}
 static char etat;
 static String jsonStr;
 static int etatvent;// = doc["arrosageT"];
     static int etattoit;//= doc["arrosageO"];
     static int etatpompe;//= doc["arrosageO"];
void loop()
{
 // Initialisé la boucle si aucun badge n'est présent 
 //if ( !rfid.PICC_IsNewCardPresent())
 //   Serial.println("dd");

  // Vérifier la présence d'un nouveau badge 
 // if ( !rfid.PICC_ReadCardSerial())
    // Serial.println("dccd");
//keypadfunction();
/*if ( !rfid.PICC_IsNewCardPresent())
  return;

  // Vérifier la présence d'un nouveau badge 
 if ( !rfid.PICC_ReadCardSerial())
    return;
  // Enregistrer l'ID du badge (4 octets) 
  for (byte i = 0; i < 4; i++) 
  {
    nuidPICC[i] = rfid.uid.uidByte[i];
    
  }
  
  // Affichage de l'ID 
  //Serial.println("Un badge est détecté");
  //Serial.println(" L'UID du tag est:");
  for (byte i = 0; i < 4; i++) 
  {
   // Serial.print(nuidPICC[i], HEX);
   RFID = nuidPICC[i], HEX;
     
   
  }
  //delay(1000);
  Serial.println();
  RFIDD = "{\"idcarte\":\"" + RFID + "\",\"etat\":\"" + g + "\"}";
 Serial.print(RFIDD);
 Serial.print(",");
  // Re-Init RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1(); // Stop encryption on PCD// Stop encryption on PCD

 
}*/


/* Gestion de la carte RFID Début*/

  /*if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }*/


//void keypadfunction()
//{
  
  String rfidd = "";
//}
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {

    String content= "";
    byte letter;

    for (byte i = 0; i < rfid.uid.size; i++) 
    {
      content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(rfid.uid.uidByte[i], HEX));
    }
    
    content.toUpperCase();
    rfidd = content.substring(1);
  }
 char key = keypad.getKey();
 
  if (key){
    Serial.println(key);
    counter = counter + 1;
    lcd.setBacklight(1);
    lcd.setCursor(counter, 1);
    lcd.print("*");
  }
  if (key == '1')
  {

    mypassword = mypassword + 1;  
  }
 
    if (key == '2')
  {

    mypassword = mypassword + 2;  
  }
 
  if (key == '3')
  {
 
    mypassword = mypassword + 3;
  }
 
   if (key == '4')
  {
 
    mypassword = mypassword + 4;  
  }
 
  if (key == '5')
  {
 
    mypassword = mypassword + 5;
  }
 
   if (key == '6')
  {
   
    mypassword = mypassword + 6;
  }
 
   if (key == '7')
  {

    mypassword = mypassword + 7;
  }

   if (key == '8')
  {

    mypassword = mypassword + 8;
  }
 
  if (key == '9')
  {

    mypassword = mypassword + 9;
  }
             
                 if (key == '0')
  {

    mypassword = mypassword + 0;
  }
 
 
        if (key == '*')
  {
    Serial.println(mypassword);
   
if ( password == mypassword )
{
 
lcd.clear();
lcd.setBacklight(1);
lcd.println("ouverture porte");
lcd.setCursor(0,1);
lcd.println("Automatique");
myservo.write(90);
delay(9000);
myservo.write(-90);
mypassword = "";
counter = 0;
lcd.clear();
lcd.setBacklight(1);
lcd.setCursor(0,0);
lcd.println("Enter password");
}
else
{
Serial.println("wrong");
myservo.write(-90);
attempts = attempts + 1;
if (attempts >= max_attempts )
{
  lcd.clear();
  lcd.setBacklight(1);
  lcd.setCursor(0,0);
  lcd.print("Locked Out");
 
digitalWrite(redled, HIGH);
delay(5000);
digitalWrite(redled, LOW);
attempts = 0;

}
mypassword = "";
counter = 0;
lcd.clear();
lcd.setBacklight(1);
lcd.setCursor(0,0);
lcd.print("Wrong Password");
delay(1000);

lcd.setCursor(0,1);
lcd.print("tentative maximale 3");
delay(5000);

lcd.clear();
lcd.println("Enter password");
lcd.setCursor(0,1);
}
   
  }  
  if (Serial.available()) {
jsonStr = Serial.readStringUntil('\n');
  }
    StaticJsonDocument<64> doc;
    DeserializationError error = deserializeJson(doc, jsonStr);
   // if (error) {
     // Serial.println("Failed to parse JSON");
   // } else {
      int extracteur = doc["extracteur"];
     int toiture = doc["toiture"];
    int arrosage = doc["arrosage"];
   

   lightValue = digitalRead(11);
        lightValue = map (lightValue, 0, 1023, 0, 90);
        // control the servo motor based on the light value read, adjust linearly by angles
        servo1.write (lightValue);
       analogVal = analogRead(analogPin);
       humidity = dht.readHumidity();
temperature = dht.readTemperature();
String temperatureString = String(temperature);
String humidityString = String(humidity);
String lightValueString = String(lightValue);
String temoin = String(etat);
String rfid = String(rfidd);
String soilHumidityString = String(analogVal);
String extracteurString = String(extracteur);
String toitureString = String(toiture);
String arrosageString = String(arrosage);
String etatventString = String(etatvent);
String etattoitString = String(etattoit);
String etatpompeString = String(etatpompe);
//String analogvalString = String(analogVal);
String djson = "{\"Temperature\":\"" + temperatureString + "\",\"Humidite\":\"" + humidityString + "\",\"HumiditeSol\":\"" + soilHumidityString + "\",\"Luminosite\":\"" + lightValueString + "\",\"Etat\":\"" + temoin + "\",\"idcarte\":\"" + rfidd + "\",\"Extracteur\":\"" + extracteurString + "\",\"Toiture\":\"" + toitureString + "\",\"Arrosage\":\"" + arrosageString + "\",\"etatvent\":\"" + etatventString + "\",\"etattoit\":\"" + etattoitString + "\",\"etatpompe\":\"" + etatpompeString + "\"}";
Serial.println(djson);

        /*   //  Serial.print("Temperature: "); //pour permettre d'afficher les données sous format JSON
      Serial.print(temperature);
       Serial.print("/");
      //  Serial.print("Humidite: ");
        Serial.print(humidity);
        Serial.print("/");
        Serial.print(humidity);
        Serial.print("/");
//Serial.print("Luminosité: ");
        Serial.print(lightValue);
        Serial.print("/");*/
         
       delay(2000);
              /*if(temperature>39){
                 
                  digitalWrite(ventilo, HIGH);
                  }
               else{
                  digitalWrite(ventilo, LOW);
             
                }*/

                if(lightValue >= 30){

                  lightValue = map (lightValue, 0, 1023, 0, 90);
                 
                 
                  }
                 
  
         
//pour l'interface
//parti extracteur d'aire
 //etat= Serial.read();



    

 
if (extracteur == 1 || temperature>28)
{
digitalWrite(ventilo, HIGH);
etatvent=1;
}
 if (extracteur == 0)
{
 digitalWrite(ventilo, LOW);
 etatvent=0;
  }
 if (toiture == 2)
{
  //for (pos = 0; pos <= 90; pos += 1) {
 servo1.write(0);  
 //delay(2000);
 etattoit=1;
  }
  else if (arrosage == 4 || analogVal > 500)
{
 
digitalWrite(digitalPin, HIGH);
etatpompe=1;


  }
    else if ((arrosage == 5 || analogVal < 500 ) && etatpompe==1)
{
 
digitalWrite(digitalPin, LOW);
etatpompe=0;
//delay(1000);

  }

   /* else if (arrosageT == 6)
{
 
digitalWrite(digitalPin, HIGH);


  }
    else if (arrosageT == 7 )
{
 
digitalWrite(digitalPin, LOW);


  }


else if (arrosageO == 8)
{
 
digitalWrite(digitalPin, HIGH);


  }
    else if (arrosageO == 9 )
{
 
digitalWrite(digitalPin, LOW);


  }*/

 
  

 if (toiture == 3)
{
  //for (pos = 90; pos >= 0; pos -= 1) {
 servo1.write(90);  
// delay(2000);
  //}
 etattoit=0;
  }
 
  //Serial.println(etat);
  
                         
  
 // Serial.print(25);
 //  Serial.print("/");
 //   Serial.print(30);
 //  Serial.print("/");
 //   Serial.print(40);
 // Serial.print("/");
//     Serial.println(250);
//   delay(1000);
// Initialisé la boucle si aucun badge n'est présent 

 
}
