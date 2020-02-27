[schematic2]
uniq 80
[tools]
[detail]
w 850 704 100 0 n#78 egenSub.setColl.OUTD 752 1008 848 1008 848 352 1056 352 eaos.ceOpticsSky.SLNK
w 882 880 100 0 n#77 egenSub.setColl.OUTC 752 1072 880 1072 880 640 1056 640 eaos.caOpticsSky.SLNK
w 1336 1202 100 0 n#74 eaos.caOptics.VAL 1312 1200 1408 1200 tcsArcsec2rad.tcsArcsec2rad#67.INP
w 1336 1234 100 0 n#73 eaos.caOptics.FLNK 1312 1232 1408 1232 tcsArcsec2rad.tcsArcsec2rad#67.SLNK
w 1720 1202 100 0 n#72 tcsArcsec2rad.tcsArcsec2rad#67.VAL 1648 1200 1840 1200 outhier.OPTCA.p
w 1728 930 100 0 n#71 tcsArcsec2rad.tcsArcsec2rad#68.VAL 1648 928 1856 928 outhier.OPTCE.p
w 1336 930 100 0 n#70 eaos.ceOptics.VAL 1312 928 1408 928 tcsArcsec2rad.tcsArcsec2rad#68.INP
w 1336 962 100 0 n#69 eaos.ceOptics.FLNK 1312 960 1408 960 tcsArcsec2rad.tcsArcsec2rad#68.SLNK
w 914 1056 100 0 n#62 egenSub.setColl.OUTB 752 1136 912 1136 912 928 1056 928 eaos.ceOptics.SLNK
w 880 1202 100 0 n#60 egenSub.setColl.OUTA 752 1200 1056 1200 eaos.caOptics.SLNK
w 2370 984 100 0 n#49 egenSub.getM1Data.OUTF 2256 1312 2368 1312 2368 608 2592 608 eaos.defnRotZ.SLNK
w 2402 1176 100 0 n#47 egenSub.getM1Data.OUTE 2256 1376 2400 1376 2400 928 2592 928 eaos.defnRotY.SLNK
w 2466 1352 100 0 n#46 egenSub.getM1Data.OUTD 2256 1440 2464 1440 2464 1216 2592 1216 eaos.defnRotX.SLNK
w 2402 1896 100 0 n#43 egenSub.getM1Data.OUTA 2256 1632 2400 1632 2400 2112 2592 2112 eaos.defnX.SLNK
w 2466 1704 100 0 n#42 egenSub.getM1Data.OUTB 2256 1568 2464 1568 2464 1792 2592 1792 eaos.defnY.SLNK
w 2400 1506 100 0 n#41 egenSub.getM1Data.OUTC 2256 1504 2592 1504 eaos.defnZ.SLNK
s 128 128 100 0 the M1 internal simulator. Do not change macro to be $(m1)
s 128 160 100 0 N.B. Input on link A is ONLY needed and available from
s 2576 2352 100 0 $Id: tcsOptics.sch,v 1.2 2001/03/12 15:54:10 cjm Exp $
s 2848 160 100 0 Gemini Telescope Control system
s 2896 96 100 0 Optics control system
[cell use]
use tcsOpticsSetModel 1952 1863 100 0 tcsOpticsSetModel#79
xform 0 2080 2080
use eaos 2616 840 100 0 defnRotY
xform 0 2720 928
p 2608 1022 100 0 -1 DESC:Current M1 Y rotation
p 2880 1022 100 0 -1 EGU:arcsec
p 2336 366 100 0 0 MDEL:0.0005
p 2336 782 100 0 0 PREC:3
p 2704 832 100 1024 0 name:$(top)$(I)
use eaos 2616 1128 100 0 defnRotX
xform 0 2720 1216
p 2608 1310 100 0 -1 DESC:Current M1 X rotation
p 2880 1310 100 0 -1 EGU:arcsec
p 2336 654 100 0 0 MDEL:0.0005
p 2336 1070 100 0 0 PREC:3
p 2704 1120 100 1024 0 name:$(top)$(I)
use eaos 2616 1416 100 0 defnZ
xform 0 2720 1504
p 2608 1598 100 0 -1 DESC:Current M1 Z offset
p 2864 1598 100 0 -1 EGU:mm
p 2336 942 100 0 0 MDEL:0.0005
p 2336 1358 100 0 0 PREC:3
p 2704 1408 100 1024 0 name:$(top)$(I)
use eaos 2616 1704 100 0 defnY
xform 0 2720 1792
p 2608 1886 100 0 -1 DESC:Current M1 Y offset
p 2864 1886 100 0 -1 EGU:mm
p 2336 1230 100 0 0 MDEL:0.0005
p 2336 1646 100 0 0 PREC:3
p 2704 1696 100 1024 0 name:$(top)$(I)
use eaos 2616 2024 100 0 defnX
xform 0 2720 2112
p 2608 2206 100 0 -1 DESC:Current M1 X offset
p 2864 2206 100 0 -1 EGU:mm
p 2336 1550 100 0 0 MDEL:0.0005
p 2336 1966 100 0 0 PREC:3
p 2704 2016 100 1024 0 name:$(top)$(I)
use eaos 2616 520 100 0 defnRotZ
xform 0 2720 608
p 2608 702 100 0 -1 DESC:Current M1 Z rotation
p 2880 702 100 0 -1 EGU:arcsec
p 2336 46 100 0 0 MDEL:0.0005
p 2336 462 100 0 0 PREC:3
p 2704 512 100 1024 0 name:$(top)$(I)
use eaos 1080 1112 100 0 caOptics
xform 0 1184 1200
p 1056 1326 100 0 -1 DESC:Horizontal collimation
p 1120 1278 100 0 1 EGU:arcsec
p 800 638 100 0 0 MDEL:0.0005
p 800 1054 100 0 0 PREC:3
p 1168 1104 100 1024 0 name:$(top)$(I)
use eaos 1080 840 100 0 ceOptics
xform 0 1184 928
p 1072 1054 100 0 -1 DESC:Vertical collimation
p 1120 1006 100 0 1 EGU:arcsec
p 800 366 100 0 0 MDEL:0.0005
p 800 782 100 0 0 PREC:3
p 1168 832 100 1024 0 name:$(top)$(I)
use eaos 1080 552 100 0 caOpticsSky
xform 0 1184 640
p 1056 766 100 0 -1 DESC:Horizontal collimation
p 1120 718 100 0 1 EGU:arcsec
p 800 78 100 0 0 MDEL:0.0005
p 800 494 100 0 0 PREC:3
p 1168 544 100 1024 0 name:$(top)$(I)
use eaos 1080 264 100 0 ceOpticsSky
xform 0 1184 352
p 1072 478 100 0 -1 DESC:Vertical collimation
p 1120 430 100 0 1 EGU:arcsec
p 800 -210 100 0 0 MDEL:0.0005
p 800 206 100 0 0 PREC:3
p 1168 256 100 1024 0 name:$(top)$(I)
use tcsArcsec2rad 1432 1112 100 0 tcsArcsec2rad#67
xform 0 1528 1192
p 1440 1278 100 0 -1 seta:top $(top)caOpt:
use tcsArcsec2rad 1432 840 100 0 tcsArcsec2rad#68
xform 0 1528 920
p 1440 1022 100 0 -1 seta:top $(top)ceOpt:
use outhier 1832 1160 100 0 OPTCA
xform 0 1824 1200
use outhier 1848 888 100 0 OPTCE
xform 0 1840 928
use egenSub 1992 872 100 0 getM1Data
xform 0 2112 1296
p 2048 1726 100 0 -1 DESC:Gets M1 data
p 2032 814 100 0 1 SCAN:1 second
p 2032 782 100 0 1 SNAM:tcsOpticsM1Offsets
p 1744 1630 100 0 -1 def(INPA):$(m1)defnX
p 1744 1566 100 0 -1 def(INPB):$(m1)defnY
p 1744 1502 100 0 -1 def(INPC):$(m1)defnZ
p 1712 1438 100 0 -1 def(INPD):$(m1)defnRotX
p 1712 1358 100 0 -1 def(INPE):$(m1)defnRotY
p 1728 1310 100 0 -1 def(INPF):$(m1)defnRotZ
p 2080 864 100 1024 0 name:$(top)$(I)
p 2256 1642 75 0 -1 pproc(OUTA):PP
p 2256 1578 75 0 -1 pproc(OUTB):PP
p 2256 1514 75 0 -1 pproc(OUTC):PP
p 2256 1450 75 0 -1 pproc(OUTD):PP
p 2256 1386 75 0 -1 pproc(OUTE):PP
p 2256 1322 75 0 -1 pproc(OUTF):PP
use egenSub 488 440 100 0 setColl
xform 0 608 864
p 448 1326 100 0 -1 DESC:Generate optics collimations
p 256 1262 100 0 1 NOA:6
p 176 1134 100 0 0 SCAN:.1 second
p 480 1278 100 0 1 SNAM:tcsOpticsSetColl
p 144 1230 100 0 -1 def(INPA):$(tcs)m1:position.VALH
p 752 1210 75 0 -1 pproc(OUTA):PP
p 752 1146 75 0 -1 pproc(OUTB):PP
p 752 1082 75 0 -1 pproc(OUTC):PP
p 752 1018 75 0 -1 pproc(OUTD):PP
use egenSubA 1272 1448 100 0 setZCoeffs
xform 0 1392 1872
p 1264 2318 100 0 -1 DESC:Store Zernike matrix coefficients
p 1025 1221 100 0 0 FTA:LONG
p 1025 837 100 0 0 NOB:11
p 1025 805 100 0 0 NOC:11
p 1025 773 100 0 0 NOD:11
p 1025 741 100 0 0 NOE:11
p 1025 709 100 0 0 NOF:11
p 1025 677 100 0 0 NOG:11
p 1025 645 100 0 0 NOH:11
p 1025 613 100 0 0 NOI:11
p 1025 581 100 0 0 NOJ:11
p 1025 581 100 0 0 NOK:11
p 1025 581 100 0 0 NOL:11
p 1025 581 100 0 0 NOM:11
p 1025 581 100 0 0 NON:11
p 1025 581 100 0 0 NOO:11
p 1025 581 100 0 0 NOP:11
p 1025 581 100 0 0 NOQ:11
p 1025 581 100 0 0 NOR:11
p 1025 581 100 0 0 NOS:11
p 1025 581 100 0 0 NOT:11
p 1296 2286 100 0 1 SNAM:tcsOpticsSetZCoeffs
p 1360 1440 100 1024 0 name:$(top)$(I)
use tcsOpticsM2ZTilt 408 1608 100 0 tcsOpticsM2ZTilt#32
xform 0 608 1760
use tcsOpticsM2XY 408 1992 100 0 tcsOpticsM2XY#31
xform 0 592 2080
use bc200tr 0 -120 -100 0 frame
xform 0 1680 1184
[comments]
