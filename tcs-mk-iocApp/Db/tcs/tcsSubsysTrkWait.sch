[schematic2]
uniq 42
[tools]
[detail]
w 1344 1570 -100 0 FLNK ecalcouts.ecalcouts#41.FLNK 1248 1568 1488 1568 outhier.FLNK.p
w 1352 1506 100 0 n#37 ecalcouts.ecalcouts#41.VAL 1248 1504 1504 1504 outhier.TRACKID.p
s 1888 2032 100 0 $Id: tcsSubsysTrkWait.sch,v 1.2 2001/05/21 16:08:58 cjm Exp $
[cell use]
use ecalcouts 928 1383 100 0 ecalcouts#41
xform 0 1088 1504
p 1000 1416 100 0 -1 CALC:A
p 1016 1648 100 0 1 OOPT:On Change
p 632 1568 100 0 -1 def(INPA):$(subsys)trackId.VAL
p 992 1384 100 0 -1 name:$(top)$(prefix)TrkWait
p 880 1576 75 0 -1 pproc(INPA):CPP
use bb200tr 96 520 -100 0 frame
xform 0 1376 1344
use outhier 1496 1464 100 0 TRACKID
xform 0 1488 1504
use outhier 1480 1528 100 0 FLNK
xform 0 1472 1568
[comments]
