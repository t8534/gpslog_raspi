
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
// 3.
// Add dynamic listeners.
//

#include "get_msg.h"


#define MSG_BEGIN  '$'   // 0x24
#define MSG_END    0x0A  //The end of message is <CR><LF>, so in practice this is <LF> hex: 0x0A


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


static Status_t status = IDLE;
static MsgReceivingState_t msgParsingStatus = MSG_WAITING_FOR_BEGIN;
MsgNMEA_t msgData;

static RingBuffer *ringBuff;



//todo: is functions below could be static ? So, in general is it possible
//      to have a function static and get acceess to it by pointer from struct
//      based pointer ? .If possible, remove RB_ prefix.
//todo: is it possible to have static variable, and global pointer to her,
//      and have an access via pointer ?
GetMsg_if_t GetMsgObject = {
  .Init = &GETMSG__Init;
  .DeInit = &GETMSG__DeInit;
  .Cyclic = &GETMSG__GetByte;
  .AddListener = &GETMSG_AddListener;
};
GetMsg_if_t *GetMsgObj = &GetMsgObject;


void GETMSG_Init(RingBuffer *rb);
void GETMSG_DeInit(void);
void GETMSG_Cyclic(void);
GETMSG_ErrStatus_t GETMSG_AddListener(newMsgNotify *notifyFnc);

static GETMSG_ErrStatus_t CollectingBytes(RingBuffer *rb);
static GETMSG_ErrStatus_t ValidateMsg(MsgNMEA_t *msg);


void GETMSG_Init(RingBuffer *rb)
{
  ringBuff = rb;
  status = INIT;
  msgParsingStatus = MSG_WAITING_FOR_BEGIN;

  //todo: clean listeners table

}


void GETMSG_DeInit()
{

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


GETMSG_ErrStatus_t GETMSG_AddListener(newMsgNotify *notifyFnc)
{
	GETMSG_ErrStatus_t res = ERR_NOT_OK;
  if



}



// Called periodically from GETMSG_Cyclic()
static GETMSG_ErrStatus_t CollectingBytes(RBuff_if_t *rb)
{
  uint8_t byte = 0;
  static uint16_t bufIdx = 0;
  ErrStatus_t res = OK;

  switch(msgParsingStatus)
  {
    case MSG_WAITING_FOR_BEGIN:
      while(TRUE != rb->IsBufferEmpty())
      {
        byte = rb->GetByte();
        if (MSG_BEGIN != byte) continue;  // what about any timeout here, not necessary ?
        msgData.buff[bufIdx] = byte;
        bufIdx++;
        msgData.length++;
        msgParsingStatus = MSG_COLLECTING;
      }
      break;

    case MSG_COLLECTING:
      while(TRUE != rb->IsBufferEmpty())  // what about any timeout here, not necessary ?
      {                                  // what about if we not receiving end of msg and buff will be full.
        byte = rb->GetByte();
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
          for (bufIdx = 0; bufIdx < MSG_BUFFER_LENGHT)
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

        for (bufIdx = 0; bufIdx < MSG_BUFFER_LENGHT)
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


static GETMSG_ErrStatus_t ValidateMsg(MsgNMEA_t* msg)
{
	GETMSG_ErrStatus_t res = OK;





  return res;
}


