#ifndef _CC3200R1M1RGC_
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>
#include <Wire.h>
#include <stdlib.h>

const int buttonpin1 = PUSH1;
const int buttonpin2 = PUSH2;
const int green = GREEN_LED;
const int red = RED_LED;
const int yellow =YELLOW_LED;

int buttonpushCounter =0;
int buttonstate1 =0;
int lastbuttonstate1 = 0;
int buttonstate2 =0;
int lastbuttonstate2 = 0;


// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "E4SRTH1TPO1G0CUB";
const int updateThingSpeakInterval = 16 * 1000; // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)

//buffer for float to string
char buffer[25];
// your network name also called SSID
char ssid[] = "SGMV";
// your network password
char password[] = "23031010";

// initialize the library instance:
WiFiClient client;

unsigned long lastConnectionTime = 0; // last time you connected to the server, in milliseconds
boolean lastConnected = false; // state of the connection last time through the main loop
const unsigned long postingInterval = 10*1000; //delay between updates to xively.com
int failedCounter = 0;
 // start with a diferent i2c address!
void setup() {
//Initialize serial and wait for port to open:
pinMode (PUSH1 , INPUT_PULLUP);
pinMode (PUSH2 , INPUT_PULLUP);
pinMode (green , OUTPUT);
pinMode (red , OUTPUT);
pinMode (yellow , OUTPUT);

Serial.begin(115200);

// attempt to connect to Wifi network:
Serial.print("Attempting to connect to Network named: ");
// print the network name (SSID);
Serial.println(ssid);
// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
WiFi.begin(ssid, password);
while ( WiFi.status() != WL_CONNECTED) {
// print dots while we wait to connect
Serial.print(".");
delay(300);
}


Serial.println("\nYou're connected to the network");
Serial.println("Waiting for an ip address");

while (WiFi.localIP() == INADDR_NONE) {
// print dots while we wait for an ip addresss
Serial.print(".");
delay(300);
}

Serial.println("\nIP Address obtained");

printWifiStatus();
}

void loop() {
// if there's incoming data from the net connection.
// send it out the serial port. This is for debugging
// purposes only:
while (client.available()) {
char c = client.read();
Serial.print(c);
}

//// if there's no net connection, but there was one last time
// through the loop, then stop the client:
if (!client.connected() && lastConnected) {
Serial.println();
Serial.println("disconnecting.");
client.stop();
}

// if you're not connected, and ten seconds have passed since
// your last connection, then connect again and send data:
if (!client.connected() && (millis() - lastConnectionTime > postingInterval)) {

  buttonstate1 = digitalRead(PUSH1);
  buttonstate2 = digitalRead(PUSH2);

  if(buttonstate1 != lastbuttonstate1){
  if(buttonstate1 == HIGH);
  buttonpushCounter++;
 } 

 if(buttonstate2 != lastbuttonstate2){
 if(buttonstate2 == HIGH);
 buttonpushCounter++;
 } 

if (buttonpushCounter <=10) {
  Serial.print("Count no ");
  Serial.print(buttonpushCounter);
  delay(1000);
}
if (buttonpushCounter == 1){
  digitalWrite(green, LOW);
  digitalWrite(red , LOW);
  digitalWrite(yellow , HIGH);
}
if (buttonpushCounter % 2 == 0){
  digitalWrite(green, HIGH);
  digitalWrite(red , LOW);
  digitalWrite(yellow , LOW);
}


if (buttonpushCounter == 10){
  Serial.print("completed");
  digitalWrite(red,HIGH);
  digitalWrite(green,LOW);
  digitalWrite(yellow,LOW);
} 

}
//send to server
updateThingSpeak("field1=" + buttonpushCounter );
}
// store the state of the connection for next time through
// the loop:
lastConnected = client.connected();
}
void updateThingSpeak(String tsData)
{
if (client.connect(thingSpeakAddress, 80))
{
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(tsData.length());
Serial.println(">>TSDATALength=" + tsData.length());
client.print("\n\n");

client.print(tsData);
Serial.println(">>TSDATA=" + tsData);

lastConnectionTime = millis();

if (client.connected())
{
Serial.println("Connecting to ThingSpeak...");
Serial.println();

failedCounter = 0;
}
else
{
failedCounter++;

Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");
Serial.println();
}

}
else
{
failedCounter++;

Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");
Serial.println();

lastConnectionTime = millis();
}
}
// This method calculates the number of digits in the
// sensor reading. Since each digit of the ASCII decimal
// representation is a byte, the number of digits equals
// the number of bytes:

int getLength(int someValue) {
// there's at least one byte:
int digits = 1;
// continually divide the value by ten,
// adding one to the digit count for each
// time you divide, until you're at 0:
int dividend = someValue / 10;
while (dividend > 0) {
dividend = dividend / 10;
digits++;
}
// return the number of digits:
return digits;
}

void printWifiStatus() {
// print the SSID of the network you're attached to:
Serial.print("SSID: ");
Serial.println(WiFi.SSID());

// print your WiFi shield's IP address:
IPAddress ip = WiFi.localIP();
Serial.print("IP Address: ");
Serial.println(ip);

// print the received signal strength:
long rssi = WiFi.RSSI();
Serial.print("signal strength (RSSI):");
Serial.print(rssi);
Serial.println(" dBm");
}
