[schematic2]
uniq 11
[tools]
[detail]
w -1574 258 100 0 n#1 tcsApply.tcsApply#544.ELLIMIT -2368 128 -2432 128 -2432 256 -656 256 -656 734 junction
w -652 850 100 0 n#1 tcsLimits.tcsLimits#670.ELLIMIT -690 734 -656 734 -656 976 -500 976 tcsDrives.tcsDrives#671.ELLIMIT
w -1662 118 100 0 n#2 tcsApply.tcsApply#544.RESET -1792 -32 -1664 -32 -1664 208 -1568 208 tcsSystemCars.TCS-CARS.RESET
w -1662 758 100 0 n#3 tcsOptics.tcsOptics#651.OPTCE -1840 512 -1664 512 -1664 944 -1560 944 tcsKernel.tcsKernel#669.OPTCE
w -1694 822 100 0 n#4 tcsOptics.tcsOptics#651.OPTCA -1840 576 -1696 576 -1696 1008 -1560 1008 tcsKernel.tcsKernel#669.OPTCA
w -524 726 100 0 n#5 tcsLimits.tcsLimits#670.ROTLOLIM -690 614 -528 614 -528 848 -500 848 -500 856 tcsDrives.tcsDrives#671.ROTLOLIM
w -556 757 100 0 n#6 tcsLimits.tcsLimits#670.ROTHILIM -690 644 -560 644 -560 880 -500 880 -500 886 tcsDrives.tcsDrives#671.ROTHILIM
w -588 788 100 0 n#7 tcsLimits.tcsLimits#670.AZLOLIM -690 674 -592 674 -592 912 -500 912 -500 916 tcsDrives.tcsDrives#671.AZLOLIM
w -620 819 100 0 n#8 tcsLimits.tcsLimits#670.AZHILIM -690 704 -624 704 -624 944 -500 944 -500 946 tcsDrives.tcsDrives#671.AZHILIM
w -852 1012 100 0 n#9 tcsKernel.tcsKernel#669.FFLNK -1144 1008 -500 1008 -500 1006 tcsDrives.tcsDrives#671.TRACK
w -1116 875 100 0 n#10 tcsKernel.tcsKernel#669.CONFLNK -1146 954 -1120 954 -1120 736 -1080 736 -1080 734 tcsLimits.tcsLimits#670.CALCLNK
s -720 2080 100 0 $Id: tcs.sch,v 1.5 2002/02/22 17:46:32 cjm Exp $
s -464 -112 100 0 Gemini Telescope Control System
s -1072 1272 100 0 NB: This schematic is here because
s -1072 1232 100 0 the hierarchy underneath AK environ
s -1072 1192 100 0 is broken
[cell use]
use bc200tr -3312 -392 -100 0 frame
xform 0 -1632 912
use tcsModeSwitch -1504 1095 100 0 tcsModeSwitch#695
xform 0 -1296 1216
use esirs -2944 -217 100 0 esirs#694
xform 0 -2736 -64
p -2808 -112 100 0 1 FTVL:STRING
p -3080 80 100 0 -1 def(INP):$(ag)oiProcSysName
p -2832 -224 100 1024 -1 name:$(top)oiProcSysName
p -2944 32 75 1280 -1 palrm(INP):MS
p -2992 32 75 1024 -1 pproc(INP):CP
use esirs -2944 135 100 0 esirs#693
xform 0 -2736 288
p -2808 240 100 0 1 FTVL:STRING
p -3080 432 100 0 -1 def(INP):$(ag)oi:name
p -2832 128 100 1024 -1 name:$(top)oi:name
p -2944 384 75 1280 -1 palrm(INP):MS
p -2992 384 75 1024 -1 pproc(INP):CP
use tcsInterlock -1816 1320 100 0 tcsInterlock#691
xform 0 -1536 1504
use tcsCombineInpos -2072 1672 100 0 tcsCombineInpos#690
xform 0 -2024 1832
use tcsFrame -2256 1319 100 0 tcsFrame#682
xform 0 -2136 1424
p -2272 1504 100 0 -1 seta:top $(top)srcframe:
use tcsDisplay -3088 967 100 0 tcsDisplay#680
xform 0 -2912 1040
p -3040 1104 100 0 -1 seta:top $(top)display:
use tcsDrives -512 311 100 0 tcsDrives#671
xform 0 -328 688
p -384 1072 100 0 -1 seta:top $(top)drives:
use tcsLimits -1088 391 100 0 tcsLimits#670
xform 0 -888 592
p -976 784 100 0 -1 seta:top $(top)limits:
use tcsKernel -1536 535 100 0 tcsKernel#669
xform 0 -1352 808
p -1456 1056 100 0 -1 seta:top $(top)ak:
use tcsHandset -3056 487 100 0 tcsHandset#668
xform 0 -2912 608
p -2992 736 100 0 -1 seta:top $(top)hs:
use tcsParameters -752 1687 100 0 tcsParameters#661
xform 0 -480 1840
use ebos -2504 1064 100 0 offsys
xform 0 -2400 1152
p -2760 1308 100 0 0 DESC:Units of RA offset
p -2848 1006 100 0 0 ONAM:Coord
p -2848 1038 100 0 0 ZNAM:Sky
p -2848 700 100 0 0 def(OUT):0.000000000000000e+00
p -2320 1038 100 0 0 palrm(OUT):NMS
p -2320 1086 100 0 0 pproc(OUT):NPP
p -2848 604 100 0 0 pproc(SDIS):NPP
use ebos -3016 1160 100 0 opstate
xform 0 -2912 1248
p -3272 1404 100 0 0 DESC:TCS Operational State
use tcsState -1160 1688 100 0 tcsState#654
xform 0 -992 1824
p -1120 1952 100 0 -1 seta:top $(top)state:
use tcsSubcadStats -2960 1696 100 0 TCS-SUBCAD
xform 0 -2904 1864
use tcsOptics -2264 328 100 0 tcsOptics#651
xform 0 -2064 672
p -2192 1022 100 0 -1 seta:top $(top)om:
use tcsHealthCombine -2352 1696 100 0 TCS_HEALTH
xform 0 -2296 1856
p -2432 1648 100 0 0 seta:health $(top)health:
use tcsSystemCars -1512 -72 100 0 TCS-CARS
xform 0 -1464 88
use tcsDefaults -1672 1688 100 0 tcsDefaults#646
xform 0 -1456 1824
p -1568 1952 100 0 -1 seta:top $(top)def:
use tcsSubsystems -1256 1352 100 0 tcsSubsystems#545
xform 0 -1120 1488
use tcsApply -2280 -88 100 0 tcsApply#544
xform 0 -2080 64
use estringins -3080 792 100 0 logrecord
xform 0 -2976 864
p -3104 958 100 0 0 VAL:
[comments]
