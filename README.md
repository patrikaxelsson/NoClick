# NoClick

A small and simple utility for enabling the NoClick functionality of
trackdisk.device V36+ in AmigaOS 2.0+.

This is definately not the first utility for enabling NoClick, but the
unique feature of this one is that there are also native binaries available
for both AmigaOS4 and MorphOS running on classic Amigas with PowerUP
accelerators.

NoClick needs no arguments and will enable NoClick by attempting to set the
`TDPF_NOCLICK` flag for all available trackdisk units.

If running this utility does not silence the clicking of a drive, do not use
it as it might cause mechanical damage to the drive.


## Installation

Start NoClick from Startup-Sequence, User-Startup, WBStartup, somewhere
else, or load it as a resident module to have it enabled even if you
boot without Startup-Sequence or something other than your normal system
drive.

There are a number of options for loading it as a resident module:
 - 68k AmigaOS: Use LoadModule, BlizKick, RemApollo or similar software
 - MorphOS: Copy NoClick.mos to SYS:Boot/ExtModules/NoClick
 - PPC AmigaOS: Copy NoClick.os4 to SYS:Kickstart/NoClick and add the
   line "MODULE Kickstart/NoClick" without quotes to the file
   SYS:Kickstart/KickLayout-&lt;YourAmigaModel&gt;
