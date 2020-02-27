[schematic2]
uniq 63
[tools]
[detail]
w 1488 1106 100 0 n#62 eaos.DomeOff.FLNK 1616 1312 1760 1312 1760 1104 1264 1104 1264 976 1360 976 eaos.ShtrsOff.SLNK
w 960 1074 100 0 n#61 estringouts.m1Park.FLNK 816 1072 1152 1072 1152 1280 1360 1280 eaos.DomeOff.SLNK
w 1288 1010 100 0 n#60 hwin.hwin#58.in 1264 1008 1360 1008 eaos.ShtrsOff.DOL
w 1280 1314 100 0 n#59 hwin.hwin#57.in 1248 1312 1360 1312 eaos.DomeOff.DOL
w 514 832 100 0 n#50 ecad2.ecad2#8.VALA 160 528 512 528 512 1088 560 1088 estringouts.m1Park.DOL
w 546 680 100 0 n#49 efanouts.efanouts#32.LNK1 480 256 544 256 544 1056 560 1056 estringouts.m1Park.SLNK
w 578 512 100 0 n#47 efanouts.efanouts#32.LNK2 480 224 576 224 576 752 944 752 eaos.Busy.SLNK
w 664 50 100 0 n#46 efanouts.efanouts#32.LNK3 480 192 576 192 576 48 800 48 tcsAllSubsysCad.tcsAllSubsysCad#36.slnk
w 920 642 100 0 n#43 eaos.Busy.FLNK 1200 784 1280 784 1280 640 608 640 608 224 944 224 eseqs.CarVals.SLNK
w 1288 722 100 0 n#26 eaos.Busy.OUT 1200 720 1424 720 1424 560 junction
w 1400 562 100 0 n#26 eseqs.CarVals.LNK1 1264 544 1296 544 1296 560 1552 560 ecars.ecars#14.IVAL
w 888 546 100 0 n#40 hwin.hwin#24.in 880 544 944 544 eseqs.CarVals.DOL1
w 920 786 100 0 n#39 hwin.hwin#22.in 944 784 944 784 eaos.Busy.DOL
w 210 232 100 0 n#33 ecad2.ecad2#8.STLK 160 240 208 240 208 176 240 176 efanouts.efanouts#32.SLNK
w 224 690 100 0 n#30 ecad2.ecad2#8.MESS 160 688 336 688 336 816 464 816 outhier.MESS.p
w 306 832 100 0 n#29 ecad2.ecad2#8.VAL 160 720 304 720 304 896 464 896 outhier.VAL.p
w -360 658 100 0 n#28 inhier.ICID.P -400 656 -272 656 -272 688 -160 688 ecad2.ecad2#8.ICID
w -288 722 100 0 n#27 inhier.DIR.P -400 736 -368 736 -368 720 -160 720 ecad2.ecad2#8.DIR
s 1968 -448 100 0 Gemini Telescope Control System
s 752 832 100 0 BUSY
s 720 576 100 0 IDLE
s 1984 -512 100 0 Issue PARK sequence command
s 1712 1744 100 0 $Id: tcsSeqPark.sch,v 1.2 2002/05/14 09:13:50 ajf Exp $
[cell use]
use hwin 1096 968 100 0 hwin#58
xform 0 1168 1008
p 1075 1000 100 0 -1 val(in):0
use hwin 1080 1272 100 0 hwin#57
xform 0 1152 1312
p 1059 1304 100 0 -1 val(in):0
use hwin 776 744 100 0 hwin#22
xform 0 848 784
p 766 712 100 0 0 typ(in):val
p 755 776 100 0 -1 val(in):$(CAR_BUSY)
use hwin 712 504 100 0 hwin#24
xform 0 784 544
p 702 472 100 0 0 typ(in):val
p 691 536 100 0 -1 val(in):$(CAR_IDLE)
use bc200tr -864 -728 -100 0 frame
xform 0 816 576
use eaos 1384 888 100 0 ShtrsOff
xform 0 1488 976
p 1408 1054 100 0 -1 DESC:Disable Shtrs
p 1328 702 100 0 0 EGU:None
p 1104 958 100 0 0 OMSL:closed_loop
p 1696 942 100 0 -1 def(OUT):$(tcs)autoMoveShtrs
p 1552 848 100 1024 1 name:$(tcs)$(seqcommand)$(I)
p 1616 944 75 768 -1 pproc(OUT):PP
use eaos 1384 1192 100 0 DomeOff
xform 0 1488 1280
p 1408 1358 100 0 -1 DESC:Disable dome
p 1328 1006 100 0 0 EGU:None
p 1104 1262 100 0 0 OMSL:closed_loop
p 1696 1246 100 0 -1 def(OUT):$(tcs)autoMoveDome
p 1552 1152 100 1024 1 name:$(tcs)$(seqcommand)$(I)
p 1616 1248 75 768 -1 pproc(OUT):PP
use eaos 968 664 100 0 Busy
xform 0 1072 752
p 724 938 100 0 0 DESC:Sets CAR record to BUSY
p 688 734 100 0 0 OMSL:closed_loop
p 1088 832 100 1024 1 name:$(tcs)$(seqcommand)$(I)
p 1200 720 75 768 -1 pproc(OUT):PP
use estringouts 584 984 100 0 m1Park
xform 0 688 1056
p 592 1134 100 0 -1 DESC:Output M1 park parameter
p 496 862 100 0 0 OMSL:closed_loop
p 896 1038 100 0 -1 def(OUT):$(m1)park.B
p 704 1136 100 1024 1 name:$(tcs)$(seqcommand)$(I)
use outhier 456 776 100 0 MESS
xform 0 448 816
use outhier 456 856 100 0 VAL
xform 0 448 896
use tcsAllSubsysCad 824 -152 100 0 tcsAllSubsysCad#36
xform 0 872 -16
p 736 -146 100 0 1 seta:cad $(seqcommand)
use efanouts 264 40 100 0 efanouts#32
xform 0 360 192
p 208 30 100 0 1 name:$(tcs)$(seqcommand)Fan
use inhier -392 616 100 0 ICID
xform 0 -400 656
use inhier -392 696 100 0 DIR
xform 0 -400 736
use ecars 1576 280 100 0 ecars#14
xform 0 1712 448
p 1552 270 100 0 1 name:$(tcs)$(seqcommand)C
use eseqs 968 136 100 0 CarVals
xform 0 1104 384
p 1024 430 100 0 1 DLY1:$(delay)
p 1024 430 100 0 0 DLY2:0.0
p 1280 542 100 0 0 def(LNK1):0.0
p 1168 96 100 1024 1 name:$(tcs)$(seqcommand):$(I)
p 944 576 75 1280 -1 palrm(SELL):NMS
p 912 544 75 1280 -1 pproc(DOL1):NPP
p 912 512 75 1280 -1 pproc(DOL2):NPP
p 1264 554 75 0 -1 pproc(LNK1):PP
p 1264 522 75 0 -1 pproc(LNK2):PP
use ecad2 -136 152 100 0 ecad2#8
xform 0 0 464
p -96 952 100 0 0 FTVA:STRING
p -128 398 100 0 -1 SNAM:tcsCAD$(seqcommand)
p -256 526 100 0 0 def(INPA):
p 241 509 100 0 0 def(OUTA):
p -144 94 100 0 1 name:$(tcs)$(seqcommand)
p 160 496 75 768 -1 pproc(OUTA):NPP
p -96 -168 100 0 0 typ(INPA):path
[comments]
