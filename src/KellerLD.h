/* Blue Robotics Arduino Keller LD Pressure/Temperature Sensor Library
----------------------------------------------------------------------
 
Title: Blue Robotics Arduino Keller LD Pressure/Temperature Sensor Library

Description: This library provides utilities to communicate with and to
read data from the Keller 4LD - 9LD pressure/temperature sensors.

Authors: Rustom Jehangir, Blue Robotics Inc.

-------------------------------
The MIT License (MIT)

Copyright (c) 2017 Blue Robotics Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-------------------------------*/ 

#ifndef KELLERLD_H_BLUEROBOTICS
#define KELLERLD_H_BLUEROBOTICS

#include "Arduino.h"

class KellerLD {
public:
	static constexpr float Pa = 100.0f;
	static constexpr float bar = 0.001f;
	static constexpr float mbar = 1.0f;

	KellerLD();

	explicit KellerLD(int i2cAddress);

  /** Reads the onboard memory map to determine min and max pressure as 
   *  well as manufacture date, mode, and customer ID.
   */
	void init();

	/** Provide the density of the working fluid in kg/m^3. Default is for 
	 * seawater. Should be 997 for freshwater.
	 */
	void setFluidDensity(float density);

	/** The read from I2C takes up for 40 ms, so use sparingly is possible.
	 */
	void read();

	/** Checks if the attached sensor is connected or not. */
	bool status();

	/** Returns current range of the attached sensor. */
	float range();

	/** Pressure returned in mbar or mbar*conversion rate.
	 */
	float pressure(float conversion = 1.0f);

	/** Temperature returned in deg C.
	 */
	float temperature();

	/** Depth returned in meters (valid for operation in incompressible
	 *  liquids only. Uses density that is set for fresh or seawater.
	 */
	float depth();

	/** Altitude returned in meters (valid for operation in air only).
	 */
	float altitude();

	/** Return true if the sensor has been initialized and detected. */
	bool isInitialized();

	uint16_t equipment;
	uint16_t place;
	uint16_t file;

	uint8_t mode;
	uint16_t calibrationYear;
	uint8_t calibrationMonth;
	uint8_t calibrationDay;

	uint32_t code;

	uint16_t P;
	float P_bar;
	float P_mode;
	float P_min;
	float P_max;

private:
	float fluidDensity = 1029;
	float T_degc;

	uint16_t cust_id0;
	uint16_t cust_id1;

	uint16_t readMemoryMap(uint8_t mtp_address);

    const int i2cAddress;
};

#endif
