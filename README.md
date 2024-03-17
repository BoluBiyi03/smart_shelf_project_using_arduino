# InternetOfThings - Smart Shelf Using Arduino and GSM Module 
## Date 
8th March,2024
## By
[Oluwabiyi Boluwatife Joshua](https://github.com/BoluBiyi03)
## Introduction
 In embedded systems the current worldwide trend is ubiquitous computing. It enables communication between everyday objects by embedding microprocessors in everyday objects to make our life simpler. Thisparticular idea revolves around sensing the load of the shelves thereby detecting the level of stocks and transmitting it to the user's mobile device. We extend this concept to solve everyday problems like forgetting to purchase a particular grocery item. Devices like smartphones and wearables keep us reachable, interactable and updated to the everyday events happening around the world. We target to embed a mind in shelves, utilizing sensor and smartphone technology an automated to buy list is generated. To implement such a system,there is the need to continuously fetch,elaborate, and analyze data deriving from smart objects. This is achieved by the use ofSensor Networks, consisting of ArduinoUno along with HC- SR04 ultrasonic sensor interface. An ultrasonic sensor is used to read the level of goods on a shelf which uses the time of flight of an ultrasonic pulse to determine the distance.
 ## Problem Statement
 To develop a system that senses the level or weight of stocks and goods in the organization warehouse incase of less stock and to be able to generate alerts and share information with users connected on mobile devices.
 ## Required Hardware
 1) Arduino Uno
 2) Button
 3) Potentiometer
 4) LED
 5) Resistors
 6) Capacitor
 7) LCD Display
 8) Buzzer
 9) Power or Battery
 10) LM34
 ## Schematic Capture
 [schematic design](https://drive.google.com/file/d/1x-WJq2eqVkdl4yezWi42FByaNasgCgNu/view?usp=sharing)
 ## Source Code
 ``` cpp
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
```
## HEX File
[text]([text](sketch_mar8a/sketch_mar8a.ino.hex))
## Advantage
The system provides access to authorized persons only. It generates alerts based on exhaustion of stocks. This system is real time and user friendly
## Disadvantage
The seamless working of the product largely depends upon the network signal quality. Calibration of the ultrasonic sensors can be a deployment time overhead. Also the system is expensive to scale up.
## Summary and Conclusion 
In summary, a smart shelf demonstrates the power of IoT technology and microcontroller-based systems to enhance everyday processes and provide valuable real-time information. It can find applications in homes, retail stores, warehouses, and various other settings where efficient item monitoring and management are crucial. Building a smart shelf project not only offers a hands-on learning experience but also has the potential to solve practical problems and streamline processes in a smart and innovative way.