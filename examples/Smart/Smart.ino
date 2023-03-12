// Smart.ino
//
// Demonstration of DHT22 library
//
// This is a more robust approach, using some more library functions.
// The goal is to catch up and handle issues with the sensor.
//
// You may disconnect / reconnect the sensor and see what happens
//
// Werner Panocha, February 2023
//
// https://github.com/dvarrel/DHT22


// Uncomment the following line to show diagnostic messages during
// sensor startup loop
//#define SHOW_LOOP_MESSAGES


#include <DHT22.h>			// https://github.com/dvarrel/DHT22

// DHT22 data pin
#define data SDA			// SDA, or almost any other I/O pin

DHT22 dht22(data); 



void setup() {
	Serial.begin(115200); //1bit=10µs
	Serial.println("\ntest capteur DTH22");

	// Startup  DHT22 ... 
	// Wait until begin() returns OK 
	int rc;
	while((rc = dht22.begin()) < 0){
		
		#ifdef SHOW_LOOP_MESSAGES
		Serial.print("==> RC: ");
		Serial.println(rc);
		#endif
		
		rc *= -1; // Turn RC into a positive value
				
		// Error codes > POWER_ON indicate sensor issues
		if(rc > DHT22::POWER_ON){
			Serial.print("DTH22 sensor not found: ");
			Serial.println(rc);
			// Retry after a while
			delay(2500);
			
			// Start revovery
			Serial.println("Trying to recover sensor connection");
			dht22.recover();
		}
		
		#ifdef SHOW_LOOP_MESSAGES
		// Slow down in order to reduce issued message while waiting
		// to get the sensor ready.
		delay(200); 
		#endif
		
		yield(); // Be nice to background tasks, if any
	}
	
	#ifdef SHOW_LOOP_MESSAGES
	Serial.print("==> exit RC: ");
	Serial.println(rc);
	#endif
	
	Serial.println("DTH22 sensor initialized, first conversion is in progress");
}


void loop() {
	
	float t, h;
	int rc;

	if(dht22.conversionInProgress()){
		// While a conversion is running, we have to wait for completion ...
		
		// In our simple example we are done for this loop() call
		return;
	}

	// After a conversion was completed, we read the data,
	if((rc = dht22.readSensor()) == DHT22::OK){
		
		// Sensor access was successful, data were read into buffer
		Serial.print("DTH22 read OK, data ==> ");
		
		// If the functions are called shortly  after the end 
		// of a conversion,  data is taken from buffer.
		h = dht22.getHumidity();
		t = dht22.getTemperature();
		
		// Print data
		Serial.print("h=");Serial.print(h,1);Serial.print("\t");
		Serial.print("t=");Serial.println(t,1);
	
		// Notice: 
		// By nature of DHT22's design, readSensor() will automatically 
		// request the start of the next conversion.
		// This approach reads the sensor as fast as possible.
		Serial.println("      new conversion ...");
	}
	else {
		// Issues while accessing sensor
		Serial.print("DTH22 error encountered: ");
		printErrText(rc);
		Serial.println();

		// Try recovery
		// This would  allow for a 'hot pluggable' sensor 
		Serial.println("DTH22 connection lost?");
		
		while(dht22.recover() < 0){
			delay(500);
			Serial.println("      trying recovery ...");
		}
	}
  
}


void printErrText(int rc){
	// Dispatch error code
	char * rct;
	switch(rc){
		case DHT22::OK:
		rct = "OK";
		break;
		
		case DHT22::BUSY:
		rct = "BUSY";
		break;
		
		case DHT22::POWER_ON:
		rct = "POWER_ON";
		break;
		
		case DHT22::ERR_TIMING_80:
		rct = "ERR_TIMING_80";
		break;
		
		case DHT22::ERR_TIMING_50:
		rct = "ERR_TIMING_50";
		break;
		
		case DHT22::ERR_TIMING_BITS:
		rct = "ERR_TIMING_BITS";
		break;
		
		case DHT22::ERR_CRC:
		rct = "ERR_CRC";
		break;
		
		default:
		rct = "<unknown>";
	}
	Serial.print(rct);
}	
