[schematic2]
uniq 30
[tools]
[detail]
w 512 635 100 0 n#29 ecad4.ecad4#16.VALA 448 624 624 624 624 896 768 896 estringout.s.DOL
w 1104 507 100 0 n#28 eseqs.d.LNK2 1440 384 1600 384 1600 496 656 496 656 832 768 832 estringout.s.U2
w 56 402 100 0 n#23 elongins.elongins#20.VAL 32 400 128 400 ecad4.ecad4#16.INPD
w -328 450 100 0 n#21 inhier.CPROBE.P -384 448 -224 448 elongins.elongins#20.INP
w 1010 200 100 0 n#15 efanouts.f.LNK2 880 256 1008 256 1008 96 1120 96 eseqs.d.SLNK
w 526 210 100 0 n#3 ecad4.ecad4#16.STLK 448 208 640 208 efanouts.f.SLNK
s 1440 -128 100 0 simulators
s 1440 -96 100 0 Generic CAD/CAR for subsystem
s 1488 -48 100 0 Gemini Telescope Control System
s 1392 1184 100 0 genericcad.sch
[cell use]
use estringout 768 519 100 0 s
xform 0 1072 816
p 912 992 100 0 -1 DESC:Holds final name of selection
p 864 750 100 0 1 OMSL:closed_loop
p 864 910 100 0 1 VAL:string
p 1488 768 100 0 -1 def(OUT):$(outa)
p 1184 800 100 1024 0 name:$(prefix)$(command):$(I)
p 1376 768 75 768 -1 pproc(OUT):PP
p 800 832 100 1024 -1 username(U2):PROC
use elongins -200 344 100 0 elongins#20
xform 0 -96 416
p -112 336 100 1024 -1 name:$(prefix)$(command)pc
use inhier -400 400 100 0 CPROBE
xform 0 -384 448
use ecad4 152 120 100 0 ecad4#16
xform 0 288 496
p 192 920 100 0 0 FTVA:STRING
p 224 400 100 0 0 FTVB:LONG
p 240 318 100 0 -1 SNAM:$(snam)
p 352 -16 100 0 0 def(INPC):$(outa)
p 272 576 100 0 0 def(OUTA):
p 496 400 100 0 -1 def(OUTD):$(outa)
p 144 110 100 0 1 name:$(prefix)$(command)
p 448 592 75 768 -1 pproc(OUTA):NPP
p 448 400 75 768 -1 pproc(OUTD):PP
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
use eseqs 1144 8 100 0 d
xform 0 1280 256
p 1216 222 100 0 1 DLY1:$(delay)
p 1216 192 100 0 1 DLY2:0.0
p 736 -2468 100 0 0 PV:$(prefix)$(command):
p 1520 414 100 0 -1 def(LNK1):$(prefix)$(mech)C:ms2.PROC
p 1120 448 75 1280 -1 palrm(SELL):NMS
use efanouts 664 72 100 0 f
xform 0 760 224
p 496 -580 100 0 0 PV:$(prefix)$(command):
p 576 366 100 0 1 def(LNK1):$(prefix)$(mech)C:ms1.PROC
[comments]
