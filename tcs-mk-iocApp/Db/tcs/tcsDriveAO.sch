[schematic2]
uniq 19
[tools]
[detail]
w 5280 1667 100 0 n#1 egenSub.driveAOS.FLNK 5024 1664 5536 1664 outhier.FLNK.p
w 4040 1363 100 0 n#2 ebos.aoRawDatum.VAL 4000 1360 4080 1360 4080 1328 4160 1328 ebis.aoProbeDatumed.INP
w 4024 1395 100 0 n#3 ebos.aoRawDatum.FLNK 4000 1392 4048 1392 4048 1296 4160 1296 ebis.aoProbeDatumed.SLNK
w 4480 1315 100 0 n#4 ebis.aoProbeDatumed.FLNK 4416 1312 4544 1312 4544 1152 4080 1152 4080 1040 4160 1040 eais.aoXpos.SLNK
w 4360 2451 100 0 n#5 ewaves.aoImageDistort.VAL 4336 2448 4384 2448 4384 2368 4736 2368 egenSub.driveAOS.INPA
w 3888 2515 100 0 n#6 inhier.c#1533.P 3696 2512 4080 2512 ewaves.aoImageDistort.INP
w 4304 1795 100 0 n#7 eais.aoYoffset.VAL 4160 1792 4448 1792 4448 2176 4736 2176 egenSub.driveAOS.INPD
w 4288 2019 100 0 n#8 eais.aoXoffset.VAL 4160 2016 4416 2016 4416 2240 4736 2240 egenSub.driveAOS.INPC
w 4272 2243 100 0 n#9 eais.aoZoffset.VAL 4160 2240 4384 2240 4384 2304 4736 2304 egenSub.driveAOS.INPB
w 5984 1443 100 0 n#10 egenSub.calcNaRange.OUTA 5728 1440 6240 1440 outhier.c#1529.p
w 5072 1411 100 0 n#11 eaos.sodium.OUT 4992 1408 5152 1408 5152 1744 5536 1744 outhier.c#1527.p
w 5040 1475 100 0 n#12 eaos.sodium.FLNK 4992 1472 5088 1472 5088 768 junction
w 4752 595 100 0 n#12 eais.aoZpos.FLNK 4416 592 5088 592 5088 768 5440 768 egenSub.calcNaRange.SLNK
w 5216 1443 100 0 n#13 eaos.sodium.VAL 4992 1440 5440 1440 egenSub.calcNaRange.INPA
w 4504 1699 100 0 n#14 inhier.SLNK.P 4272 1696 4736 1696 egenSub.driveAOS.SLNK
w 4472 835 100 0 n#15 eais.aoYpos.FLNK 4416 832 4528 832 4528 720 4080 720 4080 576 4160 576 eais.aoZpos.SLNK
w 4472 1059 100 0 n#16 eais.aoXpos.FLNK 4416 1056 4528 1056 4528 944 4080 944 4080 816 4160 816 eais.aoYpos.SLNK
w 5192 2403 100 0 n#17 egenSub.driveAOS.VALA 5024 2400 5360 2400 outhier.c#1411.p
s 6208 416 100 0 Drive Altair probe
s 5984 352 100 0 Sciences Ltd.
s 5984 384 100 0 Observatory
s 5984 416 100 0 Copyright
s 5968 2608 100 0 $Id: tcsDriveAO.sch,v 1.12 2014/02/08 02:10:21 gemvx Exp $
[cell use]
use elongins 6304 471 100 0 aoLgsoi
xform 0 6432 544
p 6336 624 100 0 -1 DESC:LGS OI mode
p 6048 542 100 0 0 EGU:units
p 5920 576 100 0 -1 def(INP):$(ao)lgsttSource.VALB
p 6416 464 100 1024 0 name:$(tcs)$(I)
p 6272 576 75 1280 -1 pproc(INP):CPP
use bc200tr 3392 136 -100 0 frame
xform 0 5072 1440
use outhier 6208 1399 100 0 c#1529
xform 0 6224 1440
use outhier 5504 1703 100 0 c#1527
xform 0 5520 1744
use outhier 5352 2360 100 0 c#1411
xform 0 5344 2400
use outhier 5504 1623 100 0 FLNK
xform 0 5520 1664
use estringins 5568 327 100 0 aoLgsIrisPosn
xform 0 5696 400
p 5568 480 100 0 -1 DESC:LGS Iris position
p 5568 494 100 0 0 VAL:
p 5504 -36 100 0 0 def(INP):$(ao)cc:lgsirisAssembly.VALA
p 5680 320 100 1024 0 name:$(tcs)$(I)
p 5536 432 75 1280 -1 pproc(INP):CPP
use estringins 5152 327 100 0 aoNgsNDfilt
xform 0 5280 400
p 5152 480 100 0 -1 DESC:NGS ND Filter position
p 5152 494 100 0 0 VAL:
p 5088 -36 100 0 0 def(INP):$(ao)cc:ngsNDfiltAssembly.VALA
p 5264 320 100 1024 0 name:$(tcs)$(I)
p 5120 432 75 1280 -1 pproc(INP):CPP
use estringins 4672 327 100 0 aoLgsNDfilt
xform 0 4800 400
p 4672 480 100 0 -1 DESC:LGS ND Filter position
p 4672 494 100 0 0 VAL:
p 4608 -36 100 0 0 def(INP):$(ao)cc:lgsNDfiltAssembly.VALA
p 4784 320 100 1024 0 name:$(tcs)$(I)
p 4640 432 75 1280 -1 pproc(INP):CPP
use elongins 6304 703 100 0 aoLgsp1
xform 0 6432 776
p 6336 856 100 0 -1 DESC:LGS P1 mode
p 6048 774 100 0 0 EGU:units
p 5920 808 100 0 -1 def(INP):$(ao)lgsttSource.VALA
p 6416 696 100 1024 0 name:$(tcs)$(I)
p 6272 808 75 1280 -1 pproc(INP):CPP
use elongins 5984 2311 100 0 controlID
xform 0 6112 2384
p 5952 2464 100 0 -1 DESC:ID of latest control matrix
p 5728 2382 100 0 0 EGU:units
p 5728 2158 100 0 0 MDEL:0
p 5648 2432 100 0 -1 def(INP):$(ao)prepareCm.VALA
p 5984 2416 75 1280 -1 palrm(INP):MS
p 5952 2416 75 1280 -1 pproc(INP):CPP
use elongins 6304 1191 100 0 aoLgszoomSfoLoop
xform 0 6432 1264
p 6336 1344 100 0 -1 DESC:SFO Loop state
p 6048 1262 100 0 0 EGU:units
p 5920 1296 100 0 -1 def(INP):$(ao)cc:lgszoomSfoLoop
p 6416 1184 100 1024 0 name:$(tcs)$(I)
p 6272 1296 75 1280 -1 pproc(INP):CPP
use elongins 6304 935 100 0 aoStrapCorrCtl
xform 0 6432 1008
p 6336 1088 100 0 -1 DESC:Strap Correction
p 6048 1006 100 0 0 EGU:units
p 5920 1040 100 0 -1 def(INP):$(ao)wfcs:strapCorrCtl.VALA
p 6416 928 100 1024 0 name:$(tcs)$(I)
p 6272 1040 75 1280 -1 pproc(INP):CPP
use ebos 3744 1271 100 0 aoRawDatum
xform 0 3872 1360
p 3728 1456 100 0 -1 DESC:Datum state of AO probe
p 3424 1310 100 0 0 OMSL:closed_loop
p 3424 1214 100 0 0 ONAM:True
p 3808 1232 100 0 1 SCAN:1 second
p 3424 1246 100 0 0 ZNAM:False
p 3520 1392 100 0 -1 def(DOL):$(ao)datumS
p 3744 1328 75 1280 -1 palrm(SDIS):NMS
p 3712 1392 75 1280 -1 pproc(DOL):CA
use ebis 5984 1879 100 0 exitShutterOpen
xform 0 6112 1952
p 5968 2016 100 0 -1 DESC:Exit shutter status
p 5760 1790 100 0 0 ONAM:OPEN
p 5760 1822 100 0 0 ZNAM:CLOSED
p 5600 1984 100 0 -1 def(INP):$(ao)exitShutterOpen
p 5984 1984 75 1280 -1 palrm(INP):MS
p 5952 1984 75 1280 -1 pproc(INP):CPP
use ebis 5984 2103 100 0 entShutterOpen
xform 0 6112 2176
p 5968 2240 100 0 -1 DESC:Entrance shutter status
p 5760 2014 100 0 0 ONAM:OPEN
p 5760 2046 100 0 0 ZNAM:CLOSED
p 5616 2208 100 0 -1 def(INP):$(ao)entShutterOpen
p 5984 2208 75 1280 -1 palrm(INP):MS
p 5952 2208 75 1280 -1 pproc(INP):CPP
use ebis 4160 1223 100 0 aoProbeDatumed
xform 0 4288 1296
p 4144 1376 100 0 -1 DESC:Datum state of AO probe
p 3936 1134 100 0 0 ONAM:DATUMED
p 4336 1184 100 0 0 SCAN:Passive
p 3936 1166 100 0 0 ZNAM:NOT DATUMED
p 3920 1328 100 0 0 def(INP):0.0000000000000000e+00
p 4160 1328 75 1280 -1 palrm(INP):MS
p 4128 1328 75 1280 -1 pproc(INP):NPP
use ebis 5984 1639 100 0 aoLoopRunning
xform 0 6112 1712
p 5968 1776 100 0 -1 DESC:WFS loop status
p 5760 1550 100 0 0 ONAM:On
p 5760 1582 100 0 0 ZNAM:Off
p 5648 1776 100 0 -1 def(INP):$(ao)wfcs:loopRunning
p 6096 1632 100 1024 0 name:$(tcs)$(I)
p 5984 1744 75 1280 -1 palrm(INP):MS
p 5952 1744 75 1280 -1 pproc(INP):CPP
use ewaves 4080 2391 100 0 aoImageDistort
xform 0 4208 2480
p 4016 2560 100 0 -1 DESC:Altair optical distortion coeffs
p 4208 2366 100 0 0 FTVL:DOUBLE
p 4208 2398 100 0 0 NELM:6
p 3984 2334 100 0 0 PREC:6
p 3744 2528 100 0 -1 def(INP):$(ao)imageDistort.VALJ
p 4080 2512 75 1280 -1 palrm(INP):NMS
p 4048 2512 75 1280 -1 pproc(INP):CA
use eais 3904 1735 100 0 aoYoffset
xform 0 4032 1808
p 3888 1888 100 0 -1 DESC:Y pointing origin
p 3648 1550 100 0 0 EGU:mm
p 3648 1646 100 0 0 PREC:2
use eais 3904 1959 100 0 aoXoffset
xform 0 4032 2032
p 3888 2112 100 0 -1 DESC:X pointing origin
p 3648 1774 100 0 0 EGU:mm
p 3648 1870 100 0 0 PREC:2
use eais 3904 2183 100 0 aoZoffset
xform 0 4032 2256
p 3888 2336 100 0 -1 DESC:Altair focal plane shift
p 3648 1998 100 0 0 EGU:mm
p 3648 2094 100 0 0 PREC:2
use eais 4160 503 100 0 aoZpos
xform 0 4288 576
p 3904 126 100 0 0 ADEL:0.0005
p 4176 656 100 0 -1 DESC:AO probe Z position
p 3904 318 100 0 0 EGU:mm
p 3904 94 100 0 0 MDEL:0.0005
p 3904 414 100 0 0 PREC:3
p 3856 608 100 0 -1 def(INP):$(ao)wfsZPosition
p 4160 608 75 1280 -1 palrm(INP):MS
p 4128 608 75 1280 -1 pproc(INP):CA
use eais 4160 743 100 0 aoYpos
xform 0 4288 816
p 3904 366 100 0 0 ADEL:0.0005
p 4176 896 100 0 -1 DESC:AO probe Y position
p 3904 558 100 0 0 EGU:mm
p 3904 334 100 0 0 MDEL:0.0005
p 3904 654 100 0 0 PREC:3
p 3856 848 100 0 -1 def(INP):$(ao)wfsYPosition
p 4160 848 75 1280 -1 palrm(INP):MS
p 4128 848 75 1280 -1 pproc(INP):CA
use eais 4160 967 100 0 aoXpos
xform 0 4288 1040
p 3904 590 100 0 0 ADEL:0.0005
p 4176 1120 100 0 -1 DESC:AO probe X position
p 3904 782 100 0 0 EGU:mm
p 3904 558 100 0 0 MDEL:0.0005
p 3904 878 100 0 0 PREC:3
p 3856 1072 100 0 -1 def(INP):$(ao)wfsXPosition
p 4160 1072 75 1280 -1 palrm(INP):MS
p 4128 1072 75 1280 -1 pproc(INP):CA
use inhier 4256 1655 100 0 SLNK
xform 0 4272 1696
use inhier 3680 2471 100 0 c#1533
xform 0 3696 2512
use egenSub 5440 679 100 0 calcNaRange
xform 0 5584 1104
p 5440 1536 100 0 -1 DESC:Compute sodium layer range
p 5152 1230 100 0 0 PREC:14
p 5728 688 100 0 1 SNAM:tcsCalcNaRange
p 5200 1392 100 0 -1 def(INPB):$(tcs)demandEl
p 5200 1328 100 0 -1 def(INPC):$(tcs)ak:height
p 5936 1456 100 0 -1 def(OUTA):$(sad)sodiumRange
p 5728 1450 75 0 -1 pproc(OUTA):CA
use egenSub 4760 1608 100 0 driveAOS
xform 0 4880 2032
p 4768 2448 100 0 -1 DESC:Drive Altair probe
p 4448 2174 100 0 0 DISV:1
p 4513 1285 100 0 0 FTE:DOUBLE
p 4816 2384 100 0 1 NOA:6
p 5392 2414 100 0 -1 NOVA:6
p 4448 2158 100 0 0 PREC:14
p 4816 1838 100 0 -1 SNAM:tcsDriveAOS
p 4400 2416 100 0 0 def(INPA):0.000000000000000e+00
p 4448 2110 100 0 0 def(INPE):0.000000000000000e+00
p 5152 2414 100 0 -1 def(OUTA):$(ao)followA.J
p 4720 2378 75 0 -1 palrm(INPA):MS
p 4688 2378 75 0 -1 pproc(INPA):PP
use eaos 4736 1351 100 0 sodium
xform 0 4864 1440
p 4768 1536 100 0 -1 DESC:Sodium altitude
p 4480 1198 100 0 0 DRVH:200
p 4480 1166 100 0 0 DRVL:50
p 4816 1392 100 0 1 EGU:km
p 4480 1294 100 0 0 PREC:1
p 5200 1776 100 0 -1 def(OUT):$(sad)sodiumAltitude
p 4848 1344 100 1024 0 name:$(tcs)$(I)
p 4992 1408 75 768 -1 pproc(OUT):CA
[comments]
