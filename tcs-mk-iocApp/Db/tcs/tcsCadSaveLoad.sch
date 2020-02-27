[schematic2]
uniq 26
[tools]
[detail]
w 1400 1435 100 0 n#25 ecars.ecars#1.VAL 1344 1424 1504 1424 eaos.CarVal.DOL
w 1428 1291 100 0 n#24 ecars.ecars#1.FLNK 1344 1200 1424 1200 1424 1392 1504 1392 eaos.CarVal.SLNK
w 704 1042 100 0 n#22 ecad4.ecad4#20.SPLK 560 1040 896 1040 tcsCadPlus.tcsCadPlus#2.SPIN
w 692 912 100 0 n#21 ecad4.ecad4#20.STLK 560 1072 688 1072 688 704 880 704 efanouts.fan.SLNK
w 984 882 100 0 n#18 efanouts.fan.LNK1 1120 784 1216 784 1216 880 800 880 800 1072 896 1072 tcsCadPlus.tcsCadPlus#2.STIN
w 1078 1682 100 0 n#6 junction 720 1680 1472 1680 outhier.VAL.p
w 722 1418 100 0 n#6 ecad4.ecad4#20.VAL 560 1680 720 1680 720 1120 896 1120 tcsCadPlus.tcsCadPlus#2.STAT
w 1006 1586 100 0 n#9 ecad4.ecad4#20.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad4.ecad4#20.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad4.ecad4#20.DIR
s 1920 2000 100 0 $Id: tcsCadSaveLoad.sch,v 1.1.1.1 1998/11/08 00:20:31 epics Exp $
s 1808 -336 100 0 16 July 1996
s 1808 -304 100 0 P.B. Taylor
s 2032 -192 100 0 Gemini Telescope Control System
[cell use]
use eaos 1504 1303 100 0 CarVal
xform 0 1632 1392
p 1248 1374 100 0 0 OMSL:closed_loop
p 1856 1360 100 0 1 def(OUT):$(tcs)softC:valCombine.$(field)
p 1760 1360 75 768 -1 pproc(OUT):PP
use ecad4 264 984 100 0 ecad4#20
xform 0 400 1360
p 304 1912 100 0 0 FTVA:$(ftva)
p 304 1880 100 0 0 FTVB:$(ftvb)
p 304 1848 100 0 0 FTVC:$(ftvc)
p 304 1816 100 0 0 FTVD:$(ftvd)
p 304 2200 100 0 0 SNAM:$(snam)
p 288 958 100 0 1 name:$(tcs)$(cad)
use efanouts 904 568 100 0 fan
xform 0 1000 720
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 1448 1544 100 0 MESS
xform 0 1440 1584
use outhier 1464 1640 100 0 VAL
xform 0 1456 1680
use inhier -152 1544 100 0 ICID
xform 0 -160 1584
use inhier -152 1640 100 0 DIR
xform 0 -160 1680
use tcsCadPlus 920 968 100 0 tcsCadPlus#2
xform 0 976 1072
use ecars 1048 1144 100 0 ecars#1
xform 0 1184 1312
p 1056 1134 100 0 1 name:$(tcs)$(cad)C
[comments]
