[schematic2]
uniq 8
[tools]
[detail]
w 878 1067 100 0 n#7 ecalcs.thermAdd.VAL 432 1104 736 1104 736 1056 1056 1056 ecalcs.thermalM.INPA
w 850 475 100 0 n#5 ecalcs.calc1.VAL 776 464 960 464 960 1024 1056 1024 ecalcs.thermalM.INPB
w 834 507 100 0 n#4 ecalcs.calc1.FLNK 776 496 928 496 928 672 1056 672 ecalcs.thermalM.SLNK
w 378 546 100 0 n#2 eaos.thermalwindSetPoint.VAL 256 432 376 432 376 624 488 624 ecalcs.calc1.INPB
s 1408 1072 100 0 Demand 2 Mode 3
s 1408 1120 100 0 Demand 1 Mode 1 or 2 depending on wind velocity
s 1408 1168 100 0 Demand 0  Mode 0
s 1408 1216 100 0 The mapping from input thermal demand and the current mode is
s 1480 1424 100 0 $Id: tcsECsimThermal.sch,v 1.1.1.1 1998/11/08 00:20:21 epics Exp $
s 1728 192 100 0 Gemini Telescope Control System
s 1744 120 100 0 Enclosure thermal simulation
s 720 1344 200 0 Generate ECS Thermal Mode
[cell use]
use ecalcs 512 184 100 0 calc1
xform 0 632 448
p 547 88 100 0 1 CALC:(A >B)?1:0
p 528 718 100 0 -1 DESC:Check wind speed
p 544 54 100 0 1 SCAN:1 second
p 264 654 100 0 -1 def(INPA):$(ws)windSpeed
p 600 176 100 1024 0 name:$(ec)$(I)
use ecalcs 1080 584 100 0 thermalM
xform 0 1200 848
p 1112 494 100 0 1 CALC:(A=1)?(A+B):A
p 1128 1110 100 0 -1 DESC:ECS Thermal mode
p 712 1046 100 0 0 def(INPA):0.0
p 1168 576 100 1024 0 name:$(ec)$(I)
p 1024 1056 75 1280 -1 pproc(INPA):PP
use ecalcs 144 823 100 0 thermAdd
xform 0 288 1088
p 224 992 100 0 1 CALC:A=2?A+1:A
p -63 1254 100 0 0 DESC:Adjust thermal demand
p -160 1296 100 0 -1 def(INPA):$(ec)thermal.VALA
p -144 864 100 1024 0 name:$(ec)$(I)
use eaos 24 344 100 0 thermalwindSetPoint
xform 0 128 432
p 32 534 100 0 -1 DESC:Wind speed set point
p -256 190 100 0 0 DRVH:150.0
p -32 158 100 0 0 EGU:Km/hr
p -256 254 100 0 0 EGUF:150.0
p -32 542 100 0 0 HOPR:150.0
p -256 286 100 0 0 PREC:1
p 112 336 100 1024 0 name:$(ec)$(I)
use bb200tr -296 -88 -100 0 frame
xform 0 984 736
[comments]
