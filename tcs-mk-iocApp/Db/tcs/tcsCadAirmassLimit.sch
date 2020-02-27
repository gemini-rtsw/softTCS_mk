[schematic2]
uniq 38
[tools]
[detail]
w 404 1107 100 0 n#37 ecad8.ecad8#16.STLK 160 816 400 816 400 1408 576 1408 eaos.buffer.SLNK
w 240 1499 100 0 n#36 ecad8.ecad8#16.VALA 160 1488 368 1488 368 1440 576 1440 eaos.buffer.DOL
w 518 1682 100 0 n#6 ecad8.ecad8#16.VAL 160 1680 912 1680 outhier.VAL.p
w 606 1586 100 0 n#9 ecad8.ecad8#16.MESS 160 1648 192 1648 192 1584 1056 1584 outhier.MESS.p
w -338 1652 100 0 n#8 inhier.ICID.P -560 1584 -480 1584 -480 1648 -160 1648 ecad8.ecad8#16.ICID
w -378 1682 100 0 n#7 inhier.DIR.P -560 1680 -160 1680 ecad8.ecad8#16.DIR
s 1808 -336 100 0 16 July 1996
s 1808 -304 100 0 P.B. Taylor
s 2032 -192 100 0 Gemini Telescope Control System
s 1824 2000 100 0 $Id: tcsCadAirmassLimit.sch,v 1.2 2002/05/13 12:15:51 ajf Exp $
[cell use]
use eaos 576 1319 100 0 buffer
xform 0 704 1408
p 544 1134 100 0 0 EGU:airmass
p 320 1390 100 0 0 OMSL:closed_loop
p 912 1376 100 0 -1 def(OUT):$(tcs)airmasslimit
p 832 1376 75 768 -1 pproc(OUT):PP
use ecad8 -136 728 100 0 ecad8#16
xform 0 0 1232
p -64 1584 100 0 0 DESC:Pointing parameter CAD
p 16 1488 100 0 -1 FTVA:DOUBLE
p 16 1422 100 0 0 FTVB:STRING
p 16 1358 100 0 0 FTVC:STRING
p 16 1294 100 0 0 FTVD:STRING
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
p -160 368 100 0 0 def(MLNK):0.0
p 512 1456 100 0 0 def(OUTA):
p 224 1390 100 0 0 def(OUTB):
p 240 1326 100 0 0 def(OUTC):
p 240 1262 100 0 0 def(OUTD):
p 240 1200 100 0 0 def(OUTE):
p 240 1136 100 0 0 def(OUTF):
p -160 144 100 0 0 def(OUTG):
p -160 112 100 0 0 def(OUTH):
p 240 816 100 0 0 def(STLK):0.0
p -96 718 100 0 1 name:$(tcs)$(cad)
p -192 1456 75 1280 0 pproc(INPA):NPP
p 160 1456 75 768 -1 pproc(OUTA):NPP
p 160 1392 75 768 -1 pproc(OUTB):NPP
p 160 1328 75 768 -1 pproc(OUTC):NPP
p 160 1264 75 768 -1 pproc(OUTD):NPP
p 160 1200 75 768 -1 pproc(OUTE):NPP
p 160 826 75 0 -1 pproc(STLK):NPP
p -64 376 100 0 0 typ(INPD):path
p -64 120 100 0 0 typ(INPF):path
p -64 -136 100 0 0 typ(INPH):path
p -64 -1800 100 0 0 typ(OUTA):path
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 1048 1544 100 0 MESS
xform 0 1040 1584
use outhier 904 1640 100 0 VAL
xform 0 896 1680
use inhier -552 1544 100 0 ICID
xform 0 -560 1584
use inhier -552 1640 100 0 DIR
xform 0 -560 1680
[comments]
