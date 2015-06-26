	
	HMC5883_SetOperatingMode(HMC5883_SINGLEMEASUREMENT);
	uint8 xmsb = HMC5883_ReadReg(0x03);
	uint8 xlsb = HMC5883_ReadReg(0x04);
	int16 HMC5883x = ((int16)xmsb << 8) | xlsb;

	uint8 zmsb = HMC5883_ReadReg(0x05);
	uint8 zlsb = HMC5883_ReadReg(0x06);
	int16 HMC5883z = ((int16)zmsb << 8) | zlsb;

	uint8 ymsb = HMC5883_ReadReg(0x07);
	uint8 ylsb = HMC5883_ReadReg(0x08);
	int16 HMC5883y = ((int16)ymsb << 8) | ylsb;
	
	char valueBuffer[32];
	
	sprintf(valueBuffer, "[%d,%d,%d]", HMC5883x, HMC5883y, HMC5883z);
	
	return valueBuffer;