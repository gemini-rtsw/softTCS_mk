[schematic2]
uniq 15
[tools]
[detail]
w 1616 1963 100 0 n#1 agSimWfsCommands.agSimWfsCommands#108.CAR 1168 1960 2064 1960 2064 2360 2464 2360 esels.esels#39.INPC
w 1616 2603 100 0 n#2 agSimWfsCommands.agSimWfsCommands#107.CAR 1168 2600 2064 2600 2064 2392 2464 2392 esels.esels#39.INPB
w 1600 3243 100 0 n#3 agSimWfsCommands.agSimWfsCommands#106.CAR 1168 3240 2032 3240 2032 2424 2464 2424 esels.esels#39.INPA
w 3280 3003 100 0 n#4 elongouts.measuring.FLNK 3200 3000 3360 3000 3360 2616 2320 2616 2320 2040 2464 2040 esels.esels#39.SLNK
w 1536 1899 100 0 n#5 agSimWfsCommands.agSimWfsCommands#108.MEASURE 1168 1896 1904 1896 1904 3112 2448 3112 esels.selMeasure.INPC
w 1520 2539 100 0 n#6 agSimWfsCommands.agSimWfsCommands#107.MEASURE 1168 2536 1872 2536 1872 3144 2448 3144 esels.selMeasure.INPB
w 1808 3179 100 0 n#7 agSimWfsCommands.agSimWfsCommands#106.MEASURE 1168 3176 2448 3176 esels.selMeasure.INPA
w 1504 2987 100 0 n#8 agSimWfsCommands.agSimWfsCommands#106.FLNK 1168 2984 1840 2984 1840 2792 2448 2792 esels.selMeasure.SLNK
w 1504 2347 100 0 n#8 agSimWfsCommands.agSimWfsCommands#107.FLNK 1168 2344 1840 2344 1840 2792 junction
w 1504 1707 100 0 n#8 agSimWfsCommands.agSimWfsCommands#108.FLNK 1168 1704 1840 1704 1840 2344 junction
w 2784 3035 100 0 n#9 esels.selMeasure.FLNK 2736 3032 2832 3032 2832 2968 2944 2968 elongouts.measuring.SLNK
w 2840 3003 100 0 n#10 esels.selMeasure.VAL 2736 3000 2944 3000 elongouts.measuring.DOL
w 2840 2251 100 0 n#11 esels.esels#39.VAL 2752 2248 2928 2248 2928 2184 3024 2184 outhier.VAL.p
w 2840 2283 100 0 n#12 esels.esels#39.FLNK 2752 2280 2928 2280 2928 2296 3024 2296 outhier.FLNK.p
w 1178 1202 -100 0 n#8 agSimWfsCommands.agSimWfsCommands#110.FLNK 1168 1200 1840 1200 1840 1704 junction
w 1178 1466 -100 0 n#13 agSimWfsCommands.agSimWfsCommands#110.CAR 1168 1456 2144 1456 2144 2328 2464 2328 esels.esels#39.INPD
w 1178 1402 -100 0 n#14 agSimWfsCommands.agSimWfsCommands#110.MEASURE 1168 1392 1960 1392 1960 3080 2448 3080 esels.selMeasure.INPD
s 2880 3408 100 0 $Id: agSimWfs.sch,v 1.10 2013/10/31 13:37:16 cjm Exp $
s 1440 3296 150 0 and WFS data transfer records
s 2928 1072 100 0 5 Dec 1997
s 2928 1104 100 0 P.B. Taylor
s 3184 1136 100 0 simulated commands
s 3168 1168 100 0 WFS processing control
s 3232 1216 130 0 Gemini TCS
s 2016 3360 150 0 WFS processing control
s 1440 3360 150 0 Set of commands for simulating
[cell use]
use bc200tr 304 936 -100 0 frame
xform 0 1984 2240
use agSimWfsCommands 784 1647 100 0 agSimWfsCommands#108
xform 0 976 1848
p 784 1640 100 0 1 seta:prefix $(oiwfs)dc:
p 784 1608 100 0 1 setb:measure $(oiwfs)
p 784 1576 100 0 1 setc:substring Oi
use agSimWfsCommands 784 2287 100 0 agSimWfsCommands#107
xform 0 976 2488
p 784 2280 100 0 1 seta:prefix $(pwfs2)dc:
p 784 2248 100 0 1 setb:measure $(pwfs2)
p 784 2216 100 0 1 setc:substring P2
use agSimWfsCommands 784 2927 100 0 agSimWfsCommands#106
xform 0 976 3128
p 784 2920 100 0 1 seta:prefix $(pwfs1)dc:
p 784 2888 100 0 1 setb:measure $(pwfs1)
p 784 2856 100 0 1 setc:substring P1
use elongouts 2968 2880 100 0 measuring
xform 0 3072 2968
p 2944 3078 100 0 -1 DESC:Implements measuring status
p 2784 2886 100 0 0 OMSL:closed_loop
p 3056 2872 100 1024 0 name:$(prefix)$(I)
use esels 2472 2720 100 0 selMeasure
xform 0 2592 2984
p 2416 3254 100 0 -1 DESC:Select any measuring state
p 2624 3174 100 0 1 SELM:High Signal
p 2560 2712 100 1024 0 name:$(prefix)$(I)
use esels 2488 1968 100 0 esels#39
xform 0 2608 2232
p 2624 2390 100 0 1 SELM:High Signal
p 2576 1960 100 1024 -1 name:$(prefix)WfsCadSel
use outhier 3016 2144 100 0 VAL
xform 0 3008 2184
use outhier 3016 2256 100 0 FLNK
xform 0 3008 2296
use agSimWfsCommands 784 1143 100 0 agSimWfsCommands#110
xform 0 976 1344
p 784 1136 100 0 1 seta:prefix $(ag)oi:dc:
p 784 1104 100 0 1 setb:measure $(ag)oi:
p 784 1072 100 0 1 setc:substring Oi
[comments]
