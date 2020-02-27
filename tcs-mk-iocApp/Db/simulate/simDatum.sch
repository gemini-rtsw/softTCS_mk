[schematic2]
uniq 23
[tools]
[detail]
w 392 411 100 0 n#22 hwin.hwin#21.in 368 400 464 400 efanouts.fan.SELL
w 168 331 100 0 n#19 ecad2.ecad2#8.STLK -32 320 416 320 efanouts.fan.SLNK
w 872 498 100 0 n#18 hwin.hwin#16.in 896 496 896 496 eseqs.delay.DOL2
w 1360 866 100 0 n#14 tcscar.tcscar#4.FLNK 1232 864 1536 864 outhier.VLNK.p
w 1336 834 100 0 n#12 tcscar.tcscar#4.VAL 1232 832 1488 832 outhier.VAL.p
w 1000 642 100 0 n#10 efanouts.fan.LNK2 656 368 768 368 768 640 1280 640 outhier.FLNK.p
w 702 338 100 0 n#9 efanouts.fan.LNK3 656 336 784 336 784 208 896 208 eseqs.delay.SLNK
w 722 602 100 0 n#5 efanouts.fan.LNK1 656 400 720 400 720 768 816 768 tcscar.tcscar#4.START
s 1216 1184 100 0 $Id: simDatum.sch,v 1.2 1998/11/16 19:28:28 cjm Exp $
s 1488 -48 100 0 Gemini Telescope Control System
s 1440 -96 100 0 Generic CAD/CAR for subsystem
s 1440 -128 100 0 simulators
[cell use]
use hwin 176 359 100 0 hwin#21
xform 0 272 400
p 179 392 100 0 -1 val(in):$(mask)
use hwin 728 456 100 0 hwin#16
xform 0 800 496
p 707 488 100 0 -1 val(in):1
use ebos 504 -152 100 0 ebos#15
xform 0 608 -64
p 160 -114 100 0 0 OMSL:supervisory
p 160 -210 100 0 0 ONAM:True
p 160 -178 100 0 0 ZNAM:False
p 596 -160 100 1024 -1 name:$(prefix)datumS
use outhier 1552 848 100 0 VLNK
xform 0 1520 864
use outhier 1272 600 100 0 FLNK
xform 0 1264 640
use outhier 1480 792 100 0 VAL
xform 0 1472 832
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
use ecad2 -328 232 100 0 ecad2#8
xform 0 -192 544
p -288 1032 100 0 0 FTVA:STRING
p -256 512 100 0 0 FTVB:LONG
p -304 910 100 0 -1 SNAM:$(snam)
p -448 606 100 0 0 def(INPA):0.0
p 48 590 100 0 -1 def(OUTA):$(outa)
p -336 174 100 0 1 name:$(prefix)datum
p -32 576 75 768 -1 pproc(OUTA):PP
p -288 -88 100 0 0 typ(INPA):path
use eseqs 920 120 100 0 delay
xform 0 1056 368
p 992 334 100 0 1 DLY1:$(delay)
p 992 302 100 0 1 DLY2:0.0
p 512 -2356 100 0 0 PV:$(prefix)datum:
p 1232 526 100 0 -1 def(LNK1):$(top)$(subsys)datumC:ms2.PROC
p 1296 494 100 0 -1 def(LNK2):$(prefix)datumS.VAL
p 896 560 75 1280 -1 palrm(SELL):NMS
p 1232 496 75 1024 -1 pproc(LNK2):PP
use tcscar 840 680 100 0 tcscar#4
xform 0 1024 800
p 896 958 100 0 1 seta:prefix $(prefix)
p 896 926 100 0 1 setb:car datumC
use efanouts 440 184 100 0 fan
xform 0 536 336
p 272 -468 100 0 0 PV:$(prefix)datum:
p 400 256 100 0 1 SELM:Mask
[comments]
