[schematic2]
uniq 44
[tools]
[detail]
w 1536 722 100 0 n#42 ecars.ecars#14.VAL 1504 720 1616 720 outhier.VAL.p
w 1536 498 100 0 n#40 ecars.ecars#14.FLNK 1504 496 1616 496 outhier.FLNK.p
w 272 338 100 0 n#38 ecad4.ecad4#43.STLK 112 336 480 336 480 384 576 384 eseqs.Seq.SLNK
w 944 674 100 0 n#26 eseqs.Seq.LNK2 896 672 1040 672 1040 720 junction
w 1032 722 100 0 n#26 eseqs.Seq.LNK1 896 704 928 704 928 720 1184 720 ecars.ecars#14.IVAL
w 512 674 100 0 n#25 hwin.hwin#24.in 496 656 496 672 576 672 eseqs.Seq.DOL2
w 552 706 100 0 n#23 hwin.hwin#22.in 576 704 576 704 eseqs.Seq.DOL1
s 1216 1184 100 0 $Id: mechSimCad4.sch,v 1.2 2001/09/10 14:59:24 cjm Exp $
s 1520 -128 100 0 specified as parameter
s 1472 -96 100 0 General simulated CAD4 with delay
s 272 688 100 0 IDLE
s 368 736 100 0 BUSY
s 1488 -48 100 0 Gemini Telescope Control System
[cell use]
use ecad4 -184 248 100 0 ecad4#43
xform 0 -48 624
p -272 48 100 0 0 FTVA:$(ftva)
p -272 16 100 0 0 FTVB:$(ftvb)
p -272 -16 100 0 0 FTVC:$(ftvc)
p -272 -48 100 0 0 FTVD:$(ftvd)
p -272 414 100 0 1 SNAM:tcs$(substring)$(cadname)CAD
p -48 912 100 256 -1 Type:cad
p -96 240 100 1024 1 name:$(prefix)$(cadname)
use outhier 1608 456 100 0 FLNK
xform 0 1600 496
use outhier 1608 680 100 0 VAL
xform 0 1600 720
use hwin 328 616 100 0 hwin#24
xform 0 400 656
p 318 584 100 0 0 typ(in):val
p 307 648 100 0 -1 val(in):$(CAR_IDLE)
use hwin 408 664 100 0 hwin#22
xform 0 480 704
p 398 632 100 0 0 typ(in):val
p 387 696 100 0 -1 val(in):$(CAR_BUSY)
use ecars 1208 440 100 0 ecars#14
xform 0 1344 608
p 1184 430 100 0 1 name:$(prefix)$(cadname)C
use eseqs 600 296 100 0 Seq
xform 0 736 544
p 672 510 100 0 0 DLY1:0.0e+00
p 656 590 100 0 1 DLY2:$(delay)
p 608 270 100 0 1 PV:$(prefix)$(cadname)
p 912 702 100 0 0 def(LNK1):0.0
p 576 736 75 1280 -1 palrm(SELL):NMS
p 544 704 75 1280 -1 pproc(DOL1):NPP
p 544 672 75 1280 -1 pproc(DOL2):NPP
p 896 714 75 0 -1 pproc(LNK1):PP
p 896 682 75 0 -1 pproc(LNK2):PP
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
[comments]
