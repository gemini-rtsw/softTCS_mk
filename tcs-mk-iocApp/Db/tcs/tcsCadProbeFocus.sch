[schematic2]
uniq 49
[tools]
[detail]
w 996 1644 100 0 n#48 ecad8.ecad8#0.VALA 857 1633 1184 1633 1184 1408 1408 1408 eaos.Zoffset.DOL
w 1188 1163 100 0 n#47 ecad8.ecad8#0.STLK 857 961 1184 961 1184 1376 1408 1376 eaos.Zoffset.SLNK
w 1028 1797 100 0 n#18 ecad8.ecad8#0.MESS 857 1793 1248 1793 1248 1728 1376 1728 outhier.MESS.p
w 1092 1829 100 0 n#17 ecad8.ecad8#0.VAL 857 1825 1376 1825 1376 1824 outhier.VAL.p
w 322 1715 100 0 n#4 inhier.ICID.P 228 1713 452 1713 452 1793 537 1793 ecad8.ecad8#0.ICID
w 322 1859 100 0 n#3 inhier.DIR.P 228 1857 452 1857 452 1825 537 1825 ecad8.ecad8#0.DIR
s 1440 2208 100 0 demands are sent to the probes.
s 1440 2240 100 0 The CAd routine simply stores the offset for later use when
s 1440 2272 100 0 This schematic implements the focus offset command for each WFS.
s 2592 2400 100 0 $Id: tcsCadProbeFocus.sch,v 1.1.1.1 1998/11/08 00:20:30 epics Exp $
s 2848 208 100 0 Gemini Telescope Control System
[cell use]
use eaos 1408 1287 100 0 Zoffset
xform 0 1536 1376
p 1440 1472 100 0 -1 DESC:Probe focus offset
p 1376 1102 100 0 0 EGU:mm
p 1152 814 100 0 0 MDEL:0.0005
p 1152 1358 100 0 0 OMSL:closed_loop
p 1152 1230 100 0 0 PREC:3
p 1520 1280 100 1024 0 name:$(top)$(I)
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
p 553 1919 100 0 -1 DESC:Implement a TCS internal command
p 704 1616 100 0 -1 FTVA:DOUBLE
p 633 1473 100 0 0 FTVD:STRING
p 633 1441 100 0 0 FTVE:STRING
p 633 1217 100 0 0 PREC:2
p 633 1087 100 0 1 SNAM:$(snam)
p 677 801 100 1024 1 name:$(tcs)$(cad)
use bc200tr 16 -72 -100 0 frame
xform 0 1696 1232
[comments]
