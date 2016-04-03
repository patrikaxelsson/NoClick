all: NoClick NoClick.mos NoClick.os4

NoClick: NoClick.c Makefile
	vc +aos68k_minstart -c99 -Os -sd -lvcs -o $@ $<

NoClick.mos: NoClick.c Makefile
	vc +morphos_minstart -Os -sd -lvcs -o $@ $<

NoClick.os4: NoClick.c Makefile
	vc +aosppc_minstart -Os -sd -lvcs -D__USE_INLINE__ -o $@ $<

clean:
	$(RM) NoClick NoClick.mos NoClick.os4
