[schematic2]
uniq 56
[tools]
[detail]
w 216 418 100 0 n#55 ecad4.ecad4#43.VALC 112 416 368 416 368 656 576 656 eseqs.CarVals.DOL4
w 432 690 100 0 n#54 ecad4.ecad4#43.VALB 112 480 336 480 336 688 576 688 eseqs.CarVals.DOL3
w 1288 130 100 0 n#53 eseqs.CarVals.LNK4 896 656 1008 656 1008 128 1616 128 outhier.WEST.p
w 1304 290 100 0 n#52 eseqs.CarVals.LNK3 896 688 1040 688 1040 288 1616 288 outhier.EAST.p
w 496 754 100 0 n#47 hwin.hwin#22.in 432 848 464 848 464 752 576 752 eseqs.CarVals.DOL1
w 480 722 100 0 n#46 hwin.hwin#24.in 432 720 576 720 eseqs.CarVals.DOL2
w 248 130 100 0 n#44 ecad4.ecad4#43.STLK 112 128 432 128 432 432 576 432 eseqs.CarVals.SLNK
w 1536 770 100 0 n#42 ecars.ecars#14.VAL 1504 768 1616 768 outhier.VAL.p
w 1536 546 100 0 n#40 ecars.ecars#14.FLNK 1504 544 1616 544 outhier.FLNK.p
w 944 722 100 0 n#26 eseqs.CarVals.LNK2 896 720 1040 720 1040 768 junction
w 1032 770 100 0 n#26 eseqs.CarVals.LNK1 896 752 928 752 928 768 1184 768 ecars.ecars#14.IVAL
s 208 752 100 0 IDLE
s 208 880 100 0 BUSY
s 1488 -48 100 0 Gemini Telescope Control System
s 1216 1184 100 0 $Id: ecMoveVentGates.sch,v 1.1.1.1 1998/11/08 00:20:19 epics Exp $
s 1456 -96 100 0 Implements a simple simulation for
s 1568 -128 100 0 the vent gates
s 160 1120 100 0 This is a very crude simulation for the vent gates. It
s 160 1088 100 0 simply sets the CAR to BUSY then, after delay seconds sets
s 160 1056 100 0 it back to IDLE and makes the demand positions available
s 160 1024 100 0 on the output links. There is no attempt to update
s 160 992 100 0 the position whilst the CAR record is BUSY.
[cell use]
use outhier 1608 504 100 0 FLNK
xform 0 1600 544
use outhier 1608 728 100 0 VAL
xform 0 1600 768
use outhier 1608 248 100 0 EAST
xform 0 1600 288
use outhier 1608 88 100 0 WEST
xform 0 1600 128
use ecad4 -184 40 100 0 ecad4#43
xform 0 -48 416
p -240 -2 100 0 1 SNAM:tcs$(substring)$(cadname)CAD
p -96 32 100 1024 1 name:$(prefix)$(cadname)
p -48 704 100 256 -1 Type:cad
p -96 526 100 0 0 FTVA:STRING
p -96 494 100 0 1 FTVB:DOUBLE
p -96 414 100 0 1 FTVC:DOUBLE
p -272 -256 100 0 0 FTVD:STRING
p -240 814 100 0 -1 DESC:Implements the moveVgates command
p -272 -384 100 0 0 PREC:1
use hwin 264 680 100 0 hwin#24
xform 0 336 720
p 243 712 100 0 -1 val(in):$(CAR_IDLE)
p 254 648 100 0 0 typ(in):val
use hwin 264 808 100 0 hwin#22
xform 0 336 848
p 243 840 100 0 -1 val(in):$(CAR_BUSY)
p 254 776 100 0 0 typ(in):val
use ecars 1208 488 100 0 ecars#14
xform 0 1344 656
p 1184 478 100 0 1 name:$(prefix)$(cadname)C
use eseqs 600 344 100 0 CarVals
xform 0 736 592
p 672 558 100 0 0 DLY1:0.0e+00
p 912 750 100 0 0 def(LNK1):0.0
p 608 318 100 0 1 PV:$(prefix)$(cadname)
p 576 784 75 1280 -1 palrm(SELL):NMS
p 656 638 100 0 1 DLY2:$(delay)
p 544 752 75 1280 -1 pproc(DOL1):NPP
p 544 720 75 1280 -1 pproc(DOL2):NPP
p 896 762 75 0 -1 pproc(LNK1):PP
p 896 730 75 0 -1 pproc(LNK2):PP
p 656 542 100 0 1 DLY3:$(delay)
p 656 510 100 0 1 DLY4:$(delay)
p 912 688 75 1024 -1 pproc(LNK3):PP
p 912 656 75 1024 -1 pproc(LNK4):PP
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
[comments]
