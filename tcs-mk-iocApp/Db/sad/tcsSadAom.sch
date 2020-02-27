[schematic2]
uniq 27
[tools]
[detail]
s 2688 96 100 0 Gemini Telescope Control System
s 2432 2288 100 0 $Id: tcsSadAom.sch,v 1.1 2007/12/18 10:51:04 cjm Exp $
[cell use]
use esirs 1352 1320 100 0 aomPr2Rmax
xform 0 1536 1472
p 1408 1646 100 0 -1 DESC:NGS probe 2 upper radial limit
p 1424 1470 100 0 1 EGU:mm
p 1264 1056 100 0 0 FDSC:Max. radius to which NGS probe 2 
p 1424 1374 100 0 1 FTVL:DOUBLE
p 1520 1248 100 0 0 PREC:2
p 1440 1312 100 1024 0 name:$(sad)$(I)
use esirs 1368 1736 100 0 aomPr2Rmin
xform 0 1552 1888
p 1424 2062 100 0 -1 DESC:NGS probe 2 lower radial limit
p 1440 1886 100 0 1 EGU:mm
p 1280 1472 100 0 0 FDSC:Min. radius to which NGS probe 
p 1440 1790 100 0 1 FTVL:DOUBLE
p 1536 1664 100 0 0 PREC:2
p 1456 1728 100 1024 0 name:$(sad)$(I)
use esirs 264 1320 100 0 aomPr1Rmax
xform 0 448 1472
p 320 1646 100 0 -1 DESC:NGS Probe 1 upper radial limit
p 336 1470 100 0 1 EGU:mm
p 176 1056 100 0 0 FDSC:Max. radius to which NGS probe
p 336 1374 100 0 1 FTVL:DOUBLE
p 432 1248 100 0 0 PREC:2
p 352 1312 100 1024 0 name:$(sad)$(I)
use esirs 264 1736 100 0 aomPr1Rmin
xform 0 448 1888
p 320 2062 100 0 -1 DESC:NGS probe 1 lower radial limit
p 336 1886 100 0 1 EGU:mm
p 176 1472 100 0 0 FDSC:Min. radius to which the NGS probe
p 336 1790 100 0 1 FTVL:DOUBLE
p 432 1664 100 0 0 PREC:2
p 352 1728 100 1024 0 name:$(sad)$(I)
use esirs 2248 1736 100 0 aomPr3Rmin
xform 0 2432 1888
p 2304 2062 100 0 -1 DESC:NGS probe 3 lower radial limit
p 2320 1886 100 0 1 EGU:mm
p 2160 1472 100 0 0 FDSC:Min. radius to which NGS probe 3
p 2320 1790 100 0 1 FTVL:DOUBLE
p 2416 1664 100 0 0 PREC:2
p 2336 1728 100 1024 0 name:$(sad)$(I)
use esirs 2264 1288 100 0 aomPr3Rmax
xform 0 2448 1440
p 2320 1614 100 0 -1 DESC:NGS probe 3 upper radial limit
p 2336 1438 100 0 1 EGU:mm
p 2176 1024 100 0 0 FDSC:Max. radius to which NGS probe 3
p 2336 1342 100 0 1 FTVL:DOUBLE
p 2432 1216 100 0 0 PREC:2
p 2352 1280 100 1024 0 name:$(sad)$(I)
use esirs 248 456 100 0 aomPr1Xmax
xform 0 432 608
p 304 782 100 0 -1 DESC:NGS Probe 1 upper X limit
p 320 606 100 0 1 EGU:mm
p 160 192 100 0 0 FDSC:Max. X to which NGS probe
p 320 510 100 0 1 FTVL:DOUBLE
p 416 384 100 0 0 PREC:2
p 336 448 100 1024 0 name:$(sad)$(I)
use esirs 248 872 100 0 aomPr1Xmin
xform 0 432 1024
p 304 1198 100 0 -1 DESC:NGS Probe 1 lower X limit
p 320 1022 100 0 1 EGU:mm
p 160 608 100 0 0 FDSC:Min. X to which the NGS probe
p 320 926 100 0 1 FTVL:DOUBLE
p 416 800 100 0 0 PREC:2
p 336 864 100 1024 0 name:$(sad)$(I)
use esirs 1352 456 100 0 aomPr2Xmax
xform 0 1536 608
p 1408 782 100 0 -1 DESC:NGS probe 2 upper X limit
p 1424 606 100 0 1 EGU:mm
p 1264 192 100 0 0 FDSC:Max. X to which NGS probe 2
p 1424 510 100 0 1 FTVL:DOUBLE
p 1520 384 100 0 0 PREC:2
p 1440 448 100 1024 0 name:$(sad)$(I)
use esirs 1368 872 100 0 aomPr2Xmin
xform 0 1552 1024
p 1424 1198 100 0 -1 DESC:NGS probe 2 lower X limit
p 1440 1022 100 0 1 EGU:mm
p 1280 608 100 0 0 FDSC:Min. X to which NGS probe
p 1440 926 100 0 1 FTVL:DOUBLE
p 1536 800 100 0 0 PREC:2
p 1456 864 100 1024 0 name:$(sad)$(I)
use esirs 2248 456 100 0 aomPr3Xmax
xform 0 2432 608
p 2304 782 100 0 -1 DESC:NGS probe 3 upper X limit
p 2320 606 100 0 1 EGU:mm
p 2160 192 100 0 0 FDSC:Max. X to which NGS probe 2
p 2320 510 100 0 1 FTVL:DOUBLE
p 2416 384 100 0 0 PREC:2
p 2336 448 100 1024 0 name:$(sad)$(I)
use esirs 2264 872 100 0 aomPr3Xmin
xform 0 2448 1024
p 2320 1198 100 0 -1 DESC:NGS probe 3 lower X limit
p 2336 1022 100 0 1 EGU:mm
p 2176 608 100 0 0 FDSC:Min. X to which NGS probe
p 2336 926 100 0 1 FTVL:DOUBLE
p 2432 800 100 0 0 PREC:2
p 2352 864 100 1024 0 name:$(sad)$(I)
use bc200tr -144 -184 -100 0 frame
xform 0 1536 1120
[comments]
