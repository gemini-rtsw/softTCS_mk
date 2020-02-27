[schematic2]
uniq 13
[tools]
[detail]
w -2614 604 100 0 n#1 genericcad.genericcad#48.FLNK -2630 601 -2598 601 -2598 584 -2024 584 junction
w -2135 1100 100 0 n#1 genericcad.genericcad#96.FLNK -2246 1097 -2024 1097 -2024 -224 -1896 -224 egenSub.simStop.SLNK
w -2616 635 100 0 n#2 genericcad.genericcad#48.VLNK -2632 632 -2600 632 -2600 616 -1272 616 junction
w -960 155 100 0 n#2 genericcad.genericcad#33.VLNK -968 152 -952 152 -952 488 junction
w -1392 811 100 0 n#2 genericcad.genericcad#23.VLNK -1512 808 -1272 808 -1272 488 -792 488 esels.simCommonSel.SLNK
w -1760 1131 100 0 n#2 genericcad.genericcad#96.VLNK -2248 1128 -1272 1128 -1272 808 junction
w -1512 323 100 0 n#3 egenSub.simStop.OUTC -1608 320 -1416 320 outhier.c#105.p
w -1512 387 100 0 n#4 egenSub.simStop.OUTB -1608 384 -1416 384 outhier.c#102.p
w -1624 1051 100 0 n#5 genericcad.genericcad#96.VAL -2248 1048 -1000 1048 -1000 680 -792 680 esels.simCommonSel.INPG
w -1512 451 100 0 n#6 egenSub.simStop.OUTA -1608 448 -1416 448 outhier.c#79.p
w -464 731 100 0 n#7 esels.simCommonSel.FLNK -504 728 -424 728 -424 792 -344 792 outhier.FLNK.p
w -424 699 100 0 n#8 esels.simCommonSel.VAL -504 696 -344 696 outhier.VAL.p
w -944 75 100 0 n#9 genericcad.genericcad#33.VAL -968 72 -920 72 -920 712 -792 712 esels.simCommonSel.INPF
w -2256 555 100 0 n#10 genericcad.genericcad#48.VAL -2632 552 -1880 552 -1880 664 -1032 664 -1032 808 -792 808 esels.simCommonSel.INPC
w -1288 731 100 0 n#11 genericcad.genericcad#23.VAL -1512 728 -1064 728 -1064 840 -792 840 esels.simCommonSel.INPB
w -960 -509 100 0 n#12 esels.inPosSel.VAL -992 -512 -928 -512 -928 -432 -792 -432 aomSimStandard.aomSimStandard#110.INPOS
s -592 -960 100 0 Sciences Ltd.
s -592 -928 100 0 Observatory
s -592 -896 100 0 Copyright
s -576 1296 100 0 $Id: aomSystem.sch,v 1.2 2010/12/21 11:14:45 cjm Exp $
[cell use]
use bc200tr -3168 -1176 -100 0 frame
xform 0 -1488 128
use aomSimStandard -792 -617 100 0 aomSimStandard#110
xform 0 -680 -496
use esels -824 424 100 0 simCommonSel
xform 0 -648 680
p -1015 285 100 0 0 PV:$(top)$(subsys)
p -696 710 100 0 -1 SELM:High Signal
use outhier -1424 280 100 0 c#105
xform 0 -1432 320
use outhier -1424 344 100 0 c#102
xform 0 -1432 384
use outhier -344 648 160 0 VAL
xform 0 -360 696
use outhier -352 752 100 0 FLNK
xform 0 -360 792
use outhier -1424 408 100 0 c#79
xform 0 -1432 448
use genericcad -1232 16 100 0 genericcad#33
xform 0 -1104 112
p -1256 -24 100 0 0 seta:prefix $(top)$(subsys)
p -1256 262 100 0 -1 setb:command debug
p -1256 230 100 0 -1 setc:delay 0.1
p -1256 198 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -1256 -56 100 0 0 sete:outa 0.0
use genericcad -1776 672 100 0 genericcad#23
xform 0 -1648 768
p -1720 934 100 0 0 seta:prefix $(top)$(subsys)
p -1720 902 100 0 -1 setb:command test
p -1720 870 100 0 -1 setc:delay 3.0
p -1720 838 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -1720 806 100 0 0 sete:outa 0.0
use genericcad -2896 496 100 0 genericcad#48
xform 0 -2768 592
p -2840 758 100 0 0 seta:prefix $(top)$(subsys)
p -2904 774 100 0 -1 setb:command reboot
p -2904 742 100 0 -1 setc:delay 0.3
p -2904 710 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2904 678 100 0 -1 sete:outa 0.0
use genericcad -2512 992 100 0 genericcad#96
xform 0 -2384 1088
p -2456 1254 100 0 0 seta:prefix $(top)$(subsys)
p -2520 1270 100 0 -1 setb:command init
p -2520 1238 100 0 -1 setc:delay 5.0
p -2520 1206 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2520 1174 100 0 -1 sete:outa 0.0
use egenSub -1872 -312 100 0 simStop
xform 0 -1752 112
p -2119 -539 100 0 0 FTVA:STRING
p -2119 -539 100 0 0 FTVB:STRING
p -2119 -571 100 0 0 FTVC:STRING
p -2119 -603 100 0 0 FTVD:STRING
p -1816 -98 100 0 0 INAM:tcsSimNullInit
p -2119 -443 100 0 0 PV:$(top)$(subsys)
p -1832 -98 100 0 -1 SNAM:tcs$(snam)Stop
p -1592 494 100 0 -1 def(OUTA):$(p1)followS.VAL
p -1592 414 100 0 -1 def(OUTB):$(p2)followS.VAL
p -1592 350 100 0 -1 def(OUTC):$(p3)followS.VAL
p -1608 458 75 0 -1 pproc(OUTA):PP
p -1608 394 75 0 -1 pproc(OUTB):PP
p -1608 330 75 0 -1 pproc(OUTC):PP
use esels -1209 -804 100 0 inPosSel
xform 0 -1136 -528
p -1105 -720 100 0 1 SCAN:5 second
p -1105 -688 100 0 1 SELM:Low Signal
p -1611 -336 100 0 -1 def(INPA):$(aom)ngsPr1InPosition
p -1168 -800 100 1024 0 name:$(aom)$(I)
p -1609 -375 100 0 -1 def(INPB):$(aom)ngsPr2InPosition
p -1611 -416 100 0 -1 def(INPC):$(aom)ngsPr3InPosition
[comments]
