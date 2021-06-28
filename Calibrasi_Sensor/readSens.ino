float readec(int btsA, int btsB, int anIN)
{
  float out = ((anIN * 12.8) - (btsA * 12.8)) / (btsB - btsA);
  return out;
}
float readph(int btsA, int btsB, int anIN)
{
  float out = (((anIN * 5.17) - (btsA * 5.17)) / (btsB - btsA)) + 4.01;
  return out;
}
