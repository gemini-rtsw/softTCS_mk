[schematic2]
uniq 52
[tools]
[detail]
w 1208 1355 100 0 n#51 ecad8.ecad8#0.VALB 857 1569 992 1569 992 1344 1472 1344 ebos.m2ComaCorrFlag.DOL
w 1584 1467 100 0 n#50 estringouts.m2ComaCorrState.FLNK 1728 1616 1824 1616 1824 1456 1392 1456 1392 1312 1472 1312 ebos.m2ComaCorrFlag.SLNK
w 1314 1304 100 0 n#44 ecad8.ecad8#0.STLK 857 961 1312 961 1312 1600 1472 1600 estringouts.m2ComaCorrState.SLNK
w 1156 1634 100 0 n#41 ecad8.ecad8#0.VALA 857 1633 889 1633 889 1632 1472 1632 estringouts.m2ComaCorrState.DOL
w 1028 1797 100 0 n#18 ecad8.ecad8#0.MESS 857 1793 1248 1793 1248 1728 1376 1728 outhier.MESS.p
w 1092 1829 100 0 n#17 ecad8.ecad8#0.VAL 857 1825 1376 1825 1376 1824 outhier.VAL.p
w 322 1715 100 0 n#4 inhier.ICID.P 228 1713 452 1713 452 1793 537 1793 ecad8.ecad8#0.ICID
w 322 1859 100 0 n#3 inhier.DIR.P 228 1857 452 1857 452 1825 537 1825 ecad8.ecad8#0.DIR
s 2848 208 100 0 Gemini Telescope Control System
s 2592 2400 100 0 $Id: tcsCadM2ComaCorr.sch,v 1.1 1999/03/12 09:30:03 cjm Exp $
[cell use]
use ebos 1472 1223 100 0 m2ComaCorrFlag
xform 0 1600 1312
p 1504 1408 100 0 -1 DESC:Enable/disable flag
p 1152 1262 100 0 0 OMSL:closed_loop
p 1152 1166 100 0 0 ONAM:On
p 1152 1198 100 0 0 ZNAM:Off
p 1856 1280 100 0 0 def(OUT):0.0
p 1728 1280 75 768 -1 pproc(OUT):NPP
use estringouts 1496 1528 100 0 m2ComaCorrState
xform 0 1600 1600
p 1504 1678 100 0 -1 DESC:M2 Coma Correction state
p 1408 1406 100 0 0 OMSL:closed_loop
p 1408 1566 100 0 0 VAL:Off
p 1872 1582 100 0 0 def(OUT):0.0
p 1744 1520 100 1024 0 name:$(tcs)$(I)
p 1728 1584 75 768 -1 pproc(OUT):NPP
use outhier 1368 1784 100 0 VAL
xform 0 1360 1824
use outhier 1368 1688 100 0 MESS
xform 0 1360 1728
use inhier 236 1817 100 0 DIR
xform 0 228 1857
use inhier 236 1673 100 0 ICID
xform 0 228 1713
use ecad8 561 873 100 0 ecad8#0
xform 0 697 1377
p 553 1919 100 0 -1 DESC:Implement the m2ComaCorr command
p 640 1536 100 0 1 FTVB:LONG
p 633 1473 100 0 0 FTVD:STRING
p 633 1441 100 0 0 FTVE:STRING
p 633 1217 100 0 0 PREC:2
p 633 1087 100 0 1 SNAM:$(snam)
p 677 801 100 1024 1 name:$(tcs)$(cad)
use bc200tr 16 -72 -100 0 frame
xform 0 1696 1232
[comments]
