[schematic2]
uniq 27
[tools]
[detail]
w 2200 658 100 0 n#26 esirs.thermalM.FLNK 2448 992 2528 992 2528 656 1920 656 1920 352 2032 352 esirs.domeState.SLNK
w 1794 696 100 0 n#25 esirs.topShtrState.FLNK 1696 512 1792 512 1792 832 2032 832 esirs.thermalM.SLNK
w 1424 658 100 0 n#24 esirs.shtrSealed.FLNK 1696 976 1760 976 1760 656 1136 656 1136 352 1280 352 esirs.topShtrState.SLNK
w 994 688 100 0 n#23 esirs.botShtrState.FLNK 864 512 992 512 992 816 1280 816 esirs.shtrSealed.SLNK
w 616 658 100 0 n#22 esirs.health.FLNK 864 976 960 976 960 656 320 656 320 352 448 352 esirs.botShtrState.SLNK
w 2280 1154 100 0 n#16 esirs.westVentGatePos.FLNK 3168 1472 3200 1472 3200 1152 1408 1152 1408 1120 320 1120 320 816 448 816 esirs.health.SLNK
w 2488 1474 100 0 n#15 esirs.eastVentGatePos.FLNK 2432 1472 2592 1472 2592 1312 2752 1312 esirs.westVentGatePos.SLNK
w 1896 1314 100 0 n#14 esirs.botShtrErr.FLNK 1680 1472 1824 1472 1824 1312 2016 1312 esirs.eastVentGatePos.SLNK
w 1104 1314 100 0 n#10 esirs.botShtrPos.FLNK 864 1472 992 1472 992 1312 1264 1312 esirs.botShtrErr.SLNK
w 1742 1570 100 0 n#9 esirs.topShtrErr.FLNK 3168 1952 3200 1952 3200 1568 320 1568 320 1312 448 1312 esirs.botShtrPos.SLNK
w 2494 1954 100 0 n#6 esirs.topShtrPos.FLNK 2432 1952 2592 1952 2592 1792 2752 1792 esirs.topShtrErr.SLNK
w 1902 1794 100 0 n#5 esirs.domeErr.FLNK 1680 1952 1824 1952 1824 1792 2016 1792 esirs.topShtrPos.SLNK
w 1094 1794 100 0 n#2 esirs.domePos.FLNK 864 1952 960 1952 960 1792 1264 1792 esirs.domeErr.SLNK
s 2528 2368 100 0 $Id: ecSad.sch,v 1.2 2001/05/18 14:53:08 cjm Exp $
s 2768 176 100 0 Gemini Telescope Control System
s 1040 2240 200 0 ECS SAD items provided with internal ECS simulator
[cell use]
use esirs 472 1704 100 0 domePos
xform 0 656 1856
p 528 2014 100 0 -1 DESC:Current dome position
p 560 1854 100 0 1 EGU:degrees
p 560 1822 100 0 1 FTVL:DOUBLE
p 384 1088 100 0 0 MDEL:0.005
p 640 1632 100 0 0 PREC:2
p 560 1790 100 0 1 SCAN:1 second
p 160 1950 100 0 -1 def(INP):$(tcs)ec:domePos
use esirs 1288 1704 100 0 domeErr
xform 0 1472 1856
p 1344 2014 100 0 -1 DESC:Current dome error
p 1376 1854 100 0 1 EGU:degrees
p 1376 1822 100 0 1 FTVL:DOUBLE
p 1200 1088 100 0 0 MDEL:0.005
p 1456 1632 100 0 0 PREC:2
p 1376 1790 100 0 0 SCAN:Passive
p 992 1950 100 0 -1 def(INP):$(tcs)ec:domeErr
use esirs 2040 1704 100 0 topShtrPos
xform 0 2224 1856
p 2096 2014 100 0 -1 DESC:Current top shutter position
p 2128 1854 100 0 1 EGU:degrees
p 2128 1822 100 0 1 FTVL:DOUBLE
p 1952 1088 100 0 0 MDEL:0.005
p 2208 1632 100 0 0 PREC:2
p 2128 1790 100 0 0 SCAN:Passive
p 1792 1982 100 0 -1 def(INP):$(tcs)ec:topShtrPos
use esirs 2776 1704 100 0 topShtrErr
xform 0 2960 1856
p 2832 2014 100 0 -1 DESC:Top shutter error
p 2864 1854 100 0 1 EGU:degrees
p 2864 1822 100 0 1 FTVL:DOUBLE
p 2688 1088 100 0 0 MDEL:0.005
p 2944 1632 100 0 0 PREC:2
p 2864 1790 100 0 0 SCAN:Passive
p 2512 1982 100 0 -1 def(INP):$(tcs)ec:topShtrErr
use esirs 472 1224 100 0 botShtrPos
xform 0 656 1376
p 528 1534 100 0 -1 DESC:Current bottom shutter position
p 560 1374 100 0 1 EGU:degrees
p 560 1342 100 0 1 FTVL:DOUBLE
p 384 608 100 0 0 MDEL:0.005
p 640 1152 100 0 0 PREC:2
p 560 1310 100 0 0 SCAN:Passive
p 224 1502 100 0 -1 def(INP):$(tcs)ec:botShtrPos
use esirs 1288 1224 100 0 botShtrErr
xform 0 1472 1376
p 1344 1534 100 0 -1 DESC:Bottom shutter error
p 1376 1374 100 0 1 EGU:degrees
p 1376 1342 100 0 1 FTVL:DOUBLE
p 1200 608 100 0 0 MDEL:0.005
p 1456 1152 100 0 0 PREC:2
p 1376 1310 100 0 0 SCAN:Passive
p 1024 1502 100 0 -1 def(INP):$(tcs)ec:botShtrErr
use esirs 2040 1224 100 0 eastVentGatePos
xform 0 2224 1376
p 2096 1534 100 0 -1 DESC:East vent gate position
p 2128 1374 100 0 1 EGU:percentage
p 2128 1342 100 0 1 FTVL:DOUBLE
p 1952 608 100 0 0 MDEL:0.05
p 2208 1152 100 0 0 PREC:1
p 2128 1310 100 0 0 SCAN:Passive
p 1792 1502 100 0 -1 def(INP):$(tcs)ec:eastVentGatePos
use esirs 2776 1224 100 0 westVentGatePos
xform 0 2960 1376
p 2832 1534 100 0 -1 DESC:West vent gate position
p 2864 1374 100 0 1 EGU:percentage
p 2864 1342 100 0 1 FTVL:DOUBLE
p 2688 608 100 0 0 MDEL:0.05
p 2944 1152 100 0 0 PREC:1
p 2864 1310 100 0 0 SCAN:Passive
p 2528 1502 100 0 -1 def(INP):$(tcs)ec:westVentGatePos
use esirs 472 728 100 0 health
xform 0 656 880
p 608 1038 100 0 -1 DESC:ECS health
p 384 528 100 0 0 EGU:none
p 560 862 100 0 1 FTVL:LONG
p 256 1006 100 0 -1 def(INP):$(tcs)ec:health
use esirs 1304 728 100 0 shtrSealed
xform 0 1488 880
p 1440 1038 100 0 -1 DESC:Shutter sealed state
p 1216 528 100 0 0 EGU:none
p 1392 862 100 0 1 FTVL:STRING
p 1088 1006 100 0 -1 def(INP):$(tcs)ec:simOutput.VALC
use esirs 2056 744 100 0 thermalM
xform 0 2240 896
p 2192 1054 100 0 -1 DESC:Thermal control mode
p 1968 544 100 0 0 EGU:none
p 2144 878 100 0 1 FTVL:STRING
p 1840 1022 100 0 -1 def(INP):$(tcs)ec:simOutput.VALB
use esirs 472 264 100 0 botShtrState
xform 0 656 416
p 608 574 100 0 -1 DESC:Bottom shutter state
p 384 64 100 0 0 EGU:none
p 560 398 100 0 1 FTVL:STRING
p 256 542 100 0 -1 def(INP):$(tcs)ec:simOutput.VALD
use esirs 1304 264 100 0 topShtrState
xform 0 1488 416
p 1440 574 100 0 -1 DESC:Top shutter state
p 1216 64 100 0 0 EGU:none
p 1392 398 100 0 1 FTVL:STRING
p 1088 542 100 0 -1 def(INP):$(tcs)ec:simOutput.VALE
use esirs 2056 264 100 0 domeState
xform 0 2240 416
p 2192 574 100 0 -1 DESC:Dome state
p 1968 64 100 0 0 EGU:none
p 2144 398 100 0 1 FTVL:STRING
p 1840 542 100 0 -1 def(INP):$(tcs)ec:simOutput.VALF
use bc200tr -48 -104 -100 0 frame
xform 0 1632 1200
[comments]
