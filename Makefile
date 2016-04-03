all: NoClick NoClick.mos NoClick.os4

NoClick: NoClick.c Makefile
	vc +aos68k -nostdlib -c99 -size -o $@ $<

NoClick.mos: NoClick.c Makefile
	vc +morphos -nostdlib -size -o $@ $<

NoClick.os4: NoClick.c Makefile
	vc +aosppc -nostdlib -size -D__USE_INLINE__ -o $@ $<

clean:
	$(RM) NoClick NoClick.mos NoClick.os4
