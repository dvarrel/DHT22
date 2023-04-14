/*!
 * @file DHT22.h
 * @brief Arduino library for interface with DHT22 sensor 
 * @n without use of pointers.
 * @author dvarrel
 * @version  1.0.0-modified
 * @date  2022-11-09
 * @url https://github.com/dvarrel/DHT22.git
 */
#ifndef _DHT22_H
#define _DHT22_H
#include "Arduino.h"

// Scope markers for debugging, uncomment folling line
//#define SCOPE_MARKER
#ifdef SCOPE_MARKER
#define SCOPE_PIN 22	// Select appropriate pin!
#define SCOPE_INIT { pinMode(SCOPE_PIN, OUTPUT); digitalWrite(SCOPE_PIN, LOW); }
#define SCOPE_PULSE { digitalWrite(SCOPE_PIN, HIGH); digitalWrite(SCOPE_PIN, LOW); }
#define SCOPE_HIGH 	digitalWrite(SCOPE_PIN, HIGH);
#define SCOPE_LOW 	digitalWrite(SCOPE_PIN, LOW);
#else
#define SCOPE_INIT 	;
#define SCOPE_PULSE ;
#define SCOPE_HIGH 	;
#define SCOPE_LOW 	;
#endif

class DHT22{
  private:
    uint8_t _pinData;
    uint32_t _timer;
    uint64_t _rawData;
    uint16_t _h16bits;
    uint16_t _t16bits;
    uint8_t _crc8bits;
    uint8_t _timing80L;
    uint8_t _timing80H;
    uint8_t _timing50;
    uint8_t _timingBit0;
    uint8_t _timingBit1;
    bool _initialized = false;
    bool _powerOn = true;
	bool _dataAvailable = false;
	bool _recoveryInProgress = false;
	uint16_t _error;
	
    const uint8_t T=30;

    
    public:
    //dht22 sampling rate ~0.5Hz
    static const int cSamplingTime = 2100; // ms
    
    enum error{
      OK = 0,
      BUSY,
      POWER_ON,
      ERR_TIMING_80,
      ERR_TIMING_50,
      ERR_TIMING_BITS,
      ERR_CRC,
      ERR_MEASURE = 10
    };

  
    DHT22(uint8_t pinData){
      _pinData = pinData;
    };
    
    /** @return 0 on success **/
    int begin();
    
    /** @return 0 on success**/
    int recover();
    
    /** @return True while conversion in progress**/
    bool conversionInProgress();
    
    /** @return 40bits of data sensor : h16 + t16 + crc8**/
    uint64_t getRawData();

    /** @return 40bits in a String ("0" left include)**/
    String getRawStrData();

    /** @return humidity %rH **/
    float getHumidity();
    
    /** @return temperature in °C **/
    float getTemperature();

    /** @return String with timings, 40bits, and calculate values**/
    String debug();

	/** @return Returncode from last readSensor() request **/
	uint16_t getError();
	
	 /**
    *@brief read the 40bits sensor data
    *@return 0 if no error, num of error instead
    */
    int readSensor();
    
  private:
    /** @return measure timings of sensor, negative value means sampling error **/
    int measureTimings();

    /** @brief compute checksum of h & t data
     * @return true if checksum==crc**/
    bool computeCRC();
    
    /** @return True when start was issued **/
    bool _startConversion();
};

#endif

