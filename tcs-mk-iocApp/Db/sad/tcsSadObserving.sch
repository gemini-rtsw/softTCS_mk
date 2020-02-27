[schematic2]
uniq 9
[tools]
[detail]
s 1184 2272 200 0 SIR records related to observing
s 2592 2432 100 0 $Id: tcsSadObserving.sch,v 1.1.1.1 1998/11/08 00:20:16 epics Exp $
s 2816 240 100 0 Gemini Telescope Control System
[cell use]
use esirs 1827 1220 100 0 rotPaStart
xform 0 2011 1372
p 1867 1530 100 0 -1 DESC:Rotator PA at start of exposure
p 1947 1322 100 0 1 EGU:degrees
p 1739 956 100 0 0 FDSC:Rotator PA at start of exposure
p 1739 924 100 0 0 FTVL:DOUBLE
p 1915 1212 100 1024 0 name:$(sad)$(I)
p 1995 1148 100 0 0 PREC:2
use esirs 2499 1220 100 0 rotPaEnd
xform 0 2683 1372
p 2539 1530 100 0 -1 DESC:Rotator PA at end of exposure
p 2619 1322 100 0 1 EGU:degrees
p 2411 956 100 0 0 FDSC:Rotator PA at end of exposure
p 2411 924 100 0 0 FTVL:DOUBLE
p 2587 1212 100 1024 0 name:$(sad)$(I)
p 2667 1148 100 0 0 PREC:2
use esirs 1816 712 100 0 airMass
xform 0 2000 864
p 1856 1022 100 0 -1 DESC:Relative airmass during exposure
p 1936 814 100 0 1 EGU:none
p 1728 448 100 0 0 FDSC:Relative airmass through exposure
p 1728 416 100 0 0 FTVL:DOUBLE
p 1904 704 100 1024 0 name:$(sad)$(I)
p 1984 640 100 0 0 PREC:3
use esirs 1144 712 100 0 amEnd
xform 0 1328 864
p 1184 1022 100 0 -1 DESC:Relative airmass at end of exposure
p 1264 814 100 0 1 EGU:none
p 1056 448 100 0 0 FDSC:Relative airmass at end of exposure
p 1056 416 100 0 0 FTVL:DOUBLE
p 1232 704 100 1024 0 name:$(sad)$(I)
p 1312 640 100 0 0 PREC:3
use esirs 472 712 100 0 amStart
xform 0 656 864
p 512 1022 100 0 -1 DESC:Relative airmass at start of exposure
p 592 814 100 0 1 EGU:none
p 384 448 100 0 0 FDSC:Relative airmass at start of exposure
p 384 416 100 0 0 FTVL:DOUBLE
p 560 704 100 1024 0 name:$(sad)$(I)
p 640 640 100 0 0 PREC:3
use esirs 1144 1224 100 0 zdEnd
xform 0 1328 1376
p 1184 1534 100 0 -1 DESC:Zenith distance at end of exposure
p 1264 1326 100 0 1 EGU:degrees
p 1056 960 100 0 0 FDSC:Zenith distance at end of exposure
p 1056 928 100 0 0 FTVL:DOUBLE
p 1232 1216 100 1024 0 name:$(sad)$(I)
p 1312 1152 100 0 0 PREC:2
use esirs 472 1224 100 0 zdStart
xform 0 656 1376
p 512 1534 100 0 -1 DESC:Zenith distance at start of exposure
p 592 1326 100 0 1 EGU:degrees
p 384 960 100 0 0 FDSC:Zenith distance at start of exposure
p 384 928 100 0 0 FTVL:DOUBLE
p 560 1216 100 1024 0 name:$(sad)$(I)
p 640 1152 100 0 0 PREC:2
use esirs 1144 1736 100 0 azEnd
xform 0 1328 1888
p 1184 2046 100 0 -1 DESC:Azimuth at end of exposure
p 1264 1838 100 0 1 EGU:degrees
p 1056 1472 100 0 0 FDSC:Azimuth at end of exposure
p 1056 1440 100 0 0 FTVL:DOUBLE
p 1232 1728 100 1024 0 name:$(sad)$(I)
p 1312 1664 100 0 0 PREC:2
use esirs 472 1736 100 0 azStart
xform 0 656 1888
p 512 2046 100 0 -1 DESC:Azimuth at start of exposure
p 592 1838 100 0 1 EGU:degrees
p 384 1472 100 0 0 FDSC:Azimuth at start of exposure
p 384 1440 100 0 0 FTVL:DOUBLE
p 560 1728 100 1024 0 name:$(sad)$(I)
p 640 1664 100 0 0 PREC:2
use bc200tr 0 -40 -100 0 frame
xform 0 1680 1264
[comments]
