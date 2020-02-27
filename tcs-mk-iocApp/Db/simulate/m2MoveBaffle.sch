[schematic2]
uniq 50
[tools]
[detail]
w 264 843 100 0 n#49 ecad4.ecad4#43.OUTA 112 368 176 368 176 832 400 832 esirs.DeployBafflePos.SLNK
w 960 843 100 0 n#48 ecad4.ecad4#43.OUTB 112 304 208 304 208 592 896 592 896 832 1072 832 esirs.CentralBafflePos.SLNK
w 1536 370 100 0 n#42 ecars.ecars#14.VAL 1504 368 1616 368 outhier.VAL.p
w 1536 146 100 0 n#40 ecars.ecars#14.FLNK 1504 144 1616 144 outhier.FLNK.p
w 272 -14 100 0 n#38 ecad4.ecad4#43.STLK 112 -16 480 -16 480 32 576 32 eseqs.CarVals.SLNK
w 1032 370 100 0 n#26 eseqs.CarVals.LNK1 896 352 928 352 928 368 1184 368 ecars.ecars#14.IVAL
w 944 322 100 0 n#26 eseqs.CarVals.LNK2 896 320 1040 320 1040 368 junction
w 512 322 100 0 n#25 hwin.hwin#24.in 496 304 496 320 576 320 eseqs.CarVals.DOL2
w 552 354 100 0 n#23 hwin.hwin#22.in 576 352 576 352 eseqs.CarVals.DOL1
s 1488 -48 100 0 Gemini Telescope Control System
s 368 384 100 0 BUSY
s 272 336 100 0 IDLE
s 1392 1184 100 0 m2MoveBaffle
s 1472 -96 100 0 Simulate movebaffle CAD
[cell use]
use esirs 400 743 100 0 DeployBafflePos
xform 0 608 896
p 512 736 100 1024 0 name:$(prefix)$(I)
use esirs 1072 743 100 0 CentralBafflePos
xform 0 1280 896
p 1184 736 100 1024 0 name:$(prefix)$(I)
use ecad4 -184 -104 100 0 ecad4#43
xform 0 -48 272
p -272 -304 100 0 0 FTVA:STRING
p -272 -336 100 0 0 FTVB:STRING
p -272 -368 100 0 0 FTVC:STRING
p -272 -400 100 0 0 FTVD:STRING
p -272 62 100 0 1 SNAM:tcs$(substring)moveBaffleCAD
p -48 560 100 256 -1 Type:cad
p 208 448 100 0 0 def(OUTA):0.0
p 16 -368 100 0 0 def(OUTB):0.0
p -96 -112 100 1024 1 name:$(prefix)moveBaffle
p 112 368 75 768 -1 pproc(OUTA):PP
p 112 304 75 768 -1 pproc(OUTB):PP
use outhier 1608 328 100 0 VAL
xform 0 1600 368
use outhier 1608 104 100 0 FLNK
xform 0 1600 144
use hwin 408 312 100 0 hwin#22
xform 0 480 352
p 398 280 100 0 0 typ(in):val
p 387 344 100 0 -1 val(in):$(CAR_BUSY)
use hwin 328 264 100 0 hwin#24
xform 0 400 304
p 318 232 100 0 0 typ(in):val
p 307 296 100 0 -1 val(in):$(CAR_IDLE)
use ecars 1208 88 100 0 ecars#14
xform 0 1344 256
p 1184 78 100 0 1 name:$(prefix)moveBaffleC
use eseqs 600 -56 100 0 CarVals
xform 0 736 192
p 672 158 100 0 0 DLY1:0.0e+00
p 656 238 100 0 1 DLY2:5.0
p 608 -82 100 0 1 PV:$(prefix)moveBaffle
p 912 350 100 0 0 def(LNK1):0.0
p 576 384 75 1280 -1 palrm(SELL):NMS
p 544 352 75 1280 -1 pproc(DOL1):NPP
p 544 320 75 1280 -1 pproc(DOL2):NPP
p 896 362 75 0 -1 pproc(LNK1):PP
p 896 330 75 0 -1 pproc(LNK2):PP
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
[comments]
