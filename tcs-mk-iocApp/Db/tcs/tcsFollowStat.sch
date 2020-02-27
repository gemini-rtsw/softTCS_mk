[schematic2]
uniq 6
[tools]
[detail]
w 1408 1771 100 0 n#1 ebos.ebos#30.VAL 1264 1760 1600 1760 outhier.VAL.p
w 408 1067 100 0 n#2 elongins.FollowDisv.VAL 320 1056 544 1056 egenSub.egenSub#25.SDIS
w 946 1432 100 0 n#3 egenSub.egenSub#25.FLNK 832 1056 944 1056 944 1760 1008 1760 ebos.ebos#30.SLNK
w 896 1794 100 0 n#4 egenSub.egenSub#25.VALA 832 1792 1008 1792 ebos.ebos#30.DOL
w -174 1114 100 0 n#5 inhier.DISV.P -184 1104 64 1104 elongins.FollowDisv.INP
s 416 1920 100 0 The FollowStat record will then show Disabled.
s 416 1952 100 0 and the EPICS version is GEM8.5 or later
s 416 1984 100 0 N.B. This gensub won't process if the subsystem is not present
s 1840 688 100 0 1
s 1728 688 100 0 1
s 1456 752 100 0 Get status from subsystem Follow SIR
s 1344 2016 100 0 $Id: tcsFollowStat.sch,v 1.6 2010/07/19 13:25:32 ajf Exp $
s 1488 816 100 0 Gemini Telescope Control System
s -32 896 100 0 Disable gensub for those subsystems
s -32 864 100 0 That don't have a follow mode
[cell use]
use bb200tr -544 536 -100 0 frame
xform 0 736 1360
use outhier 1568 1719 100 0 VAL
xform 0 1584 1760
use elongins 64 999 100 0 FollowDisv
xform 0 192 1072
p 0 1152 100 0 -1 DESC:Disable fetch of follow string
p -192 1070 100 0 0 EGU:units
p 176 992 100 1024 0 name:$(tcs)$(subnam)$(I)
use ebos 1032 1672 100 0 ebos#30
xform 0 1136 1760
p 688 1710 100 0 0 OMSL:closed_loop
p 688 1614 100 0 0 ONAM:Enabled
p 688 1646 100 0 0 ZNAM:Disabled
p 1228 1648 100 1024 1 name:$(tcs)$(subnam)FollowStat
use egenSub 568 1000 100 0 egenSub#25
xform 0 688 1424
p 321 773 100 0 0 FTA:STRING
p 321 773 100 0 0 FTVA:LONG
p 640 1278 100 0 -1 SCAN:1 second
p 608 1150 100 0 -1 SNAM:tcsFollowString
p 288 1742 100 0 -1 def(INPA):$(subsys)followS.VAL
p 768 976 100 1024 1 name:$(tcs)$(subnam)FollowString
p 496 1066 75 0 -1 pproc(SDIS):PP
use inhier -220 1054 100 0 DISV
xform 0 -184 1104
[comments]
