
void calEC(int &bts,bool &a)
{
  if ( millis() - prevCalEC > 20)
  {
    int adcIN =  getADC(a);
    bts = adcIN;
//    Serial.println(bts);
    prevCalEC = millis();
  }

}
int getADC(bool &a)
{

  static int s1, s2, s3, count;
  s3 = s2;
  s2 = s1;
  s1 = analogRead(EC_PIN);
//  Serial.print("S1:");
//  Serial.println(s1);
//  Serial.print("S2:");
//  Serial.println(s2);
//  Serial.print("S3:");
//  Serial.println(s3);
//  Serial.println("-----------------------");
  int s12 = abs(s2 - s1);
  int s23 = abs(s3 - s2);
  int s13 = abs(s3 - s1);
  if ( s12 <= 5 && s23 <= 5 && s13 <= 5 )
  {
    count++;
//    Serial.print("Count = ");
//    Serial.println(count);
  }
  if ( count == 10)
  {
    a=true;
    Serial.println("DONE");
    Serial.print("AVE= ");
    int ave = (s1 + s2 + s3 ) / 3;
    Serial.println(ave);
    count = 0;
    s1 = 0;
    s2 = 0;
    s3 = 0;
    Mode = "";
    return ave;
  }
  return 0;
}
