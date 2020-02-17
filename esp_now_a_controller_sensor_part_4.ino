#include <ESP8266WiFi.h>
#define hall_pin D5
extern "C" {
    #include <espnow.h>
}
// this is the MAC Address of the slave which receives the data
uint8_t mac4[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
#define WIFI_CHANNEL 4
int prevstate = LOW;


// must match the slave struct
struct __attribute__((packed)) 
DataStruct {
char text[32];
};
DataStruct buttonpressed;

struct __attribute__((packed)) 
DataStruct2 {
char text[32]; 
};
DataStruct2 buttonreleased;
//=======================================================================================

void setup() {
  pinMode(hall_pin,INPUT);
 // pinMode(D2,OUTPUT);
    Serial.begin(115200); Serial.println();
    Serial.println("Starting EspnowController.ino");
    WiFi.mode(WIFI_STA); // Station mode for esp-now controller
    WiFi.disconnect();
    Serial.printf("This mac: %s, ", WiFi.macAddress().c_str());
    Serial.printf("slave mac: %02x%02x%02x%02x%02x%02x", mac4[0], mac4[1], mac4[2], mac4[3], mac4[4], mac4[5]);
    Serial.printf(", channel: %i\n", WIFI_CHANNEL);
    if (esp_now_init() != 0) 
    {
    Serial.println("*** ESP_Now initialization failed");
    }
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_add_peer(mac4, ESP_NOW_ROLE_SLAVE, WIFI_CHANNEL, NULL, 0);
    strcpy(buttonpressed.text,"ir sensor 4 off");
    strcpy(buttonreleased.text,"ir sensor 4 on");
    Serial.println("Setup finished");

}

//=======================================================================================

void loop() {
    sendData();

}

//============================================================================================

void sendData() {
  int currentstate = digitalRead(hall_pin);
  if(prevstate != currentstate){
    if(currentstate == HIGH){
       uint8_t bs[sizeof(buttonpressed)];
         memcpy(bs, &buttonpressed, sizeof(buttonpressed));
        esp_now_send(NULL, bs, sizeof(buttonpressed));
        Serial.println(buttonpressed.text);

    }else if(currentstate == LOW){
        uint8_t bs[sizeof(buttonreleased)];
        memcpy(bs, &buttonreleased, sizeof(buttonreleased));
        esp_now_send(NULL, bs, sizeof(buttonreleased));
      Serial.println(buttonreleased.text);

    }
  }prevstate = currentstate;

}
