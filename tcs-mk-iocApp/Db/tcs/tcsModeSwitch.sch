[schematic2]
uniq 23
[tools]
[detail]
w 1016 2243 100 0 n#22 hwin.hwin#21.in 960 2232 1120 2232 ecalcouts.ecalcouts#19.INPA
w 1560 2115 100 0 n#20 ecalcouts.ecalcouts#19.OUT 1440 2104 1728 2104 egenSub.egenSub#0.J
w 1640 2531 100 0 n#18 hwin.hwin#15.in 1600 2520 1728 2520 egenSub.egenSub#0.INPC
w 1640 2595 100 0 n#17 hwin.hwin#14.in 1600 2584 1728 2584 egenSub.egenSub#0.INPB
w 1636 2659 100 0 n#16 hwin.hwin#13.in 1592 2648 1728 2648 egenSub.egenSub#0.INPA
w 2088 2531 100 0 n#12 egenSub.egenSub#0.OUTC 2016 2520 2208 2520 hwout.hwout#9.outp
w 2088 2595 100 0 n#11 egenSub.egenSub#0.OUTB 2016 2584 2208 2584 hwout.hwout#8.outp
w 2088 2659 100 0 n#10 egenSub.egenSub#0.OUTA 2016 2648 2208 2648 hwout.hwout#7.outp
[cell use]
use hwin 1408 2479 100 0 hwin#15
xform 0 1504 2520
p 1104 2512 100 0 -1 val(in):$(top)humidityCurrent
use hwin 1408 2543 100 0 hwin#14
xform 0 1504 2584
p 1104 2576 100 0 -1 val(in):$(top)pressureCurrent
use hwin 1400 2607 100 0 hwin#13
xform 0 1496 2648
p 1096 2640 100 0 -1 val(in):$(top)temperatureCurrent
use hwin 768 2191 100 0 hwin#21
xform 0 864 2232
p 688 2264 100 0 -1 val(in):$(top)ak:envmode.RVAL .CP .NMS
use ecalcouts 1120 2047 100 0 ecalcouts#19
xform 0 1280 2168
p 1192 2080 100 0 -1 CALC:A
p 1208 2312 100 0 1 OOPT:Transition To Non-zero
p 1184 2048 100 0 -1 name:$(top)waitLocal
p 1072 2240 75 0 -1 pproc(INPA):NPP
p 1440 2120 75 0 -1 pproc(OUT):PP
use hwout 2208 2479 100 0 hwout#9
xform 0 2304 2520
p 2416 2512 100 0 -1 val(outp):$(top)currentRH .PP .NMS
use hwout 2208 2543 100 0 hwout#8
xform 0 2304 2584
p 2416 2576 100 0 -1 val(outp):$(top)currentAirPressure .PP .NMS
use hwout 2208 2607 100 0 hwout#7
xform 0 2304 2648
p 2416 2640 100 0 -1 val(outp):$(top)currentExternalTemp .PP .NMS
use egenSub 1728 1887 100 0 egenSub#0
xform 0 1872 2312
p 1808 2640 100 0 1 FTA:DOUBLE
p 1808 2600 100 0 1 FTB:DOUBLE
p 1808 2560 100 0 1 FTC:DOUBLE
p 1808 2512 100 0 1 FTVA:DOUBLE
p 1808 2472 100 0 1 FTVB:DOUBLE
p 1808 2432 100 0 1 FTVC:DOUBLE
p 1776 2744 100 0 1 SNAM:tcsLocalRemote
p 1840 1880 100 1024 -1 name:$(top)localRemote
use bd200tr 336 -400 -100 0 frame
xform 0 2976 1304
[comments]
