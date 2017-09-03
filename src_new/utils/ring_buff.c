
#include "ring_buff.h"

#define RB_BUFF_SIZE  1024
static uint8_t buff[RB_BUFF_SIZE];

typedef struct {
	uint8_t *Buffer;
	uint16_t Size;
	uint16_t Num;
	uint16_t In;
	uint16_t Out;
} RB_RingBuffer_t;

static RB_RingBuffer_t RB_RingBuff;
static RB_RingBuffer_t* u = &RB_RingBuff;  //TODO: refactoring, pointer because original code has functions
                                           // with pointer as an argument.

void RB_Init()
{
	u->Buffer = &buff[0];
	u->Size = RB_BUFF_SIZE;
	u->Num = 0;
	u->In = 0;
	u->Out = 0;

}

void RB_DeInit()
{

}

#if 0
//TODO: This function is better then without check result.
//      If get byte from empty buffer it return 0, so the check for result is necessary.
//TODO: Add CRITICAL_SECTION
//
// Result: Return FALSE if Buffer empty, or byte in parameter and TRUE.
bool_t RB_GetByte(uint8_t* val)
{
	//uint8_t c = 0; // Bug, if nothing in the buffer 0 will be returned.
	bool_t res = FALSE;

	/* Check if we have any data in buffer */
	if (u->Num > 0) {
		if (u->Out == u->Size) {
			u->Out = 0;
		}
		*val = *(u->Buffer + u->Out);
		u->Out++;
		u->Num--;
		res = TRUE;
	}

	return res;
}
#endif



//TODO: This is original function to cooperate with gps lib.
//      This function is danger because return 0 if buffer was empty.
//      Replace it with version above.
//
//
//TODO: Add CRITICAL_SECTION
//
// Result: Return 0 even if buffer empty, check is buffer not empty before call !
uint8_t RB_GetByte()
{
	uint8_t c = 0; // ! If nothing in the buffer 0 will be returned.

	/* Check if we have any data in buffer */
	if (u->Num > 0) {
		if (u->Out == u->Size) {
			u->Out = 0;
		}
		c = *(u->Buffer + u->Out);
		u->Out++;
		u->Num--;
	}

	return c;
}






//TODO: Add CRITICAL_SECTION
//
//Return TRUE is byte added or FALSE if Buffer is full.
bool_t RB_PutByte(uint8_t val)
{
	bool_t res= FALSE;

	/* Still available space in buffer */
	if (u->Num < u->Size) {
		/* Check overflow */
		if (u->In == u->Size) {
			u->In = 0;
		}

		/* Add to buffer */
		u->Buffer[u->In] = val;
		u->In++;
		u->Num++;
		res = TRUE;
	}
}




bool_t RB_IsBufferEmpty(void)
{
	/* Check if number of characters is zero in buffer */
	return (u->Num == 0);
}


bool_t RB_IsBufferFull(void)
{
	/* Check if number of characters is the same as buffer size */
	return (u->Num == u->Size);
}


void RB_ClearBuffer(void)
{
	uint16_t i = 0;

	u->Num = 0;
	u->In = 0;
	u->Out = 0;
	for (i = 0; i < u->Size; i++)
	{
		u->Buffer[i] = 0;
	}
}

