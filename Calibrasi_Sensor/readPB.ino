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
