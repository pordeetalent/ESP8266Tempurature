#include <DHT.h>
#define DHTPIN D1
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

double sensorValue1 = 0;
//double sensorValue2 = 0;
int crosscount = 0;
int climb_flag = 0;
int val[100];
int max_v = 0;
double VmaxD = 0;
double VeffD = 0;
double Veff = 0;

String Text = "";
String Temp() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //float f = dht.readTemperature(true);
  /*if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }*/
  //float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Text = "Humidity: \t" + String(h) + "%  \nTemperature: \t"
  + String(t) + " C  \nHeat index: \t" + String(hic) +" C";
  return(Text);
}

int volt() {
  for ( int i = 0; i < 100; i++ ) {
    sensorValue1 = analogRead(A0);
    if (analogRead(A0) > 511) val[i] = sensorValue1;
    else val[i] = 0;
    delay(1);
  }
   
  max_v = 0;
   
  for ( int i = 0; i < 100; i++ ) {
    if ( val[i] > max_v ) max_v = val[i];
    val[i] = 0;
  }
  if (max_v != 0) {
    VmaxD = max_v;
    VeffD = VmaxD / sqrt(2);
    Veff = (((VeffD - 420.76) / -90.24) * -210.2) + 210.2;
  }
  else Veff = 0;
  VmaxD = 0;
  return int(Veff);
}
