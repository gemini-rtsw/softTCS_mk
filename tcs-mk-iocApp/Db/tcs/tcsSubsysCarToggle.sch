[schematic2]
uniq 17
[tools]
[detail]
w 2072 795 100 0 TRIG efanouts.FanTrigger.LNK1 1328 1008 1568 1008 1568 784 2624 784 outhier.TRIG.p
w 2424 1163 100 0 OUT elongouts.IdleDefault.OUT 2272 1152 2624 1152 outhier.OUT.p
w 2416 1419 100 0 MESS estringouts.nullDefault.OUT 2256 1408 2624 1408 outhier.MESS.p
w 456 411 100 0 DISV junction 320 864 320 400 640 400 outhier.DISV.p
w 414 1099 100 0 DISV ebos.CarDisable.VAL 128 864 320 864 320 1088 544 1088 ecalcs.CalcFan.INPA
w 1920 1227 100 0 n#13 hwin.hwin#5.in 1872 1216 2016 1216 elongouts.IdleDefault.DOL
w 2112 1339 100 0 n#12 estringouts.nullDefault.FLNK 2256 1440 2368 1440 2368 1328 1904 1328 1904 1184 2016 1184 elongouts.IdleDefault.SLNK
w 1744 1435 100 0 n#11 efanouts.FanTrigger.LNK2 1328 976 1536 976 1536 1424 2000 1424 estringouts.nullDefault.SLNK
w 1024 1019 100 0 n#10 ecalcs.CalcFan.VAL 832 896 960 896 960 1008 1136 1008 efanouts.FanTrigger.SELL
w 942 939 100 0 n#9 ecalcs.CalcFan.FLNK 832 928 1088 928 efanouts.FanTrigger.SLNK
w 222 907 100 0 n#7 ebos.CarDisable.FLNK 128 896 352 896 352 704 544 704 ecalcs.CalcFan.SLNK
s 816 1888 200 0 Subsystem CAR records
s 736 1952 200 0 Enable & disable combination of
s 2016 -192 100 0 Sciences Ltd.
s 2016 -160 100 0 Observatory
s 2016 -128 100 0 Copyright
s 2256 -128 100 0 Gemini Telescope Control System
s 2016 2064 100 0 $Id: tcsSubsysCarToggle.sch,v 1.1 2004/05/06 15:54:42 cjm Exp $
[cell use]
use outhier 2592 743 100 0 TRIG
xform 0 2608 784
use outhier 2592 1111 100 0 OUT
xform 0 2608 1152
use outhier 2592 1367 100 0 MESS
xform 0 2608 1408
use outhier 608 359 100 0 DISV
xform 0 624 400
use estringouts 2000 1351 100 0 nullDefault
xform 0 2128 1424
p 2048 1488 100 0 -1 DESC:Null string
p 1936 1390 100 0 0 VAL:
use hwin 1680 1175 100 0 hwin#5
xform 0 1776 1216
p 1683 1208 100 0 -1 val(in):0
use elongouts 2016 1095 100 0 IdleDefault
xform 0 2144 1184
p 2080 1264 100 0 -1 DESC:Idle state
p 1856 1102 100 0 0 OMSL:closed_loop
p 2272 1152 75 768 -1 pproc(OUT):PP
use efanouts 1088 791 100 0 FanTrigger
xform 0 1208 944
p 974 1209 100 0 0 DESC:Select output
p 1312 768 100 0 1 SELM:Specified
use ecalcs 544 615 100 0 CalcFan
xform 0 688 880
p 640 784 100 0 1 CALC:A+1
p 592 1168 100 0 -1 DESC:Increment flag
use ebos -128 775 100 0 CarDisable
xform 0 0 864
p -112 960 100 0 -1 DESC:Enable/disable CAR
p 112 736 100 0 1 ONAM:Disabled
p 112 688 100 0 1 ZNAM:Enabled
use bc200tr -560 -408 -100 0 frame
xform 0 1120 896
[comments]
