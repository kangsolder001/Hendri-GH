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
    Serial.println(te);
    text += te;
  }
  nilai = text.toInt();
  return nilai;
}
