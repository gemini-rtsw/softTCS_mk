[schematic2]
uniq 11
[tools]
[detail]
w 328 2739 100 0 n#1 hwin.hwin#74.in 288 2736 368 2736 368 2704 448 2704 egenSub.p2SetFollowStat.INPA
w 400 2643 100 0 n#2 tcsFollowStat.tcsFollowStat#66.VAL 352 2640 448 2640 egenSub.p2SetFollowStat.INPB
w -656 2739 100 0 n#3 hwin.hwin#70.in -704 2736 -608 2736 -608 2704 -512 2704 egenSub.p1SetFollowStat.INPA
w -576 2643 100 0 n#4 tcsFollowStat.tcsFollowStat#57.VAL -640 2640 -512 2640 egenSub.p1SetFollowStat.INPB
w -968 2483 100 0 n#5 hwin.hwin#75.in -1008 2480 -928 2480 tcsFollowStat.tcsFollowStat#57.DISV
w 52 2483 100 0 n#6 hwin.hwin#77.in 40 2480 64 2480 tcsFollowStat.tcsFollowStat#66.DISV
w 1068 2501 100 0 n#7 hwin.hwin#80.in 1056 2496 1112 2496 tcsFollowStat.tcsFollowStat#67.DISV
w -444 1571 100 0 n#8 eevents.eevents#91.FLNK -472 1568 -416 1568 -416 1680 -240 1680 tcsCommonSubsys.tcsCommonSubsys#93.SLNK
w -368 1739 100 0 n#9 hwinl.hwinl#89.in -496 1736 -240 1736 tcsCommonSubsys.tcsCommonSubsys#93.SUBSYS_STATE
w -468 1811 100 0 n#10 hwinl.hwinl#87.in -496 1808 -440 1808 -440 1768 -240 1768 tcsCommonSubsys.tcsCommonSubsys#93.PRESENCE
s 784 2896 100 0 $Id: tcsAgSubsys.sch,v 1.5 2010/07/08 12:33:49 cjm Exp $
s 1056 704 100 0 Gemini Telescope Control System
s 1024 656 100 0 Subsystem simulation & present flags
[cell use]
use bc200tr -1792 424 -100 0 frame
xform 0 -112 1728
use hwin 96 2695 100 0 hwin#74
xform 0 192 2736
p 99 2728 100 0 -1 val(in):1
use egenSub 448 1943 100 0 p2SetFollowStat
xform 0 592 2368
p 225 1717 100 0 0 FTA:LONG
p 225 1717 100 0 0 FTB:LONG
p 640 1904 100 0 1 SCAN:1 second
p 640 1856 100 0 1 SNAM:tcsFollowStat
use hwin -896 2695 100 0 hwin#70
xform 0 -800 2736
p -893 2728 100 0 -1 val(in):0
use egenSub -512 1943 100 0 p1SetFollowStat
xform 0 -368 2368
p -735 1717 100 0 0 FTA:LONG
p -735 1717 100 0 0 FTB:LONG
p -320 1904 100 0 1 SCAN:1 second
p -320 1856 100 0 1 SNAM:tcsFollowStat
use tcsFollowStat 1176 2440 100 0 tcsFollowStat#67
xform 0 1256 2584
p 1168 2432 100 0 1 seta:subsys $(ag)oi:
p 1168 2400 100 0 1 setb:subnam oiwfs
use tcsFollowStat 128 2424 100 0 tcsFollowStat#66
xform 0 208 2568
p 120 2416 100 0 1 seta:subsys $(ag)p2:
p 120 2384 100 0 1 setb:subnam pwfs2
use tcsFollowStat -864 2424 100 0 tcsFollowStat#57
xform 0 -784 2568
p -872 2416 100 0 1 seta:subsys $(ag)p1:
p -872 2384 100 0 1 setb:subnam pwfs1
use hwin -1200 2464 100 0 hwin#75
xform 0 -1104 2480
p -1197 2472 100 0 -1 val(in):$(noFollow)
use hwin -144 2464 100 0 hwin#77
xform 0 -48 2480
p -141 2472 100 0 -1 val(in):$(noFollow)
use hwin 864 2480 100 0 hwin#80
xform 0 960 2496
p 867 2488 100 0 -1 val(in):$(noFollow)
use hwinl -888 1736 100 0 hwinl#87
xform 0 -688 1784
p -870 1800 100 0 -1 val(in):$(subsys)$(record).VAL
use hwinl -888 1664 100 0 hwinl#89
xform 0 -688 1712
p -870 1728 100 0 -1 val(in):$(subsys)state.VAL
use eevents -760 1472 100 0 eevents#91
xform 0 -616 1536
p -669 1444 100 0 -1 SCAN:1 second
p -704 1414 100 1024 -1 name:$(tcs)$(subnam)Event
use tcsCommonSubsys -208 1656 100 0 tcsCommonSubsys#93
xform 0 -24 1704
[comments]
