#include <exec/exec.h>
#include <dos/dos.h>
#include <devices/trackdisk.h>

#include <proto/exec.h>

UBYTE *Version = "\0$VER: NoClick 1.1 (3.4.2016) by Patrik Axelsson\0";

#if defined(__MORPHOS__)
ULONG __abox__ = 1;
#endif

#if defined(__amigaos4__)
int32 _start(STRPTR args, int32 argsLength, struct ExecBase *sysBase) {
	struct ExecIFace *IExec = (struct ExecIFace *) sysBase->MainInterface;
	IExec->Obtain();
#else
LONG NoClick(void) {
	struct ExecBase *SysBase = *(struct ExecBase **) 4;
#endif
	
	struct MsgPort *trackDiskPort = CreateMsgPort();
	if(NULL != trackDiskPort) {
		struct IOExtTD *trackDiskReq = (struct IOExtTD *) CreateIORequest(trackDiskPort, sizeof(struct IOExtTD));
		if(NULL != trackDiskReq) {
			for(ULONG i = 0; i < NUMUNITS; i++) {
				if(0 == OpenDevice(TD_NAME, i, (struct IORequest *) trackDiskReq, 0)) {
					struct TDU_PublicUnit *publicUnit = (struct TDU_PublicUnit *) trackDiskReq->iotd_Req.io_Unit;
					Forbid();
					publicUnit->tdu_PubFlags |= TDPF_NOCLICK;
					Permit();
					CloseDevice((struct IORequest *) trackDiskReq);
				}
			}
			DeleteIORequest((struct IORequest *) trackDiskReq);
		}
		DeleteMsgPort(trackDiskPort);
	}
	
#if defined(__amigaos4__)
	IExec->Release();
#endif
	
	return RETURN_OK;
}
