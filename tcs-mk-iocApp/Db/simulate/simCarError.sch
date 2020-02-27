[schematic2]
uniq 7
[tools]
[detail]
w 292 795 100 0 n#1 embbos.testingCARVal.OUT 144 792 440 792 ecars.testingCAR.IVAL
w 212 467 100 0 n#2 estringouts.testingCARMess.OUT 144 464 280 464 280 728 440 728 ecars.testingCAR.IMSS
w 868 571 100 0 n#3 ecars.testingCAR.FLNK 760 568 976 568 outhier.FLNK.p
w 832 731 100 0 n#4 ecars.testingCAR.OMSS 760 728 904 728 outhier.OMSS.p
w 832 795 100 0 n#5 ecars.testingCAR.VAL 760 792 904 792 outhier.VAL.p
w 154 834 -100 0 n#6 embbos.testingCARVal.FLNK 144 824 232 824 232 600 440 600 ecars.testingCAR.SLNK
s 1216 1184 100 0 $Id: simCarError.sch,v 1.1 2015/05/18 09:39:02 cjm Exp $
s 1488 -48 100 0 Gemini Telescope Control System
s 1440 -96 100 0 Generate CAR error for subsystem
[cell use]
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
use outhier 968 528 100 0 FLNK
xform 0 960 568
use outhier 896 752 100 0 VAL
xform 0 888 792
use embbos -49 695 100 0 testingCARVal
xform 0 16 792
p -176 1011 100 0 0 DESC:Values for test CAR record
p 48 854 100 0 0 ONST:PAUSED
p 48 790 100 0 0 THST:ERROR
p -144 790 100 0 0 THVL:3
p 48 822 100 0 0 TWST:BUSY
p -144 822 100 0 0 TWVL:2
p 48 886 100 0 0 ZRST:IDLE
p 0 696 100 1024 0 name:$(prefix)$(I)
use estringouts -49 402 100 0 testingCARMess
xform 0 16 480
p -80 548 100 0 -1 DESC:Message for testing CAR
p -176 446 100 0 0 VAL:
p 0 400 100 1024 0 name:$(prefix)$(I)
use outhier 887 692 100 0 OMSS
xform 0 888 728
use ecars 581 507 100 0 testingCAR
xform 0 600 680
p 536 728 100 0 0 DESC:CAR for testing
p 552 504 100 1024 0 name:$(prefix)$(I)
[comments]
