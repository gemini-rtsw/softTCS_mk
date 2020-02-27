[schematic2]
uniq 113
[tools]
[detail]
w 1006 1612 100 0 n#112 ecad8.ecad8#0.OUTA 857 1601 1216 1601 1216 1568 1536 1568 eaos.rotatorGuideGain.SLNK
w 2018 1547 100 0 n#110 eaos.rotatorGuideGain.OUT 1792 1536 2304 1536 outhier.c#104.p
w 1028 1797 100 0 n#18 ecad8.ecad8#0.MESS 857 1793 1248 1793 1248 1728 1376 1728 outhier.MESS.p
w 1092 1829 100 0 n#17 ecad8.ecad8#0.VAL 857 1825 1376 1825 1376 1824 outhier.VAL.p
w 322 1715 100 0 n#4 inhier.ICID.P 228 1713 452 1713 452 1793 537 1793 ecad8.ecad8#0.ICID
w 322 1859 100 0 n#3 inhier.DIR.P 228 1857 452 1857 452 1825 537 1825 ecad8.ecad8#0.DIR
s 2464 2592 100 0 $Id: tcsCadRotGuideConfig.sch,v 1.1 2009/10/30 17:25:40 cjm Exp $
s 2704 400 100 0 Gemini Telescope Control System
[cell use]
use eaos 1536 1479 100 0 rotatorGuideGain
xform 0 1664 1568
p 1568 1648 100 0 -1 DESC:Rotator guide gain
p 1504 1294 100 0 0 EGU:units
p 1280 1550 100 0 0 OMSL:supervisory
p 1904 1552 100 0 -1 def(OUT):$(sad)rotatorGuideGain
p 1648 1472 100 1024 0 name:$(tcs)$(I)
p 1792 1536 75 768 -1 pproc(OUT):PP
use outhier 2272 1495 100 0 c#104
xform 0 2288 1536
use outhier 1368 1784 100 0 VAL
xform 0 1360 1824
use outhier 1368 1688 100 0 MESS
xform 0 1360 1728
use bc200tr -112 120 -100 0 frame
xform 0 1568 1424
use inhier 236 1817 100 0 DIR
xform 0 228 1857
use inhier 236 1673 100 0 ICID
xform 0 228 1713
use ecad8 561 873 100 0 ecad8#0
xform 0 697 1377
p 553 1919 100 0 -1 DESC:Implement the rotGuideConfig command
p 640 1600 100 0 1 FTVA:DOUBLE
p 640 1568 100 0 0 FTVB:STRING
p 640 1536 100 0 0 FTVC:STRING
p 640 1504 100 0 0 FTVD:STRING
p 633 1441 100 0 0 FTVE:STRING
p 633 1217 100 0 0 PREC:3
p 633 1087 100 0 1 SNAM:$(snam)
p 677 801 100 1024 1 name:$(tcs)$(cad)
p 857 1601 75 768 -1 pproc(OUTA):PP
p 857 1537 75 768 -1 pproc(OUTB):NPP
p 857 1473 75 768 -1 pproc(OUTC):NPP
p 857 1409 75 768 -1 pproc(OUTD):NPP
[comments]
