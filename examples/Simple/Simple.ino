// Simple.ino
//
// Simple demonstration of DHT22 library
//
// Werner Panocha, February 2023
//
// https://github.com/dvarrel/DHT22

#include <DHT22.h>			// https://github.com/dvarrel/DHT22

// DHT22 data pin
#define data SDA			// SDA, or almost any other I/O pin

DHT22 dht22(data); 


	
void setup() {
	Serial.begin(115200); //1bit=10µs
	Serial.println("\ntest capteur DTH22");

	
	// Startup  DHT22 ... until begin() returns OK
	while(dht22.begin() < 0)
		yield();

	Serial.println("DTH22 sensor initialized");
}

void loop() {
	
	float t, h;
	 
	
	h = dht22.getHumidity();
	t = dht22.getTemperature();
	
	// This is easy, but consider what's under the hood ...
	//
	// The conversion time of DHT22 is about 2 seconds, a slow device!
	// So we can never go faster than this.
	//
	// The above functions will request a new data conversion from the sensor,
	// when applicable.
	// While issuing a conversion request, the data of the _PREVIOUS_ 
	// conversion is read in.
	// In other words, we cannot read conversion result data without starting
	// a new conversion.
	// Be aware of this interleaving process when building your own applications.
	//
	// As a conseqence we have no data available immediately after power up.
	// The functions will indicate this by returning  
	// a negative humidity value and a temperature of -273°C.
	// See printout of results after program start ...
	
	// Print data
	Serial.print("h=");Serial.print(h,1);Serial.print("\t");
	Serial.print("t=");Serial.println(t,1);
	
	
	// It makes no much sense to decrease this delay below 2200 ms.
	// If the delay is increased, the printed data is as old as the
	// delay lasts.
	// See cexplainations  above
	delay(1000);
		
}
