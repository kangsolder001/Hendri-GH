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
      CekDataandSave(phB, 5);
      Mode = "PH2";
      buzzDone();
      Serial.println("DONE B");
      Serial.print("bts B = ");
      Serial.println(ecB);
      Serial.println(Mode);
    }
  }
}
