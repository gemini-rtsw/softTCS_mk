[schematic2]
uniq 55
[tools]
[detail]
w 60 818 100 0 n#54 inhier.ICID.P -200 816 368 816 368 864 512 864 ecars.car.ICID
w 116 1012 100 0 sc inhier.ISTA.P -208 1008 464 1008 464 896 512 896 ecars.car.IVAL
w 402 660 100 0 sc elongouts.st2.OUT 320 368 400 368 400 928 junction
w 396 932 100 0 sc elongouts.st1.OUT 320 896 352 896 352 928 464 928 junction
w 40 434 100 0 n#52 hwin.hwin#51.in 64 432 64 432 elongouts.st2.DOL
w 40 962 100 0 n#50 hwin.hwin#49.in 64 960 64 960 elongouts.st1.DOL
w 436 416 100 0 n#48 inhier.IMSS.P -192 -48 432 -48 432 832 512 832 ecars.car.IMSS
w 352 82 100 0 n#48 estringouts.ms2.OUT 320 80 432 80 junction
w 352 626 100 0 n#48 estringouts.ms1.OUT 320 624 432 624 junction
w 928 674 100 0 n#46 ecars.car.FLNK 832 672 1072 672 outhier.FLNK.p
w 128 212 100 0 n#40 estringouts.ms2.FLNK 320 112 320 208 -16 208 -16 400 64 400 elongouts.st2.SLNK
w 144 770 100 0 n#34 estringouts.ms1.FLNK 320 656 368 656 368 768 -32 768 -32 928 64 928 elongouts.st1.SLNK
w -138 162 100 0 n#20 inhier.CLEAR.P -192 160 -48 160 -48 96 64 96 estringouts.ms2.SLNK
w 928 898 100 0 n#17 ecars.car.VAL 832 896 1072 896 outhier.VAL.p
w 944 770 100 0 n#16 ecars.car.OMSS 832 832 864 832 864 768 1072 768 outhier.OMSS.p
w -138 706 100 0 n#9 inhier.START.P -192 704 -48 704 -48 640 64 640 estringouts.ms1.SLNK
s 1840 1712 100 0 tcscar.sch
s 1912 -600 100 0 21 Jun 96
s 1976 -488 200 0 Gemini TCS
s 224 1168 500 0 tcscar
[cell use]
use inhier -192 776 100 0 ICID
xform 0 -200 816
use inhier -184 120 100 0 CLEAR
xform 0 -192 160
use inhier -184 -88 100 0 IMSS
xform 0 -192 -48
use inhier -200 968 100 0 ISTA
xform 0 -208 1008
use inhier -184 664 100 0 START
xform 0 -192 704
use bc200tr -928 -760 -100 0 frame
xform 0 752 544
use hwin -104 920 100 0 hwin#49
xform 0 -32 960
p -125 952 100 0 -1 val(in):$(CAR_BUSY)
use hwin -104 392 100 0 hwin#51
xform 0 -32 432
p -125 424 100 0 -1 val(in):$(CAR_IDLE)
use ecars 536 616 100 0 car
xform 0 672 784
p 576 958 100 0 1 name:$(prefix)$(car)
use elongouts 88 312 100 0 st2
xform 0 192 400
p 320 368 75 768 -1 pproc(OUT):PP
p -96 -20 100 0 0 PV:$(prefix)$(car):
p -96 318 100 0 0 OMSL:closed_loop
use elongouts 88 840 100 0 st1
xform 0 192 928
p -96 846 100 0 0 OMSL:closed_loop
p 352 896 75 768 -1 palrm(OUT):NMS
p 320 896 75 768 -1 pproc(OUT):PP
p -96 508 100 0 0 PV:$(prefix)$(car):
use estringouts 88 24 100 0 ms2
xform 0 192 96
p 0 62 100 0 0 VAL:-
p 91 136 100 0 0 DESC:Default string when Clear is invoked
p 32 -576 100 0 0 PV:$(prefix)$(car):
use estringouts 88 568 100 0 ms1
xform 0 192 640
p 0 606 100 0 0 VAL:Command active
p 91 680 100 0 0 DESC:Default string when Apply is invoked
p 32 75 100 0 0 typ(OUT):path
p 32 74 100 0 0 def(OUT):0.000000000000000e+00
p 32 108 100 0 0 typ(DOL):path
p 32 -32 100 0 0 PV:$(prefix)$(car):
use outhier 1064 856 100 0 VAL
xform 0 1056 896
use outhier 1064 728 100 0 OMSS
xform 0 1056 768
use outhier 1064 632 100 0 FLNK
xform 0 1056 672
[comments]
