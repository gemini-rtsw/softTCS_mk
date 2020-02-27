[schematic2]
uniq 128
[tools]
[detail]
w 1522 507 100 0 n#127 tcsCommands42.tcsCommands42#121.MESS 2048 1664 2768 1664 2768 496 336 496 336 1936 640 1936 eapply.apply4.INMB
w 1522 475 100 0 n#126 tcsCommands42.tcsCommands42#121.VAL 2048 1760 2800 1760 2800 464 304 464 304 1968 640 1968 eapply.apply4.INPB
w 1522 443 100 0 n#125 tcsCommands41.tcsCommands41#118.MESS 2048 1936 2832 1936 2832 432 272 432 272 2000 640 2000 eapply.apply4.INMA
w 1522 411 100 0 n#124 tcsCommands41.tcsCommands41#118.VAL 2048 2032 2864 2032 2864 400 240 400 240 2032 640 2032 eapply.apply4.INPA
w 1162 1947 100 0 n#123 eapply.apply4.OCLB 1024 1936 1360 1936 1360 1664 1472 1664 tcsCommands42.tcsCommands42#121.ICID
w 1178 1979 100 0 n#122 eapply.apply4.OUTB 1024 1968 1392 1968 1392 1760 1472 1760 tcsCommands42.tcsCommands42#121.DIR
w 1194 2011 100 0 n#120 eapply.apply4.OCLA 1024 2000 1424 2000 1424 1936 1472 1936 tcsCommands41.tcsCommands41#118.ICID
w 1218 2043 100 0 n#119 eapply.apply4.OUTA 1024 2032 1472 2032 tcsCommands41.tcsCommands41#118.DIR
w 402 2107 100 0 n#110 inhier.ICID.P 176 2000 224 2000 224 2096 640 2096 eapply.apply4.CLID
w 390 2139 100 0 n#3 inhier.DIR.P 176 2128 640 2128 eapply.apply4.DIR
w 2014 2100 100 0 n#2 eapply.apply4.MESS 1024 2096 3040 2096 3040 2000 3136 2000 outhier.MESS.p
w 2062 2132 100 0 n#1 eapply.apply4.VAL 1024 2128 3136 2128 outhier.VAL.p
s 2544 2528 100 0 $Id: tcsCommands4.sch,v 1.3 2007/12/18 11:01:33 cjm Exp $
s 2864 272 200 0 Gemini TCS
s 2896 336 100 0 TCS commands
[cell use]
use tcsCommands42 1472 1575 100 0 tcsCommands42#121
xform 0 1760 1696
use tcsCommands41 1472 1847 100 0 tcsCommands41#118
xform 0 1760 1968
use bc200tr 48 56 -100 0 frame
xform 0 1728 1360
use outhier 3128 1960 100 0 MESS
xform 0 3120 2000
use outhier 3128 2088 100 0 VAL
xform 0 3120 2128
use inhier 184 1960 100 0 ICID
xform 0 176 2000
use inhier 184 2088 100 0 DIR
xform 0 176 2128
use eapply 664 1496 100 0 apply4
xform 0 832 1856
p 780 1540 100 0 0 DESC:Second apply for TCS commands
[comments]
