#include <exec/exec.h>
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <workbench/startup.h>

#include <proto/exec.h>
#include <proto/dos.h>

#include "NoClick.h"


#if defined(__MORPHOS__)
ULONG __abox__ = 1;
#endif

#if defined(__amigaos4__)
// Must be named _start in AmigaOS4 binaries.
__saveds int32 _start(STRPTR args, int32 argsLength, struct ExecBase *sysBase) {
	struct ExecIFace *IExec = (struct ExecIFace *) sysBase->MainInterface;
	IExec->Obtain();
#else
// In 68k AmigaOS and MorphOS binaries, the symbol name doesn't matter, it just have to be first.
__saveds LONG Startup(void) {
	struct ExecBase *SysBase = *(struct ExecBase **) 4;
#endif

	struct WBStartup *wbStartupMsg = NULL;
	struct Process *thisProcess = (struct Process *) FindTask(NULL);
	if (0 == thisProcess->pr_CLI) {
		// If started from Workbench, get the startup message
		WaitPort(&thisProcess->pr_MsgPort);
		wbStartupMsg = (void *) GetMsg(&thisProcess->pr_MsgPort);
	}
	
	#if defined(__amigaos4__)
	NoClick(IExec);
	#else
	NoClick(SysBase);
	#endif

	if(NULL != wbStartupMsg) {
		// This is so Workbench won't unload our segment before we exit
		Forbid();
		// If started from Workbench, reply to the startup message
		ReplyMsg((void *) wbStartupMsg);
	}

	#if defined(__amigaos4__)
	IExec->Release();
	#endif
	
	return RETURN_OK;
}
