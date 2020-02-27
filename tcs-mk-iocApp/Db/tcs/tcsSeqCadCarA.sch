[schematic2]
uniq 50
[tools]
[detail]
w 856 130 100 0 n#49 efanouts.fan.LNK3 560 240 704 240 704 128 1056 128 eseqs.CarVals.SLNK
w 1192 738 100 0 n#48 efanouts.fan.LNK2 560 272 704 272 704 736 1728 736 outhier.STLK.p
w 674 640 100 0 n#46 efanouts.fan.LNK1 560 304 672 304 672 928 1056 928 eaos.Busy.SLNK
w 216 226 100 0 n#45 ecad2.ecad2#8.STLK 160 224 320 224 efanouts.fan.SLNK
w 1032 450 100 0 n#41 hwin.hwin#24.in 1056 448 1056 448 eseqs.CarVals.DOL1
w 1496 898 100 0 n#39 eaos.Busy.OUT 1312 896 1728 896 outhier.c#38.p
w 1032 962 100 0 n#37 hwin.hwin#22.in 1056 960 1056 960 eaos.Busy.DOL
w 1608 466 100 0 n#34 eseqs.CarVals.LNK1 1376 448 1408 448 1408 464 1856 464 outhier.c#32.p
w 224 674 100 0 n#30 ecad2.ecad2#8.MESS 160 672 336 672 336 800 464 800 outhier.MESS.p
w 306 816 100 0 n#29 ecad2.ecad2#8.VAL 160 704 304 704 304 880 464 880 outhier.VAL.p
w -360 642 100 0 n#28 inhier.ICID.P -400 640 -272 640 -272 672 -160 672 ecad2.ecad2#8.ICID
w -288 706 100 0 n#27 inhier.DIR.P -400 720 -368 720 -368 704 -160 704 ecad2.ecad2#8.DIR
s 1232 1184 100 0 $Id: tcsSeqCadCarA.sch,v 1.2 2002/05/14 09:13:49 ajf Exp $
s 832 480 100 0 IDLE
s 880 1008 100 0 BUSY
s 1440 -128 100 0 with specified CAR set
s 1440 -96 100 0 Generic CAD/CAR for sequence command
s 1488 -48 100 0 Gemini Telescope Control System
[cell use]
use outhier 1720 696 100 0 STLK
xform 0 1712 736
use outhier 1720 856 100 0 c#38
xform 0 1712 896
use outhier 1848 424 100 0 c#32
xform 0 1840 464
use outhier 456 840 100 0 VAL
xform 0 448 880
use outhier 456 760 100 0 MESS
xform 0 448 800
use efanouts 344 88 100 0 fan
xform 0 440 240
p 496 48 100 1024 1 name:$(tcs)$(seqcommand)$(I)
use eaos 1080 840 100 0 Busy
xform 0 1184 928
p 836 1114 100 0 0 DESC:Writes BUSY to CAR record
p 800 910 100 0 0 OMSL:closed_loop
p 1408 910 100 0 0 def(DOL):0.0
p 1408 910 100 0 -1 def(OUT):$(tcs)$(carname).IVAL
p 1248 1008 100 1024 1 name:$(tcs)$(seqcommand)$(I)
p 1312 896 75 768 -1 pproc(OUT):PP
use inhier -392 680 100 0 DIR
xform 0 -400 720
use inhier -392 600 100 0 ICID
xform 0 -400 640
use hwin 888 408 100 0 hwin#24
xform 0 960 448
p 878 376 100 0 0 typ(in):val
p 867 440 100 0 -1 val(in):$(CAR_IDLE)
use hwin 888 920 100 0 hwin#22
xform 0 960 960
p 867 952 100 0 -1 val(in):$(CAR_BUSY)
use eseqs 1080 40 100 0 CarVals
xform 0 1216 288
p 1136 334 100 0 1 DLY1:$(delay)
p 1136 334 100 0 0 DLY2:0.0
p 1488 478 100 0 -1 def(LNK1):$(tcs)$(carname).IVAL
p 1488 430 100 0 0 def(LNK2):0.0
p 1232 528 100 1024 1 name:$(tcs)$(seqcommand)$(I)
p 1056 480 75 1280 -1 palrm(SELL):NMS
p 1024 448 75 1280 -1 pproc(DOL1):NPP
p 1024 416 75 1280 -1 pproc(DOL2):NPP
p 1376 458 75 0 -1 pproc(LNK1):PP
p 1376 426 75 0 -1 pproc(LNK2):PP
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
use ecad2 -136 136 100 0 ecad2#8
xform 0 0 448
p -96 936 100 0 0 FTVA:STRING
p -128 366 100 0 -1 SNAM:tcsCAD$(seqcommand)
p -256 510 100 0 0 def(INPA):
p 240 494 100 0 0 def(OUTA):
p -144 78 100 0 1 name:$(tcs)$(seqcommand)
p 160 480 75 768 -1 pproc(OUTA):NPP
p -96 -184 100 0 0 typ(INPA):path
[comments]
