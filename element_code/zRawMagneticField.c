	
	HMC5883_SetOperatingMode(HMC5883_SINGLEMEASUREMENT);
	uint8_t zmsb = HMC5883_ReadReg(0x05);
	uint8_t zlsb = HMC5883_ReadReg(0x06);
	int16_t HMC5883z = ((int16_t)zmsb << 8) | zlsb;
	
	return HMC5883z;