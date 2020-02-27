[schematic2]
uniq 49
[tools]
[detail]
w 808 923 100 0 n#40 eaos.ypm.DOL 1376 912 288 912 junction
w 808 715 100 0 n#40 eaos.djmls.DOL 1376 704 288 704 junction
w 808 523 100 0 n#40 eaos.delat.DOL 1376 512 288 512 junction
w 808 331 100 0 n#40 junction 288 1120 288 320 1376 320 eaos.delut.DOL
w 1176 299 100 0 n#48 efanouts.fan.LNK5 784 1216 1024 1216 1024 288 1376 288 eaos.delut.SLNK
w 912 1259 100 0 n#47 efanouts.fan.LNK4 784 1248 1088 1248 1088 480 1376 480 eaos.delat.SLNK
w 944 1291 100 0 n#46 efanouts.fan.LNK3 784 1280 1152 1280 1152 672 1376 672 eaos.djmls.SLNK
w 976 1323 100 0 n#45 efanouts.fan.LNK2 784 1312 1216 1312 1216 880 1376 880 eaos.ypm.SLNK
w 808 1131 100 0 n#40 ecad8.ecad8#16.VALD 160 1296 288 1296 288 1120 1376 1120 eaos.xpm.DOL
w 1008 1355 100 0 n#39 efanouts.fan.LNK1 784 1344 1280 1344 1280 1088 1376 1088 eaos.xpm.SLNK
w 264 827 100 0 n#37 ecad8.ecad8#16.STLK 160 816 416 816 416 1264 544 1264 efanouts.fan.SLNK
w 272 1371 100 0 n#36 ecad8.ecad8#16.VALC 160 1360 432 1360 432 1344 592 1344 efanouts.fan.SELL
w 518 1682 100 0 n#6 ecad8.ecad8#16.VAL 160 1680 912 1680 outhier.VAL.p
w 606 1586 100 0 n#9 ecad8.ecad8#16.MESS 160 1648 192 1648 192 1584 1056 1584 outhier.MESS.p
w -338 1652 100 0 n#8 inhier.ICID.P -560 1584 -480 1584 -480 1648 -160 1648 ecad8.ecad8#16.ICID
w -378 1682 100 0 n#7 inhier.DIR.P -560 1680 -160 1680 ecad8.ecad8#16.DIR
s 1808 -336 100 0 16 July 1996
s 1808 -304 100 0 P.B. Taylor
s 2032 -192 100 0 Gemini Telescope Control System
s 1824 2000 100 0 $Id: tcsCadTimeParam.sch,v 1.2 2002/05/14 09:13:49 ajf Exp $
[cell use]
use eaos 1376 199 100 0 delut
xform 0 1504 288
p 1344 14 100 0 0 EGU:arcsec
p 1120 270 100 0 0 OMSL:closed_loop
p 1712 256 100 0 -1 def(OUT):$(tcs)ak:delut
p 1632 256 75 768 -1 pproc(OUT):PP
use eaos 1376 391 100 0 delat
xform 0 1504 480
p 1344 206 100 0 0 EGU:arcsec
p 1120 462 100 0 0 OMSL:closed_loop
p 1712 448 100 0 -1 def(OUT):$(tcs)ak:delat
p 1632 448 75 768 -1 pproc(OUT):PP
use eaos 1376 583 100 0 djmls
xform 0 1504 672
p 1344 398 100 0 0 EGU:arcsec
p 1120 654 100 0 0 OMSL:closed_loop
p 1712 640 100 0 -1 def(OUT):$(tcs)ak:djmls
p 1632 640 75 768 -1 pproc(OUT):PP
use eaos 1376 791 100 0 ypm
xform 0 1504 880
p 1344 606 100 0 0 EGU:arcsec
p 1120 862 100 0 0 OMSL:closed_loop
p 1712 848 100 0 -1 def(OUT):$(tcs)ak:ypm
p 1632 848 75 768 -1 pproc(OUT):PP
use eaos 1376 999 100 0 xpm
xform 0 1504 1088
p 1344 814 100 0 0 EGU:arcsec
p 1120 1070 100 0 0 OMSL:closed_loop
p 1712 1056 100 0 -1 def(OUT):$(tcs)ak:xpm
p 1632 1056 75 768 -1 pproc(OUT):PP
use efanouts 544 1127 100 0 fan
xform 0 664 1280
p 400 1246 100 0 0 SELM:Specified
use ecad8 -136 728 100 0 ecad8#16
xform 0 0 1232
p -64 1584 100 0 0 DESC:Time parameter CAD
p 16 1488 100 0 -1 FTVA:STRING
p 16 1424 100 0 -1 FTVB:DOUBLE
p 16 1360 100 0 -1 FTVC:LONG
p 16 1296 100 0 -1 FTVD:DOUBLE
p 48 1232 100 0 0 FTVE:DOUBLE
p 16 1168 100 0 0 FTVF:DOUBLE
p -64 1688 100 0 0 FTVG:DOUBLE
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
p 240 816 100 0 0 def(STLK):0.0
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
use outhier 1048 1544 100 0 MESS
xform 0 1040 1584
use outhier 904 1640 100 0 VAL
xform 0 896 1680
use inhier -552 1544 100 0 ICID
xform 0 -560 1584
use inhier -552 1640 100 0 DIR
xform 0 -560 1680
[comments]
