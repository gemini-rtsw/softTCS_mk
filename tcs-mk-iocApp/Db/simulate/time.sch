[schematic2]
uniq 3
[tools]
[detail]
s 912 272 100 0 Simulated time for subsystems
s 912 320 100 0 Gemini Telescope Control System
s 864 1136 100 0 time.sch
[cell use]
use ebos 232 344 100 0 intSimulate
xform 0 336 432
p -24 588 100 0 0 DESC:Time simulation flag
p -112 318 100 0 0 ZNAM:notSimulated
p -112 286 100 0 0 ONAM:simulated
p 272 542 100 0 1 PV:$(top)$(subsys)TIME:
use ba200tr -144 40 -100 0 frame
xform 0 656 664
use embbos 232 632 100 0 health
xform 0 336 720
p 144 939 100 0 0 DESC:TIME health for TCS simulations
p 368 814 100 0 0 ZRST:Good
p 368 750 100 0 0 TWST:Bad
p 560 750 100 0 0 TWSV:MAJOR
p 368 782 100 0 0 ONST:Warning
p 560 782 100 0 0 ONSV:MINOR
p 176 782 100 0 0 ONVL:1
p 176 750 100 0 0 TWVL:2
p 272 814 100 0 1 PV:$(top)$(subsys)TIME:
use esirs 776 536 100 0 logrecord
xform 0 960 688
p 703 432 100 0 0 DESC:Log record for TIME system
p 703 416 100 0 0 FDSC:Log record for TIME system 
p 928 606 100 0 -1 SNAM:tcsSimLog
p 832 846 100 0 1 PV:$(top)$(subsys)
[comments]
