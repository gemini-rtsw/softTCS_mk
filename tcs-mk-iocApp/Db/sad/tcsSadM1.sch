[schematic2]
uniq 3
[tools]
[detail]
s 1344 2336 100 0 SAD records that relate to M1
s 2512 2464 100 0 $Id: tcsSadM1.sch,v 1.2 1999/01/05 17:04:12 epics Exp $
s 2768 272 100 0 Gemini Telescope Control System
[cell use]
use esirs 2008 1816 100 0 m1GuideMode
xform 0 2192 1968
p 2064 2142 100 0 -1 DESC:Mirror guiding state
p 2064 1870 100 0 1 EGU:none
p 1920 1552 100 0 0 FDSC:figure corr. are being sent to M1
p 1920 1520 100 0 0 FTVL:STRING
p 2176 1744 100 0 0 PREC:2
p 2096 1808 100 1024 0 name:$(sad)$(I)
use esirs 1224 1816 100 0 m1SurfaceTarget
xform 0 1408 1968
p 1280 2142 100 0 -1 DESC:M1 Surface target temperature
p 1280 1870 100 0 1 EGU:deg C
p 1136 1552 100 0 0 FDSC:Set point for surface temp of M1
p 1136 1520 100 0 0 FTVL:DOUBLE
p 1392 1744 100 0 0 PREC:2
p 1312 1808 100 1024 0 name:$(sad)$(I)
use esirs 440 1816 100 0 m1BulkTarget
xform 0 624 1968
p 496 2142 100 0 -1 DESC:Mirror bulk temperature
p 496 1870 100 0 1 EGU:deg C
p 352 1552 100 0 0 FDSC:Set point for bulk temperature of M1
p 352 1520 100 0 0 FTVL:DOUBLE
p 608 1744 100 0 0 PREC:2
p 528 1808 100 1024 0 name:$(sad)$(I)
use bc200tr -64 -8 -100 0 frame
xform 0 1616 1296
[comments]
