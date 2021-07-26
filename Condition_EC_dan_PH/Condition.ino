bool Condition_ph(float ph, float ph_a, float ph_b, bool b_ph)
{
  if (b_ph)
  {
    if (ph < ph_a)
    {
      start_ph = millis();
      pumpON(p_phup);
      Serial.println("pump pH UP ON");
      Serial.println(millis());
      b_ph = false;
      //on ph up
    }
    else if ( ph > ph_b)
    {
      // on ph down
      start_ph = millis();
      pumpON(p_phdown);
      Serial.println("pump pH Dwon ON");
      Serial.println(millis());
      b_ph = false;
    }
    else
    {
      b_ph = true;
    }
  }
  return b_ph;
}
bool Condition_ec(float ec, float ec_a, bool b_ec)
{
  if (b_ec)
  {
    if ( ec < ec_a)
    {
      start_ec = millis();
      pumpON(p_ecA);
      pumpON(p_ecB);
      Serial.println("pump EC A & EC B ON ");
      Serial.println(millis());
      b_ec = false;
    }
    else
    {
      b_ec = true;
    }
  }
  return b_ec;
}

void pumpON(int pin)
{
  digitalWrite(pin, 1);

}
void pumpOFF(int pin)
{
  digitalWrite(pin, 0);
}
bool OFFPUMPEC(unsigned long start_EC, bool EC, int interval_EC)
{
  if (!EC)
  {
    if ( millis() - start_EC > interval_EC )
    {
      pumpOFF(p_ecA);
      pumpOFF(p_ecB);
      Serial.println("pump EC A & EC B OFF");
      Serial.println(millis());
      EC = true;
      delay_cond_ec = millis() ;
    }
  }
  return EC;
}
bool OFFPUMPPH( unsigned long start_PH, bool PH, int interval_PH)
{
  if (!PH)
  {
    if (millis() - start_PH > interval_PH)
    {
      pumpOFF(p_phdown);
      pumpOFF(p_phup);
      Serial.println("pump pH UP & pH Down OFF");
      Serial.println(millis());
      PH = true;
      delay_cond_ph = millis() ;

    }
  }
  return PH;
}
