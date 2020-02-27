[schematic2]
uniq 15
[tools]
[detail]
w 1408 939 100 0 n#14 junction 1376 720 1376 928 1488 928 elongouts.abortAllUnfollowTrg.DOL
w 1408 731 100 0 n#14 hwin.hwin#13.in 1376 480 1376 720 1488 720 elongouts.abortAllGuideTrg.DOL
w 1576 779 100 0 n#12 elongouts.abortAllUnfollowTrg.SLNK 1488 896 1408 896 1408 768 1792 768 1792 720 1744 720 elongouts.abortAllGuideTrg.FLNK
w 1374 1163 100 0 n#7 ecad8.abortAll.VALA 1088 1280 1280 1280 1280 1152 1504 1152 estringouts.abortAllStopTrg.DOL
w 1216 1443 100 0 n#1 ecad8.abortAll.MESS 1088 1440 1344 1440 1344 1392 1536 1392 outhier.MESS.p
w 1312 1475 100 0 n#2 ecad8.abortAll.VAL 1088 1472 1536 1472 outhier.VAL.p
w 416 1395 100 0 n#3 inhier.ICID.P 160 1392 672 1392 672 1440 768 1440 ecad8.abortAll.ICID
w 464 1475 100 0 n#4 inhier.DIR.P 160 1472 768 1472 ecad8.abortAll.DIR
w 1534 1003 100 0 n#5 elongouts.abortAllUnfollowTrg.FLNK 1744 928 1792 928 1792 992 1312 992 1312 1120 1504 1120 estringouts.abortAllStopTrg.SLNK
w 1334 699 -100 0 n#6 ecad8.abortAll.STLK 1088 608 1216 608 1216 688 1488 688 elongouts.abortAllGuideTrg.SLNK
s 2288 2112 100 0 $Id: tcsCadabortAll.sch,v 1.4 2015/08/12 16:14:08 gemvx Exp $
s 2592 -144 100 0 TCS ABORT ALL Command
s 2512 -80 100 0 Gemini Telescope Control System
[cell use]
use hwin 1184 439 100 0 hwin#13
xform 0 1280 480
p 1187 472 100 0 -1 val(in):$(CAD_MARK)
use elongouts 1488 807 100 0 abortAllUnfollowTrg
xform 0 1616 896
p 1328 814 100 0 0 OMSL:closed_loop
p 1808 864 100 0 -1 def(OUT):$(tcs)unfollowAll.DIR
p 1744 864 75 768 -1 pproc(OUT):PP
use elongouts 1488 599 100 0 abortAllGuideTrg
xform 0 1616 688
p 1328 606 100 0 0 OMSL:closed_loop
p 1808 656 100 0 -1 def(OUT):$(tcs)stopGuideAll.DIR
p 1744 656 75 768 -1 pproc(OUT):PP
use estringouts 1575 1037 100 0 abortAllStopTrg
xform 0 1632 1120
p 1440 926 100 0 0 OMSL:closed_loop
p 1440 1086 100 0 0 VAL:MARK
p 1830 1094 100 0 -1 def(OUT):$(tcs)stopAll.A
p 1768 1112 75 768 -1 pproc(OUT):NPP
p 1432 1096 75 1280 -1 pproc(SDIS):NPP
use bc200tr -288 -360 -100 0 frame
xform 0 1392 944
use outhier 1528 1352 100 0 MESS
xform 0 1520 1392
use outhier 1528 1432 100 0 VAL
xform 0 1520 1472
use inhier 168 1352 100 0 ICID
xform 0 160 1392
use inhier 168 1432 100 0 DIR
xform 0 160 1472
use ecad8 792 520 -100 0 abortAll
xform 0 928 1024
p 864 1672 100 0 0 FTVA:STRING
p 864 1640 100 0 0 FTVB:DOUBLE
p 864 1608 100 0 0 FTVC:DOUBLE
p 864 1576 100 0 0 FTVD:DOUBLE
p 864 1544 100 0 0 FTVE:DOUBLE
p 864 1512 100 0 0 FTVF:DOUBLE
p 864 1480 100 0 0 FTVG:DOUBLE
p 864 1448 100 0 0 FTVH:DOUBLE
p 864 1960 100 0 0 SNAM:tcsCADabortAll
p 864 -3224 100 0 0 def(SPLK):0.0
p 864 776 100 0 0 def(STLK):0.0
p 864 494 100 0 -1 name:$(tcs)abortAll
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
