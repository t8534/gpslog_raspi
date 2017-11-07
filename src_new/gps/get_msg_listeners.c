//
// TODO:
//
// 1.Listener tests
//
// 1.Replace listener table with linked list and malloc.
//

#include <stdint.h>
#include <stddef.h>
#include "src_new/gps/get_msg_listeners.h"


//todo: what about static functions
void GETMSGLISTN_Init(void);
void GETMSGLISTN_DeInit(void);
GETMSG_ErrStatus_t GETMSGLISTN_AddListener(NewMsgNotify* f);
void GETMSGLISTN_SendNotify(MsgNMEA_t *msg);


static GETMSG_Listener_if_t ListenerObject = {
  .Init = &GETMSGLISTN_Init,
  .DeInit = &GETMSGLISTN_DeInit,
  .AddListener = &GETMSGLISTN_AddListener,
  .SendNotify = &GETMSGLISTN_SendNotify,
};
GETMSG_Listener_if_t *GETMSG_ListenerObj = &ListenerObject;


#define GETMSG_LISTENERS_NUMBER  2
static NewMsgNotify listeners[GETMSG_LISTENERS_NUMBER];


void GETMSGLISTN_Init(void)
{
  uint16_t i = 0;

  for(i = 0; i < GETMSG_LISTENERS_NUMBER; i++)
  {
	  listeners[i] = NULL;
  }
}


void GETMSGLISTN_DeInit(void)
{
  uint16_t i = 0;

  for(i = 0; i < GETMSG_LISTENERS_NUMBER; i++)
  {
	  listeners[i] = NULL;
  }
}


GETMSG_ErrStatus_t GETMSGLISTN_AddListener(NewMsgNotify* f)
{
  GETMSG_ErrStatus_t res = ERR_LISTENER_NOT_ADDED;
  uint16_t i = 0;

  if (NULL == f) return res;

  for(i = 0; i < GETMSG_LISTENERS_NUMBER; i++)
  {
    if (NULL == listeners[i])
    {
      listeners[i] = f;
      res = OK;
    }
  }

  return res;
}


void GETMSGLISTN_SendNotify(MsgNMEA_t *msg)
{
  uint16_t i = 0;

  for(i = 0; i < GETMSG_LISTENERS_NUMBER; i++)
  {
	if (NULL != listeners[i])
	{
      (*listeners[i])(msg);
	}
  }

}

