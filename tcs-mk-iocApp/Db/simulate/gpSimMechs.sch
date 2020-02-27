[schematic2]
uniq 105
[tools]
[detail]
w 2642 1003 100 0 n#103 ecalcs.calc1.FLNK 2624 992 2720 992 2720 896 2816 896 gpInPosn.gpInPosn#92.SLNK
w 2690 971 100 0 n#102 ecalcs.calc1.VAL 2624 960 2816 960 gpInPosn.gpInPosn#92.INPOS
w 2002 1291 100 0 n#101 efanouts.fan1.LNK2 2448 1696 2560 1696 2560 1280 1504 1280 1504 752 1632 752 esels.sel2.SLNK
w 2034 1659 100 0 n#100 esels.sel1.FLNK 1920 1648 2208 1648 efanouts.fan1.SLNK
w 2560 1739 100 0 FLNK efanouts.fan1.LNK1 2448 1728 2720 1728 outhier.FLNK.p
w 2152 1163 100 0 n#97 esels.sel2.VAL 1920 960 2016 960 2016 1152 2336 1152 ecalcs.calc1.INPA
w 2200 779 100 0 n#96 esels.sel2.FLNK 1920 992 2112 992 2112 768 2336 768 ecalcs.calc1.SLNK
w 1448 1019 100 0 n#50 junction 1312 1600 1312 1008 1632 1008 esels.sel2.INPE
w 1304 1611 100 0 n#50 gpIdentifyCad.gpIdentifyCad#47.VAL 448 512 1024 512 1024 1600 1632 1600 esels.sel1.INPG
w 1464 1051 100 0 n#49 junction 1344 1632 1344 1040 1632 1040 esels.sel2.INPD
w 1288 1643 100 0 n#49 gpMechCad.gpMechCad#45.VAL 464 816 992 816 992 1632 1632 1632 esels.sel1.INPF
w 1480 1083 100 0 n#39 junction 1376 1728 1376 1072 1632 1072 esels.sel2.INPC
w 1240 1739 100 0 n#39 gpPlateAngle.gpPlateAngle#91.VAL 448 1568 896 1568 896 1728 1632 1728 esels.sel1.INPC
w 1496 1115 100 0 n#90 junction 1408 1760 1408 1104 1632 1104 esels.sel2.INPB
w 1168 1771 100 0 n#90 gpPlateRotateCad.gpPlateRotateCad#87.VAL 464 1792 752 1792 752 1760 1632 1760 esels.sel1.INPB
w 1512 1147 100 0 n#37 junction 1440 1792 1440 1136 1632 1136 esels.sel2.INPA
w 1256 1803 100 0 n#37 gpMechCad.gpMechCad#22.VAL 448 2032 928 2032 928 1792 1632 1792 esels.sel1.INPA
w 520 1371 100 0 n#88 gpPlateBeamCad.gpPlateBeamCad#79.FLNK 448 1360 640 1360 640 1120 junction
w 664 875 100 0 n#88 gpMechCad.gpMechCad#45.FLNK 464 864 912 864 912 1120 junction
w 624 2091 100 0 n#88 gpMechCad.gpMechCad#22.FLNK 448 2080 848 2080 848 1120 junction
w 552 1627 100 0 n#88 gpPlateAngle.gpPlateAngle#91.FLNK 448 1616 704 1616 704 1120 junction
w 728 1131 100 0 n#88 gpPlateParkCad.gpPlateParkCad#81.FLNK 448 1120 1056 1120 1056 1408 1632 1408 esels.sel1.SLNK
w 656 571 100 0 n#88 gpIdentifyCad.gpIdentifyCad#47.FLNK 448 560 912 560 912 864 junction
w 600 1851 100 0 n#88 gpPlateRotateCad.gpPlateRotateCad#87.FLNK 464 1840 784 1840 784 1120 junction
w 1256 1707 100 0 n#80 gpPlateBeamCad.gpPlateBeamCad#79.VAL 448 1312 928 1312 928 1696 1632 1696 esels.sel1.INPD
w 1272 1675 100 0 n#48 gpPlateParkCad.gpPlateParkCad#81.VAL 448 1072 960 1072 960 1664 1632 1664 esels.sel1.INPE
w 2048 1563 100 0 VAL esels.sel1.VAL 1920 1616 2016 1616 2016 1552 2128 1552 outhier.VAL.p
s 1456 2224 100 0 the plateAnge, plateBeam and platePark commands
s 1456 2256 100 0 The seq command drives all its actions through
s 240 2352 150 0 Set of commands
s 240 2304 150 0 simulating GPOL
s 240 2256 150 0 mechanism control
s 2560 2448 100 0 $Id: gpSimMechs.sch,v 1.5 2002/07/02 07:42:49 cjm Exp $
s 2336 576 100 0 Need to process this at initialisation
s 2336 544 100 0 or else it will taker its default value of 0.
s 2336 512 100 0 This would mean the system was out of position
[cell use]
use gpPlateSeq 1600 2023 100 0 gpPlateSeq#104
xform 0 1720 2120
p 1600 2016 100 0 -1 seta:command seq
use efanouts 2208 1511 100 0 fan1
xform 0 2328 1664
p 2320 1504 100 1024 0 name:$(prefix)$(I)
use ecalcs 2336 679 100 0 calc1
xform 0 2480 944
p 2496 752 100 0 1 CALC:A=0?1:0
p 2496 704 100 0 1 PINI:YES
p 2448 672 100 1024 0 name:$(prefix)$(I)
use esels 1632 679 100 0 sel2
xform 0 1776 944
p 1728 1184 100 0 1 SELM:High Signal
p 1744 672 100 1024 0 name:$(prefix)$(I)
use esels 1632 1335 100 0 sel1
xform 0 1776 1600
p 1728 1744 100 0 1 SELM:High Signal
p 1744 1328 100 1024 0 name:$(prefix)$(I)
use gpInPosn 2832 935 100 0 gpInPosn#92
xform 0 2944 1040
use gpPlateAngle 224 1495 100 0 gpPlateAngle#91
xform 0 344 1592
p 224 1504 100 0 -1 seta:command plateAngle
p 224 1472 100 0 -1 setb:delay 5.0
use gpPlateRotateCad 240 1719 100 0 gpPlateRotateCad#87
xform 0 360 1816
p 240 1728 100 0 -1 seta:command plateRotate
p 240 1696 100 0 -1 setb:delay 2.0
use gpPlateParkCad 224 999 100 0 gpPlateParkCad#81
xform 0 344 1096
p 224 992 100 0 -1 seta:command platePark
p 224 960 100 0 -1 setb:delay 5.0
use gpPlateBeamCad 224 1239 100 0 gpPlateBeamCad#79
xform 0 344 1336
p 224 1232 100 0 -1 seta:command plateBeam
p 224 1200 100 0 -1 setb:delay 5.0
use gpIdentifyCad 224 439 100 0 gpIdentifyCad#47
xform 0 344 536
p 224 432 100 0 1 seta:command identify
p 224 400 100 0 1 setb:delay 5.0
use gpMechCad 232 744 100 0 gpMechCad#45
xform 0 360 840
p 248 726 100 0 -1 seta:command plateDatum
p 248 694 100 0 -1 setb:delay 5.0
use gpMechCad 216 1960 100 0 gpMechCad#22
xform 0 344 2056
p 232 1942 100 0 -1 seta:command plateStep
p 232 1910 100 0 -1 setb:delay 2.0
p 232 1878 100 0 0 setc:outa 0.0
p 232 518 100 0 0 setd:snam tcsGpGenericCAD
use outhier 2096 1511 100 0 VAL
xform 0 2112 1552
use outhier 2688 1687 100 0 FLNK
xform 0 2704 1728
use bc200tr -16 -24 -100 0 frame
xform 0 1664 1280
[comments]
