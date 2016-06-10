	
	HMC5883_SetOperatingMode(HMC5883_SINGLEMEASUREMENT);
	uint8_t xmsb = HMC5883_ReadReg(0x03);
	uint8_t xlsb = HMC5883_ReadReg(0x04);
	int16_t HMC5883x = ((int16_t)xmsb << 8) | xlsb;

	uint8_t zmsb = HMC5883_ReadReg(0x05);
	uint8_t zlsb = HMC5883_ReadReg(0x06);
	int16_t HMC5883z = ((int16_t)zmsb << 8) | zlsb;

	uint8_t ymsb = HMC5883_ReadReg(0x07);
	uint8_t ylsb = HMC5883_ReadReg(0x08);
	int16_t HMC5883y = ((int16_t)ymsb << 8) | ylsb;
	
	static char valueBuffer[32];
	
	sprintf(valueBuffer, "[%d,%d,%d]", HMC5883x, HMC5883y, HMC5883z);
	
	return valueBuffer;