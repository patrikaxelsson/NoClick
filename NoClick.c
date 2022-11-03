#include <exec/exec.h>
#include <dos/dosextens.h>
#include <workbench/startup.h>
#include <devices/trackdisk.h>

#include <proto/exec.h>

#if defined(__amigaos4__)
void NoClick(struct ExecIFace *IExec) {
#elif defined(__MORPHOS__)
void NoClick(struct ExecBase *SysBase) {
#else
// Putting SysBase in a6 is not necessary here, it is just to make vbcc
// produce simpler/better code.
void NoClick(__reg("a6") struct ExecBase *SysBase) {
#endif
	struct MsgPort *trackDiskPort = CreateMsgPort();
	for (int unitNum = 0; unitNum < NUMUNITS; unitNum++) {
		struct IOExtTD *trackDiskReq = (void *) CreateIORequest(trackDiskPort, sizeof(struct IOExtTD));
		if (NULL != trackDiskReq) {
			if (0 == OpenDevice(TD_NAME, unitNum, (void *) trackDiskReq, 0)) {
				struct TDU_PublicUnit *publicUnit = (void *) trackDiskReq->iotd_Req.io_Unit;
				Forbid();
				publicUnit->tdu_PubFlags |= TDPF_NOCLICK;
				Permit();
				CloseDevice((void *) trackDiskReq);
			}
			DeleteIORequest((void *) trackDiskReq);
		}
	}
	DeleteMsgPort(trackDiskPort);
}
