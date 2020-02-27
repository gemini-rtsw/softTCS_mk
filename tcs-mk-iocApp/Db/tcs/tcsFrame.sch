[schematic2]
uniq 6
[tools]
[detail]
w 1140 1458 100 0 n#4 embbos.cframe.VAL 1504 1024 1536 1024 1536 1168 1136 1168 1136 1712 1264 1712 ecalcs.txtvis.INPA
w 1614 1058 100 0 n#4 junction 1536 1056 1728 1056 outhier.CVAL.p
w 1334 1204 100 0 n#3 embbos.cframe.FLNK 1504 1088 1504 1200 1200 1200 1200 1328 1264 1328 ecalcs.txtvis.SLNK
s 1248 1792 300 0 frame
s 2544 80 100 0 Gemini Telescope Control System
s 2464 2240 100 0 $Id: tcsFrame.sch,v 1.1.1.1 1998/11/08 00:20:36 epics Exp $
[cell use]
use bc200tr -288 -200 -100 0 frame
xform 0 1392 1104
use outhier 1720 1016 100 0 CVAL
xform 0 1712 1056
use ecalcs 1288 1240 100 0 txtvis
xform 0 1408 1504
p 1376 1454 100 0 -1 CALC:A<2?0:1
p 1456 1342 100 0 -1 DESC:Set visibility for Source frame
use embbos 1272 968 100 0 cframe
xform 0 1376 1056
p 1456 974 100 0 -1 DESC:Co-ordinate Frame Selection
p 1504 814 100 0 -1 FRST:FK4
p 1456 814 100 0 -1 FRVL:4
p 1504 910 100 0 -1 ONST:Az/El
p 1456 910 100 0 -1 ONVL:1
p 1504 846 100 0 -1 THST:FK5
p 1456 846 100 0 -1 THVL:3
p 1504 878 100 0 -1 TWST:Apparent
p 1456 878 100 0 -1 TWVL:2
p 1504 942 100 0 -1 ZRST:Mount
p 1456 942 100 0 -1 ZRVL:0
p 1552 1102 100 0 0 def(OUT):0.0
[comments]
