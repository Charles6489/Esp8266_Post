#ifdef ESP32
#include <WiFi.h>
#include <ESPmDNS.h>
#include <Ethernet.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#endif
#include <PubSubClient.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
const char* ssid     = "Ambafiber Orozco";
const char* password = "0939979649";
const char* host     = "192.168.1.128";
const char* url      = "/control.php/";
String PostData;
String postVariable = "temp=";
String postVariable1 = "volt=";
String postVariable2 = "hum=";
int Led_OnBoard = 2;                  // Initialize the Led_OnBoard 

IPAddress local_IP(192,168,1,130);
IPAddress server(192,168,1,128);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
IPAddress primaryDNS(8, 8, 8, 8); //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional
WiFiClient  ethClient;
PubSubClient client(ethClient);
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
int sensorPin = A0;
int sensorPin1 = A0;
int sensorPin2 = A0;
int input;
double sensorValue;
double sensorValue1;
double sensorValue2;

void setup()
{
   // put your setup code here, to run once:
  delay(1000);
  pinMode(Led_OnBoard, OUTPUT);       // Initialize the Led_OnBoard pin as an output
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

 //client.setServer(server, 80);
  //client.setCallback(callback);

// if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
//    Serial.println("STA Failed to configure");
//  }

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(Led_OnBoard, LOW);
    delay(250);
    Serial.print(".");
    digitalWrite(Led_OnBoard, HIGH);
    delay(250);
  }

 }


void loop() {
   sensorValue =  ( 5.0 * analogRead(sensorPin)* 100.0) / 1024.0;//voltaje  
   sensorValue1 = (( 5.0 * analogRead(sensorPin) * 100.0) / 1024.0)-10;//temperatura
   sensorValue2 = (( 5.0 * analogRead(sensorPin)*100.0) / 1024.0)+1.5;//presion

   PostData = postVariable + sensorValue +"&" + postVariable1 + sensorValue1 +"&" + postVariable2 + sensorValue2 ;

   Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

if (client.connect(host, 80)) {

client.println("POST /control.php HTTP/1.1");
client.println("Host: 192.168.1.128");
client.println("Cache-Control: no-cache");
client.println("Content-Type: application/x-www-form-urlencoded");
client.print("Content-Length: ");
client.println(PostData.length());
client.println();
client.println(PostData);


    } 
 delay(4000);  //Here there is 4 seconds delay plus 1 second delay below, so Post Data at every 5 seconds
  digitalWrite(Led_OnBoard, LOW);
  delay(1000);
  digitalWrite(Led_OnBoard, HIGH);
}   
