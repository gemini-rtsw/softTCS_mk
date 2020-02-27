[schematic2]
uniq 28
[tools]
[detail]
w 1240 1131 100 0 n#27 ecad8.stopAll.VALA 1088 1280 1184 1280 1184 1120 1344 1120 estringouts.stopAllRotBrakes.DOL
w 1224 971 100 0 n#27 junction 1184 1120 1184 960 1312 960 estringouts.stopAllMntElBrakes.DOL
w 1208 811 100 0 n#27 junction 1184 960 1184 800 1280 800 estringouts.stopAllMntAzBrakes.DOL
w 1416 1163 100 0 n#26 estringouts.stopAllRotBrakes.FLNK 1600 1104 1600 1152 1280 1152 1280 1248 1376 1248 estringouts.stopAllEnc.SLNK
w 1384 1003 100 0 n#25 estringouts.stopAllMntElBrakes.FLNK 1568 944 1568 992 1248 992 1248 1088 1344 1088 estringouts.stopAllRotBrakes.SLNK
w 1352 843 100 0 n#24 estringouts.stopAllMntAzBrakes.FLNK 1536 784 1536 832 1216 832 1216 928 1312 928 estringouts.stopAllMntElBrakes.SLNK
w 1320 683 100 0 n#23 estringouts.stopAllMntAxSel.FLNK 1504 624 1504 672 1184 672 1184 768 1280 768 estringouts.stopAllMntAzBrakes.SLNK
w 1144 619 100 0 n#18 ecad8.stopAll.STLK 1088 608 1248 608 estringouts.stopAllMntAxSel.SLNK
w 1216 1443 100 0 n#1 ecad8.stopAll.MESS 1088 1440 1344 1440 1344 1392 1536 1392 outhier.MESS.p
w 1312 1475 100 0 n#2 ecad8.stopAll.VAL 1088 1472 1536 1472 outhier.VAL.p
w 566 1403 100 0 n#3 inhier.ICID.P 496 1392 672 1392 672 1440 768 1440 ecad8.stopAll.ICID
w 614 1483 100 0 n#4 inhier.DIR.P 496 1472 768 1472 ecad8.stopAll.DIR
s 1056 2112 100 0 $Id: tcsCadstopAll.sch,v 1.3 2015/08/07 20:00:44 gemvx Exp $
s 1328 0 100 0 TCS StopAll Command
s 1264 64 100 0 Gemini Telescope Control System
[cell use]
use estringouts 1447 1165 100 0 stopAllEnc
xform 0 1504 1248
p 1312 1214 100 0 0 VAL:MARK
p 1702 1222 100 0 -1 def(OUT):$(tcs)enclosureStop.DIR
p 1664 1232 75 768 -1 palrm(OUT):NMS
p 1632 1232 75 768 -1 pproc(OUT):PP
p 1344 1216 75 1280 -1 pproc(SDIS):NPP
use estringouts 1319 525 100 0 stopAllMntAxSel
xform 0 1376 608
p 1184 574 100 0 0 VAL:Both
p 1574 582 100 0 -1 def(OUT):$(tcs)telstop.A
p 1536 592 75 768 -1 palrm(OUT):NMS
p 1216 640 75 1280 -1 pproc(DOL):NPP
p 1504 592 75 768 -1 pproc(OUT):NPP
p 1216 576 75 1280 -1 pproc(SDIS):NPP
use estringouts 1280 695 100 0 stopAllMntAzBrakes
xform 0 1408 768
p 1216 574 100 0 0 OMSL:closed_loop
p 1600 752 100 0 -1 def(OUT):$(tcs)telstop.B
use estringouts 1312 855 100 0 stopAllMntElBrakes
xform 0 1440 928
p 1248 734 100 0 0 OMSL:closed_loop
p 1632 896 100 0 -1 def(OUT):$(tcs)telstop.C
use estringouts 1344 1015 100 0 stopAllRotBrakes
xform 0 1472 1088
p 1280 894 100 0 0 OMSL:closed_loop
p 1664 1056 100 0 -1 def(OUT):$(tcs)rotStop.B
use outhier 1528 1352 100 0 MESS
xform 0 1520 1392
use outhier 1528 1432 100 0 VAL
xform 0 1520 1472
use inhier 504 1352 100 0 ICID
xform 0 496 1392
use inhier 504 1432 100 0 DIR
xform 0 496 1472
use ecad8 792 520 -100 0 stopAll
xform 0 928 1024
p 864 1672 100 0 0 FTVA:STRING
p 864 1640 100 0 0 FTVB:DOUBLE
p 864 1608 100 0 0 FTVC:DOUBLE
p 864 1576 100 0 0 FTVD:DOUBLE
p 864 1544 100 0 0 FTVE:DOUBLE
p 864 1512 100 0 0 FTVF:DOUBLE
p 864 1480 100 0 0 FTVG:DOUBLE
p 864 1448 100 0 0 FTVH:DOUBLE
p 864 1960 100 0 0 SNAM:tcsCADstopAll
p 864 -3224 100 0 0 def(SPLK):0.0
p 864 776 100 0 0 def(STLK):0.0
p 864 494 100 0 -1 name:$(tcs)stopAll
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
