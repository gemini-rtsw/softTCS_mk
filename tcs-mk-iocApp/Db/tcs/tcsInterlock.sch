[schematic2]
uniq 17
[tools]
[detail]
w -2416 -77 100 0 n#1 hwin.hwin#745.in -2464 -80 -2368 -80 eaos.gisClear.DOL
w -480 259 100 0 n#2 ecalcs.gisOverrideState.FLNK -512 256 -448 256 -448 192 -368 192 ebis.gisOverriden.SLNK
w -440 227 100 0 n#3 ecalcs.gisOverrideState.VAL -512 224 -368 224 ebis.gisOverriden.INP
w -1080 403 100 0 n#4 ebis.permitGISOverride.FLNK -1120 400 -1040 400 -1040 32 junction
w -960 35 100 0 n#4 ebos.overrideGIS.FLNK -1120 32 -800 32 ecalcs.gisOverrideState.SLNK
w -1064 371 100 0 n#5 ebis.permitGISOverride.VAL -1120 368 -1008 368 -1008 416 -800 416 ecalcs.gisOverrideState.INPA
w -1024 3 100 0 n#6 ebos.overrideGIS.VAL -1120 0 -928 0 -928 384 -800 384 ecalcs.gisOverrideState.INPB
w -2088 323 100 0 n#7 estringouts.gisSimEnabled.OUT -2128 320 -2048 320 -2048 0 -1376 0 ebos.overrideGIS.SLNK
w -1520 451 100 0 n#8 ecalcs.checkGIS.FLNK -1568 448 -1472 448 -1472 384 -1376 384 ebis.permitGISOverride.SLNK
w -1472 419 100 0 n#9 ecalcs.checkGIS.VAL -1568 416 -1376 416 ebis.permitGISOverride.INP
w -840 1907 100 0 n#10 embbis.userInterlock.VAL -912 1904 -768 1904 -768 1952 -576 1952 elongouts.userIntDemand.DOL
w -824 1939 100 0 n#11 embbis.userInterlock.FLNK -912 1936 -736 1936 -736 1920 -576 1920 elongouts.userIntDemand.SLNK
w -1264 1123 100 0 n#12 ecalcs.gisdemand.FLNK -1312 1120 -1216 1120 -1216 864 -1104 864 esubs.interlock.SLNK
w -1245 1168 100 0 n#13 junction -1248 1088 -1248 1248 -1104 1248 esubs.interlock.INPA
w -1280 1091 100 0 n#13 ecalcs.gisdemand.VAL -1312 1088 -1248 1088 -1248 720 -736 720 -736 1072 -688 1072 ebos.interlockState.DOL
w -800 1091 100 0 n#14 esubs.interlock.FLNK -816 1088 -784 1088 -784 1040 -688 1040 ebos.interlockState.SLNK
w -2104 355 100 0 n#15 estringouts.gisSimEnabled.FLNK -2128 352 -2080 352 -2080 32 -2464 32 -2464 -112 -2368 -112 eaos.gisClear.SLNK
w -2444 371 100 0 n#16 hwin.hwin#750.in -2504 368 -2384 368 estringouts.gisSimEnabled.DOL
s -1808 1392 100 0 unsuccessful.
s -1808 1424 100 0 of gisdemand. Attemptes to use a user defined port were
s -1808 1456 100 0 N.B. Both xycomIntDemand and userIntDemand write to field A
s -720 2080 100 0 $Id: tcsInterlock.sch,v 1.3 2005/05/09 01:03:17 gemvx Exp $
s -496 -112 100 0 Gemini Telescope Control System
s -1008 592 100 0 The output of gisOverrideState is used as the input for SDIS
s -1008 560 100 0 for both xycomInterlock and userInterlock. It was not
s -1008 528 100 0 connected by wires due to avoid cluttering diagram
s -2754 398 100 0 Force GIS simulation enabled
[cell use]
use bc200tr -3312 -392 -100 0 frame
xform 0 -1632 912
use tcsGIS -576 1319 100 0 tcsGIS#748
xform 0 -384 1456
use hwin -2632 -120 100 0 hwin#745
xform 0 -2560 -80
p -2653 -88 100 0 -1 val(in):2
use eaos -2344 -200 100 0 gisClear
xform 0 -2240 -112
p -2304 -18 100 0 -1 DESC:Clear Interlock
p -2624 -130 100 0 0 OMSL:closed_loop
p -2096 -178 100 0 -1 def(OUT):$(top)gisdemand.A
p -2112 -144 75 768 -1 pproc(OUT):PP
use ebis -344 120 100 0 gisOverriden
xform 0 -240 192
p -541 267 100 0 0 DESC:GIS override allowed
p -336 46 100 0 1 ONAM:Yes
p -336 78 100 0 1 ZNAM:No
use ebis -1352 312 100 0 permitGISOverride
xform 0 -1248 384
p -1549 459 100 0 0 DESC:GIS override allowed
p -1344 238 100 0 1 ONAM:Yes
p -1344 270 100 0 1 ZNAM:No
use estringouts -2360 264 100 0 gisSimEnabled
xform 0 -2256 336
p -2352 414 100 0 -1 DESC:Enable GIS simulation
p -2448 302 100 0 0 VAL:Enabled
use ecalcs -776 -56 100 0 gisOverrideState
xform 0 -656 208
p -704 78 100 0 -1 CALC:(A=1 && B=1)?1:0
p -928 478 100 0 -1 DESC:Calculate whether or not to simulate GIS
use ecalcs -1832 136 100 0 checkGIS
xform 0 -1712 400
p -1920 78 100 0 1 CALC:C=1 || (A=0 && B=3)?1:0
p -1840 670 100 0 -1 DESC:Is GIS override allowed ?
p -1744 462 100 0 1 PINI:NO
use ecalcs -1576 808 100 0 gisdemand
xform 0 -1456 1072
p -1488 990 100 0 -1 CALC:A=2?0:1
p -1632 1342 100 0 -1 DESC:Calculate interlock state
p -1632 990 100 0 0 HHSV:MAJOR
p -1632 1118 100 0 0 HIHI:1
p -1823 645 100 0 0 typ(U0):path
p -1344 1056 100 1024 -1 username(U0):A
use ebos -1352 -88 100 0 overrideGIS
xform 0 -1248 0
p -1392 94 100 0 -1 DESC:Enable/disable GIS override
p -1344 -162 100 0 1 ONAM:Enabled
p -1344 -130 100 0 1 ZNAM:Disabled
use ebos -664 952 100 0 interlockState
xform 0 -560 1040
p -672 1150 100 0 -1 DESC:Interlock state of TCS
p -1008 990 100 0 0 OMSL:closed_loop
p -624 862 100 0 1 ONAM:Interlocked
p -384 862 100 0 1 OSV:MAJOR
p -1008 1022 100 0 0 PINI:YES
p -624 894 100 0 1 ZNAM:Clear
p -384 894 100 0 1 ZSV:NO_ALARM
p -368 1006 100 0 -1 def(OUT):$(sad)interlockState
p -400 1008 75 768 -1 palrm(OUT):MS
p -432 1008 75 768 -1 pproc(OUT):PP
use elongouts -552 1832 100 0 userIntDemand
xform 0 -448 1920
p -691 2265 100 0 0 DESC:Xycom interlock demand
p -736 1838 100 0 0 OMSL:closed_loop
p -240 1886 100 0 -1 def(OUT):$(top)gisdemand.A
p -320 1888 75 768 -1 pproc(OUT):PP
use embbis -1144 1848 100 0 userInterlock
xform 0 -1040 1920
p -1200 2014 100 0 -1 DESC:Simulate GIS inputs
p -1232 1630 100 0 1 DISV:0
p -1234 1624 100 0 0 DTYP:Soft Channel
p -1232 1582 100 0 1 NOBT:2
p -1120 1726 100 0 1 ONST:Interlock Demand
p -848 1726 100 0 1 ONSV:MAJOR
p -1232 1726 100 0 1 ONVL:1
p -1120 1662 100 0 1 THST:Illegal input
p -848 1662 100 0 1 THSV:MAJOR
p -1232 1662 100 0 1 THVL:3
p -1120 1694 100 0 1 TWST:Clear
p -848 1694 100 0 1 TWSV:NO_ALARM
p -1232 1694 100 0 1 TWVL:2
p -1120 1758 100 0 1 ZRST:No Signal
p -848 1758 100 0 1 ZRSV:MAJOR
p -1232 1758 100 0 1 ZRVL:0
p -1504 1870 100 0 -1 def(SDIS):$(top)gisOverrideState
use esubs -1080 776 100 0 interlock
xform 0 -960 1040
p -1088 1310 100 0 -1 DESC:Store interlock state
p -1392 894 100 0 0 INAM:tcsNullInit
p -1024 974 100 0 -1 SNAM:tcsInterlock
use hwin -2696 352 100 0 hwin#750
xform 0 -2600 368
p -2693 360 100 0 -1 val(in):1
[comments]
