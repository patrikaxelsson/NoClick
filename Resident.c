#include <exec/resident.h>

#include "ResidentEnd.h"
#include "ResidentInit.h"

const struct Resident ROMTag = {
	.rt_MatchWord = RTC_MATCHWORD,
	.rt_MatchTag  = (void *) &ROMTag,
	.rt_EndSkip   = (void *) &EndVariable,
	#if defined(__amigaos4__)
	.rt_Flags     = RTF_COLDSTART | RTF_NATIVE,
	#elif defined(__MORPHOS__)
	.rt_Flags     = RTF_COLDSTART | RTF_PPC,
	#else
	.rt_Flags     = RTF_COLDSTART,
	#endif
	.rt_Version   = 2,
	.rt_Type      = NT_UNKNOWN, // We just want to run rt_Init
	.rt_Pri       = 0, // Need to be initialized later than trackdisk at 20
	.rt_Name      = "NoClick",
	.rt_IdString  = "NoClick 2.0 (31.10.2022) by Patrik Axelsson",
	.rt_Init      = (void *) &ResidentInit
};
