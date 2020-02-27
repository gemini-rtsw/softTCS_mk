[schematic2]
uniq 749
[tools]
[detail]
w -2302 34 100 0 n#747 estringouts.gisSimEnabled.FLNK -2128 352 -2080 352 -2080 32 -2464 32 -2464 -112 -2368 -112 eaos.gisClear.SLNK
w -2446 -78 100 0 n#746 hwin.hwin#745.in -2464 -80 -2368 -80 eaos.gisClear.DOL
w -438 194 100 0 n#743 ecalcs.gisOverrideState.FLNK -512 256 -448 256 -448 192 -368 192 ebis.gisOverriden.SLNK
w -470 226 100 0 n#742 ecalcs.gisOverrideState.VAL -512 224 -368 224 ebis.gisOverriden.INP
w -1038 246 100 0 n#738 ebis.permitGISOverride.FLNK -1120 400 -1040 400 -1040 32 junction
w -990 34 100 0 n#738 ebos.overrideGIS.FLNK -1120 32 -800 32 ecalcs.gisOverrideState.SLNK
w -934 418 100 0 n#740 ebis.permitGISOverride.VAL -1120 368 -1008 368 -1008 416 -800 416 ecalcs.gisOverrideState.INPA
w -926 222 100 0 n#739 ebos.overrideGIS.VAL -1120 0 -928 0 -928 384 -800 384 ecalcs.gisOverrideState.INPB
w -1742 2 100 0 n#737 estringouts.gisSimEnabled.OUT -2128 320 -2048 320 -2048 0 -1376 0 ebos.overrideGIS.SLNK
w -2558 518 100 0 n#733 ebis.xycomAbsent.VAL -2784 176 -2560 176 -2560 800 -2400 800 efanouts.gisFan.SELL
w -2286 178 100 0 n#733 junction -2560 176 -1952 176 -1952 544 -1856 544 ecalcs.checkGIS.INPC
w -1862 1714 100 0 n#707 embbi.xycomInterlock.VAL -1952 1616 -1888 1616 -1888 1712 -1776 1712 elongouts.xycomIntDemand.DOL
w -2542 1122 100 0 n#707 junction -1888 1616 -1888 1120 -3136 1120 -3136 864 -2992 864 ecalcs.checkForXycom.INPB
w -1886 878 100 0 n#707 junction -1888 1120 -1888 576 -1856 576 ecalcs.checkGIS.INPB
w -2558 1138 100 0 n#729 embbi.xycomInterlock.U0 -1952 1552 -1904 1552 -1904 1136 -3152 1136 -3152 896 -2992 896 ecalcs.checkForXycom.INPA
w -1902 902 100 0 n#729 junction -1904 1136 -1904 608 -1856 608 ecalcs.checkGIS.INPA
w -2014 558 100 0 n#735 efanouts.gisFan.FLNK -2208 832 -2016 832 -2016 224 -1856 224 ecalcs.checkGIS.SLNK
w -2110 654 100 0 n#734 efanouts.gisFan.LNK1 -2208 800 -2112 800 -2112 448 -2464 448 -2464 336 -2384 336 estringouts.gisSimEnabled.SLNK
w -2526 494 100 0 n#732 ebis.xycomAbsent.FLNK -2784 208 -2528 208 -2528 720 -2448 720 efanouts.gisFan.SLNK
w -2894 322 100 0 n#731 ecalcs.checkForXycom.VAL -2704 704 -2624 704 -2624 320 -3104 320 -3104 224 -3040 224 ebis.xycomAbsent.INP
w -2926 354 100 0 n#730 ecalcs.checkForXycom.FLNK -2704 736 -2656 736 -2656 352 -3136 352 -3136 192 -3040 192 ebis.xycomAbsent.SLNK
w -1550 450 100 0 n#716 ecalcs.checkGIS.FLNK -1568 448 -1472 448 -1472 384 -1376 384 ebis.permitGISOverride.SLNK
w -1502 418 100 0 n#715 ecalcs.checkGIS.VAL -1568 416 -1376 416 ebis.permitGISOverride.INP
w -3022 1778 100 0 n#709 hwin.hwin#708.in -3008 1776 -2976 1776 embbi.xycomInterlock.INP
w -1854 1774 100 0 n#706 embbi.xycomInterlock.FLNK -1952 1808 -1856 1808 -1856 1680 -1776 1680 elongouts.xycomIntDemand.SLNK
w -702 1954 100 0 n#704 embbis.userInterlock.VAL -912 1904 -768 1904 -768 1952 -576 1952 elongouts.userIntDemand.DOL
w -854 1938 100 0 n#703 embbis.userInterlock.FLNK -912 1936 -736 1936 -736 1920 -576 1920 elongouts.userIntDemand.SLNK
w -1214 1022 100 0 n#698 ecalcs.gisdemand.FLNK -1312 1120 -1216 1120 -1216 864 -1104 864 esubs.interlock.SLNK
w -1246 1198 100 0 n#697 junction -1248 1088 -1248 1248 -1104 1248 esubs.interlock.INPA
w -1022 722 100 0 n#697 ecalcs.gisdemand.VAL -1312 1088 -1248 1088 -1248 720 -736 720 -736 1072 -688 1072 ebos.interlockState.DOL
w -766 1042 100 0 n#657 esubs.interlock.FLNK -816 1088 -784 1088 -784 1040 -688 1040 ebos.interlockState.SLNK
s -1808 1392 100 0 unsuccessful.
s -1808 1424 100 0 of gisdemand. Attemptes to use a user defined port were 
s -1808 1456 100 0 N.B. Both xycomIntDemand and userIntDemand write to field A
s -720 2080 100 0 $Id: tcsInterlock.sch,v 1.3 2005/05/09 01:03:17 gemvx Exp $
s -496 -112 100 0 Gemini Telescope Control System
s -1008 592 100 0 The output of gisOverrideState is used as the input for SDIS
s -1008 560 100 0 for both xycomInterlock and userInterlock. It was not
s -1008 528 100 0 connected by wires due to avoid cluttering diagram
s -3200 1728 100 0 This is pins 1 & 2
s -3200 1696 100 0 on Xycom JK1
[cell use]
use tcsGIS -576 1319 100 0 tcsGIS#748
xform 0 -384 1456
use hwin -2632 -120 100 0 hwin#745
xform 0 -2560 -80
p -2653 -88 100 0 -1 val(in):2
use hwin -3176 1736 100 0 hwin#708
xform 0 -3104 1776
p -3197 1768 100 0 -1 val(in):#C0 S24
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
use ebis -3016 120 100 0 xycomAbsent
xform 0 -2912 192
p -3213 267 100 0 0 DESC:GIS override allowed
p -3008 46 100 0 1 ONAM:Yes
p -3008 78 100 0 1 ZNAM:No
use estringouts -2360 264 100 0 gisSimEnabled
xform 0 -2256 336
p -2352 414 100 0 -1 DESC:Enable GIS simulation
p -2448 302 100 0 0 VAL:Enabled
use efanouts -2424 584 100 0 gisFan
xform 0 -2328 736
p -2592 702 100 0 0 SELM:Mask
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
use ecalcs -2968 424 100 0 checkForXycom
xform 0 -2848 688
p -2976 382 100 0 1 CALC:(A=1 && B=0)?1:0
p -3040 958 100 0 -1 DESC:Check if Xycom card is installed
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
use elongouts -1752 1592 100 0 xycomIntDemand
xform 0 -1648 1680
p -1891 2025 100 0 0 DESC:Xycom interlock demand
p -1936 1598 100 0 0 OMSL:closed_loop
p -1440 1646 100 0 -1 def(OUT):$(top)gisdemand.A
p -1520 1648 75 768 -1 pproc(OUT):PP
use embbi -2952 1176 100 0 xycomInterlock
xform 0 -2464 1600
p -2240 1230 100 0 0 COSV:NO_ALARM
p -2656 1899 100 0 -1 DESC:Connects to global interlock event
p -2530 1944 100 0 -1 DTYP:XYCOM-240
p -2432 1518 100 0 0 EIST:
p -2240 1518 100 0 0 EISV:NO_ALARM
p -2624 1518 100 0 0 EIVL:0
p -2432 1422 100 0 0 ELST:
p -2240 1422 100 0 0 ELSV:NO_ALARM
p -2624 1422 100 0 0 ELVL:0
p -2848 1710 100 0 0 EVNT:0
p -2432 1294 100 0 0 FFST:
p -2240 1294 100 0 0 FFSV:NO_ALARM
p -2624 1294 100 0 0 FFVL:0
p -2432 1646 100 0 0 FRST:
p -2240 1646 100 0 0 FRSV:NO_ALARM
p -2624 1646 100 0 0 FRVL:0
p -2432 1326 100 0 0 FTST:
p -2240 1326 100 0 0 FTSV:NO_ALARM
p -2624 1326 100 0 0 FTVL:0
p -2432 1614 100 0 0 FVST:
p -2240 1614 100 0 0 FVSV:NO_ALARM
p -2624 1614 100 0 0 FVVL:0
p -2432 1486 100 0 0 NIST:
p -2240 1486 100 0 0 NISV:NO_ALARM
p -2624 1486 100 0 0 NIVL:0
p -2848 1440 100 0 1 NOBT:2
p -2528 1742 100 0 1 ONST:Interlock Demand
p -2240 1742 100 0 1 ONSV:MAJOR
p -2624 1742 100 0 1 ONVL:1
p -2848 1742 100 0 0 PHAS:0
p -2848 1646 100 0 1 PINI:YES
p -2848 1582 100 0 0 PRIO:LOW
p -2848 1774 100 0 1 SCAN:I/O Intr
p -2848 1230 100 0 0 SIML:0.000000000000000e+00
p -2848 1518 100 0 0 SIMS:NO_ALARM
p -2848 1262 100 0 0 SIOL:0.000000000000000e+00
p -2432 1550 100 0 0 SVST:
p -2240 1550 100 0 0 SVSV:NO_ALARM
p -2624 1550 100 0 0 SVVL:0
p -2432 1582 100 0 0 SXST:
p -2240 1582 100 0 0 SXSV:NO_ALARM
p -2624 1582 100 0 0 SXVL:0
p -2432 1454 100 0 0 TEST:
p -2240 1454 100 0 0 TESV:NO_ALARM
p -2624 1454 100 0 0 TEVL:0
p -2528 1678 100 0 1 THST:Illegal input
p -2240 1678 100 0 1 THSV:MAJOR
p -2624 1678 100 0 1 THVL:3
p -2432 1358 100 0 0 TTST:
p -2240 1358 100 0 0 TTSV:NO_ALARM
p -2624 1358 100 0 0 TTVL:0
p -2432 1390 100 0 0 TVST:
p -2240 1390 100 0 0 TVSV:NO_ALARM
p -2624 1390 100 0 0 TVVL:0
p -2528 1710 100 0 1 TWST:Clear
p -2624 1710 100 0 1 TWVL:2
p -2240 1262 100 0 0 UNSV:NO_ALARM
p -2528 1774 100 0 1 ZRST:No Signal
p -2240 1774 100 0 1 ZRSV:MAJOR
p -2864 1358 100 0 -1 def(SDIS):$(top)gisOverrideState
p -1984 1552 100 1024 -1 username(U0):UDF
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
use bc200tr -3312 -392 -100 0 frame
xform 0 -1632 912
use esubs -1080 776 100 0 interlock
xform 0 -960 1040
p -1088 1310 100 0 -1 DESC:Store interlock state
p -1392 894 100 0 0 INAM:tcsNullInit
p -1024 974 100 0 -1 SNAM:tcsInterlock
[comments]
