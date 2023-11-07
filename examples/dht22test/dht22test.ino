#include <DHT22.h>
//define pin data
#define pinDATA SDA // SDA, or almost any other I/O pin

DHT22 dht22(pinDATA); 
 
void setup() {
  Serial.begin(115200); //1bit=10µs
  Serial.println("\ntest capteur DTH22");
}

void loop() {
  Serial.println(dht22.debug()); //optionnal

  float t = dht22.getTemperature();
  float h = dht22.getHumidity();

  if (dht22.getLastError() != dht22.OK) {
    Serial.print("last error :");
    Serial.println(dht22.getLastError());
  }

  Serial.print("h=");Serial.print(h,1);Serial.print("\t");
  Serial.print("t=");Serial.println(t,1);
  delay(2000); //Collecting period should be : >1.7 second
}
