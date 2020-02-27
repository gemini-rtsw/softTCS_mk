[schematic2]
uniq 21
[tools]
[detail]
w 1488 1234 100 0 n#1 egenSub.position.FLNK 848 848 1216 848 1216 1232 1808 1232 1808 1184 1904 1184 efanouts.fan.SLNK
w 1544 1266 100 0 n#2 egenSub.position.VALG 848 1200 1184 1200 1184 1264 1952 1264 efanouts.fan.SELL
w 2400 898 100 0 n#3 efanouts.fan.LNK3 2144 1200 2240 1200 2240 896 2608 896 elongouts.zeroIdle.SLNK
w 2352 1234 100 0 n#4 efanouts.fan.LNK2 2144 1232 2608 1232 elongouts.figIdle.SLNK
w 2400 1554 100 0 n#5 efanouts.fan.LNK1 2144 1264 2240 1264 2240 1552 2608 1552 elongouts.defnIdle.SLNK
w 2912 866 100 0 n#6 elongouts.zeroIdle.OUT 2864 864 3008 864 outhier.ZEROIDLE.p
w 2912 1202 100 0 n#7 elongouts.figIdle.OUT 2864 1200 3008 1200 outhier.FIGIDLE.p
w 2912 1522 100 0 n#8 elongouts.defnIdle.OUT 2864 1520 3008 1520 outhier.DEFNIDLE.p
w 2536 930 100 0 n#9 hwin.hwin#28.in 2512 928 2608 928 elongouts.zeroIdle.DOL
w 2536 1266 100 0 n#10 hwin.hwin#27.in 2512 1264 2608 1264 elongouts.figIdle.DOL
w 2536 1586 100 0 n#11 hwin.hwin#23.in 2512 1584 2608 1584 elongouts.defnIdle.DOL
w 208 1346 100 0 n#12 inhier.CARZERO.P 96 1344 368 1344 368 1424 560 1424 egenSub.position.INPC
w 304 1490 100 0 n#13 inhier.CARFIG.P 96 1488 560 1488 egenSub.position.INPB
w 208 1634 100 0 n#14 inhier.CARDEFN.P 96 1632 368 1632 368 1552 560 1552 egenSub.position.INPA
w 978 888 100 0 n#15 egenSub.position.OUTF 848 1232 976 1232 976 496 1344 496 eaos.defnRotZ.SLNK
w 1010 1072 100 0 n#16 egenSub.position.OUTE 848 1296 1008 1296 1008 800 1328 800 eaos.defnRotY.SLNK
w 1042 1240 100 0 n#17 egenSub.position.OUTD 848 1360 1040 1360 1040 1072 1328 1072 eaos.defnRotX.SLNK
w 1182 1378 100 0 n#18 egenSub.position.OUTC 848 1424 1072 1424 1072 1376 1328 1376 eaos.defnZ.SLNK
w 1182 1682 100 0 n#19 egenSub.position.OUTB 848 1488 1072 1488 1072 1680 1328 1680 eaos.defnY.SLNK
w 1042 1786 100 0 n#20 egenSub.position.OUTA 848 1552 1040 1552 1040 1984 1328 1984 eaos.defnX.SLNK
s 2768 208 200 0 Gemini TCS
s 2688 160 100 0 Track M1 position realtive to LUT
s 2448 2416 100 0 $id$
s 736 2304 100 0 The work of this schematic is done by the subroutine
s 736 2272 100 0 attached to the genSub record. It keeps track of the total
s 576 2240 100 0 offset of M1 relative to the LUT and writes the results
s 576 2208 100 0 to EPICS records. These records are accessed by the TCS
s 208 2192 100 0 in order to compute the expected optical abberations.
[cell use]
use bc200tr -128 -56 -100 0 frame
xform 0 1552 1248
use outhier 3000 1480 100 0 DEFNIDLE
xform 0 2992 1520
use outhier 3000 1160 100 0 FIGIDLE
xform 0 2992 1200
use outhier 3000 824 100 0 ZEROIDLE
xform 0 2992 864
use hwin 2344 1544 100 0 hwin#23
xform 0 2416 1584
p 2323 1576 100 0 -1 val(in):$(CAR_IDLE)
use hwin 2344 1224 100 0 hwin#27
xform 0 2416 1264
p 2323 1256 100 0 -1 val(in):$(CAR_IDLE)
use hwin 2344 888 100 0 hwin#28
xform 0 2416 928
p 2323 920 100 0 -1 val(in):$(CAR_IDLE)
use elongouts 2632 1464 100 0 defnIdle
xform 0 2736 1552
p 2448 1470 100 0 0 OMSL:closed_loop
p 2592 1662 100 0 -1 DESC:Set definition CAR to IDLE
p 2720 1456 100 1024 0 name:$(m1)posn$(I)
p 2864 1520 75 768 -1 pproc(OUT):PP
use elongouts 2632 1144 100 0 figIdle
xform 0 2736 1232
p 2448 1150 100 0 0 OMSL:closed_loop
p 2592 1342 100 0 -1 DESC:Set figure CAR to IDLE
p 2720 1136 100 1024 0 name:$(m1)posn$(I)
p 2864 1200 75 768 -1 pproc(OUT):PP
use elongouts 2632 808 100 0 zeroIdle
xform 0 2736 896
p 2448 814 100 0 0 OMSL:closed_loop
p 2592 1006 100 0 -1 DESC:Set zerodemands CAR to IDLE
p 2720 800 100 1024 0 name:$(m1)posn$(I)
p 2864 864 75 768 -1 pproc(OUT):PP
use efanouts 1928 1048 100 0 fan
xform 0 2024 1200
p 1984 1374 100 0 -1 DESC:Trigger CAR records
p 1760 1166 100 0 0 SELM:Mask
p 2016 1040 100 1024 0 name:$(m1)posn$(I)
p 2176 1264 75 1280 -1 pproc(LNK1):PP
p 2176 1232 75 1280 -1 pproc(LNK2):PP
p 2176 1200 75 1280 -1 pproc(LNK3):PP
use inhier 104 1592 100 0 CARDEFN
xform 0 96 1632
use inhier 104 1448 100 0 CARFIG
xform 0 96 1488
use inhier 104 1304 100 0 CARZERO
xform 0 96 1344
use eaos 1352 1896 100 0 defnX
xform 0 1456 1984
p 1312 2094 100 0 -1 DESC:X position relative to LUT
p 1408 1950 100 0 1 EGU:mm
p 1440 1888 100 1024 0 name:$(m1)$(I)
p 1072 1838 100 0 0 PREC:3
p 1072 1422 100 0 0 MDEL:0.0005
use eaos 1352 1592 100 0 defnY
xform 0 1456 1680
p 1312 1790 100 0 -1 DESC:Y position relative to LUT
p 1408 1646 100 0 1 EGU:mm
p 1440 1584 100 1024 0 name:$(m1)$(I)
p 1072 1534 100 0 0 PREC:3
p 1072 1118 100 0 0 MDEL:0.0005
use eaos 1352 1288 100 0 defnZ
xform 0 1456 1376
p 1312 1486 100 0 -1 DESC:Z position relative to LUT
p 1408 1342 100 0 1 EGU:mm
p 1440 1280 100 1024 0 name:$(m1)$(I)
p 1072 1230 100 0 0 PREC:3
p 1072 814 100 0 0 MDEL:0.0005
use eaos 1352 984 100 0 defnRotX
xform 0 1456 1072
p 1312 1182 100 0 -1 DESC:X rotation relative to LUT
p 1376 1150 100 0 1 EGU:millirads
p 1440 976 100 1024 0 name:$(m1)$(I)
p 1072 926 100 0 0 PREC:6
p 1072 510 100 0 0 MDEL:0.0000005
use eaos 1352 712 100 0 defnRotY
xform 0 1456 800
p 1312 910 100 0 -1 DESC:Y rotation relative to LUT
p 1376 878 100 0 1 EGU:millirads
p 1440 704 100 1024 0 name:$(m1)$(I)
p 1072 654 100 0 0 PREC:6
p 1072 238 100 0 0 MDEL:0.0000005
use eaos 1368 408 100 0 defnRotZ
xform 0 1472 496
p 1328 606 100 0 -1 DESC:Z rotation relative to LUT
p 1392 574 100 0 1 EGU:millirads
p 1456 400 100 1024 0 name:$(m1)$(I)
p 1088 350 100 0 0 PREC:6
p 1088 -66 100 0 0 MDEL:0.0000005
use egenSub 584 792 100 0 position
xform 0 704 1216
p 528 1662 100 0 -1 DESC:Track M1 position relative to LUT
p 672 784 100 1024 0 name:$(m1)$(I)
p 592 686 100 0 1 SNAM:tcsM1Position
p 512 1562 75 0 -1 pproc(INPA):NPP
p 848 1562 75 0 -1 pproc(OUTA):PP
p 848 1498 75 0 -1 pproc(OUTB):PP
p 848 1434 75 0 -1 pproc(OUTC):PP
p 848 1370 75 0 -1 pproc(OUTD):PP
p 848 1306 75 0 -1 pproc(OUTE):PP
p 848 1242 75 0 -1 pproc(OUTF):PP
p 640 1582 100 0 -1 FTA:LONG
p 640 1518 100 0 -1 FTB:LONG
p 640 1454 100 0 -1 FTC:LONG
p 592 654 100 0 1 SCAN:10 second
p 688 1134 100 0 1 NOVH:6
p 656 1198 100 0 1 FTVG:LONG
[comments]
