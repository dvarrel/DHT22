/*!
 * @file DHT22.h
 * @brief Arduino library for interface with DHT22 sensor 
 * @n without use of pointers.
 * @author dvarrel
 * @version  1.0.0
 * @date  2022-11-09
 * @url https://github.com/dvarrel/DHT22.git
 */
#ifndef _DHT22_H
#define _DHT22_H
#include "Arduino.h"

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
    bool _firstStart=true;

    const uint8_t T=30;
    enum error{
      OK,
      ERR_TIMING_80,
      ERR_TIMING_50,
      ERR_TIMING_BITS,
      ERR_CRC
    };

  public:
    DHT22(uint8_t pinData){
      _pinData = pinData;
    };
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

  private:
    /** @brief measure timings of sensor*/
    void measureTimings();

    /**
    *@brief read the 40bits sensor data
    *@return 0 if no error, num of error instead
    */
    uint16_t readSensor();

    /** @brief compute checksum of h & t data
     * @return true if checksum==crc**/
    bool computeCRC();
    
};

#endif

