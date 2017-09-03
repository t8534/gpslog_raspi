//todo: add defineat begin of file


typedef struct {
	nmea_s base;
	nmea_position longitude;
	nmea_position latitude;
	struct tm time;
} nmea_gprmc_t;


void GPS_PRS_GPRMC_Init();
void GPS_PRS_GPRMC_DeInit(void);
void GPS_PRS_GPRMC_Parser(uint8_t *msg, uint16_t length);
void GPS_PRS_GPRMC_GetData(nmea_gprmc_t *data);

