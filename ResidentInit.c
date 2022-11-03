#include <exec/execbase.h>
#include <dos/dos.h>
#include <devices/trackdisk.h>

#include <proto/exec.h>

#include "NoClick.h"

#if defined(__amigaos4__)
void ResidentInit(void *zero, BPTR segList, struct ExecBase *sysBase) {
	struct ExecIFace *IExec = (void *) sysBase->MainInterface;
	IExec->Obtain();
	NoClick(IExec);
	IExec->Release();
}
#elif defined(__MORPHOS__)
void ResidentInit(void *zero, BPTR segList, struct ExecBase *SysBase) {
	NoClick(SysBase);
}
#else
void ResidentInit(__reg("d0") void *zero, __reg("a0") BPTR segList, __reg("a6") struct ExecBase *SysBase) {
	NoClick(SysBase);
}
#endif
