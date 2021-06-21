int PB[] = {8, 9, 10, 11};
bool PBin[5];
void setup() {
  for (int i = 0 ; i <= 4; i++)
  {
    pinMode(PB[i], INPUT);
  }
  Serial.begin(115200);
  // put your setup code here, to run once:

}

void loop() {
 for ( int i =0;i<=4;i++)
 {
  int input = readSwitch(PB[i]);
  if ( input ==1 )
  {
    PBin[i] =true;
  }
  else 
  {
    PBin[i] =false;
  }
 }
 readPh();
 readSuhu();
 readKel();
 readUV();
 
 

  // put your main code here, to run repeatedly:

}
