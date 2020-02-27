[schematic2]
uniq 31
[tools]
[detail]
w 416 1179 100 0 n#30 inhier.SLNK.P 304 1168 576 1168 elongouts.healthIn.SLNK
w 1010 1296 100 0 n#26 elongouts.healthIn.VAL 832 1168 1008 1168 1008 1376 1136 1376 ecalcs.calc.INPA
w 912 1202 100 0 n#25 elongouts.healthIn.FLNK 832 1200 1040 1200 1040 992 1136 992 ecalcs.calc.SLNK
w 2464 1218 100 0 n#16 estringouts.warning.OUT 2336 1216 2640 1216 estringouts.HealthIn.SLNK
w 2498 1352 100 0 n#16 estringouts.good.OUT 2336 1440 2496 1440 2496 1216 junction
w 2498 1128 100 0 n#16 estringouts.bad.OUT 2336 992 2496 992 2496 1216 junction
w 2976 1202 100 0 n#19 estringouts.HealthIn.OUT 2896 1200 3104 1200 outhier.HEALTHOUT.p
w 1938 1144 100 0 n#14 efanouts.fan.LNK3 1856 1232 1936 1232 1936 1008 2080 1008 estringouts.bad.SLNK
w 1888 1266 100 0 n#13 efanouts.fan.LNK2 1856 1264 1968 1264 1968 1232 2080 1232 estringouts.warning.SLNK
w 1970 1400 100 0 n#12 efanouts.fan.LNK1 1856 1296 1968 1296 1968 1456 2080 1456 estringouts.good.SLNK
w 1574 1298 100 0 n#8 ecalcs.calc.VAL 1424 1184 1520 1184 1520 1296 1664 1296 efanouts.fan.SELL
w 1502 1218 100 0 n#7 ecalcs.calc.FLNK 1424 1216 1616 1216 efanouts.fan.SLNK
s 2560 2336 100 0 $Id: tcsEcsHealthTranslate.sch,v 1.4 2004/05/25 13:46:07 cjm Exp $
s 2816 144 100 0 Gemini Telescope Control System
s 1344 1952 100 0 This schematic translates the ECS health values 0, 1, or 2
s 1344 1920 100 0 into the strings GOOD, WARNING or BAD
[cell use]
use elongouts 600 1080 100 0 healthIn
xform 0 704 1168
p 624 1278 100 0 -1 DESC:ECS health value
p 640 974 100 0 1 DISV:1
p 640 1038 100 0 1 IVOA:Set output to IVOV
p 640 944 100 0 1 IVOV:2
p 416 1086 100 0 0 OMSL:closed_loop
p 640 1006 100 0 1 SCAN:Passive
p 352 1214 100 0 -1 def(DOL):$(ec)health
p 288 1118 100 0 0 def(SDIS):
p 576 1200 75 1280 -1 palrm(DOL):MS
p 544 1200 75 1280 -1 pproc(DOL):CA
use inhier 312 1128 100 0 SLNK
xform 0 304 1168
use estringouts 2104 1384 100 0 good
xform 0 2208 1456
p 2096 1550 100 0 -1 DESC:String for good health
p 2016 1230 100 0 0 IVOA:Continue normally
p 2016 1198 100 0 0 IVOV:
p 2016 1422 100 0 0 VAL:GOOD
p 2336 1440 75 768 -1 pproc(OUT):PP
use estringouts 2104 1160 100 0 warning
xform 0 2208 1232
p 2096 1326 100 0 -1 DESC:String for poor health
p 2016 1006 100 0 0 IVOA:Continue normally
p 2016 974 100 0 0 IVOV:
p 2016 1198 100 0 0 VAL:WARNING
p 2336 1216 75 768 -1 pproc(OUT):PP
use estringouts 2104 936 100 0 bad
xform 0 2208 1008
p 2096 1102 100 0 -1 DESC:String for bad health
p 2016 782 100 0 0 IVOA:Continue normally
p 2016 750 100 0 0 IVOV:
p 2016 974 100 0 0 VAL:BAD
p 2336 992 75 768 -1 pproc(OUT):PP
use estringouts 2664 1144 100 0 HealthIn
xform 0 2768 1216
p 2656 1310 100 0 -1 DESC:Health string
p 2576 990 100 0 0 IVOA:Continue normally
p 2576 958 100 0 0 IVOV:
p 2576 1182 100 0 0 VAL:
p 2752 1136 100 1024 0 name:$(tcs)ec$(I)
p 2896 1200 75 768 -1 pproc(OUT):PP
use outhier 3096 1160 100 0 HEALTHOUT
xform 0 3088 1200
use efanouts 1640 1080 100 0 fan
xform 0 1736 1232
p 1472 1198 100 0 0 SELM:Specified
use ecalcs 1160 904 100 0 calc
xform 0 1280 1168
p 1248 1214 100 0 1 CALC:A+1
p 1136 1470 100 0 -1 DESC:Increment health value
use bc200tr -32 -136 -100 0 frame
xform 0 1648 1168
[comments]
