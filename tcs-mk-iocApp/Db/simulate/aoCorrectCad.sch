[schematic2]
uniq 62
[tools]
[detail]
w 424 1147 100 0 n#60 junction 224 1008 224 1136 672 1136 672 1152 eais.settled.INP
w 1056 1003 100 0 n#61 eais.settled.FLNK 928 1136 992 1136 992 992 1168 992 eais.conMatX.SLNK
w 264 1019 100 0 n#60 ecad4.ecad4#43.VALA 112 752 224 752 224 1008 352 1008 eais.loopRunning.INP
w 864 971 100 0 n#53 eais.loopRunning.VAL 608 960 1168 960 eais.conMatX.SDIS
w 616 1131 100 0 n#52 eais.loopRunning.FLNK 608 992 608 1120 672 1120 eais.settled.SLNK
w 1480 1019 100 0 n#50 eais.conMatX.FLNK 1424 1008 1584 1008 eais.conMatY.SLNK
w 448 571 100 0 n#48 efanouts.correctfan.LNK1 512 416 640 416 640 560 304 560 304 976 352 976 eais.loopRunning.SLNK
w 712 411 100 0 n#47 efanouts.correctfan.LNK2 512 384 656 384 656 400 816 400 eseqs.Seq.SLNK
w 1760 290 100 0 n#42 ecars.ecars#14.VAL 1728 288 1840 288 outhier.VAL.p
w 1760 66 100 0 n#40 ecars.ecars#14.FLNK 1728 64 1840 64 outhier.FLNK.p
w 168 347 100 0 n#38 ecad4.ecad4#43.STLK 112 336 272 336 efanouts.correctfan.SLNK
w 1168 699 100 0 n#26 eseqs.Seq.LNK2 1136 688 1248 688 junction
w 1304 299 100 0 n#26 eseqs.Seq.LNK1 1136 720 1248 720 1248 288 1408 288 ecars.ecars#14.IVAL
w 752 690 100 0 n#25 hwin.hwin#24.in 736 672 736 688 816 688 eseqs.Seq.DOL2
w 792 722 100 0 n#23 hwin.hwin#22.in 816 720 816 720 eseqs.Seq.DOL1
s 1216 1184 100 0 $Id: aoCorrectCad.sch,v 1.2 2003/07/24 15:31:39 dlt Exp $
s 1520 -128 100 0 delay specified as parameter
s 1472 -96 100 0 General simulated Correct CAD with
s 512 704 100 0 IDLE
s 608 752 100 0 BUSY
s 1488 -48 100 0 Gemini Telescope Control System
[cell use]
use eais 352 903 100 0 loopRunning
xform 0 480 976
p 141 1049 100 0 0 DESC:Loop running flag
p 448 1040 100 0 0 DISV:1
p 96 718 100 0 0 EGU:mm
p 16 992 100 0 0 def(INP):0.000000000000000e+00
p 496 864 100 1024 1 name:$(prefix)wfcs:$(I)
use eais 1168 919 100 0 conMatX
xform 0 1296 992
p 957 1065 100 0 0 DESC:Current control matrix X
p 1136 734 100 0 0 DISS:NO_ALARM
p 1280 912 100 0 1 DISV:0
p 912 734 100 0 0 EGU:mm
p 912 830 100 0 0 PREC:14
p 896 1056 100 0 -1 def(INP):$(prefix)prepareCm.VALB
p 1280 912 100 1024 0 name:$(prefix)$(I)
use eais 1584 935 100 0 conMatY
xform 0 1712 1008
p 1373 1081 100 0 0 DESC:Current control matrix X
p 1328 622 100 0 0 DISV:1
p 1328 750 100 0 0 EGU:mm
p 1328 846 100 0 0 PREC:14
p 1312 1072 100 0 -1 def(INP):$(prefix)prepareCm.VALC
p 1696 928 100 1024 0 name:$(prefix)$(I)
use eais 672 1047 100 0 settled
xform 0 800 1120
p 461 1193 100 0 0 DESC:Loop settled flag
p 768 1184 100 0 0 DISV:1
p 416 862 100 0 0 EGU:mm
p 336 1136 100 0 0 def(INP):0.000000000000000e+00
p 816 1008 100 1024 1 name:$(prefix)wfcs:$(I)
p 736 1136 75 1280 -1 pproc(INP):NPP
use eseqs 840 312 100 0 Seq
xform 0 976 560
p 912 526 100 0 0 DLY1:0.0e+00
p 896 606 100 0 1 DLY2:$(delay)
p 848 286 100 0 1 PV:$(prefix)$(cadname)
p 1152 718 100 0 0 def(LNK1):0.0
p 816 752 75 1280 -1 palrm(SELL):NMS
p 784 720 75 1280 -1 pproc(DOL1):NPP
p 784 688 75 1280 -1 pproc(DOL2):NPP
p 1136 730 75 0 -1 pproc(LNK1):PP
p 1136 698 75 0 -1 pproc(LNK2):PP
use efanouts 272 199 100 0 correctfan
xform 0 392 352
p 384 192 100 1024 0 name:$(prefix)$(I)
use ecad4 -184 248 100 0 ecad4#43
xform 0 -48 624
p -272 48 100 0 0 FTVA:$(ftva)
p -272 16 100 0 0 FTVB:$(ftvb)
p -272 -16 100 0 0 FTVC:$(ftvc)
p -272 -48 100 0 0 FTVD:$(ftvd)
p -272 414 100 0 1 SNAM:tcs$(substring)$(cadname)CAD
p -48 912 100 256 -1 Type:cad
p -96 240 100 1024 1 name:$(prefix)$(cadname)
use outhier 1832 24 100 0 FLNK
xform 0 1824 64
use outhier 1832 248 100 0 VAL
xform 0 1824 288
use hwin 568 632 100 0 hwin#24
xform 0 640 672
p 558 600 100 0 0 typ(in):val
p 547 664 100 0 -1 val(in):$(CAR_IDLE)
use hwin 648 680 100 0 hwin#22
xform 0 720 720
p 638 648 100 0 0 typ(in):val
p 627 712 100 0 -1 val(in):$(CAR_BUSY)
use ecars 1432 8 100 0 ecars#14
xform 0 1568 176
p 1408 -2 100 0 1 name:$(prefix)$(cadname)C
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
[comments]
