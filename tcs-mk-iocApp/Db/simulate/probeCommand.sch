[schematic2]
uniq 5
[tools]
[detail]
w 72 466 100 0 n#1 elongins.elongins#22.VAL 16 496 48 496 48 464 144 464 ecad2.ecad2#8.INPA
w 1072 98 100 0 n#2 efanouts.efanouts#19.LNK2 864 224 1008 224 1008 96 1184 96 eseqs.d.SLNK
w 496 210 100 0 n#3 ecad2.ecad2#8.STLK 464 208 576 208 576 176 624 176 efanouts.efanouts#19.SLNK
w -352 548 100 0 n#4 inhier.PROBE.P -416 544 -240 544 elongins.elongins#22.INP
s 1440 -128 100 0 simulators
s 1440 -96 100 0 Generic CAD/CAR for subsystem
s 1488 -48 100 0 Gemini Telescope Control System
s 1392 1184 100 0 probeCommand.sch
[cell use]
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
use elongins -216 440 100 0 elongins#22
xform 0 -112 512
p -496 542 100 0 0 PINI:NO
p -128 432 100 1024 -1 name:$(prefix)$(command)pa
use efanouts 648 40 100 0 efanouts#19
xform 0 744 192
p 736 32 100 1024 -1 name:$(prefix)$(command)f
p 624 334 100 0 1 def(LNK1):$(prefix)probeC:ms1.PROC
use inhier -408 504 100 0 PROBE
xform 0 -416 544
use ecad2 168 120 100 0 ecad2#8
xform 0 304 432
p 192 798 100 0 -1 SNAM:$(snam)
p 160 62 100 0 1 name:$(prefix)$(command)
p 48 494 100 0 0 def(INPA):0.0
p 208 -200 100 0 0 typ(INPA):path
p 544 478 100 0 -1 def(OUTA):$(outa)
p 464 464 75 768 -1 pproc(OUTA):PP
p 208 920 100 0 0 FTVA:STRING
p 240 400 100 0 1 FTVB:STRING
use eseqs 1208 8 100 0 d
xform 0 1344 256
p 1280 222 100 0 1 DLY1:$(delay)
p 1568 430 100 0 -1 def(LNK1):$(prefix)probeC:ms2.PROC
p 800 -2468 100 0 0 PV:$(prefix)$(command):
p 1184 448 75 1280 -1 palrm(SELL):NMS
[comments]
