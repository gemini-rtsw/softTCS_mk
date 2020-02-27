[schematic2]
uniq 42
[tools]
[detail]
w 1568 491 100 0 n#41 efanouts.efanouts#1.LNK2 1264 1296 1472 1296 1472 480 1712 480 tcsMarkStartSubCAD.tcsMarkStartSubCAD#40.SubCadStart
w 1424 1570 100 0 n#39 efanouts.efanouts#0.LNK4 1264 1568 1632 1568 1632 1440 1712 1440 tcsMarkStartSubCAD.tcsMarkStartSubCAD#36.SubCadStart
w 1424 1602 100 0 n#33 efanouts.efanouts#0.LNK3 1264 1600 1632 1600 1632 1664 1712 1664 tcsMarkStartSubCAD.tcsMarkStartSubCAD#29.SubCadStart
w 1408 1634 100 0 n#32 efanouts.efanouts#0.LNK2 1264 1632 1600 1632 1600 1872 1712 1872 tcsMarkStartSubCAD.tcsMarkStartSubCAD#35.SubCadStart
w 1570 1904 100 0 n#31 efanouts.efanouts#0.LNK1 1264 1664 1568 1664 1568 2096 1712 2096 tcsMarkStartSubCAD.tcsMarkStartSubCAD#34.SubCadStart
w 1570 1376 100 0 n#28 efanouts.efanouts#0.LNK5 1264 1536 1568 1536 1568 1168 1728 1168 tcsMarkStartSubCAD.tcsMarkStartSubCAD#27.SubCadStart
w 1506 1048 100 0 n#24 efanouts.efanouts#1.LNK1 1264 1328 1504 1328 1504 720 1712 720 tcsMarkStartSubCAD.tcsMarkStartSubCAD#38.SubCadStart
w 1538 1240 100 0 n#23 efanouts.efanouts#0.LNK6 1264 1504 1536 1504 1536 928 1712 928 tcsMarkStartSubCAD.tcsMarkStartSubCAD#37.SubCadStart
w 824 1586 100 0 n#12 inhier.slnk.P 640 1568 672 1568 672 1584 1024 1584 efanouts.efanouts#0.SLNK
w 898 1554 100 0 n#3 efanouts.efanouts#0.FLNK 1264 1696 1296 1696 1296 1824 896 1824 896 1248 1024 1248 efanouts.efanouts#1.SLNK
s 1216 2240 100 0 contained in $(subcad)
s 1216 2272 100 0 by apply a mark then start to the command whose name is
s 1216 2304 100 0 all subsystems. It fans out the command to each subsystem
s 1216 2336 100 0 This schematic is used for commands that are common to
s 2496 2432 100 0 $Id: tcsAllSubsysCad.sch,v 1.2 2001/09/25 16:24:48 ptaylor Exp $
s 2720 160 100 0 TCS subsystems
s 2720 192 100 0 Issue the same CAD command to all
s 3088 112 100 0 1
s 2992 112 100 0 1
s 2528 96 100 0 P B Taylor
s 2528 128 100 0 16 Jan 97
s 2736 240 100 0 Gemini Telescope Control System
[cell use]
use tcsMarkStartSubCAD 1736 392 100 0 tcsMarkStartSubCAD#40
xform 0 1840 456
p 1712 398 100 0 1 seta:prefix gp
p 1712 366 100 0 1 setb:subsys $(gp)
p 1712 334 100 0 1 setc:subcad $(cad)
p 1712 302 100 0 1 setd:text GPOL
use tcsMarkStartSubCAD 1736 632 100 0 tcsMarkStartSubCAD#38
xform 0 1840 696
p 1712 638 100 0 1 seta:prefix ao
p 1712 606 100 0 1 setb:subsys $(ao)
p 1712 574 100 0 1 setc:subcad $(cad)
p 1712 542 100 0 1 setd:text GAOS
use tcsMarkStartSubCAD 1736 840 100 0 tcsMarkStartSubCAD#37
xform 0 1840 904
p 1712 846 100 0 1 seta:prefix m1
p 1712 814 100 0 1 setb:subsys $(m1)
p 1712 782 100 0 1 setc:subcad $(cad)
p 1712 750 100 0 1 setd:text PCS
use tcsMarkStartSubCAD 1736 1352 100 0 tcsMarkStartSubCAD#36
xform 0 1840 1416
p 1712 1358 100 0 1 seta:prefix ag
p 1712 1326 100 0 1 setb:subsys $(ag)
p 1712 1294 100 0 1 setc:subcad $(cad)
p 1712 1262 100 0 1 setd:text A&G
use tcsMarkStartSubCAD 1736 1784 100 0 tcsMarkStartSubCAD#35
xform 0 1840 1848
p 1712 1790 100 0 1 seta:prefix cr
p 1712 1758 100 0 1 setb:subsys $(cr)
p 1712 1726 100 0 1 setc:subcad $(cad)
p 1712 1694 100 0 1 setd:text Rotator
use tcsMarkStartSubCAD 1736 2008 100 0 tcsMarkStartSubCAD#34
xform 0 1840 2072
p 1712 2014 100 0 1 seta:prefix mc
p 1712 1982 100 0 1 setb:subsys $(mc)
p 1712 1950 100 0 1 setc:subcad $(cad)
p 1712 1918 100 0 1 setd:text MCS
use tcsMarkStartSubCAD 1736 1576 100 0 tcsMarkStartSubCAD#29
xform 0 1840 1640
p 1712 1582 100 0 1 seta:prefix ec
p 1712 1550 100 0 1 setb:subsys $(ec)
p 1712 1518 100 0 1 setc:subcad $(cad)
p 1712 1486 100 0 1 setd:text ECS
use tcsMarkStartSubCAD 1752 1080 100 0 tcsMarkStartSubCAD#27
xform 0 1856 1144
p 1728 1070 100 0 1 seta:prefix m2
p 1728 1038 100 0 1 setb:subsys $(m2)
p 1728 1006 100 0 1 setc:subcad $(cad)
p 1728 974 100 0 1 setd:text SCS
use inhier 648 1528 100 0 slnk
xform 0 640 1568
use efanouts 1048 1448 100 0 efanouts#0
xform 0 1144 1600
p 1008 1454 100 0 1 name:$(tcs)$(cad)fanA
use efanouts 1048 1112 100 0 efanouts#1
xform 0 1144 1264
p 1008 1102 100 0 1 name:$(tcs)$(cad)fanB
use bc200tr -80 -40 -100 0 frame
xform 0 1600 1264
[comments]
