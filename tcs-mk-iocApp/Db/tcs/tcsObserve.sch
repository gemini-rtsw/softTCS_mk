[schematic2]
uniq 63
[tools]
[detail]
w 1760 1035 100 0 n#12 junction 1344 1024 2224 1024 2224 864 2464 864 eaos.currentZd.DOL
w 1992 331 100 0 n#62 eaos.airMassNow.FLNK 1808 320 2224 320 2224 832 2464 832 eaos.currentZd.SLNK
w 1752 114 100 0 n#59 efanouts.obsEnd.LNK3 496 544 1184 544 1184 112 2368 112 2368 464 2464 464 eaos.rotPaEnd.SLNK
w 2336 498 100 0 n#53 inhier.c#57.P 2256 496 2464 496 eaos.rotPaEnd.DOL
w 1504 2178 100 0 n#45 efanouts.obsBegin.LNK3 512 1952 1088 1952 1088 2176 1968 2176 1968 2096 2256 2096 eaos.rotPaStart.SLNK
w 2128 2130 100 0 n#41 inhier.c#39.P 2048 2128 2256 2128 eaos.rotPaStart.DOL
w 2104 1266 100 0 n#37 inhier.CONTINUE.P 2048 1264 2208 1264 tcsMeanAirmass.tcsMeanAirmass#26.CONTINUE
w 2104 1330 100 0 n#36 inhier.PAUSE.P 2048 1328 2208 1328 tcsMeanAirmass.tcsMeanAirmass#26.PAUSE
w 2178 928 100 0 n#33 eaos.amEnd.FLNK 1808 608 2176 608 2176 1200 2208 1200 tcsMeanAirmass.tcsMeanAirmass#26.END
w 1920 1570 100 0 n#32 eaos.amStart.FLNK 1808 1568 2080 1568 2080 1392 2208 1392 tcsMeanAirmass.tcsMeanAirmass#26.BEGIN
w 2114 896 100 0 n#31 eaos.airMassNow.VAL 1808 288 2112 288 2112 1456 2208 1456 tcsMeanAirmass.tcsMeanAirmass#26.AIRMASS
w 2626 1464 100 0 n#30 tcsMeanAirmass.tcsMeanAirmass#26.AMMEAN 2592 1392 2624 1392 2624 1488 2688 1488 eaos.airMass.DOL
w 2616 1458 100 0 n#29 tcsMeanAirmass.tcsMeanAirmass#26.FLNK 2592 1456 2688 1456 eaos.airMass.SLNK
w 1378 488 100 0 n#13 junction 1376 608 1376 320 1552 320 eaos.airMassNow.DOL
w 1378 1096 100 0 n#13 junction 1376 1536 1376 608 1552 608 eaos.amEnd.DOL
w 1248 1538 100 0 n#13 egenSub.calcAirmass.VALC 1168 1536 1376 1536 1376 1568 1552 1568 eaos.amStart.DOL
w 1250 632 100 0 n#25 egenSub.calcAirmass.FLNK 1168 928 1248 928 1248 288 1552 288 eaos.airMassNow.SLNK
w 864 578 100 0 n#23 efanouts.obsEnd.LNK2 496 576 1280 576 1280 1200 1552 1200 eaos.azEnd.SLNK
w 1346 1288 100 0 n#12 junction 1344 1600 1344 928 1552 928 eaos.zdEnd.DOL
w 1424 1794 100 0 n#12 egenSub.calcAirmass.VALB 1168 1600 1344 1600 1344 1792 1552 1792 eaos.zdStart.DOL
w 1314 1466 100 0 n#9 junction 1312 1664 1312 1232 1552 1232 eaos.azEnd.DOL
w 1314 1874 100 0 n#9 egenSub.calcAirmass.VALA 1168 1664 1312 1664 1312 2048 1552 2048 eaos.azStart.DOL
w 1656 738 100 0 n#22 eaos.zdEnd.FLNK 1808 928 1920 928 1920 736 1440 736 1440 576 1552 576 eaos.amEnd.SLNK
w 1656 1074 100 0 n#21 eaos.azEnd.FLNK 1808 1232 1920 1232 1920 1072 1440 1072 1440 896 1552 896 eaos.zdEnd.SLNK
w 160 530 100 0 n#17 inhier.OBSEND.P 112 528 256 528 efanouts.obsEnd.SLNK
w 674 802 100 0 n#2 efanouts.obsEnd.LNK1 496 608 672 608 672 960 junction
w 674 1546 100 0 n#2 efanouts.obsBegin.LNK1 512 2016 672 2016 672 1040 junction
w 758 962 100 0 n#2 efanouts.scan.FLNK 496 1040 672 1040 672 960 880 960 egenSub.calcAirmass.SLNK
w 904 1986 100 0 n#14 efanouts.obsBegin.LNK2 512 1984 1344 1984 1344 2016 1552 2016 eaos.azStart.SLNK
w 1656 1666 100 0 n#11 eaos.zdStart.FLNK 1808 1792 1920 1792 1920 1664 1440 1664 1440 1536 1552 1536 eaos.amStart.SLNK
w 1656 1890 100 0 n#10 eaos.azStart.FLNK 1808 2048 1920 2048 1920 1888 1440 1888 1440 1760 1552 1760 eaos.zdStart.SLNK
w 174 1938 100 0 n#5 inhier.OBSBEGIN.P 112 1936 272 1936 efanouts.obsBegin.SLNK
s 288 2144 100 0 outputs to be sent to the SAD
s 288 2176 100 0 to be recalculated then it forces the
s 288 2208 100 0 This record first causes the airmass etc.
s 2528 2432 100 0 $Id: tcsObserve.sch,v 1.4 2000/05/09 08:02:16 cjm Exp $
s 2784 240 100 0 Gemini Telescope Control System
s 1344 2272 100 0 This schematic implements the processing that occurs when
s 1344 2240 100 0 the observe command is issued
[cell use]
use eaos 2488 744 100 0 currentZd
xform 0 2592 832
p 2432 926 100 0 -1 DESC:Current zenith distance
p 2432 558 100 0 0 EGU:degrees
p 2208 270 100 0 0 MDEL:0.00005
p 2208 814 100 0 0 OMSL:closed_loop
p 2208 686 100 0 0 PREC:6
p 2800 798 100 0 -1 def(OUT):$(sad)currentZd
p 2768 736 100 1024 1 name:$(tcs)$(I)
p 2720 800 75 768 -1 pproc(OUT):PP
use eaos 2488 376 100 0 rotPaEnd
xform 0 2592 464
p 2400 576 100 0 -1 DESC:Rotator PA at end of observation
p 2351 698 100 0 0 DTYP:Soft Channel
p 2432 190 100 0 0 EGU:degs
p 2208 446 100 0 0 OMSL:closed_loop
p 2240 526 100 0 -1 def(DOL):$(cr)crCurrentPos
p 2800 432 100 0 -1 def(OUT):$(sad)rotPaEnd
p 2576 368 100 1024 0 name:$(tcs)$(I)
p 2432 496 75 1280 -1 pproc(DOL):NPP
p 2720 432 75 768 -1 pproc(OUT):PP
use eaos 2280 2008 100 0 rotPaStart
xform 0 2384 2096
p 2224 2208 100 0 -1 DESC:Rotator PA at start of observation
p 2143 2330 100 0 0 DTYP:Soft Channel
p 2000 2078 100 0 0 OMSL:closed_loop
p 2032 2158 100 0 -1 def(DOL):$(cr)crCurrentPos
p 2592 2048 100 0 -1 def(OUT):$(sad)rotPaStart
p 2368 2000 100 1024 0 name:$(tcs)$(I)
p 2512 2064 75 768 -1 pproc(OUT):PP
use eaos 1576 200 100 0 airMassNow
xform 0 1680 288
p 1616 382 100 0 -1 DESC:Current airmass
p 1520 14 100 0 0 EGU:none
p 1696 142 100 0 1 HHSV:MINOR
p 1552 142 100 0 1 HIHI:4.0
p 1296 270 100 0 0 OMSL:closed_loop
p 1296 142 100 0 0 PREC:3
p 1888 254 100 0 -1 def(OUT):$(sad)airMassNow
p 1824 192 100 1024 1 name:$(tcs)$(I)
p 1552 320 75 1280 -1 palrm(DOL):MS
p 1840 256 75 768 -1 palrm(OUT):MS
p 1808 256 75 768 -1 pproc(OUT):PP
use eaos 1576 488 100 0 amEnd
xform 0 1680 576
p 1520 670 100 0 -1 DESC:Airmass at observation end
p 1520 302 100 0 0 EGU:none
p 1296 558 100 0 0 OMSL:closed_loop
p 1296 430 100 0 0 PREC:3
p 1888 542 100 0 -1 def(OUT):$(sad)amEnd
p 1760 480 100 1024 1 name:$(tcs)$(I)
p 1808 544 75 768 -1 pproc(OUT):PP
use eaos 1576 808 100 0 zdEnd
xform 0 1680 896
p 1520 990 100 0 -1 DESC:Zenith distance at observation end
p 1520 622 100 0 0 EGU:degrees
p 1296 878 100 0 0 OMSL:closed_loop
p 1296 750 100 0 0 PREC:2
p 1888 862 100 0 -1 def(OUT):$(sad)zdEnd
p 1744 800 100 1024 1 name:$(tcs)$(I)
p 1808 864 75 768 -1 pproc(OUT):PP
use eaos 1576 1112 100 0 azEnd
xform 0 1680 1200
p 1520 1294 100 0 -1 DESC:Azimith at observation end
p 1520 926 100 0 0 EGU:degrees
p 1296 1182 100 0 0 OMSL:closed_loop
p 1296 1054 100 0 0 PREC:2
p 1888 1166 100 0 -1 def(OUT):$(sad)azEnd
p 1760 1104 100 1024 1 name:$(tcs)$(I)
p 1808 1168 75 768 -1 pproc(OUT):PP
use eaos 1576 1448 100 0 amStart
xform 0 1680 1536
p 1520 1630 100 0 -1 DESC:Airmass at observation start
p 1520 1262 100 0 0 EGU:none
p 1296 1518 100 0 0 OMSL:closed_loop
p 1296 1390 100 0 0 PREC:3
p 1888 1502 100 0 -1 def(OUT):$(sad)amStart
p 1776 1440 100 1024 1 name:$(tcs)$(I)
p 1808 1504 75 768 -1 pproc(OUT):PP
use eaos 1576 1672 100 0 zdStart
xform 0 1680 1760
p 1520 1854 100 0 -1 DESC:Zenith distance at observation start
p 1520 1486 100 0 0 EGU:degrees
p 1296 1742 100 0 0 OMSL:closed_loop
p 1296 1614 100 0 0 PREC:2
p 1888 1726 100 0 -1 def(OUT):$(sad)zdStart
p 1776 1664 100 1024 1 name:$(tcs)$(I)
p 1808 1728 75 768 -1 pproc(OUT):PP
use eaos 1576 1928 100 0 azStart
xform 0 1680 2016
p 1520 2110 100 0 -1 DESC:Azimuth at observation start
p 1520 1742 100 0 0 EGU:degrees
p 1296 1998 100 0 0 OMSL:closed_loop
p 1296 1870 100 0 0 PREC:2
p 1888 1982 100 0 -1 def(OUT):$(sad)azStart
p 1792 1920 100 1024 1 name:$(tcs)$(I)
p 1808 1984 75 768 -1 pproc(OUT):PP
use eaos 2712 1368 100 0 airMass
xform 0 2816 1456
p 2656 1550 100 0 -1 DESC:Mean airmass during observation
p 2656 1182 100 0 0 EGU:none
p 2432 1438 100 0 0 OMSL:closed_loop
p 2432 1310 100 0 0 PREC:3
p 3024 1422 100 0 -1 def(OUT):$(sad)airMass
p 2912 1360 100 1024 1 name:$(tcs)$(I)
p 2944 1424 75 768 -1 pproc(OUT):PP
use inhier 2056 2088 100 0 c#39
xform 0 2048 2128
use inhier 120 488 100 0 OBSEND
xform 0 112 528
use inhier 120 1896 100 0 OBSBEGIN
xform 0 112 1936
use inhier 2056 1288 100 0 PAUSE
xform 0 2048 1328
use inhier 2056 1224 100 0 CONTINUE
xform 0 2048 1264
use inhier 2264 456 100 0 c#57
xform 0 2256 496
use tcsMeanAirmass 2232 1080 100 0 tcsMeanAirmass#26
xform 0 2400 1344
p 2272 1600 100 0 -1 seta:top $(tcs)airmass:
use efanouts 280 392 100 0 obsEnd
xform 0 376 544
p 336 702 100 0 0 SCAN:Passive
p 368 384 100 1024 0 name:$(top)$(I)
use efanouts 296 1800 100 0 obsBegin
xform 0 392 1952
p 352 2110 100 0 0 SCAN:Passive
p 384 1792 100 1024 0 name:$(top)$(I)
use efanouts 280 792 100 0 scan
xform 0 376 944
p 336 1102 100 0 1 SCAN:1 second
p 368 784 100 1024 0 name:$(top)$(I)
use egenSub 904 872 100 0 calcAirmass
xform 0 1024 1296
p 912 1726 100 0 -1 DESC:Compute zd and airmass
p 912 798 100 0 1 SNAM:tcsDisplayAirmass
p 592 1630 100 0 -1 def(INPA):$(mc)azCurrentPos
p 592 1566 100 0 -1 def(INPB):$(mc)elCurrentPos
p 992 864 100 1024 0 name:$(top)$(I)
use bc200tr -48 -40 -100 0 frame
xform 0 1632 1264
[comments]
