[schematic2]
uniq 1335
[tools]
[detail]
w 1716 2987 100 0 n#1334 junction 1632 3232 1632 2976 1872 2976 egenSub.addtrm.SLNK
w 1516 3243 100 0 n#1334 estringouts.name.FLNK 1472 3232 1632 3232 1632 3648 1488 3648 ecalcs.netint.FLNK
w 1548 3211 100 0 n#1333 estringouts.name.OUT 1472 3200 1696 3200 1696 3680 1872 3680 egenSub.addtrm.A
w 1692 3595 100 0 n#1329 ecalcs.netint.VAL 1488 3616 1584 3616 1584 3584 1872 3584 egenSub.addtrm.INPB
w 1044 3819 100 0 n#1325 ecalcs.netint.INPA 1200 3808 960 3808 960 3600 816 3600 eaos.value.VAL
w 924 3643 100 0 n#1323 eaos.value.FLNK 816 3632 1104 3632 1104 3424 1200 3424 ecalcs.netint.SLNK
w 38 3643 -100 0 SESSION inhier.SESSION.P 0 3632 160 3632 eaos.snew.SLNK
w 4 3771 -100 0 n#1327 inhier.NEW.P 0 3760 80 3760 80 3664 160 3664 eaos.snew.DOL
w 452 3611 100 0 n#1326 eaos.snew.OUT 416 3600 560 3600 eaos.value.SLNK
[cell use]
use estringouts 1216 3143 100 0 name
xform 0 1344 3216
use egenSub 1872 2887 100 0 addtrm
xform 0 2016 3312
p 1649 2661 100 0 0 FTA:STRING
p 2000 2864 100 0 1 SNAM:tcsModel
use eaos 560 3511 100 0 value
xform 0 688 3600
p 340 3786 100 0 0 DESC:net $(descr)
p 528 3326 100 0 0 EGU:$(units)
p 304 3582 100 0 0 OMSL:closed_loop
p 304 3454 100 0 0 PREC:3
p 880 3568 100 0 0 def(OUT):0.00000000000000e+00
p 816 3568 75 768 -1 pproc(OUT):PP
use eaos 160 3543 100 0 snew
xform 0 288 3632
p -60 3818 100 0 0 DESC:New value of pointing parameter
p 128 3358 100 0 0 EGU:$(units)
p -96 3614 100 0 0 OMSL:closed_loop
p 128 3664 75 1280 -1 pproc(DOL):PP
p 416 3600 75 768 -1 pproc(OUT):PP
use inhier -16 3591 100 0 SESSION
xform 0 0 3632
use inhier -16 3719 100 0 NEW
xform 0 0 3760
use ecalcs 1200 3335 100 0 netint
xform 0 1344 3600
p 1296 3712 100 0 -1 CALC:A*$(scale)
p 993 3766 100 0 0 DESC:net value of $(descr)
p 912 3486 100 0 0 EGU:
p 1312 3584 100 0 0 PREC:0
use eborderB -528 1943 100 0 eborderB#1308
xform 0 1152 3248
p 1744 2576 100 768 -1 author:D Terrett
p 1728 2544 100 768 -1 date:8 Aug 1997
p 1888 2624 200 768 -1 file:tcsPointParam.sch
p 1680 2672 100 0 -1 page:
p 1600 2688 100 0 -1 pages:
p 2320 2096 100 0 0 revision:$Revision: 1.3 $
p 1744 2736 150 768 -1 system:
[comments]
