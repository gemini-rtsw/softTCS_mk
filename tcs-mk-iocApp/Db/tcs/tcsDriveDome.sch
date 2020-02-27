[schematic2]
uniq 1562
[tools]
[detail]
w 4316 1010 100 0 n#1554 eaos.domeAz.VAL 4032 1008 4672 1008 eseqs.moveDomeSeq.DOL1
w 4676 354 100 0 n#1554 junction 4160 1008 4160 352 5264 352 eaos.carouselAz.DOL
w 5122 540 100 0 n#1561 eseqs.moveDomeSeq.FLNK 4992 688 5120 688 5120 320 5264 320 eaos.carouselAz.SLNK
w 4396 690 100 0 n#1560 eaos.domeAz.FLNK 4032 1040 4192 1040 4192 688 4672 688 eseqs.moveDomeSeq.SLNK
w 5116 978 100 0 n#1559 eseqs.moveDomeSeq.LNK2 4992 976 5312 976 5312 912 5472 912 outhier.c#1557.p
w 5116 1010 100 0 n#1558 eseqs.moveDomeSeq.LNK1 4992 1008 5312 1008 5312 1072 5472 1072 outhier.c#1556.p
w 4460 978 100 0 n#1555 hwin.hwin#1539.in 4032 816 4320 816 4320 976 4672 976 eseqs.moveDomeSeq.DOL2
w 3698 884 100 0 n#1552 efanouts.domeFan.LNK1 3600 688 3696 688 3696 1008 3776 1008 eaos.domeAz.SLNK
w 3172 690 100 0 n#1551 inhier.SDIS.P 3008 688 3408 688 efanouts.domeFan.SELL
w 3148 610 100 0 n#1550 inhier.SLNK.P 3008 608 3360 608 efanouts.domeFan.SLNK
w 3188 1170 100 0 n#1532 inhier.DOL.P 3024 1168 3424 1168 3424 1040 3776 1040 eaos.domeAz.DOL
s 5440 -496 100 0 Gemini Telescope Control System
s 5216 1696 100 0 $Id: tcsDriveDome.sch,v 1.1.1.1 1998/11/08 00:20:35 epics Exp $
[cell use]
use outhier 5464 1032 100 0 c#1556
xform 0 5456 1072
use outhier 5464 872 100 0 c#1557
xform 0 5456 912
use eseqs 4696 600 100 0 moveDomeSeq
xform 0 4832 848
p 4288 -1332 100 0 0 DLY2:0.05
p 5088 1022 100 0 -1 def(LNK1):$(ec)moveDome.B
p 5088 990 100 0 -1 def(LNK2):$(ec)moveDome.DIR
p 5008 976 75 1024 -1 pproc(LNK2):PP
use efanouts 3384 472 100 0 domeFan
xform 0 3480 624
p 3216 590 100 0 0 SELM:Specified
p 3632 688 75 1280 -1 pproc(LNK1):PP
use hwin 3864 776 100 0 hwin#1539
xform 0 3936 816
p 3843 808 100 0 -1 val(in):$(CAD_START)
use eaos 5288 232 100 0 carouselAz
xform 0 5392 320
p 5296 414 100 0 -1 DESC:Dome azimuth demand 
p 5360 286 100 0 0 DISV:1
p 5232 46 100 0 0 EGU:degrees
p 5008 302 100 0 0 OMSL:closed_loop
p 5008 174 100 0 0 PREC:14
p 5600 286 100 0 -1 def(OUT):$(sad)carouselAz
p 5376 224 100 1024 0 name:$(top)$(I)
p 5520 288 75 768 -1 pproc(OUT):PP
use eaos 3800 920 100 0 domeAz
xform 0 3904 1008
p 3824 1118 100 0 -1 DESC:Dome azimuth demand 
p 3872 974 100 0 1 DISV:1
p 3744 734 100 0 0 EGU:degrees
p 3520 990 100 0 0 OMSL:closed_loop
p 3520 862 100 0 0 PREC:14
p 4112 974 100 0 0 def(OUT):0.0
p 3888 912 100 1024 0 name:$(top)$(I)
use inhier 3032 1128 100 0 DOL
xform 0 3024 1168
use inhier 3016 568 100 0 SLNK
xform 0 3008 608
use inhier 3016 648 100 0 SDIS
xform 0 3008 688
use bc200tr 2640 -776 -100 0 frame
xform 0 4320 528
[comments]
