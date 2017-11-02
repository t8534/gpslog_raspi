#ifndef PARSERS_MANAGER_H_
#define PARSERS_MANAGER_H_

#include <stdint.h>
#include "typedefs.h"

void GPS_ParsersManagerInit(void);
void GPS_ParsersManagerDeInit(void);
void GPS_ParsersManagerCyclic(void);


#endif /* PARSERS_MANAGER_H_ */

