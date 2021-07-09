void readCal()
{
  
  ReadPB(ModeEC);
  ReadPB(ModePH);
  MenuCal(ModeEC);
  MenuCal(ModePH);
}

void cal(int &bts, bool &a, int pin)
{
  if ( millis() - prevCalEC > 20)
  {
    int adcIN =  getADC(pin, a);
    bts = adcIN;
    prevCalEC = millis();
  }
}

int getADC(int pin, bool &a)
{
  static int s1, s2, s3, count;
  s3 = s2;
  s2 = s1;
  s1 = analogRead(pin);
  int s12 = abs(s2 - s1);
  int s23 = abs(s3 - s2);
  int s13 = abs(s3 - s1);
  if ( s12 <= 5 && s23 <= 5 && s13 <= 5 )
  {
    count++;
  }
  if ( count == 10)
  {
    a = true;
    Serial.println("DONE");
    Serial.print("AVE= ");
    int ave = (s1 + s2 + s3 ) / 3;
    Serial.println(ave);
    count = 0;
    s1 = 0;
    s2 = 0;
    s3 = 0;
    return ave;
  }
  return 0;
}


void MenuCal(String &Mode)
{
  
  if ( Mode == "calEC A")
  {
    cal(ecA, becA, EC_PIN);
    if (becA)
    {
      digitalWrite(buzz, 0);
      CekDataandSave(ecA, 1);
      Mode = "EC1";
      buzzDone();
      Serial.println("DONE A ");
      Serial.print("bts A = ");
      Serial.println(ecA);
      Serial.println(Mode);
    }
  }
  else if ( Mode == "calEC B")
  {
    cal(ecB, becB, EC_PIN);
    if (becB)
    {
      digitalWrite(buzz, 0);
      CekDataandSave(ecB, 5);
      Mode = "EC2";
      buzzDone();
      Serial.println("DONE B");
      Serial.print("bts B = ");
      Serial.println(ecB);
      Serial.println(Mode);
    }
  }
  else if ( Mode == "calPH A")
  {
    cal(phA, bphA, PH_PIN);
    if (bphA)
    {
      digitalWrite(buzz, 0);
      CekDataandSave(phA, 9);
      Mode = "PH1";
      buzzDone();
      Serial.println("DONE A");
      Serial.print("bts pH A = ");
      Serial.println(phA);
      Serial.println(Mode);
    }
  }
  else if ( Mode == "calPH B")
  {
    cal(phB, bphB, PH_PIN);
    if (bphB)
    {
      digitalWrite(buzz, 0);
      CekDataandSave(phB, 13);
      Mode = "PH2";
      buzzDone();
      Serial.println("DONE B");
      Serial.print("bts B = ");
      Serial.println(phB);
      Serial.println(Mode);
    }
  }
}

void CekDataandSave(int val, int address)
{
  int n[5];
  int s1, s2, s3, s4;
  n[1] = val / 1000;
  s1 = val % 1000;
  n[2] = s1 / 100;
  s2 = s1 % 100;
  n[3] = s2 / 10;
  s4 = s2 % 10;
  n[4] = s4 / 1;
  int x = 1;
  for (int i = address; i <= address + 3; i++)
  {
    EEPROM.write(i, n[x]);
    Serial.print("n" + String(i));
    Serial.println(n[x]);
    x++;
  }
}
int readEEPROM(int address)
{
  String text;
  int nilai;
  for (int i = address; i <= address + 3; i++)
  {
    int te = EEPROM.read(i);
//    Serial.println(te);
    text += te;
  }
  nilai = text.toInt();
  return nilai;
}

void buzzB()
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
void buzzA()
{
  digitalWrite(buzz, 1);
  delay(500);
  digitalWrite(buzz, 0);
  delay(500);
}
void buzzDone()
{
  digitalWrite(buzz, 1);
  delay(1000);
  digitalWrite(buzz, 0);
}

int rPB(int pin)
{
  int in = digitalRead(pin);
  return in;
}
void ReadPB(String &Mode)
{
  int PBA, PBB;
  PBA = rPB(PB_A);
  PBB = rPB(PB_B);

  if ( PBA &&  Mode == "EC2")
  {
    Start_PBA1 = millis();
  }
  else if ( PBA && Mode == "EC1")
  {
    Start_PBA2 = millis();
  }
  else if (!PBA  && Mode == "EC2")
  {
    if ( millis() - Start_PBA1 > 1000)
    {
      Serial.println("calEC A");
      Mode = "calEC A";
      becA = false;
      Start_PBA1 = millis();
      buzzA();
    }
  }
  else if (!PBA  && Mode == "EC1")
  {
    if ( millis() - Start_PBA2 > 1000)
    {
      Serial.println("calEC B");
      Mode = "calEC B";
      becB = false;
      Start_PBA2 = millis();
      buzzB();
    }
  }
  
  if ( PBB &&  Mode == "PH2")
  {
    Start_PBB1 = millis();
  }
  else if ( PBB && Mode == "PH1")
  {
    Start_PBB2 = millis();
  }
  else if (!PBB  && Mode == "PH2")
  {
    if ( millis() - Start_PBB1 > 1000)
    {
      Serial.println("calPH A");
      Mode = "calPH A";
      bphA = false;
      Start_PBB1 = millis();
      buzzA();
    }
  }
  else if (!PBB  && Mode == "PH1")
  {
    if ( millis() - Start_PBB2 > 1000)
    {
      Serial.println("calPHlEC B");
      Mode = "calPH B";
      bphB = false;
      Start_PBB2 = millis();
      buzzB();
    }
  }
}
