[schematic2]
uniq 46
[tools]
[detail]
w 168 123 100 0 n#45 ecad4.ecad4#44.STLK 160 112 224 112 224 176 240 176 efanouts.Fan.SLNK
w 920 738 100 0 n#43 eaos.Busy.FLNK 1200 880 1280 880 1280 736 608 736 608 320 944 320 eseqs.CarVals.SLNK
w 664 50 100 0 n#42 efanouts.Fan.LNK2 480 224 576 224 576 48 800 48 tcsAllSubsysCad.tcsAllSubsysCad#36.slnk
w 578 576 100 0 n#41 efanouts.Fan.LNK1 480 256 576 256 576 848 944 848 eaos.Busy.SLNK
w 1400 658 100 0 n#26 eseqs.CarVals.LNK1 1264 640 1296 640 1296 656 1552 656 ecars.ecars#14.IVAL
w 1288 818 100 0 n#26 eaos.Busy.OUT 1200 816 1424 816 1424 656 junction
w 888 642 100 0 n#40 hwin.hwin#24.in 880 640 944 640 eseqs.CarVals.DOL1
w 920 882 100 0 n#39 hwin.hwin#22.in 944 880 944 880 eaos.Busy.DOL
w 224 690 100 0 n#30 ecad4.ecad4#44.MESS 160 688 336 688 336 816 464 816 outhier.MESS.p
w 306 832 100 0 n#29 ecad4.ecad4#44.VAL 160 720 304 720 304 896 464 896 outhier.VAL.p
w -360 658 100 0 n#28 inhier.ICID.P -400 656 -272 656 -272 688 -160 688 ecad4.ecad4#44.ICID
w -288 722 100 0 n#27 inhier.DIR.P -400 736 -368 736 -368 720 -160 720 ecad4.ecad4#44.DIR
s 720 672 100 0 IDLE
s 752 928 100 0 BUSY
s 1440 -128 100 0 triggering subsystem CADs
s 1440 -96 100 0 Generic CAD/CAR for sequence command
s 1488 -48 100 0 Gemini Telescope Control System
s 1216 1184 100 0 $Id: tcsSeqCadCarB.sch,v 1.2 1998/11/16 19:08:16 cjm Exp $
[cell use]
use ecad4 -160 23 100 0 ecad4#44
xform 0 0 400
p -128 272 100 0 -1 SNAM:tcsCAD$(seqcommand)
p 64 -208 100 0 0 def(OUTA):$(outa)
p 64 -240 100 0 0 def(OUTB):$(outb)
p 64 -272 100 0 0 def(OUTC):$(outc)
p 64 -304 100 0 0 def(OUTD):$(outd)
p -48 16 100 1024 1 name:$(tcs)$(seqcommand)
use eaos 968 760 100 0 Busy
xform 0 1072 848
p 724 1034 100 0 0 DESC:Sets CAR record to BUSY
p 688 830 100 0 0 OMSL:closed_loop
p 1184 928 100 1024 1 name:$(tcs)$(seqcommand)$(I)
p 1200 816 75 768 -1 pproc(OUT):PP
use tcsAllSubsysCad 824 -152 100 0 tcsAllSubsysCad#36
xform 0 872 -16
p 736 -146 100 0 1 seta:cad $(seqcommand)
use efanouts 264 40 100 0 Fan
xform 0 360 192
p 240 0 100 0 1 name:$(tcs)$(seqcommand)$(I)
use outhier 456 856 100 0 VAL
xform 0 448 896
use outhier 456 776 100 0 MESS
xform 0 448 816
use inhier -392 696 100 0 DIR
xform 0 -400 736
use inhier -392 616 100 0 ICID
xform 0 -400 656
use hwin 712 600 100 0 hwin#24
xform 0 784 640
p 702 568 100 0 0 typ(in):val
p 691 632 100 0 -1 val(in):$(CAR_IDLE)
use hwin 776 840 100 0 hwin#22
xform 0 848 880
p 766 808 100 0 0 typ(in):val
p 755 872 100 0 -1 val(in):$(CAR_BUSY)
use ecars 1576 376 100 0 ecars#14
xform 0 1712 544
p 1552 366 100 0 1 name:$(tcs)$(seqcommand)C
use eseqs 968 232 100 0 CarVals
xform 0 1104 480
p 1024 526 100 0 1 DLY1:$(delay)
p 1024 526 100 0 0 DLY2:0.0
p 1280 638 100 0 0 def(LNK1):0.0
p 1248 224 100 1024 1 name:$(tcs)$(seqcommand)$(I)
p 944 672 75 1280 -1 palrm(SELL):NMS
p 912 640 75 1280 -1 pproc(DOL1):NPP
p 912 608 75 1280 -1 pproc(DOL2):NPP
p 1264 650 75 0 -1 pproc(LNK1):PP
p 1264 618 75 0 -1 pproc(LNK2):PP
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
[comments]
