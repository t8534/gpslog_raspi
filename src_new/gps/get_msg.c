
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
//

#include <stddef.h>
#include "get_msg.h"
#include "src_new/gps/get_msg_listeners.h"
//#include "get_msg_listeners.h"


#define GETMSG_MSG_BEGIN  '$'   // 0x24
#define GETMSG_MSG_END    0x0A  //The end of message is <CR><LF>, so in practice this is <LF> hex: 0x0A


typedef enum
{
  IDLE,
  INIT,
  RUN,
  DEINIT,
} GETMSG_Status_t;


typedef enum
{
  MSG_WAITING_FOR_BEGIN,
  MSG_COLLECTING,
  MSG_RECEIVED,
} GETMSG_MsgReceivingState_t;


static GETMSG_Status_t status = IDLE;
static GETMSG_MsgReceivingState_t msgParsingStatus = MSG_WAITING_FOR_BEGIN;
MsgNMEA_t msgData;  //todo Is it static or/and pointer

static RBuff_if_t *ringBuff;

void GETMSG_Init(RBuff_if_t *rb);
void GETMSG_DeInit(void);
void GETMSG_Cyclic(void);
GETMSG_ErrStatus_t GETMSG_AddListener(NewMsgNotify *notifyFnc);

GETMSG_ErrStatus_t GETMSG_CollectingBytes(RBuff_if_t *rb);
GETMSG_ErrStatus_t GETMSG_ValidateMsg(MsgNMEA_t *msg);


//todo: is functions below could be static ? So, in general is it possible
//      to have a function static and get acceess to it by pointer from struct
//      based pointer ? .If possible, remove RB_ prefix.
//todo: is it possible to have static variable, and global pointer to her,
//      and have an access via pointer ?
GETMSG_GetMsg_if_t GetMsgObject = {
  .Init = &GETMSG_Init,
  .DeInit = &GETMSG_DeInit,
  .Cyclic = &GETMSG_Cyclic,
  .AddListener = &GETMSG_AddListener,
};
GETMSG_GetMsg_if_t *GETMSG_GetMsgObj = &GetMsgObject;


void GETMSG_Init(RBuff_if_t *rb)
{
  ringBuff = rb;
  status = INIT;
  msgParsingStatus = MSG_WAITING_FOR_BEGIN;

  GETMSG_ListenerObj->Init();
}


void GETMSG_DeInit()
{
  GETMSG_ListenerObj->DeInit();
}


void GETMSG_Cyclic()
{
  switch(status)
  {
    case INIT:
      break;

    case RUN:
      GETMSG_CollectingBytes(ringBuff);  //todo Check for faults returned.
      break;

    case IDLE:
      break;

    default:
    	break;

  }

}


GETMSG_ErrStatus_t GETMSG_AddListener(NewMsgNotify *notifyFnc)
{
  GETMSG_ErrStatus_t res = ERR_LISTENER_NOT_ADDED;

  if (NULL == notifyFnc) return res;
  res = GETMSG_ListenerObj->AddListener(notifyFnc);

  return res;
}



// Called periodically from GETMSG_Cyclic()
GETMSG_ErrStatus_t GETMSG_CollectingBytes(RBuff_if_t *rb)
{
  uint8_t byte = 0;
  uint16_t i = 0;
  static uint16_t bufIdx = 0;
  GETMSG_ErrStatus_t res = OK;

  switch(msgParsingStatus)
  {
    case MSG_WAITING_FOR_BEGIN:
      while(TRUE != rb->IsBufferEmpty())
      {
        byte = rb->GetByte();
        if (GETMSG_MSG_BEGIN != byte) continue;  // what about any timeout here, not necessary ?
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

        if (GETMSG_MSG_END == byte)
        {
          msgParsingStatus = MSG_RECEIVED;
        };

        if (bufIdx >= MSG_BUFFER_LENGHT && GETMSG_MSG_END != byte)  //replace sides, abd what about Msg end condition.
        {
          // The buffer is full and there was not end of message sign received,
          // clear all data and start again from beginning.
          for (bufIdx = 0; bufIdx < MSG_BUFFER_LENGHT; bufIdx++)
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
    	//todo redesing ! GETMSG_LISTENERS_NUMBER is not, and cannot be available here
#if 0
        for (i = 0; i < GETMSG_LISTENERS_NUMBER; i++)  //todo GETMSG_LISTENERS_NUMBER defined at listeners break OpenClose principle,
        {
          (*newMsgNotify[i])(msgData);
        }
#endif
        for (bufIdx = 0; bufIdx < MSG_BUFFER_LENGHT; bufIdx++)
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


GETMSG_ErrStatus_t GETMSG_ValidateMsg(MsgNMEA_t* msg)
{
	GETMSG_ErrStatus_t res = OK;





  return res;
}


