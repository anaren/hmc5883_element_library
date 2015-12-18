/**
 *	----------------------------------------------------------------------------
 *	Copyright (c) 2014, Anaren Microwave, Inc.
 *
 *	For more information on licensing, please see Anaren Microwave, Inc's
 *	end user software licensing agreement: EULA.txt.
 *
 *	----------------------------------------------------------------------------
 *
 *	hmc5883.c - driver interface for the Honeywell HMC5883L 3-Axis Digital
 *	Compass.
 *
 *	@version		1.0.00
 *	@date			 31 Jul 2014
 *	@author		 Anaren, air@anaren.com
 *
 *	assumptions
 *	===========
 *	- The i2c driver provides the proper signaling sequences for read & write
 *		operations.
 *	- The i2c driver meets the timing requirements specified in the HMC5883L
 *		datasheet.
 *
 *	file dependency
 *	===============
 *	i2c.h : defines the i2c read & write interfaces.
 *
 *	revision history
 *	================
 *	ver 1.0.00 : 31 Jul 2014
 *	- initial release
 */

#include "hmc5883.h"
#include "../i2c/i2c.h"


// -----------------------------------------------------------------------------
/**
 *	Global data
 */

// -----------------------------------------------------------------------------
/**
 *	Private interface
 */

// -----------------------------------------------------------------------------
/**
 *	Public interface
 */

void HMC5883_WriteReg(uint8_t addr, uint8_t data)
{
	uint8_t writeBytes[2];

	writeBytes[0] = addr;
	writeBytes[1] = data;
	AIR_I2C_Write(HMC5883_SLAVE_BASE_ADDR, writeBytes, 2);
}

uint8_t HMC5883_ReadReg(uint8_t addr)
{
	uint8_t readByte;

	AIR_I2C_Write(HMC5883_SLAVE_BASE_ADDR, &addr, 1);
	AIR_I2C_ComboRead(HMC5883_SLAVE_BASE_ADDR, NULL, 0, &readByte, 1);
	return readByte;
}

void HMC5883_BurstReadReg(uint8_t addr, uint8_t* readBytes, uint8_t numBytes)
{
	AIR_I2C_Write(HMC5883_SLAVE_BASE_ADDR, &addr, 1);
	AIR_I2C_ComboRead(HMC5883_SLAVE_BASE_ADDR, NULL, 0, readBytes, numBytes);
}



void HMC5883_SetNumberSamplesAveraged(enum eHMC5883SamplesAveraged samples)
{
	uint8_t data = HMC5883_ReadReg(HMC5883_CONFIG_A_REG_ADDR);
	
	data &= ~HMC5883_CONFIG_A_REG_MA;
	data |= (uint8_t)samples;
	HMC5883_WriteReg(HMC5883_CONFIG_A_REG_ADDR, data);
}

enum eHMC5883SamplesAveraged HMC5883_GetNumberSamplesAveraged(void)
{
	return (enum eHMC5883SamplesAveraged)(HMC5883_ReadReg(HMC5883_CONFIG_A_REG_ADDR) & HMC5883_CONFIG_A_REG_MA);
}

void HMC5883_SetDataOutputRate(enum eHMC5883DataOutputRate rate)
{
	uint8_t data = HMC5883_ReadReg(HMC5883_CONFIG_A_REG_ADDR);
	
	data &= ~HMC5883_CONFIG_A_REG_DO;
	data |= (uint8_t)rate;
	HMC5883_WriteReg(HMC5883_CONFIG_A_REG_ADDR, data);
}

enum eHMC5883DataOutputRate HMC5883_GetDataOutputRate(void)
{
	return (enum eHMC5883DataOutputRate)(HMC5883_ReadReg(HMC5883_CONFIG_A_REG_ADDR) & HMC5883_CONFIG_A_REG_DO);
}

void HMC5883_SetMeasurementMode(enum eHMC5883MeasurementMode mode)
{
	uint8_t data = HMC5883_ReadReg(HMC5883_CONFIG_A_REG_ADDR);
	
	data &= ~HMC5883_CONFIG_A_REG_MS;
	data |= (uint8_t)mode;
	HMC5883_WriteReg(HMC5883_CONFIG_A_REG_ADDR, data);
}

enum eHMC5883MeasurementMode HMC5883_GetMeasurementMode(void)
{
	return (enum eHMC5883MeasurementMode)(HMC5883_ReadReg(HMC5883_CONFIG_A_REG_ADDR) & HMC5883_CONFIG_A_REG_MS);
}

void HMC5883_SetGain(enum eHMC5883Gain gain)
{
	uint8_t data = HMC5883_ReadReg(HMC5883_CONFIG_B_REG_ADDR);
	
	data &= ~HMC5883_CONFIG_B_REG_GN;
	data |= (uint8_t)gain;
	HMC5883_WriteReg(HMC5883_CONFIG_B_REG_ADDR, data);
}

enum eHMC5883Gain HMC5883_GetGain(void)
{
	return (enum eHMC5883Gain)(HMC5883_ReadReg(HMC5883_CONFIG_B_REG_ADDR) & HMC5883_CONFIG_B_REG_GN);
}


void HMC5883_SetOperatingMode(enum eHMC5883OperatingMode mode)
{
	uint8_t data = HMC5883_ReadReg(HMC5883_MODE_REG_ADDR);
	
	data &= ~HMC5883_MODE_REG_MD;
	data |= (uint8_t)mode;
	HMC5883_WriteReg(HMC5883_MODE_REG_ADDR, data);
}

enum eHMC5883OperatingMode HMC5883_GetOperatingMode(void)
{
	return (enum eHMC5883OperatingMode)(HMC5883_ReadReg(HMC5883_MODE_REG_ADDR) & HMC5883_MODE_REG_MD);
}

struct sHMC5883Status HMC5883_GetStatus(void)
{
	struct sHMC5883Status status;
	uint8_t data = HMC5883_ReadReg(HMC5883_STATUS_REG_ADDR);

	status.rdy = (data & HMC5883_STATUS_REG_RDY) ? true : false;
	status.lock = (data & HMC5883_STATUS_REG_LOCK) ? true : false;

	return status;
}

uint8_t HMC5883_GetIdRegA(void)
{
	return HMC5883_ReadReg(HMC5883_ID_A_REG_ADDR);
}

uint8_t HMC5883_GetIdRegB(void)
{
	return HMC5883_ReadReg(HMC5883_ID_B_REG_ADDR);
}

uint8_t HMC5883_GetIdRegC(void)
{
	return HMC5883_ReadReg(HMC5883_ID_C_REG_ADDR);
}
