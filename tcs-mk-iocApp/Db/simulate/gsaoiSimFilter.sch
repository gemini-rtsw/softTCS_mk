[schematic2]
uniq 15
[tools]
[detail]
w 2664 -470 100 0 n#1 ecars.ecars#20.VAL 2592 -472 2784 -472 outhier.VAL.p
w 2672 -694 100 0 n#2 ecars.ecars#20.FLNK 2592 -696 2800 -696 outhier.FLNK.p
w 1514 -414 100 0 n#3 hwin.hwin#15.in 1504 -424 1624 -424 1624 -472 1728 -472 eseqs.eseqs#102.DOL1
w 1514 -510 100 0 n#4 hwin.hwin#16.in 1504 -520 1608 -520 1608 -504 1728 -504 eseqs.eseqs#102.DOL2
w 2058 -462 100 0 n#5 eseqs.eseqs#102.LNK1 2048 -472 2272 -472 ecars.ecars#20.IVAL
w 2058 -494 100 0 n#5 eseqs.eseqs#102.LNK2 2048 -504 2144 -504 2144 -472 junction
w 1114 -1038 100 0 n#6 ecad8.ecad8#11.STLK 1104 -1048 1568 -1048 1568 -792 1728 -792 eseqs.eseqs#102.SLNK
w 114 -446 100 0 n#7 embbos.embbos#33.OUT 264 -448 624 -448 624 -376 784 -376 ecad8.ecad8#11.A
w 114 -478 100 0 n#8 embbos.embbos#33.VAL 264 -480 504 -480 504 -40 1272 -40 1272 -560 1632 -560 1632 -536 1728 -536 eseqs.eseqs#102.DOL3
w 2058 -526 100 0 n#9 eseqs.eseqs#102.LNK3 2048 -536 2112 -536 2112 232 296 232 296 648 288 648 288 656 456 656 elutouts.elutouts#123.VAL
w 722 698 100 0 n#10 elutouts.elutouts#123.VALA 712 688 808 688 808 696 864 696 outhier.Fname.p
w 722 634 100 0 n#11 elutouts.elutouts#123.VALB 712 624 808 624 808 616 864 616 outhier.Zoff.p
w 722 570 100 0 n#12 elutouts.elutouts#123.VALC 712 560 792 560 792 544 864 544 outhier.Xoff.p
w 722 506 100 0 n#13 elutouts.elutouts#123.VALD 712 496 800 496 800 464 864 464 outhier.Yoff.p
w 722 762 100 0 n#14 elutouts.elutouts#123.FLNK 712 752 856 752 outhier.LUTFLNK.p
s 2416 -1120 100 0 Gemini Telescope Control System
s 2416 -1184 100 0 GSAOI Simulated filter handling
s 1216 1184 100 0 $Id:
[cell use]
use bc200tr -384 -1376 100 0 bc200tr#21
xform 0 1296 -96
use outhier 2776 -512 100 0 VAL
xform 0 2768 -472
use ecars 2296 -752 100 0 ecars#20
xform 0 2432 -584
p 2380 -760 100 1024 1 name:$(prefix)$(filtname)SelC
use hwin 1336 -560 100 0 hwin#16
xform 0 1408 -520
p 1315 -528 100 0 -1 val(in):$(CAR_IDLE)
use hwin 1336 -464 100 0 hwin#15
xform 0 1408 -424
p 1315 -432 100 0 -1 val(in):$(CAR_BUSY)
use outhier 2792 -736 100 0 FLNK
xform 0 2784 -696
use ecad8 808 -1136 100 0 ecad8#11
xform 0 944 -632
p 805 -1176 100 0 1 SNAM:tcsGsaoiGenericCAD
p 800 -1210 100 0 1 name:$(prefix)$(filtname)Sel
p 880 16 100 0 0 FTVA:$(ftva)
p 880 -16 100 0 0 FTVB:$(ftvb)
p 880 -48 100 0 0 FTVC:$(ftvc)
p 880 -80 100 0 0 FTVD:$(ftvd)
p 880 112 100 0 0 PREC:5
use embbos 8 -512 100 0 embbos#33
xform 0 136 -448
p 68 -545 100 1024 1 name:$(prefix)$(filtname)Menu
p 168 -482 100 0 0 FRST:FOUR
p -24 -482 100 0 0 FRVL:4
p 168 -514 100 0 0 FVST:FIVE
p -24 -514 100 0 0 FVVL:5
p 168 -450 100 0 0 THST:THREE
p -24 -450 100 0 0 THVL:3
p 168 -418 100 0 0 TWST:TWO
p -24 -418 100 0 0 TWVL:2
p 168 -354 100 0 0 ZRST:ZERO
p 168 -386 100 0 0 ONST:ONE
p -24 -386 100 0 0 ONVL:1
p -24 -610 100 0 0 EIVL:8
p -24 -706 100 0 0 ELVL:11
p -24 -834 100 0 0 FFVL:15
p -24 -802 100 0 0 FTVL:14
p -24 -642 100 0 0 NIVL:9
p -24 -578 100 0 0 SVVL:7
p -24 -546 100 0 0 SXVL:6
p -24 -674 100 0 0 TEVL:10
p -24 -770 100 0 0 TTVL:13
p -24 -738 100 0 0 TVVL:12
p 272 -440 75 768 -1 pproc(OUT):NPP
p 3382 -1268 100 0 1 def(OUT):$(prefix)$(filtname)MenuStrout
use eseqs 1728 -856 100 0 eseqs#102
xform 0 1888 -632
p 2058 -467 75 1024 -1 pproc(LNK1):PP
p 2056 -496 75 1024 -1 pproc(LNK2):PP
p 2056 -528 75 1024 -1 pproc(LNK3):PP
p 1858 -558 100 0 1 DLY1:0.0
p 1856 -580 100 0 1 DLY2:3.0
p 1859 -604 100 0 1 DLY3:0.0
p 1840 -888 100 1024 1 name:$(prefix)$(filtname)CadSeq
use elutouts 456 400 100 0 elutouts#123
xform 0 584 592
p 568 368 100 1024 1 name:$(prefix)$(filtname)Lutout
p 1408 -268 100 0 0 FTVA:STRING
p 1428 -288 100 0 0 FTVB:DOUBLE
p 1448 -308 100 0 0 FTVC:DOUBLE
p 1468 -328 100 0 0 FTVD:DOUBLE
p 1488 -348 100 0 0 FDIR:./data
p 1508 -368 100 0 0 FNAM:gsaoi$(filtname).lut
p 1528 -388 100 0 0 PREC:0
use outhier 832 680 100 0 Fname
xform 0 848 696
use outhier 832 600 100 0 Zoff
xform 0 848 616
use outhier 832 528 100 0 Xoff
xform 0 848 544
use outhier 832 448 100 0 Yoff
xform 0 848 464
use outhier 867 747 100 0 LUTFLNK
xform 0 840 752
[comments]
