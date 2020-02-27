[schematic2]
uniq 27
[tools]
[detail]
w -40 -213 100 0 n#26 ecad20.ecad20#25.STLK -288 -224 256 -224 256 384 800 384 eseqs.delay.SLNK
w 1736 706 100 0 n#24 ecars.ecars#20.VAL 1664 704 1856 704 outhier.VAL.p
w 1744 482 100 0 n#22 ecars.ecars#20.FLNK 1664 480 1872 480 outhier.FLNK.p
w 1208 706 100 0 n#21 eseqs.delay.LNK1 1120 704 1344 704 ecars.ecars#20.IVAL
w 1160 674 100 0 n#21 eseqs.delay.LNK2 1120 672 1248 672 1248 704 junction
w 712 674 100 0 n#18 hwin.hwin#16.in 576 656 672 656 672 672 800 672 eseqs.delay.DOL2
w 712 706 100 0 n#17 hwin.hwin#15.in 576 752 672 752 672 704 800 704 eseqs.delay.DOL1
s 1632 1776 100 0 $Id: genericcad20.sch,v 1.1 2002/11/23 12:58:41 cjm Exp $
s 1904 -496 100 0 simulators
s 1904 -464 100 0 Generic CAD/CAR for subsystem
s 1888 -416 100 0 Gemini Telescope Control System
[cell use]
use ecad20 -608 -313 100 0 ecad20#25
xform 0 -448 576
p -512 1152 100 0 0 FTVA:$(ftva)
p -512 1120 100 0 0 FTVB:$(ftvb)
p -512 1088 100 0 0 FTVC:$(ftvc)
p -512 1056 100 0 0 FTVD:$(ftvd)
p -512 416 100 0 0 PREC:5
p -512 1328 100 0 1 SNAM:$(snam)
p -480 -368 100 1024 1 name:$(prefix)$(command)
use bc200tr -944 -696 -100 0 frame
xform 0 736 608
use outhier 1864 440 100 0 FLNK
xform 0 1856 480
use outhier 1848 664 100 0 VAL
xform 0 1840 704
use ecars 1368 424 100 0 ecars#20
xform 0 1504 592
p 1452 416 100 1024 1 name:$(prefix)$(command)C
use hwin 408 712 100 0 hwin#15
xform 0 480 752
p 387 744 100 0 -1 val(in):$(CAR_BUSY)
use hwin 408 616 100 0 hwin#16
xform 0 480 656
p 387 648 100 0 -1 val(in):$(CAR_IDLE)
use eseqs 824 296 100 0 delay
xform 0 960 544
p 896 510 100 0 0 DLY1:0.0
p 896 574 100 0 1 DLY2:$(delay)
p 416 -2180 100 0 0 PV:$(prefix)$(command):
p 1136 702 100 0 0 def(LNK1):0.0
p 800 736 75 1280 -1 palrm(SELL):NMS
p 1136 704 75 1024 -1 pproc(LNK1):PP
p 1136 672 75 1024 -1 pproc(LNK2):PP
[comments]
