#include <ESP8266WiFi.h>
#include<SoftwareSerial.h> //Included SoftwareSerial Library
#include <Wire.h>      // I2c communication
//#include <RTClib.h>
#include <RTClib.h>

RTC_DS3231 rtc;
char t1[32];
char t2[32];
char t3[32];
char t4[32];
char t5[32];
char d11[32];
char d22[32];
//String s1[32];
//String r[32];
    //ds3231 library library
//RTC_DS3231 rtc;
//RtcDS3231<TwoWire> rtcObject(Wire);
unsigned long start_millis;
unsigned long start_millis_1;
unsigned long end_millis;
unsigned long end_millis_1;
unsigned long diff=0;
unsigned long diff_1=0;

unsigned long current_time ;

extern "C" {
    #include <espnow.h>
     #include <user_interface.h>
}
uint8_t mac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
void initVariant() {
  WiFi.mode(WIFI_AP);
  wifi_set_macaddr(SOFTAP_IF, &mac[0]);
}
#define WIFI_CHANNEL 4
SoftwareSerial s(3,1);
// must match the controller struct
struct __attribute__((packed)) 
DataStruct {
    char text[32];
//    char text1[32];
    unsigned int time;
};

DataStruct myData;
char str1[32], str2[32],str3[32];
char IR11[32],IR10[32];
//String str[50];
//==============================================
void setup() {
  //Serial S Begin at 115200 Baud
  s.begin(115200);
   rtc.begin();
  Serial.begin(115200);
  rtc.adjust(DateTime(2020,2,11,13,14,0));
  
 // delay(1000); // wait for console opening
 // if (! rtc.begin()) {
//Serial.println("Couldn't find RTC");
  // while (1);
  //}
  // if (rtc.lostPower()) {
  // Serial.println("RTC lost power, lets set the time!");
// rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 // }
//rtcObject.Begin();     //Starts I2C
 
  //RtcDateTime currentTime = RtcDateTime(04, 02, 20, 10, 20, 0); //define date and time object
  //rtcObject.SetDateTime(currentTime); //configure the RTC with object


 
Serial.println("Starting EspnowSlave.ino");
    Serial.print("This node AP mac: "); Serial.println(WiFi.softAPmacAddress());
    Serial.print("This node STA mac: "); Serial.println(WiFi.macAddress());
    if (esp_now_init()!=0) {
        Serial.println("*** ESP_Now init failed");
        while(true) {};
    }
     esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
   esp_now_register_recv_cb(receiveCallBackFunction);
   Serial.println("End of setup - waiting for messages");
}

void loop() {
  //Write '123' to Serial
  //s.write(1);
  //Serial.print(1); 
  current_time  =millis();
  //delay(10);
}
void receiveCallBackFunction(uint8_t *senderMac, uint8_t *incomingData, uint8_t len) {
    memcpy(&myData, incomingData, sizeof(myData));

//Serial.println(*incomingData);
//Serial.println(*senderMac);
int indata=*incomingData;
int macr = *senderMac;
//Serial.println(macr);
//===============================================diff 1========================================
      if(macr==132)
      {
          if((macr==132)&&(indata==72))  
          { 
          
          start_millis=current_time;
           DateTime now = rtc.now();
      sprintf(t1, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());  
              
          }
          else
          { 
            
          end_millis=current_time;
           DateTime now = rtc.now();
         sprintf(t2, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());  
          diff=end_millis-start_millis;
           sprintf(d11, " %02ld",diff); 
         String b1="{'Id' :1,'type':2,'name':'h1','start_time':";
         String b2="{'start_time':";
         String b3= t1;
         String b4= "}";
         String b5="{'end_time':";
         String b6= t2;
         String b7= "}";
         String b8="{'diff':";
         String b9= d11;
         String b10= "}";
         String b11=",'end_time':";
         String b12=",'diff':";
         String b13="    ";
         String e1=b1+b3+b11+b6+b12+b9+b4+b13;
         Serial.println(e1);
          }
        }
//=================================================diff 2=====================================================================================================     
      if(macr==80)
     {
        if((macr==80) && (indata==72) )
        {
         start_millis_1=current_time;
         DateTime now = rtc.now();
        sprintf(t3, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());   
        }
        else
        {
            end_millis_1=current_time;
              DateTime now = rtc.now();
         sprintf(t4, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());  
         diff_1=end_millis_1-start_millis_1;
           sprintf(d22, " %02ld",diff_1); 
         String a1="{'Id' :1,'type':1,'name':'h2','start_time':";
         String a2="{'start_time':";
         String a3= t3;
         String a4= "}";
         String a5="{'end_time':";
         String a6= t4;
         String a7= "}";
         String a8="{'diff':";
         String a9= d22;
         String a10= "}";
         String a11=",'end_time':";
         String a12=",'diff':";
         String a13="    ";
         String e2=a1+a3+a11+a6+a12+a9+a4+a13;
         Serial.println(e2);
         
   //===============================================================================================================================================================          
        }
      }
}   
