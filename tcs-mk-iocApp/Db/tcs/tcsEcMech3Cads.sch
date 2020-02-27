[schematic2]
uniq 90
[tools]
[detail]
w 1600 -46 100 0 n#89 elongouts.start3.FLNK 1360 -48 1888 -48 1888 80 2080 80 tcsSubCadWait.tcsSubCadWait#84.START
w 1480 354 100 0 n#87 efanouts.Fan2.LNK2 1920 592 2016 592 2016 352 992 352 992 208 1104 208 elongouts.mark3.SLNK
w 1976 626 100 0 n#86 efanouts.Fan2.LNK1 1920 624 2080 624 tcsSubCadWait.tcsSubCadWait#79.START
w 1496 546 100 0 n#85 elongouts.start2.FLNK 1360 544 1680 544 efanouts.Fan2.SLNK
w 1480 946 100 0 n#78 efanouts.Fan1.LNK2 1920 1184 2016 1184 2016 944 992 944 992 784 1088 784 elongouts.mark2.SLNK
w 1976 1218 100 0 n#77 efanouts.Fan1.LNK1 1920 1216 2080 1216 tcsSubCadWait.tcsSubCadWait#63.START
w 1488 1138 100 0 n#76 elongouts.start1.FLNK 1344 1136 1680 1136 efanouts.Fan1.SLNK
w -14 1200 100 0 n#75 ecad8.ecad8#23.STLK -176 912 -16 912 -16 1440 208 1440 estringouts.null.SLNK
w -568 1746 100 0 n#74 inhier.ICID.P -640 1680 -592 1680 -592 1744 -496 1744 ecad8.ecad8#23.ICID
w -592 1778 100 0 n#73 inhier.DIR.P -640 1776 -496 1776 ecad8.ecad8#23.DIR
w 672 1234 100 0 n#71 elongouts.busy.FLNK 464 1232 928 1232 928 1376 1088 1376 elongouts.mark1.SLNK
w 336 1330 100 0 n#70 estringouts.null.FLNK 464 1456 544 1456 544 1328 176 1328 176 1200 208 1200 elongouts.busy.SLNK
w 184 1234 100 0 n#68 hwin.hwin#66.in 208 1232 208 1232 elongouts.busy.DOL
w 1184 82 100 0 n#62 elongouts.mark3.FLNK 1360 240 1424 240 1424 80 992 80 992 -80 1104 -80 elongouts.start3.SLNK
w 1184 642 100 0 n#60 elongouts.mark2.FLNK 1344 816 1424 816 1424 640 992 640 992 512 1104 512 elongouts.start2.SLNK
w 1184 1250 100 0 n#58 elongouts.mark1.FLNK 1344 1408 1424 1408 1424 1248 992 1248 992 1104 1088 1104 elongouts.start1.SLNK
w 930 864 100 0 n#56 junction 928 544 928 1136 1088 1136 elongouts.start1.DOL
w 930 272 100 0 n#56 junction 928 544 928 -48 1104 -48 elongouts.start3.DOL
w 952 548 100 0 n#56 hwin.hwin#54.in 848 544 1104 544 elongouts.start2.DOL
w 962 552 100 0 n#55 junction 960 816 960 240 1104 240 elongouts.mark3.DOL
w 962 1136 100 0 n#55 junction 960 816 960 1408 1088 1408 elongouts.mark1.DOL
w 944 820 100 0 n#55 hwin.hwin#53.in 848 816 1088 816 elongouts.mark2.DOL
w 808 1778 100 0 n#46 ecad8.ecad8#23.VAL -176 1776 1840 1776 outhier.VAL.p
w 1078 1684 100 0 n#9 ecad8.ecad8#23.MESS -176 1744 352 1744 352 1680 1840 1680 outhier.MESS.p
s 368 1888 200 0 Trigger 3 subsystem CADs that have no parameters
s 1808 -336 100 0 20 October 1996
s 2032 -192 100 0 Gemini Telescope Control System
s 1888 2000 100 0 $Id: tcsEcMech3Cads.sch,v 1.1.1.1 1998/11/08 00:20:35 epics Exp $
[cell use]
use tcsSubCadWait 2104 984 100 0 tcsSubCadWait#63
xform 0 2216 1128
p 2160 1326 100 0 -1 seta:top $(tcs)domeStop:
p 2160 1358 100 0 -1 setb:cad domeStop:
p 2160 1294 100 0 -1 setc:subcad stopDome
p 2160 1262 100 0 -1 setd:index 1
use tcsSubCadWait 2104 392 100 0 tcsSubCadWait#79
xform 0 2216 536
p 2144 734 100 0 -1 seta:top $(tcs)shtrsStop:
p 2144 782 100 0 -1 setv:cad shtrsStop:
p 2144 702 100 0 -1 setc:subcad stopShtrs
p 2144 670 100 0 -1 setd:index 1
use tcsSubCadWait 2104 -152 100 0 tcsSubCadWait#84
xform 0 2216 -8
p 2160 190 100 0 -1 seta:top $(tcs)vgatesStop:
p 2160 238 100 0 -1 setb:cad vgatesStop:
p 2160 158 100 0 -1 setc:subcad stopVgates
p 2160 126 100 0 -1 setd:index 1
use efanouts 1704 1000 100 0 Fan1
xform 0 1800 1152
p 1792 992 100 1024 0 name:$(top)$(cad)$(I)
use efanouts 1704 408 100 0 Fan2
xform 0 1800 560
p 1792 400 100 1024 0 name:$(top)$(cad)$(I)
use hwin 680 504 100 0 hwin#54
xform 0 752 544
p 659 536 100 0 -1 val(in):$(CAD_START)
use hwin 680 776 100 0 hwin#53
xform 0 752 816
p 659 808 100 0 -1 val(in):$(CAD_MARK)
use hwin 40 1192 100 0 hwin#66
xform 0 112 1232
p 19 1224 100 0 -1 val(in):$(CAR_BUSY)
use elongouts 1136 -176 100 0 start3
xform 0 1232 -80
p 1168 14 100 0 -1 DESC:Start directive
p 944 -162 100 0 0 OMSL:closed_loop
p 1424 -114 100 0 -1 def(OUT):$(subsys)$(subcad)Vgates.DIR
p 1216 -176 100 1024 0 name:$(top)$(cad)$(I)
p 1360 -112 75 768 -1 pproc(OUT):PP
use elongouts 1136 112 100 0 mark3
xform 0 1232 208
p 1152 318 100 0 -1 DESC:Mark directive
p 944 126 100 0 0 OMSL:closed_loop
p 1424 174 100 0 -1 def(OUT):$(subsys)$(subcad)Vgates.DIR
p 1216 112 100 1024 0 name:$(top)$(cad)$(I)
p 1360 176 75 768 -1 pproc(OUT):PP
use elongouts 1136 416 100 0 start2
xform 0 1232 512
p 1168 606 100 0 -1 DESC:Start directive
p 944 430 100 0 0 OMSL:closed_loop
p 1424 478 100 0 -1 def(OUT):$(subsys)$(subcad)Shtrs.DIR
p 1216 416 100 1024 0 name:$(top)$(cad)$(I)
p 1360 480 75 768 -1 pproc(OUT):PP
use elongouts 1120 688 100 0 mark2
xform 0 1216 784
p 1136 894 100 0 -1 DESC:Mark directive
p 928 702 100 0 0 OMSL:closed_loop
p 1408 750 100 0 -1 def(OUT):$(subsys)$(subcad)Shtrs.DIR
p 1200 688 100 1024 0 name:$(top)$(cad)$(I)
p 1344 752 75 768 -1 pproc(OUT):PP
use elongouts 1120 1008 100 0 start1
xform 0 1216 1104
p 1152 1198 100 0 -1 DESC:Start directive
p 928 1022 100 0 0 OMSL:closed_loop
p 1408 1070 100 0 -1 def(OUT):$(subsys)$(subcad)Dome.DIR
p 1200 1008 100 1024 0 name:$(top)$(cad)$(I)
p 1344 1072 75 768 -1 pproc(OUT):PP
use elongouts 1120 1280 100 0 mark1
xform 0 1216 1376
p 1136 1486 100 0 -1 DESC:Mark directive
p 928 1294 100 0 0 OMSL:closed_loop
p 1408 1342 100 0 -1 def(OUT):$(subsys)$(subcad)Dome.DIR
p 1200 1280 100 1024 0 name:$(top)$(cad)$(I)
p 1344 1344 75 768 -1 pproc(OUT):PP
use elongouts 240 1104 100 0 busy
xform 0 336 1200
p 272 1294 100 0 -1 DESC:Busy state
p 48 1118 100 0 0 OMSL:closed_loop
p 528 1166 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
p 320 1104 100 1024 0 name:$(top)$(cad)$(I)
p 464 1168 75 768 -1 pproc(OUT):PP
use estringouts 232 1368 100 0 null
xform 0 336 1440
p 144 1406 100 0 0 VAL:
p 320 1360 100 1024 0 name:$(top)$(cad)$(I)
p 224 1518 100 0 -1 DESC:Supply an empty string
p 544 1422 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
use outhier 1832 1640 100 0 MESS
xform 0 1824 1680
use outhier 1832 1736 100 0 VAL
xform 0 1824 1776
use ecad8 -472 824 100 0 ecad8#23
xform 0 -336 1328
p -400 1976 100 0 0 FTVA:LONG
p -400 1488 100 0 0 FTVB:LONG
p -400 1456 100 0 0 FTVC:LONG
p -416 1006 100 0 -1 SNAM:$(snam)
p -112 1550 100 0 0 def(OUTA):0.0
p -112 1486 100 0 0 def(OUTB):0.0
p -112 1422 100 0 0 def(OUTC):0.0
p -112 1358 100 0 -1 def(OUTD):$(outc)
p -112 1294 100 0 -1 def(OUTE):$(outd)
p -112 1230 100 0 -1 def(OUTF):$(oute)
p -112 1166 100 0 -1 def(OUTG):$(outf)
p -432 766 100 0 1 name:$(tcs)$(cad)
p -176 1552 75 768 -1 pproc(OUTA):NPP
p -176 1488 75 768 -1 pproc(OUTB):NPP
p -176 1424 75 768 -1 pproc(OUTC):NPP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -632 1640 100 0 ICID
xform 0 -640 1680
use inhier -632 1736 100 0 DIR
xform 0 -640 1776
[comments]
