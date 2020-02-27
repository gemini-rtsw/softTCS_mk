[schematic2]
uniq 12
[tools]
[detail]
w 424 1939 100 0 n#1 hwin.hwin#81.in 400 1936 448 1936 448 1824 480 1824 tcsGsaoiFollowStat.tcsGsaoiFollowStat#80.ODGW
w -64 2003 100 0 n#2 hwin.hwin#78.in -96 2000 -32 2000 -32 1824 0 1824 tcsGsaoiFollowStat.tcsGsaoiFollowStat#77.ODGW
w -456 2003 100 0 n#3 hwin.hwin#75.in -480 2000 -432 2000 -432 1888 -400 1888 tcsGsaoiFollowStat.tcsGsaoiFollowStat#74.ODGW
w -845 1944 100 0 n#4 hwin.hwin#72.in -848 2000 -848 1888 -816 1888 tcsGsaoiFollowStat.tcsGsaoiFollowStat#71.ODGW
w -880 1643 100 0 n#5 hwin.hwin#83.in -904 1640 -856 1640 -856 1728 -808 1728 tcsGsaoiFollowStat.tcsGsaoiFollowStat#71.DISV
w -460 1539 100 0 n#6 hwin.hwin#85.in -488 1600 -432 1600 -432 1728 -392 1728 tcsGsaoiFollowStat.tcsGsaoiFollowStat#74.DISV
w -264 1603 100 0 n#6 junction -432 1600 -96 1600 -96 1664 0 1664 tcsGsaoiFollowStat.tcsGsaoiFollowStat#77.DISV
w 140 1605 100 0 n#6 junction -96 1600 376 1600 376 1664 480 1664 tcsGsaoiFollowStat.tcsGsaoiFollowStat#80.DISV
w -252 1467 100 0 n#7 hwinl.hwinl#87.in -280 1464 -224 1464 -224 1312 280 1312 tcsCommonSubsys.tcsCommonSubsys#91.PRESENCE
w -896 955 100 0 n#8 elongouts.elongouts#8.DOL -744 952 -1048 952 tcsGsaoiState.tcsGsaoiState#82.STATE
w -960 875 100 0 n#9 tcsGsaoiState.tcsGsaoiState#82.FLNK -1048 872 -872 872 -872 920 -744 920 elongouts.elongouts#8.SLNK
w -470 962 -100 0 n#10 elongouts.elongouts#8.FLNK -488 952 -88 952 -88 1224 280 1224 tcsCommonSubsys.tcsCommonSubsys#91.SLNK
w -478 922 -100 0 n#11 elongouts.elongouts#8.VAL -488 920 -176 920 -176 1280 280 1280 tcsCommonSubsys.tcsCommonSubsys#91.SUBSYS_STATE
s 400 752 100 0 Subsystem simulation & present flags
s 432 800 100 0 Gemini Telescope Control System
s 176 2032 100 0 $Id: tcsGsaoiSubsys.sch,v 1.5 2010/07/08 12:36:42 cjm Exp $
[cell use]
use bb200tr -1600 520 -100 0 frame
xform 0 -320 1344
use hwin 208 1895 100 0 hwin#81
xform 0 304 1936
p 211 1928 100 0 -1 val(in):3
use tcsGsaoiFollowStat 480 1607 100 0 tcsGsaoiFollowStat#80
xform 0 624 1752
p 512 1600 100 0 1 seta:subnam odgw4
use hwin -288 1959 100 0 hwin#78
xform 0 -192 2000
p -285 1992 100 0 -1 val(in):2
use tcsGsaoiFollowStat 0 1607 100 0 tcsGsaoiFollowStat#77
xform 0 144 1752
p 32 1600 100 0 1 seta:subnam odgw3
use hwin -672 1959 100 0 hwin#75
xform 0 -576 2000
p -669 1992 100 0 -1 val(in):1
use tcsGsaoiFollowStat -400 1671 100 0 tcsGsaoiFollowStat#74
xform 0 -256 1816
p -368 1664 100 0 1 seta:subnam odgw2
use tcsGsaoiFollowStat -816 1671 100 0 tcsGsaoiFollowStat#71
xform 0 -672 1816
p -768 1664 100 0 1 seta:subnam odgw1
use hwin -1040 1959 100 0 hwin#72
xform 0 -944 2000
p -1037 1992 100 0 -1 val(in):0
use tcsGsaoiState -1256 856 100 0 tcsGsaoiState#82
xform 0 -1128 920
use hwin -1096 1624 100 0 hwin#83
xform 0 -1000 1640
p -1093 1632 100 0 -1 val(in):$(noFollow)
use hwin -680 1584 100 0 hwin#85
xform 0 -584 1600
p -677 1592 100 0 -1 val(in):$(noFollow)
use hwinl -672 1392 100 0 hwinl#87
xform 0 -472 1440
p -654 1456 100 0 -1 val(in):$(subsys)$(record).VAL
use tcsCommonSubsys 312 1200 100 0 tcsCommonSubsys#91
xform 0 496 1248
use elongouts -744 856 100 0 elongouts#8
xform 0 -616 920
p -658 880 100 0 0 SCAN:Passive
p -632 824 100 1024 -1 name:$(tcs)$(subnam)PreState
p -742 998 100 0 -1 DESC:Reflect subsystem state
p -1006 975 100 0 0 def(DOL):0.000000000000000e+00
p -816 960 75 1280 0 pproc(DOL):CA
p -784 960 75 1280 0 palrm(DOL):MS
p -904 838 100 0 1 OMSL:closed_loop
[comments]
