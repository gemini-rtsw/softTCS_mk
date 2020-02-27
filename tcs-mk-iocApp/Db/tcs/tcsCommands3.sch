[schematic2]
uniq 108
[tools]
[detail]
w 1570 475 100 0 n#107 tcsCommands32.tcsCommands32#98.MESS 2096 1680 2896 1680 2896 464 304 464 304 1936 640 1936 eapply.apply3.INMB
w 1570 443 100 0 n#106 tcsCommands32.tcsCommands32#98.VAL 2096 1776 2928 1776 2928 432 272 432 272 1968 640 1968 eapply.apply3.INPB
w 1570 411 100 0 n#105 tcsCommands31.tcsCommands31#97.MESS 2080 1936 2960 1936 2960 400 240 400 240 2000 640 2000 eapply.apply3.INMA
w 1570 379 100 0 n#104 tcsCommands31.tcsCommands31#97.VAL 2080 2032 2992 2032 2992 368 208 368 208 2032 640 2032 eapply.apply3.INPA
w 1170 1947 100 0 n#102 eapply.apply3.OCLB 1024 1936 1376 1936 1376 1680 1520 1680 tcsCommands32.tcsCommands32#98.ICID
w 1186 1979 100 0 n#101 eapply.apply3.OUTB 1024 1968 1408 1968 1408 1776 1520 1776 tcsCommands32.tcsCommands32#98.DIR
w 1202 2011 100 0 n#100 eapply.apply3.OCLA 1024 2000 1440 2000 1440 1936 1504 1936 tcsCommands31.tcsCommands31#97.ICID
w 1240 2043 100 0 n#99 eapply.apply3.OUTA 1024 2032 1504 2032 tcsCommands31.tcsCommands31#97.DIR
w 390 2098 100 0 n#4 inhier.ICID.P 112 2000 176 2000 176 2096 640 2096 eapply.apply3.CLID
w 358 2130 100 0 n#3 inhier.DIR.P 112 2128 640 2128 eapply.apply3.DIR
w 2014 2100 100 0 n#2 eapply.apply3.MESS 1024 2096 3040 2096 3040 2000 3136 2000 outhier.MESS.p
w 2062 2132 100 0 n#1 eapply.apply3.VAL 1024 2128 3136 2128 outhier.VAL.p
s 2656 2496 100 0 $Id: tcsCommands3.sch,v 1.3 2007/12/18 11:01:33 cjm Exp $
s 2864 240 200 0 Gemini TCS
s 2896 304 100 0 TCS commands
[cell use]
use tcsCommands32 1520 1591 100 0 tcsCommands32#98
xform 0 1808 1712
use tcsCommands31 1504 1847 100 0 tcsCommands31#97
xform 0 1792 1968
use outhier 3128 1960 100 0 MESS
xform 0 3120 2000
use outhier 3128 2088 100 0 VAL
xform 0 3120 2128
use inhier 120 1960 100 0 ICID
xform 0 112 2000
use inhier 120 2088 100 0 DIR
xform 0 112 2128
use eapply 664 1496 100 0 apply3
xform 0 832 1856
p 780 1540 100 0 0 DESC:Second apply for TCS commands
use bc200tr -32 24 -100 0 frame
xform 0 1648 1328
[comments]
