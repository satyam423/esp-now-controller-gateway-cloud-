//int data1; //Initialized variable to store recieved data
#include <ArduinoJson.h>
#include <RtcDS3231.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
int i=0;
unsigned int p;
//====================================================================


String txtMsg = "";                         // a string for incoming text
//unsigned int lastStringLength = txtMsg.length();     // previous length of the String

String lastStringLength="";

//====================================================================================================================

// Update these with values suitable for your network.
const char* ssid = "satyam";
const char* password = "satyam1020";
const char* mqtt_server = "159.65.146.25";
char val[200];
#define mqtt_port 1883

//======================================================================================================================


WiFiClient wifiClient;
PubSubClient client(wifiClient);

//================================================================================================================================

void setup_wifi() {
   Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(D2,HIGH);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      //Once connected, publish an announcement...
     // client.publish("/icircuit/presence/ESP32/", "hello world");
     //client.publish("outTopic", "Hello from ESP8266 testing tynor");
      // ... and resubscribe
      client.subscribe("outTopic");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------new message from broker-----");
    //Serial.print("channel:");
    //Serial.println(topic);
    //Serial.print("data:");  
   
    Serial.write(payload, length);
    Serial.println();


}


 

void setup() {
  Serial.begin(115200); 
  Serial.setTimeout(500);// Set time out for 
 setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
 client.setCallback(callback);
  reconnect();
   Serial.begin(115200);
   Serial.println();
  }
void loop() {
  client.loop();  
  int k=0;
 // txtMsg="\0";
if (Serial.available() > 0) {
     txtMsg [500];
    char inChar = Serial.read();
   //  Serial.print(inChar);
     txtMsg += inChar; 
     k=txtMsg.length();
    if(k==112)
    { 
      k=0;
   client.publish("outTopic",String(txtMsg.substring(0,112)).c_str());
     txtMsg="\0";
     k=0;
    }}}
 





    

 


    
 














    
   





    
  
    
    
 
 
