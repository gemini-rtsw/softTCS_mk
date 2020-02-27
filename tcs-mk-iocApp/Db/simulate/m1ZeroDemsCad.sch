[schematic2]
uniq 52
[tools]
[detail]
w 856 1010 100 0 n#50 inhier.IVAL.P 736 1008 1024 1008 1024 720 junction
w 1026 560 100 0 n#50 elongouts.CarVals.OUT 928 352 1024 352 1024 720 1184 720 ecars.ecars#14.IVAL
w 296 338 100 0 n#49 ecad4.ecad4#43.STLK 112 336 528 336 528 384 672 384 elongouts.CarVals.SLNK
w 592 418 100 0 n#48 hwin.hwin#22.in 560 416 672 416 elongouts.CarVals.DOL
w 1536 722 100 0 n#42 ecars.ecars#14.VAL 1504 720 1616 720 outhier.VAL.p
w 1536 498 100 0 n#40 ecars.ecars#14.FLNK 1504 496 1616 496 outhier.FLNK.p
s 1520 -128 100 0 specified as parameter
s 1472 -96 100 0 General simulated CAD4 with delay
s 320 448 100 0 BUSY
s 1488 -48 100 0 Gemini Telescope Control System
s 1216 1184 100 0 $Id: m1ZeroDemsCad.sch,v 1.1.1.1 1998/11/08 00:20:22 epics Exp $
[cell use]
use inhier 744 968 100 0 IVAL
xform 0 736 1008
use elongouts 696 296 100 0 CarVals
xform 0 800 384
p 512 302 100 0 0 OMSL:closed_loop
p 688 494 100 0 -1 DESC:Drives CAR to busy
p 784 288 100 1024 0 name:$(prefix)$(cadname)$(I)
p 928 352 75 768 -1 pproc(OUT):PP
use outhier 1608 456 100 0 FLNK
xform 0 1600 496
use outhier 1608 680 100 0 VAL
xform 0 1600 720
use ecad4 -184 248 100 0 ecad4#43
xform 0 -48 624
p -272 414 100 0 1 SNAM:tcs$(substring)$(cadname)CAD
p -96 240 100 1024 1 name:$(prefix)$(cadname)
p -48 912 100 256 -1 Type:cad
p -272 48 100 0 0 FTVA:$(ftva)
p -272 16 100 0 0 FTVB:$(ftvb)
p -272 -16 100 0 0 FTVC:$(ftvc)
p -272 -48 100 0 0 FTVD:$(ftvd)
use hwin 392 376 100 0 hwin#22
xform 0 464 416
p 371 408 100 0 -1 val(in):$(CAR_BUSY)
p 382 344 100 0 0 typ(in):val
use ecars 1208 440 100 0 ecars#14
xform 0 1344 608
p 1184 430 100 0 1 name:$(prefix)$(cadname)C
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
[comments]
