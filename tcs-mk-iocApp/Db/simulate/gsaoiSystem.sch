[schematic2]
uniq 18
[tools]
[detail]
w -1064 -805 100 0 n#1 hwin.hwin#114.in -1144 -808 -984 -808 gsaoiSimStandard.gsaoiSimStandard#116.INPOS
w -2095 708 100 0 n#2 genericcad.genericcad#96.FLNK -2206 705 -1984 705 -1984 -912 -1872 -912 egenSub.simStop.SLNK
w -2574 212 100 0 n#2 genericcad.genericcad#48.FLNK -2590 209 -2558 209 -2558 192 -1984 192 junction
w -1720 739 100 0 n#3 genericcad.genericcad#96.VLNK -2208 736 -1232 736 -1232 416 junction
w -1352 419 100 0 n#3 genericcad.genericcad#23.VLNK -1472 416 -1232 416 -1232 96 -752 96 esels.simCommonSel.SLNK
w -964 11 100 0 n#3 genericcad.genericcad#33.VLNK -1016 8 -912 8 -912 96 junction
w -2576 243 100 0 n#3 genericcad.genericcad#48.VLNK -2592 240 -2560 240 -2560 224 -1232 224 junction
w -1472 -333 100 0 n#4 egenSub.simStop.VALC -1584 -336 -1360 -336 -1360 -528 -1168 -528 estringouts.p3FollowS.DOL
w -1436 -269 100 0 n#5 egenSub.simStop.VALB -1584 -272 -1288 -272 -1288 -368 -1168 -368 estringouts.p2FollowS.DOL
w -1584 659 100 0 n#6 genericcad.genericcad#96.VAL -2208 656 -960 656 -960 288 -752 288 esels.simCommonSel.INPG
w -1376 -205 100 0 n#7 egenSub.simStop.VALA -1584 -208 -1168 -208 estringouts.p1FollowS.DOL
w -424 339 100 0 n#8 esels.simCommonSel.FLNK -464 336 -384 336 -384 400 -304 400 outhier.FLNK.p
w -384 307 100 0 n#9 esels.simCommonSel.VAL -464 304 -304 304 outhier.VAL.p
w -948 -69 100 0 n#10 genericcad.genericcad#33.VAL -1016 -72 -880 -72 -880 320 -752 320 esels.simCommonSel.INPF
w -2216 163 100 0 n#11 genericcad.genericcad#48.VAL -2592 160 -1840 160 -1840 272 -992 272 -992 416 -752 416 esels.simCommonSel.INPC
w -1248 339 100 0 n#12 genericcad.genericcad#23.VAL -1472 336 -1024 336 -1024 448 -752 448 esels.simCommonSel.INPB
w -1504 -397 100 0 n#13 egenSub.simStop.VALD -1584 -400 -1424 -400 -1424 -688 -1168 -688 estringouts.p4FollowS.DOL
w -1476 -939 100 0 n#14 egenSub.simStop.FLNK -1584 -944 -1368 -944 -1368 -720 -1168 -720 estringouts.p4FollowS.SLNK
w -888 -699 100 0 n#15 estringouts.p4FollowS.FLNK -912 -704 -864 -704 -864 -656 -1352 -656 -1352 -560 -1168 -560 estringouts.p3FollowS.SLNK
w -888 -541 100 0 n#16 estringouts.p3FollowS.FLNK -912 -544 -864 -544 -864 -496 -1280 -496 -1280 -400 -1168 -400 estringouts.p2FollowS.SLNK
w -888 -381 100 0 n#17 estringouts.p2FollowS.FLNK -912 -384 -864 -384 -864 -336 -1248 -336 -1248 -240 -1168 -240 estringouts.p1FollowS.SLNK
s -576 1296 100 0 $Id: gsaoiSystem.sch,v 1.2 2010/06/15 14:09:58 cjm Exp $
s -592 -896 100 0 Copyright
s -592 -928 100 0 Observatory
s -592 -960 100 0 Sciences Ltd.
[cell use]
use bc200tr -3168 -1176 -100 0 frame
xform 0 -1488 128
use gsaoiSimStandard -984 -993 100 0 gsaoiSimStandard#116
xform 0 -872 -872
use hwin -1336 -849 100 0 hwin#114
xform 0 -1240 -808
p -1333 -816 100 0 -1 val(in):1
use esels -784 32 100 0 simCommonSel
xform 0 -608 288
p -975 -107 100 0 0 PV:$(top)$(subsys)
p -656 318 100 0 -1 SELM:High Signal
use outhier -312 360 100 0 FLNK
xform 0 -320 400
use outhier -304 256 160 0 VAL
xform 0 -320 304
use genericcad -2472 600 100 0 genericcad#96
xform 0 -2344 696
p -2416 862 100 0 0 seta:prefix $(top)$(subsys)
p -2480 878 100 0 -1 setb:command init
p -2480 846 100 0 -1 setc:delay 5.0
p -2480 814 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2480 782 100 0 -1 sete:outa 0.0
use genericcad -2856 104 100 0 genericcad#48
xform 0 -2728 200
p -2800 366 100 0 0 seta:prefix $(top)$(subsys)
p -2864 382 100 0 -1 setb:command reboot
p -2864 350 100 0 -1 setc:delay 0.3
p -2864 318 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2864 286 100 0 -1 sete:outa 0.0
use genericcad -1736 280 100 0 genericcad#23
xform 0 -1608 376
p -1680 542 100 0 0 seta:prefix $(top)$(subsys)
p -1680 510 100 0 -1 setb:command test
p -1680 478 100 0 -1 setc:delay 3.0
p -1680 446 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -1680 414 100 0 0 sete:outa 0.0
use genericcad -1280 -128 100 0 genericcad#33
xform 0 -1152 -32
p -1304 -168 100 0 0 seta:prefix $(top)$(subsys)
p -1304 118 100 0 -1 setb:command debug
p -1304 86 100 0 -1 setc:delay 0.1
p -1304 54 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -1304 -200 100 0 0 sete:outa 0.0
use egenSub -1848 -1000 100 0 simStop
xform 0 -1728 -576
p -2095 -1227 100 0 0 FTVA:STRING
p -2095 -1227 100 0 0 FTVB:STRING
p -2095 -1259 100 0 0 FTVC:STRING
p -2095 -1291 100 0 0 FTVD:STRING
p -1792 -786 100 0 0 INAM:tcsSimNullInit
p -2095 -1131 100 0 0 PV:$(top)$(subsys)
p -1808 -786 100 0 -1 SNAM:tcs$(snam)Stop
p -1568 -194 100 0 -1 def(OUTA):$(p1)followS.VAL
p -1568 -274 100 0 -1 def(OUTB):$(p2)followS.VAL
p -1568 -338 100 0 -1 def(OUTC):$(p3)followS.VAL
p -1568 -418 100 0 -1 def(OUTD):$(p4)followS.VAL
p -1584 -230 75 0 -1 pproc(OUTA):PP
p -1584 -294 75 0 -1 pproc(OUTB):PP
p -1584 -358 75 0 -1 pproc(OUTC):PP
use estringouts -1166 -316 100 0 p1FollowS
xform 0 -1040 -240
p -887 -289 100 0 -1 def(OUT):$(p1)followS.VAL
use estringouts -1166 -636 100 0 p3FollowS
xform 0 -1040 -560
p -887 -609 100 0 -1 def(OUT):$(p3)followS.VAL
use estringouts -1166 -476 100 0 p2FollowS
xform 0 -1040 -400
p -887 -449 100 0 -1 def(OUT):$(p2)followS.VAL
use estringouts -1166 -796 100 0 p4FollowS
xform 0 -1040 -720
p -887 -769 100 0 -1 def(OUT):$(p4)followS.VAL
[comments]
