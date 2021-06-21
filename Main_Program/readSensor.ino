float readPh(bool sens)
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue, voltage;
  if ( sens)
  {
    if (millis() - samplingTime > samplingInterval)
    {
      pHArray[pHArrayIndex++] = analogRead(SensorPin);
      if (pHArrayIndex == ArrayLenth)pHArrayIndex = 0;
      voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024;
      pHValue = 3.5 * voltage + Offset;
      samplingTime = millis();
    }
    if (millis() - printTime > printInterval)  //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
    {
      //      Serial.print("SENSOR PH");
      //      Serial.println();
      //      Serial.print("Voltage:");
      //      Serial.print(voltage, 2);
      //      Serial.print("    pH value: ");
      //      Serial.println(pHValue, 2);
      return pHValue;
    }
  }
  else
  {
    return 0;
    //non ph
  }
}
float readSuhu(bool sens)
{
  if (sens)
  {
    //suhu
    float temp = dht.readTemperature();
    return temp;
  }
  else
  {
    return 0;
  }
}
float readKel(bool sens)
{
  if ( sens )
  {
    float hum = dht.readHumidity();
    return hum;
  }
  else
  {
    return 0;
  }
}
float readUV(bool sens)
{
  if ( sens)
  {
    float uv = 5;

    return uv;
  }
  else
  {
    return 0;
  }
}
float readEc(bool sens)
{
  if (sens)
  {
    float ec;
    ec = readEC();

    static unsigned long timepoint = millis();
    if (millis() - timepoint > 1000U) //time interval: 1s
    {
      timepoint = millis();
      voltage = analogRead(EC_PIN) / 1024.0 * 5000; // read the voltage
      ecValue =  ec.readEC(voltage, temperature); // convert voltage to EC with temperature compensation
      return ecValue;
    }
  }
  else
  {
    return 0;
  }
}
