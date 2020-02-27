[schematic2]
uniq 11
[tools]
[detail]
w 664 2011 100 0 n#1 eais.m1ModelMaxAge.VAL 616 2008 712 2008 egenSub.calcM1Valid.INPA
w 1180 2011 100 0 n#2 egenSub.calcM1Valid.OUTA 1000 2008 1360 2008 ebis.m1AOModelValid.SLNK
w 1096 1947 100 0 n#3 egenSub.calcM1Valid.OUTB 1000 1944 1192 1944 1192 1944 1256 1944 1256 1792 1352 1792 estringouts.m1AOModelReason.SLNK
w 1112 1883 100 0 n#4 egenSub.calcM1Valid.OUTC 1000 1880 1224 1880 1224 1552 1352 1552 ebis.m1ModelValid.SLNK
w 1096 1819 100 0 n#5 egenSub.calcM1Valid.OUTD 1000 1816 1192 1816 1192 1328 1352 1328 estringouts.m1ModelReason.SLNK
w 1084 1755 100 0 n#6 egenSub.calcM1Valid.OUTE 1000 1752 1168 1752 1168 1120 1352 1120 ebis.m1GPIModelValid.SLNK
w 1076 1691 100 0 n#7 egenSub.calcM1Valid.OUTF 1000 1688 1152 1688 1152 928 1352 928 estringouts.m1GPIModelReason.SLNK
w 2634 1794 -100 0 n#8 egenSub.m1FileStatus.OUTA 2624 1792 2840 1792 2840 1776 2896 1776 estringouts.m1ModelName.SLNK
w 2634 1730 -100 0 n#9 egenSub.m1FileStatus.OUTB 2624 1728 2776 1728 2776 1584 2896 1584 estringouts.m1RestoredFile.SLNK
w 2634 1666 -100 0 n#10 egenSub.m1FileStatus.OUTC 2624 1664 2736 1664 2736 1392 2896 1392 estringouts.m1RestoredTime.SLNK
s 2570 2441 100 0 $Id: tcsM1CalcModelValid.sch,v 1.3 2013/10/15 12:39:31 cjm Exp $
s 2859 252 100 0 Gemini Telescope Control System
s 2867 196 100 0 Compute M1 stored model validity
s 2587 252 100 0 Copyright
s 2587 220 100 0 Observatory
s 2587 188 100 0 Sciences Ltd.
[cell use]
use bc200tr 0 0 100 0 bc200tr#1
xform 0 1680 1280
use egenSub 783 1226 100 0 calcM1Valid
xform 0 856 1672
p 489 1021 100 0 0 FTVA:LONG
p 489 1021 100 0 0 FTVB:STRING
p 489 989 100 0 0 FTVC:LONG
p 489 957 100 0 0 FTVD:STRING
p 785 1197 100 0 1 SCAN:10 second
p 782 1169 100 0 1 SNAM:tcsOpticsCalcM1ValidFlags
p 762 2096 100 0 -1 DESC:Calc M1 Model valid flags
p 1008 2018 75 0 -1 pproc(OUTA):PP
p 1008 1954 75 0 -1 pproc(OUTB):PP
p 1008 1890 75 0 -1 pproc(OUTC):PP
p 1008 1826 75 0 -1 pproc(OUTD):PP
p 489 925 100 0 0 FTVE:LONG
p 489 861 100 0 0 FTVF:STRING
p 1008 1762 75 0 -1 pproc(OUTE):PP
p 1008 1698 75 0 -1 pproc(OUTF):PP
use ebis 1425 1924 100 0 m1AOModelValid
xform 0 1488 2008
p 1446 2072 100 0 -1 DESC:AO valid
p 1136 1846 100 0 0 ONAM:Valid
p 1136 1878 100 0 0 ZNAM:Invalid
p 1360 1942 100 0 0 ZSV:MAJOR
use ebis 1417 1470 100 0 m1ModelValid
xform 0 1480 1552
p 1438 1616 100 0 -1 DESC:Non AO valid
p 1128 1390 100 0 0 ONAM:Valid
p 1128 1422 100 0 0 ZNAM:Invalid
p 1352 1486 100 0 0 ZSV:MAJOR
use eais 415 1928 100 0 m1ModelMaxAge
xform 0 488 2024
p 390 2104 100 0 -1 DESC:Maximum file age
p 104 1766 100 0 0 EGU:hours
p 104 1862 100 0 0 PREC:3
use estringouts 1416 1714 100 0 m1AOModelReason
xform 0 1480 1792
use estringouts 1416 1250 100 0 m1ModelReason
xform 0 1480 1328
use ebis 1417 1036 100 0 m1GPIModelValid
xform 0 1480 1120
p 1438 1184 100 0 -1 DESC:GPI Valid
p 1128 958 100 0 0 ONAM:Valid
p 1128 990 100 0 0 ZNAM:Invalid
p 1352 1054 100 0 0 ZSV:MAJOR
use estringouts 1416 850 100 0 m1GPIModelReason
xform 0 1480 928
use estringouts 2960 1698 100 0 m1ModelName
xform 0 3024 1776
p 2832 1742 100 0 0 VAL:non-AO
p 2934 1846 100 0 -1 DESC:Type of restored model
use estringouts 2960 1506 100 0 m1RestoredFile
xform 0 3024 1584
p 2832 1550 100 0 0 VAL:None
p 2917 1648 100 0 -1 DESC:Name of last restored file
use estringouts 2960 1314 100 0 m1RestoredTime
xform 0 3024 1392
p 2832 1358 100 0 0 VAL:None
p 2917 1456 100 0 -1 DESC:Time file was restored
use egenSub 2401 1024 100 0 m1FileStatus
xform 0 2480 1456
p 2373 1879 100 0 -1 DESC:Compute file restore status
p 2113 805 100 0 0 FTVA:STRING
p 2113 805 100 0 0 FTVB:STRING
p 2113 773 100 0 0 FTVC:STRING
p 2632 1802 75 0 -1 pproc(OUTA):PP
p 2632 1738 75 0 -1 pproc(OUTB):PP
p 2632 1674 75 0 -1 pproc(OUTC):PP
p 2400 994 100 0 1 SNAM:tcsOpticsM1FileStatus
p 2400 965 100 0 1 SCAN:1 second
[comments]
