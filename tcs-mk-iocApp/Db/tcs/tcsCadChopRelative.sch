[schematic2]
uniq 43
[tools]
[detail]
w 1296 1682 100 0 n#34 ecad8.ecad8#23.VAL 560 1680 2080 1680 outhier.VAL.p
w 1318 1586 100 0 n#9 ecad8.ecad8#23.MESS 560 1648 592 1648 592 1584 2080 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad8.ecad8#23.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad8.ecad8#23.DIR
s 960 1152 100 0 to trigger them from the STLK link
s 960 1184 100 0 whenever the CAD record processes. It might be better
s 960 1216 100 0 N.B. the output links to the SAD will fire
s 2032 -192 100 0 Gemini Telescope Control System
s 1792 2000 100 0 $Id: tcsCadChopRelative.sch,v 1.2 2000/11/21 14:09:21 cjm Exp $
s 1808 -336 100 0 20 October 1996
[cell use]
use ecad8 264 728 100 0 ecad8#23
xform 0 400 1232
p 224 1790 100 0 -1 DESC:Implements the chopRelative command
p 416 1456 100 0 -1 FTVA:DOUBLE
p 416 1406 100 0 -1 FTVB:DOUBLE
p 416 1358 100 0 -1 FTVC:STRING
p 416 1294 100 0 -1 FTVD:STRING
p 400 1214 100 0 0 FTVE:DOUBLE
p 432 1166 100 0 0 FTVF:STRING
p 432 1038 100 0 0 FTVH:STRING
p 336 1976 100 0 0 PREC:5
p 320 910 100 0 1 SNAM:$(snam)
p 640 1456 100 0 -1 def(OUTA):$(sad)chopThrow
p 640 1392 100 0 -1 def(OUTB):$(sad)chopPA
p 640 1328 100 0 -1 def(OUTC):$(sad)chopFrame
p 640 1262 100 0 -1 def(OUTD):$(sad)chopEquinox
p 640 1198 100 0 0 def(OUTE):0.0
p 640 1070 100 0 0 def(OUTG):0.0
p 304 670 100 0 1 name:$(tcs)$(cad)
p 560 1456 75 768 -1 pproc(OUTA):PP
p 560 1392 75 768 -1 pproc(OUTB):PP
p 560 1328 75 768 -1 pproc(OUTC):PP
p 560 1264 75 768 -1 pproc(OUTD):PP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 2072 1640 100 0 VAL
xform 0 2064 1680
use outhier 2072 1544 100 0 MESS
xform 0 2064 1584
use inhier -152 1640 100 0 DIR
xform 0 -160 1680
use inhier -152 1544 100 0 ICID
xform 0 -160 1584
[comments]
