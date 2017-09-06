
//TODO:
// 1.
// Add kind of interface for input from ring buffer.
// It could be struct represent interface, and than you can call a function from inside.
// It safe encapsulation if a function name will be changed inside of ring buffer module.
//
// 2.
// Add interface by vritual table when you read functions from listener.
// It safe encapsulation if a function name will be changed inside of listener module.
//

#define MSG_BEGIN  '$'   // 0x24
#define MSG_END    0x0A  //The end of message is <CR><LF>, so in practice this is <LF> hex: 0x0A


#define MSG_BUFFER_LENGHT  2048
typedef struct {
  uint8_t buff[MSG_BUFFER_LENGHT];
  uint8_t length;
} MsgNMEA_t;


typedef enum
{
  IDLE,
  INIT,
  RUN,
  DEINIT,
} Status_t;


typedef enum
{
  MSG_WAITING_FOR_BEGIN,
  MSG_COLLECTING,
  MSG_RECEIVED,
} MsgReceivingState_t;


typedef enum
{
  OK,
  ERR_NOT_OK,
  ERR_BUFFER_OVERLOADED,
} ErrStatus_t;


// Listeners
#define LISTENERS_AMOUNT  1
typedef void (*newMsgNotify)(MsgNMEA_t*)
static newMsgNotify listeners[LISTENERS_NUMBER] = {};


static Status_t status = IDLE;
static MsgReceivingState_t msgParsingStatus = MSG_WAITING_FOR_BEGIN;
MsgNMEA_t msgData;

static RingBuffer *ringBuff;

void GETMSG_Init(RingBuffer *rb);
void GETMSG_DeInit(void);
void GETMSG_Cyclic(void);

static ErrStatus_t CollectingBytes(RingBuffer *rb);
static ErrStatus_t ValidateMsg(MsgNMEA_t *msg);


void GETMSG_Init(RingBuffer *rb)
{
  ringBuff = rb;
  status = INIT;
  msgParsingStatus = MSG_WAITING_FOR_BEGIN;
}


void GETMSG_Cyclic()
{
  switch(status)
  {
    case INIT:
      break;

    case RUN:
      CollectingBytes(ringBuff);  // Check for faults returned.
      break;

    case IDLE:
      break;

    default:
  }


}


// Called periodically from GETMSG_Cyclic()
ErrStatus_t CollectingBytes(RingBuffer *rb)
{
  uint8_t byte = 0;
  static uint16_t bufIdx = 0;
  ErrStatus_t res = OK;

  switch(msgParsingStatus)
  {
    case MSG_WAITING_FOR_BEGIN:
      while(TRUE != rb->RB_IsBufferEmpty())
      {
        byte = rb->RB_GetByte();
        if (MSG_BEGIN != byte) continue;  // what about any timeout here, not necessary ?
        msgData.buff[bufIdx] = byte;
        bufIdx++;
        msgData.length++;
        msgParsingStatus = MSG_COLLECTING;
      }
      break;

    case MSG_COLLECTING:
      while(TRUE != rb->RB_IsBufferEmpty())  // what about any timeout here, not necessary ?
      {                                  // what about if we not receiving end of msg and buff will be full.
        byte = rb->RB_GetByte();
        msgData.buff[bufIdx] = byte;
        msgData.length++;
        bufIdx++;

        if (MSG_END == byte)
        {
          msgParsingStatus = MSG_RECEIVED;
        };

        if (bufIdx >= MSG_BUFFER_LENGHT && MSG_END != byte)  //replace sides, abd what about Msg end condition.
        {
          // The buffer is full and there was not end of message sign received,
          // clear all data and start again from beginning.
          for (bufIdx = 0; bufIdx <= MSG_BUFFER_LENGHT)
          {
            msgData.buff[bufIdx] = 0;
          }
          msgData.length = 0;
          bufIdx = 0;
          msgParsingStatus = MSG_WAITING_FOR_BEGIN;
          res = ERR_BUFFER_OVERLOADED;
        }

      }
      break;

    case MSG_RECEIVED:
        // push message outside (should it be buffered anywhere outside ?), clear buffer, set states to init.
        for (i = 0; i < LISTENERS_AMOUNT)
        {
          (*newMsgNotify[i])(msgData);
        }

        for (bufIdx = 0; bufIdx <= MSG_BUFFER_LENGHT)
        {
          msgData.buff[bufIdx] = 0;
        }
        msgData.length = 0;
        bufIdx = 0;

        msgParsingStatus = MSG_WAITING_FOR_BEGIN;
      break;

    default:
      msgParsingStatus = ERR_NOT_OK;
      break;

  }

  return res;
}


ErrStatus_t ValidateMsg(MsgNMEA_t* msg)
{
  ErrStatus_t res = OK;





  return res;
}


