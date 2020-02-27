[schematic2]
uniq 28
[tools]
[detail]
w 800 1451 100 0 n#27 ecalcouts.ecalcouts#25.VAL 608 1344 736 1344 736 1440 912 1440 eaos.eaos#5.DOL
w 736 1419 100 0 n#26 ecalcouts.ecalcouts#25.FLNK 608 1408 912 1408 eaos.eaos#5.SLNK
w 1560 1122 100 0 n#23 estringouts.estringouts#14.OUT 1360 1120 1808 1120 outhier.c#22.p
w 1000 1170 100 0 n#20 inhier.c#21.P 944 1168 1104 1168 estringouts.estringouts#14.DOL
w 1096 1266 100 0 n#15 eaos.eaos#5.FLNK 1168 1440 1328 1440 1328 1264 912 1264 912 1136 1104 1136 estringouts.estringouts#14.SLNK
w 1470 1378 100 0 n#9 eaos.eaos#5.OUT 1168 1376 1808 1376 outhier.c#8.p
s 1488 816 100 0 Gemini Telescope Control System
s 1344 2016 100 0 $Id: tcsSubcadWait.sch,v 1.2 2001/05/21 15:57:36 cjm Exp $
s 1488 752 100 0 Get status from Subsystem CAD
s 1728 688 100 0 1
s 1840 688 100 0 1
[cell use]
use ecalcouts 288 1223 100 0 ecalcouts#25
xform 0 448 1344
p 360 1256 100 0 -1 CALC:A
p 376 1488 100 0 1 OOPT:On Change
p -48 1408 100 0 -1 def(INPA):$(subsys)$(subcad).VAL
p 352 1224 100 0 -1 name:$(tcs)$(cad)ScWait
p 240 1416 75 0 -1 pproc(INPA):CPP
use outhier 1800 1336 100 0 c#8
xform 0 1792 1376
use outhier 1800 1080 100 0 c#22
xform 0 1792 1120
use inhier 952 1128 100 0 c#21
xform 0 944 1168
use estringouts 1128 1064 100 0 estringouts#14
xform 0 1232 1136
p 1040 942 100 0 0 OMSL:closed_loop
p 768 1198 100 0 -1 def(DOL):$(subsys)$(subcad).MESS
p 1424 1134 100 0 -1 def(OUT):$(tcs)$(prefix)SubcadMess.VAL
p 1188 1056 100 1024 1 name:$(tcs)$(cad)ScWso
p 1360 1120 75 768 -1 pproc(OUT):PP
use bb200tr -544 536 -100 0 frame
xform 0 736 1360
use eaos 936 1320 100 0 eaos#5
xform 0 1040 1408
p 656 1390 100 0 0 OMSL:closed_loop
p 656 1422 100 0 0 PINI:YES
p 624 1470 100 0 0 def(DOL):0.0
p 1344 1390 100 0 -1 def(OUT):$(tcs)$(prefix)SubcadStat.VAL
p 1104 1312 100 1024 1 name:$(tcs)$(cad)ScWao
p 1168 1376 75 768 -1 pproc(OUT):PP
[comments]
