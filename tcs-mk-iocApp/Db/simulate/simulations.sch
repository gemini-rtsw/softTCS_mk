[schematic2]
uniq 21
[tools]
[detail]
s 1568 2784 100 0 simulations.sch
s -96 2704 100 0 Top level internal simulation databases
s 1752 584 200 0 Gemini TCS
s 1688 472 100 0 21 Jun 96
s 1456 440 100 0 Chris Mayer
[cell use]
use gems 416 1415 100 0 gems#20
xform 0 672 1568
p 436 1388 100 0 1 seta:prefix $(gems)
p 432 1360 100 0 1 setb:subsys gems:
use gsaoi 416 999 100 0 gsaoi#19
xform 0 672 1152
p 436 972 100 0 -1 seta:prefix $(gsaoi)
p 432 944 100 0 -1 setb:subsys gsaoi:
p 656 976 100 0 -1 setc:snam Gsaoi
p 656 944 100 0 -1 setd:p1 $(gsaoi)odgw1
p 864 976 100 0 -1 sete:p2 $(gsaoi)odgw2
p 864 928 100 0 -1 setf:p3 $(gsaoi)odgw3
p 1104 976 100 0 -1 setg:p4 $(gsaoi)odgw4
use aom 416 631 100 0 aom#18
xform 0 672 784
p 416 624 100 0 1 seta:top $(top)
p 416 576 100 0 1 setb:subsys aom:
p 436 556 100 0 1 setc:snam Aom
p 456 536 100 0 1 setd:p1 $(aom)ngsPr1
p 476 516 100 0 1 sete:p2 $(aom)ngsPr2
p 496 496 100 0 1 setf:p3 $(aom)ngsPr3
p 516 476 100 0 1 setg:prefix $(aom)
use nici -272 631 100 0 nici#17
xform 0 -16 784
p -252 604 100 0 1 seta:top $(top)nici:
p -256 576 100 0 1 setb:subsys nici:
use gp -928 631 100 0 gp#16
xform 0 -672 784
p -908 604 100 0 1 seta:top $(top)
p -912 576 100 0 1 setb:subsys gp:
p -912 544 100 0 1 setc:substring GP
p -624 608 100 0 1 setd:prefix $(gp)
p -624 576 100 0 1 sete:snam Gp
p -912 512 100 0 1 setf:sadtop $(gp)sad:
use gi 1168 1543 100 0 gi#15
xform 0 1248 1704
p 1184 1888 100 0 -1 seta:top $(top)
p 1168 1856 100 0 -1 setb:prefix $(gi)
use tcsOpticsSimulation 1432 1128 100 0 tcsOpticsSimulation#14
xform 0 1680 1552
p 1424 1998 100 0 -1 seta:optics $(top)omSim:
use m1 -248 1000 100 0 m1#13
xform 0 -16 1152
p -240 1326 100 0 -1 seta:top $(top)
p -240 1294 100 0 -1 setb:subsys m1:
p -80 1294 100 0 -1 setc:prefix $(m1)
p -80 1326 100 0 -1 setd:substring M1
p 96 1342 100 0 -1 sete:snam M1
use ao -248 1416 100 0 ao#12
xform 0 -16 1568
p -272 1758 100 0 -1 seta:top $(top)
p -272 1726 100 0 -1 setb:subsys ao:
p -112 1758 100 0 -1 setc:substring AO
p -112 1726 100 0 -1 setd:prefix $(ao)
p 64 1758 100 0 -1 sete:snam Ao
use sky 1432 2040 100 0 sky#11
xform 0 1600 2216
p 1408 2398 100 0 -1 seta:top $(top)
p 1584 2400 100 0 1 setb:tcs $(top)
use ws -904 1000 100 0 ws#10
xform 0 -672 1152
p -928 1342 100 0 -1 seta:top $(top)
p -928 1310 100 0 -1 setb:subsys ws:
use cr -248 2280 100 0 cr#9
xform 0 -16 2432
p -272 2622 100 0 -1 seta:top $(top)
p -272 2590 100 0 -1 setb:subsys cr:
p -112 2622 100 0 -1 setc:substring CR
p -112 2590 100 0 -1 setd:prefix $(cr)
p 80 2622 100 0 -1 sete:snam Cr
use ag -904 1416 100 0 ag#8
xform 0 -672 1568
p -928 1790 100 0 -1 seta:top $(top)
p -928 1758 100 0 -1 setb:subsys ag:
p -768 1790 100 0 -1 setc:substring AG
p -768 1758 100 0 -1 setd:prefix $(ag)
p -592 1790 100 0 -1 sete:snam Ag
p -928 1726 100 0 -1 setf:p1 $(ag)p1:
p -672 1726 100 0 -1 setg:p2 $(ag)p2:
p -592 1758 100 0 -1 seth:oi $(ag)oi:
use m2 -248 1832 100 0 m2#7
xform 0 -16 1984
p -272 2174 100 0 -1 seta:top $(top)
p -272 2142 100 0 -1 setb:subsys m2:
p -112 2174 100 0 -1 setc:substring M2
p -112 2142 100 0 -1 setd:prefix $(m2)
p 80 2190 100 0 -1 sete:snam M2
use ec -904 1832 100 0 ec#6
xform 0 -672 1984
p -928 2222 100 0 -1 seta:top $(top)
p -928 2190 100 0 -1 setb:subsys ec:
p -928 2158 100 0 -1 setc:snam Ec
p -784 2222 100 0 -1 setd:prefix $(ec)
p -784 2190 100 0 -1 sete:substring EC
use bc200tr -1152 312 -100 0 frame
xform 0 528 1616
use time 1160 2024 100 0 time#5
xform 0 1232 2288
p 1136 2574 100 0 -1 seta:top $(top)
p 1136 2542 100 0 -1 setb:subsys sim:
use mc -904 2280 100 0 mc#3
xform 0 -672 2432
p -896 2638 100 0 -1 seta:top $(top)
p -896 2606 100 0 -1 setb:subsys mc:
p -736 2606 100 0 -1 setc:prefix $(mc)
p -912 2574 100 0 -1 setd:substring MC
p -736 2638 100 0 -1 sete:snam Mc
[comments]
