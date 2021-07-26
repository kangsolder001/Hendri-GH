int readSwitch(int pin)
{
  int in = digitalRead(pin);
  return in;
}

float ecRead(int btsA, int btsB, int anIN)
{
  float out = ((anIN * 12.8) - (btsA * 12.8)) / (btsB - btsA);
  //  out = out*1000/2;
  return out;
}
float phRead(int btsA, int btsB, int anIN)
{
  float out = (((anIN * 5.17) - (btsA * 5.17)) / (btsB - btsA)) + 4.01;
  return out;
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
  uv = lux.readLightLevel();
  return uv;
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
