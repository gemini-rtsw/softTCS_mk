[schematic2]
uniq 13
[tools]
[detail]
w 872 603 100 0 n#1 ecad8.ecad8#16.VALD 560 1296 672 1296 672 592 1120 592 estringouts.gg4SelectedGuider.DOL
w 1192 715 100 0 n#2 estringouts.gg3SelectedGuider.FLNK 1376 832 1472 832 1472 704 960 704 960 560 1120 560 estringouts.gg4SelectedGuider.SLNK
w 888 859 100 0 n#3 ecad8.ecad8#16.VALC 560 1360 704 1360 704 848 1120 848 estringouts.gg3SelectedGuider.DOL
w 1192 987 100 0 n#4 estringouts.gg2SelectedGuider.FLNK 1376 1120 1472 1120 1472 976 960 976 960 816 1120 816 estringouts.gg3SelectedGuider.SLNK
w 904 1147 100 0 n#5 ecad8.ecad8#16.VALB 560 1424 736 1424 736 1136 1120 1136 estringouts.gg2SelectedGuider.DOL
w 1192 1259 100 0 n#6 estringouts.gg1SelectedGuider.FLNK 1376 1376 1472 1376 1472 1248 960 1248 960 1104 1120 1104 estringouts.gg2SelectedGuider.SLNK
w 920 1403 100 0 n#7 ecad8.ecad8#16.VALA 560 1488 768 1488 768 1392 1120 1392 estringouts.gg1SelectedGuider.DOL
w 920 1371 100 0 n#8 ecad8.ecad8#16.STLK 560 816 768 816 768 1360 1120 1360 estringouts.gg1SelectedGuider.SLNK
w 918 1682 100 0 n#9 ecad8.ecad8#16.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#10 ecad8.ecad8#16.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#11 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad8.ecad8#16.ICID
w 22 1682 100 0 n#12 inhier.DIR.P -160 1680 240 1680 ecad8.ecad8#16.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
s 1840 2000 100 0 $Id: tcsCadguiderConfig.sch,v 1.2 2010/05/27 07:41:36 cjm Exp $
[cell use]
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use estringouts 1120 1287 100 0 gg1SelectedGuider
xform 0 1248 1360
p 1120 1456 100 0 -1 DESC:Name of physical guider
p 1056 1166 100 0 0 OMSL:closed_loop
p 1056 1326 100 0 0 VAL:NONE
p 1232 1280 100 1024 0 name:$(tcs)$(I)
use estringouts 1120 1031 100 0 gg2SelectedGuider
xform 0 1248 1104
p 1120 1200 100 0 -1 DESC:Name of physical guider
p 1056 910 100 0 0 OMSL:closed_loop
p 1056 1070 100 0 0 VAL:NONE
p 1232 1024 100 1024 0 name:$(tcs)$(I)
use estringouts 1120 743 100 0 gg3SelectedGuider
xform 0 1248 816
p 1120 912 100 0 -1 DESC:Name of physical guider
p 1056 622 100 0 0 OMSL:closed_loop
p 1056 782 100 0 0 VAL:NONE
p 1232 736 100 1024 0 name:$(tcs)$(I)
use estringouts 1120 487 100 0 gg4SelectedGuider
xform 0 1248 560
p 1120 656 100 0 -1 DESC:Name of physical guider
p 1056 366 100 0 0 OMSL:closed_loop
p 1056 526 100 0 0 VAL:NONE
p 1232 480 100 1024 0 name:$(tcs)$(I)
use ecad8 264 728 100 0 ecad8#16
xform 0 400 1232
p 288 1728 100 0 -1 DESC:Implement guiderConfig
p 336 1880 100 0 0 FTVA:$(ftva)
p 336 1848 100 0 0 FTVB:$(ftvb)
p 336 1816 100 0 0 FTVC:$(ftvc)
p 336 1784 100 0 0 FTVD:$(ftvd)
p 336 1752 100 0 0 FTVE:$(ftve)
p 336 1720 100 0 0 FTVF:$(ftvf)
p 336 1688 100 0 0 FTVG:$(ftvg)
p 336 1200 100 0 0 FTVH:$(ftvh)
p 336 2168 100 0 0 SNAM:$(snam)
p 336 792 100 0 0 def(INPA):
p 336 664 100 0 0 def(INPB):
p 336 536 100 0 0 def(INPC):
p 336 408 100 0 0 def(INPD):
p 336 280 100 0 0 def(INPE):
p 336 152 100 0 0 def(INPF):
p 336 24 100 0 0 def(INPG):
p 336 -104 100 0 0 def(INPH):
p 304 718 100 0 1 name:$(tcs)$(cad)
p 336 376 100 0 0 typ(INPD):path
p 336 120 100 0 0 typ(INPF):path
p 336 -136 100 0 0 typ(INPH):path
p 336 -1800 100 0 0 typ(OUTA):path
use outhier 1304 1640 100 0 VAL
xform 0 1296 1680
use outhier 1448 1544 100 0 MESS
xform 0 1440 1584
use inhier -152 1640 100 0 DIR
xform 0 -160 1680
use inhier -152 1544 100 0 ICID
xform 0 -160 1584
[comments]
