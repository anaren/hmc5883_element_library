	
	HMC5883_SetOperatingMode(HMC5883_SINGLEMEASUREMENT);
	uint8 ymsb = HMC5883_ReadReg(0x07);
	uint8 ylsb = HMC5883_ReadReg(0x08);
	int16 HMC5883y = ((int16)ymsb << 8) | ylsb;
	
	return HMC5883y;