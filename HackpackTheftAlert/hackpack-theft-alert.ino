#include <b64.h>
#include <HttpClient.h>

#include <LGPS.h>

#include <LGPRS.h>
#include <LGPRSClient.h>

#include <Wire.h>
#include "ADXL345.h"
#include "DisplayManager.h"

#define SITE_URL "[your_site_url]"

ADXL345 accelerometer;
LGPRSClient client;

gpsSentenceInfoStruct info;
char buff[256];
double latitude;
double longitude;

double centerLongitude=0; //YOUR VALUE
double centerLatitude=0;  //YOUR VALUE

double latrange=0.0002;//this is the offset for how exact it needs to be
double longrange=0.0002;//this is the offset for how exact it needs to be

int timer = 60;
bool timerRunning = false;

// Whether we should check for radius or not.
bool armed = false;

bool inFence() {
  if((longitude >= (centerLongitude-longrange) && longitude <= (centerLongitude+longrange))&& (latitude >= (centerLatitude-latrange) && latitude <= (centerLatitude+latrange))) {
    return true;
  }
  else {
    return false;
  }
}

static unsigned char getComma(unsigned char num,const char *str)
{
  unsigned char i,j = 0;
  int len=strlen(str);
  for(i = 0;i < len;i ++)
  {
     if(str[i] == ',')
      j++;
     if(j == num)
      return i + 1; 
  }
  return 0; 
}

static double getDoubleNumber(const char *s)
{
  String buf;
  unsigned char i;
  double rev;
  
  i=getComma(1, s);
  for(int j=0;j<i;j++)
    buf+=s[j];
  rev=buf.toFloat();
  return rev; 
}

void parseGPGGA(const char* GPGGAstr)
{ 
  int tmp ;
  if(GPGGAstr[0] == '$')
  {
    tmp = getComma(2, GPGGAstr);
    latitude = getDoubleNumber(&GPGGAstr[tmp])/100.0;
    int latitude_int=floor(latitude);
    double latitude_decimal=(latitude-latitude_int)*100.0/60.0;
    latitude=latitude_int+latitude_decimal;
    tmp = getComma(4, GPGGAstr);
    longitude = getDoubleNumber(&GPGGAstr[tmp])/100.0;
    int longitude_int=floor(longitude);
    double longitude_decimal=(longitude-longitude_int)*100.0/60.0;
    longitude=longitude_int+longitude_decimal;
    
    sprintf(buff, "Lat: %5.4f", latitude);
    Serial.println(buff);
    DisplayManager::writeText(buff);
  }
}

void setupAccelerometer() {
  // Set tap detection on Z-Axis
  accelerometer.setTapDetectionX(0);       // Don't check tap on X-Axis
  accelerometer.setTapDetectionY(0);       // Don't check tap on Y-Axis
  accelerometer.setTapDetectionZ(1);       // Check tap on Z-Axis

  accelerometer.setTapThreshold(2.5);      // Recommended 2.5 g
  accelerometer.setTapDuration(0.02);      // Recommended 0.02 s
  accelerometer.setDoubleTapLatency(0.10); // Recommended 0.10 s
  accelerometer.setDoubleTapWindow(0.30);  // Recommended 0.30 s

  // Select INT1 for get activities
  accelerometer.useInterrupt(ADXL345_INT1);
}

void sendArmedText() {
  client.println("GET /armed HTTP/1.1");
  client.println("Host: " SITE_URL);
  client.println();
}

void sendDisarmedText() {
  client.println("GET /disarmed HTTP/1.1");
  client.println("Host: " SITE_URL);
  client.println();
}

void sendStolenText() {
  client.println("GET /stolen HTTP/1.1");
  client.println("Host: " SITE_URL);
  client.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  DisplayManager::init();
  
  Serial.println("booting up");
  //DisplayManager::writeText("Booting.");
  //DisplayManager::writeText("GPS on.");
  LGPS.powerOn();
  
  while(!LGPRS.attachGPRS("wireless.twilio.com", NULL, NULL)) {
    Serial.println("Waiting for GPRS signal...");
    delay(1000);
  }

  Serial.print("Connecting to: " SITE_URL "...");
   if(!client.connect(SITE_URL, 80))
   {
     Serial.println("Could not connect to: " SITE_URL);
     return;
   } else {
    Serial.println("Connection successful.");
   }

  //DisplayManager::writeText("Cellular on.");

  DisplayManager::writeText("Listening...");
  Serial.println("Initializing accelerometer...");
  if (!accelerometer.begin())
  {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    delay(500);
  }

  setupAccelerometer();
  
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  LGPS.getData(&info);
  parseGPGGA((const char*)info.GPGGA);

  Vector norm = accelerometer.readNormalize();

  // Read activities
  Activites activities = accelerometer.readActivites();

  if(activities.isDoubleTap)
  {
    armed = !armed;
    if(armed) {
      sprintf(buff, "Armed: %5.4f", latitude);
      Serial.println(buff);
      DisplayManager::writeText(buff);
      sendArmedText();
      //DisplayManager::writeText("Armed.");
      centerLatitude = latitude;
      centerLongitude = longitude;
    } else {
      sendDisarmedText();
      timer = 60;
      timerRunning = false;
      DisplayManager::writeText("Disarmed.");
      centerLatitude = 0;
      centerLongitude = 0;
    }
  }
  
  if(armed) {
    if(!inFence()){
      if(timer == 60) {
        sendStolenText(); 
        timerRunning = true;
      }
      else if(timer == 0) {
        timer = 60;
      }
    }
  }

  if(timerRunning) {
    timer--;
  }
 
  delay(2000);
}
