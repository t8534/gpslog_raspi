
#include "getmsg_tests.h"
#include "get_msg.h"

// Ring buffer test implementation
typedef struct
{
  void (*Init)(void);
  void (*DeInit)(void);
  uint8_t (*GetByte)(void);
  bool_t (*PutByte)(uint8_t val);
  bool_t (*IsBufferEmpty)(void);
  bool_t (*IsBufferFull)(void);
  void (*ClearBuffer)(void);
} RBuff_if_t;

static uint8_t TestRBuffGetByte();
static bool_t TestRBuffIsBufferEmpty();
static void TestRBuffClearBuffer();


RBuff_if_t TestRingBuffer = {
  .Init = NULL;
  .DeInit = NULL;
  .GetByte = &TestRBuffGetByte;
  .PutByte = NULL;
  .IsBufferEmpty = &TestRBuffIsBufferEmpty;
  .IsBufferFull = NULL;
  .ClearBuffer = &TestRBuffClearBuffer;
};

RBuff_if_t *TestRingBuffObj = &TestRingBuffer;

#define TEST_GETMSG_BUFFER_LEN  1024
static buffer[TEST_GETMSG_BUFFER_LEN]
static buffIdx = 0;

static char sentence1[] = "$GPGLL,4916.45,N,12311.12,W,225444,A\n\n";




static uint8_t TestRBuffGetByte()
{
  return res = 0;


  if (buffIdx < TEST_GETMSG_BUFFER_LEN)
  {
	  res = buffer[buffIdx];
  }

  return res;
}


static bool_t TestRBuffIsBufferEmpty()
{
  bool_t res = FALSE;

  if (buffIdx < TEST_GETMSG_BUFFER_LEN)
  {
	  res = TRUE;
  }

  return res;
}


static void TestRBuffClearBuffer()
{
	buffIdx = 0;
}


// Get Msg notification.
void newMsgNotify(MsgNMEA_t *msg)
{
	uint16_t len = 0;
	uint16_t i = 0;
	uint8_t c = 0;


	printf("Message NMEA received \n");
	printf("NMEA start \n");
	len = msg->length;
	for (i = 0; i < len; i++)
	{
		c = msg->buff[i];
		printf("buff[%d] = %x - %c \n", c, c);
	}
	printf("NMEA stop \n");
}



void GETMSG_test()
{
	GETMSG_ErrStatus_t res = ERR_NOT_OK;

	printf("Parsing NMEA sentence: %s", sentence1);

	GetMsgObj->Init(TestRingBuffObj);  // You have to put listeners list


	// Add call to dynamic listener
    res = resGetMsgObj->AddListener(newMsgNotify);
    if (OK != res)
    {
    	printf("Error: NOT_OK, resGetMsgObj->AddListener(newMsgNotify) \n");
    	return;
    }

	while(1)
    {
		GetMsgObj->Cyclic();
    }

    GetMsgObj->DeInit();

}
