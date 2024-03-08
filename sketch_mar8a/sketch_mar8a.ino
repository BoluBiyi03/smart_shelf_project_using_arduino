#include <SoftwareSerial.h>// Importing SoftwareSerial.h as a library
#include <LiquidCrystal.h>// Importing LiquidCrystal.h as a library

SoftwareSerial mySerial(0, 1);//Setting pin 0 and pin 1 as TX and RX respectively
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);//Setting pin 2,3,4,5,6,7 as LCD pins

#define SENSOR_PIN A0// Setting pin A0 as the Sensor pin 
#define BT_SILENCE A5// Setting pin A5 as the BT Slience 
#define GREEN_LED 8// Setting pin 8 as the Green led pin
#define RED_LED 9// Setting pin 9 as the Red led pin 
#define BUZZER 13// Setting pin 13 as the Buzzer pin 
#define SIM_TX 10// Setting pin 10 as the SIM TX pin 
#define SIM_RX 11// Setting pin 11 as the SIM RX pin 

int smsCount = 0;// Making the sms count to be equals to zero
int silent = 0;// Making the slient to equal to zero

SoftwareSerial sim(SIM_TX, SIM_RX);// Setting the SoftwareSerial for SIM module

void setup(){
  pinMode(SENSOR_PIN, INPUT);// Setting the Sensor Pin as an input
  pinMode(BT_SILENCE, INPUT);// Setting the BT Silence pin as an input
  pinMode(GREEN_LED, OUTPUT);// Setting the Green led pin as an output
  pinMode(RED_LED, OUTPUT);// Setting the Red led pin as an output
  pinMode(BUZZER, OUTPUT);// Setting the Buzzer pin as an output
  
  sim.begin(9600);// Intializing the SIM module serial communication
  mySerial.begin(9600);// Intializing the SIM module from the other device
  
  lcd.begin(16, 2);// Starting up the cursor
  lcd.clear();// Clearing from the LCD screen
  lcd.setCursor(0, 0);// Setting the set up cursor to 0
  lcd.print("WELCOME TO DKT NIGERIA");// Displaying the text to be printed on the LCD screen
  delay(4000);// Delaying for four seconds 
  lcd.clear();// Clearing from the LCD scren
  lcd.setCursor(0, 1);// Setting the set up cursor to 1
  lcd.print("DKT SMART SHELF");// Displaying the text to be printed on the LCD screen
  delay(4000);// Delaying for four seconds
  lcd.clear();// Clearing from the LCD screen
  lcd.setCursor(0, 2);// Setting the set up cursor to 2
  lcd.print("PRODUCT SHELF");// Displaying the text to be printed on the LCD screen
  delay(4000);// Delaying for four seconds
  lcd.clear();// Clearing from the LCD screen
  lcd.setCursor(0, 3);// Setting the set up cursor to 3
  lcd.print("KISS CONDOM");// Displaying the text to be printed on the LCD screen 
  delay(4000);// Delaying for four seconds
  lcd.clear();// Clearing from the LCD screen
  
}

void loop() {
  int forceValue = analogRead(SENSOR_PIN);// Making the sensor pin to read the force value
  lcd.setCursor(0, 0);// Setting the set up cursor to 0
  lcd.print("PRODUCT SENSOR");// Displaying the text to be printed on the LCD screen
  lcd.setCursor(0, 1);// Setting the set up cursor to 1
  lcd.print("STOCK WEIGHT");// Displaying the text to be printed on the LCD screen 
  lcd.print(forceValue);// Displaying the exact value of the stock weight 
  
  if (digitalRead(BT_SILENCE) == LOW)// Reading the bt silence to be eqyal to zero
  {
    silent = 0;// Making silent to be equal to zero
    delay(200);// Delaying for 0.2 seconds
  }
  if (forceValue < 200 || forceValue > 400)// If the forcevalue is less or greater than 200 or 400 
  {
    silent = 1;// There would be no silence
  }
  if (silent == 1)// If the silence is high
  {
    digitalWrite(BUZZER, HIGH);// Turning on the buzzer 
    digitalWrite(GREEN_LED, LOW);// Turning off the green led 
    digitalWrite(RED_LED, HIGH);// Turning on the red led 
    delay(500);// Delaying for 0.5 seconds
  }
  else{
    digitalWrite(GREEN_LED, HIGH);//Turning on the green led 
    digitalWrite(RED_LED, LOW);// Turning off the red led 
  }
  digitalWrite(BUZZER, LOW);// Turning off the buzzer 
  delay(500);// Delaying for 0.5 seconds 
  
  //Checking for incoming calls 
  if (sim.available())// To check if the sim is available 
  {
    receiveTextMessage();// To receive the text messages
  }
}

void sendTextMessage()
{
  mySerial.println("AT+CMGF=1");// To send sms in the text mode 
  delay(1000);// Delaying for a seconds 
  mySerial.println("AT+CMGS=\"+2347045260312\"\r");// Inserting the mobile number that will receive the text message or the alert
  delay(1000);// Delaying for a seconds
  mySerial.println("Emergency Checkout");// Sending the content of the message 
  delay(500);// Delaying for 0.5 seconds 
  mySerial.println((char)26);// Stopping the character type 
  delay(500);// Delaying for 0.5 seconds 
  smsCount++;
  
}

void receiveTextMessage()
{
  sim.println("AT+CNMI=2,2,0,0,0");// AT command to receive a live sms 
  delay(1000);// Delaying for 1 seconds 
}