[schematic2]
uniq 16
[tools]
[detail]
w 1456 866 100 0 n#14 tcscar.tcscar#4.FLNK 1328 864 1632 864 outhier.VLNK.p
w 1432 834 100 0 n#12 tcscar.tcscar#4.VAL 1328 832 1584 832 outhier.VAL.p
w 1096 642 100 0 n#10 efanouts.fan.LNK2 752 368 864 368 864 640 1376 640 outhier.FLNK.p
w 798 338 100 0 n#9 efanouts.fan.LNK3 752 336 880 336 880 208 992 208 eseqs.del.SLNK
w 818 602 100 0 n#5 efanouts.fan.LNK1 752 400 816 400 816 768 912 768 tcscar.tcscar#4.START
w 414 91 100 0 n#3 ecad8.ecad8#15.STLK 352 80 512 80 512 320 efanouts.fan.SLNK
s 1392 1184 100 0 gpGenericCad8.sch
s 1488 -48 100 0 Gemini Telescope Control System
s 1440 -96 100 0 Generic CAD/CAR for subsystem
s 1440 -128 100 0 simulators
[cell use]
use ecad8 32 -9 100 0 ecad8#15
xform 0 192 496
p 128 208 100 0 1 SNAM:$(snam)
p 368 704 100 0 -1 def(OUTA):$(outa)
p 144 -16 100 1024 1 name:$(prefix)$(command)
p 352 720 75 768 -1 pproc(OUTA):PP
use outhier 1648 848 100 0 VLNK
xform 0 1616 864
use outhier 1368 600 100 0 FLNK
xform 0 1360 640
use outhier 1576 792 100 0 VAL
xform 0 1568 832
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
use eseqs 1016 120 100 0 del
xform 0 1152 368
p 1088 334 100 0 1 DLY1:$(delay)
p 608 -2356 100 0 0 PV:$(prefix)$(command):
p 1328 526 100 0 -1 def(LNK1):$(prefix)$(command)C:ms2.PROC
p 992 560 75 1280 -1 palrm(SELL):NMS
use tcscar 936 680 100 0 tcscar#4
xform 0 1120 800
p 992 958 100 0 1 seta:prefix $(prefix)
p 992 926 100 0 1 setb:car $(command)C
use efanouts 536 184 100 0 fan
xform 0 632 336
p 368 -468 100 0 0 PV:$(prefix)$(command):
[comments]
