[schematic2]
uniq 20
[tools]
[detail]
w 1000 754 100 0 n#19 ecalcs.mult.FLNK 880 704 944 704 944 752 1104 752 outhier.FLNK.p
w 968 674 100 0 n#18 ecalcs.mult.VAL 880 672 1104 672 outhier.VAL.p
w 336 596 100 0 n#16 inhier.SLNK.P 224 592 496 592 496 480 592 480 ecalcs.mult.SLNK
w 312 770 100 0 n#15 inhier.INP.P 224 768 448 768 448 832 592 832 ecalcs.mult.INPB
w 478 868 100 0 n#2 hwin.hwin#1.in 400 864 592 864 ecalcs.mult.INPA
s 992 256 100 0 Converts degrees to radians
s 960 320 100 0 Gemini Telescope Control System
s 896 1136 100 0 $Id: tcsDeg2rad.sch,v 1.1.1.1 1998/11/08 00:20:34 epics Exp $
[cell use]
use ba200tr -112 40 -100 0 frame
xform 0 688 664
use inhier 232 728 100 0 INP
xform 0 224 768
use inhier 232 552 100 0 SLNK
xform 0 224 592
use outhier 1096 632 100 0 VAL
xform 0 1088 672
use outhier 1096 712 100 0 FLNK
xform 0 1088 752
use hwin 224 832 100 0 hwin#1
xform 0 304 864
p 208 894 100 0 -1 val(in):0.0174532925199432958
use ecalcs 616 392 100 0 mult
xform 0 736 656
p 736 622 100 0 -1 CALC:A*B
p 496 974 100 0 -1 DESC:Convert an angle in degrees to radians
p 304 510 100 0 0 PREC:14
[comments]
