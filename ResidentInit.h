#ifndef _RESIDENTINIT_H_
#define _RESIDENTINIT_H_

#include <exec/execbase.h>
#include <dos/dos.h>

#if defined(__amigaos4__)
__saveds void ResidentInit(void *zero, BPTR segList, struct ExecBase *sysBase);
#elif defined(__MORPHOS__)
__saveds void *ResidentInit(void *zero, BPTR segList, struct ExecBase *SysBase);
#else
__saveds void *ResidentInit(__reg("d0") void *zero, __reg("a0") BPTR segList, __reg("a6") struct ExecBase *SysBase);
#endif

#endif
