[schematic2]
uniq 29
[tools]
[detail]
w 770 1296 100 0 n#28 ecad4.ecad4#20.VALB 560 1424 768 1424 768 1120 992 1120 eaos.m2YUserOffset.DOL
w 1096 1234 100 0 n#27 eaos.m2XUserOffset.FLNK 1248 1424 1344 1424 1344 1232 896 1232 896 1088 992 1088 eaos.m2YUserOffset.SLNK
w 656 1490 100 0 n#26 ecad4.ecad4#20.VALA 560 1488 800 1488 800 1424 992 1424 eaos.m2XUserOffset.DOL
w 818 1256 100 0 n#25 ecad4.ecad4#20.STLK 560 1072 816 1072 816 1392 992 1392 eaos.m2XUserOffset.SLNK
w 918 1682 100 0 n#6 ecad4.ecad4#20.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad4.ecad4#20.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad4.ecad4#20.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad4.ecad4#20.DIR
s 1808 -336 100 0 16 July 1996
s 1808 -304 100 0 P.B. Taylor
s 2032 -192 100 0 Gemini Telescope Control System
s 1792 2000 100 0 $Id: tcsCadM2XYOffset.sch,v 1.1.1.1 1998/11/08 00:20:29 epics Exp $
s 608 1872 100 0 This schematic implements the m2XYOffset command
[cell use]
use eaos 1016 1304 100 0 m2XUserOffset
xform 0 1120 1392
p 1008 1486 100 0 -1 DESC:User defined X offset
p 1072 1342 100 0 1 EGU:mm
p 736 1374 100 0 0 OMSL:closed_loop
p 736 1246 100 0 0 PREC:3
p 1376 1358 100 0 -1 def(OUT):$(sad)m2XUserOffset
p 1248 1360 75 768 -1 pproc(OUT):PP
p 1104 1296 100 1024 0 name:$(tcs)$(I)
use eaos 1016 1000 100 0 m2YUserOffset
xform 0 1120 1088
p 1008 1182 100 0 -1 DESC:User defined Y offset
p 1072 1038 100 0 1 EGU:mm
p 736 1070 100 0 0 OMSL:closed_loop
p 736 942 100 0 0 PREC:3
p 1376 1054 100 0 -1 def(OUT):$(sad)m2YUserOffset
p 1248 1056 75 768 -1 pproc(OUT):PP
p 1104 992 100 1024 0 name:$(tcs)$(I)
use ecad4 264 984 100 0 ecad4#20
xform 0 400 1360
p 304 1912 100 0 0 FTVA:$(ftva)
p 304 1880 100 0 0 FTVB:$(ftvb)
p 304 1848 100 0 0 FTVC:$(ftvc)
p 304 1816 100 0 0 FTVD:$(ftvd)
p 304 2200 100 0 0 SNAM:$(snam)
p 464 464 100 0 0 def(STLK):0.0
p 288 958 100 0 1 name:$(tcs)$(cad)
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 1448 1544 100 0 MESS
xform 0 1440 1584
use outhier 1304 1640 100 0 VAL
xform 0 1296 1680
use inhier -152 1544 100 0 ICID
xform 0 -160 1584
use inhier -152 1640 100 0 DIR
xform 0 -160 1680
[comments]
