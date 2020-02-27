[schematic2]
uniq 884
[tools]
[detail]
w -78 1307 100 0 n#883 efanouts.valfan1.LNK1 16 1584 144 1584 144 1296 -240 1296 -240 1168 -128 1168 estringouts.p2bl.SLNK
w -246 1595 100 0 n#881 ecalcs.mask2.VAL -288 1472 -256 1472 -256 1584 -176 1584 efanouts.valfan1.SELL
w -286 1515 100 0 n#880 ecalcs.mask2.FLNK -288 1504 -224 1504 efanouts.valfan1.SLNK
w -2094 2827 100 0 n#851 junction -2560 2592 -2560 2816 -1568 2816 ecalcs.p2Vis.INPA
w -2294 2603 100 0 n#851 junction -2560 2368 -2560 2592 -1968 2592 ecalcs.p1Vis.INPA
w -2494 2379 100 0 n#851 junction -2560 1792 -2560 2368 -2368 2368 ecalcs.z.INPA
w -1886 1803 100 0 n#851 junction -2560 1568 -2560 1792 -1152 1792 ecalcs.rot.INPA
w -2078 1579 100 0 n#851 junction -2560 1344 -2560 1568 -1536 1568 ecalcs.az.INPA
w -2294 1355 100 0 n#851 junction -2560 1120 -2560 1344 -1968 1344 ecalcs.airmass.INPA
w -2558 1131 100 0 n#851 inhier.MASK.P -2672 1120 -2384 1120 ecalcs.el.INPA
w -1854 2907 100 0 n#851 junction -2560 2816 -2560 2896 -1088 2896 ecalcs.mask1.INPA
w -1678 1851 100 0 n#851 junction -2560 1840 -736 1840 -736 1664 -576 1664 ecalcs.mask2.INPA
w -614 2555 100 0 n#878 efanouts.valfan.FLNK -480 2848 -400 2848 -400 2544 -768 2544 -768 1280 -576 1280 ecalcs.mask2.SLNK
w -742 2827 100 0 n#877 ecalcs.mask1.VAL -800 2704 -752 2704 -752 2816 -672 2816 efanouts.valfan.SELL
w -278 1915 100 0 n#874 efanouts.valfan.LNK6 -480 2656 -368 2656 -368 1904 -128 1904 estringouts.p1bl.SLNK
w -262 2091 100 0 n#872 efanouts.valfan.LNK5 -480 2688 -336 2688 -336 2080 -128 2080 estringouts.elbl.SLNK
w -422 2731 100 0 n#871 efanouts.valfan.LNK4 -480 2720 -304 2720 -304 2224 -128 2224 estringouts.ambl.SLNK
w -406 2763 100 0 n#870 efanouts.valfan.LNK3 -480 2752 -272 2752 -272 2368 -128 2368 estringouts.azbl.SLNK
w -390 2795 100 0 n#869 efanouts.valfan.LNK2 -480 2784 -240 2784 -240 2528 -128 2528 estringouts.rotbl.SLNK
w -30 2747 100 0 n#868 estringouts.zoutbl.FLNK 128 2832 208 2832 208 2736 -208 2736 -208 2672 -128 2672 estringouts.zinbl.SLNK
w -334 2827 100 0 n#867 efanouts.valfan.LNK1 -480 2816 -128 2816 estringouts.zoutbl.SLNK
w -790 2747 100 0 n#865 ecalcs.mask1.FLNK -800 2736 -720 2736 efanouts.valfan.SLNK
w -1182 2523 100 0 n#864 ecalcs.p2Vis.FLNK -1280 2656 -1216 2656 -1216 2512 -1088 2512 ecalcs.mask1.SLNK
w -1678 1899 100 0 n#859 ecalcs.rot.FLNK -864 1632 -800 1632 -800 1888 -2496 1888 -2496 1984 -2368 1984 ecalcs.z.SLNK
w -1654 2443 100 0 n#858 ecalcs.p1Vis.FLNK -1680 2432 -1568 2432 ecalcs.p2Vis.SLNK
w -2054 2219 100 0 n#857 ecalcs.z.FLNK -2080 2208 -1968 2208 ecalcs.p1Vis.SLNK
w -1230 1419 100 0 n#854 ecalcs.az.FLNK -1248 1408 -1152 1408 ecalcs.rot.SLNK
w -1638 1195 100 0 n#853 ecalcs.airmass.FLNK -1680 1184 -1536 1184 ecalcs.az.SLNK
w -2062 971 100 0 n#852 ecalcs.el.FLNK -2096 960 -1968 960 ecalcs.airmass.SLNK
w -2550 747 100 0 n#846 inhier.SLNK.P -2656 736 -2384 736 ecalcs.el.SLNK
s -1760 2064 100 0 screens.
s -1760 2096 100 0 of outputs on the engineering
s -1760 2128 100 0 turn on and off the visibility
s -1760 2160 100 0 These calc records are used to
s -304 2976 100 0 $Id: tcsLimitTimes.sch,v 1.1 2008/05/01 15:31:25 cjm Exp $
[cell use]
use estringouts -128 2743 100 0 zoutbl
xform 0 0 2816
p 528 2288 100 0 0 VAL:
p 64 2768 100 0 -1 def(OUT):$(sad)timeToBlindSpotExit
p 128 2800 75 768 -1 pproc(OUT):PP
use estringouts -128 2007 100 0 elbl
xform 0 0 2080
p 528 1552 100 0 0 VAL:
p 64 2032 100 0 -1 def(OUT):$(sad)currentTimeToSet
p 128 2064 75 768 -1 pproc(OUT):PP
use estringouts -128 2151 100 0 ambl
xform 0 0 2224
p 528 1696 100 0 0 VAL:
p 64 2176 100 0 -1 def(OUT):$(sad)timeToAmSet
p 128 2208 75 768 -1 pproc(OUT):PP
use estringouts -128 2295 100 0 azbl
xform 0 0 2368
p 528 1840 100 0 0 VAL:
p 64 2320 100 0 -1 def(OUT):$(sad)timeToAzlim
p 128 2352 75 768 -1 pproc(OUT):PP
use estringouts -128 2455 100 0 rotbl
xform 0 0 2528
p 528 2000 100 0 0 VAL:
p 64 2480 100 0 -1 def(OUT):$(sad)timeToRotlim
p 128 2512 75 768 -1 pproc(OUT):PP
use estringouts -128 2599 100 0 zinbl
xform 0 0 2672
p 528 2144 100 0 0 VAL:
p 64 2624 100 0 -1 def(OUT):$(sad)timeToBlindSpot
p 128 2656 75 768 -1 pproc(OUT):PP
use estringouts -128 1831 100 0 p1bl
xform 0 0 1904
p 528 1376 100 0 0 VAL:
p 64 1856 100 0 -1 def(OUT):$(sad)timeToP1lim
p 128 1888 75 768 -1 pproc(OUT):PP
use estringouts -128 1095 100 0 p2bl
xform 0 0 1168
p 528 640 100 0 0 VAL:
p 64 1120 100 0 -1 def(OUT):$(sad)timeToP2lim
p 128 1152 75 768 -1 pproc(OUT):PP
use efanouts -720 2599 100 0 valfan
xform 0 -600 2752
p -864 2718 100 0 0 SELM:Mask
use efanouts -224 1367 100 0 valfan1
xform 0 -104 1520
p -368 1486 100 0 0 SELM:Mask
use ecalcs -1568 2343 100 0 p2Vis
xform 0 -1424 2608
p -1488 2544 100 0 -1 CALC:(A&64)?0:1
p -1775 2774 100 0 0 DESC:P2 times valid
use ecalcs -1968 2119 100 0 p1Vis
xform 0 -1824 2384
p -1888 2320 100 0 -1 CALC:(A&32)?0:1
p -2175 2550 100 0 0 DESC:P1 times valid
use ecalcs -2368 1895 100 0 z
xform 0 -2224 2160
p -2288 2096 100 0 -1 CALC:(A&16)?0:1
p -2575 2326 100 0 0 DESC:zenith region times valid
use ecalcs -2384 647 100 0 el
xform 0 -2240 912
p -2304 848 100 0 -1 CALC:(A&1)?0:1
p -2591 1078 100 0 0 DESC:elevation limit valid
use ecalcs -1968 871 100 0 airmass
xform 0 -1824 1136
p -1888 1072 100 0 -1 CALC:(A&2)?0:1
p -2175 1302 100 0 0 DESC:air mass limit valid
use ecalcs -1536 1095 100 0 az
xform 0 -1392 1360
p -1456 1296 100 0 -1 CALC:(A&4)?0:1
p -1743 1526 100 0 0 DESC:azimuth wrap limit valid
use ecalcs -1152 1319 100 0 rot
xform 0 -1008 1584
p -1072 1520 100 0 -1 CALC:(A&8)?0:1
p -1359 1750 100 0 0 DESC:rotator wrap limit valid
use ecalcs -1088 2423 100 0 mask1
xform 0 -944 2688
p -992 2624 100 0 1 CALC:A&&63
use ecalcs -576 1191 100 0 mask2
xform 0 -432 1456
p -496 1392 100 0 -1 CALC:(A&&64)?0:1
use inhier -2688 1079 100 0 MASK
xform 0 -2672 1120
use inhier -2672 695 100 0 SLNK
xform 0 -2656 736
use eborderC -2880 503 100 0 eborderC#658
xform 0 -1200 1808
p -304 656 100 768 -1 author:D.L.Terrett
p -320 624 100 768 -1 date:1997/07/01
p -80 704 200 768 -1 file:tcsLimits.sch
[comments]
