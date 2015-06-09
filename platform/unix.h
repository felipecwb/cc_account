/*
 *
 * API platform UNIX
 *
 */

#ifndef _CC_PLATFORM
#define _CC_PLATFORM

#include <stdlib.h>

#define CC_PAUSE system("read __cc_buffer");
#define CC_CLEAR system("clear");

#endif //_CC_PLATFORM

