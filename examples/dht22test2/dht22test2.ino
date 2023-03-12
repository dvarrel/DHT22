// dht22test2.ino
// Testframe for development 
//
// Werner Panocha, February 2023
//
// https://github.com/dvarrel/DHT22


#include <DHT22.h>

// DHT22 data pin
#define data SDA			// SDA, or almost any other I/O pin

DHT22 dht22(data); 


	
void setup() {
	Serial.begin(115200); //1bit=10µs
	Serial.println("\ntest capteur DTH22");

	
	// Startup DHT22 
	int rc = -1;
	while((rc = dht22.begin()) < 0){
		Serial.print("DTH22 sensor not ready, code #");
		Serial.print(rc * -1);
		Serial.print(" - ");
		printErrText(rc * -1);
		Serial.println();
		
		// Pause beteen checks
		delay(200); 
	}
	Serial.println("DTH22 sensor now ready, first conversion is still in progress ...");
}

void loop() {
	
	float t, h;
	int rc;

	if(dht22.conversionInProgress())
		// Abort loop() while conversion is running
		return;
		
	
	rc = dht22.readSensor();

	// If the sensor read was successful ...
	if(rc == DHT22::OK){
		
		Serial.print("DTH22 read OK, ");
		
		
		// Force buffer to get invalidated, will request new conversion
		// when calling the getXXX() methods.
		//#define INVALID_BUFFER
		#ifdef INVALID_BUFFER
		Serial.print("testing read from invalid buffer (wait) ");
		delay(2500); 
		#endif
		
		// If the functions are called shortly  after the end 
		// of last conversion,  data is taken from buffer.
		// Buffer is valid for apprx. 2 seconds after a read
		h = dht22.getHumidity();
		t = dht22.getTemperature();
		
		// Print data
		Serial.print("h=");Serial.print(h,1);Serial.print("\t");
		Serial.print("t=");Serial.println(t,1);
	}
	Serial.println("DTH22 new conversion in progress ...");
  
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
