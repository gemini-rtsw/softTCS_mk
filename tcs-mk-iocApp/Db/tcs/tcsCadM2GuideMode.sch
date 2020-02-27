[schematic2]
uniq 53
[tools]
[detail]
w 1576 955 100 0 n#52 ebos.absorbFocusFlag.FLNK 1728 1120 1840 1120 1840 944 1360 944 1360 800 1472 800 ebos.comaCorrectFlag.SLNK
w 1004 1452 100 0 n#51 ecad8.ecad8#0.VALD 857 1441 1200 1441 1200 832 1472 832 ebos.comaCorrectFlag.DOL
w 1020 1516 100 0 n#50 ecad8.ecad8#0.VALC 857 1505 1232 1505 1232 1120 1472 1120 ebos.absorbFocusFlag.DOL
w 1576 1243 100 0 n#48 estringouts.comaCorrect.FLNK 1728 1376 1840 1376 1840 1232 1360 1232 1360 1088 1472 1088 ebos.absorbFocusFlag.SLNK
w 1314 1304 100 0 n#44 ecad8.ecad8#0.STLK 857 961 1312 961 1312 1600 1472 1600 estringouts.absorbFocus.SLNK
w 1036 1571 100 0 n#43 ecad8.ecad8#0.VALB 857 1569 1264 1569 1264 1392 1472 1392 estringouts.comaCorrect.DOL
w 1576 1490 100 0 n#42 estringouts.absorbFocus.FLNK 1728 1616 1840 1616 1840 1488 1360 1488 1360 1360 1472 1360 estringouts.comaCorrect.SLNK
w 1156 1634 100 0 n#41 ecad8.ecad8#0.VALA 857 1633 889 1633 889 1632 1472 1632 estringouts.absorbFocus.DOL
w 1028 1797 100 0 n#18 ecad8.ecad8#0.MESS 857 1793 1248 1793 1248 1728 1376 1728 outhier.MESS.p
w 1092 1829 100 0 n#17 ecad8.ecad8#0.VAL 857 1825 1376 1825 1376 1824 outhier.VAL.p
w 322 1715 100 0 n#4 inhier.ICID.P 228 1713 452 1713 452 1793 537 1793 ecad8.ecad8#0.ICID
w 322 1859 100 0 n#3 inhier.DIR.P 228 1857 452 1857 452 1825 537 1825 ecad8.ecad8#0.DIR
s 2592 2400 100 0 $Id: tcsCadM2GuideMode.sch,v 1.2 2000/01/30 00:03:52 cjm Exp $
s 2848 208 100 0 Gemini Telescope Control System
[cell use]
use ebos 1472 999 100 0 absorbFocusFlag
xform 0 1600 1088
p 1472 1184 100 0 -1 DESC:Absorbing focus errors
p 1152 1038 100 0 0 OMSL:closed_loop
p 1152 942 100 0 0 ONAM:On
p 1152 974 100 0 0 ZNAM:Off
use ebos 1472 711 100 0 comaCorrectFlag
xform 0 1600 800
p 1472 896 100 0 -1 DESC:Correcting for coma errors
p 1152 750 100 0 0 OMSL:closed_loop
p 1152 654 100 0 0 ONAM:On
p 1152 686 100 0 0 ZNAM:Off
use estringouts 1496 1528 100 0 absorbFocus
xform 0 1600 1600
p 1504 1678 100 0 -1 DESC:Absorb focus mode
p 1408 1406 100 0 0 OMSL:closed_loop
p 1408 1566 100 0 0 VAL:Off
p 1872 1582 100 0 -1 def(OUT):$(sad)absorbFocus
p 1744 1520 100 1024 1 name:$(tcs)$(I)
p 1728 1584 75 768 -1 pproc(OUT):PP
use estringouts 1496 1288 100 0 comaCorrect
xform 0 1600 1360
p 1504 1438 100 0 -1 DESC:Coma Correct mode
p 1408 1166 100 0 0 OMSL:closed_loop
p 1408 1326 100 0 0 VAL:Off
p 1872 1342 100 0 -1 def(OUT):$(sad)comaCorrect
p 1584 1280 100 1024 0 name:$(tcs)$(I)
p 1728 1344 75 768 -1 pproc(OUT):PP
use outhier 1368 1688 100 0 MESS
xform 0 1360 1728
use outhier 1368 1784 100 0 VAL
xform 0 1360 1824
use inhier 236 1673 100 0 ICID
xform 0 228 1713
use inhier 236 1817 100 0 DIR
xform 0 228 1857
use ecad8 561 873 100 0 ecad8#0
xform 0 697 1377
p 553 1919 100 0 -1 DESC:Implement m2GuideMode command
p 633 1505 100 0 0 FTVC:LONG
p 633 1473 100 0 0 FTVD:LONG
p 633 1441 100 0 0 FTVE:STRING
p 633 1217 100 0 0 PREC:2
p 633 1087 100 0 1 SNAM:$(snam)
p 677 801 100 1024 1 name:$(tcs)$(cad)
use bc200tr 16 -72 -100 0 frame
xform 0 1696 1232
[comments]
