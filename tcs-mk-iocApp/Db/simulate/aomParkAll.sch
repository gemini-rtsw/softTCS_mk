[schematic2]
uniq 154
[tools]
[detail]
w 498 -414 100 0 n#153 genericcad.genericcad#147.VAL 464 -416 592 -416 592 -528 672 -528 outhier.VAL.p
w 498 -334 100 0 n#152 genericcad.genericcad#147.VLNK 464 -336 592 -336 592 -224 672 -224 outhier.FLNK.p
w 834 150 100 0 n#149 genericcad.genericcad#147.FLNK 466 -367 832 -367 832 608 1344 608 elongouts.elongouts#119.SLNK
w 1272 -734 100 0 n#141 hwin.hwin#145.in 1248 -736 1344 -736 elongouts.elongouts#143.DOL
w 1272 -478 100 0 n#140 hwin.hwin#144.in 1248 -480 1344 -480 elongouts.elongouts#142.DOL
w 1416 -638 100 0 n#139 elongouts.elongouts#142.FLNK 1600 -480 1664 -480 1664 -640 1216 -640 1216 -768 1344 -768 elongouts.elongouts#143.SLNK
w 1410 -382 100 0 n#138 elongouts.elongouts#131.FLNK 1600 -176 1664 -176 1664 -384 1216 -384 1216 -512 1344 -512 elongouts.elongouts#142.SLNK
w 1410 178 100 0 n#137 elongouts.elongouts#120.FLNK 1600 384 1664 384 1664 176 1216 176 1216 48 1344 48 elongouts.elongouts#132.SLNK
w 1272 -174 100 0 n#130 hwin.hwin#133.in 1248 -176 1344 -176 elongouts.elongouts#131.DOL
w 1272 82 100 0 n#129 hwin.hwin#134.in 1248 80 1344 80 elongouts.elongouts#132.DOL
w 1416 -78 100 0 n#128 elongouts.elongouts#132.FLNK 1600 80 1664 80 1664 -80 1216 -80 1216 -208 1344 -208 elongouts.elongouts#131.SLNK
w 1272 386 100 0 n#118 hwin.hwin#122.in 1248 384 1344 384 elongouts.elongouts#120.DOL
w 1272 642 100 0 n#117 hwin.hwin#121.in 1248 640 1344 640 elongouts.elongouts#119.DOL
w 1416 482 100 0 n#115 elongouts.elongouts#119.FLNK 1600 640 1664 640 1664 480 1216 480 1216 352 1344 352 elongouts.elongouts#120.SLNK
s 2096 1104 100 0 agParkAll.sch
[cell use]
use outhier 664 -264 100 0 FLNK
xform 0 656 -224
use outhier 664 -568 100 0 VAL
xform 0 656 -528
use genericcad 200 -472 100 0 genericcad#147
xform 0 328 -376
p 176 -512 100 0 1 seta:command park
p 176 -544 100 0 1 setb:delay 5.0
p 176 -576 100 0 1 setc:snam tcsAgGenericCAD
p 176 -608 100 0 0 setd:outa 0.0
use hwin 1080 40 100 0 hwin#134
xform 0 1152 80
p 1059 72 100 0 -1 val(in):$(CAD_MARK)
use hwin 1080 -216 100 0 hwin#133
xform 0 1152 -176
p 1059 -184 100 0 -1 val(in):$(CAD_START)
use hwin 1080 600 100 0 hwin#121
xform 0 1152 640
p 1059 632 100 0 -1 val(in):$(CAD_MARK)
use hwin 1080 344 100 0 hwin#122
xform 0 1152 384
p 1059 376 100 0 -1 val(in):$(CAD_START)
use hwin 1080 -520 100 0 hwin#144
xform 0 1152 -480
p 1059 -488 100 0 -1 val(in):$(CAD_MARK)
use hwin 1080 -776 100 0 hwin#145
xform 0 1152 -736
p 1059 -744 100 0 -1 val(in):$(CAD_START)
use elongouts 1368 -40 100 0 elongouts#132
xform 0 1472 48
p 1392 142 100 0 -1 DESC:Mark directive
p 1184 -34 100 0 0 OMSL:closed_loop
p 1680 14 100 0 -1 def(OUT):$(p2)Ctrl.DIR
p 1456 -48 100 1024 -1 name:$(aom)ngsPr2mPark
p 1600 16 75 768 -1 pproc(OUT):PP
use elongouts 1368 -296 100 0 elongouts#131
xform 0 1472 -208
p 1392 -114 100 0 -1 DESC:Start Directive
p 1184 -290 100 0 0 OMSL:closed_loop
p 1680 -242 100 0 -1 def(OUT):$(p2)Ctrl.DIR
p 1456 -304 100 1024 -1 name:$(aom)ngsPr2sPark
p 1600 -240 75 768 -1 pproc(OUT):PP
use elongouts 1368 520 100 0 elongouts#119
xform 0 1472 608
p 1392 702 100 0 -1 DESC:Mark directive
p 1184 526 100 0 0 OMSL:closed_loop
p 1680 574 100 0 -1 def(OUT):$(p1)Ctrl.DIR
p 1456 512 100 1024 -1 name:$(aom)ngsPr1mPark
p 1600 576 75 768 -1 pproc(OUT):PP
use elongouts 1368 264 100 0 elongouts#120
xform 0 1472 352
p 1392 446 100 0 -1 DESC:Start Directive
p 1184 494 100 0 0 EGU:units
p 1184 270 100 0 0 OMSL:closed_loop
p 1184 526 100 0 0 PINI:NO
p 1680 318 100 0 -1 def(OUT):$(p1)Ctrl.DIR
p 1456 256 100 1024 -1 name:$(aom)ngsPr1sPark
p 1600 320 75 768 -1 pproc(OUT):PP
use elongouts 1368 -600 100 0 elongouts#142
xform 0 1472 -512
p 1392 -418 100 0 -1 DESC:Mark directive
p 1184 -594 100 0 0 OMSL:closed_loop
p 1680 -546 100 0 -1 def(OUT):$(p3)Ctrl.DIR
p 1456 -608 100 1024 -1 name:$(aom)ngsPr3mPark
p 1600 -544 75 768 -1 pproc(OUT):PP
use elongouts 1368 -856 100 0 elongouts#143
xform 0 1472 -768
p 1392 -674 100 0 -1 DESC:Start Directive
p 1184 -850 100 0 0 OMSL:closed_loop
p 1680 -802 100 0 -1 def(OUT):$(p3)Ctrl.DIR
p 1456 -864 100 1024 -1 name:$(aom)ngsPr3sPark
p 1600 -800 75 768 -1 pproc(OUT):PP
use bc200tr -640 -1368 -100 0 frame
xform 0 1040 -64
[comments]
