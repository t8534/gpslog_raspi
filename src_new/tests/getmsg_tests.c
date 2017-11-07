#include <stddef.h>
#include <stdint.h>

#include "getmsg_tests.h"
#include "get_msg.h"

// Tests description.
//
// Create test phantom RingBuffer object and fill it with test bytes sentence.
// The pointer to test RingBuffer is put into Get Message Init function.
// In next step Get Message AddListener is called and newMsgNotify() is added
// to the Listener. When message will be received this function will be called,
// with NMEA message as a parameter. The message should be validated by Get Message
// module before call newMsgNotify()
// After notify about new message the code will be still in infinity loop
// at GETMSG_test()
// In order to start tests call GETMSG_test() for tests beginning.
//
// Test cases.
// #1 One, correct sentence, match buffer length.
// Sentence: "$GPGLL,4916.45,N,12311.12,W,225444,A\n\n"
//
// #2 Two correct sentences.
// Sentence: "$GPGLL,4916.45,N,12311.12,W,225444,A\n\n$GPGLL,4916.45,N,12311.12,W,225444,A\n\n"
//
// #3 Five correct sentences, match buffer length.
//
// #4 Two correct sentences and random bytes between, outside of ascii, match ring buffer length.
//
// #4 Corrupted sentence with non ascii bytes inside, len correct.
//
// #5 Corrupted sentence, begin mark but in place of end mark another begin one,
//    first sentence is smaller than should be.
//
// #6 Corrupted sentence, only begin and end mark.
//
// #7 Corrupted sentence, only begin, one ascci byte and end mark.
//
// #8 Corrupted sentence, only end mark.
//
// #9 Corrupted sentence, only begin mark.
//
// #10 Corrupted sentence, random bytes, match buffer length.
//
// #12 Corrupted sentence - wrong crc.









// Test sentences
static char sentence1[] = "$GPGLL,4916.45,N,12311.12,W,225444,A\n\n";


/////////////////////////////////////////////////////////////////////
// Ring buffer test implementation
/////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////



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


	GETMSG_GetMsgObj->Init(TestRingBuffObj);
    res = GETMSG_GetMsgObj->AddListener(newMsgNotify);
    if (OK != res)
    {
    	printf("Error: not OK, GETMSG_GetMsgObj->AddListener(newMsgNotify) \n");
    	return;
    }

	while(1)
    {
		GETMSG_GetMsgObj->Cyclic();
    }

    GETMSG_GetMsgObj->DeInit();

}

