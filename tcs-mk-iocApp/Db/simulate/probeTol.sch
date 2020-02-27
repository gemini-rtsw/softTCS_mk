[schematic2]
uniq 28
[tools]
[detail]
w 792 338 100 0 n#25 efanouts.efanouts#23.LNK2 736 336 896 336 896 208 992 208 eseqs.d.SLNK
w 344 322 100 0 n#24 ecad2.ecad2#8.STLK 320 320 416 320 416 288 496 288 efanouts.efanouts#23.SLNK
s 1392 1184 100 0 probeTol.sch
s 1488 -48 100 0 Gemini Telescope Control System
s 1472 -112 100 0 Probe tolerance set command
[cell use]
use efanouts 520 152 100 0 efanouts#23
xform 0 616 304
p 608 144 100 1024 -1 name:$(prefix)tolFan
p 464 446 100 0 1 def(LNK1):$(prefix)probeC:ms1.PROC
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
use ecad2 24 232 100 0 ecad2#8
xform 0 160 544
p 48 430 100 0 -1 SNAM:tcsAGtoleranceCAD
p 16 174 100 0 1 name:$(prefix)tolerance
p -96 606 100 0 0 def(INPA):0.0
p 64 -88 100 0 0 typ(INPA):path
p 400 590 100 0 -1 def(OUTA):$(prefix)xyTol.VAL
p 320 576 75 768 -1 pproc(OUTA):PP
p 64 1032 100 0 0 FTVA:DOUBLE
p 96 512 100 0 0 FTVB:DOUBLE
p 336 512 75 1024 -1 pproc(OUTB):PP
p 400 526 100 0 -1 def(OUTB):$(prefix)zTol.VAL
use eseqs 1016 120 100 0 d
xform 0 1152 368
p 1088 334 100 0 1 DLY1:$(delay)
p 1376 542 100 0 -1 def(LNK1):$(prefix)probeC:ms2.PROC
p 992 560 75 1280 -1 palrm(SELL):NMS
p 1104 112 100 1024 -1 name:$(prefix)tolDel
[comments]
