[schematic2]
uniq 172
[tools]
[detail]
w 642 -30 100 0 n#171 ecad20.park.STLK 224 -32 1120 -32 1120 864 1616 864 elongouts.elongouts#119.SLNK
w 386 866 100 0 n#170 ecad20.park.OUTI 224 864 608 864 outhier.c#158.p
w 386 930 100 0 n#169 ecad20.park.OUTH 224 928 608 928 outhier.c#159.p
w 386 994 100 0 n#168 ecad20.park.OUTG 224 992 608 992 outhier.c#160.p
w 386 1058 100 0 n#167 ecad20.park.OUTF 224 1056 608 1056 outhier.c#161.p
w 386 1122 100 0 n#166 ecad20.park.OUTE 224 1120 608 1120 outhier.c#149.p
w 386 1186 100 0 n#165 ecad20.park.OUTD 224 1184 608 1184 outhier.c#148.p
w 386 1250 100 0 n#164 ecad20.park.OUTC 224 1248 608 1248 outhier.c#145.p
w 386 1314 100 0 n#163 ecad20.park.OUTB 224 1312 608 1312 outhier.c#137.p
w 386 1378 100 0 n#162 ecad20.park.OUTA 224 1376 608 1376 outhier.c#135.p
w -326 1122 100 0 n#156 inhier.c#133.P -496 1120 -96 1120 ecad20.park.INPE
w -326 1186 100 0 n#155 inhier.c#132.P -496 1184 -96 1184 ecad20.park.INPD
w -326 1250 100 0 n#154 inhier.c#129.P -496 1248 -96 1248 ecad20.park.INPC
w -326 1314 100 0 n#153 inhier.c#128.P -496 1312 -96 1312 ecad20.park.INPB
w -326 1378 100 0 n#152 inhier.c#125.P -496 1376 -96 1376 ecad20.park.INPA
w 1544 642 100 0 n#118 hwin.hwin#122.in 1520 640 1616 640 elongouts.elongouts#120.DOL
w 1544 898 100 0 n#117 hwin.hwin#121.in 1520 896 1616 896 elongouts.elongouts#119.DOL
w 1688 738 100 0 n#115 elongouts.elongouts#119.FLNK 1872 896 1936 896 1936 736 1488 736 1488 608 1616 608 elongouts.elongouts#120.SLNK
s 1632 2000 100 0 $Id: m2Park.sch,v 1.1.1.1 1998/11/08 00:20:22 epics Exp $
s 1840 -256 100 0 Simulation of parking secondary mirror
s 1856 -192 100 0 Gemini Telescope Control System
[cell use]
use outhier 600 1016 100 0 c#161
xform 0 592 1056
use outhier 600 952 100 0 c#160
xform 0 592 992
use outhier 600 888 100 0 c#159
xform 0 592 928
use outhier 600 824 100 0 c#158
xform 0 592 864
use ecad20 -72 -120 100 0 park
xform 0 64 768
p -32 1662 100 0 -1 DESC:SCS park command
p -32 -194 100 0 1 SNAM:tcsM2parkCAD
p 16 -128 100 1024 0 name:$(m2)$(I)
p -400 1390 100 0 -1 def(INPA):$(m2)xTiltDef
p -400 1326 100 0 -1 def(INPB):$(m2)yTiltDef
p -400 1262 100 0 -1 def(INPC):$(m2)xDef
p -400 1198 100 0 -1 def(INPD):$(m2)yDef
p -400 1150 100 0 -1 def(INPE):$(m2)zDef
p 352 1390 100 0 -1 def(OUTA):$(m2)move.A
p 352 1326 100 0 -1 def(OUTB):$(m2)move.B
p 352 1262 100 0 -1 def(OUTC):$(m2)move.C
p 352 1198 100 0 -1 def(OUTD):$(m2)move.D
p 352 1134 100 0 -1 def(OUTE):$(m2)move.E
p 352 1070 100 0 -1 def(OUTF):$(m2)move.F
p 352 1006 100 0 -1 def(OUTG):$(m2)move.G
p 352 942 100 0 -1 def(OUTH):$(m2)move.H
p 352 878 100 0 -1 def(OUTI):$(m2)move.I
use bc200tr -960 -472 -100 0 frame
xform 0 720 832
use outhier 600 1336 100 0 c#135
xform 0 592 1376
use outhier 600 1272 100 0 c#137
xform 0 592 1312
use outhier 600 1208 100 0 c#145
xform 0 592 1248
use outhier 600 1144 100 0 c#148
xform 0 592 1184
use outhier 600 1080 100 0 c#149
xform 0 592 1120
use inhier -488 1336 100 0 c#125
xform 0 -496 1376
use inhier -488 1272 100 0 c#128
xform 0 -496 1312
use inhier -488 1208 100 0 c#129
xform 0 -496 1248
use inhier -488 1144 100 0 c#132
xform 0 -496 1184
use inhier -488 1080 100 0 c#133
xform 0 -496 1120
use hwin 1352 600 100 0 hwin#122
xform 0 1424 640
p 1331 632 100 0 -1 val(in):3
use hwin 1352 856 100 0 hwin#121
xform 0 1424 896
p 1331 888 100 0 -1 val(in):0
use elongouts 1640 520 100 0 elongouts#120
xform 0 1744 608
p 1664 702 100 0 -1 DESC:Start Directive
p 1728 512 100 1024 -1 name:$(m2)startPark
p 1872 576 75 768 -1 pproc(OUT):PP
p 1952 574 100 0 -1 def(OUT):$(m2)move.DIR
p 1456 526 100 0 0 OMSL:closed_loop
use elongouts 1640 776 100 0 elongouts#119
xform 0 1744 864
p 1664 958 100 0 -1 DESC:Mark directive
p 1728 768 100 1024 -1 name:$(m2)markPark
p 1872 832 75 768 -1 pproc(OUT):PP
p 1952 830 100 0 -1 def(OUT):$(m2)move.DIR
p 1456 782 100 0 0 OMSL:closed_loop
[comments]
