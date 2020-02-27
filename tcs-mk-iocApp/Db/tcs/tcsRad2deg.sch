[schematic2]
uniq 25
[tools]
[detail]
w 1192 642 100 0 n#24 eaos.ao.OUT 1120 640 1312 640 outhier.OUT.p
w 1192 706 100 0 n#23 eaos.ao.FLNK 1120 704 1312 704 outhier.FLNK.p
w 792 674 100 0 n#22 ecalcs.mult.FLNK 704 736 768 736 768 672 864 672 eaos.ao.SLNK
w 760 706 100 0 n#21 ecalcs.mult.VAL 704 704 864 704 eaos.ao.DOL
w 160 628 100 0 n#16 inhier.SLNK.P 48 624 320 624 320 512 416 512 ecalcs.mult.SLNK
w 136 802 100 0 n#15 inhier.INP.P 48 800 272 800 272 864 416 864 ecalcs.mult.INPB
w 302 900 100 0 n#2 hwin.hwin#1.in 224 896 416 896 ecalcs.mult.INPA
s 992 256 100 0 Converts radians to degrees
s 960 320 100 0 Gemini Telescope Control System
s 896 1136 100 0 $Id: tcsRad2deg.sch,v 1.1.1.1 1998/11/08 00:20:45 epics Exp $
[cell use]
use eaos 888 584 100 0 ao
xform 0 992 672
p 644 858 100 0 0 DESC:Outputs degrees 
p 832 398 100 0 0 EGU:degrees
p 608 654 100 0 0 OMSL:closed_loop
p 608 526 100 0 0 PREC:6
p 1184 606 100 0 -1 def(OUT):$(out)
use ba200tr -112 40 -100 0 frame
xform 0 688 664
use inhier 56 760 100 0 INP
xform 0 48 800
use inhier 56 584 100 0 SLNK
xform 0 48 624
use outhier 1304 600 100 0 OUT
xform 0 1296 640
use outhier 1304 664 100 0 FLNK
xform 0 1296 704
use hwin 48 864 100 0 hwin#1
xform 0 128 896
p 32 926 100 0 -1 val(in):0.0174532925199432958
use ecalcs 440 424 100 0 mult
xform 0 560 688
p 560 654 100 0 -1 CALC:B/A
p 320 1006 100 0 -1 DESC:Convert an angle in radians to degrees
p 128 574 100 0 0 EGU:degrees
p 128 542 100 0 0 PREC:14
[comments]
