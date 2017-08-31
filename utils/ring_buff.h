
//todo add ifded



//TODO: It should be optimized to use many RingBuffers, OOP.


void RB_Init(void);

void RB_DeInit(void);

//bool_t RB_GetByte(uint8_t* val);
uint8_t RB_GetByte();

bool_t RB_PutByte(uint8_t val);

bool_t RB_IsBufferEmpty(void);

bool_t RB_IsBufferFull(void);

void RB_ClearBuffer(void);

