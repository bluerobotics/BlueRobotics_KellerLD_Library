#include "KellerLD.h"
#include <Wire.h>

#define LD_ADDR                     0x40
#define LD_REQUEST                  0xAC
#define LD_CUST_ID0                 0x00
#define LD_CUST_ID1                 0x01
#define LD_SCALING0                 0x12
#define LD_SCALING1                 0x13
#define LD_SCALING2                 0x14
#define LD_SCALING3                 0x15
#define LD_SCALING4                 0x16

KellerLD::KellerLD() {
	fluidDensity = 1029;
}

void KellerLD::init() {
	// Request memory map information
	uint16_t cust_id0;
	cust_id0 = readMemoryMap(LD_CUST_ID0);

	uint16_t cust_id1;
	cust_id1 = readMemoryMap(LD_CUST_ID1);

	code = (uint32_t(cust_id1) << 16) | cust_id0;

	uint16_t scaling0;
	scaling0 = readMemoryMap(LD_SCALING0);

	mode = scaling0 & 0b00000011;

	uint32_t scaling12 = (uint32_t(readMemoryMap(LD_SCALING1)) << 16) | readMemoryMap(LD_SCALING2);

	P_min = *reinterpret_cast<float*>(&scaling12);

	uint32_t scaling34 = (uint32_t(readMemoryMap(LD_SCALING3)) << 16) | readMemoryMap(LD_SCALING4);

	P_max = *reinterpret_cast<float*>(&scaling34);
}

void KellerLD::setFluidDensity(float density) {
	fluidDensity = density;
}

void KellerLD::read() {
	uint8_t status;

	Wire.beginTransmission(LD_ADDR);
	Wire.write(LD_REQUEST);
	Wire.endTransmission();

	delay(9); // Max conversion time per datasheet

 	Wire.requestFrom(LD_ADDR,5);
	status = Wire.read();
	uint16_t P = (Wire.read() << 8) | Wire.read();
	uint16_t T = (Wire.read() << 8) | Wire.read();
	
	P_bar = (P-16384)*(P_max-P_min)/32768 + P_min;
	T_degc = ((T>>4)-24)*0.05-50;
}

uint16_t KellerLD::readMemoryMap(uint8_t mtp_address) {
	uint8_t status;

	Wire.beginTransmission(LD_ADDR);
	Wire.write(mtp_address);
	Wire.endTransmission();

	Wire.requestFrom(LD_ADDR,3);
	status = Wire.read();
	return ((Wire.read() << 8) | Wire.read());
}

float KellerLD::pressure(float conversion) {
	return P_bar*1000.0f*conversion;
}

float KellerLD::temperature() {
	return T_degc;
}

float KellerLD::depth() {
	return (pressure(KellerLD::Pa)-101300)/(fluidDensity*9.80665);
}

float KellerLD::altitude() {
	return (1-pow((pressure()/1013.25),0.190284))*145366.45*.3048;
}