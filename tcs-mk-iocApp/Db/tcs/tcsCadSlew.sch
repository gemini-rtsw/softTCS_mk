[schematic2]
uniq 31
[tools]
[detail]
w 760 275 100 0 n#30 ecad20.ecad20#20.VALT 560 272 1008 272 1008 256 1104 256 efanouts.fan.SELL
w 1896 459 100 0 n#29 estringouts.chop.FLNK 2000 240 2064 240 2064 448 1776 448 1776 560 1920 560 tcsStartSubCAD.tcsStartSubCAD#28.SubCadStart
w 1080 339 100 0 n#27 ecad20.ecad20#20.VALS 560 336 1648 336 1648 256 1744 256 estringouts.chop.DOL
w 1400 267 100 0 n#25 efanouts.fan.LNK1 1296 256 1552 256 1552 224 1744 224 estringouts.chop.SLNK
w 872 179 100 0 n#23 ecad20.ecad20#20.STLK 560 48 736 48 736 176 1056 176 efanouts.fan.SLNK
w 918 1682 100 0 n#6 ecad20.ecad20#20.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad20.ecad20#20.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad20.ecad20#20.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad20.ecad20#20.DIR
s 1840 2000 100 0 $Id: tcsCadSlew.sch,v 1.2 2003/01/10 10:45:05 dlt Exp $
s 1808 -336 100 0 16 July 1996
s 1808 -304 100 0 P.B. Taylor
s 2032 -192 100 0 Gemini Telescope Control System
[cell use]
use tcsStartSubCAD 1920 471 100 0 tcsStartSubCAD#28
xform 0 2048 536
p 1936 702 100 0 -1 seta:prefix slew
p 1936 670 100 0 -1 setb:subcad guide
p 1936 638 100 0 -1 setc:subsys $(m2)
p 1936 606 100 0 -1 setd:text Secondary
use estringouts 1744 151 100 0 chop
xform 0 1872 224
p 1680 30 100 0 0 OMSL:closed_loop
p 2048 176 100 0 -1 def(OUT):$(m2)guide.A
use efanouts 1056 39 100 0 fan
xform 0 1176 192
p 1152 16 100 0 1 SELM:Mask
use ecad20 240 -41 100 0 ecad20#20
xform 0 400 848
p 432 1488 100 0 0 FTVA:STRING
p 432 272 100 0 -1 FTVT:LONG
p 320 96 100 0 1 SNAM:$(snam)
p 384 -48 100 1024 1 name:$(tcs)$(cad)
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
