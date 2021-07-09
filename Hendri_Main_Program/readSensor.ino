float readSensor(bool sens1, bool sens2, bool sens3, bool sens4, float &hum, float &temp, float &EC, float &ph, float &uv)
{
  float zero = 0;
  String phStat, ecStat, dhtStat, uvStat;
  if ( sens1)
  {

    phStat = "ON";
    int anIn= analogRead(PH_PIN);
    ph = phRead(phA, phB, anIn);
  }
  else
  {
    phStat = "OFF";
    ph = zero;
  }
  if ( sens2)
  {
    
    int anIn= analogRead(EC_PIN);
    EC = ecRead(ecA, ecB, anIn);
    ecStat = "ON";
  }
  else
  {
    ecStat = "OFF";
    EC =zero;
  }
  if ( sens3)
  {
    dhtStat = "ON";
    temp = tempRead();
    hum = humRead();


  }
  else
  {
    dhtStat = "OFF";
    temp = zero;
    hum = zero;
  }
  if ( sens4)
  {
    uv = uvRead();
    uvStat = "ON";
  }
  else
  {
    uv = zero;
    uvStat = "OFF";
  }

  Serial.print("pH    = "); Serial.print(phStat); Serial.print("\t| pH      = "); Serial.println(ph);
  Serial.print("EC    = "); Serial.print(ecStat); Serial.print("\t| EC      = "); Serial.println(EC);
  Serial.print("Temp  = "); Serial.print(dhtStat); Serial.print("\t| Temp    = "); Serial.println(temp);
  Serial.print("Humi  = "); Serial.print(dhtStat); Serial.print("\t| Humi    = "); Serial.println(hum);
  Serial.print("UV    = "); Serial.print(uvStat); Serial.print("\t| UV      = "); Serial.println(uv);

}
