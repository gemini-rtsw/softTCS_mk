[schematic2]
uniq 47
[tools]
[detail]
w 712 987 100 0 n#46 egenSub.egenSub#25.VALD 416 1664 608 1664 608 976 864 976 ebos.ebos#40.DOL
w 504 1739 100 0 n#45 egenSub.egenSub#25.VALC 416 1728 640 1728 640 1280 864 1280 ebos.ebos#39.DOL
w 520 1803 100 0 n#44 egenSub.egenSub#25.VALB 416 1792 672 1792 672 1568 864 1568 ebos.ebos#38.DOL
w 976 1099 100 0 n#43 ebos.ebos#39.FLNK 1120 1280 1248 1280 1248 1088 752 1088 752 944 864 944 ebos.ebos#40.SLNK
w 976 1403 100 0 n#42 ebos.ebos#38.FLNK 1120 1568 1248 1568 1248 1392 752 1392 752 1248 864 1248 ebos.ebos#39.SLNK
w 976 1691 100 0 n#41 ebos.ebos#30.FLNK 1120 1856 1248 1856 1248 1680 752 1680 752 1536 864 1536 ebos.ebos#38.SLNK
w 672 1835 100 0 n#29 egenSub.egenSub#25.FLNK 416 1120 528 1120 528 1824 864 1824 ebos.ebos#30.SLNK
w 616 1867 100 0 n#28 egenSub.egenSub#25.VALA 416 1856 864 1856 ebos.ebos#30.DOL
s 1840 688 100 0 1
s 1728 688 100 0 1
s 1456 752 100 0 Get status from subsystem Follow SIR
s 1488 816 100 0 Gemini Telescope Control System
s 1232 2048 100 0 $Id: tcsGGFollowStat.sch,v 1.2 2010/01/28 14:04:44 ajf Exp $
[cell use]
use ebos 888 1736 100 0 ebos#30
xform 0 992 1824
p 896 1920 100 0 -1 DESC:GG1 follow state
p 544 1774 100 0 0 OMSL:closed_loop
p 544 1678 100 0 0 ONAM:Enabled
p 544 1710 100 0 0 ZNAM:Disabled
p 1084 1712 100 1024 1 name:$(tcs)gg1FollowStat
use ebos 888 1448 100 0 ebos#38
xform 0 992 1536
p 896 1632 100 0 -1 DESC:GG2 follow state
p 544 1486 100 0 0 OMSL:closed_loop
p 544 1390 100 0 0 ONAM:Enabled
p 544 1422 100 0 0 ZNAM:Disabled
p 1084 1424 100 1024 1 name:$(tcs)gg2FollowStat
use ebos 888 1160 100 0 ebos#39
xform 0 992 1248
p 896 1344 100 0 -1 DESC:GG1 follow state
p 544 1198 100 0 0 OMSL:closed_loop
p 544 1102 100 0 0 ONAM:Enabled
p 544 1134 100 0 0 ZNAM:Disabled
p 1084 1136 100 1024 1 name:$(tcs)gg3FollowStat
use ebos 888 856 100 0 ebos#40
xform 0 992 944
p 896 1040 100 0 -1 DESC:GG1 follow state
p 544 894 100 0 0 OMSL:closed_loop
p 544 798 100 0 0 ONAM:Enabled
p 544 830 100 0 0 ZNAM:Disabled
p 1084 832 100 1024 1 name:$(tcs)gg4FollowStat
use egenSub 152 1064 100 0 egenSub#25
xform 0 272 1488
p 144 1920 100 0 -1 DESC:Generate GG follow states
p -95 837 100 0 0 FTA:LONG
p -95 837 100 0 0 FTB:LONG
p -95 805 100 0 0 FTC:LONG
p -95 773 100 0 0 FTD:LONG
p -95 741 100 0 0 FTE:LONG
p -95 677 100 0 0 FTF:LONG
p -95 677 100 0 0 FTG:LONG
p -95 837 100 0 0 FTVA:LONG
p -95 837 100 0 0 FTVB:LONG
p -95 805 100 0 0 FTVC:LONG
p -95 773 100 0 0 FTVD:LONG
p 224 1342 100 0 -1 SCAN:1 second
p 192 1214 100 0 -1 SNAM:tcsGuideGGFollowStates
p -256 1824 100 0 -1 def(INPA):$(tcs)guiderConfig.VALE
p -256 1760 100 0 -1 def(INPB):$(tcs)guiderConfig.VALF
p -256 1696 100 0 -1 def(INPC):$(tcs)guiderConfig.VALG
p -256 1632 100 0 -1 def(INPD):$(tcs)guiderConfig.VALH
p -256 1568 100 0 -1 def(INPE):$(tcs)ngsPr1FollowStat
p -256 1504 100 0 -1 def(INPF):$(tcs)ngsPr2FollowStat
p -272 1440 100 0 -1 def(INPG):$(tcs)ngsPr3FollowStat
p 352 1040 100 1024 1 name:$(tcs)GGFollowString
p 80 1130 75 0 -1 pproc(SDIS):NPP
use bb200tr -544 536 -100 0 frame
xform 0 736 1360
[comments]
