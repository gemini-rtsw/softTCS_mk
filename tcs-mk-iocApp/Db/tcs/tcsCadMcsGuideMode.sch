[schematic2]
uniq 63
[tools]
[detail]
w 1432 635 100 0 n#62 ecad8.ecad8#0.VALD 857 1441 1056 1441 1056 624 1856 624 eaos.p2weight.DOL
w 1472 891 100 0 n#61 ecad8.ecad8#0.VALC 857 1505 1152 1505 1152 880 1840 880 eaos.p1weight.DOL
w 1904 699 100 0 n#60 eaos.p1weight.FLNK 2096 880 2144 880 2144 688 1712 688 1712 592 1856 592 eaos.p2weight.SLNK
w 1896 1051 100 0 n#59 elongouts.absorbTipTiltFlag.FLNK 2080 1184 2144 1184 2144 1040 1696 1040 1696 848 1840 848 eaos.p1weight.SLNK
w 1156 972 100 0 n#56 ecad8.ecad8#0.STLK 857 961 1504 961 1504 1440 1824 1440 estringouts.absorbTipTilt.SLNK
w 1520 1195 100 0 n#53 ecad8.ecad8#0.VALE 864 1376 1264 1376 1264 1184 1824 1184 elongouts.absorbTipTiltFlag.DOL
w 1920 1314 100 0 n#52 estringouts.absorbTipTilt.FLNK 2080 1456 2176 1456 2176 1312 1712 1312 1712 1152 1824 1152 elongouts.absorbTipTiltFlag.SLNK
w 1544 1474 100 0 n#51 ecad8.ecad8#0.VALA 857 1633 1312 1633 1312 1472 1824 1472 estringouts.absorbTipTilt.DOL
w 1028 1797 100 0 n#18 ecad8.ecad8#0.MESS 857 1793 1248 1793 1248 1728 1376 1728 outhier.MESS.p
w 1092 1829 100 0 n#17 ecad8.ecad8#0.VAL 857 1825 1376 1825 1376 1824 outhier.VAL.p
w 322 1715 100 0 n#4 inhier.ICID.P 228 1713 452 1713 452 1793 537 1793 ecad8.ecad8#0.ICID
w 322 1859 100 0 n#3 inhier.DIR.P 228 1857 452 1857 452 1825 537 1825 ecad8.ecad8#0.DIR
s 2848 208 100 0 Gemini Telescope Control System
s 896 2352 100 0 This schematic implements an internal TCS command i.e. one
s 896 2320 100 0 that sends no commands to any TCS subsystems. 
s 896 2288 100 0 The CAR record is set to BUSY by the start link of the CAD. It
s 896 2256 100 0 is set to IDLE after a short time interval set by the 
s 896 2224 100 0 delay parameter. In practice the command is already 
s 896 2192 100 0 complete by the time the CAD subroutine is executed but
s 896 2160 100 0 the seq record ensures that a Busy to Idle transition is
s 896 2128 100 0 generated.
s 2592 2400 100 0 $Id: tcsCadMcsGuideMode.sch,v 1.2 1999/01/24 00:41:01 dlt Exp $
[cell use]
use eaos 1856 503 100 0 p2weight
xform 0 1984 592
p 1600 574 100 0 0 OMSL:closed_loop
p 2176 544 100 0 -1 def(OUT):$(tcs)ak:guide:p2weight
p 2112 560 75 768 -1 pproc(OUT):PP
use eaos 1840 759 100 0 p1weight
xform 0 1968 848
p 1584 830 100 0 0 OMSL:closed_loop
p 2160 800 100 0 -1 def(OUT):$(tcs)ak:guide:p1weight
p 2096 816 75 768 -1 pproc(OUT):PP
use elongouts 1848 1064 100 0 absorbTipTiltFlag
xform 0 1952 1152
p 1744 1246 100 0 -1 DESC:Toggle absorption of tip/tilt into mount
p 1664 1070 100 0 0 OMSL:closed_loop
p 2176 1118 100 0 -1 def(OUT):$(tcs)ak:guide:enable
p 1936 1056 100 1024 0 name:$(tcs)$(I)
p 2080 1120 75 768 -1 pproc(OUT):PP
use estringouts 1848 1368 100 0 absorbTipTilt
xform 0 1952 1440
p 1856 1518 100 0 -1 DESC:Absorb tip/tilt mode
p 1760 1246 100 0 0 OMSL:closed_loop
p 1760 1406 100 0 0 VAL:Off
p 2224 1422 100 0 -1 def(OUT):$(sad)absorbTipTilt
p 2096 1360 100 1024 0 name:$(tcs)$(I)
p 2080 1424 75 768 -1 pproc(OUT):PP
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
p 553 1919 100 0 -1 DESC:Implement the mountGuideMode command
p 672 1566 100 0 0 FTVB:STRING
p 720 1504 100 0 -1 FTVC:DOUBLE
p 704 1424 100 0 -1 FTVD:DOUBLE
p 720 1360 100 0 -1 FTVE:LONG
p 633 1217 100 0 0 PREC:2
p 633 1087 100 0 1 SNAM:$(snam)
p 928 1472 100 0 0 def(OUTC):0.0
p 944 1408 100 0 0 def(OUTD):0.0
p 677 801 100 1024 1 name:$(tcs)$(cad)
use bc200tr 16 -72 -100 0 frame
xform 0 1696 1232
[comments]
