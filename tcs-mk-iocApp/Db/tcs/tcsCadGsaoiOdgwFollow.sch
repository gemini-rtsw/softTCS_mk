[schematic2]
uniq 35
[tools]
[detail]
w 616 1499 100 0 n#34 ecad4.ecad4#20.VALA 560 1488 720 1488 720 1152 816 1152 efanouts.efanouts#31.SELL
w 1368 1083 100 0 n#33 efanouts.efanouts#31.LNK1 1008 1152 1184 1152 1184 1072 1600 1072 elongouts.elongouts#23.SLNK
w 640 1083 100 0 n#32 ecad4.ecad4#20.STLK 560 1072 768 1072 efanouts.efanouts#31.SLNK
w 1688 891 100 0 n#28 elongouts.elongouts#23.FLNK 1856 1104 1984 1104 1984 880 1440 880 1440 736 1600 736 elongouts.elongouts#27.SLNK
w 1552 779 100 0 n#26 junction 1552 1104 1552 768 1600 768 elongouts.elongouts#27.DOL
w 1504 1211 100 0 n#26 hwin.hwin#25.in 1504 1200 1552 1200 1552 1104 1600 1104 elongouts.elongouts#23.DOL
w 918 1682 100 0 n#6 ecad4.ecad4#20.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad4.ecad4#20.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad4.ecad4#20.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad4.ecad4#20.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
s 1920 2000 100 0 $Id: tcsCadGsaoiOdgwFollow.sch,v 1.1 2013/07/22 16:23:45 cjm Exp $
s 1600 1360 100 0 Force inPosition to false on starting follow
s 1600 1328 100 0 This ensures that on follow if the
s 1600 1296 100 0 the inposition state is currently true
s 1600 1264 100 0 there will definitely be a transition back to true
[cell use]
use efanouts 768 935 100 0 efanouts#31
xform 0 888 1088
p 896 1024 100 0 0 SELM:Specified
p 880 928 100 1024 1 name:$(tcs)$(odgw)FollowFan
use elongouts 1600 647 100 0 elongouts#27
xform 0 1728 736
p 1552 832 100 0 -1 DESC:Trigger in position calculation
p 1440 654 100 0 0 OMSL:closed_loop
p 2064 704 100 0 -1 def(OUT):$(tcs)drives:odgwCalcInPos.PROC
p 1728 608 100 1024 -1 name:$(tcs)$(odgw)FollowInPosCalc
p 1856 704 75 768 -1 pproc(OUT):PP
use elongouts 1600 983 100 0 elongouts#23
xform 0 1728 1072
p 1600 1168 100 0 -1 DESC:Set in position to false
p 1440 990 100 0 0 OMSL:closed_loop
p 2064 1040 100 0 -1 def(OUT):$(tcs)drives:$(odgw)inPosition
p 1728 944 100 1024 -1 name:$(tcs)$(odgw)FollowSetInPos
p 1856 1040 75 768 -1 pproc(OUT):PP
use hwin 1312 1159 100 0 hwin#25
xform 0 1408 1200
p 1315 1192 100 0 -1 val(in):0
use ecad4 264 984 100 0 ecad4#20
xform 0 400 1360
p 304 1912 100 0 0 FTVA:$(ftva)
p 304 1880 100 0 0 FTVB:$(ftvb)
p 304 1848 100 0 0 FTVC:$(ftvc)
p 304 1816 100 0 0 FTVD:$(ftvd)
p 304 2200 100 0 0 SNAM:$(snam)
p 464 464 100 0 0 def(STLK):0.0
p 288 958 100 0 1 name:$(tcs)$(odgw)Follow
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 1304 1640 100 0 VAL
xform 0 1296 1680
use outhier 1448 1544 100 0 MESS
xform 0 1440 1584
use inhier -152 1640 100 0 DIR
xform 0 -160 1680
use inhier -152 1544 100 0 ICID
xform 0 -160 1584
[comments]
