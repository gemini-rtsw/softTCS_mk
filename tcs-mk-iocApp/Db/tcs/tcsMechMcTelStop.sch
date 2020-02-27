[schematic2]
uniq 17
[tools]
[detail]
w 1272 227 100 0 n#1 elongouts.busy.FLNK 1240 224 1304 224 1304 80 856 80 856 -48 984 -48 elongouts.start.SLNK
w 432 1155 100 0 n#2 ecad8.ecad8#23.VALA 288 1152 576 1152 576 1072 992 1072 estringouts.outa.DOL
w 432 483 100 0 n#3 ecad8.ecad8#23.STLK 288 480 576 480 576 1040 992 1040 estringouts.outa.SLNK
w 1272 451 100 0 n#4 estringouts.null.FLNK 1240 448 1304 448 1304 320 856 320 856 192 984 192 elongouts.busy.SLNK
w 1512 -13 100 0 n#5 elongouts.start.FLNK 1240 -16 1784 -16 1784 192 1880 192 tcsSubCadWait.tcsSubCadWait#55.START
w 936 227 100 0 n#6 hwin.hwin#58.in 888 224 984 224 elongouts.busy.DOL
w 936 -13 100 0 n#7 hwin.hwin#52.in 888 -16 984 -16 elongouts.start.DOL
w 1296 1347 100 0 n#8 ecad8.ecad8#23.VAL 288 1344 2304 1344 outhier.VAL.p
w 552 1315 100 0 n#9 ecad8.ecad8#23.MESS 288 1312 816 1312 816 1248 2304 1248 outhier.MESS.p
w -392 1251 100 0 n#10 inhier.ICID.P -432 1248 -352 1248 -352 1312 -32 1312 ecad8.ecad8#23.ICID
w -232 1347 100 0 n#11 inhier.DIR.P -432 1344 -32 1344 ecad8.ecad8#23.DIR
w 1258 1058 -100 0 n#12 estringouts.outa.FLNK 1248 1056 1320 1056 1320 920 872 920 872 856 1000 856 estringouts.outb.SLNK
w 1266 874 -100 0 n#13 estringouts.outb.FLNK 1256 872 1312 872 1312 736 864 736 864 672 1008 672 estringouts.outc.SLNK
w 1274 698 -100 0 n#14 estringouts.outc.FLNK 1264 688 1344 688 1344 576 856 576 856 432 984 432 estringouts.null.SLNK
w 298 1098 -100 0 n#15 ecad8.ecad8#23.VALB 288 1088 520 1088 520 888 1000 888 estringouts.outb.DOL
w 306 1026 -100 0 n#16 ecad8.ecad8#23.VALC 288 1024 472 1024 472 704 1008 704 estringouts.outc.DOL
s 1848 -88 100 0 well as command rejection.
s 1848 -56 100 0 This symbol handles timeouts on command acknowledgement as
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -336 100 0 20 October 1996
s 1808 2000 100 0 $Id: tcsMechMcTelStop.sch,v 1.1 2015/05/18 10:43:04 cjm Exp $
s 368 1856 200 0 Trigger the MCS stop CAD
[cell use]
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use estringouts 1008 360 100 0 null
xform 0 1112 432
p 1016 526 100 0 -1 DESC:Supply an empty string
p 920 398 100 0 0 VAL:
p 1384 414 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
p 1096 352 100 1024 0 name:$(tcs)$(cad)$(I)
use estringouts 992 967 100 0 outa
xform 0 1120 1040
p 1008 1120 100 0 -1 DESC:Output VALA from CAD
p 928 846 100 0 0 OMSL:closed_loop
p 928 1006 100 0 0 VAL:
p 1344 1024 100 0 -1 def(OUT):$(subsys)stop.A
p 1104 960 100 1024 0 name:$(tcs)$(cad)$(I)
p 1256 1032 75 768 -1 pproc(OUT):CA
use hwin 720 -56 100 0 hwin#52
xform 0 792 -16
p 699 -24 100 0 -1 val(in):$(CAD_START)
use hwin 720 184 100 0 hwin#58
xform 0 792 224
p 699 216 100 0 -1 val(in):$(CAR_BUSY)
use elongouts 1008 -136 100 0 start
xform 0 1112 -48
p 1032 46 100 0 -1 DESC:Start Directive
p 824 -130 100 0 0 OMSL:closed_loop
p 1320 -82 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1224 -144 100 1024 1 name:$(tcs)$(cad)$(I)
p 1240 -80 75 768 -1 pproc(OUT):PP
use elongouts 1008 104 100 0 busy
xform 0 1112 192
p 1032 286 100 0 -1 DESC:Busy state
p 824 110 100 0 0 OMSL:closed_loop
p 1320 158 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
p 1208 96 100 1024 1 name:$(tcs)$(cad)$(I)
p 1240 160 75 768 -1 pproc(OUT):PP
use tcsSubCadWait 1904 -40 100 0 tcsSubCadWait#55
xform 0 2016 104
p 1976 270 100 0 -1 seta:top $(tcs)$(cad):
p 1976 238 100 0 -1 setb:index 0
use outhier 2296 1304 100 0 VAL
xform 0 2288 1344
use outhier 2296 1208 100 0 MESS
xform 0 2288 1248
use ecad8 -8 392 100 0 ecad8#23
xform 0 128 896
p -80 1438 100 0 -1 DESC:Triggers a subsystem CAD on START only
p 80 1142 100 0 0 FTVA:STRING
p 80 1086 100 0 0 FTVB:STRING
p 160 686 100 0 0 FTVH:STRING
p 64 736 100 0 0 PREC:4
p 48 574 100 0 -1 SNAM:$(snam)
p 352 1118 100 0 0 def(OUTA):0.0
p 352 1054 100 0 0 def(OUTB):0.0
p 352 990 100 0 0 def(OUTC):0.0
p 352 926 100 0 0 def(OUTD):0.0
p 352 862 100 0 0 def(OUTE):0.0
p 352 798 100 0 0 def(OUTF):0.0
p 352 734 100 0 0 def(OUTG):0.0
p 368 670 100 0 0 def(OUTH):0.0
p 32 334 100 0 1 name:$(tcs)$(cad)
p 288 1120 75 768 -1 pproc(OUTA):NPP
p 288 1056 75 768 -1 pproc(OUTB):NPP
p 288 672 75 768 -1 pproc(OUTH):NPP
use inhier -424 1304 100 0 DIR
xform 0 -432 1344
use inhier -424 1208 100 0 ICID
xform 0 -432 1248
use estringouts 1000 783 100 0 outb
xform 0 1128 856
p 1016 936 100 0 -1 DESC:Output VALB from CAD
p 936 662 100 0 0 OMSL:closed_loop
p 936 822 100 0 0 VAL:
p 1352 840 100 0 -1 def(OUT):$(subsys)stop.B
p 1112 776 100 1024 0 name:$(tcs)$(cad)$(I)
p 1264 848 75 768 -1 pproc(OUT):CA
use estringouts 1008 599 100 0 outc
xform 0 1136 672
p 1024 752 100 0 -1 DESC:Output VALC from CAD
p 944 478 100 0 0 OMSL:closed_loop
p 944 638 100 0 0 VAL:
p 1360 656 100 0 -1 def(OUT):$(subsys)stop.C
p 1120 592 100 1024 0 name:$(tcs)$(cad)$(I)
p 1272 664 75 768 -1 pproc(OUT):CA
[comments]
