[schematic2]
uniq 33
[tools]
[detail]
w 2248 587 100 0 n#32 junction 2208 800 2208 576 2336 576 elongouts.stopGuideWFSTrg.DOL
w 2248 811 100 0 n#32 junction 2208 1008 2208 800 2336 800 elongouts.stopGuideRotTrg.DOL
w 2248 1019 100 0 n#32 junction 2208 1232 2208 1008 2336 1008 elongouts.stopGuideMountTrg.DOL
w 2248 1243 100 0 n#32 junction 2208 1456 2208 1232 2336 1232 elongouts.stopGuideM1Trg.DOL
w 2248 1467 100 0 n#32 hwin.hwin#31.in 2208 1536 2208 1456 2336 1456 elongouts.stopGuideM2Trg.DOL
w 2440 667 100 0 n#30 elongouts.stopGuideRotTrg.FLNK 2592 800 2656 800 2656 656 2272 656 2272 544 2336 544 elongouts.stopGuideWFSTrg.SLNK
w 2440 1099 100 0 n#29 elongouts.stopGuideM1Trg.FLNK 2592 1232 2656 1232 2656 1088 2272 1088 2272 976 2336 976 elongouts.stopGuideMountTrg.SLNK
w 2440 875 100 0 n#28 elongouts.stopGuideMountTrg.FLNK 2592 1008 2656 1008 2656 864 2272 864 2272 768 2336 768 elongouts.stopGuideRotTrg.SLNK
w 2440 1323 100 0 n#27 elongouts.stopGuideM2Trg.FLNK 2592 1456 2656 1456 2656 1312 2272 1312 2272 1200 2336 1200 elongouts.stopGuideM1Trg.SLNK
w 1888 587 100 0 n#26 estringouts.stopGuideWFS.FLNK 1744 576 2080 576 2080 1424 2336 1424 elongouts.stopGuideM2Trg.SLNK
w 928 1443 100 0 n#1 ecad8.stopGuideAll.MESS 800 1440 1056 1440 1056 1392 1248 1392 outhier.MESS.p
w 1024 1475 100 0 n#2 ecad8.stopGuideAll.VAL 800 1472 1248 1472 outhier.VAL.p
w 128 1395 100 0 n#3 inhier.ICID.P -128 1392 384 1392 384 1440 480 1440 ecad8.stopGuideAll.ICID
w 176 1475 100 0 n#4 inhier.DIR.P -128 1472 480 1472 ecad8.stopGuideAll.DIR
w 1638 1323 100 0 n#5 estringouts.stopGuideM2.FLNK 1720 1440 1936 1440 1936 1312 1376 1312 1376 1200 1472 1200 estringouts.stopGuideM1.SLNK
w 1638 1083 100 0 n#6 estringouts.stopGuideM1.FLNK 1728 1216 1936 1216 1936 1072 1376 1072 1376 984 1480 984 estringouts.stopGuideMount.SLNK
w 1638 875 100 0 n#7 estringouts.stopGuideMount.FLNK 1736 1000 1936 1000 1936 864 1376 864 1376 768 1488 768 estringouts.stopGuideRot.SLNK
w 1642 659 100 0 n#8 estringouts.stopGuideRot.FLNK 1744 784 1944 784 1944 648 1376 648 1376 560 1488 560 estringouts.stopGuideWFS.SLNK
w 1048 619 -100 0 n#20 ecad8.stopGuideAll.STLK 800 608 1344 608 1344 1424 1464 1424 estringouts.stopGuideM2.SLNK
s 2512 -80 100 0 Gemini Telescope Control System
s 2592 -144 100 0 TCS STOP GUIDE ALL Command
s 2288 2112 100 0 $Id: tcsCadStopGuideAll.sch,v 1.1 2015/08/12 16:14:08 gemvx Exp $
[cell use]
use hwin 2016 1495 100 0 hwin#31
xform 0 2112 1536
p 2019 1528 100 0 -1 val(in):$(CAD_START)
use elongouts 2336 455 100 0 stopGuideWFSTrg
xform 0 2464 544
p 2176 462 100 0 0 OMSL:closed_loop
p 2672 512 100 0 -1 def(OUT):$(tcs)wfsGuideMode.DIR
p 2592 512 75 768 -1 pproc(OUT):PP
use elongouts 2336 679 100 0 stopGuideRotTrg
xform 0 2464 768
p 2176 686 100 0 0 OMSL:closed_loop
p 2672 736 100 0 -1 def(OUT):$(tcs)rotGuideMode.DIR
p 2592 736 75 768 -1 pproc(OUT):PP
use elongouts 2336 887 100 0 stopGuideMountTrg
xform 0 2464 976
p 2176 894 100 0 0 OMSL:closed_loop
p 2672 928 100 0 0 def(DOL):0.000000000000000e+00
p 2672 928 100 0 -1 def(OUT):$(tcs)mountGuideMode.DIR
p 2592 944 75 768 -1 pproc(OUT):PP
use elongouts 2336 1111 100 0 stopGuideM1Trg
xform 0 2464 1200
p 2176 1118 100 0 0 OMSL:closed_loop
p 2672 1168 100 0 -1 def(OUT):$(tcs)m1GuideMode.DIR
p 2592 1168 75 768 -1 pproc(OUT):PP
use elongouts 2336 1335 100 0 stopGuideM2Trg
xform 0 2464 1424
p 2176 1342 100 0 0 OMSL:closed_loop
p 2672 1376 100 0 -1 def(OUT):$(tcs)m2GuideControl.DIR
p 2592 1392 75 768 -1 pproc(OUT):PP
use bc200tr -288 -360 -100 0 frame
xform 0 1392 944
use outhier 1240 1432 100 0 VAL
xform 0 1232 1472
use outhier 1240 1352 100 0 MESS
xform 0 1232 1392
use inhier -120 1432 100 0 DIR
xform 0 -128 1472
use inhier -120 1352 100 0 ICID
xform 0 -128 1392
use ecad8 504 520 -100 0 stopGuideAll
xform 0 640 1024
p 576 1672 100 0 0 FTVA:DOUBLE
p 576 1640 100 0 0 FTVB:DOUBLE
p 576 1608 100 0 0 FTVC:DOUBLE
p 576 1576 100 0 0 FTVD:DOUBLE
p 576 1544 100 0 0 FTVE:DOUBLE
p 576 1512 100 0 0 FTVF:DOUBLE
p 576 1480 100 0 0 FTVG:DOUBLE
p 576 1448 100 0 0 FTVH:DOUBLE
p 576 1960 100 0 0 SNAM:tcsCADstopGuideAll
p 576 -3224 100 0 0 def(SPLK):0.0
p 576 776 100 0 0 def(STLK):0.0
p 576 494 100 0 -1 name:$(tcs)stopGuideAll
p 800 1248 75 768 -1 pproc(OUTA):NPP
p 800 1184 75 768 -1 pproc(OUTB):NPP
p 800 1120 75 768 -1 pproc(OUTC):NPP
p 800 1056 75 768 -1 pproc(OUTD):NPP
p 800 992 75 768 -1 pproc(OUTE):NPP
p 800 928 75 768 -1 pproc(OUTF):NPP
p 800 864 75 768 -1 pproc(OUTG):NPP
p 800 800 75 768 -1 pproc(OUTH):NPP
p 576 -2904 100 0 0 typ(OUTH):path
use estringouts 1535 1341 100 0 stopGuideM2
xform 0 1592 1424
p 1400 1390 100 0 0 VAL:off
p 1792 1408 100 0 -1 def(OUT):$(tcs)m2GuideControl.A
p 1728 1416 75 768 -1 pproc(OUT):NPP
p 1392 1400 75 1280 -1 pproc(SDIS):NPP
use estringouts 1543 1117 100 0 stopGuideM1
xform 0 1600 1200
p 1408 1166 100 0 0 VAL:off
p 1798 1174 100 0 -1 def(OUT):$(tcs)m1GuideMode.A
p 1736 1192 75 768 -1 pproc(OUT):NPP
p 1400 1176 75 1280 -1 pproc(SDIS):NPP
use estringouts 1551 901 100 0 stopGuideMount
xform 0 1608 984
p 1416 950 100 0 0 VAL:off
p 1808 960 100 0 -1 def(OUT):$(tcs)mountGuideMode.A
use estringouts 1559 685 100 0 stopGuideRot
xform 0 1616 768
p 1424 734 100 0 0 VAL:off
p 1814 742 100 0 -1 def(OUT):$(tcs)rotGuideMode.A
p 1752 760 75 768 -1 pproc(OUT):NPP
p 1416 744 75 1280 -1 pproc(SDIS):NPP
use estringouts 1559 477 100 0 stopGuideWFS
xform 0 1616 560
p 1424 526 100 0 0 VAL:off
p 1814 534 100 0 -1 def(OUT):$(tcs)wfsGuideMode.A
p 1752 552 75 768 -1 pproc(OUT):NPP
p 1416 536 75 1280 -1 pproc(SDIS):NPP
[comments]
