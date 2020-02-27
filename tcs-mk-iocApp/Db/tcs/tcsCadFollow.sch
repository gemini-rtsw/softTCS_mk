[schematic2]
uniq 48
[tools]
[detail]
w 1272 1227 100 0 n#47 ecad8.follow.STLK 1088 608 1216 608 1216 1216 1376 1216 tcsStopFollow.tcsStopFollow#8.Slnk
w 1208 1291 100 0 n#46 ecad8.follow.VALA 1088 1280 1376 1280 tcsStopFollow.tcsStopFollow#8.Action
w 1192 1451 100 0 n#45 ecad8.follow.MESS 1088 1440 1344 1440 1344 1392 1536 1392 outhier.MESS.p
w 1288 1483 100 0 n#44 ecad8.follow.VAL 1088 1472 1536 1472 outhier.VAL.p
w 392 1394 100 0 n#24 inhier.ICID.P 160 1392 672 1392 672 1440 768 1440 ecad8.follow.ICID
w 440 1474 100 0 n#23 inhier.DIR.P 160 1472 768 1472 ecad8.follow.DIR
s 2512 -80 100 0 Gemini Telescope Control System
s 2592 -144 100 0 TCS FOLLOW Command
s 2288 2112 100 0 $Id: tcsCadFollow.sch,v 1.3 2000/01/26 06:05:26 cjm Exp $
[cell use]
use bc200tr -288 -360 -100 0 frame
xform 0 1392 944
use tcsStopFollow 1400 1128 100 0 tcsStopFollow#8
xform 0 1456 1232
use outhier 1528 1432 100 0 VAL
xform 0 1520 1472
use outhier 1528 1352 100 0 MESS
xform 0 1520 1392
use inhier 168 1432 100 0 DIR
xform 0 160 1472
use inhier 168 1352 100 0 ICID
xform 0 160 1392
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
