	
	HMC5883_SetOperatingMode(HMC5883_SINGLEMEASUREMENT);
	uint8 zmsb = HMC5883_ReadReg(0x05);
	uint8 zlsb = HMC5883_ReadReg(0x06);
	int16 HMC5883z = ((int16)zmsb << 8) | zlsb;
	
	return HMC5883z;