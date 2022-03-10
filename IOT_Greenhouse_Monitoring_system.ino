#include <ESP8266TelegramBOT.h>

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include <DHT.h>
#include <SimpleTimer.h>
#define moistureCriticalLevel 30

byte pinMoistureVCC = 4; // D2
byte pinMoistureSensor = A0;

int  moistureValue;
int TempValue;
int HumidValue;
int tempValue;
float tempCriticalLevel = 29;
int  moistureReadingInterval = 10;   // interval in seconds between sensor reading (every 24h)
long moistureLastRead = 0;              // last time the moisture was read

int tempReadingInterval = 10;   // interval in seconds between sensor reading (every minute)
long tempLastRead = 0;              // last time the moisture was read


int  botScanInterval = 1;               // interval time between scan messages (seconds)
long botLastScan;                       // last time messages' scan has been done

long nowMillis;
char auth[] = "6vrE-TPVYGQFfGOTWsCHPuIymRm2QtMg";
WiFiClientSecure net_ssl;
// WiFi connection
const char* ssid     = "OnePlus 7T";      // wifi name
const char* pass = "qwertyui";      // wifi password
//dht
#define DHTPIN 2
#define DHTTYPE DHT11


// Telegram bot
#define botMyChatID "461276769"          // reference to my phone's chat
#define botToken "1168081048:AAEHUOH9lJ2tX_y4v3sZGJXlTyolnnuEgnM"
#define botName "Iot_greenhouse"
#define botUsername "Greenhouse_Monitor_Bot"
TelegramBOT bot(botToken, botName, botUsername);

String botCommand;
String botResponse;
DHT dht(DHTPIN, DHTTYPE);

boolean tflag = false;
boolean fan_status =true;
boolean pump_status = false;
boolean flag2 = false;

SimpleTimer timer;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Blynk.begin(auth, ssid, pass);
  // init the moisture sensor
  pinMode(pinMoistureSensor, INPUT);
  pinMode(pinMoistureVCC, OUTPUT);
  digitalWrite(pinMoistureVCC, LOW);    // by default, we
//  do not power the sensor
  Serial.print("Connecting to \"");
  Serial.print(ssid);
  Serial.println("\"");

  //WiFi.begin(ssid, pass);
Blynk.begin(auth, ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected (");
  Serial.print(WiFi.localIP());
  Serial.println(")");
  Serial.println("");
  net_ssl.setInsecure();
  // start bot
  bot.begin();
  botResponse = "connected!";
  bot.sendMessage(botMyChatID,botResponse,"");
  botResponse = "type - /help for help";
  bot.sendMessage(botMyChatID,botResponse,"");
   timer.setInterval(2000L,blynk_reading);
    //timer.setInterval(2000L,read_humid);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run(); // Initiates Blynk
  timer.run();
handleBotMessages();
checkSoilMoisture();
checkTempHumidity();

}

void blynk_reading(){
  float temp = read_temp();
  float hum = read_humid();
  int soil = readMoisture();
  Blynk.virtualWrite(V6, temp);
  Blynk.virtualWrite(V5, hum); 
  Blynk.virtualWrite(V7, soil);
}

int readMoisture() {
  digitalWrite(pinMoistureVCC, HIGH); // power up sensor

  delay(500);
  int value = analogRead(pinMoistureSensor);
   value = map(value,1024,550,0,100);
  digitalWrite(pinMoistureVCC, LOW); // power down sensor

  return value;
}


float read_temp(){
  delay(500);
  float t = dht.readTemperature();
  return t;
  
  }
float read_humid(){
  delay(500);
  float h = dht.readHumidity();
  return h;
  
  }  

void checkSoilMoisture() {
  nowMillis = millis();

  if ((nowMillis > moistureLastRead + (moistureReadingInterval * 1000)) or moistureLastRead == 0) {
    moistureLastRead = nowMillis;

    moistureValue = readMoisture();

    if ((moistureValue < moistureCriticalLevel)&&(flag2==false)) {
      // send value to Telegram chat
      botResponse = " turning pump on (moisture Level [0-100]: ";
      botResponse.concat(moistureValue);
      botResponse.concat(")");
      bot.sendMessage(botMyChatID, botResponse, "");    // send notification to my phone
      flag2 = true;
      pump_status = true;
      Blynk.notify("pump on");
    }
    if((moistureValue >= moistureCriticalLevel)&&(flag2==true)){
      flag2 = false;
      pump_status  = false;
      
    }

    Serial.print("moisture  Level (0-100): ");
    Serial.println(moistureValue);
    Serial.println("");
  }
}

void checkTempHumidity() {
 nowMillis = millis();
 

  if ((nowMillis > tempLastRead + (tempReadingInterval * 1000)) or tempLastRead == 0) {
    tempLastRead = nowMillis;

    tempValue = read_temp();

    if ((tempValue > tempCriticalLevel)&&(tflag==false)) {
      // send value to Telegram chat
      botResponse = "It's tooo hott here! turning fan on!!! temp: ";
      botResponse.concat(tempValue);
      botResponse.concat(")");
      bot.sendMessage(botMyChatID, botResponse, "");    // send notification to my phone
      tflag= true;
      fan_status = true;
       Serial.println("Flag true fan on");
    }
    if ((tempValue<=tempCriticalLevel)&&(tflag==true)){
      tflag=false;
      fan_status = false;
       Serial.println("Flag false fan off");
    }
     Serial.print("temp  Level (0-100): ");
    Serial.println(tempValue);
    Serial.println("");
  }
}


void handleBotMessages() {
  nowMillis = millis();

  if (nowMillis > botLastScan + (botScanInterval * 1000)) {
    botLastScan = millis();

    bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message

    // loop at messages received
    for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
      handleBotCommands(i);
    }
    bot.message[0][0] = "";   // All messages have been replied - reset new messages
  }
}


/* Execute command sent to the bot */
void handleBotCommands(int line) {
  botCommand = bot.message[line][5]; // message reiceived
  botCommand.toUpperCase();  // not case sensitive anymore

  if (botCommand.equals("/READ")) {

    // read data
    moistureValue = readMoisture();

    //botResponse = "Sensor value: ";
    botResponse = "Humidity Level (0-1023): ";
    botResponse.concat(moistureValue);
    if (moistureValue < moistureCriticalLevel) {
      botResponse.concat(" (critical)");
    }

  } else if (botCommand.equals("/HELP")) {

    botResponse = "Allowed commands are:";
    bot.sendMessage(bot.message[line][4], botResponse, "");
    botResponse = "/read - Read soil moisture";
    bot.sendMessage(bot.message[line][4], botResponse, "");
    botResponse = "/ip - Get local IP address";
    bot.sendMessage(bot.message[line][4], botResponse, "");
    botResponse = "/TEMP - Get TEMPERATURE";
    bot.sendMessage(bot.message[line][4], botResponse, "");
    botResponse = "/HUMID - Get humidity";
    // bot.sendMessage(bot.message[line][4], botResponse, "");
    
  } else if (botCommand.equals("HI") or botCommand.equals("HELLO")) {

    botResponse = "Hello " + bot.message[line][2] + " !";  // user's name
    
  } else if (botCommand.equals("/IP")) {
    
    botResponse = "Local IP address: ";
    botResponse.concat(WiFi.localIP().toString());
    
  } else if (botCommand.equals("/TEMP")) {

    // read data
    TempValue = read_temp();

    //botResponse = "Sensor value: ";
    botResponse = "Temperature: ";
    botResponse.concat(TempValue);
  } else if (botCommand.equals("/HUMID")) {

    // read data
    HumidValue = read_humid();

    //botResponse = "Sensor value: ";
    botResponse = "Humidity: ";
    botResponse.concat(HumidValue);
  } else if (botCommand.equals("/STATUS")) {
    if(fan_status){
      botResponse="fan on";
       bot.sendMessage(bot.message[line][4], botResponse, "");
    }
    if(fan_status==false){
      botResponse=" fan off";
       bot.sendMessage(bot.message[line][4], botResponse, "");
      }
    }
    else if (botCommand.equals("/PUMP")) {
    if(pump_status){
      botResponse="pump on";
       bot.sendMessage(bot.message[line][4], botResponse, "");
    }
    if(pump_status==false){
      botResponse=" pump off";
       bot.sendMessage(bot.message[line][4], botResponse, "");
      }
    }
    else {

    botResponse = "unknown command sir!";

  }
  bot.sendMessage(bot.message[line][4], botResponse, "");    // bot.message[line][4] is chat ID
}  


  
