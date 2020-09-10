#ifndef DEBUGGER_NEW_H_
#define DEBUGGER_NEW_H_

#ifndef NDEBUG


#include "TracerNew.h"

#define new new(__FILE__, __LINE__)


#endif // NDEBUG

#endif // !DEBUGGER_NEW_H_
