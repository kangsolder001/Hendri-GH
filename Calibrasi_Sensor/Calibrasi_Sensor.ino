#define EC_PIN A0
#define PB_A 5
#define PB_B 6
#define buzz 2
unsigned int prevCalEC;
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
  if (!PBA && Mode != "calEC A")
  {
    if ((millis() - prevPBA > 100) && b1st)
    {
      if (b1st)
      {
        digitalWrite(buzz, 1);
        b1st = false;
      }
      prevPBA = millis();
    }
    else if (( millis() - prevPBA > 100) && !b1st)
    {
      if (!b1st)
      {
        digitalWrite(buzz, 0);
      }
    }
    if ( millis() - Start_PBA > 3000)
    {
      Mode = "calEC A";
      Serial.println("calEC A");
      digitalWrite(buzz, 1);
      Start_PBA = millis();
      b1st = true;

    }
  }
  else if ( PBA && Mode != "calEC A")
  {
    Start_PBA = millis();
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

  if ( Mode == "calEC A")
  {
    if (b1st && millis() - Start_PBA > 2000)
    {
      digitalWrite(buzz, 0);
    }
    calEC(btsA);
    //    Serial.println(btsA);
    if ( btsA != 0)
    {
      Serial.println("DONE A ");
      Serial.print("bts A = ");
      Serial.println(btsA);
    }
  }
  else if ( Mode == "calEC B")
  {
    calEC(btsB);
    if ( btsB != 0)
    {
      Serial.println("DONE B ");
      Serial.print("bts B = ");
      Serial.println(btsB);
    }
  }
}
