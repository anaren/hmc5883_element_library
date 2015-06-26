	
	HMC5883_SetOperatingMode(HMC5883_SINGLEMEASUREMENT);
	uint8 xmsb = HMC5883_ReadReg(0x03);
	uint8 xlsb = HMC5883_ReadReg(0x04);
	int16 HMC5883x = ((int16)xmsb << 8) | xlsb;
	
	return HMC5883x;
	
