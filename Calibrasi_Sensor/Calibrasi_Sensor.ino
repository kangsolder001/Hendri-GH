#include <EEPROM.h>

#define EC_PIN A2 // tetep 0
#define PB_A 5
#define PB_B 6
#define buzz 2
String Mode = "doneB";
int btsA, btsB;
bool btsa = false;
bool btsb = false;
unsigned long prevCalEC, prevPBA, Start_PBA, Start_PBB, prevR;
bool b1st;
void setup() {
  Serial.begin(115200);
  pinMode(PB_A, INPUT_PULLUP);
  pinMode(PB_B, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
  btsA = readEEPROM(1);
  btsB = readEEPROM(5);
  Serial.print("bts A = ");
  Serial.println(btsA);
  Serial.print("bts B = ");
  Serial.println(btsB);
}

void loop() 
{
  if (millis() - prevR > 500)
  {
    int in = analogRead(EC_PIN);
    float nilai = readec(btsA, btsB, in);
    Serial.print("anIN = ");
    Serial.println(in);
    Serial.print("EC = ");
    Serial.println(nilai);
    prevR = millis();
  }
  int PBA, PBB;
  PBA = rPB(PB_A);
  PBB = rPB(PB_B);
  //Serial.print("PBA = ");
  //Serial.println(PBA);
  if ( PBA &&  Mode == "doneB")
  {
    Start_PBA = millis();
  }
  else if ( PBA && Mode == "doneA")
  {
    Start_PBB = millis();
  }

  else if (!PBA  && Mode == "doneB")
  {
    if ( millis() - Start_PBA > 1000)
    {
      Mode = "calEC A";
      Serial.println("calEC A");
      btsa = false;
      Start_PBA = millis();
      for ( int i = 0 ; i < 1 ; i++)
      {
        digitalWrite(buzz, 1);
        delay(500);
        digitalWrite(buzz, 0);
        delay(500);
      }
      //      digitalWrite(buzz, 1);
      b1st = true;
    }
  }
  else if (!PBA  && Mode == "doneA")
  {
    if ( millis() - Start_PBB > 1000)
    {
      Mode = "calEC B";
      Serial.println("calEC B");
      btsb = false;
      Start_PBB = millis();
      for ( int i = 0 ; i < 1 ; i++)
      {
        digitalWrite(buzz, 1);
        delay(400);
        digitalWrite(buzz, 0);
        delay(400);
        digitalWrite(buzz, 1);
        delay(500);
        digitalWrite(buzz, 0);
        delay(500);
      }
      //      digitalWrite(buzz, 1);
      b1st = true;
    }
  }


  if ( Mode == "calEC A")
  {
    //    if (b1st && millis() - Start_PBA > 1000)
    //    {
    //      digitalWrite(buzz, 0);
    //      //      Serial.println("LED OFF");
    //      b1st = false;
    //    }
    calEC(btsA, btsa);
    //    Serial.println(btsA);
    if (btsa)
    {
      Serial.println("DONE A ");
      Serial.print("bts A = ");
      digitalWrite(buzz, 0);
      Serial.println(btsA);
      CekDataandSave(btsA,1);
      Mode = "doneA";
      Serial.println(Mode);
      digitalWrite(buzz, 1);
      delay(1000);
      digitalWrite(buzz, 0);
      //      delay(500);
    }
  }
  else if ( Mode == "calEC B")
  {
    //    if (b1st && millis() - Start_PBB > 1000)
    //    {
    //      digitalWrite(buzz, 0);
    //      b1st = false;
    //    }
    calEC(btsB, btsb);
    if (btsb)
    {
      Serial.println("DONE B");
      Serial.print("bts B = ");
      Mode = "doneB";
      digitalWrite(buzz, 0);
      Serial.println(btsB);
      CekDataandSave(btsB,5);
      Serial.println(Mode);
      digitalWrite(buzz, 1);
      delay(1000);
      digitalWrite(buzz, 0);
    }
  }


  //  if ( Serial.available() > 0)
  //  {
  //    String in = Serial.readStringUntil('\r');
  //    if ( in == "1")
  //    {
  //      Mode = "calEC A";
  //      Serial.println("calEC A");
  //    }
  //    else if ( in == "2")
  //    {
  //      Mode = "calEC B";
  //      Serial.println("calEC B");
  //    }
  //    else if ( in == "3")
  //    {
  //      Serial.print("bts A = ");
  //      Serial.println(btsA);
  //      Serial.print("bts B = ");
  //      Serial.println(btsB);
  //    }
  //    else if ( in == "4")
  //    {
  //      btsA = 0;
  //      btsB = 0;
  //    }
  //    else
  //    {
  //      Mode = "";
  //    }
  //  }

}
