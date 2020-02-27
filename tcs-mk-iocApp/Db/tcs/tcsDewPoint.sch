[schematic2]
uniq 10
[tools]
[detail]
w 384 1587 100 0 n#1 inhier.SDIS.P 112 1584 656 1584 egenSub.calcDewPoint.SDIS
w 408 963 100 0 n#2 inhier.SDIS.P 112 960 704 960 eaos.wsDewPoint.SDIS
w 1840 963 100 0 n#3 eais.m1Temp.VAL 1760 960 1920 960 1920 1184 2080 1184 ecalcs.dewPointAlarm.INPB
w 900 1363 100 0 n#4 inhier.SDIS.P 776 1360 1024 1360 1024 1576 1256 1576 esels.selDewPointSource.NVL
w 1008 995 100 0 n#5 eaos.wsDewPoint.VAL 960 992 1056 992 1056 1544 1256 1544 esels.selDewPointSource.INPA
w 1020 2323 100 0 n#6 egenSub.calcDewPoint.VALA 944 2320 1096 2320 1096 1512 1256 1512 esels.selDewPointSource.INPB
w 1692 1691 100 0 n#7 eaos.currentDewPoint.DOL 1696 1688 1664 1688 1664 1368 1544 1368 esels.selDewPointSource.VAL
w 1962 1658 -100 0 n#8 eaos.currentDewPoint.VAL 1952 1656 2016 1656 2016 1216 2080 1216 ecalcs.dewPointAlarm.INPA
w 970 1034 -100 0 n#9 eaos.wsDewPoint.FLNK 960 1024 1112 1024 1112 1160 1256 1160 esels.selDewPointSource.SLNK
w 954 1586 -100 0 n#9 egenSub.calcDewPoint.FLNK 944 1584 984 1584 984 1160 1112 1160 junction
s 1072 2560 300 0 Calculate Dew Point Alarms
s 2544 2720 100 0 $Id: tcsDewPoint.sch,v 1.1.1.1 1998/11/08 00:20:34 epics Exp $
s 2672 464 100 0 Dew Point Calculations
s 2624 528 100 0 Gemini Telescope Control System
s 112 1392 100 0 Depending on the value of SDIS, either the dew point
s 112 1360 100 0 is calculated or it is simply pulled in from the weather
s 112 1328 100 0 server.
s 1856 704 100 0 This record goes into a minor alarm when temperature
s 1856 672 100 0 difference is less than 5 C and a major alarm when the
s 1856 640 100 0 difference is less than or equal to 0 C
s 112 1296 100 0 calcDewPoint uses the values of temp, pressure and
s 112 1264 100 0 relative humidity input by the user.
[cell use]
use bc200tr -208 248 -100 0 frame
xform 0 1472 1552
use eaos 728 904 100 0 wsDewPoint
xform 0 832 992
p 688 1102 100 0 -1 DESC:Dew Point from Weather Server
p 752 830 100 0 1 EGU:deg C
p 448 974 100 0 0 OMSL:closed_loop
p 448 846 100 0 0 PREC:5
p 752 862 100 0 1 SCAN:1 second
p 464 1022 100 0 -1 def(DOL):$(ws)dewPoint
p 992 896 100 1024 1 name:$(tcs)$(I)
p 1015 950 100 0 0 def(OUT):
use inhier 120 1544 100 0 SDIS
xform 0 112 1584
use inhier 120 920 100 0 SDIS
xform 0 112 960
use eais 1528 904 100 0 m1Temp
xform 0 1632 976
p 1536 1070 100 0 -1 DESC:Mirror temperature
p 1568 830 100 0 1 EGU:deg C
p 1248 782 100 0 0 EGUF:0.0000000e+00
p 1248 814 100 0 0 PREC:1
p 1184 1006 100 0 -1 def(INP):$(m1)positionThermal
p 1744 896 100 1024 1 name:$(tcs)$(I)
use ecalcs 2104 744 100 0 dewPointAlarm
xform 0 2224 1008
p 2176 958 100 0 1 CALC:B-A
p 2064 1310 100 0 -1 DESC:Temp of M1 above Dew Point
p 1792 894 100 0 0 EGU:deg C
p 2048 830 100 0 0 LLSV:MAJOR
p 2048 1022 100 0 0 LOLO:0.0
p 2048 958 100 0 0 LOW:5.0
p 2048 862 100 0 0 LSV:MINOR
p 1792 862 100 0 0 PREC:5
p 2144 926 100 0 1 SCAN:1 second
p 2304 784 100 1024 1 name:$(tcs)$(I)
p 2048 1216 75 1280 -1 pproc(INPA):PP
p 2048 1184 75 1280 -1 pproc(INPB):PP
use egenSub 680 1528 100 0 calcDewPoint
xform 0 800 1952
p 720 2398 100 0 -1 DESC:Calculate Dew Point
p 368 2094 100 0 0 DISV:0
p 368 2078 100 0 0 PREC:5
p 720 1694 100 0 1 SCAN:1 second
p 720 1758 100 0 -1 SNAM:tcsCalcDewPoint
p 768 1472 100 1024 1 name:$(tcs)$(I)
use eaos 1704 1571 100 0 currentDewPoint
xform 0 1824 1656
p 1893 1596 100 1024 1 name:$(tcs)$(I)
p 1440 1638 100 0 0 OMSL:closed_loop
p 2028 1623 100 0 -1 def(OUT):$(sad)currentDewPoint
use esels 1409 1179 100 0 selDewPointSource
xform 0 1400 1352
p 1252 1088 100 0 1 EGU:deg C
p 1407 1152 100 1024 1 name:$(tcs)$(I)
use inhier 781 1320 100 0 SDIS
xform 0 776 1360
[comments]
