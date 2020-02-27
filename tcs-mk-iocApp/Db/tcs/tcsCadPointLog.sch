[schematic2]
uniq 40
[tools]
[detail]
w 1608 875 100 0 n#39 tcsLockBreak.tcsLockBreak#38.FLNK 1472 864 1792 864 ebis.flnk.SLNK
w 1128 867 100 0 n#37 efanouts.Fan.LNK2 1024 864 1280 864 tcsLockBreak.tcsLockBreak#38.SLNK
w 1172 1067 100 0 n#25 efanouts.Fan.LNK1 1024 896 1168 896 1168 1248 1360 1248 eaos.Busy.SLNK
w 1240 1291 100 0 n#24 hwin.hwin#23.in 1168 1280 1360 1280 eaos.Busy.DOL
w 448 827 100 0 n#21 ecad8.ecad8#16.STLK 160 816 784 816 efanouts.Fan.SLNK
w 518 1682 100 0 n#6 ecad8.ecad8#16.VAL 160 1680 912 1680 outhier.VAL.p
w 606 1586 100 0 n#9 ecad8.ecad8#16.MESS 160 1648 192 1648 192 1584 1056 1584 outhier.MESS.p
w -338 1652 100 0 n#8 inhier.ICID.P -560 1584 -480 1584 -480 1648 -160 1648 ecad8.ecad8#16.ICID
w -378 1682 100 0 n#7 inhier.DIR.P -560 1680 -160 1680 ecad8.ecad8#16.DIR
s 1824 2000 100 0 $Id: tcsCadPointLog.sch,v 1.3 2002/05/14 09:13:49 ajf Exp $
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
[cell use]
use tcsLockBreak 1280 807 100 0 tcsLockBreak#38
xform 0 1376 880
use ebis 1792 791 100 0 flnk
xform 0 1920 864
p 2080 880 100 0 -1 def(FLNK):$(tcs)drives:pointLog
use hwin 976 1239 100 0 hwin#23
xform 0 1072 1280
p 979 1272 100 0 -1 val(in):$(CAR_BUSY)
use eaos 1360 1159 100 0 Busy
xform 0 1488 1248
p 1104 1230 100 0 0 OMSL:closed_loop
p 1696 1200 100 0 -1 def(OUT):$(tcs)kernelC.IVAL
p 1616 1216 75 768 -1 pproc(OUT):PP
use efanouts 784 679 100 0 Fan
xform 0 904 832
p 1104 864 100 0 0 def(LNK2):0.000000000000000e+00
p 1056 864 75 1280 -1 pproc(LNK2):PP
use ecad8 -136 728 100 0 ecad8#16
xform 0 0 1232
p -64 1584 100 0 0 DESC:Pointing parameter CAD
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
p 240 1264 100 0 0 def(OUTD):
p 240 1200 100 0 0 def(OUTE):
p 240 1136 100 0 0 def(OUTF):
p -160 144 100 0 0 def(OUTG):
p -160 112 100 0 0 def(OUTH):
p 224 816 100 0 0 def(STLK):0.0
p -96 718 100 0 1 name:$(tcs)$(cad)
p -192 1456 75 1280 0 pproc(INPA):NPP
p 160 1200 75 768 -1 pproc(OUTE):NPP
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
