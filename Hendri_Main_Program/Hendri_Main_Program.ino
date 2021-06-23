#include <DHT.h>
#include "DFRobot_EC10.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>
//===============EC==================
DFRobot_EC10 ec;
#define EC_PIN A3
//=============PH====================
#define phPin A1
const int ArrayLenth = 40;
int pHArray[ArrayLenth];
//==============DHT==================
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
//===============MCU ================
SoftwareSerial MCU(4,3); //rx,tx
//============Switch Sensor==========
int PB[] = {8, 9, 10, 11};
bool PBin[5];
unsigned long prevReadSwitch;
unsigned long prevReadSensor;
//===================================
float hum , temp, EC , ph, uv;

void setup()
{
  Serial.begin(115200);
  MCU.begin(9600);
  Serial.println("Inisialisasi Program ...............");
  for (int i = 0 ; i <= 4; i++)
  {
    pinMode(PB[i], INPUT);
  }
  dht.begin();
  ec.begin();
  Serial.println("Program Siap ");
}

void loop() {
  readAllSensor();
  reciveDataMCU();
  if ( millis() - prevReadSwitch > 100)
  {
    prevReadSwitch = millis();
    for ( int i = 0; i <= 4; i++)
    {
      int input = readSwitch(PB[i]);
      if ( input == 0 )
      {
        PBin[i] = true;
      }
      else
      {
        PBin[i] = false;
      }
    }
  }
  if (millis() - prevReadSensor >= 1000) // 1000 artinya 1 detik 
  {
    readSensor(PBin[0], PBin[1], PBin[2], PBin[3], hum , temp, EC , ph, uv);
    Serial.println("===========================================================");
    prevReadSensor = millis();
    sendDataMCU(String(EC), String (ph), String (temp), String (hum), String (uv));

  }

  //  delay(1000);


}
