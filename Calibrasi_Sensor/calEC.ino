//void calEC(int &bts, bool &a)
//{
//  if ( millis() - prevCalEC > 20)
//  {
//    int adcIN =  getADC(a);
//    bts = adcIN;
//    prevCalEC = millis();
//  }
//}
//
//int getADC(bool &a)
//{
//  static int s1, s2, s3, count;
//  s3 = s2;
//  s2 = s1;
//  s1 = analogRead(EC_PIN);
//  int s12 = abs(s2 - s1);
//  int s23 = abs(s3 - s2);
//  int s13 = abs(s3 - s1);
//  if ( s12 <= 5 && s23 <= 5 && s13 <= 5 )
//  {
//    count++;
//  }
//  if ( count == 10)
//  {
//    a = true;
//    Serial.println("DONE");
//    Serial.print("AVE= ");
//    int ave = (s1 + s2 + s3 ) / 3;
//    Serial.println(ave);
//    count = 0;
//    s1 = 0;
//    s2 = 0;
//    s3 = 0;
//    Mode = "";
//    return ave;
//  }
//  return 0;
//}
//void CaliberEC()
//{
//  if ( PBA &&  Mode == "doneB")
//  {
//    Start_PBA1 = millis();
//  }
//  else if ( PBA && Mode == "doneA")
//  {
//    Start_PBA2 = millis();
//  }
//  else if (!PBA  && Mode == "doneB")
//  {
//    if ( millis() - Start_PBA1 > 1000)
//    {
//      Mode = "calEC A";
//      Serial.println("calEC A");
//      becA = false;
//      Start_PBA1 = millis();
//      buzzA();
//      b1st = true;
//    }
//  }
//  else if (!PBA  && Mode == "doneA")
//  {
//    if ( millis() - Start_PBA2 > 1000)
//    {
//      Mode = "calEC B";
//      Serial.println("calEC B");
//      becB = false;
//      Start_PBA2 = millis();
//      buzzB();
//      b1st = true;
//    }
//  }
//  if ( Mode == "calEC A")
//  {
//    calEC(ecA, becA);
//    if (becA)
//    {
//      Serial.println("DONE A ");
//      Serial.print("bts A = ");
//      digitalWrite(buzz, 0);
//      Serial.println(ecA);
//      CekDataandSave(ecA, 1);
//      Mode = "doneA";
//      Serial.println(Mode);
//      digitalWrite(buzz, 1);
//      delay(1000);
//      digitalWrite(buzz, 0);
//    }
//  }
//  else if ( Mode == "calEC B")
//  {
//    calEC(ecB, becB);
//    if (becB)
//    {
//      Serial.println("DONE B");
//      Serial.print("bts B = ");
//      Mode = "doneB";
//      digitalWrite(buzz, 0);
//      Serial.println(ecB);
//      CekDataandSave(ecB, 5);
//      Serial.println(Mode);
//      digitalWrite(buzz, 1);
//      delay(1000);
//      digitalWrite(buzz, 0);
//    }
//  }
//}
