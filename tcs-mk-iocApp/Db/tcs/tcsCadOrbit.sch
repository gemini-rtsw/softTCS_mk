[schematic2]
uniq 26
[tools]
[detail]
w 1096 747 100 0 n#25 estringouts.orbitObjectName.FLNK 1280 896 1344 896 1344 736 896 736 896 624 1024 624 estringouts.orbitBrightness.SLNK
w 676 459 100 0 n#23 ecad20.ecad20#20.STLK 560 48 672 48 672 880 1024 880 estringouts.orbitObjectName.SLNK
w 768 915 100 0 n#22 ecad20.ecad20#20.VALJ 560 912 1024 912 estringouts.orbitObjectName.DOL
w 918 1682 100 0 n#6 ecad20.ecad20#20.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad20.ecad20#20.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad20.ecad20#20.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad20.ecad20#20.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
s 1840 2000 100 0 $Id4
[cell use]
use estringouts 1024 551 100 0 orbitBrightness
xform 0 1152 624
p 1051 664 100 0 0 DESC:Brightness description
p 960 430 100 0 0 OMSL:supervisory
p 960 590 100 0 0 VAL:Unspecified
p 1360 608 100 0 -1 def(OUT):$(sad)$(vt)Brightness
p 1136 544 100 1024 0 name:$(top)$(tel)$(I)
p 1280 608 75 768 -1 pproc(OUT):PP
use estringouts 1024 807 100 0 orbitObjectName
xform 0 1152 880
p 960 686 100 0 0 OMSL:closed_loop
p 960 846 100 0 0 VAL:
p 1360 864 100 0 -1 def(OUT):$(sad)$(vt)ObjectName
p 1136 800 100 1024 0 name:$(top)$(tel)$(I)
p 1280 864 75 768 -1 pproc(OUT):PP
use ecad20 240 -41 100 0 ecad20#20
xform 0 400 848
p 336 1744 100 0 -1 DESC:Orbit command
p 336 1424 100 0 0 FTVA:LONG
p 336 1392 100 0 0 FTVB:DOUBLE
p 336 1360 100 0 0 FTVC:DOUBLE
p 336 1328 100 0 0 FTVD:DOUBLE
p 336 1296 100 0 0 FTVE:DOUBLE
p 336 1264 100 0 0 FTVF:DOUBLE
p 336 1232 100 0 0 FTVG:DOUBLE
p 336 1200 100 0 0 FTVH:DOUBLE
p 336 1168 100 0 0 FTVI:DOUBLE
p 496 -64 100 0 1 SNAM:tcsCADorbit
p 640 880 100 0 0 def(OUTJ):0.0
p 352 -48 100 1024 0 name:$(tcs)$(tel)orbit
p 560 880 75 768 -1 pproc(OUTJ):NPP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 1304 1640 100 0 VAL
xform 0 1296 1680
use outhier 1448 1544 100 0 MESS
xform 0 1440 1584
use inhier -152 1640 100 0 DIR
xform 0 -160 1680
use inhier -152 1544 100 0 ICID
xform 0 -160 1584
[comments]
