// Copyright (c) 2014, Anaren Inc.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies, 
// either expressed or implied, of the FreeBSD Project.

#ifndef HMC5883_H
#define HMC5883_H

#include "hmc5883_config.h"
#include "types.h"

//------------------------------------------------------------------------------
/**
 *	Defines, enumerations, and structure definitions
 */
#ifndef bool
#define bool uint8
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

//------------------------------------------------------------------------------
/**
 *	Defines, enumerations, and structure definitions
 */

#define HMC5883_SLAVE_BASE_ADDR		0x1E

#define HMC5883_CONFIG_A_REG_ADDR	0x00	// Configuration A
#define HMC5883_CONFIG_B_REG_ADDR	0x01	// Configuration B
#define HMC5883_MODE_REG_ADDR				 0x02	// Mode
#define HMC5883_DATA_X_MSB_REG_ADDR	0x03	// Data Output X MSB (read only)
#define HMC5883_DATA_X_LSB_REG_ADDR	0x04	// Data Output X LSB (read only)
#define HMC5883_DATA_Z_MSB_REG_ADDR	0x05	// Data Output Z MSB (read only)
#define HMC5883_DATA_Z_LSB_REG_ADDR	0x06	// Data Output Z LSB (read only)
#define HMC5883_DATA_Y_MSB_REG_ADDR	0x07	// Data Output Y MSB (read only)
#define HMC5883_DATA_Y_LSB_REG_ADDR	0x08	// Data Output Y LSB (read only)
#define HMC5883_STATUS_REG_ADDR		0x09	// Status (read only)
#define HMC5883_ID_A_REG_ADDR		0x0A	// Identification A (read only)
#define HMC5883_ID_B_REG_ADDR		0x0B	// Identification B (read only)
#define HMC5883_ID_C_REG_ADDR		0x0C	// Identification C (read only)

#define HMC5883_CONFIG_A_REG_MA		0x60
#define HMC5883_CONFIG_A_REG_DO		0x1C
#define HMC5883_CONFIG_A_REG_MS		0x03

#define HMC5883_CONFIG_B_REG_GN		0xE0

#define HMC5883_MODE_REG_MD		0x03
#define HMC5883_MODE_REG_HS		0x80
	 
#define HMC5883_STATUS_REG_RDY		0x01
#define HMC5883_STATUS_REG_LOCK		0x02

/**
 *	eHMC5883SamplesAveraged - type indicating the number of samples averaged per
 *	measurement output.
 */
enum eHMC5883SamplesAveraged
{
	HMC5883_AVGSMPL_1	= 0x00,
	HMC5883_AVGSMPL_2	= 0x20,
	HMC5883_AVGSMPL_4	= 0x40,
	HMC5883_AVGSMPL_8	= 0x60
};

/**
 *	eHMC5883DataOutputRate - type indicating the output rate of the HMC5883
 *	device, specified in Hz, when in continuous measurement mode.
 */
enum eHMC5883DataOutputRate
{
	HMC5883_RATE_0P75HZ	= 0x00,
	HMC5883_RATE_1P5HZ	= 0x04,
	HMC5883_RATE_3HZ	= 0x08,
	HMC5883_RATE_7P5HZ	= 0x0C,
	HMC5883_RATE_15HZ	= 0x10,
	HMC5883_RATE_30HZ	= 0x14,
	HMC5883_RATE_75HZ	= 0x18
};

/**
 *	eHMC5883MeasurementMode - type indicating the measurement mode of the
 *	HMC5883 device.	The HMC5883 offers three modes; Normal, Positive Bias, and
 *	Negative Bias.	Refer to the HMC5883 datasheet for details regarding use of
 *	the bias modes.
 */
enum eHMC5883MeasurementMode
{
	HMC5883_NORMAL		= 0x00,
	HMC5883_POSITIVEBIAS	= 0x01,
	HMC5883_NEGATIVEBIAS	= 0x02
};

/**
 *	eHMC5883Gain - type indicating the gain setting of the HMC5883 device.
 */
enum eHMC5883Gain
{
	HMC5883_GAIN_1370	= 0x00,
	HMC5883_GAIN_1090	= 0x20,
	HMC5883_GAIN_820	= 0x40,
	HMC5883_GAIN_660	= 0x60,
	HMC5883_GAIN_440	= 0x80,
	HMC5883_GAIN_390	= 0xA0,
	HMC5883_GAIN_330	= 0xC0,
	HMC5883_GAIN_230	= 0xE0
};

/**
 *	eHMC5883OperatingMode - type indicating the operating mode of the HMC5883
 *	device.	The HMC5883 offers three modes; Continuous Measurement, Single
 *	Measurement, and Idle.	When ultra-low power consumption is important, the
 *	application should place the device in Idle when measurements are not
 *	required.	While in Continuous Measurement mode, the device automatically
 *	enters a low-power state between samples.	However, this low-power state
 *	draws significantly more current than when in Idle.
 */
enum eHMC5883OperatingMode
{
	HMC5883_CONTINUOUSMEASUREMENT 	= 0x00,
	HMC5883_SINGLEMEASUREMENT	= 0x01,
	HMC5883_IDLE			= 0x02
};

/**
 *	sHMC5883Status - structure defining the HMC5883 status register.
 */
struct sHMC5883Status
{
	bool lock;
	bool rdy;
};


/** 
Write an 8-bit value to a device register.	All of the HMC5883L registers are
read only except for the configuration and mode registers.	This function does
not do any form of error checking, so trying to write to one of the read-only
registers may result in undesireable behavior.
@param addr device register address
@param data data to be written to the specified register address
*/
void HMC5883_WriteReg(uint8 addr, uint8 data);

/** 
Read an 8-bit value from a device register.
@param addr device register address
@return data read from the specified register address
*/
uint8 HMC5883_ReadReg(uint8 addr);

/** 
Read multiple 8-bit register values from the device.	The HMC5883L uses an
address pointer to determine which register to start reading from.	This pointer
is automatically incremented for each register read.
@param addr device register address
@param readBytes pointer to buffer for storing the values read
@param numBytes number of registers to read
*/
void HMC5883_BurstReadReg(uint8 addr, uint8* readBytes, uint8 numBytes);


void HMC5883_SetNumberSamplesAveraged(enum eHMC5883SamplesAveraged samples);
enum eHMC5883SamplesAveraged HMC5883_GetNumberSamplesAveraged(void);

void HMC5883_SetDataOutputRate(enum eHMC5883DataOutputRate rate);
enum eHMC5883DataOutputRate HMC5883_GetDataOutputRate(void);

void HMC5883_SetMeasurementMode(enum eHMC5883MeasurementMode mode);
enum eHMC5883MeasurementMode HMC5883_GetMeasurementMode(void);

void HMC5883_SetGain(enum eHMC5883Gain gain);
enum eHMC5883Gain HMC5883_GetGain(void);


float HMC5883_GetHeading(void);


/**
Select the device operating mode.	Refer to eHMC5883OperatingMode definition for
details regarding the allowed states.
@param mode specifies the device mode of operation
*/
void HMC5883_SetOperatingMode(enum eHMC5883OperatingMode mode);

/**
Read the currently selected operating mode.	Refer to eHMC5883OperatingMode
definition for details regarding the available states.
@return device mode of operation
*/
enum eHMC5883OperatingMode HMC5883_GetOperatingMode(void);

/**
Read the current status of the device.
@return device status
*/
struct sHMC5883Status HMC5883_GetStatus(void);

/**
Read ID Register A.
@return contents of ID Register A.	Value always = 0x48 (ascii 'H').
*/
uint8 HMC5883_GetIdRegA(void);

/**
Read ID Register B.
@return contents of ID Register B.	Value always = 0x34 (ascii '4').
*/
uint8 HMC5883_GetIdRegB(void);

/**
Read ID Register C.
@return contents of ID Register C.	Value always = 0x33 (ascii '3').
*/
uint8 HMC5883_GetIdRegC(void);


#endif	/* HMC5883_H */
