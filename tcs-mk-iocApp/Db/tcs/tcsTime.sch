[schematic2]
uniq 7
[tools]
[detail]
w 2126 1787 100 0 n#6 esirs.health.OMSS 1872 1872 2032 1872 2032 1776 2256 1776 outhier.OMSS.p
w 2046 1906 100 0 n#3 esirs.health.VAL 1872 1904 2256 1904 outhier.TIMEHEALTH.p
s 2096 1232 100 0 Gemini Telescope Control System
s 1840 2048 100 0 $Id: tcsTime.sch,v 1.2 2002/02/22 17:48:19 cjm Exp $
[cell use]
use outhier 2224 1735 100 0 OMSS
xform 0 2240 1776
use esirs 1480 1688 100 0 health
xform 0 1664 1840
use outhier 2248 1864 100 0 TIMEHEALTH
xform 0 2240 1904
use ba200tr 1024 952 -100 0 frame
xform 0 1824 1576
use ebos 1560 1416 100 0 intSimulate
xform 0 1664 1504
p 1304 1660 100 0 0 DESC:Time system simulate flag
p 1536 1342 100 0 1 ONAM:True
p 1712 1342 100 0 1 OSV:MINOR
p 1536 1374 100 0 1 ZNAM:False
p 1712 1374 100 0 1 ZSV:NO_ALARM
[comments]
