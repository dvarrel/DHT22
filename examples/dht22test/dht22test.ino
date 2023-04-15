#include <DHT22.h>
//define pin data
#define data SDA

DHT22 dht22(data); 
 
void setup() {
  Serial.begin(115200); //1bit=10µs
  Serial.println("\ntest capteur DTH22");
}

void loop() {
  //Serial.println(dht22.debug()); //optionnal

  float t = dht22.getTemperature();
  float h = dht22.getHumidity();

  Serial.println(dht22.getLastError());

  Serial.print("h=");Serial.print(h,1);Serial.print("\t");
  Serial.print("t=");Serial.println(t,1);
  delay(5000);
}
