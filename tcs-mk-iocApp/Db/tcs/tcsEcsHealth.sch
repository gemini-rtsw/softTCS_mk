[schematic2]
uniq 46
[tools]
[detail]
w 2296 763 100 0 n#45 esirs.Health.FLNK 2528 1056 2560 1056 2560 752 2080 752 2080 0 2192 0 egenSub.HealthIndex.SLNK
w 2568 1035 100 0 n#35 esirs.Health.VAL 2528 1024 2656 1024 outhier.HLTH.p
w 2264 795 100 0 n#35 junction 2528 1024 2528 784 2048 784 2048 672 2192 672 egenSub.HealthIndex.INPA
w 1896 619 100 0 n#38 tcsEcsHealthTranslate.tcsEcsHealthTranslate#41.HEALTHOUT 1888 608 1952 608 1952 1184 junction
w 2024 1339 100 0 n#38 estringouts.HlthDefVal.OUT 1776 1184 1952 1184 1952 1328 2144 1328 estringinval.HealthVal.SLNK
w 1576 763 100 0 n#42 estringouts.HealthMess.FLNK 1776 896 1888 896 1888 752 1312 752 1312 544 1408 544 tcsEcsHealthTranslate.tcsEcsHealthTranslate#41.SLNK
w 2216 1195 100 0 n#40 estringinval.HealthVal.VAL 2400 1312 2432 1312 2432 1184 2048 1184 2048 1056 2112 1056 esirs.Health.INP
w 2216 1163 100 0 n#39 estringinval.HealthVal.FLNK 2400 1344 2464 1344 2464 1152 2016 1152 2016 896 2112 896 esirs.Health.SLNK
w 1856 1451 100 0 n#37 estringouts.HlthDefMess.OUT 1776 1440 1984 1440 1984 1024 2112 1024 esirs.Health.IMSS
w 1856 875 100 0 n#37 estringouts.HealthMess.OUT 1776 864 1984 864 1984 1024 junction
w 2536 1003 100 0 n#36 esirs.Health.OMSS 2528 992 2592 992 2592 896 2656 896 outhier.MESS.p
w 1584 379 100 0 n#26 efanouts.HlthFanTrigger.FLNK 1072 1072 1248 1072 1248 368 1968 368 outhier.FLNK.p
w 1168 1051 100 0 n#24 efanouts.HlthFanTrigger.LNK1 1072 1040 1312 1040 1312 880 1520 880 estringouts.HealthMess.SLNK
w 1608 1323 100 0 n#22 estringouts.HlthDefMess.FLNK 1776 1472 1888 1472 1888 1312 1376 1312 1376 1200 1520 1200 estringouts.HlthDefVal.SLNK
w -122 539 100 0 n#7 inhier.SLNK.P -304 528 96 528 96 736 junction
w -34 939 100 0 n#7 ebos.HlthDisable.FLNK -128 928 96 928 96 736 288 736 ecalcs.HlthCalcFan.SLNK
w 158 1131 100 0 DISV ebos.HlthDisable.VAL -128 896 64 896 64 1120 288 1120 ecalcs.HlthCalcFan.INPA
w 1376 1467 100 0 n#11 efanouts.HlthFanTrigger.LNK2 1072 1008 1280 1008 1280 1456 1520 1456 estringouts.HlthDefMess.SLNK
w 768 1051 100 0 n#10 ecalcs.HlthCalcFan.VAL 576 928 704 928 704 1040 880 1040 efanouts.HlthFanTrigger.SELL
w 686 971 100 0 n#9 ecalcs.HlthCalcFan.FLNK 576 960 832 960 efanouts.HlthFanTrigger.SLNK
s 2016 2064 100 0 $Id: tcsEcsHealth.sch,v 1.2 2005/05/09 22:42:32 gemvx Exp $
s 2256 -128 100 0 Gemini Telescope Control System
s 2016 -128 100 0 Copyright
s 2016 -160 100 0 Observatory
s 2016 -192 100 0 Sciences Ltd.
s 736 1952 200 0 Enable & disable combination of
s 816 1888 200 0 Subsystem Health records
[cell use]
use egenSub 2192 -89 100 0 HealthIndex
xform 0 2336 336
p 2035 651 100 0 0 DESC:Generate health index
p 1969 -315 100 0 0 FTA:STRING
p 2352 672 100 0 -1 FTVA:LONG
p 1904 286 100 0 0 SNAM:tcsHealthIndex
use tcsEcsHealthTranslate 1408 487 100 0 tcsEcsHealthTranslate#41
xform 0 1648 608
p 1428 460 100 0 1 seta:top $(top)Health
use esirs 2112 807 100 0 Health
xform 0 2320 960
p 2160 1104 100 0 -1 DESC:Resultant subsystem health
use estringinval 2144 1255 100 0 HealthVal
xform 0 2272 1328
use estringouts 1520 1127 100 0 HlthDefVal
xform 0 1648 1200
p 1568 1264 100 0 -1 DESC:Good Health
p 1456 1166 100 0 0 VAL:GOOD
p 1776 1184 75 768 -1 pproc(OUT):PP
use estringouts 1520 1383 100 0 HlthDefMess
xform 0 1648 1456
p 1568 1520 100 0 -1 DESC:Null string
p 1456 1422 100 0 0 VAL:
use estringouts 1520 807 100 0 HealthMess
xform 0 1648 880
p 1568 944 100 0 -1 DESC:Subsystem health message
p 1456 686 100 0 0 OMSL:closed_loop
p 1456 846 100 0 0 VAL:
p 1216 944 100 0 -1 def(DOL):$(subsys)health.OMSS
p 1488 912 75 1280 -1 pproc(DOL):CA
use inhier -320 487 100 0 SLNK
xform 0 -304 528
use outhier 2624 855 100 0 MESS
xform 0 2640 896
use outhier 2624 983 100 0 HLTH
xform 0 2640 1024
use outhier 1936 327 100 0 FLNK
xform 0 1952 368
use efanouts 832 823 100 0 HlthFanTrigger
xform 0 952 976
p 718 1241 100 0 0 DESC:Select output
p 1056 800 100 0 1 SELM:Specified
use ecalcs 288 647 100 0 HlthCalcFan
xform 0 432 912
p 384 816 100 0 1 CALC:A+1
p 336 1200 100 0 -1 DESC:Increment flag
use ebos -384 807 100 0 HlthDisable
xform 0 -256 896
p -368 992 100 0 -1 DESC:Enable/disable health
p -144 768 100 0 1 ONAM:Disabled
p -144 720 100 0 1 ZNAM:Enabled
p -272 800 100 1024 0 name:$(top)$(I)
use bc200tr -560 -408 -100 0 frame
xform 0 1120 896
[comments]
