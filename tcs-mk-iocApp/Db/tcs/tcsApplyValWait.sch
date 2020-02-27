[schematic2]
uniq 24
[tools]
[detail]
w 1560 1122 100 0 n#23 estringouts.estringouts#14.OUT 1360 1120 1808 1120 outhier.MLNK.p
w 1000 1170 100 0 n#20 inhier.c#21.P 944 1168 1104 1168 estringouts.estringouts#14.DOL
w 808 1442 100 0 n#19 inhier.c#18.P 752 1440 912 1440 eaos.eaos#5.DOL
w 1096 1266 100 0 n#15 eaos.eaos#5.FLNK 1168 1440 1328 1440 1328 1264 912 1264 912 1136 1104 1136 estringouts.estringouts#14.SLNK
w 1470 1410 100 0 n#9 eaos.eaos#5.VAL 1168 1408 1808 1408 outhier.VAL.p
s 1488 816 100 0 Gemini Telescope Control System
s 1344 2016 100 0 $Id: tcsApplyValWait.sch,v 1.2 2001/05/21 15:50:08 cjm Exp $
s 1488 752 100 0 Get APPLY MESS and VAL
s 1728 688 100 0 1
s 1840 688 100 0 1
[cell use]
use outhier 1800 1368 100 0 VAL
xform 0 1792 1408
use outhier 1800 1080 100 0 MLNK
xform 0 1792 1120
use inhier 760 1400 100 0 c#18
xform 0 752 1440
use inhier 952 1128 100 0 c#21
xform 0 944 1168
use estringouts 1128 1064 100 0 estringouts#14
xform 0 1232 1136
p 1040 942 100 0 0 OMSL:closed_loop
p 768 1198 100 0 -1 def(DOL):$(top)apply.MESS
p 1424 1134 100 0 0 def(OUT):0.0
p 1188 1056 100 1024 1 name:$(top)ApplyValWso
p 1360 1120 75 768 -1 pproc(OUT):PP
use bb200tr -544 536 -100 0 frame
xform 0 736 1360
use eaos 936 1320 100 0 eaos#5
xform 0 1040 1408
p 656 1390 100 0 0 OMSL:closed_loop
p 624 1470 100 0 -1 def(DOL):$(top)apply.VAL
p 1344 1390 100 0 0 def(OUT):0.0
p 1104 1312 100 1024 1 name:$(top)ApplyValWao
p 880 1440 75 1280 -1 pproc(DOL):CPP
p 1168 1376 75 768 -1 pproc(OUT):PP
[comments]
