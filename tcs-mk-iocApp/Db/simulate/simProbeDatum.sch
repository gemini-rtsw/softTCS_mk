[schematic2]
uniq 35
[tools]
[detail]
w 48 546 100 0 n#28 elongins.elongins#25.VAL -16 544 160 544 ecad2.ecad2#8.INPA
w -368 596 100 0 n#26 inhier.PROBE.P -416 592 -272 592 elongins.elongins#25.INP
w 944 290 100 0 n#24 efanouts.efanouts#22.LNK2 880 288 1056 288 1056 176 1152 176 eseqs.d.SLNK
w 504 290 100 0 n#23 ecad2.ecad2#8.STLK 480 288 576 288 576 240 640 240 efanouts.efanouts#22.SLNK
w 1128 466 100 0 n#20 hwin.hwin#19.in 1152 464 1152 464 eseqs.d.DOL2
s 2304 -464 100 0 Gemini Telescope Control System
s 2256 -512 100 0 Generic CAD/CAR for subsystem
s 2256 -544 100 0 simulators
s 2016 1728 100 0 $Id: simProbeDatum.sch,v 1.1.1.1 1998/11/08 00:20:24 epics Exp $
[cell use]
use bc200tr -560 -744 -100 0 frame
xform 0 1120 560
use elongins -248 488 100 0 elongins#25
xform 0 -144 560
p -160 480 100 1024 -1 name:$(prefix)datumPn
use efanouts 664 104 100 0 efanouts#22
xform 0 760 256
p 624 398 100 0 1 def(LNK1):$(prefix)probeC:ms1.PROC
p 752 96 100 1024 -1 name:$(prefix)datumFan
use ebos 2168 392 100 0 ebos#21
xform 0 2272 480
p 2160 592 100 0 -1 DESC:Datum state of probe
p 1824 430 100 0 0 OMSL:supervisory
p 2192 304 100 0 1 ONAM:NOT DATUMED
p 2192 336 100 0 1 ZNAM:DATUMED
p 2256 384 100 1024 -1 name:$(prefix)probeDatumed
use hwin 984 424 100 0 hwin#19
xform 0 1056 464
p 963 456 100 0 -1 val(in):1
use inhier -408 552 100 0 PROBE
xform 0 -416 592
use ecad2 184 200 100 0 ecad2#8
xform 0 320 512
p 224 1000 100 0 0 FTVA:STRING
p 256 480 100 0 0 FTVB:LONG
p 288 382 100 0 -1 SNAM:$(snam)
p 64 574 100 0 0 def(INPA):0.0
p 560 558 100 0 -1 def(OUTA):$(outa)
p 176 142 100 0 1 name:$(prefix)probeDatum
p 480 544 75 768 -1 pproc(OUTA):PP
p 224 -120 100 0 0 typ(INPA):path
use eseqs 1176 88 100 0 d
xform 0 1312 336
p 1248 302 100 0 1 DLY1:$(delay)
p 1248 270 100 0 1 DLY2:0.0
p 768 -2388 100 0 0 PV:$(prefix)datum:
p 1568 494 100 0 -1 def(LNK1):$(prefix)probeC:ms2.PROC
p 1568 462 100 0 -1 def(LNK2):$(prefix)probeDatumed.VAL
p 1152 528 75 1280 -1 palrm(SELL):NMS
p 1488 464 75 1024 -1 pproc(LNK2):PP
[comments]
