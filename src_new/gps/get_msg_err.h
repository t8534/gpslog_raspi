#ifndef GET_MSG_ERR_H_
#define GET_MSG_ERR_H_


typedef enum
{
  OK,
  ERR_NOT_OK,
  ERR_BUFFER_OVERLOADED,   //todo: overloaded information in this .h file.
  ERR_LISTENER_NOT_ADDED,
} GETMSG_ErrStatus_t;



#endif /* GET_MSG_ERR_H_ */
