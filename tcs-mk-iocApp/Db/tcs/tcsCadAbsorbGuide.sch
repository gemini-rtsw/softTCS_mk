[schematic2]
uniq 39
[tools]
[detail]
w 518 1682 100 0 n#6 ecad8.ecad8#16.VAL 160 1680 912 1680 outhier.VAL.p
w 606 1586 100 0 n#9 ecad8.ecad8#16.MESS 160 1648 192 1648 192 1584 1056 1584 outhier.MESS.p
w -338 1652 100 0 n#8 inhier.ICID.P -560 1584 -480 1584 -480 1648 -160 1648 ecad8.ecad8#16.ICID
w -378 1682 100 0 n#7 inhier.DIR.P -560 1680 -160 1680 ecad8.ecad8#16.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
s 1904 2000 100 0 $Id: tcsCadAbsorbGuide.sch,v 1.2 2002/05/14 09:13:49 ajf Exp $
[cell use]
use ecad8 -136 728 100 0 ecad8#16
xform 0 0 1232
p -64 1584 100 0 0 DESC:Absorb guide CAD
p 16 1488 100 0 0 FTVA:STRING
p 16 1424 100 0 0 FTVB:STRING
p 16 1360 100 0 0 FTVC:STRING
p 48 1280 100 0 0 FTVD:STRING
p 48 1232 100 0 0 FTVE:STRING
p 16 1168 100 0 0 FTVF:STRING
p -64 1688 100 0 0 FTVG:STRING
p -96 688 100 0 1 SNAM:$(snam)
p -64 792 100 0 0 def(INPA):
p -64 664 100 0 0 def(INPB):
p -64 536 100 0 0 def(INPC):
p 240 1264 100 0 0 def(INPD):
p -64 280 100 0 0 def(INPE):
p -64 152 100 0 0 def(INPF):
p -64 24 100 0 0 def(INPG):
p -64 -104 100 0 0 def(INPH):
p 208 1456 100 0 0 def(OUTA):
p 240 1264 100 0 0 def(OUTD):
p 240 1200 100 0 0 def(OUTE):
p 240 1136 100 0 0 def(OUTF):
p -160 144 100 0 0 def(OUTG):
p -160 112 100 0 0 def(OUTH):
p 224 816 100 0 -1 def(STLK):$(tcs)ak:guide:absorb
p -96 718 100 0 1 name:$(tcs)$(cad)
p -192 1456 75 1280 0 pproc(INPA):NPP
p 160 1456 75 768 -1 pproc(OUTA):NPP
p 160 1200 75 768 -1 pproc(OUTE):PP
p 160 826 75 0 -1 pproc(STLK):NPP
p -64 376 100 0 0 typ(INPD):path
p -64 120 100 0 0 typ(INPF):path
p -64 -136 100 0 0 typ(INPH):path
p -64 -1800 100 0 0 typ(OUTA):path
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 904 1640 100 0 VAL
xform 0 896 1680
use outhier 1048 1544 100 0 MESS
xform 0 1040 1584
use inhier -552 1640 100 0 DIR
xform 0 -560 1680
use inhier -552 1544 100 0 ICID
xform 0 -560 1584
[comments]
