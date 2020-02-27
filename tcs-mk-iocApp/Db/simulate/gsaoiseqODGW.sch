[schematic2]
uniq 55
[tools]
[detail]
w 1520 43 100 0 n#54 ecalcs.calcExp4.FLNK 1264 32 1824 32 outhier.FLNK.p
w 1376 11 100 0 n#53 ecalcs.calcExp4.VAL 1264 0 1536 0 outhier.EXP4.p
w 1368 587 100 0 n#52 ecalcs.calcExp3.VAL 1248 576 1536 576 outhier.EXP3.p
w 1368 1195 100 0 n#51 ecalcs.calcExp2.VAL 1248 1184 1536 1184 outhier.EXP2.p
w 1368 1803 100 0 n#50 ecalcs.calcExp1.VAL 1248 1792 1536 1792 outhier.EXP1.p
w 1048 267 100 0 n#49 ecalcs.calcExp3.FLNK 1248 608 1344 608 1344 256 800 256 800 -192 976 -192 ecalcs.calcExp4.SLNK
w 1048 875 100 0 n#48 ecalcs.calcExp2.FLNK 1248 1216 1344 1216 1344 864 800 864 800 384 960 384 ecalcs.calcExp3.SLNK
w 1048 1483 100 0 n#47 ecalcs.calcExp1.FLNK 1248 1824 1344 1824 1344 1472 800 1472 800 992 960 992 ecalcs.calcExp2.SLNK
w 736 171 100 0 n#45 ecad20.seqODGW.VALJ 192 992 544 992 544 160 976 160 ecalcs.calcExp4.INPB
w 696 747 100 0 n#44 ecad20.seqODGW.VALI 192 1056 480 1056 480 736 960 736 ecalcs.calcExp3.INPB
w 616 1995 100 0 n#41 ecad20.seqODGW.VALD 192 1376 320 1376 320 1984 960 1984 ecalcs.calcExp1.INPA
w 616 1387 100 0 n#41 junction 320 1376 960 1376 ecalcs.calcExp2.INPA
w 616 779 100 0 n#41 junction 320 1376 320 768 960 768 ecalcs.calcExp3.INPA
w 624 203 100 0 n#41 junction 320 768 320 192 976 192 ecalcs.calcExp4.INPA
w 696 1355 100 0 n#43 ecad20.seqODGW.VALH 192 1120 480 1120 480 1344 960 1344 ecalcs.calcExp2.INPB
w 632 1963 100 0 n#42 ecad20.seqODGW.VALG 192 1184 352 1184 352 1952 960 1952 ecalcs.calcExp1.INPB
w 664 1611 100 0 n#40 ecad20.seqODGW.STLK 192 128 416 128 416 1600 960 1600 ecalcs.calcExp1.SLNK
s 2032 2064 100 0 $Id: gsaoiseqODGW.sch,v 1.2 2010/03/12 15:37:28 ajf Exp $
s 2016 -128 100 0 Copyright
s 2016 -160 100 0 Observatory
s 2016 -192 100 0 Sciences Ltd.
[cell use]
use outhier 1792 -9 100 0 FLNK
xform 0 1808 32
use outhier 1504 1751 100 0 EXP1
xform 0 1520 1792
use outhier 1504 1143 100 0 EXP2
xform 0 1520 1184
use outhier 1504 535 100 0 EXP3
xform 0 1520 576
use outhier 1504 -41 100 0 EXP4
xform 0 1520 0
use ecalcs 960 1511 100 0 calcExp1
xform 0 1104 1776
p 1088 1728 100 0 -1 CALC:A*B
p 672 1662 100 0 0 EGU:seconds
p 672 1630 100 0 0 PREC:3
p 1072 1504 100 1024 0 name:$(gsaoi)seqODGW:$(I)
use ecalcs 960 903 100 0 calcExp2
xform 0 1104 1168
p 1088 1120 100 0 -1 CALC:A*B
p 672 1054 100 0 0 EGU:seconds
p 672 1022 100 0 0 PREC:3
p 1072 896 100 1024 0 name:$(gsaoi)seqODGW:$(I)
use ecalcs 960 295 100 0 calcExp3
xform 0 1104 560
p 1088 512 100 0 -1 CALC:A*B
p 672 446 100 0 0 EGU:seconds
p 672 414 100 0 0 PREC:3
p 1072 288 100 1024 0 name:$(gsaoi)seqODGW:$(I)
use ecalcs 976 -281 100 0 calcExp4
xform 0 1120 -16
p 1104 -64 100 0 -1 CALC:A*B
p 688 -130 100 0 0 EGU:seconds
p 688 -162 100 0 0 PREC:3
p 1088 -288 100 1024 0 name:$(gsaoi)seqODGW:$(I)
use ecad20 -128 39 100 0 seqODGW
xform 0 32 928
p -32 1664 100 0 0 DESC:Implement GSAOI DC seqODGW command
p -32 640 100 0 0 SNAM:tcsGsaoiseqODGWCAD
p -16 32 100 1024 0 name:$(gsaoi)dc:$(I)
use bc200tr -560 -408 -100 0 frame
xform 0 1120 896
[comments]
