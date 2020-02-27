[schematic2]
uniq 89
[tools]
[detail]
w 1192 2340 100 0 n#35 tcsCadOffsetPo.tcsCadOffsetPo#76.MESS 1904 2000 1984 2000 1984 2336 448 2336 448 1408 640 1408 eapply.apply65.INMB
w 1184 2308 100 0 n#34 tcsCadOffsetPo.tcsCadOffsetPo#76.VAL 1904 2080 1936 2080 1936 2304 480 2304 480 1440 640 1440 eapply.apply65.INPB
w 1296 1412 100 0 n#33 eapply.apply65.OCLB 1024 1408 1616 1408 1616 2000 1680 2000 tcsCadOffsetPo.tcsCadOffsetPo#76.ICID
w 1604 1784 100 0 n#32 eapply.apply65.OUTB 1024 1440 1600 1440 1600 2080 1680 2080 tcsCadOffsetPo.tcsCadOffsetPo#76.DIR
w 1016 2276 100 0 n#21 tcsCadOffsetPo.tcsCadOffsetPo#68.MESS 1504 2000 1568 2000 1568 2272 512 2272 512 1472 640 1472 eapply.apply65.INMA
w 1016 2244 100 0 n#20 tcsCadOffsetPo.tcsCadOffsetPo#68.VAL 1504 2080 1536 2080 1536 2240 544 2240 544 1504 640 1504 eapply.apply65.INPA
w 1188 1760 100 0 n#19 eapply.apply65.OCLA 1024 1472 1184 1472 1184 2000 1280 2000 tcsCadOffsetPo.tcsCadOffsetPo#68.ICID
w 1156 1816 100 0 n#18 eapply.apply65.OUTA 1024 1504 1152 1504 1152 2080 1280 2080 tcsCadOffsetPo.tcsCadOffsetPo#68.DIR
w 374 1570 100 0 n#4 inhier.ICID.P 80 1472 144 1472 144 1568 640 1568 eapply.apply65.CLID
w 342 1602 100 0 n#3 inhier.DIR.P 80 1600 640 1600 eapply.apply65.DIR
w 1934 1570 100 0 n#2 eapply.apply65.MESS 1024 1568 2880 1568 2880 1472 3040 1472 outhier.MESS.p
w 2014 1602 100 0 n#1 eapply.apply65.VAL 1024 1600 3040 1600 outhier.VAL.p
s 2848 264 200 0 Gemini TCS
s 2608 2432 100 0 $Id: tcsOffCommands5.sch,v 1.2 2010/01/28 13:45:02 ajf Exp $
s 2752 224 100 0 TCS commands
[cell use]
use tcsCadOffsetPo 1704 1656 100 0 tcsCadOffsetPo#76
xform 0 1792 1936
p 1664 1646 100 0 1 setb:cad offsetPoC2
use tcsCadOffsetPo 1304 1656 100 0 tcsCadOffsetPo#68
xform 0 1392 1936
p 1264 1646 100 0 1 setb:cad offsetPoC1
use eapply 664 968 100 0 apply65
xform 0 832 1328
p 780 1012 100 0 0 DESC:First apply for TCS commands
use outhier 3032 1560 100 0 VAL
xform 0 3024 1600
use outhier 3032 1432 100 0 MESS
xform 0 3024 1472
use inhier 88 1560 100 0 DIR
xform 0 80 1600
use inhier 88 1432 100 0 ICID
xform 0 80 1472
use bc200tr -48 -8 -100 0 frame
xform 0 1632 1296
[comments]
