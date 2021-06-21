int rPB(int pin)
{
  int in = digitalRead(pin);
  return in;
}
float readec(int btsA, int btsB, int anIN)
{
    float out = ((anIN *12.8) - (btsA*12.8)) /(btsB-btsA);
  return out;
}
