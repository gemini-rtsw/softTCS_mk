[schematic2]
uniq 96
[tools]
[detail]
w 2048 1220 100 0 n#55 eapply.apply32.OUTD 1024 1840 1312 1840 1312 1216 2832 1216 2832 1744 2896 1744 tcsVtCommands.tcsVtCommands#91.DIR
w 1704 2468 100 0 n#53 tcsVtCommands.tcsVtCommands#91.MESS 3120 1664 3200 1664 3200 2464 256 2464 256 1808 640 1808 eapply.apply32.INMD
w 1704 2436 100 0 n#52 tcsVtCommands.tcsVtCommands#91.VAL 3120 1744 3152 1744 3152 2432 304 2432 304 1840 640 1840 eapply.apply32.INPD
w 2064 1204 100 0 n#51 eapply.apply32.OCLD 1024 1808 1296 1808 1296 1200 2880 1200 2880 1664 2896 1664 tcsVtCommands.tcsVtCommands#91.ICID
w 1552 2403 100 0 n#48 tcsVtCommands.tcsVtCommands#90.MESS 2720 1824 2816 1824 2816 2400 336 2400 336 1872 640 1872 eapply.apply32.INMC
w 1560 2371 100 0 n#47 tcsVtCommands.tcsVtCommands#90.VAL 2720 1904 2784 1904 2784 2368 384 2368 384 1904 640 1904 eapply.apply32.INPC
w 1872 1235 100 0 n#46 eapply.apply32.OCLC 1024 1872 1360 1872 1360 1232 2432 1232 2432 1824 2496 1824 tcsVtCommands.tcsVtCommands#90.ICID
w 1872 1267 100 0 n#45 eapply.apply32.OUTC 1024 1904 1392 1904 1392 1264 2400 1264 2400 1904 2496 1904 tcsVtCommands.tcsVtCommands#90.DIR
w 1352 2339 100 0 n#43 eapply.apply32.INMB 640 1936 416 1936 416 2336 2336 2336 2336 1824 2240 1824 tcsVtCommands.tcsVtCommands#89.MESS
w 1360 2291 100 0 n#42 eapply.apply32.INPB 640 1968 464 1968 464 2288 2304 2288 2304 1904 2240 1904 tcsVtCommands.tcsVtCommands#89.VAL
w 1420 1603 100 0 n#41 eapply.apply32.OCLB 1024 1936 1424 1936 1424 1280 1984 1280 1984 1824 2016 1824 tcsVtCommands.tcsVtCommands#89.ICID
w 1176 2259 100 0 n#40 eapply.apply32.INMA 640 2000 496 2000 496 2256 1904 2256 1904 1808 1824 1808 tcsVtCommands.tcsVtCommands#88.MESS
w 1176 2227 100 0 n#38 eapply.apply32.INPA 640 2032 528 2032 528 2224 1872 2224 1872 1888 1824 1888 tcsVtCommands.tcsVtCommands#88.VAL
w 1232 2003 100 0 n#37 eapply.apply32.OCLA 1024 2000 1488 2000 1488 1808 1600 1808 tcsVtCommands.tcsVtCommands#88.ICID
w 1452 1627 100 0 n#13 eapply.apply32.OUTB 1024 1968 1456 1968 1456 1296 1952 1296 1952 1904 2016 1904 tcsVtCommands.tcsVtCommands#89.DIR
w 1248 2035 100 0 n#11 eapply.apply32.OUTA 1024 2032 1520 2032 1520 1888 1600 1888 tcsVtCommands.tcsVtCommands#88.DIR
w 390 2098 100 0 n#4 inhier.ICID.P 112 2000 176 2000 176 2096 640 2096 eapply.apply32.CLID
w 358 2130 100 0 n#3 inhier.DIR.P 112 2128 640 2128 eapply.apply32.DIR
w 2014 2100 100 0 n#2 eapply.apply32.MESS 1024 2096 3040 2096 3040 2000 3136 2000 outhier.MESS.p
w 2062 2132 100 0 n#1 eapply.apply32.VAL 1024 2128 3136 2128 outhier.VAL.p
s 2656 2496 100 0 $Id: tcsCommands32.sch,v 1.2 2010/01/28 13:45:00 ajf Exp $
s 2864 240 200 0 Gemini TCS
s 2896 304 100 0 TCS commands
[cell use]
use tcsVtCommands 2896 1319 100 0 tcsVtCommands#91
xform 0 3008 1600
p 2928 1520 100 0 -1 seta:vt g4
p 2928 1488 100 0 -1 setb:vtnum 10
p 2928 1456 100 0 -1 setc:tag G4
p 2928 1424 100 0 -1 setd:apply apply324
use tcsVtCommands 2496 1479 100 0 tcsVtCommands#90
xform 0 2608 1760
p 2528 1680 100 0 -1 seta:vt g3
p 2528 1648 100 0 -1 setb:vtnum 9
p 2528 1616 100 0 -1 setc:tag G3
p 2528 1584 100 0 -1 setd:apply apply323
use tcsVtCommands 2016 1479 100 0 tcsVtCommands#89
xform 0 2128 1760
p 2048 1680 100 0 -1 seta:vt g2
p 2048 1648 100 0 -1 setb:vtnum 8
p 2048 1616 100 0 -1 setc:tag G2
p 2048 1584 100 0 -1 setd:apply apply322
use tcsVtCommands 1600 1463 100 0 tcsVtCommands#88
xform 0 1712 1744
p 1632 1664 100 0 -1 seta:vt g1
p 1632 1632 100 0 -1 setb:vtnum 7
p 1632 1600 100 0 -1 setc:tag G1
p 1632 1568 100 0 -1 setd:apply apply321
use outhier 3128 1960 100 0 MESS
xform 0 3120 2000
use outhier 3128 2088 100 0 VAL
xform 0 3120 2128
use inhier 120 1960 100 0 ICID
xform 0 112 2000
use inhier 120 2088 100 0 DIR
xform 0 112 2128
use eapply 664 1496 100 0 apply32
xform 0 832 1856
p 780 1540 100 0 0 DESC:Second apply for TCS commands
use bc200tr -32 24 -100 0 frame
xform 0 1648 1328
[comments]
