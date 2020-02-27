[schematic2]
uniq 80
[tools]
[detail]
w 1896 619 100 0 n#79 elongouts.start.FLNK 2048 800 2112 800 2112 608 1728 608 1728 480 1792 480 tcsSubCadWait.tcsSubCadWait#68.START
w 1424 475 100 0 n#78 eaos.m1SurfaceTarget.FLNK 1264 464 1632 464 1632 768 1792 768 elongouts.start.SLNK
w 272 1323 100 0 n#77 ecad8.ecad8#23.VALD 192 1312 400 1312 400 624 576 624 ecalcs.Calc.INPB
w 560 939 100 0 n#76 ecad8.ecad8#23.VALA 192 1504 432 1504 432 928 736 928 eaos.m1BulkTarget.DOL
w 832 1051 100 0 n#75 elongouts.busy.FLNK 992 1216 1072 1216 1072 1040 640 1040 640 896 736 896 eaos.m1BulkTarget.SLNK
w 832 1323 100 0 n#74 estringouts.null.FLNK 992 1440 1072 1440 1072 1312 640 1312 640 1184 736 1184 elongouts.busy.SLNK
w 552 1435 100 0 n#73 ecad8.ecad8#23.STLK 192 832 416 832 416 1424 736 1424 estringouts.null.SLNK
w 680 1227 100 0 n#72 hwin.hwin#71.in 672 1216 736 1216 elongouts.busy.DOL
w 944 434 100 0 n#67 ecalcs.Calc.FLNK 864 496 928 496 928 432 1008 432 eaos.m1SurfaceTarget.SLNK
w 912 466 100 0 n#66 ecalcs.Calc.VAL 864 464 1008 464 eaos.m1SurfaceTarget.DOL
w 736 738 100 0 n#63 eaos.m1BulkTarget.VAL 992 896 1056 896 1056 736 464 736 464 656 576 656 ecalcs.Calc.INPA
w 728 754 100 0 n#62 eaos.m1BulkTarget.FLNK 992 928 1072 928 1072 752 432 752 432 272 576 272 ecalcs.Calc.SLNK
w 1720 802 100 0 n#54 hwin.hwin#52.in 1696 800 1792 800 elongouts.start.DOL
w 1176 1698 100 0 n#46 ecad8.ecad8#23.VAL 192 1696 2208 1696 outhier.VAL.p
w 1446 1604 100 0 n#9 ecad8.ecad8#23.MESS 192 1664 720 1664 720 1600 2208 1600 outhier.MESS.p
w -306 1668 100 0 n#8 inhier.ICID.P -528 1600 -448 1600 -448 1664 -128 1664 ecad8.ecad8#23.ICID
w -346 1698 100 0 n#7 inhier.DIR.P -528 1696 -128 1696 ecad8.ecad8#23.DIR
s 1792 128 100 0 acknowledgement as well as command rejection.
s 1792 160 100 0 This symbol handles timeouts on both command
s 544 1952 200 0 Trigger the PCS bulktemp command
s 1808 2000 100 0 $Id: tcsCadM1Btempset.sch,v 1.1.1.1 1998/11/08 00:20:29 epics Exp $
s 1808 -336 100 0 20 October 1996
s 2064 -192 100 0 Gemini Telescope Control System
[cell use]
use hwin 480 1175 100 0 hwin#71
xform 0 576 1216
p 483 1208 100 0 -1 val(in):$(CAR_BUSY)
use elongouts 760 1096 100 0 busy
xform 0 864 1184
p 784 1278 100 0 -1 DESC:Busy state
p 576 1102 100 0 0 OMSL:closed_loop
p 1072 1150 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
p 976 1088 100 1024 1 name:$(tcs)$(cad)$(I)
p 992 1152 75 768 -1 pproc(OUT):PP
use estringouts 736 1351 100 0 null
xform 0 864 1424
p 752 1504 100 0 -1 DESC:Supply an empty string
p 672 1390 100 0 0 VAL:
p 1088 1408 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
p 848 1344 100 1024 0 name:$(tcs)$(cad)$(I)
use tcsSubCadWait 1792 247 100 0 tcsSubCadWait#68
xform 0 1928 392
p 1856 560 100 0 -1 seta:top $(tcs)$(cad):
p 1856 528 100 0 -1 setb:index 0
p 2112 560 100 0 -1 setc:timeout 3.0
p 2112 528 100 0 -1 setd:text PCS
use ecalcs 600 184 100 0 Calc
xform 0 720 448
p 672 382 100 0 1 CALC:A+B
p 512 702 100 0 -1 DESC:Generate surface temperature demand
p 816 176 100 1024 1 name:$(tcs)$(cad)$(I)
use eaos 1032 344 100 0 m1SurfaceTarget
xform 0 1136 432
p 1008 542 100 0 -1 DESC:Surface temperature demand
p 1088 382 100 0 1 EGU:deg C
p 752 414 100 0 0 OMSL:closed_loop
p 752 286 100 0 0 PREC:2
p 1360 398 100 0 -1 def(OUT):$(sad)m1SurfaceTarget
p 1120 304 100 1024 1 name:$(tcs)$(I)
p 1296 400 75 768 -1 palrm(OUT):MS
p 1264 400 75 768 -1 pproc(OUT):PP
use eaos 760 808 100 0 m1BulkTarget
xform 0 864 896
p 736 1006 100 0 -1 DESC:Bulk temperature demand
p 816 846 100 0 1 EGU:deg C
p 480 878 100 0 0 OMSL:closed_loop
p 480 750 100 0 0 PREC:2
p 1088 862 100 0 -1 def(OUT):$(sad)m1BulkTarget
p 1024 800 100 1024 1 name:$(tcs)$(I)
p 1024 864 75 768 -1 palrm(OUT):MS
p 992 864 75 768 -1 pproc(OUT):PP
use hwin 1528 760 100 0 hwin#52
xform 0 1600 800
p 1507 792 100 0 -1 val(in):$(CAD_START)
use elongouts 1816 680 100 0 start
xform 0 1920 768
p 1840 862 100 0 -1 DESC:Start Directive
p 1632 686 100 0 0 OMSL:closed_loop
p 2128 734 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 2032 672 100 1024 1 name:$(tcs)$(cad)$(I)
p 2048 736 75 768 -1 pproc(OUT):PP
use outhier 2200 1560 100 0 MESS
xform 0 2192 1600
use outhier 2200 1656 100 0 VAL
xform 0 2192 1696
use ecad8 -104 744 100 0 ecad8#23
xform 0 32 1248
p -176 1790 100 0 -1 DESC:Triggers a subsystem CAD on START only
p -16 1494 100 0 0 FTVA:STRING
p -16 1438 100 0 0 FTVB:STRING
p 64 1038 100 0 0 FTVH:STRING
p -48 926 100 0 -1 SNAM:$(snam)
p 256 1470 100 0 -1 def(OUTA):$(outa)
p 256 1406 100 0 -1 def(OUTB):$(outb)
p 256 1342 100 0 -1 def(OUTC):$(outc)
p 256 1278 100 0 -1 def(OUTD):$(outd)
p 256 1214 100 0 -1 def(OUTE):$(oute)
p 256 1150 100 0 -1 def(OUTF):$(outf)
p 256 1086 100 0 0 def(OUTG):0.0
p 272 1022 100 0 0 def(OUTH):0.0
p -64 686 100 0 1 name:$(tcs)$(cad)
p 192 1472 75 768 -1 pproc(OUTA):NPP
p 192 1408 75 768 -1 pproc(OUTB):NPP
p 192 1024 75 768 -1 pproc(OUTH):NPP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -520 1560 100 0 ICID
xform 0 -528 1600
use inhier -520 1656 100 0 DIR
xform 0 -528 1696
[comments]
