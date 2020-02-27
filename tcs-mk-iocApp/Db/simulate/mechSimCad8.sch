[schematic2]
uniq 45
[tools]
[detail]
w 272 123 100 0 n#38 ecad8.ecad8#44.SPLK 112 112 480 112 480 144 junction
w 272 146 100 0 n#38 ecad8.ecad8#44.STLK 112 144 480 144 480 192 576 192 eseqs.D.SLNK
w 1536 530 100 0 n#42 ecars.ecars#14.VAL 1504 528 1616 528 outhier.VAL.p
w 1536 306 100 0 n#40 ecars.ecars#14.FLNK 1504 304 1616 304 outhier.FLNK.p
w 944 482 100 0 n#26 eseqs.D.LNK2 896 480 1040 480 1040 528 junction
w 1032 530 100 0 n#26 eseqs.D.LNK1 896 512 928 512 928 528 1184 528 ecars.ecars#14.IVAL
w 512 482 100 0 n#25 hwin.hwin#24.in 496 464 496 480 576 480 eseqs.D.DOL2
w 552 514 100 0 n#23 hwin.hwin#22.in 576 512 576 512 eseqs.D.DOL1
s 1520 -128 100 0 specified as parameter
s 1472 -96 100 0 Generate simulated CAD8 with delay
s 1216 1184 100 0 $Id: mechSimCad8.sch,v 1.4 2003/10/17 16:31:10 gemvx Exp $
s 272 496 100 0 IDLE
s 368 544 100 0 BUSY
s 1488 -48 100 0 Gemini Telescope Control System
[cell use]
use ecad8 -184 56 100 0 ecad8#44
xform 0 -48 560
p -112 752 100 0 0 FTVA:$(ftva)
p -112 720 100 0 0 FTVB:$(ftvb)
p -112 688 100 0 0 FTVC:$(ftvc)
p -112 656 100 0 0 FTVD:$(ftvd)
p -112 624 100 0 0 FTVE:$(ftve)
p -240 16 100 0 1 SNAM:tcs$(substring)$(cadname)CAD
p -96 48 100 1024 1 name:$(prefix)$(cadname)
use outhier 1608 264 100 0 FLNK
xform 0 1600 304
use outhier 1608 488 100 0 VAL
xform 0 1600 528
use hwin 328 424 100 0 hwin#24
xform 0 400 464
p 318 392 100 0 0 typ(in):val
p 307 456 100 0 -1 val(in):$(CAR_IDLE)
use hwin 408 472 100 0 hwin#22
xform 0 480 512
p 398 440 100 0 0 typ(in):val
p 387 504 100 0 -1 val(in):$(CAR_BUSY)
use ecars 1208 248 100 0 ecars#14
xform 0 1344 416
p 1184 238 100 0 1 name:$(prefix)$(cadname)C
use eseqs 600 104 100 0 D
xform 0 736 352
p 672 318 100 0 0 DLY1:0.0e+00
p 656 398 100 0 1 DLY2:$(delay)
p 608 78 100 0 1 PV:$(prefix)$(cadname)
p 912 510 100 0 0 def(LNK1):0.0
p 576 544 75 1280 -1 palrm(SELL):NMS
p 544 512 75 1280 -1 pproc(DOL1):NPP
p 544 480 75 1280 -1 pproc(DOL2):NPP
p 896 522 75 0 -1 pproc(LNK1):PP
p 896 490 75 0 -1 pproc(LNK2):PP
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
[comments]
