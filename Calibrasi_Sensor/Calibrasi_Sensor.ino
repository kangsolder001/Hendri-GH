#include <EEPROM.h>

#define EC_PIN A3 // tetep 0
#define PH_PIN A4
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
unsigned long prevCalEC, prevPBA, Start_PBA1, Start_PBA2, Start_PBB1, Start_PBB2, prevR;
bool b1st;
void setup() {
  Serial.begin(115200);
  pinMode(PB_A, INPUT_PULLUP);
  pinMode(PB_B, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
  ecA = readEEPROM(1);
  ecB = readEEPROM(5);
  phA = readEEPROM(9);
  phB = readEEPROM(13);
  Serial.print("ec A = ");
  Serial.println(ecA);
  Serial.print("ec B = ");
  Serial.println(ecB);
  Serial.print("ph A = ");
  Serial.println(phA);
  Serial.print("ph B = ");
  Serial.println(phB);
}

void loop()
{
  if (millis() - prevR > 500)
  {
    int in = analogRead(EC_PIN);
    float nilai = readec(ecA, ecB, in);
    int a = analogRead(PH_PIN);
    float phVal = readph(phA, phB, a);
    Serial.print("anPH = ");
    Serial.println(a);
    Serial.print("PH = ");
    Serial.println(phVal);
    Serial.print("anIN = ");
    Serial.println(in);
    Serial.print("EC = ");
    Serial.println(nilai);
    Serial.println("===============================");
    prevR = millis();
  }
  ReadPB(ModeEC);
  ReadPB(ModePH);
  MenuCal(ModeEC);
  MenuCal(ModePH);


}
