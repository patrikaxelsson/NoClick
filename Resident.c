#include <exec/resident.h>

#include "ResidentEnd.h"
#include "ResidentInit.h"

const struct Resident ROMTag = {
	.rt_MatchWord = RTC_MATCHWORD,
	.rt_MatchTag  = (void *) &ROMTag,
	.rt_EndSkip   = (void *) &EndVariable,
	// RTF_AFTERDOS is used to make sure we run NoClick() after all units
	// have been mounted. If we run at RTF_COLDSTART, then depending on system
	// configuration, it is possible that there is a long enough time between
	// our unit close and the next open by the fs mounting, so trackdisk will
	// notice that it has no users and clean up the unit data including the
	// TDPF_NOCLICK flag bit NoClick() just set.
	// So RTF_AFTERDOS guarantees that NoClick() works, at the cost of an
	// extra click or two at boot.
	#if defined(__amigaos4__)
	.rt_Flags     = RTF_AFTERDOS | RTF_NATIVE,
	#elif defined(__MORPHOS__)
	.rt_Flags     = RTF_AFTERDOS | RTF_PPC,
	#else
	.rt_Flags     = RTF_AFTERDOS,
	#endif
	.rt_Version   = 2,
	.rt_Type      = NT_UNKNOWN, // We just want to run rt_Init
	.rt_Pri       = 0,
	.rt_Name      = "NoClick",
	.rt_IdString  = "NoClick 2.0 (3.11.2022) by Patrik Axelsson",
	.rt_Init      = (void *) &ResidentInit
};
