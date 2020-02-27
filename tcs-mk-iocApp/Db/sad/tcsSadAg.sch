[schematic2]
uniq 21
[tools]
[detail]
s 96 1936 100 0 of the same name in the main TCS database. 
s 96 1984 100 0 The four records below are written to by records
s 2432 2288 100 0 $Id: tcsSadAg.sch,v 1.3 2006/04/21 09:30:20 cjm Exp $
s 2688 96 100 0 Gemini Telescope Control System
s 416 224 100 0 Note that only one set of records for the OIWFS
s 416 192 100 0 is valid at any one time. If the LimitType is
s 416 160 100 0 radial (= 1) then the records Rmin and Rmax are 
s 416 128 100 0 relevant. If the LimitType is XY (= 0) then the 
s 416 96 100 0 Xmin, Xmax etc. records apply.
[cell use]
use esirs 2648 1896 100 0 oiwfsProbeGuiding
xform 0 2832 2048
p 2688 2192 100 0 -1 DESC:OIWFS probe guiding flag
p 2720 2046 100 0 1 EGU:units
p 2560 1632 100 0 0 FDSC:Set to 1 if probe is being guided
p 2720 1950 100 0 1 FTVL:LONG
p 2816 1824 100 0 0 PREC:0
p 2736 1888 100 1024 0 name:$(sad)$(I)
use esirs 1944 1896 100 0 pwfs2ProbeGuiding
xform 0 2128 2048
p 1984 2192 100 0 -1 DESC:PWFS2 probe guiding flag
p 2016 2046 100 0 1 EGU:units
p 1856 1632 100 0 0 FDSC:Set to 1 if probe is being guided
p 2016 1950 100 0 1 FTVL:LONG
p 2112 1824 100 0 0 PREC:0
p 2032 1888 100 1024 0 name:$(sad)$(I)
use esirs 1176 1896 100 0 pwfs1ProbeGuiding
xform 0 1360 2048
p 1232 2222 100 0 -1 DESC:PWFS1 probe guiding flag
p 1248 2046 100 0 1 EGU:units
p 1088 1632 100 0 0 FDSC:Set to 1 if probe is being guided
p 1248 1950 100 0 1 FTVL:LONG
p 1344 1824 100 0 0 PREC:0
p 1264 1888 100 1024 0 name:$(sad)$(I)
use tcsSadAgDemands 2624 1015 100 0 tcsSadAgDemands#17
xform 0 2792 1096
use esirs 2648 1448 100 0 pwfs2Rmax
xform 0 2832 1600
p 2704 1774 100 0 -1 DESC:PWFS2 upper radial limit
p 2720 1598 100 0 1 EGU:mm
p 2560 1184 100 0 0 FDSC:Max. radius PWFS2 can be driven
p 2720 1502 100 0 1 FTVL:DOUBLE
p 2816 1376 100 0 0 PREC:2
p 2736 1440 100 1024 0 name:$(sad)$(I)
use esirs 1944 1448 100 0 pwfs2Rmin
xform 0 2128 1600
p 2000 1774 100 0 -1 DESC:PWFS2 lower radial limit
p 2016 1598 100 0 1 EGU:mm
p 1856 1184 100 0 0 FDSC:Min. radius PWFS2 can be driven
p 2016 1502 100 0 1 FTVL:DOUBLE
p 2112 1376 100 0 0 PREC:2
p 2032 1440 100 1024 0 name:$(sad)$(I)
use esirs 1176 1448 100 0 pwfs1Rmax
xform 0 1360 1600
p 1232 1774 100 0 -1 DESC:PWFS1 upper radial limit
p 1248 1598 100 0 1 EGU:mm
p 1088 1184 100 0 0 FDSC:Max. radius PWFS1 can be driven
p 1248 1502 100 0 1 FTVL:DOUBLE
p 1344 1376 100 0 0 PREC:2
p 1264 1440 100 1024 0 name:$(sad)$(I)
use esirs 408 1448 100 0 pwfs1Rmin
xform 0 592 1600
p 464 1774 100 0 -1 DESC:PWFS1 lower radial limit
p 480 1598 100 0 1 EGU:mm
p 320 1184 100 0 0 FDSC:Min. radius PWFS1 can be driven
p 480 1502 100 0 1 FTVL:DOUBLE
p 576 1376 100 0 0 PREC:2
p 496 1440 100 1024 0 name:$(sad)$(I)
use esirs 1176 904 100 0 oiwfsRmin
xform 0 1360 1056
p 1232 1230 100 0 -1 DESC:OIWFS lower radial limit
p 1248 1054 100 0 1 EGU:mm
p 1088 640 100 0 0 FDSC:Min. radius OIWFS can be driven
p 1248 958 100 0 1 FTVL:DOUBLE
p 1344 832 100 0 0 PREC:2
p 1264 896 100 1024 0 name:$(sad)$(I)
use esirs 1944 904 100 0 oiwfsRmax
xform 0 2128 1056
p 2000 1230 100 0 -1 DESC:OIWFS upper radial limit
p 2016 1054 100 0 1 EGU:mm
p 1856 640 100 0 0 FDSC:Max. radius OIWFS can be driven
p 2016 958 100 0 1 FTVL:DOUBLE
p 2112 832 100 0 0 PREC:2
p 2032 896 100 1024 0 name:$(sad)$(I)
use esirs 384 903 100 0 oiwfsLimitType
xform 0 592 1056
p 464 1232 100 0 -1 DESC:XY or R limits for OIWFS
p 320 640 100 0 0 FDSC:show if OIWFS has XY-Radial limits
p 480 960 100 0 1 FTVL:LONG
p 496 896 100 1024 0 name:$(sad)$(I)
use esirs 408 392 100 0 oiwfsXmin
xform 0 592 544
p 464 718 100 0 -1 DESC:OIWFS lower X limit
p 480 542 100 0 1 EGU:mm
p 320 128 100 0 0 FDSC:Min. X coord OIWFS can be driven
p 480 446 100 0 1 FTVL:DOUBLE
p 576 320 100 0 0 PREC:2
p 496 384 100 1024 0 name:$(sad)$(I)
use esirs 1176 392 100 0 oiwfsXmax
xform 0 1360 544
p 1232 718 100 0 -1 DESC:OIWFS upper X limit
p 1248 542 100 0 1 EGU:mm
p 1088 128 100 0 0 FDSC:Max. X coord OIWFS can be driven
p 1248 446 100 0 1 FTVL:DOUBLE
p 1344 320 100 0 0 PREC:2
p 1264 384 100 1024 0 name:$(sad)$(I)
use esirs 1944 392 100 0 oiwfsYmin
xform 0 2128 544
p 2000 718 100 0 -1 DESC:OIWFS lower Y limit
p 2016 542 100 0 1 EGU:mm
p 1856 128 100 0 0 FDSC:Min. Y coord OIWFS can be driven
p 2016 446 100 0 1 FTVL:DOUBLE
p 2112 320 100 0 0 PREC:2
p 2032 384 100 1024 0 name:$(sad)$(I)
use esirs 2616 392 100 0 oiwfsYmax
xform 0 2800 544
p 2672 718 100 0 -1 DESC:OIWFS upper Y limit
p 2688 542 100 0 1 EGU:mm
p 2528 128 100 0 0 FDSC:Max. Y coord OIWFS can be driven
p 2688 446 100 0 1 FTVL:DOUBLE
p 2784 320 100 0 0 PREC:2
p 2704 384 100 1024 0 name:$(sad)$(I)
use bc200tr -144 -184 -100 0 frame
xform 0 1536 1120
[comments]
