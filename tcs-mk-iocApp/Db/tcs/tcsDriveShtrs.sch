[schematic2]
uniq 1570
[tools]
[detail]
w 4404 1282 100 0 n#1569 eaos.botShtrEl.FLNK 4240 1280 4640 1280 4640 1200 4784 1200 eseqs.moveShtrsSeq.SLNK
w 5260 1458 100 0 n#1568 eseqs.moveShtrsSeq.LNK3 5104 1456 5488 1456 5488 1328 5664 1328 outhier.c#1566.p
w 5276 1490 100 0 n#1567 eseqs.moveShtrsSeq.LNK2 5104 1488 5520 1488 5520 1424 5664 1424 outhier.c#1564.p
w 5348 1522 100 0 n#1565 eseqs.moveShtrsSeq.LNK1 5104 1520 5664 1520 outhier.c#1563.p
w 4508 898 100 0 n#1562 eseqs.moveShtrsSeq.FLNK 5104 1200 5184 1200 5184 896 3904 896 3904 736 3984 736 eaos.topShtrPosDem.SLNK
w 4514 1268 100 0 n#1561 hwin.hwin#1560.in 4240 1008 4512 1008 4512 1456 4784 1456 eseqs.moveShtrsSeq.DOL3
w 4580 1490 100 0 n#1479 junction 4400 1248 4448 1248 4448 1488 4784 1488 eseqs.moveShtrsSeq.DOL2
w 3842 860 100 0 n#1479 eaos.botShtrEl.VAL 4240 1248 4400 1248 4400 1136 3840 1136 3840 512 4000 512 eaos.botShtrPosDem.DOL
w 4556 1522 100 0 n#1478 junction 4400 1520 4784 1520 eseqs.moveShtrsSeq.DOL1
w 3874 1132 100 0 n#1478 eaos.topShtrEl.VAL 4256 1520 4400 1520 4400 1424 3872 1424 3872 768 3984 768 eaos.topShtrPosDem.DOL
w 3586 -156 100 0 n#1558 elongouts.shtrSealed.FLNK 3424 -64 3584 -64 3584 -320 3712 -320 ecalcs.incrSealed.SLNK
w 3554 20 100 0 n#1557 elongouts.shtrSealed.VAL 3424 -96 3552 -96 3552 64 3712 64 ecalcs.incrSealed.INPA
w 2980 -62 100 0 n#1556 inhier.c#1540.P 2864 -64 3168 -64 elongouts.shtrSealed.DOL
w 5020 50 100 0 n#1554 estringouts.openStr.OUT 4992 48 5120 48 5120 -48 5248 -48 estringouts.shutterState.SLNK
w 5122 -100 100 0 n#1554 estringouts.closedStr.OUT 4992 -224 5120 -224 5120 -48 junction
w 4460 -46 100 0 n#1553 efanouts.fanSealed.LNK2 4416 -48 4576 -48 4576 -208 4736 -208 estringouts.closedStr.SLNK
w 4460 -14 100 0 n#1552 efanouts.fanSealed.LNK1 4416 -16 4576 -16 4576 64 4736 64 estringouts.openStr.SLNK
w 4124 -14 100 0 n#1549 ecalcs.incrSealed.VAL 4000 -128 4096 -128 4096 -16 4224 -16 efanouts.fanSealed.SELL
w 4052 -94 100 0 n#1548 ecalcs.incrSealed.FLNK 4000 -96 4176 -96 efanouts.fanSealed.SLNK
w 3172 1090 100 0 n#1538 inhier.SDIS.P 2896 1088 3520 1088 3520 1488 4000 1488 eaos.topShtrEl.SDIS
w 3156 1250 100 0 n#1537 inhier.SLNK.P 2896 1248 3488 1248 3488 1520 4000 1520 eaos.topShtrEl.SLNK
w 3252 1410 100 0 n#1536 inhier.BOT.P 2896 1408 3680 1408 3680 1280 3984 1280 eaos.botShtrEl.DOL
w 3412 1554 100 0 n#1535 inhier.TOP.P 2896 1552 4000 1552 eaos.topShtrEl.DOL
w 4100 626 100 0 n#1477 eaos.topShtrPosDem.FLNK 4240 768 4368 768 4368 624 3904 624 3904 480 4000 480 eaos.botShtrPosDem.SLNK
w 4100 1394 100 0 n#1436 eaos.topShtrEl.FLNK 4256 1552 4368 1552 4368 1392 3904 1392 3904 1248 3984 1248 eaos.botShtrEl.SLNK
s 5216 1696 100 0 $Id: tcsDriveShtrs.sch,v 1.1.1.1 1998/11/08 00:20:35 epics Exp $
s 5440 -496 100 0 Gemini Telescope Control System
[cell use]
use outhier 5656 1288 100 0 c#1566
xform 0 5648 1328
use outhier 5656 1384 100 0 c#1564
xform 0 5648 1424
use outhier 5656 1480 100 0 c#1563
xform 0 5648 1520
use hwin 4072 968 100 0 hwin#1560
xform 0 4144 1008
p 4051 1000 100 0 -1 val(in):$(CAD_START)
use eseqs 4808 1112 100 0 moveShtrsSeq
xform 0 4944 1360
p 4896 1406 100 0 1 DLY3:0.05
p 5232 1534 100 0 -1 def(LNK1):$(ec)moveShtrs.B
p 5232 1502 100 0 -1 def(LNK2):$(ec)moveShtrs.C
p 5232 1470 100 0 -1 def(LNK3):$(ec)moveShtrs.DIR
p 5120 1456 75 1024 -1 pproc(LNK3):PP
use elongouts 3192 -184 100 0 shtrSealed
xform 0 3296 -96
p 3008 -178 100 0 0 OMSL:closed_loop
p 3200 14 100 0 -1 DESC:Shutter sealed state
p 2896 -18 100 0 -1 def(DOL):$(ec)shtrSealed
p 3200 -226 100 0 1 SCAN:.5 second
use estringouts 4760 -8 100 0 openStr
xform 0 4864 64
p 4672 30 100 0 0 VAL:Open
p 4800 142 100 0 -1 DESC:Output Open
p 4992 48 75 768 -1 pproc(OUT):PP
use estringouts 4760 -280 100 0 closedStr
xform 0 4864 -208
p 4672 -242 100 0 0 VAL:Closed
p 4800 -130 100 0 -1 DESC:Output Closed
p 4992 -224 75 768 -1 pproc(OUT):PP
use estringouts 5272 -120 100 0 shutterState
xform 0 5376 -48
p 5184 -82 100 0 0 VAL:Open
p 5312 30 100 0 -1 DESC:Shutter state
use ecalcs 3736 -408 100 0 incrSealed
xform 0 3856 -144
p 3824 -194 100 0 1 CALC:A+1
use efanouts 4200 -232 100 0 fanSealed
xform 0 4296 -80
p 4032 -114 100 0 0 SELM:Specified
p 4448 -16 75 1280 -1 pproc(LNK1):PP
p 4448 -48 75 1280 -1 pproc(LNK2):PP
use inhier 2904 1512 100 0 TOP
xform 0 2896 1552
use inhier 2904 1368 100 0 BOT
xform 0 2896 1408
use inhier 2904 1208 100 0 SLNK
xform 0 2896 1248
use inhier 2904 1048 100 0 SDIS
xform 0 2896 1088
use inhier 2872 -104 100 0 c#1540
xform 0 2864 -64
use eaos 4008 1160 100 0 botShtrEl
xform 0 4112 1248
p 4032 1358 100 0 -1 DESC:Bottom shutter elevation demand
p 3952 974 100 0 0 EGU:rads
p 3728 1230 100 0 0 OMSL:closed_loop
p 3728 1102 100 0 0 PREC:14
p 4320 1214 100 0 0 def(OUT):0.0
p 4096 1152 100 1024 0 name:$(top)$(I)
use eaos 4024 1432 100 0 topShtrEl
xform 0 4128 1520
p 4048 1630 100 0 -1 DESC:Top shutter elevation demand
p 4096 1470 100 0 1 DISV:0
p 3968 1246 100 0 0 EGU:rads
p 3744 1502 100 0 0 OMSL:closed_loop
p 3744 1374 100 0 0 PREC:14
p 4336 1486 100 0 0 def(OUT):0.0
p 4112 1424 100 1024 0 name:$(top)$(I)
use eaos 4008 648 100 0 topShtrPosDem
xform 0 4112 736
p 4032 846 100 0 -1 DESC:Top shutter elevation demand
p 4080 686 100 0 0 DISV:1
p 3952 462 100 0 0 EGU:degrees
p 3728 718 100 0 0 OMSL:closed_loop
p 3728 590 100 0 0 PREC:14
p 4320 702 100 0 -1 def(OUT):$(sad)topShtrPosDem
p 4096 640 100 1024 0 name:$(top)$(I)
p 4240 704 75 768 -1 pproc(OUT):PP
use eaos 4024 392 100 0 botShtrPosDem
xform 0 4128 480
p 4048 590 100 0 -1 DESC:Bottom shutter elevation demand
p 3968 206 100 0 0 EGU:degrees
p 3744 462 100 0 0 OMSL:closed_loop
p 3744 334 100 0 0 PREC:14
p 4336 446 100 0 -1 def(OUT):$(sad)botShtrPosDem
p 4112 384 100 1024 0 name:$(top)$(I)
p 4256 448 75 768 -1 pproc(OUT):PP
use bc200tr 2640 -776 -100 0 frame
xform 0 4320 528
[comments]
