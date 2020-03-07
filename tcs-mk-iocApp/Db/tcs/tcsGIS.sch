[schematic2]
uniq 15
[tools]
[detail]
w -1344 739 100 0 n#1 ebos.ebos#710.FLNK -1696 736 -992 736 -992 352 -3104 352 -3104 -128 -2336 -128 ecalcs.ecalcs#716.SLNK
w -656 1491 100 0 n#2 ebos.ebos#696.FLNK -1024 1488 -288 1488 -288 1088 -3104 1088 -3104 544 -2336 544 ecalcs.ecalcs#707.SLNK
w -2392 259 100 0 n#3 hwin.hwin#723.in -2448 256 -2336 256 ecalcs.ecalcs#716.INPA
w -2040 99 100 0 n#4 ecalcs.ecalcs#716.FLNK -2048 96 -2032 96 -2032 32 -1952 32 ebos.ebos#718.SLNK
w -2000 67 100 0 n#5 ecalcs.ecalcs#716.VAL -2048 64 -1952 64 ebos.ebos#718.DOL
w -2392 931 100 0 n#6 hwin.hwin#711.in -2448 928 -2336 928 ecalcs.ecalcs#707.INPA
w -2040 771 100 0 n#7 ecalcs.ecalcs#707.FLNK -2048 768 -2032 768 -2032 704 -1952 704 ebos.ebos#710.SLNK
w -2000 739 100 0 n#8 ecalcs.ecalcs#707.VAL -2048 736 -1952 736 ebos.ebos#710.DOL
w -1368 1523 100 0 n#9 ecalcs.calc1.FLNK -1376 1520 -1360 1520 -1360 1456 -1280 1456 ebos.ebos#696.SLNK
w -1296 1491 100 0 n#10 junction -1312 1488 -1280 1488 ebos.ebos#696.DOL
w -1344 1491 100 0 n#10 ecalcs.calc1.VAL -1376 1488 -1312 1488 -1312 1728 -1792 1728 -1792 1680 -1664 1680 ecalcs.calc1.INPA
w -1856 1539 100 0 n#11 efanouts.fanout.LNK1 -1936 1536 -1776 1536 -1776 1296 -1664 1296 ecalcs.calc1.SLNK
w -2384 1395 100 0 n#12 ecalcs.ecalcs#676.FLNK -2512 1392 -2256 1392 -2256 1456 -2176 1456 efanouts.fanout.SLNK
w -2424 1363 100 0 n#13 ecalcs.ecalcs#676.VAL -2512 1360 -2336 1360 -2336 1536 -2128 1536 efanouts.fanout.SELL
w -2854 1562 -100 0 n#14 hwin.hwin#675.in -2872 1552 -2800 1552 ecalcs.ecalcs#676.INPA
s -1440 32 100 0 Laser Vignetting Interlock OFF
s -1440 704 100 0 Laser Vignetting Interlock ON
s -768 1456 100 0 Laser Interlock System "heartbeat"
s -736 2080 100 0 $Id: tcsGIS.sch,v 1.2 2011/01/27 20:36:40 gemvx Exp $
s -2336 1856 300 0 Manage the Laser System "heartbeat" Transition
s -496 -176 100 0 Gemini Telescope Control System
[cell use]
use bc200tr -3312 -392 -100 0 frame
xform 0 -1632 912
use hwin -2640 887 100 0 hwin#711
xform 0 -2544 928
p -2896 912 100 0 -1 val(in):$(top)domeVignette
use hwin -3064 1511 100 0 hwin#675
xform 0 -2968 1552
p -3096 1600 100 0 -1 val(in):$(top)checkForXycom.VAL
use hwin -2640 215 100 0 hwin#723
xform 0 -2544 256
p -2896 240 100 0 -1 val(in):$(top)domeVignette
use ebos -1952 -57 100 0 ebos#718
xform 0 -1824 32
p -2272 -18 100 0 0 OMSL:closed_loop
p -2272 -114 100 0 0 ONAM:1
p -2272 -82 100 0 0 ZNAM:0
p -1840 -64 100 1024 -1 name:$(top)LaserIntOFF
use ebos -1952 615 100 0 ebos#710
xform 0 -1824 704
p -2272 654 100 0 0 OMSL:closed_loop
p -2272 558 100 0 0 ONAM:1
p -2272 590 100 0 0 ZNAM:0
p -1840 608 100 1024 -1 name:$(top)LaserIntON
use ebos -1280 1367 100 0 ebos#696
xform 0 -1152 1456
p -1600 1406 100 0 0 OMSL:closed_loop
p -1600 1310 100 0 0 ONAM:1
p -1600 1342 100 0 0 ZNAM:0
p -1168 1360 100 1024 -1 name:$(top)LaserInterlock
use ecalcs -2312 -216 -100 0 ecalcs#716
xform 0 -2192 48
p -2240 -18 100 0 1 CALC:(A=0)?1:0
p -2368 304 100 0 -1 DESC:Laser Dome Vignetting OFF
p -2240 -50 100 0 1 SCAN:Passive
p -2160 -256 100 1024 1 name:$(top)LaserVignettingOFF
use ecalcs -2312 456 -100 0 ecalcs#707
xform 0 -2192 720
p -2240 654 100 0 1 CALC:(A=0)?0:1
p -2368 976 100 0 -1 DESC:Laser Dome Vignetting ON
p -2240 622 100 0 1 SCAN:Passive
p -2160 416 100 1024 1 name:$(top)LaserVignettingON
use ecalcs -2776 1080 100 0 ecalcs#676
xform 0 -2656 1344
p -2704 1200 100 0 1 CALC:(A=0)?1:0
p -2784 1662 100 0 -1 DESC:Check xycomm card
p -2704 1246 100 0 1 SCAN:1 second
p -2678 1121 100 1024 1 name:$(top)XycomCalc
use ecalcs -1640 1208 -100 0 calc1
xform 0 -1520 1472
p -1568 1406 100 0 1 CALC:(A+1)%2
p -1648 1790 100 0 -1 DESC:HeartBeat transition
p -1568 1374 100 0 1 SCAN:Passive
p -1488 1168 100 1024 1 name:$(top)LaserHeartBeat
use efanouts -2152 1320 100 0 fanout
xform 0 -2056 1472
p -2064 1630 100 0 -1 DESC:Select string output
p -2320 1662 100 0 0 SCAN:Passive
p -2112 1262 100 0 1 SELM:Specified
p -2064 1312 100 1024 0 name:$(top)LaserGISfan
[comments]
