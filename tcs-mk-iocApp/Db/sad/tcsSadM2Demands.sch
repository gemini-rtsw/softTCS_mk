[schematic2]
uniq 9
[tools]
[detail]
s 3776 528 100 0 Gemini Telescope Control System
s 3632 2720 100 0 tcsSadM2Demands.sch
s 3856 464 100 0 M2 Demand Data
s 1312 2688 100 0 The records in this column are written
s 1312 2656 100 0 by the chopRelative command
s 2048 2688 100 0 The records in this column are written
s 2048 2656 100 0 by the chopConfig command
[cell use]
use esirs 1352 2296 100 0 chopThrow
xform 0 1536 2448
p 1424 2606 100 0 -1 DESC:M2 chop throw demand
p 1424 2542 100 0 1 EGU:arcsec
p 1279 2176 100 0 0 FDSC:Relative chop throw
p 1279 1968 100 0 0 FTVL:DOUBLE
p 1424 2510 100 0 1 PREC:3
p 1279 1295 100 0 0 PV:$(sad)
use esirs 1352 1848 100 0 chopPA
xform 0 1536 2000
p 1392 2174 100 0 -1 DESC:Chop position angle demand
p 1424 2094 100 0 1 EGU:degrees
p 1279 1728 100 0 0 FDSC:Position angle for relative chop
p 1279 1520 100 0 0 FTVL:DOUBLE
p 1424 2062 100 0 1 PREC:6
p 1279 847 100 0 0 PV:$(sad)
use esirs 1368 1416 100 0 chopFrame
xform 0 1552 1568
p 1504 1726 100 0 -1 DESC:Chop frame
p 1295 1296 100 0 0 FDSC:Chop frame for relative chopping
p 1295 415 100 0 0 PV:$(sad)
use esirs 1384 1000 100 0 chopEquinox
xform 0 1568 1152
p 1504 1310 100 0 -1 DESC:Chop Equinox
p 1311 -1 100 0 0 PV:$(sad)
use esirs 1384 552 100 0 chopWavelength
xform 0 1568 704
p 1488 862 100 0 -1 DESC:Chop wavelength
p 1440 798 100 0 1 EGU:microns
p 1311 432 100 0 0 FDSC:Chop wavelength for relative chopping
p 1311 224 100 0 0 FTVL:DOUBLE
p 1440 766 100 0 1 PREC:3
p 1311 -449 100 0 0 PV:$(sad)
use esirs 2072 2296 100 0 chopMode
xform 0 2256 2448
p 2192 2606 100 0 -1 DESC:Chop mode
p 1999 2176 100 0 0 FDSC:chopping, 2posn,3posn,triangular
p 1999 1295 100 0 0 PV:$(sad)
use esirs 2072 1848 100 0 chopSync
xform 0 2256 2000
p 2176 2158 100 0 -1 DESC:Chop sync source
p 1999 1728 100 0 0 FDSC:Sync source e.g. SCS, GNIRS etc.
p 1999 847 100 0 0 PV:$(sad)
use esirs 2072 1416 100 0 chopFreq
xform 0 2256 1568
p 2192 1726 100 0 -1 DESC:Chop frequency
p 2144 1662 100 0 1 EGU:Hz
p 1999 1296 100 0 0 FDSC:frequency of chop
p 1999 1088 100 0 0 FTVL:DOUBLE
p 2144 1630 100 0 1 PREC:3
p 1999 415 100 0 0 PV:$(sad)
use bc200tr 928 248 -100 0 frame
xform 0 2608 1552
[comments]
