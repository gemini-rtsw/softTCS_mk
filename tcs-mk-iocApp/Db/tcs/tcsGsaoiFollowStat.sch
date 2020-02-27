[schematic2]
uniq 7
[tools]
[detail]
w 256 1771 100 0 n#1 inhier.ODGW.P 16 1760 544 1760 egenSub.egenSub#25.INPA
w 1408 1771 100 0 n#2 ebos.ebos#30.VAL 1264 1760 1600 1760 outhier.VAL.p
w -96 1115 100 0 DISV#3 inhier.DISV.P -208 1104 64 1104 elongins.FollowDisv.INP
w 408 1067 100 0 n#4 elongins.FollowDisv.VAL 320 1056 544 1056 egenSub.egenSub#25.SDIS
w 946 1432 100 0 n#5 egenSub.egenSub#25.FLNK 832 1056 944 1056 944 1760 1008 1760 ebos.ebos#30.SLNK
w 896 1794 100 0 n#6 egenSub.egenSub#25.VALA 832 1792 1008 1792 ebos.ebos#30.DOL
s 288 1952 100 0 what it really means is that the ODGW is in use and guiding.
s 288 1984 100 0 Although the nomenclature here is that the ODGW is following
s -32 864 100 0 That don't have a follow mode
s -32 896 100 0 Disable gensub for those subsystems
s 1488 816 100 0 Gemini Telescope Control System
s 1344 2016 100 0 $Id: tcsGsaoiFollowStat.sch,v 1.2 2010/05/27 07:43:11 cjm Exp $
s 1456 752 100 0 Get status from subsystem Follow SIR
s 1728 688 100 0 1
s 1840 688 100 0 1
[cell use]
use bb200tr -544 536 -100 0 frame
xform 0 736 1360
use inhier 0 1719 100 0 ODGW
xform 0 16 1760
use outhier 1568 1719 100 0 VAL
xform 0 1584 1760
use elongins 64 999 100 0 FollowDisv
xform 0 192 1072
p 0 1152 100 0 -1 DESC:Disable fetch of follow string
p -192 1070 100 0 0 EGU:units
p 176 992 100 1024 0 name:$(tcs)$(subnam)$(I)
use inhier -224 1063 100 0 DISV
xform 0 -208 1104
use ebos 1032 1672 100 0 ebos#30
xform 0 1136 1760
p 688 1710 100 0 0 OMSL:closed_loop
p 688 1614 100 0 0 ONAM:Enabled
p 688 1646 100 0 0 ZNAM:Disabled
p 1228 1648 100 1024 1 name:$(tcs)$(subnam)FollowStat
use egenSub 568 1000 100 0 egenSub#25
xform 0 688 1424
p 544 1856 100 0 -1 DESC:Extract ODGW guide status
p 321 773 100 0 0 FTA:LONG
p 321 773 100 0 0 FTVA:LONG
p 640 1278 100 0 -1 SCAN:1 second
p 608 944 100 0 1 SNAM:tcsGuideGetOdgwFollowState
p 288 1742 100 0 0 def(INPA):0.000000000000000e+00
p 768 976 100 1024 1 name:$(tcs)$(subnam)FollowString
p 496 1066 75 0 -1 pproc(SDIS):PP
[comments]
