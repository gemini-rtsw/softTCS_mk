[schematic2]
uniq 24
[tools]
[detail]
w 704 827 100 0 n#23 ecad8.ecad8#16.STLK 560 816 896 816 896 960 1088 960 ebos.StartMove.SLNK
w 1032 1003 100 0 n#22 hwin.hwin#21.in 1024 992 1088 992 ebos.StartMove.DOL
w 918 1682 100 0 n#6 ecad8.ecad8#16.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad8.ecad8#16.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad8.ecad8#16.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad8.ecad8#16.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
s 1840 2000 100 0 $Id: tcsCadM2NomPosn.sch,v 1.2 2002/05/14 09:13:49 ajf Exp $
[cell use]
use hwin 832 951 100 0 hwin#21
xform 0 928 992
p 835 984 100 0 -1 val(in):1
use ebos 1088 871 100 0 StartMove
xform 0 1216 960
p 1136 1072 100 0 -1 DESC:Trigger m2 move
p 768 910 100 0 0 OMSL:closed_loop
p 1456 928 100 0 -1 def(OUT):$(tcs)drives:issueM2Move.PROC
p 1200 864 100 1024 0 name:$(top)$(cad)$(I)
p 1344 928 75 768 -1 pproc(OUT):PP
use ecad8 264 728 100 0 ecad8#16
xform 0 400 1232
p 288 1776 100 0 -1 DESC:Implement m2NomPosn command
p 336 1880 100 0 0 FTVA:STRING
p 336 1848 100 0 0 FTVB:STRING
p 336 1816 100 0 0 FTVC:STRING
p 336 1784 100 0 0 FTVD:STRING
p 336 1752 100 0 0 FTVE:STRING
p 336 1720 100 0 0 FTVF:LONG
p 336 1688 100 0 0 FTVG:LONG
p 336 1200 100 0 0 FTVH:LONG
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
