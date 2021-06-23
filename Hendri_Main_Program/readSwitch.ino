int readSwitch(int pin)
{
  int in = digitalRead(pin);
  return in;
}
void readAllSensor()
{
  float ecVal = ecRead();
  float phVal = phRead();
  float tempVal = tempRead();
  float humVal = humRead();
}

float ecRead()
{
  float ecValue, voltage;
  float temperature = 25;
  voltage = analogRead(EC_PIN) / 1024.0 * 5000;
  //Serial.print("voltage:");
  //Serial.print(voltage);
  ecValue =  ec.readEC(voltage, temperature);
  return ecValue;
}
float phRead()
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float Offset = 0.00;
  static int samplingInterval = 20;
  static int pHArrayIndex;
  static float pHValue, voltage;
  if (millis() - samplingTime > samplingInterval)
  {
    pHArray[pHArrayIndex++] = analogRead(phPin);
    if (pHArrayIndex == ArrayLenth)
    {
      pHArrayIndex = 0;
      voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024;
      pHValue = 3.5 * voltage + Offset;
    }
    samplingTime = millis();
  }
  return pHValue;
}
float tempRead()
{
  float t;

  t = dht.readTemperature();
  return t;
}
float humRead()
{
  float h ;
  h = dht.readHumidity();
  return h ;
}
float uvRead()
{
  float uv;
  uv = random(0, 10);
}



double avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if (number < 5) { //less than 5, calculated directly statistics
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0]; max = arr[1];
    }
    else {
      min = arr[1]; max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;      //arr<min
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;  //arr>max
          max = arr[i];
        } else {
          amount += arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount / (number - 2);
  }//if
  return avg;
}
