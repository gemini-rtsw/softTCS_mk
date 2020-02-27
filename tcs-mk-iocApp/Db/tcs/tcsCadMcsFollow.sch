[schematic2]
uniq 50
[tools]
[detail]
w 1528 1579 100 0 n#49 ecad8.follow.VAL 1088 1472 1344 1472 1344 1568 1760 1568 outhier.VAL.p
w 1544 1499 100 0 n#48 ecad8.follow.MESS 1088 1440 1376 1440 1376 1488 1760 1488 outhier.MESS.p
w 1240 619 100 0 n#47 ecad8.follow.STLK 1088 608 1440 608 1440 1152 1536 1152 tcsStopMcFollow.tcsStopMcFollow#38.Slnk
w 1752 1419 100 0 n#45 junction 1440 1280 1440 1408 2112 1408 2112 1280 2256 1280 tcsStopFollow.tcsStopFollow#1.Action
w 1288 1291 100 0 n#45 ecad8.follow.VALA 1088 1280 1536 1280 tcsStopMcFollow.tcsStopMcFollow#38.Action
w 1944 1291 100 0 n#46 tcsStopMcFollow.tcsStopMcFollow#38.Flnk 1872 1280 2064 1280 2064 1216 2256 1216 tcsStopFollow.tcsStopFollow#1.Slnk
w 392 1394 100 0 n#24 inhier.ICID.P 160 1392 672 1392 672 1440 768 1440 ecad8.follow.ICID
w 440 1474 100 0 n#23 inhier.DIR.P 160 1472 768 1472 ecad8.follow.DIR
s 2512 -80 100 0 Gemini Telescope Control System
s 2592 -144 100 0 TCS FOLLOW Command
s 2288 2112 100 0 $Id: tcsCadMcsFollow.sch,v 1.1 2000/01/26 06:06:13 cjm Exp $
s 192 1920 100 0 Unlike other subsystems, the MCS must be
s 192 1888 100 0 sent a number of parameters with its stop command.
s 192 1856 100 0 The defaults are initialised by pvload.
s 192 1824 100 0 The defaults can be modified from the mount specific control screen. 
s 192 1792 100 0 N.B. These defaults are not affected by whatever the user
s 192 1760 100 0 may have entered via the telstop command.
[cell use]
use tcsStopFollow 2280 1128 100 0 tcsStopFollow#1
xform 0 2336 1232
p 2240 1134 100 0 1 seta:prefix mc
p 2240 1102 100 0 1 setb:subsys $(mc)
p 2240 1070 100 0 1 setc:text Mount
use tcsStopMcFollow 1536 1063 100 0 tcsStopMcFollow#38
xform 0 1704 1200
p 1616 1328 100 0 1 seta:top $(tcs)$(cad):
use outhier 1752 1528 100 0 VAL
xform 0 1744 1568
use outhier 1752 1448 100 0 MESS
xform 0 1744 1488
use inhier 168 1432 100 0 DIR
xform 0 160 1472
use inhier 168 1352 100 0 ICID
xform 0 160 1392
use bc200tr -288 -360 -100 0 frame
xform 0 1392 944
use ecad8 792 520 -100 0 follow
xform 0 928 1024
p 864 1672 100 0 0 FTVA:DOUBLE
p 864 1640 100 0 0 FTVB:DOUBLE
p 864 1608 100 0 0 FTVC:DOUBLE
p 864 1576 100 0 0 FTVD:DOUBLE
p 864 1544 100 0 0 FTVE:DOUBLE
p 864 1512 100 0 0 FTVF:DOUBLE
p 864 1480 100 0 0 FTVG:DOUBLE
p 864 1448 100 0 0 FTVH:DOUBLE
p 864 1960 100 0 0 SNAM:$(snam)
p 864 -3224 100 0 0 def(SPLK):0.0
p 864 776 100 0 0 def(STLK):0.0
p 864 494 100 0 -1 name:$(tcs)$(cad)
p 1088 1248 75 768 -1 pproc(OUTA):NPP
p 1088 1184 75 768 -1 pproc(OUTB):NPP
p 1088 1120 75 768 -1 pproc(OUTC):NPP
p 1088 1056 75 768 -1 pproc(OUTD):NPP
p 1088 992 75 768 -1 pproc(OUTE):NPP
p 1088 928 75 768 -1 pproc(OUTF):NPP
p 1088 864 75 768 -1 pproc(OUTG):NPP
p 1088 800 75 768 -1 pproc(OUTH):NPP
p 864 -2904 100 0 0 typ(OUTH):path
[comments]
