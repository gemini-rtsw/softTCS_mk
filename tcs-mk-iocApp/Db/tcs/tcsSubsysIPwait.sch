[schematic2]
uniq 50
[tools]
[detail]
w 1448 1515 100 0 n#49 ecalcouts.ecalcouts#41.VAL 1280 1504 1664 1504 1664 1696 1856 1696 ecalcs.InPosCalc.INPB
w 1400 1099 100 0 n#48 ebos.InPosOverride.VAL 1216 1088 1632 1088 1632 1728 1856 1728 ecalcs.InPosCalc.INPA
w 1336 1131 100 0 n#47 ebos.InPosOverride.FLNK 1216 1120 1504 1120 1504 1344 junction
w 1656 1355 100 0 n#47 ecalcouts.ecalcouts#41.FLNK 1280 1568 1504 1568 1504 1344 1856 1344 ecalcs.InPosCalc.SLNK
w 2184 1547 100 0 n#46 ecalcs.InPosCalc.VAL 2144 1536 2272 1536 2272 1456 2400 1456 outhier.INPOS.p
w 2248 1579 100 0 n#45 ecalcs.InPosCalc.FLNK 2144 1568 2400 1568 outhier.FLNK.p
s 1888 2032 100 0 $Id: tcsSubsysIPwait.sch,v 1.4 2002/12/12 10:13:54 cjm Exp $
[cell use]
use ebos 960 999 100 0 InPosOverride
xform 0 1088 1088
p 864 1184 100 0 -1 DESC:Over ride subsystem in position state
p 1152 928 100 0 1 ONAM:enabled
p 1152 960 100 0 1 ZNAM:disabled
p 1072 992 100 1024 0 name:$(top)$(prefix)$(I)
use ecalcs 1856 1255 100 0 InPosCalc
xform 0 2000 1520
p 2016 1328 100 0 1 CALC:A=1?1:B
p 1968 1248 100 1024 0 name:$(top)$(prefix)$(I)
use ecalcouts 960 1383 100 0 ecalcouts#41
xform 0 1120 1504
p 1032 1416 100 0 -1 CALC:A
p 1048 1648 100 0 1 OOPT:On Change
p 736 1568 100 0 -1 def(INPA):$(inpos).VAL
p 1024 1384 100 0 -1 name:$(top)$(prefix)InposWait
p 912 1576 75 0 -1 pproc(INPA):CPP
use bb200tr 96 520 -100 0 frame
xform 0 1376 1344
use outhier 2392 1416 100 0 INPOS
xform 0 2384 1456
use outhier 2392 1528 100 0 FLNK
xform 0 2384 1568
[comments]
