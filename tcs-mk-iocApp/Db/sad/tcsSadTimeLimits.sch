[schematic2]
uniq 14
[tools]
[detail]
s 2560 2304 100 0 $Id: tcsSadTimeLimits.sch,v 1.2 2008/05/01 15:28:38 cjm Exp $
s 2800 112 100 0 Gemini Telescope Control System
s 1056 2144 200 0 This schematic holds SIR records that relate to limits 
s 1472 2080 200 0 or time to limits
[cell use]
use esirs 1112 168 100 0 timeToP2lim
xform 0 1296 320
p 1120 478 100 0 -1 DESC:Time to P2 wrap limit
p 1024 32 100 0 0 DISS:NO_ALARM
p 1248 254 100 0 1 EGU:minutes
p 1024 -96 100 0 0 FDSC:Time to rotary probe P2 wrap limit
p 1024 -128 100 0 0 FTVL:STRING
p 1280 96 100 0 0 PREC:2
p 1200 160 100 1024 0 name:$(sad)$(I)
use esirs 408 168 100 0 timeToP1lim
xform 0 592 320
p 416 478 100 0 -1 DESC:Time to P1 wrap limit
p 320 32 100 0 0 DISS:NO_ALARM
p 544 254 100 0 1 EGU:minutes
p 320 -96 100 0 0 FDSC:Time to rotary probe P1 wrap limit
p 320 -128 100 0 0 FTVL:STRING
p 576 96 100 0 0 PREC:2
p 496 160 100 1024 0 name:$(sad)$(I)
use esirs 408 1672 100 0 airMassLimit
xform 0 592 1824
p 480 1982 100 0 -1 DESC:Current airmass limit
p 544 1758 100 0 1 EGU:none
p 320 1408 100 0 0 FDSC:Current airmass limit
p 320 1376 100 0 0 FTVL:DOUBLE
p 576 1600 100 0 0 PREC:3
p 496 1664 100 1024 0 name:$(sad)$(I)
use esirs 1112 1672 100 0 airMassLimitEl
xform 0 1296 1824
p 1072 1982 100 0 -1 DESC:Elevation airmass limit
p 1248 1758 100 0 1 EGU:degrees
p 1024 1408 100 0 0 FDSC:Elevation airmass limit
p 1024 1376 100 0 0 FTVL:DOUBLE
p 1280 1600 100 0 0 PREC:5
p 1200 1664 100 1024 0 name:$(sad)$(I)
use esirs 408 1128 100 0 timeToAmRise
xform 0 592 1280
p 416 1438 100 0 -1 DESC:Time to rise above airmass limit
p 544 1214 100 0 1 EGU:minutes
p 320 864 100 0 0 FDSC:Time to rise to airmass limit
p 320 832 100 0 0 FTVL:DOUBLE
p 576 1056 100 0 0 PREC:2
p 496 1120 100 1024 0 name:$(sad)$(I)
use esirs 1112 1128 100 0 timeToAmSet
xform 0 1296 1280
p 1120 1438 100 0 -1 DESC:Time to set below airmass limit
p 1248 1214 100 0 1 EGU:minutes
p 1024 864 100 0 0 FDSC:Time to set below airmass limit
p 1024 832 100 0 0 FTVL:STRING
p 1280 1056 100 0 0 PREC:2
p 1200 1120 100 1024 0 name:$(sad)$(I)
use esirs 408 616 100 0 currentTimeToSet
xform 0 592 768
p 416 926 100 0 -1 DESC:Time to set
p 544 702 100 0 1 EGU:minutes
p 320 352 100 0 0 FDSC:Time to set for current target
p 320 320 100 0 0 FTVL:STRING
p 576 544 100 0 0 PREC:2
p 496 608 100 1024 0 name:$(sad)$(I)
use esirs 1112 616 100 0 currentTimeToRise
xform 0 1296 768
p 1120 926 100 0 -1 DESC:Time to rise
p 1248 702 100 0 1 EGU:minutes
p 1024 352 100 0 0 FDSC:Time to rise for current target
p 1024 320 100 0 0 FTVL:DOUBLE
p 1280 544 100 0 0 PREC:2
p 1200 608 100 1024 0 name:$(sad)$(I)
use esirs 1912 1672 100 0 timeToAzlim
xform 0 2096 1824
p 1920 1982 100 0 -1 DESC:Time to Az wrap limit
p 2048 1758 100 0 1 EGU:minutes
p 1824 1408 100 0 0 FDSC:Time to az wrap limit
p 1824 1376 100 0 0 FTVL:STRING
p 2080 1600 100 0 0 PREC:2
p 2000 1664 100 1024 0 name:$(sad)$(I)
use esirs 2584 1672 100 0 timeToRotlim
xform 0 2768 1824
p 2592 1982 100 0 -1 DESC:Time to rotator wrap limit
p 2496 1536 100 0 0 DISS:NO_ALARM
p 2720 1758 100 0 1 EGU:minutes
p 2496 1408 100 0 0 FDSC:Time to rotator wrap limit
p 2496 1376 100 0 0 FTVL:STRING
p 2752 1600 100 0 0 PREC:2
p 2672 1664 100 1024 0 name:$(sad)$(I)
use esirs 1912 1128 100 0 timeToBlindSpot
xform 0 2096 1280
p 1920 1438 100 0 -1 DESC:Time to blind spot limit
p 2048 1214 100 0 1 EGU:minutes
p 1824 864 100 0 0 FDSC:Time to blind spot limit
p 1824 832 100 0 0 FTVL:STRING
p 2080 1056 100 0 0 PREC:2
p 2000 1120 100 1024 0 name:$(sad)$(I)
use esirs 2600 1128 100 0 timeToBlindSpotExit
xform 0 2784 1280
p 2608 1438 100 0 -1 DESC:Time to Blind Spot exit
p 2736 1214 100 0 1 EGU:minutes
p 2512 864 100 0 0 FDSC:Time to Blind Spot exit
p 2512 832 100 0 0 FTVL:STRING
p 2768 1056 100 0 0 PREC:2
p 2688 1120 100 1024 0 name:$(sad)$(I)
use esirs 1912 616 100 0 timeToDomeLimit
xform 0 2096 768
p 1920 926 100 0 -1 DESC:Time to dome limit
p 2048 702 100 0 1 EGU:seconds
p 1824 352 100 0 0 FDSC:Time to dome limit
p 1824 320 100 0 0 FTVL:DOUBLE
p 2080 544 100 0 0 PREC:1
p 2000 608 100 1024 0 name:$(sad)$(I)
use bc200tr -16 -168 -100 0 frame
xform 0 1664 1136
[comments]
