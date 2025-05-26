#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "Yashwini";
const char* password = "123456789";

// Initialize Telegram BOT
#define BOTtoken "7891657057:AAEW-zSBWYjwaffk3KaU6pxCuGkr8jTILAw"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "989306034"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

#include <Wire.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

float latitude=13.0107051;
float longitude=77.7000617;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Elderly Fall Detection");
   if(!accel.begin())
{

      Serial.println("No valid sensor found");

      while(1);

   }  

    // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
     
  bot.sendMessage(CHAT_ID, "Elderly Fall detection");


}

void loop() {
  // put your main code here, to run repeatedly:
sensors_event_t event; 

   accel.getEvent(&event);

  float X_val=event.acceleration.x;

  float Y_val=event.acceleration.y;

  float Z_val=event.acceleration.z;
Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
//
   Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
//
   Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
//
//   Serial.println("m/s^2 ");
    delay(500);
   
   if((X_val<-7.50)||(X_val>7.5)||(Y_val<-7.50)||(Y_val>7.5))
   {
    Serial.println("Person Fallen");
    String one = "Person Fallen at:https://www.google.com/maps/?q=";
    String two = "," ;   
 
     String message = one + String(latitude, 6) + two + String(longitude, 6);
     // Convert String to char array
     int str_len = message.length() + 1;
     char textmessage[str_len];
     message.toCharArray(textmessage,str_len);
     Serial.println(textmessage);
     bot.sendMessage(CHAT_ID,textmessage);
     delay(2000);
       }
}
