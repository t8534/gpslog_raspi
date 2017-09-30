//
// TODO:
//
// 1.Listener tests
//
// 1.Replace listener table with linked list and malloc.
//

#include <stdint.h>
#include "get_msg_listener.h"


typedef void (*NewMsgNotify)(MsgNMEA_t*);


static void Init(void);
static void DeInit(void);
static void AddListener(NewMsgNotify* f);
static void SendNotify(MsgNMEA_t *msg);


static GETMSG_Listener_if_t ListenerObject = {
  .Init = &Init;
  .DeInit = &DeInit;
  .AddListener = &AddListener;
  .SendNotify = &SendNotify;
};
GETMSG_Listener_if_t *GETMSG_ListenerObj = &ListenerObject;


#define GETMSG_LISTENERS_AMOUNT  2
static NewMsgNotify listeners[GETMSG_LISTENERS_NUMBER];


static void Init(void)
{
  uint16_t i = 0;

  for(i = 0; i < GETMSG_LISTENERS_AMOUNT; i++)
  {
	  listeners[i] = NULL;
  }
}


static void DeInit(void)
{
  uint16_t i = 0;

  for(i = 0; i < GETMSG_LISTENERS_AMOUNT; i++)
  {
	  listeners[i] = NULL;
  }
}


static GETMSG_ErrStatus_t AddListener(NewMsgNotify* f)
{
  GETMSG_ErrStatus_t res = ERR_LISTENER_NOT_ADDED;
  uint16_t i = 0;

  if (NULL == f) return;

  for(i = 0; i < GETMSG_LISTENERS_AMOUNT; i++)
  {
    if (NULL == listeners[i])
    {
      listeners[i] = NewMsgNotify;
      res = OK;
    }
  }

  return res;
}


static void SendNotify(MsgNMEA_t *msg)
{
  uint16_t i = 0;

  for(i = 0; i < GETMSG_LISTENERS_AMOUNT; i++)
  {
	if (NULL != listeners[i])
	{
      (*listeners[i])(msg);
	}
  }

}

