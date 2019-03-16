all: NoClick NoClick.mos NoClick.os4

NoClick: NoClick.c Makefile
	vc +aos68k -nostdlib -c99 -size -sc -D__NOLIBBASE__ -o $@ $<

NoClick.mos: NoClick.c Makefile
	vc +morphos -nostdlib -size -sd -D__NOLIBBASE__ -o $@ $<

NoClick.os4: NoClick.c Makefile
	vc +aosppc -nostdlib -size -sd -D__USE_INLINE__ -D__NOLIBBASE__ -D__NOGLOBALIFACE__ -o $@ $<

clean:
	$(RM) NoClick NoClick.mos NoClick.os4
