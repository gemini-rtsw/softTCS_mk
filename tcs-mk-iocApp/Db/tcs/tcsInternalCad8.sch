[schematic2]
uniq 19
[tools]
[detail]
w 1160 1794 100 0 n#18 ecad8.ecad8#0.MESS 1120 1792 1248 1792 1248 1728 1376 1728 outhier.MESS.p
w 1224 1826 100 0 n#17 ecad8.ecad8#0.VAL 1120 1824 1376 1824 outhier.VAL.p
w 478 1714 100 0 n#4 inhier.ICID.P 384 1712 608 1712 608 1792 800 1792 ecad8.ecad8#0.ICID
w 478 1858 100 0 n#3 inhier.DIR.P 384 1856 608 1856 608 1824 800 1824 ecad8.ecad8#0.DIR
s 2608 2400 100 0 $Id: tcsInternalCad8.sch,v 1.1.1.1 1998/11/08 00:20:38 epics Exp $
s 2848 208 100 0 Gemini Telescope Control System
[cell use]
use outhier 1368 1688 100 0 MESS
xform 0 1360 1728
use outhier 1368 1784 100 0 VAL
xform 0 1360 1824
use inhier 392 1672 100 0 ICID
xform 0 384 1712
use inhier 392 1816 100 0 DIR
xform 0 384 1856
use ecad8 824 872 100 0 ecad8#0
xform 0 960 1376
p 816 1918 100 0 -1 DESC:Implement a TCS internal command
p 896 1216 100 0 0 PREC:2
p 896 1086 100 0 1 SNAM:$(snam)
p 940 800 100 1024 1 name:$(tcs)$(cad)
use bc200tr 16 -72 -100 0 frame
xform 0 1696 1232
[comments]
