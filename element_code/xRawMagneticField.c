	
	HMC5883_SetOperatingMode(HMC5883_SINGLEMEASUREMENT);
	uint8_t xmsb = HMC5883_ReadReg(0x03);
	uint8_t xlsb = HMC5883_ReadReg(0x04);
	int16_t HMC5883x = ((int16_t)xmsb << 8) | xlsb;
	
	return HMC5883x;
	
