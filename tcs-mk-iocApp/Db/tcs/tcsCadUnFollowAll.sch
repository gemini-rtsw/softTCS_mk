[schematic2]
uniq 21
[tools]
[detail]
w 928 1443 100 0 n#1 ecad8.unfollowAll.MESS 800 1440 1056 1440 1056 1392 1248 1392 outhier.MESS.p
w 1024 1475 100 0 n#2 ecad8.unfollowAll.VAL 800 1472 1248 1472 outhier.VAL.p
w 128 1395 100 0 n#3 inhier.ICID.P -128 1392 384 1392 384 1440 480 1440 ecad8.unfollowAll.ICID
w 176 1475 100 0 n#4 inhier.DIR.P -128 1472 480 1472 ecad8.unfollowAll.DIR
w 1908 1923 100 0 n#5 estringouts.unfollowAllMount.FLNK 1880 1920 1936 1920 1936 1792 1448 1792 1448 1680 1632 1680 estringouts.unfollowAllCass.SLNK
w 1912 1699 100 0 n#6 estringouts.unfollowAllCass.FLNK 1888 1696 1936 1696 1936 1544 1448 1544 1448 1464 1640 1464 estringouts.unfollowAllEncD.SLNK
w 1916 1483 100 0 n#7 estringouts.unfollowAllEncD.FLNK 1896 1480 1936 1480 1936 1336 1448 1336 1448 1248 1648 1248 estringouts.unfollowAllEncE.SLNK
w 1924 1267 100 0 n#8 estringouts.unfollowAllEncE.FLNK 1904 1264 1944 1264 1944 1128 1448 1128 1448 1040 1648 1040 estringouts.unfollowAllM2.SLNK
w 1924 1059 100 0 n#9 estringouts.unfollowAllM2.FLNK 1904 1056 1944 1056 1944 912 1456 912 1456 824 1648 824 estringouts.unfollowAllPwfs1.SLNK
w 1920 843 100 0 n#10 estringouts.unfollowAllPwfs1.FLNK 1904 840 1936 840 1936 704 1456 704 1456 632 1648 632 estringouts.unfollowAllPwfs2.SLNK
w 1920 651 100 0 n#11 estringouts.unfollowAllPwfs2.FLNK 1904 648 1936 648 1936 520 1464 520 1464 440 1648 440 estringouts.unfollowAllOiwfs.SLNK
w 1920 459 100 0 n#12 estringouts.unfollowAllOiwfs.FLNK 1904 456 1936 456 1936 320 1464 320 1464 240 1656 240 estringouts.unfollowAllAO.SLNK
w 2716 1891 100 0 n#13 estringouts.unfollowAllngs1.FLNK 2688 1888 2744 1888 2744 1760 2256 1760 2256 1648 2440 1648 estringouts.unfollowAllngs2.SLNK
w 2720 1667 100 0 n#14 estringouts.unfollowAllngs2.FLNK 2696 1664 2744 1664 2744 1512 2256 1512 2256 1432 2448 1432 estringouts.unfollowAllngs3.SLNK
w 2724 1451 100 0 n#15 estringouts.unfollowAllngs3.FLNK 2704 1448 2744 1448 2744 1304 2256 1304 2256 1216 2456 1216 estringouts.unfollowAllodgw1.SLNK
w 2732 1235 100 0 n#16 estringouts.unfollowAllodgw1.FLNK 2712 1232 2752 1232 2752 1096 2256 1096 2256 1008 2456 1008 estringouts.unfollowAllodgw2.SLNK
w 2732 1027 100 0 n#17 estringouts.unfollowAllodgw2.FLNK 2712 1024 2752 1024 2752 880 2264 880 2264 792 2456 792 estringouts.unfollowAllodgw3.SLNK
w 2728 811 100 0 n#18 estringouts.unfollowAllodgw3.FLNK 2712 808 2744 808 2744 672 2264 672 2264 600 2456 600 estringouts.unfollowAllodgw4.SLNK
w 1922 266 -100 0 n#19 estringouts.unfollowAllAO.FLNK 1912 256 2168 256 2168 1872 2432 1872 estringouts.unfollowAllngs1.SLNK
w 810 618 -100 0 n#20 ecad8.unfollowAll.STLK 800 608 1328 608 1328 1904 1624 1904 estringouts.unfollowAllMount.SLNK
s 2288 2112 100 0 $Id: tcsCadUnFollowAll.sch,v 1.4 2015/08/07 20:00:44 gemvx Exp $
s 2592 -144 100 0 TCS FOLLOW Command
s 2512 -80 100 0 Gemini Telescope Control System
[cell use]
use bc200tr -288 -360 -100 0 frame
xform 0 1392 944
use outhier 1240 1352 100 0 MESS
xform 0 1232 1392
use outhier 1240 1432 100 0 VAL
xform 0 1232 1472
use inhier -120 1352 100 0 ICID
xform 0 -128 1392
use inhier -120 1432 100 0 DIR
xform 0 -128 1472
use ecad8 504 520 -100 0 unfollowAll
xform 0 640 1024
p 576 1672 100 0 0 FTVA:DOUBLE
p 576 1640 100 0 0 FTVB:DOUBLE
p 576 1608 100 0 0 FTVC:DOUBLE
p 576 1576 100 0 0 FTVD:DOUBLE
p 576 1544 100 0 0 FTVE:DOUBLE
p 576 1512 100 0 0 FTVF:DOUBLE
p 576 1480 100 0 0 FTVG:DOUBLE
p 576 1448 100 0 0 FTVH:DOUBLE
p 576 1960 100 0 0 SNAM:tcsCADunfollowAll
p 576 -3224 100 0 0 def(SPLK):0.0
p 576 776 100 0 0 def(STLK):0.0
p 576 494 100 0 -1 name:$(tcs)unfollowAll
p 800 1248 75 768 -1 pproc(OUTA):NPP
p 800 1184 75 768 -1 pproc(OUTB):NPP
p 800 1120 75 768 -1 pproc(OUTC):NPP
p 800 1056 75 768 -1 pproc(OUTD):NPP
p 800 992 75 768 -1 pproc(OUTE):NPP
p 800 928 75 768 -1 pproc(OUTF):NPP
p 800 864 75 768 -1 pproc(OUTG):NPP
p 800 800 75 768 -1 pproc(OUTH):NPP
p 576 -2904 100 0 0 typ(OUTH):path
use estringouts 2527 517 100 0 unfollowAllodgw4
xform 0 2584 600
p 2392 566 100 0 0 VAL:off
p 2782 574 100 0 -1 def(OUT):$(tcs)odgw4Follow.A
p 2720 592 75 768 -1 pproc(OUT):NPP
p 2384 576 75 1280 -1 pproc(SDIS):NPP
use estringouts 2527 709 100 0 unfollowAllodgw3
xform 0 2584 792
p 2392 758 100 0 0 VAL:off
p 2782 766 100 0 -1 def(OUT):$(tcs)odgw3Follow.A
p 2720 784 75 768 -1 pproc(OUT):NPP
p 2384 768 75 1280 -1 pproc(SDIS):NPP
use estringouts 2527 925 100 0 unfollowAllodgw2
xform 0 2584 1008
p 2392 974 100 0 0 VAL:off
p 2782 982 100 0 -1 def(OUT):$(tcs)odgw2Follow.A
p 2720 1000 75 768 -1 pproc(OUT):NPP
p 2384 984 75 1280 -1 pproc(SDIS):NPP
use estringouts 2527 1133 100 0 unfollowAllodgw1
xform 0 2584 1216
p 2392 1182 100 0 0 VAL:off
p 2782 1190 100 0 -1 def(OUT):$(tcs)odgw1Follow.A
p 2720 1208 75 768 -1 pproc(OUT):NPP
p 2384 1192 75 1280 -1 pproc(SDIS):NPP
use estringouts 2519 1349 100 0 unfollowAllngs3
xform 0 2576 1432
p 2384 1398 100 0 0 VAL:off
p 2774 1406 100 0 -1 def(OUT):$(tcs)ngs3Follow.A
p 2712 1424 75 768 -1 pproc(OUT):NPP
p 2376 1408 75 1280 -1 pproc(SDIS):NPP
use estringouts 2511 1565 100 0 unfollowAllngs2
xform 0 2568 1648
p 2376 1614 100 0 0 VAL:off
p 2766 1622 100 0 -1 def(OUT):$(tcs)ngs2Follow.A
p 2704 1640 75 768 -1 pproc(OUT):NPP
p 2368 1624 75 1280 -1 pproc(SDIS):NPP
use estringouts 2503 1789 100 0 unfollowAllngs1
xform 0 2560 1872
p 2368 1838 100 0 0 VAL:off
p 2758 1846 100 0 -1 def(OUT):$(tcs)ngs1Follow.A
p 2696 1864 75 768 -1 pproc(OUT):NPP
p 2360 1848 75 1280 -1 pproc(SDIS):NPP
use estringouts 1727 157 100 0 unfollowAllAO
xform 0 1784 240
p 1592 206 100 0 0 VAL:off
p 1982 214 100 0 -1 def(OUT):$(tcs)aoFollow.A
p 1920 232 75 768 -1 pproc(OUT):NPP
p 1584 216 75 1280 -1 pproc(SDIS):NPP
use estringouts 1719 357 100 0 unfollowAllOiwfs
xform 0 1776 440
p 1584 406 100 0 0 VAL:off
p 1974 414 100 0 -1 def(OUT):$(tcs)oiwfsFollow.A
p 1912 432 75 768 -1 pproc(OUT):NPP
p 1576 416 75 1280 -1 pproc(SDIS):NPP
use estringouts 1719 549 100 0 unfollowAllPwfs2
xform 0 1776 632
p 1584 598 100 0 0 VAL:off
p 1974 606 100 0 -1 def(OUT):$(tcs)pwfs2Follow.A
p 1912 624 75 768 -1 pproc(OUT):NPP
p 1576 608 75 1280 -1 pproc(SDIS):NPP
use estringouts 1719 741 100 0 unfollowAllPwfs1
xform 0 1776 824
p 1584 790 100 0 0 VAL:off
p 1974 798 100 0 -1 def(OUT):$(tcs)pwfs1Follow.A
p 1912 816 75 768 -1 pproc(OUT):NPP
p 1576 800 75 1280 -1 pproc(SDIS):NPP
use estringouts 1719 957 100 0 unfollowAllM2
xform 0 1776 1040
p 1584 1006 100 0 0 VAL:off
p 1974 1014 100 0 -1 def(OUT):$(tcs)m2Follow.A
p 1912 1032 75 768 -1 pproc(OUT):NPP
p 1576 1016 75 1280 -1 pproc(SDIS):NPP
use estringouts 1719 1165 100 0 unfollowAllEncE
xform 0 1776 1248
p 1584 1214 100 0 0 VAL:off
p 1974 1222 100 0 -1 def(OUT):$(tcs)carouselMode.E
p 1912 1240 75 768 -1 pproc(OUT):NPP
p 1576 1224 75 1280 -1 pproc(SDIS):NPP
use estringouts 1711 1381 100 0 unfollowAllEncD
xform 0 1768 1464
p 1576 1430 100 0 0 VAL:off
p 1966 1438 100 0 -1 def(OUT):$(tcs)carouselMode.D
p 1904 1456 75 768 -1 pproc(OUT):NPP
p 1568 1440 75 1280 -1 pproc(SDIS):NPP
use estringouts 1703 1597 100 0 unfollowAllCass
xform 0 1760 1680
p 1568 1646 100 0 0 VAL:off
p 1958 1654 100 0 -1 def(OUT):$(tcs)crFollow.A
p 1896 1672 75 768 -1 pproc(OUT):NPP
p 1560 1656 75 1280 -1 pproc(SDIS):NPP
use estringouts 1695 1821 100 0 unfollowAllMount
xform 0 1752 1904
p 1560 1870 100 0 0 VAL:off
p 1950 1878 100 0 -1 def(OUT):$(tcs)mcFollow.A
p 1888 1896 75 768 -1 pproc(OUT):NPP
p 1552 1880 75 1280 -1 pproc(SDIS):NPP
[comments]
