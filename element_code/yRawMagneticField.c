	
	HMC5883_SetOperatingMode(HMC5883_SINGLEMEASUREMENT);
	uint8_t ymsb = HMC5883_ReadReg(0x07);
	uint8_t ylsb = HMC5883_ReadReg(0x08);
	int16_t HMC5883y = ((int16_t)ymsb << 8) | ylsb;
	
	return HMC5883y;