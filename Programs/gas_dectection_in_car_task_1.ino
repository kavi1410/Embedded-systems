#ifndef CC3200R1M1RGC
#include <SPI.h>
#endif
#include <WiFi.h>
#include <Wire.h>
#include <stdlib.h>


int MQ2 = 2;
int MQ6 = 6;

int MQ135 =24;
int dust =23;




// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "****";
const int updateThingSpeakInterval = 16 * 1000; // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)

//buffer for float to string
char buffer[25];
// your network name also called SSID
char ssid[] = "***";
// your network password
char password[] = "****";

// initialize the library instance:
WiFiClient client;

unsigned long lastConnectionTime = 0; // last time you connected to the server, in milliseconds
boolean lastConnected = false; // state of the connection last time through the main loop
const unsigned long postingInterval = 10*1000; //delay between updates to xively.com
int failedCounter = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(6, INPUT);

  pinMode(24, INPUT);
  pinMode(23, INPUT);
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
  // put your main code here, to run repeatedly: 
  float alert_MQ2_value , alert_MQ6_value , alert_MQ135_value ,salert_MQ135, alert_dust_value;

while (client.available()) {
char c = client.read();
Serial.print(c);
}

// if there's no net connection, but there was one last time
// through the loop, then stop the client:
if (!client.connected() && lastConnected) {
Serial.println();
Serial.println("disconnecting.");
client.stop();
}

// if you're not connected, and ten seconds have passed since
// your last connection, then connect again and send data:
if (!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
  float MQ2_value = analogRead(MQ2);
  float MQ6_value = analogRead(MQ6);
  
  float MQ135_value = analogRead(MQ135);
  float dust_value = analogRead(dust);
 
if(MQ2_value >  400){
  alert_MQ2_value = MQ2_value;
}
else{
  alert_MQ2_value = MQ2_value;
}
Serial.print("Smoke range : ");
String sMQ2_value = dtostrf(alert_MQ2_value,3,3,buffer);
Serial.println(sMQ2_value);

if(MQ6_value > 400){
  alert_MQ6_value = MQ6_value;
}
else{
  alert_MQ6_value =MQ6_value;
}
Serial.print("LPG Gas range : ");
String sMQ6_value = dtostrf(alert_MQ6_value,3,3,buffer);
Serial.println(sMQ6_value);

if(MQ135 > 400){
  float salert_MQ135 =  (alert_MQ135_value/1023*100);
}
else{
  salert_MQ135 =MQ135;
}
Serial.print("Gas Level : ");
Serial.println(salert_MQ135);
 
if(dust_value> 400){
 float v = alert_dust_value * (5  / 1024);
 dust = (0.17 * v - 0.1);
}
else{
  dust =dust_value;
}

Serial.print("Dust density : ");
Serial.println(dust);





//send to server
updateThingSpeak("field1=" + sMQ2_value + "&field2=" + sMQ6_value + "&field3=" +salert_MQ135 + "&field4=" +dust);
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
