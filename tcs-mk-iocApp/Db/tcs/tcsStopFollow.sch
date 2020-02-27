[schematic2]
uniq 15
[tools]
[detail]
w 1072 594 100 0 n#14 efanouts.efanouts#2.FLNK 784 448 816 448 816 592 1376 592 outhier.flnk.p
w -56 226 100 0 n#13 inhier.Slnk.P -160 224 96 224 ecalcs.ecalcs#0.SLNK
w 416 450 100 0 n#12 ecalcs.ecalcs#0.FLNK 384 448 496 448 496 336 544 336 efanouts.efanouts#2.SLNK
w 792 386 100 0 n#11 efanouts.efanouts#2.LNK2 784 384 848 384 848 336 896 336 tcsStartSubCAD.tcsStartSubCAD#7.SubCadStart
w 792 418 100 0 n#10 efanouts.efanouts#2.LNK1 784 416 848 416 848 480 896 480 tcsStartSubCAD.tcsStartSubCAD#4.SubCadStart
w 470 418 100 0 n#3 ecalcs.ecalcs#0.VAL 384 416 592 416 efanouts.efanouts#2.SELL
w -50 610 100 0 n#1 inhier.Action.P -160 608 96 608 ecalcs.ecalcs#0.INPA
s 1440 -160 100 0 Gemini Telescope Control System
s 1424 -224 100 0 Trigger STOP or FOLLOW CAD in subsystem
s 1360 1072 100 0 $Id: tcsStopFollow.sch,v 1.2 2007/12/18 11:22:23 cjm Exp $
[cell use]
use outhier 1368 552 100 0 flnk
xform 0 1360 592
use inhier -208 576 100 0 Action
xform 0 -160 608
use inhier -208 176 100 0 Slnk
xform 0 -160 224
use bb200tr -576 -440 -100 0 frame
xform 0 704 384
use tcsStartSubCAD 920 256 100 0 tcsStartSubCAD#7
xform 0 1024 312
p 880 270 100 0 1 seta:subcad $(follow)
use tcsStartSubCAD 920 400 100 0 tcsStartSubCAD#4
xform 0 1024 456
p 880 414 100 0 1 seta:subcad $(stop)
use efanouts 568 200 100 0 efanouts#2
xform 0 664 352
p 400 318 100 0 0 SELM:Specified
p 512 190 100 0 -1 name:$(tcs)$(prefix)FanStopFollow
use ecalcs 120 136 100 0 ecalcs#0
xform 0 240 400
p 224 350 100 0 1 CALC:A+1
p 32 126 100 0 -1 name:$(tcs)$(prefix)CalcStopFollow
[comments]
