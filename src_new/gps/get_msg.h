#ifndef GET_MSG_H_
#define GET_MSG_H_

#include <stdint.h>
#include "ring_buff.h"


#define MSG_BUFFER_LENGHT  2048
typedef struct {
  uint8_t buff[MSG_BUFFER_LENGHT];
  uint16_t length;
} MsgNMEA_t;


typedef enum
{
  OK,
  ERR_NOT_OK,
  ERR_BUFFER_OVERLOADED,   //todo: overloaded information in this .h file.
  ERR_LISTENER_NOT_ADDED,
} GETMSG_ErrStatus_t;


// Notify function type
typedef void (*newMsgNotify)(MsgNMEA_t*)

//todo is this typedef could be moved to .c ?
typedef struct
{
  void (*Init)(RBuff_if_t *rb);  //todo: you have to put listeners list
  void (*DeInit)(void);
  void (*Cyclic)(void);
  GETMSG_ErrStatus_t (*AddListener)(newMsgNotify);
} GetMsg_if_t;

extern GetMsg_if_t *GetMsgObj;


#endif /* GET_MSG_H_ */



