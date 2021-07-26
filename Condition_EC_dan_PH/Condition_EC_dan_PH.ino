#define p_phup 12
#define p_phdown 13
#define p_ecA A0
#define p_ecB A1
float ph_a= 4.00, ph_b=6.00;
float ec_a=100.00, ec_b=200.00;
float temp_a, temp_b;
float hum_a, hum_b;
float lux_a;

float ph=5.00, ec=150.00;

bool b_ph, b_ec;
unsigned long start_ph, start_ec,  delay_cond_ph, delay_cond_ec;
int interval_ph = 3000; // 0.5 ph = 100 ml  , 100 ml = 3000 ms, 
int interval_ec = 3000;
unsigned long interval_cond_ec = 5000;
unsigned long interval_cond_ph = 5000;

void setup() {
  Serial.begin(115200);
  pinMode(p_phup, OUTPUT);
  pinMode(p_phdown, OUTPUT);
  pinMode(p_ecA, OUTPUT);
  pinMode(p_ecA, OUTPUT);
  // put your setup code here, to run once:
  Serial.println(" inputkan ph dan ec dengan format |EC|PH| ");
}

void loop()
{
  
  if ( Serial.available() > 0)
  {
    String req = Serial.readStringUntil('\r');
    int ind1, ind2, ind3;
    String data1, data2;
    ind1 = req.indexOf('|');
    ind2 = req.indexOf('|', ind1 + 1);
    ind3 = req.indexOf('|', ind2 + 1);
    data1 = req.substring(ind1 + 1, ind2);
    data2 = req.substring(ind2 + 1, ind3);
    ec = data1.toFloat();
    ph = data2.toFloat();
    Serial.print("ec = ");
    Serial.println(ec);
    Serial.print("ph = ");
    Serial.println(ph);
  }
  if ( millis() - delay_cond_ec > interval_cond_ec && b_ec)
  {
//    delay_cond_ec = millis() - interval_cond_ec * 0.1;
    b_ec = Condition_ec(ec, ec_a, b_ec);
  }
  if ( millis() - delay_cond_ph > interval_cond_ph && b_ph)
  {
//    delay_cond_ph = millis() - interval_cond_ph * 0.1;
    b_ph = Condition_ph(ph, ph_a, ph_b, b_ph);
  }

  b_ec = OFFPUMPEC(start_ec, b_ec, interval_ec);
  b_ph = OFFPUMPPH(start_ph, b_ph, interval_ph);


}
