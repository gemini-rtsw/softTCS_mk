[schematic2]
uniq 12
[tools]
[detail]
s 1184 2272 200 0 SIR records related to the rotator
s 2592 2432 100 0 $Id:
s 2816 240 100 0 Gemini Telescope Control System
[cell use]
use esirs 1112 1352 100 0 rotatorGuideGain
xform 0 1296 1504
p 1152 1662 100 0 -1 DESC:Rotator guiding gain
p 1232 1454 100 0 0 EGU:
p 1024 1088 100 0 0 FDSC:Rotator guiding gain (-1 to +1)
p 1024 1056 100 0 0 FTVL:DOUBLE
p 1280 1280 100 0 0 PREC:2
p 1200 1344 100 1024 0 name:$(sad)$(I)
use esirs 1112 1736 100 0 rotatorGuideState
xform 0 1296 1888
p 1152 2046 100 0 -1 DESC:Rotator guiding state
p 1232 1838 100 0 0 EGU:
p 1024 1472 100 0 0 FDSC:Rotator guiding state (0 or 1)
p 1024 1440 100 0 0 FTVL:LONG
p 1280 1664 100 0 0 PREC:2
p 1200 1728 100 1024 0 name:$(sad)$(I)
use esirs 472 1736 100 0 rotTrackFrame
xform 0 656 1888
p 512 2046 100 0 -1 DESC:Rotator tracking frame
p 592 1838 100 0 0 EGU:
p 384 1472 100 0 0 FDSC:Rotator tracking frame
p 384 1440 100 0 0 FTVL:STRING
p 640 1664 100 0 0 PREC:2
p 560 1728 100 1024 0 name:$(sad)$(I)
use esirs 456 1352 100 0 rotTrackEqnx
xform 0 640 1504
p 496 1662 100 0 -1 DESC:Equinox of rotator tracking frame
p 576 1454 100 0 0 EGU:
p 368 1088 100 0 0 FDSC:Equinox of rotator tracking frame
p 368 1056 100 0 0 FTVL:STRING
p 624 1280 100 0 0 PREC:2
p 544 1344 100 1024 0 name:$(sad)$(I)
use esirs 456 984 100 0 instrAA
xform 0 640 1136
p 496 1294 100 0 -1 DESC:Instrument Alignment Angle
p 576 1086 100 0 1 EGU:degrees
p 368 720 100 0 0 FDSC:Instrument Aligment Angle
p 368 688 100 0 0 FTVL:DOUBLE
p 704 976 100 0 1 PREC:3
p 544 976 100 1024 0 name:$(sad)$(I)
use esirs 440 600 100 0 instrPA
xform 0 624 752
p 480 910 100 0 -1 DESC:Instrument Position Angle
p 560 702 100 0 1 EGU:degrees
p 352 336 100 0 0 FDSC:Instrument Position Angle
p 352 304 100 0 0 FTVL:DOUBLE
p 704 592 100 0 1 PREC:3
p 528 592 100 1024 0 name:$(sad)$(I)
use bc200tr 0 -40 -100 0 frame
xform 0 1680 1264
[comments]
