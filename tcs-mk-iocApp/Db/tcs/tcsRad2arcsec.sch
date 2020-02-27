[schematic2]
uniq 26
[tools]
[detail]
w 1200 610 100 0 n#25 eaos.ao.OUT 1136 608 1312 608 outhier.OUT.p
w 1240 706 100 0 n#24 eaos.ao.FLNK 1136 672 1216 672 1216 704 1312 704 outhier.FLNK.p
w 808 642 100 0 n#23 ecalcs.mult.FLNK 704 704 784 704 784 640 880 640 eaos.ao.SLNK
w 768 674 100 0 n#22 ecalcs.mult.VAL 704 672 880 672 eaos.ao.DOL
w 160 596 100 0 n#16 inhier.SLNK.P 48 592 320 592 320 480 416 480 ecalcs.mult.SLNK
w 136 770 100 0 n#15 inhier.INP.P 48 768 272 768 272 832 416 832 ecalcs.mult.INPB
w 302 868 100 0 n#2 hwin.hwin#1.in 224 864 416 864 ecalcs.mult.INPA
s 960 240 100 0 Converts radians to arcsecs
s 960 304 100 0 Gemini Telescope Control System
s 832 1120 100 0 $Id4
[cell use]
use eaos 904 552 100 0 ao
xform 0 1008 640
p 660 826 100 0 0 DESC:Outputs result of calculation
p 848 366 100 0 0 EGU:arcsec
p 624 622 100 0 0 OMSL:closed_loop
p 624 494 100 0 0 PREC:3
p 1184 574 100 0 -1 def(OUT):$(out)
use ba200tr -128 24 -100 0 frame
xform 0 672 648
use inhier 56 552 100 0 SLNK
xform 0 48 592
use inhier 56 728 100 0 INP
xform 0 48 768
use outhier 1304 664 100 0 FLNK
xform 0 1296 704
use outhier 1304 568 100 0 OUT
xform 0 1296 608
use hwin 56 824 100 0 hwin#1
xform 0 128 864
p 32 894 100 0 -1 val(in):4.84813681109536e-6
use ecalcs 440 392 100 0 mult
xform 0 560 656
p 544 622 100 0 -1 CALC:B/A
p 128 542 100 0 0 EGU:arcsecs
p 128 510 100 0 0 PREC:14
[comments]
