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
