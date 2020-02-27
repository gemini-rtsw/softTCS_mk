[schematic2]
uniq 106
[tools]
[detail]
w 1842 1259 100 0 n#105 elongouts.rotatorGuideState.OUT 1664 1248 2080 1248 outhier.c#104.p
w 974 1580 100 0 n#103 ecad8.ecad8#0.VALB 857 1569 1152 1569 1152 1312 1408 1312 elongouts.rotatorGuideState.DOL
w 1490 1419 100 0 n#102 estringouts.rotatorGuideMode.FLNK 1664 1568 1792 1568 1792 1408 1248 1408 1248 1280 1408 1280 elongouts.rotatorGuideState.SLNK
w 1006 1644 100 0 n#100 ecad8.ecad8#0.VALA 857 1633 1216 1633 1216 1584 1408 1584 estringouts.rotatorGuideMode.DOL
w 1012 972 100 0 n#99 ecad8.ecad8#0.STLK 857 961 1216 961 1216 1552 1408 1552 estringouts.rotatorGuideMode.SLNK
w 1028 1797 100 0 n#18 ecad8.ecad8#0.MESS 857 1793 1248 1793 1248 1728 1376 1728 outhier.MESS.p
w 1092 1829 100 0 n#17 ecad8.ecad8#0.VAL 857 1825 1376 1825 1376 1824 outhier.VAL.p
w 322 1715 100 0 n#4 inhier.ICID.P 228 1713 452 1713 452 1793 537 1793 ecad8.ecad8#0.ICID
w 322 1859 100 0 n#3 inhier.DIR.P 228 1857 452 1857 452 1825 537 1825 ecad8.ecad8#0.DIR
s 656 512 100 0 clear and start.
s 640 544 100 0 is not an option as these would fire for both 
s 640 576 100 0 Driving the ao records direct from the output links
s 640 608 100 0 successful start from setting all the ao records to 0.0.
s 640 640 100 0 This in particular prevents a clear issued before a 
s 640 672 100 0 The ao records are only triggerred by a successful start.
s 2704 400 100 0 Gemini Telescope Control System
s 2464 2592 100 0 $Id: tcsCadRotGuideMode.sch,v 1.1 2009/10/30 17:26:45 cjm Exp $
[cell use]
use outhier 1368 1688 100 0 MESS
xform 0 1360 1728
use outhier 1368 1784 100 0 VAL
xform 0 1360 1824
use outhier 2048 1207 100 0 c#104
xform 0 2064 1248
use elongouts 1408 1191 100 0 rotatorGuideState
xform 0 1536 1280
p 1424 1360 100 0 -1 DESC:Rotator guiding flag
p 1248 1198 100 0 0 OMSL:closed_loop
p 1744 1280 100 0 -1 def(OUT):$(sad)rotatorGuideState
p 1520 1184 100 1024 0 name:$(tcs)$(I)
p 1664 1248 75 768 -1 pproc(OUT):PP
use estringouts 1408 1479 100 0 rotatorGuideMode
xform 0 1536 1552
p 1424 1632 100 0 -1 DESC:Rotator guide mode
p 1344 1358 100 0 0 OMSL:closed_loop
p 1344 1518 100 0 0 VAL:Off
p 1520 1472 100 1024 0 name:$(tcs)$(I)
use bc200tr -112 120 -100 0 frame
xform 0 1568 1424
use inhier 236 1673 100 0 ICID
xform 0 228 1713
use inhier 236 1817 100 0 DIR
xform 0 228 1857
use ecad8 561 873 100 0 ecad8#0
xform 0 697 1377
p 553 1919 100 0 -1 DESC:Implement the rotGuideMode command
p 640 1600 100 0 1 FTVA:STRING
p 640 1568 100 0 1 FTVB:LONG
p 640 1536 100 0 0 FTVC:STRING
p 640 1504 100 0 0 FTVD:STRING
p 633 1441 100 0 0 FTVE:STRING
p 633 1217 100 0 0 PREC:3
p 633 1087 100 0 1 SNAM:$(snam)
p 677 801 100 1024 1 name:$(tcs)$(cad)
p 857 1601 75 768 -1 pproc(OUTA):NPP
p 857 1537 75 768 -1 pproc(OUTB):NPP
p 857 1473 75 768 -1 pproc(OUTC):NPP
p 857 1409 75 768 -1 pproc(OUTD):NPP
[comments]
