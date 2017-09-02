

TM_GPS_Result_t TM_GPS_Update(TM_GPS_t* GPS_Data) {
	/* Check for data in Ring Buffer */
	if (!GPS_RING_BUFFER_EMPTY) {
		/* Go through all buffer */
		while (!GPS_RING_BUFFER_EMPTY) {
			/* Do character by character */
			TM_GPS_INT_Do(GPS_Data, (char)GPS_RING_BUFFER_GET_CHAR);
			/* If new data available, return to user */
			if (GPS_Data->Status == TM_GPS_Result_NewData) {
				return GPS_Data->Status;
			}
		}
	}

	if (TM_GPS_FirstTime) {
		/* No any valid data, return First Data Waiting */
		/* Returning only after power up and calling when no all data is received */
		TM_GPS_INT_ReturnWithStatus(GPS_Data, TM_GPS_Result_FirstDataWaiting);
	}

	/* We have old data */
	TM_GPS_INT_ReturnWithStatus(GPS_Data, TM_GPS_Result_OldData);
}


typedef struct {
	uint8_t *Buffer;
	uint16_t Size;
	uint16_t Num;
	uint16_t In;
	uint16_t Out;
	uint8_t Initialized;
	uint8_t StringDelimiter;
} TM_USART_t;



