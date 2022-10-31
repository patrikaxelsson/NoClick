#ifndef _NOCLICK_H_
#define _NOCLICK_H_

#include <exec/execbase.h>

#if defined(__amigaos4__)
void NoClick(struct ExecIFace *IExec);
#elif defined(__MORPHOS__)
void NoClick(struct ExecBase *SysBase);
#else
// Putting SysBase in a6 is not necessary here, it is just to make vbcc
// produce simpler/better code.
void NoClick(__reg("a6") struct ExecBase *SysBase);
#endif

#endif
