[schematic2]
uniq 20
[tools]
[detail]
w 918 1682 100 0 n#6 ecad8.ecad8#16.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad8.ecad8#16.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad8.ecad8#16.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad8.ecad8#16.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
s 1936 2000 100 0 $Id: tcsCadOffsetPo.sch,v 1.3 2002/05/14 09:13:49 ajf Exp $
[cell use]
use ecad8 264 728 100 0 ecad8#16
xform 0 400 1232
p 336 1880 100 0 0 FTVA:DOUBLE
p 336 1848 100 0 0 FTVB:DOUBLE
p 336 1816 100 0 0 FTVC:STRING
p 336 1784 100 0 0 FTVD:STRING
p 336 1072 100 0 0 PREC:14
p 304 686 100 0 1 SNAM:tcsCADoffsetPo
p -64 1486 100 0 0 def(INPA):
p 336 664 100 0 0 def(INPB):
p 336 536 100 0 0 def(INPC):
p 336 408 100 0 0 def(INPD):
p 336 280 100 0 0 def(INPE):
p 336 152 100 0 0 def(INPF):
p 336 24 100 0 0 def(INPG):
p -96 1006 100 0 0 def(INPH):
p 304 718 100 0 1 name:$(tcs)$(cad)
p 336 376 100 0 0 typ(INPD):path
p 336 120 100 0 0 typ(INPF):path
p 336 -136 100 0 0 typ(INPH):path
p 336 -1800 100 0 0 typ(OUTA):path
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
