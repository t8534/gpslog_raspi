#ifndef GET_MSG_H_
#define GET_MSG_H_

#include <stdint.h>
#include "get_msg_err.h"
#include "get_msg_listeners.h"
#include "ring_buff.h"


#define MSG_BUFFER_LENGHT  2048
typedef struct {
  uint8_t buff[MSG_BUFFER_LENGHT];
  uint16_t length;
} MsgNMEA_t;


typedef struct
{
  void (*Init)(RBuff_if_t *rb);
  void (*DeInit)(void);
  void (*Cyclic)(void);
  GETMSG_ErrStatus_t (*AddListener)(newMsgNotify);
} GETMSG_GetMsg_if_t;

extern GETMSG_GetMsg_if_t *GETMSG_GetMsgObj;


#endif /* GET_MSG_H_ */
