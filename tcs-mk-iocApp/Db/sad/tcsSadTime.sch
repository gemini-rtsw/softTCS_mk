[schematic2]
uniq 15
[tools]
[detail]
w 2192 1355 100 0 n#14 esirs.MJD.FLNK 2128 1344 2304 1344 outhier.FLNK.p
w 1584 1195 100 0 n#12 esirs.date.FLNK 1392 1344 1504 1344 1504 1184 1712 1184 esirs.MJD.SLNK
w 1768 1506 100 0 n#10 esirs.LST.FLNK 2816 1824 2880 1824 2880 1504 704 1504 704 1184 976 1184 esirs.date.SLNK
w 2278 1666 100 0 n#9 esirs.UTC.FLNK 2128 1824 2192 1824 2192 1664 2400 1664 esirs.LST.SLNK
w 1590 1666 100 0 n#8 esirs.localTime.FLNK 1392 1824 1504 1824 1504 1664 1712 1664 esirs.UTC.SLNK
w 750 1666 100 0 n#7 inhier.SLNK.P 560 1664 976 1664 esirs.localTime.SLNK
s 272 2144 100 0 name (but different prefix) in the main TCS database.
s 272 2176 100 0 SLNK field. Each then updates from a record of the same
s 272 2208 100 0 These records should be driven at 1 Hz by the incoming
s 1392 2192 300 0 Date and Time SAD records
s 2784 2368 100 0 tcsSadTime.sch
s 2880 112 100 0 Gemini Telescope Control System
s 2896 176 100 0 Time and Date records
[cell use]
use esirs 1000 1096 100 0 date
xform 0 1184 1248
p 1136 1406 100 0 -1 DESC:Current date
p 912 832 100 0 0 FDSC:Current date
p 784 1342 100 0 -1 def(INP):$(top)date
p 1088 1088 100 1024 0 name:$(sad)$(I)
p 1168 640 100 0 0 typ(INP):path
use esirs 2424 1576 100 0 LST
xform 0 2608 1728
p 2608 1886 100 0 -1 DESC:LST
p 2336 1312 100 0 0 FDSC:Local Sidereal Time
p 2208 1822 100 0 -1 def(INP):$(top)LST
p 2512 1568 100 1024 0 name:$(sad)$(I)
p 2592 1120 100 0 0 typ(INP):path
use esirs 1736 1576 100 0 UTC
xform 0 1920 1728
p 1920 1886 100 0 -1 DESC:UTC
p 1648 1312 100 0 0 FDSC:UTC
p 1520 1822 100 0 -1 def(INP):$(top)UTC
p 1824 1568 100 1024 0 name:$(sad)$(I)
p 1904 1120 100 0 0 typ(INP):path
use esirs 1000 1576 100 0 localTime
xform 0 1184 1728
p 1136 1886 100 0 -1 DESC:Local time
p 912 1312 100 0 0 FDSC:Local time
p 720 1822 100 0 -1 def(INP):$(top)localTime
p 1088 1568 100 1024 0 name:$(sad)$(I)
p 1168 1120 100 0 0 typ(INP):path
use esirs 1712 1095 100 0 MJD
xform 0 1920 1248
p 1904 1408 100 0 -1 DESC:MJD
p 1648 896 100 0 0 EGU:days
p 1648 832 100 0 0 FDSC:Modified Julian Date on UTC timescale
p 1648 800 100 0 0 FTVL:DOUBLE
p 1904 1024 100 0 0 PREC:14
p 1520 1344 100 0 -1 def(INP):$(top)MJD
p 1824 1088 100 1024 0 name:$(sad)$(I)
use outhier 2296 1304 100 0 FLNK
xform 0 2288 1344
use inhier 568 1624 100 0 SLNK
xform 0 560 1664
use bc200tr 64 -104 -100 0 frame
xform 0 1744 1200
[comments]
