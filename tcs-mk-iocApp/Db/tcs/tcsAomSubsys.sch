[schematic2]
uniq 5
[tools]
[detail]
w -816 2003 100 0 n#1 hwin.hwin#71.in -840 2000 -792 2000 -792 1744 -760 1744 tcsFollowStat.tcsFollowStat#57.DISV
w -584 2003 100 0 n#1 junction -792 2000 -376 2000 -376 1744 -312 1744 tcsFollowStat.tcsFollowStat#66.DISV
w -160 2003 100 0 n#1 junction -376 2000 56 2000 56 1744 112 1744 tcsFollowStat.tcsFollowStat#67.DISV
w -776 1427 100 0 n#2 hwinl.hwinl#76.in -840 1424 -712 1424 -712 1400 -696 1400 tcsCommonSubsys.tcsCommonSubsys#82.PRESENCE
w -808 1339 100 0 n#3 hwinl.hwinl#78.in -840 1336 -776 1336 -776 1368 -696 1368 tcsCommonSubsys.tcsCommonSubsys#82.SUBSYS_STATE
w -796 1187 100 0 n#4 eevents.eevents#80.FLNK -816 1184 -776 1184 -776 1312 -696 1312 tcsCommonSubsys.tcsCommonSubsys#82.SLNK
s 176 2032 100 0 $Id: tcsAomSubsys.sch,v 1.2 2010/07/08 12:34:20 cjm Exp $
s 432 800 100 0 Gemini Telescope Control System
s 400 752 100 0 Subsystem simulation & present flags
[cell use]
use bb200tr -1600 520 -100 0 frame
xform 0 -320 1344
use tcsFollowStat 176 1688 100 0 tcsFollowStat#67
xform 0 256 1832
p 168 1680 100 0 1 seta:subsys $(aom)ngsPr3
p 168 1648 100 0 1 setb:subnam ngsPr3
use tcsFollowStat -256 1688 100 0 tcsFollowStat#66
xform 0 -176 1832
p -264 1680 100 0 1 seta:subsys $(aom)ngsPr2
p -264 1648 100 0 1 setb:subnam ngsPr2
use tcsFollowStat -696 1688 100 0 tcsFollowStat#57
xform 0 -616 1832
p -704 1680 100 0 1 seta:subsys $(aom)ngsPr1
p -704 1648 100 0 1 setb:subnam ngsPr1
use hwin -1032 1984 100 0 hwin#71
xform 0 -936 2000
p -1029 1992 100 0 -1 val(in):$(noFollow)
use hwinl -1232 1352 100 0 hwinl#76
xform 0 -1032 1400
p -1214 1416 100 0 -1 val(in):$(subsys)$(record).VAL
use hwinl -1232 1264 100 0 hwinl#78
xform 0 -1032 1312
p -1214 1328 100 0 -1 val(in):$(subsys)state.VAL
use eevents -1104 1088 100 0 eevents#80
xform 0 -960 1152
p -1013 1060 100 0 -1 SCAN:1 second
p -1081 1034 100 1024 -1 name:$(tcs)$(subnam)Event
use tcsCommonSubsys -664 1288 100 0 tcsCommonSubsys#82
xform 0 -480 1336
[comments]
