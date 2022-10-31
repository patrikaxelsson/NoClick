all: NoClick NoClick.mos NoClick.os4

# The order of the files given to the compiler is important as this order
# will be kept in the resulting executable.
# The file containing the startup function must be first as AmigaOS simply
# starts executing from the start of the first hunk. Then to make it as
# efficient as possible to load this as a resident, the Resident structure
# is placed next, followed by the actual code for the patch and then ending
# it with an empty function used to point/skip to the end in Resident
# structure.
NoClick: Startup.c Resident.c ResidentInit.c NoClick.c ResidentEnd.c ResidentInit.h NoClick.h ResidentEnd.h Makefile
	vc +aos68k -nostdlib -O1 -sc -D__NOLIBBASE__ -o $@ Startup.c Resident.c ResidentInit.c NoClick.c ResidentEnd.c

NoClick.mos: Startup.c Resident.c ResidentInit.c NoClick.c ResidentEnd.c ResidentInit.h NoClick.h ResidentEnd.h Makefile
	vc +morphos -nostdlib -O1 -sd -use-lmw -D__NOLIBBASE__ -o $@ Startup.c Resident.c ResidentInit.c NoClick.c ResidentEnd.c

NoClick.os4: Startup.c Resident.c ResidentInit.c NoClick.c ResidentEnd.c ResidentInit.h NoClick.h ResidentEnd.h Makefile
	vc +aosppc -nostdlib -O1 -sd -use-lmw -D__USE_INLINE__ -D__NOLIBBASE__ -D__NOGLOBALIFACE__ -o $@ Startup.c Resident.c ResidentInit.c NoClick.c ResidentEnd.c

clean:
	$(RM) NoClick NoClick.mos NoClick.os4
