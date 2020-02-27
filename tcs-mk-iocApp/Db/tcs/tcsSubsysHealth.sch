[schematic2]
uniq 45
[tools]
[detail]
w 2568 1195 100 0 n#35 esirs.Health.VAL 2528 1184 2656 1184 outhier.HLTH.p
w 2296 939 100 0 n#35 junction 2528 1184 2528 928 2112 928 2112 768 2240 768 egenSub.HealthIndex.INPA
w 2296 907 100 0 n#44 esirs.Health.FLNK 2528 1216 2560 1216 2560 896 2080 896 2080 96 2240 96 egenSub.HealthIndex.SLNK
w 2216 1355 100 0 n#40 estringinval.HealthVal.VAL 2400 1472 2432 1472 2432 1344 2048 1344 2048 1216 2112 1216 esirs.Health.INP
w 2216 1323 100 0 n#39 estringinval.HealthVal.FLNK 2400 1504 2464 1504 2464 1312 2016 1312 2016 1056 2112 1056 esirs.Health.SLNK
w 1840 731 100 0 n#38 estringouts.HealthIn.OUT 1776 720 1952 720 1952 1344 junction
w 2024 1499 100 0 n#38 estringouts.HlthDefVal.OUT 1776 1344 1952 1344 1952 1488 2144 1488 estringinval.HealthVal.SLNK
w 1856 1035 100 0 n#37 estringouts.HealthMess.OUT 1776 1024 1984 1024 1984 1184 junction
w 1856 1611 100 0 n#37 estringouts.HlthDefMess.OUT 1776 1600 1984 1600 1984 1184 2112 1184 esirs.Health.IMSS
w 2536 1163 100 0 n#36 esirs.Health.OMSS 2528 1152 2592 1152 2592 1056 2656 1056 outhier.MESS.p
w 1584 539 100 0 n#26 efanouts.HlthFanTrigger.FLNK 1072 1232 1248 1232 1248 528 1968 528 outhier.FLNK.p
w 1608 907 100 0 n#25 estringouts.HealthMess.FLNK 1776 1056 1888 1056 1888 896 1376 896 1376 736 1520 736 estringouts.HealthIn.SLNK
w 1168 1211 100 0 n#24 efanouts.HlthFanTrigger.LNK1 1072 1200 1312 1200 1312 1040 1520 1040 estringouts.HealthMess.SLNK
w 1608 1483 100 0 n#22 estringouts.HlthDefMess.FLNK 1776 1632 1888 1632 1888 1472 1376 1472 1376 1360 1520 1360 estringouts.HlthDefVal.SLNK
w -34 1099 100 0 n#7 ebos.HlthDisable.FLNK -128 1088 96 1088 96 896 288 896 ecalcs.HlthCalcFan.SLNK
w -122 699 100 0 n#7 inhier.SLNK.P -304 688 96 688 96 896 junction
w 158 1291 100 0 DISV ebos.HlthDisable.VAL -128 1056 64 1056 64 1280 288 1280 ecalcs.HlthCalcFan.INPA
w 1376 1627 100 0 n#11 efanouts.HlthFanTrigger.LNK2 1072 1168 1280 1168 1280 1616 1520 1616 estringouts.HlthDefMess.SLNK
w 768 1211 100 0 n#10 ecalcs.HlthCalcFan.VAL 576 1088 704 1088 704 1200 880 1200 efanouts.HlthFanTrigger.SELL
w 686 1131 100 0 n#9 ecalcs.HlthCalcFan.FLNK 576 1120 832 1120 efanouts.HlthFanTrigger.SLNK
s 816 1888 200 0 Subsystem Health records
s 736 1952 200 0 Enable & disable combination of
s 2016 -192 100 0 Sciences Ltd.
s 2016 -160 100 0 Observatory
s 2016 -128 100 0 Copyright
s 2256 -128 100 0 Gemini Telescope Control System
s 2016 2064 100 0 $Id: tcsSubsysHealth.sch,v 1.2 2005/11/30 09:44:13 cjm Exp $
[cell use]
use egenSub 2240 7 100 0 HealthIndex
xform 0 2384 432
p 2208 848 100 0 -1 DESC:Convert string health to index
p 2017 -219 100 0 0 FTA:STRING
p 2400 784 100 0 -1 FTVA:LONG
p 1952 382 100 0 0 SNAM:tcsHealthIndex
use esirs 2112 967 100 0 Health
xform 0 2320 1120
p 2160 1264 100 0 -1 DESC:Resultant subsystem health
use estringinval 2144 1415 100 0 HealthVal
xform 0 2272 1488
use estringouts 1520 967 100 0 HealthMess
xform 0 1648 1040
p 1568 1104 100 0 -1 DESC:Subsystem health message
p 1456 814 100 0 0 IVOA:Set output to IVOV
p 1456 782 100 0 0 IVOV:Health invalid - subsystem offline?
p 1456 846 100 0 0 OMSL:closed_loop
p 1456 1006 100 0 0 VAL:
p 1216 1104 100 0 -1 def(DOL):$(subsys)health.OMSS
p 1488 1072 75 1280 -1 pproc(DOL):CA
use estringouts 1520 663 100 0 HealthIn
xform 0 1648 736
p 1568 800 100 0 -1 DESC:Subsystem health value
p 1456 510 100 0 0 IVOA:Set output to IVOV
p 1456 478 100 0 0 IVOV:BAD
p 1456 542 100 0 0 OMSL:closed_loop
p 1456 702 100 0 0 VAL:
p 1280 816 100 0 -1 def(DOL):$(subsys)health
p 1488 768 75 1280 -1 pproc(DOL):CA
p 1776 720 75 768 -1 pproc(OUT):PP
use estringouts 1520 1543 100 0 HlthDefMess
xform 0 1648 1616
p 1568 1680 100 0 -1 DESC:Null string
p 1456 1582 100 0 0 VAL:
use estringouts 1520 1287 100 0 HlthDefVal
xform 0 1648 1360
p 1568 1424 100 0 -1 DESC:Good Health
p 1456 1326 100 0 0 VAL:GOOD
p 1776 1344 75 768 -1 pproc(OUT):PP
use inhier -320 647 100 0 SLNK
xform 0 -304 688
use outhier 1936 487 100 0 FLNK
xform 0 1952 528
use outhier 2624 1143 100 0 HLTH
xform 0 2640 1184
use outhier 2624 1015 100 0 MESS
xform 0 2640 1056
use efanouts 832 983 100 0 HlthFanTrigger
xform 0 952 1136
p 718 1401 100 0 0 DESC:Select output
p 1056 960 100 0 1 SELM:Specified
use ecalcs 288 807 100 0 HlthCalcFan
xform 0 432 1072
p 384 976 100 0 1 CALC:A+1
p 336 1360 100 0 -1 DESC:Increment flag
use ebos -384 967 100 0 HlthDisable
xform 0 -256 1056
p -368 1152 100 0 -1 DESC:Enable/disable health
p -144 928 100 0 1 ONAM:Disabled
p -144 880 100 0 1 ZNAM:Enabled
p -272 960 100 1024 0 name:$(top)$(I)
use bc200tr -560 -408 -100 0 frame
xform 0 1120 896
[comments]
