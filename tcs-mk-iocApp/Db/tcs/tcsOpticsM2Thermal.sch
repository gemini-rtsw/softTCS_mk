[schematic2]
uniq 57
[tools]
[detail]
w 824 683 100 0 n#56 eais.ANB103.VAL 736 672 960 672 egenSub.sensor2.INPB
w 272 731 100 0 n#55 inhier.c#22.P 112 720 480 720 eais.ANB103.INP
w 112 1915 100 0 n#53 inhier.c#9.P -48 1904 320 1904 eais.ANB101.INP
w 744 1867 100 0 n#51 eais.ANB101.VAL 576 1856 960 1856 egenSub.sensor1.INPB
w 2488 1451 100 0 n#48 eaos.temp.VAL 2400 1440 2624 1440 outhier.TEMP.p
w 2024 1355 100 0 n#47 egenSub.truss.VALC 1984 1344 2112 1344 2112 1184 2240 1184 esirs.health.INP
w 2136 1163 100 0 n#46 egenSub.truss.OUTB 1984 1376 2080 1376 2080 1152 2240 1152 esirs.health.IMSS
w 2056 747 100 0 n#45 egenSub.truss.FLNK 1984 736 2176 736 2176 1024 2240 1024 esirs.health.SLNK
w 2040 1451 100 0 n#43 egenSub.truss.OUTA 1984 1440 2144 1440 eaos.temp.SLNK
w 904 907 100 0 n#41 eaos.diff.VAL 16 480 224 480 224 896 1632 896 1632 1056 1696 1056 egenSub.truss.INPG
w 1432 43 100 0 n#39 egenSub.sensor2.FLNK 1248 32 1664 32 1664 768 1696 768 egenSub.truss.SLNK
w 1400 651 100 0 n#38 egenSub.sensor2.VALC 1248 640 1600 640 1600 1120 1696 1120 egenSub.truss.INPF
w 1384 715 100 0 n#37 egenSub.sensor2.VALB 1248 704 1568 704 1568 1184 1696 1184 egenSub.truss.INPE
w 1368 779 100 0 n#36 egenSub.sensor2.VALA 1248 768 1536 768 1536 1248 1696 1248 egenSub.truss.INPD
w 1368 1835 100 0 n#35 egenSub.sensor1.VALC 1248 1824 1536 1824 1536 1312 1696 1312 egenSub.truss.INPC
w 1384 1899 100 0 n#34 egenSub.sensor1.VALB 1248 1888 1568 1888 1568 1376 1696 1376 egenSub.truss.INPB
w 1400 1963 100 0 n#33 egenSub.sensor1.VALA 1248 1952 1600 1952 1600 1440 1696 1440 egenSub.truss.INPA
w 768 1227 100 0 n#31 ecalcs.disable.VAL 624 1216 960 1216 egenSub.sensor1.SDIS
w 768 1259 100 0 n#30 ecalcs.disable.FLNK 624 1248 960 1248 egenSub.sensor1.SLNK
w 1096 971 100 0 n#29 egenSub.sensor1.FLNK 1248 1216 1408 1216 1408 960 832 960 832 64 960 64 egenSub.sensor2.SLNK
w 664 1675 100 0 n#28 eaos.step1.VAL 576 1664 800 1664 800 1792 960 1792 egenSub.sensor1.INPC
w 840 747 100 0 n#14 junction 768 1920 768 736 960 736 egenSub.sensor2.INPA
w 560 2011 100 0 n#14 inhier.REFTEMP.P 400 2000 768 2000 768 1920 960 1920 egenSub.sensor1.INPA
w 648 491 100 0 n#19 eaos.step2.VAL 576 480 768 480 768 608 960 608 egenSub.sensor2.INPC
w 190 1035 100 0 n#6 ecalcs.counter.FLNK 48 1248 80 1248 80 1024 336 1024 ecalcs.disable.SLNK
w 238 1419 100 0 n#5 junction 112 1216 176 1216 176 1408 336 1408 ecalcs.disable.INPA
w -146 1579 100 0 n#5 ecalcs.counter.VAL 48 1216 112 1216 112 1568 -368 1568 -368 1408 -240 1408 ecalcs.counter.INPA
s -384 720 100 0 new valus every 10s.
s -384 752 100 0 are read but relies on the fact the PCS provides
s -384 784 100 0 This ensures independent values every time the sensors
s -384 816 100 0 a 12s poll of the sensors in the PCS
s -384 848 100 0 The purpose of these records is to provide
s -384 2032 100 0 use by the focus model.
s -384 2064 100 0 check them for consistency and then provide a smoothed average for
s -384 2096 100 0 Read the truss temperature from the sensors monitored by the PCS
s 2256 -96 100 0 Generate truss temperature
s 2256 -32 100 0 Gemini TCS
s 2000 -96 100 0 Sciences Ltd.
s 2000 -64 100 0 Observatory 
s 2000 -32 100 0 Copyright
s 2016 2160 100 0 $Id: tcsOpticsM2Thermal.sch,v 1.3 2005/06/30 14:24:09 cjm Exp $
[cell use]
use eais 480 615 100 0 ANB103
xform 0 608 688
p 224 238 100 0 0 ADEL:0.005
p 608 656 100 0 0 DESC:Temperature reading from M1
p 224 430 100 0 0 EGU:degC
p 224 206 100 0 0 MDEL:0.005
p 224 526 100 0 0 PREC:2
p 160 736 100 0 -1 def(INP):$(m1)ANB103:ExtTemp1
p 448 720 75 1280 -1 pproc(INP):CA
use eais 320 1799 100 0 ANB101
xform 0 448 1872
p 64 1422 100 0 0 ADEL:0.005
p 448 1840 100 0 0 DESC:Temperature reading from M1
p 64 1614 100 0 0 EGU:degC
p 64 1390 100 0 0 MDEL:0.005
p 64 1710 100 0 0 PREC:2
p 0 1920 100 0 -1 def(INP):$(m1)ANB101:ExtTemp1
p 288 1904 75 1280 -1 pproc(INP):CA
use egenSub 1696 679 100 0 truss
xform 0 1840 1104
p 1712 1552 100 0 -1 DESC:Average sensor readings
p 1473 453 100 0 0 FTB:STRING
p 1473 421 100 0 0 FTC:LONG
p 1473 357 100 0 0 FTE:STRING
p 1473 293 100 0 0 FTF:LONG
p 1473 453 100 0 0 FTVB:STRING
p 1473 421 100 0 0 FTVC:STRING
p 1408 1230 100 0 0 PREC:4
p 1760 624 100 0 1 SNAM:tcsOpticsTrussTemp
p 1984 1450 75 0 -1 pproc(OUTA):PP
use egenSub 960 -25 100 0 sensor2
xform 0 1104 400
p 976 832 100 0 -1 DESC:Monitor and smooth sensor
p 737 -251 100 0 0 FTVB:STRING
p 737 -283 100 0 0 FTVC:LONG
p 672 526 100 0 0 PREC:4
p 1216 -64 100 0 1 SNAM:tcsOpticsSensor2Temp
p 464 688 100 0 0 def(INPB):0.000000000000000e+00
p 672 510 100 0 0 def(INPD):$(top)ANB103.SEVR
p 912 682 75 0 -1 pproc(INPB):PP
use egenSub 960 1159 100 0 sensor1
xform 0 1104 1584
p 976 2016 100 0 -1 DESC:Monitor and smooth sensor
p 737 933 100 0 0 FTVB:STRING
p 737 901 100 0 0 FTVC:LONG
p 672 1710 100 0 0 PREC:4
p 1024 1120 100 0 1 SNAM:tcsOpticsSensor1Temp
p 464 1872 100 0 0 def(INPB):0.00000000000000e+00
p 672 1694 100 0 0 def(INPD):$(top)ANB101.SEVR
p 912 1866 75 0 -1 pproc(INPB):PP
use egenSub 2272 39 100 0 reset
xform 0 2416 464
p 2272 880 100 0 -1 DESC:Reset truss calculations
p 2368 16 100 0 1 SNAM:tcsOpticsTrussReset
use outhier 2592 1399 100 0 TEMP
xform 0 2608 1440
use esirs 2240 935 100 0 health
xform 0 2448 1088
p 2272 1248 100 0 -1 DESC:Health of temperature monitor
p 2176 672 100 0 0 FDSC:Overall health of temperature monitor
p 2432 736 100 0 0 SNAM:sirHealth
use eaos 2144 1351 100 0 temp
xform 0 2272 1440
p 2128 1536 100 0 -1 DESC:Current truss temperature
p 2112 1166 100 0 0 EGU:deg C
p 1888 1422 100 0 0 OMSL:closed_loop
p 1888 1294 100 0 0 PREC:4
use eaos -240 391 100 0 diff
xform 0 -112 480
p -256 576 100 0 -1 DESC:Permitted temperature difference
p -272 206 100 0 0 EGU:deg C
p -496 334 100 0 0 PREC:4
use eaos 320 391 100 0 step2
xform 0 448 480
p 304 576 100 0 -1 DESC:Permitted temperature step
p 288 206 100 0 0 EGU:deg C
p 64 334 100 0 0 PREC:4
use eaos 320 1575 100 0 step1
xform 0 448 1664
p 304 1760 100 0 -1 DESC:Permitted temperature step
p 288 1390 100 0 0 EGU:deg C
p 64 1518 100 0 0 PREC:4
use inhier 96 679 100 0 c#22
xform 0 112 720
use inhier -64 1863 100 0 c#9
xform 0 -48 1904
use inhier 384 1959 100 0 REFTEMP
xform 0 400 2000
use ecalcs 336 935 100 0 disable
xform 0 480 1200
p 496 960 100 0 1 CALC:A>0?1:0
p 129 1366 100 0 0 DESC:calculation record
use ecalcs -240 935 100 0 counter
xform 0 -96 1200
p -80 960 100 0 1 CALC:(A+1)%12
p -224 1472 100 0 -1 DESC:Counter 0 to 11
p -80 928 100 0 1 SCAN:1 second
use bc200tr -576 -312 -100 0 frame
xform 0 1104 992
[comments]
