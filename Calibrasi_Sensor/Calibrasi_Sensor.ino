#define EC_PIN A2
#define PB_A 5
#define PB_B 6
#define buzz 2
unsigned int prevCalEC, prevPBA, Start_PBA,Start_PBB;
bool b1st;
void setup() {
  Serial.begin(115200);
  pinMode(PB_A, INPUT_PULLUP);
  pinMode(PB_B, INPUT_PULLUP);
  pinMode(buzz, OUTPUT);
}
String Mode;
int btsA, btsB;
void loop() {
  int PBA, PBB;
  PBA = rPB(PB_A);
  PBB = rPB(PB_B);
  //Serial.print("PBA = ");
  //Serial.println(PBA);
  if ( PBA &&  Mode != "doneA")
  {
    Start_PBA = millis();
  }
  else if ( PBA && Mode == "doneA")
  {
    Start_PBB = millis();
  }

  else if (!PBA  && Mode != "doneA")
  {
    if ( millis() - Start_PBA > 3000)
    {
      Mode = "calEC A";
      Serial.println("calEC A");

      Start_PBA = millis();
      for ( int i = 0 ; i < 2 ; i++)
      {
        digitalWrite(buzz, 1);
        delay(100);
        digitalWrite(buzz, 0);
        delay(100);
      }
      digitalWrite(buzz, 1);
      Serial.println("LED ON ");
      b1st = true;
    }
  }
  else if (!PBA  && Mode == "doneA")
  {
    if ( millis() - Start_PBB > 3000)
    {
      Mode = "calEC B";
      Serial.println("calEC B");

      Start_PBB = millis();
      for ( int i = 0 ; i < 2 ; i++)
      {
        digitalWrite(buzz, 1);
        delay(100);
        digitalWrite(buzz, 0);
        delay(100);
      }
      digitalWrite(buzz, 1);
      Serial.println("LED ON ");
      b1st = true;
    }
  }


  if ( Mode == "calEC A")
  {
    if (b1st && millis() - Start_PBA > 1000)
    {
      digitalWrite(buzz, 0);
      Serial.println("LED OFF");
      b1st = false;
    }
    calEC(btsA);
    //    Serial.println(btsA);
    if ( btsA != 0)
    {
      Serial.println("DONE A ");
      Serial.print("bts A = ");
      Serial.println(btsA);
      Mode = "done A";
    }
  }
  else if ( Mode == "calEC B")
  {
    if (b1st && millis() - Start_PBB > 1000)
    {
      digitalWrite(buzz, 0);
      Serial.println("LED OFF");
      b1st = false;
    }
    calEC(btsB);
    if ( btsB != 0)
    {
      Serial.println("DONE B ");
      Serial.print("bts B = ");
      Serial.println(btsB);
    }
  }


  if ( Serial.available() > 0)
  {
    String in = Serial.readStringUntil('\r');
    if ( in == "1")
    {
      Mode = "calEC A";
      Serial.println("calEC A");
    }
    else if ( in == "2")
    {
      Mode = "calEC B";
      Serial.println("calEC B");
    }
    else if ( in == "3")
    {
      Serial.print("bts A = ");
      Serial.println(btsA);
      Serial.print("bts B = ");
      Serial.println(btsB);
    }
    else if ( in == "4")
    {
      btsA = 0;
      btsB = 0;
    }
    else
    {
      Mode = "";
    }
  }

}
