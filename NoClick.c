#include <proto/exec.h>
#include <exec/exec.h>
#include <dos/dos.h>
#include <devices/trackdisk.h>

UBYTE *Version = "\0$VER: NoClick 1.0 (13.12.2015) by Patrik Axelsson\0";

int main(void) {
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
	return RETURN_OK;
}
