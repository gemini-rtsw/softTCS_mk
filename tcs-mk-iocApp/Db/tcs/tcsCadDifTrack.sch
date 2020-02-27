[schematic2]
uniq 42
[tools]
[detail]
w 918 1682 100 0 n#6 ecad20.ecad20#24.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad20.ecad20#24.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad20.ecad20#24.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad20.ecad20#24.DIR
s 992 992 100 0 this specific CAD is executed.
s 992 1024 100 0 They are now set on every new configuration rahter than when
s 992 1056 100 0 have been moved to the tcsVtDiffTrack schematic
s 992 1088 100 0 The records that were here to set the SAD items
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
s 1920 2000 100 0 $Id: tcsCadDifTrack.sch,v 1.3 2004/08/05 09:56:59 cjm Exp $
[cell use]
use ecad20 264 -40 100 0 ecad20#24
xform 0 400 848
p 400 1848 100 0 0 FTVB:STRING
p 400 1816 100 0 0 FTVC:DOUBLE
p 400 1784 100 0 0 FTVD:DOUBLE
p 336 1296 100 0 0 FTVE:DOUBLE
p 400 1688 100 0 0 FTVG:DOUBLE
p 400 1656 100 0 0 FTVH:DOUBLE
p 400 1624 100 0 0 FTVI:DOUBLE
p 400 1592 100 0 0 FTVJ:DOUBLE
p 400 1560 100 0 0 FTVK:DOUBLE
p 400 1528 100 0 0 FTVL:DOUBLE
p 400 1496 100 0 0 FTVM:DOUBLE
p 400 1464 100 0 0 FTVN:DOUBLE
p 400 1432 100 0 0 FTVO:LONG
p 304 -82 100 0 1 SNAM:tcsCADdiffTr
p 752 1422 100 0 0 def(OUTA):0.0
p 752 1390 100 0 0 def(OUTB):0.0
p 752 1358 100 0 0 def(OUTC):0.0
p 752 1326 100 0 0 def(OUTD):0.0
p 752 1294 100 0 0 def(OUTE):0.0
p 304 -130 100 0 1 name:$(tcs)$(cad)
p 560 1456 75 768 -1 pproc(OUTA):PP
p 560 1392 75 768 -1 pproc(OUTB):PP
p 560 1328 75 768 -1 pproc(OUTC):PP
p 560 1264 75 768 -1 pproc(OUTD):PP
p 560 1200 75 768 -1 pproc(OUTE):PP
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
