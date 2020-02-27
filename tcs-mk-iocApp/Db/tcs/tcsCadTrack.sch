[schematic2]
uniq 33
[tools]
[detail]
w 962 760 100 0 n#32 ecad20.ecad20#24.STLK 560 48 960 48 960 1424 1152 1424 estringouts.TrackFrame.SLNK
w 968 1202 100 0 n#31 ecad20.ecad20#24.VALB 560 1424 832 1424 832 1200 1152 1200 estringouts.TrackEq.DOL
w 688 1490 100 0 n#30 ecad20.ecad20#24.VALA 560 1488 864 1488 864 1456 1152 1456 estringouts.TrackFrame.DOL
w 1240 1298 100 0 n#29 estringouts.TrackFrame.FLNK 1408 1440 1472 1440 1472 1296 1056 1296 1056 1168 1152 1168 estringouts.TrackEq.SLNK
w 918 1682 100 0 n#6 ecad20.ecad20#24.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad20.ecad20#24.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad20.ecad20#24.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad20.ecad20#24.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
s 1920 2000 100 0 $Id: tcsCadTrack.sch,v 1.1.1.1 1998/11/08 00:20:31 epics Exp $
s 1744 1296 100 0 N.B. The output links are set to PP so that the SAD
s 1744 1264 100 0 records will process. If this is not done, the SAD records
s 1744 1232 100 0 are left with SEVR set to INVALID.
[cell use]
use estringouts 1176 1096 100 0 TrackEq
xform 0 1280 1168
p 1184 1246 100 0 -1 DESC:Equinox of tracking frame
p 1088 974 100 0 0 OMSL:closed_loop
p 1088 1134 100 0 0 VAL:Undefined
p 1488 1150 100 0 -1 def(OUT):$(sad)$(vt)TrackEq
p 1296 1056 100 1024 1 name:$(top)$(vt)$(I)
p 1408 1152 75 768 -1 pproc(OUT):PP
use estringouts 1176 1352 100 0 TrackFrame
xform 0 1280 1424
p 1184 1502 100 0 -1 DESC:Target tracking frame
p 1088 1230 100 0 0 OMSL:closed_loop
p 1088 1390 100 0 0 VAL:Undefined
p 1488 1406 100 0 -1 def(OUT):$(sad)$(vt)TrackFrame
p 1296 1312 100 1024 1 name:$(top)$(vt)$(I)
p 1408 1408 75 768 -1 pproc(OUT):PP
use ecad20 264 -40 100 0 ecad20#24
xform 0 400 848
p 400 1848 100 0 0 FTVB:STRING
p 400 1816 100 0 0 FTVC:STRING
p 400 1784 100 0 0 FTVD:STRING
p 400 1688 100 0 0 FTVG:STRING
p 400 1656 100 0 0 FTVH:DOUBLE
p 400 1624 100 0 0 FTVI:DOUBLE
p 400 1592 100 0 0 FTVJ:DOUBLE
p 400 1560 100 0 0 FTVK:DOUBLE
p 400 1528 100 0 0 FTVL:DOUBLE
p 400 1496 100 0 0 FTVM:DOUBLE
p 400 1464 100 0 0 FTVN:DOUBLE
p 400 1432 100 0 0 FTVO:LONG
p 304 -82 100 0 1 SNAM:tcsCADtrack
p 704 1454 100 0 0 def(OUTA):0.0
p 704 1422 100 0 0 def(OUTB):0.0
p 304 -130 100 0 1 name:$(tcs)$(cad)
p 560 1456 75 768 -1 pproc(OUTA):PP
p 560 1392 75 768 -1 pproc(OUTB):PP
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
