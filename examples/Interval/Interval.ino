// Interval.ino
//
// Demonstration of DHT22 library
// 
// This is an approach for slow conversion intervals.

//
// Werner Panocha, February 2023
//


#include <DHT22.h>			// https://github.com/dvarrel/DHT22
#include <arduino-timer.h> 	// https://github.com/contrem/arduino-timer

// DHT22 data pin
#define data SDA			// SDA, or almost any other I/O pin

#define INTERVAL_SEC 10		// Interval in s (should be > 5s)

DHT22 dht22(data); 

// create a timer with default settings
auto timer = timer_create_default(); 
bool updateRequested;

// Periodic timer callback
bool newConversion(void *) {
   
	if(dht22.conversionInProgress()){
		// This should not happen, interval too short?!
		Serial.println("ERROR conversion already in progress, interval too short?");
		return false; // stop repetitions!
	}

	// Request a conversion (discarding the retrieved data for now)
	dht22.readSensor();
	// Set a flag, to make loop() aware of the new conversion
	updateRequested = true;
	return true; // repeat? true
}


void setup() {
	Serial.begin(115200); //1bit=10µs
	Serial.println("\ntest capteur DTH22");

	
	// Startup  DHT22 ... until begin() returns OK
	while(dht22.begin() < 0)
		yield();

	Serial.println("DTH22 sensor initialized");
	
	// Interval timer
	timer.every(INTERVAL_SEC * 1000, newConversion);
	// DHT22 conversion is already running after begin()
	updateRequested = true;
	
}

void loop() {
	
	float t, h;
	
	// Run timer, will periodically request an update
	timer.tick();	
	
	// If a request was made, wait for end of conversion
	if(updateRequested && !dht22.conversionInProgress()){
		updateRequested = false;
		
		// Read the sensor values
		dht22.readSensor();
		
		// Notice:
		// The above line may be commented out, as the following lines
		// will automatically trigger a new read from Sensor in order
		// to get the values from most recent conversion.
		h = dht22.getHumidity();
		t = dht22.getTemperature();
		
	
		// Print data
		Serial.print("h=");Serial.print(h,1);Serial.print("\t");
		Serial.print("t=");Serial.println(t,1);
	
	}

		
}
