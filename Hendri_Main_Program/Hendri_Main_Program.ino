#include <DHT.h>
#include "DFRobot_EC10.h"
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <BH1750.h>
//================Actuator===================
#define p_phup 12
#define p_phdown 13
#define p_ecA A0
#define p_ecB A1

bool b_data = false;
float ph_a, ph_b;
float ec_a, ec_b;
float temp_a, temp_b;
float hum_a, hum_b;
float lux_a;

bool b_ph, b_ec;
unsigned long start_ph, start_ec,  delay_cond_ph, delay_cond_ec;
int interval_ph = 3000; // 0.5 ph = 100 ml  , 100 ml = 3000 ms,
int interval_ec = 3000;
unsigned long interval_cond_ec = 5000;
unsigned long interval_cond_ph = 5000;

//===============Calibration==================
#define PB_A 5
#define PB_B 6
#define buzz 7

String ModeEC = "EC2";
String ModePH = "PH2";
int ecA, ecB, phA, phB;
bool becA = false;
bool becB = false;
bool bphA = false;
bool bphB = false;
unsigned long prevCalEC, prevPBA, Start_PBA1, Start_PBA2, Start_PBB1, Start_PBB2;
bool b1st;
//===============LUX==================
BH1750 lux;
// SDA = A4;
// SCL = A5;
// ADD = GND;
// VCC = 3V
// GND = GND
//===============EC==================
DFRobot_EC10 ec;
#define EC_PIN A3
//=============PH====================
#define PH_PIN A2
//==============DHT==================
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
//===============MCU ================
SoftwareSerial MCU(4, 3); //rx,tx
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

  pinMode(p_phup, OUTPUT);
  pinMode(p_phdown, OUTPUT);
  pinMode(p_ecA, OUTPUT);
  pinMode(p_ecB, OUTPUT);
  pumpOFF(p_phup);
  pumpOFF(p_phdown);
  pumpOFF(p_ecA);
  pumpOFF(p_ecB);

  Serial.println("Inisialisasi Program ...............");
  for (int i = 0 ; i <= 4; i++)
  {
    pinMode(PB[i], INPUT);
  }
  Wire.begin();
  dht.begin();
  lux.begin();
  ec.begin();

  pinMode(PB_A, INPUT_PULLUP);
  pinMode(PB_B, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
  ecA = readEEPROM(1);
  ecB = readEEPROM(5);
  phA = readEEPROM(9);
  phB = readEEPROM(13);
  Serial.println("Program Siap ");
}

void loop() {
  readCal();
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

  Condition(b_data);



}
