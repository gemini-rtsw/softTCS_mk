[schematic2]
uniq 29
[tools]
[detail]
w 616 1027 100 0 n#1 inhier.c#105.P 528 1024 704 1024 ewaves.gemsAo.INP
w 1024 963 100 0 n#2 ewaves.gemsAo.VAL 960 960 1088 960 1088 1408 1152 1408 egenSubC.averageAo.INPN
w 1008 1155 100 0 n#3 ewaves.aoAo.VAL 960 1152 1056 1152 1056 1536 1152 1536 egenSubC.averageAo.INPJ
w 992 1379 100 0 n#4 ewaves.oiwfsAo.VAL 960 1376 1024 1376 1024 1664 1152 1664 egenSubC.averageAo.INPF
w 520 1827 100 0 n#5 egenSub.calcM1Moving.VALA 480 1824 560 1824 560 1552 992 1552 992 1472 1152 1472 egenSubC.averageAo.INPL
w 656 1219 100 0 n#6 inhier.c#80.P 608 1216 704 1216 ewaves.aoAo.INP
w 1056 1731 100 0 n#7 ewaves.pwfs2Ao.VAL 960 1728 1152 1728 egenSubC.averageAo.INPD
w 656 1795 100 0 n#8 inhier.c#9.P 608 1792 704 1792 ewaves.pwfs2Ao.INP
w 984 1955 100 0 n#9 ewaves.pwfs1Ao.VAL 944 1952 1024 1952 1024 1792 1152 1792 egenSubC.averageAo.INPB
w 648 2019 100 0 n#10 inhier.c#11.P 608 2016 688 2016 ewaves.pwfs1Ao.INP
w 656 1443 100 0 n#11 inhier.c#74.P 608 1440 704 1440 ewaves.oiwfsAo.INP
w 928 67 100 0 n#12 egenSubC.displayAo.FLNK 896 64 960 64 960 96 1088 96 egenSubB.startFigure.SLNK
w 432 3 100 0 n#12 efanouts.dummyFan.FLNK 352 0 512 0 512 -128 960 -128 960 64 junction
w -8 -109 100 0 n#13 tcsM1CalcModel.tcsM1CalcModel#40.FLNK -128 -112 112 -112 efanouts.dummyFan.SLNK
w 912 1603 100 0 n#14 inhier.c#77.P 672 1600 1152 1600 egenSubC.averageAo.INPH
w 356 435 100 0 n#15 ecalcouts.ecalcouts#71.VAL 328 432 384 432 384 64 608 64 egenSubC.displayAo.SDIS
w 380 499 100 0 n#16 ecalcouts.ecalcouts#71.FLNK 328 496 432 496 432 96 608 96 egenSubC.displayAo.SLNK
w 1536 67 100 0 n#17 egenSubB.startFigure.FLNK 1376 64 1696 64 1696 576 1728 576 eseqs.seqFigure.SLNK
w 1696 899 100 0 n#18 hwin.hwin#66.in 1664 896 1728 896 eseqs.seqFigure.DOL1
w 0 1091 100 0 n#19 elongins.aoMoving.VAL -64 1088 64 1088 64 1600 192 1600 egenSub.calcM1Moving.INPD
w -16 1347 100 0 n#20 elongins.m1CentreLimit.VAL -64 1344 32 1344 32 1664 192 1664 egenSub.calcM1Moving.INPC
w -32 1571 100 0 n#21 elongins.m1HighLimit.VAL -64 1568 0 1568 0 1728 192 1728 egenSub.calcM1Moving.INPB
w 64 1795 100 0 n#22 elongins.m1LowLimit.VAL -64 1792 192 1792 egenSub.calcM1Moving.INPA
w 64 1123 100 0 n#23 elongins.aoMoving.FLNK -64 1120 192 1120 egenSub.calcM1Moving.SLNK
w 2032 1251 100 0 n#24 ebis.apssInPosn.FLNK 1952 1248 2112 1248 2112 1232 2336 1232 estringins.figureMess.SLNK
w 2640 1731 100 0 n#25 ebis.pssOn.FLNK 2592 1728 2688 1728 2688 1600 1536 1600 1536 1456 1696 1456 ebis.aosOn.SLNK
w 2640 1475 100 0 n#26 ebis.pssInPosn.FLNK 2592 1472 2688 1472 2688 1344 1536 1344 1536 1232 1696 1232 ebis.apssInPosn.SLNK
w 2032 1475 100 0 n#27 ebis.aosOn.FLNK 1952 1472 2112 1472 2112 1456 2336 1456 ebis.pssInPosn.SLNK
w 2032 1731 100 0 n#28 ebis.apssOn.FLNK 1952 1728 2112 1728 2112 1712 2336 1712 ebis.pssOn.SLNK
s 1104 1968 100 0 terms starting with tip, tilt and focus
s 1104 2000 100 0 VALB to VALT contain the first 19 Zernike
s 1104 2032 100 0 is new data for M1.
s 1104 2064 100 0 VALA contains the flag that says whether there
s 2304 -64 100 0 Gemini Telescope Control System
s 2336 -128 100 0 Trigger PCS figure command
s 2080 2128 100 0 $Id: tcsDrivePcs.sch,v 1.20 2012/10/04 13:34:22 cjm Exp $
s 1792 384 100 0 Note a sequence record is used to
s 1792 352 100 0 issue the start as it was found that
s 1792 320 100 0 using the gensub meant the START
s 1792 288 100 0 directive arrived in the wrong order
[cell use]
use bc200tr -496 -344 -100 0 frame
xform 0 1184 960
use inhier 656 1559 100 0 c#77
xform 0 672 1600
use inhier 592 1751 100 0 c#9
xform 0 608 1792
use inhier 592 1975 100 0 c#11
xform 0 608 2016
use inhier 592 1399 100 0 c#74
xform 0 608 1440
use inhier 592 1175 100 0 c#80
xform 0 608 1216
use inhier 512 983 100 0 c#105
xform 0 528 1024
use ewaves 704 1095 100 0 aoAo
xform 0 832 1184
p 711 1272 100 0 0 DESC:AO data
p 832 1070 100 0 0 FTVL:DOUBLE
p 832 1102 100 0 0 NELM:40
p 624 1264 100 0 -1 def(INP):$(ao)aoZernikes.VALJ
p 672 1216 75 1280 -1 pproc(INP):CA
use ewaves 704 1671 100 0 pwfs2Ao
xform 0 832 1760
p 711 1848 100 0 0 DESC:PWFS2 data
p 832 1646 100 0 0 FTVL:DOUBLE
p 832 1678 100 0 0 NELM:40
p 624 1840 100 0 -1 def(INP):$(pwfs2)dc:ao.VALJ
p 672 1792 75 1280 -1 pproc(INP):CA
use ewaves 688 1895 100 0 pwfs1Ao
xform 0 816 1984
p 695 2072 100 0 0 DESC:PWFS1 data
p 816 1870 100 0 0 FTVL:DOUBLE
p 816 1902 100 0 0 NELM:40
p 608 2064 100 0 -1 def(INP):$(pwfs1)dc:ao.VALJ
p 656 2016 75 1280 -1 pproc(INP):CA
use ewaves 704 1319 100 0 oiwfsAo
xform 0 832 1408
p 711 1496 100 0 0 DESC:OIWFS data
p 832 1294 100 0 0 FTVL:DOUBLE
p 832 1326 100 0 0 NELM:40
p 624 1488 100 0 -1 def(INP):$(oiwfs)dc:ao.VALJ
p 672 1440 75 1280 -1 pproc(INP):CA
use ewaves 704 903 100 0 gemsAo
xform 0 832 992
p 711 1080 100 0 0 DESC:AO data from GeMS
p 832 878 100 0 0 FTVL:DOUBLE
p 832 910 100 0 0 NELM:40
p 624 1072 100 0 -1 def(INP):$(gems)aoZernikes.VALJ
p 672 1024 75 1280 -1 pproc(INP):CA
use efanouts 112 -249 100 0 dummyFan
xform 0 232 -96
p -64 48 100 0 -1 DESC:Dummy record to disable processing
p -112 -48 100 0 -1 def(SDIS):$(tcs)im:m1GuideOn
use ecalcouts 8 311 100 0 ecalcouts#71
xform 0 168 432
p 80 344 100 0 -1 CALC:A&&B
p 48 600 100 0 -1 DESC:Wait until enabled
p 96 568 100 0 1 OOPT:Every Time
p -304 488 100 0 -1 def(INPA):$(tcs)im:m1GuideOn.VAL
p -376 448 100 0 -1 def(INPB):$(tcs)drives:averageAo.VALA
p 72 312 100 0 -1 name:$(top)waitFigure
p -40 504 75 0 -1 pproc(INPA):CPP
p -40 472 75 0 -1 pproc(INPB):CPP
use hwin 1472 855 100 0 hwin#66
xform 0 1568 896
p 1475 888 100 0 -1 val(in):$(CAD_START)
use eseqs 1728 487 100 0 seqFigure
xform 0 1888 736
p 1840 784 100 0 1 DLY1:0.020
p 2128 896 100 0 -1 def(LNK1):$(m1)figure.DIR
p 2064 896 75 1024 -1 pproc(LNK1):CA
use elongins -320 1031 100 0 aoMoving
xform 0 -192 1104
p -320 1200 100 0 -1 DESC:Number of moving actuators
p -576 1102 100 0 0 EGU:none
p -352 1166 100 0 0 HIGH:3
p -352 1230 100 0 0 HIHI:120
p -576 1070 100 0 0 HOPR:120
p -352 1070 100 0 0 HSV:MINOR
p -256 976 100 0 1 SCAN:.2 second
p -256 944 100 0 1 def(INP):$(m1)aoMoving
p -320 1136 75 1280 -1 palrm(INP):MS
p -352 1136 75 1280 -1 pproc(INP):CA
use elongins -320 1735 100 0 m1LowLimit
xform 0 -192 1808
p -288 1888 100 0 -1 DESC:Low trigger limit
p -576 1806 100 0 0 EGU:none
use elongins -320 1511 100 0 m1HighLimit
xform 0 -192 1584
p -288 1664 100 0 -1 DESC:High trigger limit
p -576 1582 100 0 0 EGU:none
use elongins -320 1287 100 0 m1CentreLimit
xform 0 -192 1360
p -288 1440 100 0 -1 DESC:Deadband centre
p -576 1358 100 0 0 EGU:none
use egenSub 192 1031 100 0 calcM1Moving
xform 0 336 1456
p 224 1888 100 0 -1 DESC:Generate m1Moving flag
p -31 805 100 0 0 FTA:LONG
p -31 805 100 0 0 FTB:LONG
p -31 773 100 0 0 FTC:LONG
p 368 1312 100 0 0 FTD:LONG
p -31 805 100 0 0 FTVA:LONG
p -31 805 100 0 0 FTVB:LONG
p -31 773 100 0 0 FTVC:LONG
p -31 741 100 0 0 FTVD:LONG
p -31 709 100 0 0 FTVE:STRING
p 128 976 100 0 1 SNAM:tcsOpticsCalcM1Moving
use estringins 2336 1159 100 0 figureMess
xform 0 2464 1232
p 2320 1312 100 0 -1 DESC:Message from figure record
p 2336 1326 100 0 0 VAL:
p 2080 1264 100 0 -1 def(INP):$(m1)figure.MESS
p 2336 1264 75 1280 -1 palrm(INP):MS
p 2304 1264 75 1280 -1 pproc(INP):CA
use egenSubC 608 7 100 0 displayAo
xform 0 752 432
p 608 864 100 0 -1 DESC:Display ao data sent to PCS
p 688 64 100 0 1 DISV:0
p 320 558 100 0 0 PREC:14
p 656 -48 100 0 1 SNAM:tcsOpticsDisplayAo
use egenSubC 1152 1031 100 0 averageAo
xform 0 1296 1456
p 1072 1888 100 0 -1 DESC:Average Zernikes for PCS Figure command
p 929 645 100 0 0 FTF:DOUBLE
p 929 613 100 0 0 FTH:DOUBLE
p 929 549 100 0 0 FTJ:DOUBLE
p 929 549 100 0 0 FTL:LONG
p 1264 1824 100 0 1 FTVA:LONG
p 929 453 100 0 0 NOA:1
p 1232 1792 100 0 -1 NOB:40
p 1232 1728 100 0 -1 NOD:40
p 1232 1664 100 0 -1 NOF:40
p 1248 1600 100 0 -1 NOH:40
p 1232 1520 100 0 1 NOJ:40
p 929 165 100 0 0 NON:40
p 864 1582 100 0 0 PREC:14
p 1216 992 100 0 1 SCAN:.2 second
p 1216 960 100 0 1 SNAM:tcsOpticsAverageAo
p 880 1808 100 0 0 def(INPB):0.0000000000000000e+00
p 880 1744 100 0 0 def(INPD):0.0000000000000000e+00
p 880 1680 100 0 0 def(INPF):0.0000000000000000e+00
p 880 1616 100 0 -1 def(INPH):$(tcs)hr:dc:ao.VALJ
p 864 1552 100 0 0 def(INPJ):0.0000000000000000e+00
p 1104 1802 75 0 -1 pproc(INPB):PP
p 1104 1738 75 0 -1 pproc(INPD):PP
p 1104 1674 75 0 -1 pproc(INPF):PP
p 1104 1546 75 0 -1 pproc(INPJ):PP
p 1104 1418 75 0 -1 pproc(INPN):PP
use tcsM1CalcModel -384 -201 100 0 tcsM1CalcModel#40
xform 0 -240 0
use egenSubE 2368 199 100 0 figureTotals
xform 0 2512 624
p 2320 1040 100 0 -1 DESC:Fetch total figure offsets from M1
p 2080 750 100 0 0 PREC:10
p 2432 144 100 0 1 SCAN:1 second
p 2432 96 100 0 1 SNAM:tcsOpticsFigureTotals
p 2084 1002 100 0 0 def(INPA):$(m1)aos:ZernikeSum.VALA
p 2084 970 100 0 0 def(INPB):$(m1)aos:ZernikeSum.VALB
p 2084 938 100 0 0 def(INPC):$(m1)aos:ZernikeSum.VALC
p 2084 906 100 0 0 def(INPD):$(m1)aos:ZernikeSum.VALD
p 2084 874 100 0 0 def(INPE):$(m1)aos:ZernikeSum.VALE
p 2084 842 100 0 0 def(INPF):$(m1)aos:ZernikeSum.VALF
p 2084 810 100 0 0 def(INPG):$(m1)aos:ZernikeSum.VALG
p 2084 778 100 0 0 def(INPH):$(m1)aos:ZernikeSum.VALH
p 2084 746 100 0 0 def(INPI):$(m1)aos:ZernikeSum.VALI
p 2084 714 100 0 0 def(INPJ):$(m1)aos:ZernikeSum.VALJ
p 2084 682 100 0 0 def(INPK):$(m1)aos:ZernikeSum.VALK
p 2084 650 100 0 0 def(INPL):$(m1)aos:ZernikeSum.VALL
p 2084 618 100 0 0 def(INPM):$(m1)aos:ZernikeSum.VALM
p 2084 586 100 0 0 def(INPN):$(m1)aos:ZernikeSum.VALN
use ebis 2336 1383 100 0 pssInPosn
xform 0 2464 1456
p 2272 1536 100 0 -1 DESC:Passive supports in position status
p 2112 1294 100 0 0 ONAM:TRUE
p 2112 1326 100 0 0 ZNAM:FALSE
p 2336 1390 100 0 0 ZSV:MINOR
p 2048 1488 100 0 -1 def(INP):$(m1)pss:inPosnBO
p 2336 1488 75 1280 -1 palrm(INP):MS
p 2304 1488 75 1280 -1 pproc(INP):CA
use ebis 1696 1383 100 0 aosOn
xform 0 1824 1456
p 1680 1536 100 0 -1 DESC:State of active supports
p 1472 1294 100 0 0 ONAM:ON
p 1472 1326 100 0 0 ZNAM:OFF
p 1504 1488 100 0 -1 def(INP):$(m1)aosOn
p 1696 1488 75 1280 -1 palrm(INP):MS
p 1664 1488 75 1280 -1 pproc(INP):CA
use ebis 1696 1639 100 0 apssOn
xform 0 1824 1712
p 1664 1792 100 0 -1 DESC:State of air pressure support
p 1472 1550 100 0 0 ONAM:ON
p 1904 1648 100 0 1 SCAN:1 second
p 1472 1582 100 0 0 ZNAM:OFF
p 1488 1744 100 0 -1 def(INP):$(m1)apssOn
p 1696 1744 75 1280 -1 palrm(INP):MS
p 1664 1744 75 1280 -1 pproc(INP):CA
use ebis 2336 1639 100 0 pssOn
xform 0 2464 1712
p 2320 1792 100 0 -1 DESC:State of passive supports
p 2112 1550 100 0 0 ONAM:ON
p 2112 1582 100 0 0 ZNAM:OFF
p 2144 1744 100 0 -1 def(INP):$(m1)pssOn
p 2336 1744 75 1280 -1 palrm(INP):MS
p 2304 1744 75 1280 -1 pproc(INP):CA
use ebis 1696 1159 100 0 apssInPosn
xform 0 1824 1232
p 1632 1312 100 0 -1 DESC:Air pressure support in position status
p 1712 1120 100 0 1 ONAM:In Position
p 1712 1072 100 0 1 ZNAM:Off Target
p 1696 1166 100 0 0 ZSV:MINOR
p 1728 1040 100 0 1 def(INP):$(m1)apss:inPosition
p 1696 1264 75 1280 -1 palrm(INP):MS
p 1664 1264 75 1280 -1 pproc(INP):CA
use egenSubB 1088 7 100 0 startFigure
xform 0 1232 432
p 1120 864 100 0 -1 DESC:Drive M1 figure command
p 1168 336 100 0 0 DISV:1
p 865 -475 100 0 0 FTVO:DOUBLE
p 800 558 100 0 0 PREC:14
p 1152 -48 100 0 1 SNAM:tcsOpticsM1Figure
p 1488 800 100 0 -1 def(OUTA):$(m1)figure.B
p 1488 768 100 0 -1 def(OUTB):$(m1)figure.C
p 1488 736 100 0 -1 def(OUTC):$(m1)figure.D
p 1488 704 100 0 -1 def(OUTD):$(m1)figure.E
p 1488 672 100 0 -1 def(OUTE):$(m1)figure.F
p 1488 640 100 0 -1 def(OUTF):$(m1)figure.G
p 1488 608 100 0 -1 def(OUTG):$(m1)figure.H
p 1488 576 100 0 -1 def(OUTH):$(m1)figure.I
p 1488 544 100 0 -1 def(OUTI):$(m1)figure.J
p 1488 512 100 0 -1 def(OUTJ):$(m1)figure.K
p 1488 480 100 0 -1 def(OUTK):$(m1)figure.L
p 1488 448 100 0 -1 def(OUTL):$(m1)figure.M
p 1488 416 100 0 -1 def(OUTM):$(m1)figure.N
p 1488 384 100 0 -1 def(OUTN):$(m1)figure.O
p 1488 352 100 0 0 def(OUTO):0.0
p 1376 362 75 0 -1 pproc(OUTO):NPP
use tcsM1CalcModelValid -336 576 100 0 tcsM1CalcModelValid#106
xform 0 -224 728
[comments]
