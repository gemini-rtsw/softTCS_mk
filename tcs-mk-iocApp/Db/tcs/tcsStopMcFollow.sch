[schematic2]
uniq 11
[tools]
[detail]
w 736 1283 100 0 n#1 efanouts.fan.LNK1 640 1280 832 1280 832 1432 1368 1432 estringouts.axesOut.SLNK
w 1248 1315 100 0 n#2 efanouts.fan.FLNK 640 1312 1856 1312 outhier.Flnk.p
w 192 1315 100 0 n#3 ecalcs.incr.FLNK 128 1312 256 1312 256 1200 400 1200 efanouts.fan.SLNK
w 288 1283 100 0 n#4 ecalcs.incr.VAL 128 1280 448 1280 efanouts.fan.SELL
w -312 1091 100 0 n#5 inhier.Slnk.P -464 1088 -160 1088 ecalcs.incr.SLNK
w -312 1475 100 0 Action inhier.Action.P -464 1472 -160 1472 ecalcs.incr.INPA
w 1196 1555 100 0 n#6 estringinval.axes.VAL 1168 1552 1224 1552 1224 1464 1368 1464 estringouts.axesOut.DOL
w 988 963 100 0 n#7 estringinval.azBrake.VAL 920 960 1056 960 1056 1208 1368 1208 estringouts.azBrakeOut.DOL
w 1060 523 100 0 n#8 estringinval.elBrake.VAL 944 520 1176 520 1176 952 1368 952 estringouts.elBrakeOut.DOL
w 1664 1451 100 0 n#9 estringouts.axesOut.FLNK 1624 1448 1704 1448 1704 1264 1216 1264 1216 1176 1368 1176 estringouts.azBrakeOut.SLNK
w 1660 1195 100 0 n#10 estringouts.azBrakeOut.FLNK 1624 1192 1696 1192 1696 1040 1224 1040 1224 920 1368 920 estringouts.elBrakeOut.SLNK
s 1920 -192 100 0 Gemini Telescope Control System
s 1920 -256 100 0 Set default stop options
s 1664 2000 100 0 $Id: tcsStopMcFollow.sch,v 1.5 2015/05/18 09:40:12 cjm Exp $
s 320 1888 100 0 This schematic is used to pass on default parameters
s 320 1856 100 0 to the mount stop command.
s 320 1824 100 0 If the action initiated by the higher level schematic is
s 320 1792 100 0 follow rather than stop then this diagram
s 320 1760 100 0 just passes the forward link through without taking
s 320 1728 100 0 any action itself
[cell use]
use bc200tr -912 -472 -100 0 frame
xform 0 768 832
use inhier -480 1431 100 0 Action
xform 0 -464 1472
use inhier -480 1047 100 0 Slnk
xform 0 -464 1088
use outhier 1824 1271 100 0 Flnk
xform 0 1840 1312
use estringouts 1368 1359 100 0 axesOut
xform 0 1496 1432
p 1395 1472 100 0 0 DESC:Axes parameter for mount stop
p 1560 1368 100 0 1 VAL:Both
p 1720 1416 100 0 -1 def(OUT):$(mc)stop.A
p 1304 1238 100 0 0 OMSL:closed_loop
p 1632 1424 75 768 -1 pproc(OUT):CA
use estringouts 1368 1103 100 0 azBrakeOut
xform 0 1496 1176
p 1395 1216 100 0 0 DESC:Apply az brakes on stop
p 1560 1096 100 0 1 VAL:No
p 1720 1160 100 0 -1 def(OUT):$(mc)stop.B
p 1304 982 100 0 0 OMSL:closed_loop
p 1632 1168 75 768 -1 pproc(OUT):CA
use estringouts 1368 847 100 0 elBrakeOut
xform 0 1496 920
p 1395 960 100 0 0 DESC:Apply el brakes on stop
p 1560 840 100 0 1 VAL:No
p 1720 904 100 0 -1 def(OUT):$(mc)stop.C
p 1304 726 100 0 0 OMSL:closed_loop
p 1632 912 75 768 -1 pproc(OUT):CA
use efanouts 400 1063 100 0 fan
xform 0 520 1216
p 256 1182 100 0 0 SELM:Specified
use ecalcs -160 999 100 0 incr
xform 0 -16 1264
p -64 1200 100 0 1 CALC:A+1
p -367 1430 100 0 0 DESC:Increment action input
use estringinval 697 455 100 0 elBrake
xform 0 816 536
p 857 443 100 0 1 VAL:No
use estringinval 673 895 100 0 azBrake
xform 0 792 976
p 833 883 100 0 1 VAL:No
use estringinval 921 1487 100 0 axes
xform 0 1040 1568
p 1081 1475 100 0 1 VAL:Both
[comments]
