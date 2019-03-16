#include <exec/exec.h>
#include <dos/dosextens.h>
#include <workbench/startup.h>
#include <devices/trackdisk.h>

#include <proto/exec.h>

UBYTE *Version = "\0$VER: NoClick 1.1 (12.4.2016) by Patrik Axelsson\0";

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
__saveds LONG NoClick(void) {
	struct ExecBase *SysBase = *(struct ExecBase **) 4;
#endif

	struct WBStartup *wbStartupMsg = NULL;
	struct Process *thisProcess = (struct Process *) FindTask(NULL);
	if(MKBADDR(NULL) == thisProcess->pr_CLI) {
		// If started from Workbench, get the startup message
		WaitPort(&thisProcess->pr_MsgPort);
		wbStartupMsg = (struct WBStartup *) GetMsg(&thisProcess->pr_MsgPort);
	}
	
	struct MsgPort *trackDiskPort = CreateMsgPort();
	for(ULONG i = 0; i < NUMUNITS; i++) {
		struct IOExtTD *trackDiskReq = (struct IOExtTD *) CreateIORequest(trackDiskPort, sizeof(struct IOExtTD));
		if(NULL != trackDiskReq) {
			if(0 == OpenDevice(TD_NAME, i, (struct IORequest *) trackDiskReq, 0)) {
				struct TDU_PublicUnit *publicUnit = (struct TDU_PublicUnit *) trackDiskReq->iotd_Req.io_Unit;
				Forbid();
				publicUnit->tdu_PubFlags |= TDPF_NOCLICK;
				Permit();
				CloseDevice((struct IORequest *) trackDiskReq);
			}
			DeleteIORequest((struct IORequest *) trackDiskReq);
		}
	}
	DeleteMsgPort(trackDiskPort);

	if(NULL != wbStartupMsg) {
		Forbid();
		// If started from Workbench, reply to the startup message
		ReplyMsg((struct Message *) wbStartupMsg);
	}

#if defined(__amigaos4__)
	IExec->Release();
#endif
	
	return RETURN_OK;
}
