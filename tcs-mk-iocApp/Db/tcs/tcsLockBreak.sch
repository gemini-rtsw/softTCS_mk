[schematic2]
uniq 11
[tools]
[detail]
w 542 763 100 0 n#10 ecalcs.lbcalc.VAL 384 608 480 608 480 752 640 752 eais.eais#9.INP
w 190 907 100 0 n#10 ecalcs.lbcalc.INPA 96 800 0 800 0 896 416 896 416 608 junction
w 1006 747 100 0 FLNK eais.eais#9.FLNK 896 736 1152 736 outhier.FLNK.p
w -18 427 100 0 SLNK inhier.SLNK.P -96 416 96 416 ecalcs.lbcalc.SLNK
[cell use]
use eais 640 647 100 0 eais#9
xform 0 768 720
p 704 784 100 0 1 SCAN:Passive
p 752 640 100 1024 -1 name:$(top)lbwait
p 608 752 75 1280 -1 pproc(INP):CPP
use outhier 1120 695 100 0 FLNK
xform 0 1136 736
use inhier -112 375 100 0 SLNK
xform 0 -96 416
use ecalcs 96 327 100 0 lbcalc
xform 0 240 592
p 208 672 100 0 -1 CALC:A?0:1
use ba200tr -240 -104 -100 0 frame
xform 0 560 520
[comments]
