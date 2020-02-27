[schematic2]
uniq 23
[tools]
[detail]
w 918 1682 100 0 n#6 ecad4.ecad4#20.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad4.ecad4#20.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad4.ecad4#20.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad4.ecad4#20.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
s 1920 2000 100 0 $Id: tcsCadWrap.sch,v 1.1.1.1 1998/11/08 00:20:31 epics Exp $
[cell use]
use ecad4 264 984 100 0 ecad4#20
xform 0 400 1360
p 304 1912 100 0 0 FTVA:$(ftva)
p 304 1880 100 0 0 FTVB:$(ftvb)
p 304 1848 100 0 0 FTVC:$(ftvc)
p 304 1816 100 0 0 FTVD:$(ftvd)
p 304 2200 100 0 0 SNAM:$(snam)
p 624 1072 100 0 -1 def(STLK):$(tcs)limits:delay
p 288 958 100 0 1 name:$(tcs)$(cad)
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
