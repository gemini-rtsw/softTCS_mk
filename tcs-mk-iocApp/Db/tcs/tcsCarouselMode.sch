[schematic2]
uniq 46
[tools]
[detail]
w 946 1168 100 0 n#44 ecad8.ecad8#0.VALB 857 1569 944 1569 944 720 1168 720 estringouts.shutterDriveMode.DOL
w 962 1328 100 0 n#43 ecad8.ecad8#0.VALA 857 1633 960 1633 960 976 1168 976 estringouts.carouselDriveMode.DOL
w 1296 802 100 0 n#42 estringouts.carouselDriveMode.FLNK 1424 960 1536 960 1536 800 1104 800 1104 688 1168 688 estringouts.shutterDriveMode.SLNK
w 1296 1074 100 0 n#41 eaos.moveShtrsFlag.FLNK 1424 1232 1536 1232 1536 1072 1104 1072 1104 944 1168 944 estringouts.carouselDriveMode.SLNK
w 2104 1090 100 0 n#38 eaos.moveShtrsFlag.OUT 1424 1168 1824 1168 1824 1088 2432 1088 2432 1552 junction
w 2434 1768 100 0 n#38 egenSub.ecsShowFlags.OUTB 2336 1936 2432 1936 2432 1552 2736 1552 ebos.autoMoveShtrs.SLNK
w 2466 1488 100 0 n#37 eaos.moveDomeFlag.OUT 1424 1424 1856 1424 1856 1120 2464 1120 2464 1808 junction
w 2576 1810 100 0 n#37 egenSub.ecsShowFlags.OUTA 2336 2000 2464 2000 2464 1808 2736 1808 ebos.autoMoveDome.SLNK
w 1056 1234 100 0 n#31 ecad8.ecad8#0.VALE 857 1377 992 1377 992 1232 1168 1232 eaos.moveShtrsFlag.DOL
w 1296 1330 100 0 n#30 eaos.moveDomeFlag.FLNK 1424 1488 1536 1488 1536 1328 1104 1328 1104 1200 1168 1200 eaos.moveShtrsFlag.SLNK
w 1056 1490 100 0 n#28 ecad8.ecad8#0.VALD 857 1441 992 1441 992 1488 1168 1488 eaos.moveDomeFlag.DOL
w 1026 1232 100 0 n#27 ecad8.ecad8#0.STLK 857 961 1024 961 1024 1456 1168 1456 eaos.moveDomeFlag.SLNK
w 1028 1797 100 0 n#18 ecad8.ecad8#0.MESS 857 1793 1248 1793 1248 1728 1376 1728 outhier.MESS.p
w 1092 1829 100 0 n#17 ecad8.ecad8#0.VAL 857 1825 1376 1825 1376 1824 outhier.VAL.p
w 322 1715 100 0 n#4 inhier.ICID.P 228 1713 452 1713 452 1793 537 1793 ecad8.ecad8#0.ICID
w 322 1859 100 0 n#3 inhier.DIR.P 228 1857 452 1857 452 1825 537 1825 ecad8.ecad8#0.DIR
s 1920 2112 100 0 dome and shutters.
s 1920 2144 100 0 CAD schematics i.e. those to move, stop and park the
s 1920 2176 100 0 through EPICS links would have meant customising 6
s 1920 2208 100 0 accessible. This is a fudge but to have done this 
s 1920 2240 100 0 This gensub simply keeps the autoMove flags publically
s 2608 1920 100 0 park sequence command.
s 2608 1952 100 0 N.B. These two records are also written to by the 
s 2848 208 100 0 Gemini Telescope Control System
s 2608 2400 100 0 $Id: tcsCarouselMode.sch,v 1.1.1.1 1998/11/08 00:20:32 epics Exp $
[cell use]
use estringouts 1192 872 100 0 carouselDriveMode
xform 0 1296 944
p 1184 1022 100 0 -1 DESC:Enclosure operating mode
p 1104 750 100 0 0 OMSL:closed_loop
p 1104 910 100 0 0 VAL:Basic
p 1136 378 100 0 0 def(OUT):$(sad)carouselDriveMode
p 1280 832 100 1024 1 name:$(tcs)$(I)
p 1424 928 75 768 -1 pproc(OUT):PP
use estringouts 1192 616 100 0 shutterDriveMode
xform 0 1296 688
p 1184 766 100 0 -1 DESC:Shutter operating mode
p 1104 494 100 0 0 OMSL:closed_loop
p 1104 654 100 0 0 VAL:FullyOpen
p 1136 122 100 0 0 def(OUT):$(sad)shutterDriveMode
p 1280 576 100 1024 1 name:$(tcs)$(I)
p 1424 672 75 768 -1 pproc(OUT):PP
use egenSub 2072 1240 100 0 ecsShowFlags
xform 0 2192 1664
p 2064 2078 100 0 -1 DESC:Update enable/disable flags
p 2144 1998 100 0 1 FTVA:LONG
p 2144 1934 100 0 1 FTVB:LONG
p 2112 1166 100 0 1 SCAN:.5 second
p 2096 1406 100 0 -1 SNAM:tcsEcsShowFlags
p 2160 1200 100 1024 1 name:$(tcs)$(I)
p 2336 2010 75 0 -1 pproc(OUTA):PP
p 2336 1946 75 0 -1 pproc(OUTB):PP
use eaos 1192 1112 100 0 moveShtrsFlag
xform 0 1296 1200
p 1168 1294 100 0 -1 DESC:Propagate shtrs move flag
p 1136 926 100 0 0 EGU:None
p 912 1182 100 0 0 OMSL:closed_loop
p 1456 1104 100 1024 1 name:$(tcs)$(I)
p 1424 1168 75 768 -1 pproc(OUT):PP
use eaos 1192 1368 100 0 moveDomeFlag
xform 0 1296 1456
p 1168 1550 100 0 -1 DESC:Propagate dome move flag
p 1136 1182 100 0 0 EGU:None
p 912 1438 100 0 0 OMSL:closed_loop
p 1440 1360 100 1024 1 name:$(tcs)$(I)
p 1424 1424 75 768 -1 pproc(OUT):PP
use ebos 2760 1720 100 0 autoMoveDome
xform 0 2864 1808
p 2416 1758 100 0 0 OMSL:supervisory
p 2416 1662 100 0 0 ONAM:On
p 2416 1694 100 0 0 ZNAM:Off
p 2848 1680 100 1024 1 name:$(tcs)$(I)
use ebos 2760 1464 100 0 autoMoveShtrs
xform 0 2864 1552
p 2416 1502 100 0 0 OMSL:supervisory
p 2416 1406 100 0 0 ONAM:On
p 2416 1438 100 0 0 ZNAM:Off
p 2848 1424 100 1024 1 name:$(tcs)$(I)
use outhier 1368 1784 100 0 VAL
xform 0 1360 1824
use outhier 1368 1688 100 0 MESS
xform 0 1360 1728
use inhier 236 1817 100 0 DIR
xform 0 228 1857
use inhier 236 1673 100 0 ICID
xform 0 228 1713
use ecad8 561 873 100 0 ecad8#0
xform 0 697 1377
p 553 1919 100 0 -1 DESC:Implement a TCS internal command
p 633 1473 100 0 0 FTVD:LONG
p 633 1441 100 0 0 FTVE:LONG
p 633 1217 100 0 0 PREC:2
p 633 1087 100 0 1 SNAM:$(snam)
p 677 801 100 1024 1 name:$(tcs)$(cad)
use bc200tr 16 -72 -100 0 frame
xform 0 1696 1232
[comments]
