[schematic2]
uniq 19
[tools]
[detail]
w -256 578 100 0 n#18 inhier.PROBE.P -368 576 -96 576 ecad2.ecad2#8.INPA
w 274 816 100 0 n#16 ecad2.ecad2#8.VALA 224 608 272 608 272 976 368 976 esirs.esirs#15.INP
w 1456 866 100 0 n#14 tcscar.tcscar#4.FLNK 1328 864 1632 864 outhier.VLNK.p
w 1432 834 100 0 n#12 tcscar.tcscar#4.VAL 1328 832 1584 832 outhier.VAL.p
w 1096 642 100 0 n#10 efanouts.fan.LNK2 752 368 864 368 864 640 1376 640 outhier.FLNK.p
w 798 338 100 0 n#9 efanouts.fan.LNK3 752 336 880 336 880 208 992 208 eseqs.delay.SLNK
w 818 602 100 0 n#5 efanouts.fan.LNK1 752 400 816 400 816 768 912 768 tcscar.tcscar#4.START
w 350 324 100 0 n#3 ecad2.ecad2#8.STLK 224 320 512 320 efanouts.fan.SLNK
s 1472 -112 130 0 A&G probe follow command
s 1392 1184 100 0 probeFollow.sch
s 1488 -48 100 0 Gemini Telescope Control System
[cell use]
use inhier -360 536 100 0 PROBE
xform 0 -368 576
use esirs 392 728 100 0 esirs#15
xform 0 576 880
p 480 720 100 1024 -1 name:$(prefix)followS
use outhier 1648 848 100 0 VLNK
xform 0 1616 864
use outhier 1368 600 100 0 FLNK
xform 0 1360 640
use outhier 1576 792 100 0 VAL
xform 0 1568 832
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
use ecad2 -72 232 100 0 ecad2#8
xform 0 64 544
p -16 446 100 0 -1 SNAM:tcsAgFollowCAD
p -32 222 100 0 -1 name:$(prefix)follow
p -192 606 100 0 0 def(INPA):0.0
p -32 -88 100 0 0 typ(INPA):path
p 304 590 100 0 0 def(OUTA):0.0
p 224 576 75 768 -1 pproc(OUTA):PP
p -32 1032 100 0 0 FTVA:STRING
p 0 512 100 0 0 FTVB:LONG
use eseqs 1016 120 100 0 delay
xform 0 1152 368
p 1088 334 100 0 1 DLY1:$(delay)
p 1392 526 100 0 -1 def(LNK1):$(prefix)followC:ms2.PROC
p 608 -2356 100 0 0 PV:$(prefix)follow
p 992 560 75 1280 -1 palrm(SELL):NMS
use tcscar 936 680 100 0 tcscar#4
xform 0 1120 800
p 1008 926 100 0 1 seta:car followC
use efanouts 536 184 100 0 fan
xform 0 632 336
p 368 -468 100 0 0 PV:$(prefix)follow
[comments]
