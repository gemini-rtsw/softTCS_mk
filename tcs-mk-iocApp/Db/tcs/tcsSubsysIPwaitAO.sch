[schematic2]
uniq 56
[tools]
[detail]
w 1224 1739 100 0 n#55 ecalcouts.ecalcouts#53.VAL 1088 1728 1408 1728 1408 1568 1664 1568 ecalcs.InPosCalc.INPC
w 1176 1803 100 0 n#47 ecalcouts.ecalcouts#53.FLNK 1088 1792 1312 1792 1312 1472 junction
w 1144 1035 100 0 n#47 ebos.InPosOverride.FLNK 1024 1024 1312 1024 1312 1248 junction
w 1464 1259 100 0 n#47 ecalcouts.ecalcouts#41.FLNK 1088 1472 1312 1472 1312 1248 1664 1248 ecalcs.InPosCalc.SLNK
w 576 1803 100 0 n#54 inhier.c#50.P 432 1792 768 1792 ecalcouts.ecalcouts#53.INPA
w 1256 1419 100 0 n#49 ecalcouts.ecalcouts#41.VAL 1088 1408 1472 1408 1472 1600 1664 1600 ecalcs.InPosCalc.INPB
w 1208 1003 100 0 n#48 ebos.InPosOverride.VAL 1024 992 1440 992 1440 1632 1664 1632 ecalcs.InPosCalc.INPA
w 1992 1451 100 0 n#46 ecalcs.InPosCalc.VAL 1952 1440 2080 1440 2080 1360 2208 1360 outhier.INPOS.p
w 2056 1483 100 0 n#45 ecalcs.InPosCalc.FLNK 1952 1472 2208 1472 outhier.FLNK.p
s 704 1920 100 0 execute the configureForAO command.
s 704 1952 100 0 It now waits for the user to explicitly 
s 704 1984 100 0 This record used to wait for the AO fold.
s 1888 2032 100 0 $Id: tcsSubsysIPwaitAO.sch,v 1.2 2006/11/24 11:17:03 cjm Exp $
[cell use]
use ecalcouts 768 1607 100 0 ecalcouts#53
xform 0 928 1728
p 840 1640 100 0 -1 CALC:A
p 1368 2428 100 0 0 DESC:Monitor AO fold
p 848 1872 100 0 1 OOPT:On Change
p 512 1808 60 0 -1 def(INPA):$(tcs)im:AOConfigFlag
p 832 1608 100 0 -1 name:$(top)$(prefix)AoConfigWait
p 720 1800 75 0 -1 pproc(INPA):CPP
use ecalcouts 768 1287 100 0 ecalcouts#41
xform 0 928 1408
p 840 1320 100 0 -1 CALC:A
p 856 1552 100 0 1 OOPT:On Change
p 544 1472 100 0 -1 def(INPA):$(inpos).VAL
p 832 1288 100 0 -1 name:$(top)$(prefix)InposWait
p 720 1480 75 0 -1 pproc(INPA):CPP
use inhier 416 1751 100 0 c#50
xform 0 432 1792
use ebos 768 903 100 0 InPosOverride
xform 0 896 992
p 672 1088 100 0 -1 DESC:Over ride subsystem in position state
p 960 832 100 0 1 ONAM:enabled
p 960 864 100 0 1 ZNAM:disabled
p 880 896 100 1024 0 name:$(top)$(prefix)$(I)
use ecalcs 1664 1159 100 0 InPosCalc
xform 0 1808 1424
p 1824 1232 100 0 1 CALC:(A=1||C=0)?1:B
p 992 1696 100 0 0 def(INPC):0.0
p 1776 1152 100 1024 0 name:$(top)$(prefix)$(I)
use bb200tr 96 520 -100 0 frame
xform 0 1376 1344
use outhier 2200 1320 100 0 INPOS
xform 0 2192 1360
use outhier 2200 1432 100 0 FLNK
xform 0 2192 1472
[comments]
