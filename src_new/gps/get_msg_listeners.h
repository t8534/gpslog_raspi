#ifndef GET_MSG_LISTENERS_H_
#define GET_MSG_LISTENERS_H_

#include "typedefs.h"
#include "get_msg_err.h"
#include "get_msg.h"

typedef void (*Init)(void);
typedef void (*DeInit)(void);
typedef GETMSG_ErrStatus_t (*AddListener)(NewMsgNotify* f);
typedef void (*SendNotify)(MsgNMEA_t *msg);

typedef struct
{
  void (*Init)(void);
  void (*DeInit)(void);
  GETMSG_ErrStatus_t (*AddListener)(NewMsgNotify* f);
  void (*SendNotify)(MsgNMEA_t *msg);
} GETMSG_Listener_if_t;

extern GETMSG_Listener_if_t *GETMSG_ListenerObj;


#endif /* GET_MSG_LISTENERS_H_ */

