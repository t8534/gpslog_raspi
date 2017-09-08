



typedef void (*newMsgNotify)(MsgNMEA_t*);
typedef void (*initListener)(void);
typedef void (*addListener)(newMsgNotify* f);

#define LISTENERS_AMOUNT  1
static struct GETMSG_LISTENER
{
  initListener = &GETMSG_initListener;
  addListener = &GETMSG_addListener;
  newMsgNotify listeners[LISTENERS_NUMBER];
  uint16_t listenerIdx
} GETMSG_Listener;

GETMSG_LISTENER *GETMSG_ListenerObj = &GETMSG_Listener;

static void GETMSG_initListener()
{
  uint16_t i = 0;


  for(i = 0; i < LISTENERS_AMOUNT; i++)
  {
    GETMSG_Listener.listeners[i] = NULL;
  }
  GETMSG_Listener.listenerIdx = 0;

}

//todo: return is add done or not possible.
static void GETMSG_addListener(newMsgNotify* f)
{
  if (NULL != f)
  {
    for(i = 0; i < LISTENERS_AMOUNT; i++)
    {
    
    }
  }


}
