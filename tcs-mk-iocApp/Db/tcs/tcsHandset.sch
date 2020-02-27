[schematic2]
uniq 36
[tools]
[detail]
w 3064 3723 100 0 n#34 ecalcs.gacqId.INPA 2944 3648 2880 3648 2880 3712 3296 3712 3296 3456 3232 3456 ecalcs.gacqId.VAL
w 1760 1899 100 0 n#29 egenSub.guideOffset.FLNK 1360 1888 2208 1888 2208 2000 junction
w 2212 2931 100 0 n#29 egenSub.poOffset.FLNK 2032 3056 2208 3056 2208 2816 junction
w 2212 2403 100 0 n#29 egenSub.tarOffset.FLNK 1376 3040 1600 3040 1600 2816 2208 2816 2208 2000 2768 2000 embbos.applyBusy.SLNK
w 2672 2043 100 0 n#28 hwin.hwin#27.in 2624 2032 2768 2032 embbos.applyBusy.DOL
s 3440 3936 100 0 $Id: tcsHandset.sch,v 1.4 2006/10/11 21:02:10 gemvx Exp $
s 2688 3776 100 0 adjustements sent by Iraf/GACQ to TCC
s 2704 3808 100 0 container records to handle
[cell use]
use eais 2448 3543 100 0 gacqP
xform 0 2576 3616
p 2544 3520 100 0 1 PREC:4
use eais 2448 3367 100 0 gacqQ
xform 0 2576 3440
p 2544 3344 100 0 1 PREC:4
use eais 2448 3191 100 0 gacqIPA
xform 0 2576 3264
p 2528 3136 100 0 1 PREC:4
use eais 2448 2983 100 0 gacqIAA
xform 0 2576 3056
p 2528 2928 100 0 1 PREC:4
use ecalcs 2944 3175 100 0 gacqId
xform 0 3088 3440
p 3040 3408 100 0 1 CALC:A+1
use hwin 2432 1991 100 0 hwin#27
xform 0 2528 2032
p 2435 2024 100 0 -1 val(in):$(CAR_BUSY)
use embbos 2768 1911 100 0 applyBusy
xform 0 2896 2000
p 2512 1806 100 0 0 OMSL:closed_loop
p 3088 2000 100 0 -1 def(OUT):$(tcs)kernelC.IVAL
p 3024 2000 75 768 -1 pproc(OUT):PP
use egenSub 1072 1831 100 0 guideOffset
xform 0 1216 2256
p 1104 2688 100 0 -1 DESC:Guide handset
p 849 1605 100 0 0 FTA:LONG
p 849 1573 100 0 0 FTC:LONG
p 849 1541 100 0 0 FTD:DOUBLE
p 1184 1808 100 0 1 SNAM:tcsHsGuide
p 1440 2592 100 0 -1 def(OUTA):$(tcs)ak:guide:castep
p 1440 2528 100 0 -1 def(OUTB):$(tcs)ak:guide:cestep
p 1360 2602 75 0 -1 pproc(OUTA):PP
p 1360 2538 75 0 -1 pproc(OUTB):PP
use egenSub 1088 2983 100 0 tarOffset
xform 0 1232 3408
p 1120 3840 100 0 -1 DESC:Target offset handset
p 865 2757 100 0 0 FTA:LONG
p 865 2725 100 0 0 FTC:LONG
p 865 2693 100 0 0 FTD:LONG
p 1200 2960 100 0 1 SNAM:tcsHsTarOffset
use egenSub 1744 2999 100 0 poOffset
xform 0 1888 3424
p 1760 3856 100 0 -1 DESC:Pointing origin handset
p 1521 2773 100 0 0 FTA:LONG
p 1521 2741 100 0 0 FTC:LONG
p 1521 2709 100 0 0 FTD:DOUBLE
p 1856 2976 100 0 1 SNAM:tcsHsPoOffset
use bc200tr 704 1464 -100 0 frame
xform 0 2384 2768
[comments]
