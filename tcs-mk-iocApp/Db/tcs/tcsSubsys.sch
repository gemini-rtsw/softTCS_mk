[schematic2]
uniq 5
[tools]
[detail]
w -430 1733 100 0 n#1 hwin.hwin#58.in -448 1728 -384 1728 tcsFollowStat.tcsFollowStat#57.DISV
w -1040 1459 100 0 n#2 hwinl.hwinl#61.in -1072 1456 -824 1456 tcsCommonSubsys.tcsCommonSubsys#62.SUBSYS_STATE
w -1016 1547 100 0 n#3 hwinl.hwinl#60.in -1072 1544 -960 1544 -960 1488 -824 1488 tcsCommonSubsys.tcsCommonSubsys#62.PRESENCE
w -1020 1307 100 0 n#4 eevents.eevents#67.FLNK -1048 1304 -992 1304 -992 1400 -824 1400 tcsCommonSubsys.tcsCommonSubsys#62.SLNK
s 400 752 100 0 Subsystem simulation & present flags
s 432 800 100 0 Gemini Telescope Control System
s 320 2032 100 0 $Id: tcsSubsys.sch,v 1.7 2010/07/08 12:36:12 cjm Exp $
[cell use]
use bb200tr -1600 520 -100 0 frame
xform 0 -320 1344
use hwin -640 1687 100 0 hwin#58
xform 0 -544 1728
p -637 1720 100 0 -1 val(in):$(noFollow)
use tcsFollowStat -328 1672 100 0 tcsFollowStat#57
xform 0 -248 1816
use hwinl -1464 1472 100 0 hwinl#60
xform 0 -1264 1520
p -1446 1536 100 0 -1 val(in):$(subsys)$(record).VAL
use hwinl -1464 1384 100 0 hwinl#61
xform 0 -1264 1432
p -1446 1448 100 0 -1 val(in):$(subsys)state.VAL
use tcsCommonSubsys -792 1376 100 0 tcsCommonSubsys#62
xform 0 -608 1424
use eevents -1336 1208 100 0 eevents#67
xform 0 -1192 1272
p -1245 1180 100 0 -1 SCAN:1 second
p -1299 1142 100 1024 -1 name:$(tcs)$(subnam)Event
[comments]
