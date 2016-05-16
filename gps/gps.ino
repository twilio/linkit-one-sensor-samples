#include <LGPS.h>
#include "string_parsing.h"
#include "DisplayManager.h"

//rgb_lcd lcd;
gpsSentenceInfoStruct gpsInfo;

char buff[256];
int num;

void parseGPGGA(const char* GPGGAstr) {
  double latitude;
  double longitude;
  double dilution, alt, hg;
  int tmp, hour, minute, second;
  if (GPGGAstr[0] == '$') {
    tmp = getComma(1, GPGGAstr);
    hour     = (GPGGAstr[tmp + 0] - '0') * 10 + (GPGGAstr[tmp + 1] - '0');
    minute   = (GPGGAstr[tmp + 2] - '0') * 10 + (GPGGAstr[tmp + 3] - '0');
    second    = (GPGGAstr[tmp + 4] - '0') * 10 + (GPGGAstr[tmp + 5] - '0');

    sprintf(buff, "UTC timer %2d-%2d-%2d", hour, minute, second);
    Serial.println(buff);

    tmp = getComma(2, GPGGAstr);
    latitude = getDoubleNumber(&GPGGAstr[tmp]);
    tmp = getComma(4, GPGGAstr);
    longitude = getDoubleNumber(&GPGGAstr[tmp]);

    int latdeg = latitude / 100;
    int londeg = longitude / 100;
    double latmin = latitude - (((double)latdeg) * 100);
    double lonmin = longitude - (((double)londeg) * 100);

    tmp = getComma(7, GPGGAstr);
    num = getIntNumber(&GPGGAstr[tmp]);
    sprintf(buff, "satellites number = %d ", num);
    Serial.println(buff);

    sprintf(buff, "Lat=%dd %5.4fm", latdeg, latmin);
    Serial.println(buff);

    sprintf(buff, "Lon=%dd %5.4fm", londeg, lonmin);
    Serial.println(buff);

    tmp = getComma(8, GPGGAstr);
    dilution = getDoubleNumber(&GPGGAstr[tmp]);
    sprintf(buff, "Horizontal dilution = %10.4f ", dilution);
    Serial.println(buff);

    tmp = getComma(9, GPGGAstr);
    alt = getDoubleNumber(&GPGGAstr[tmp]);
    sprintf(buff, "Altitude (meters) = %10.4f ", alt);
    Serial.println(buff);

    tmp = getComma(11, GPGGAstr);
    hg = getDoubleNumber(&GPGGAstr[tmp]);
    sprintf(buff, "Height from mean sea level (geoid) = %10.4f", hg);
    Serial.println(buff);
    Serial.println("====================================================================");

  }
  else
  {
    Serial.println("Didn't get data");
//    lcd.clear();
//    lcd.print("No satellite");
  }
}

void parseGPRMC(const char* GPRMCstr) {
  double latitude;
  double longitude;
  double speedInKnots;
  double trackAngleInDegrees;

  int tmp;

  if (GPRMCstr[0] == '$') {
    tmp = getComma(3, GPRMCstr);
    latitude = getDoubleNumber(&GPRMCstr[tmp]);
    tmp = getComma(5, GPRMCstr);
    longitude = getDoubleNumber(&GPRMCstr[tmp]);

    int latdeg = latitude / 100;
    int londeg = longitude / 100;
    double latmin = latitude - (((double)latdeg) * 100);
    double lonmin = longitude - (((double)londeg) * 100);

    sprintf(buff, "Lat: %dd%2.1fm", latdeg, latmin);
    Serial.println(buff);

    DisplayManager::putString(buff, 0, 0);

    sprintf(buff, "Lng: %dd%2.1fm", londeg, lonmin);
    Serial.println(buff);
    
    DisplayManager::putString(buff, 1, 0);

    tmp = getComma(7, GPRMCstr);
    speedInKnots = getDoubleNumber(&GPRMCstr[tmp]);
    sprintf(buff, "Speed: %2.1f ", speedInKnots);
    Serial.println(buff);

    DisplayManager::putString(buff, 2, 0);

    tmp = getComma(8, GPRMCstr);
    trackAngleInDegrees = getDoubleNumber(&GPRMCstr[tmp]);
    sprintf(buff, "Angle: %3.1f ", trackAngleInDegrees);

    DisplayManager::putString(buff, 3, 0);
    
    Serial.println(buff);
    Serial.println("====================================================================");

  }
  else
  {
    Serial.println("Didn't get data");
  }
}

void setup() {
  Serial.begin(115200);
  LGPS.powerOn();
  Serial.println("LGPS armed.");
  Serial.println("Waiting for GPS data...");

  DisplayManager::init();
  
  delay(2000);
}

void loop() {
  LGPS.getData(&gpsInfo);

  Serial.print("Raw GPS Data RMC Sentence: ");
  //Serial.println((char*)gpsInfo.GPGGA);
  Serial.println((char*)gpsInfo.GPRMC);

  parseGPRMC((const char*)gpsInfo.GPRMC);
  delay(2000);
}
