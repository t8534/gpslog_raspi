#ifndef RING_BUFF_H_
#define RING_BUFF_H_

#include <stdint.h>
#include "sys/typedefs.h"

//TODO: It should be optimized to use many RingBuffers, OOP.


//todo is this typedef could be moved to .c ?
typedef struct
{
  void (*Init)(void);
  void (*DeInit)(void);
  uint8_t (*GetByte)(void);
  bool_t (*PutByte)(uint8_t val);
  bool_t (*IsBufferEmpty)(void);
  bool_t (*IsBufferFull)(void);
  void (*ClearBuffer)(void);
} RBuff_if_t;


extern RBuff_if_t *RingBuffObj;


#endif /* RING_BUFF_H_ */

