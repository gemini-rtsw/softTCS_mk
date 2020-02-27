[schematic2]
uniq 131
[tools]
[detail]
w 1522 1483 100 0 n#119 mechSimCad8.mechSimCad8#129.FLNK 992 1472 2112 1472 2112 1824 junction
w 1538 1563 100 0 n#130 mechSimCad8.mechSimCad8#129.VAL 992 1552 2144 1552 2144 2256 2368 2256 esels.selObserve.INPE
w 1522 1835 100 0 n#119 mechSimCad8.mechSimCad8#126.FLNK 992 1824 2112 1824 2112 2000 junction
w 1522 2251 100 0 n#119 mechSimCad8.mechSimCad8#125.FLNK 992 2240 2112 2240 junction
w 2210 2011 100 0 n#119 elongouts.measuring.FLNK 1904 2976 2112 2976 2112 2000 2368 2000 esels.selObserve.SLNK
w 1522 2603 100 0 n#119 mechSimCad8.mechSimCad8#123.FLNK 992 2592 2112 2592 junction
w 1506 1915 100 0 n#128 mechSimCad8.mechSimCad8#126.VAL 992 1904 2080 1904 2080 2288 2368 2288 esels.selObserve.INPD
w 1650 2331 100 0 n#127 mechSimCad8.mechSimCad8#125.VAL 992 2320 2368 2320 esels.selObserve.INPC
w 1506 2683 100 0 n#124 mechSimCad8.mechSimCad8#123.VAL 992 2672 2080 2672 2080 2352 2368 2352 esels.selObserve.INPB
w 1730 2395 100 0 n#122 mechSimCad8.mechSimCad8#92.VAL 992 3024 1152 3024 1152 2384 2368 2384 esels.selObserve.INPA
w 2442 2955 100 0 n#121 elongouts.measuring.VAL 1904 2944 3040 2944 outhier.MEASURE.p
w 1290 2955 100 0 n#117 mechSimCad8.mechSimCad8#92.FLNK 992 2944 1648 2944 elongouts.measuring.SLNK
w 2898 2347 100 0 n#104 esels.selObserve.FLNK 2656 2240 2816 2240 2816 2336 3040 2336 outhier.FLNK.p
w 2818 2219 100 0 n#103 esels.selObserve.VAL 2656 2208 3040 2208 outhier.CAR.p
s 2720 1728 100 0 never ends in CAR_ERROR
s 2720 1760 100 0 to combine the CAR values as this simulation
s 2720 1792 100 0 Note we can use a simple selection record
s 2896 1152 100 0 Sciences Ltd.
s 2896 1184 100 0 Observatory
s 2896 1216 100 0 Copyright
s 3232 1216 130 0 Gemini TCS
s 3168 1168 100 0 Simulated AGWFS Observe command
s 2928 1104 100 0 C.J. Mayer
s 2928 1072 100 0 22 Nov 1999
s 2880 3408 100 0 $Id: agSimWfsCommands.sch,v 1.5 2004/03/24 14:57:14 cjm Exp $
s 1584 3296 200 0 Implement the WFS commands of PWFS1
[cell use]
use mechSimCad8 768 1383 100 0 mechSimCad8#129
xform 0 880 1488
p 768 1344 100 0 1 setb:cadname detSigModeAo
p 768 1312 100 0 1 setc:delay 1.0
p 788 1260 100 0 0 sete:ftva DOUBLE
p 808 1240 100 0 0 setf:ftvb LONG
p 828 1220 100 0 0 setg:ftvc STRING
p 848 1200 100 0 0 seth:ftvd STRING
p 868 1180 100 0 0 seti:ftve STRING
use mechSimCad8 768 1735 100 0 mechSimCad8#126
xform 0 880 1840
p 768 1696 100 0 1 setb:cadname detSigModeSeq
p 768 1664 100 0 1 setc:delay 1.0
p 788 1612 100 0 0 sete:ftva DOUBLE
p 808 1592 100 0 0 setf:ftvb DOUBLE
p 828 1572 100 0 0 setg:ftvc LONG
p 848 1552 100 0 0 seth:ftvd DOUBLE
p 868 1532 100 0 0 seti:ftve STRING
use mechSimCad8 768 2151 100 0 mechSimCad8#125
xform 0 880 2256
p 768 2112 100 0 1 setb:cadname detSigModeSeqDark
p 768 2080 100 0 1 setc:delay 1.0
p 788 2028 100 0 0 sete:ftva STRING
p 808 2008 100 0 0 setf:ftvb STRING
p 828 1988 100 0 0 setg:ftvc STRING
p 848 1968 100 0 0 seth:ftvd STRING
p 868 1948 100 0 0 seti:ftve STRING
use mechSimCad8 768 2855 100 0 mechSimCad8#92
xform 0 880 2960
p 768 2816 100 0 1 setb:cadname observe
p 768 2784 100 0 1 setc:delay 1.0
p 788 2732 100 0 0 sete:ftva LONG
p 808 2712 100 0 0 setf:ftvb DOUBLE
p 828 2692 100 0 0 setg:ftvc LONG
p 848 2672 100 0 0 seth:ftvd STRING
p 868 2652 100 0 0 seti:ftve STRING
use mechSimCad8 768 2503 100 0 mechSimCad8#123
xform 0 880 2608
p 768 2464 100 0 1 setb:cadname detSigInit
p 768 2432 100 0 1 setc:delay 1.0
p 788 2380 100 0 0 sete:ftva STRING
p 808 2360 100 0 0 setf:ftvb STRING
p 828 2340 100 0 0 setg:ftvc STRING
p 848 2320 100 0 0 seth:ftvd STRING
p 868 2300 100 0 0 seti:ftve STRING
use outhier 3032 2296 100 0 FLNK
xform 0 3024 2336
use outhier 3032 2168 100 0 CAR
xform 0 3024 2208
use outhier 3008 2903 100 0 MEASURE
xform 0 3024 2944
use elongouts 1648 2855 100 0 measuring
xform 0 1776 2944
p 1616 3040 100 0 -1 DESC:Shows if WFS is integrating
p 1488 2862 100 0 0 OMSL:closed_loop
p 1296 2976 100 0 -1 def(DOL):$(prefix)observe.VALC
p 1760 2848 100 1024 0 name:$(measure)$(I)
use bc200tr 304 936 -100 0 frame
xform 0 1984 2240
use esels 2368 1927 100 0 selObserve
xform 0 2512 2192
p 2320 2480 100 0 -1 DESC:Select from observe commands
p 2512 1952 100 0 1 SELM:High Signal
p 2480 1920 100 1024 0 name:$(prefix)$(I)
[comments]
