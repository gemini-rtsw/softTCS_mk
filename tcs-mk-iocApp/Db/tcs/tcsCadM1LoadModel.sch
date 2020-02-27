[schematic2]
uniq 81
[tools]
[detail]
w 2136 1675 100 0 n#80 tcsM1LoadCoeffs.tcsM1LoadCoeffs#57.FLNK 3152 1856 3232 1856 3232 1664 1088 1664 1088 480 1312 480 egenSubC.aVals.SLNK
w 1872 491 100 0 n#79 egenSubC.aVals.FLNK 1600 448 1760 448 1760 480 2032 480 egenSubC.bVals.SLNK
w 2632 491 100 0 n#78 egenSubC.bVals.FLNK 2320 448 2528 448 2528 480 2784 480 egenSubC.cVals.SLNK
w 2788 571 100 2 n#77 hwin.hwin#76.in 2784 576 2784 576 egenSubC.cVals.INPT
w 2036 571 100 2 n#75 hwin.hwin#74.in 2032 576 2032 576 egenSubC.bVals.INPT
w 1316 571 100 2 n#73 hwin.hwin#72.in 1312 576 1312 576 egenSubC.aVals.INPT
w 936 619 100 0 n#68 ecad8.ecad8#0.STLK 864 608 1056 608 1056 1856 1248 1856 ebos.m1TriggerLoadModel.SLNK
w 1704 1867 100 0 n#67 ebos.m1TriggerLoadModel.FLNK 1504 1888 1600 1888 1600 1856 1856 1856 tcsM1LoadCoeffs.tcsM1LoadCoeffs#55.SLNK
w 1860 1915 100 2 n#65 hwin.hwin#64.in 1856 1920 1856 1920 tcsM1LoadCoeffs.tcsM1LoadCoeffs#55.INDEX
w 2340 1915 100 2 n#63 hwin.hwin#62.in 2336 1920 2336 1920 tcsM1LoadCoeffs.tcsM1LoadCoeffs#56.INDEX
w 2819 1972 100 0 n#61 hwin.hwin#60.in 2816 1920 2832 1920 tcsM1LoadCoeffs.tcsM1LoadCoeffs#57.INDEX
w 2720 1867 100 0 n#59 tcsM1LoadCoeffs.tcsM1LoadCoeffs#56.FLNK 2656 1856 2832 1856 tcsM1LoadCoeffs.tcsM1LoadCoeffs#57.SLNK
w 2232 1867 100 0 n#58 tcsM1LoadCoeffs.tcsM1LoadCoeffs#55.FLNK 2176 1856 2336 1856 tcsM1LoadCoeffs.tcsM1LoadCoeffs#56.SLNK
w 1035 1444 100 0 n#18 ecad8.ecad8#0.MESS 864 1440 1255 1440 1255 1375 1383 1375 outhier.MESS.p
w 1099 1476 100 0 n#17 ecad8.ecad8#0.VAL 864 1472 1383 1472 1383 1471 outhier.VAL.p
w 329 1362 100 0 n#4 inhier.ICID.P 235 1360 459 1360 459 1440 544 1440 ecad8.ecad8#0.ICID
w 329 1506 100 0 n#3 inhier.DIR.P 235 1504 459 1504 459 1472 544 1472 ecad8.ecad8#0.DIR
s 2592 2400 100 0 $Id: tcsCadM1LoadModel.sch,v 1.1 1999/03/10 21:06:07 cjm Exp $
s 2848 208 100 0 Gemini Telescope Control System
s 1248 2336 100 0 This command just triggers the loading of a new
s 1840 2336 100 0 open loop figure model for M1
s 1248 2272 100 0 It somewhat breaks the TCS/OCS interface in that all the real work is
s 1248 2240 100 0 done outside the CAD subroutine. This had to be done as there
s 1248 2208 100 0 is no CAD that can read in 42 inputs.
s 1152 2048 100 0 m1TriggerLoadModel is processed at load time through 
s 1152 2016 100 0 pvload to get an initial model into the system.
[cell use]
use hwin 1664 1879 100 0 hwin#64
xform 0 1760 1920
p 1667 1912 100 0 -1 val(in):0
use hwin 2144 1879 100 0 hwin#62
xform 0 2240 1920
p 2147 1912 100 0 -1 val(in):1
use hwin 2624 1879 100 0 hwin#60
xform 0 2720 1920
p 2627 1912 100 0 -1 val(in):2
use hwin 1120 535 100 0 hwin#72
xform 0 1216 576
p 1123 568 100 0 -1 val(in):0
use hwin 1840 535 100 0 hwin#74
xform 0 1936 576
p 1843 568 100 0 -1 val(in):1
use hwin 2592 535 100 0 hwin#76
xform 0 2688 576
p 2595 568 100 0 -1 val(in):2
use egenSubC 1312 391 100 0 aVals
xform 0 1456 816
p 1264 1280 100 0 -1 DESC:Display A coefficients of Zernike model
p 1392 576 100 0 1 FTT:DOUBLE
p 1392 544 100 0 0 FTU:DOUBLE
p 1024 942 100 0 0 PREC:3
p 1360 320 100 0 1 SNAM:tcsOpticsM1ShowCoeffs
use egenSubC 2032 391 100 0 bVals
xform 0 2176 816
p 1984 1280 100 0 -1 DESC:Display B coefficients of Zernike model
p 2112 576 100 0 1 FTT:DOUBLE
p 2112 544 100 0 0 FTU:DOUBLE
p 1744 942 100 0 0 PREC:3
p 2080 320 100 0 1 SNAM:tcsOpticsM1ShowCoeffs
use egenSubC 2784 391 100 0 cVals
xform 0 2928 816
p 2736 1280 100 0 -1 DESC:Display C coefficients of Zernike model
p 2864 576 100 0 1 FTT:DOUBLE
p 2864 544 100 0 0 FTU:DOUBLE
p 2496 942 100 0 0 PREC:3
p 2832 320 100 0 1 SNAM:tcsOpticsM1ShowCoeffs
use ebos 1248 1767 100 0 m1TriggerLoadModel
xform 0 1376 1856
p 1016 2012 100 0 0 DESC:Trigger load of coefficients
p 928 1710 100 0 0 ONAM:enabled
p 928 1742 100 0 0 ZNAM:disabled
use tcsM1LoadCoeffs 2896 1799 100 0 tcsM1LoadCoeffs#57
xform 0 2992 1968
p 2916 1772 100 0 1 seta:top $(top)cVals:
p 2912 1728 100 0 1 setb:snam tcsOpticsM1StoreCoeffs
use tcsM1LoadCoeffs 2400 1799 100 0 tcsM1LoadCoeffs#56
xform 0 2496 1968
p 2400 1792 100 0 1 seta:top $(top)bVals:
p 2400 1760 100 0 1 setb:snam tcsOpticsM1StoreCoeffs
use tcsM1LoadCoeffs 1920 1799 100 0 tcsM1LoadCoeffs#55
xform 0 2016 1968
p 1920 1792 100 0 1 seta:top $(top)aVals:
p 1920 1760 100 0 1 setb:snam tcsOpticsM1StoreCoeffs
use outhier 1375 1335 100 0 MESS
xform 0 1367 1375
use outhier 1375 1431 100 0 VAL
xform 0 1367 1471
use inhier 243 1320 100 0 ICID
xform 0 235 1360
use inhier 243 1464 100 0 DIR
xform 0 235 1504
use ecad8 568 520 100 0 ecad8#0
xform 0 704 1024
p 560 1566 100 0 -1 DESC:Implement the m1LoadModel command
p 647 1183 100 0 0 FTVB:STRING
p 640 1120 100 0 0 FTVD:STRING
p 640 1088 100 0 0 FTVE:STRING
p 640 864 100 0 0 PREC:2
p 640 734 100 0 1 SNAM:$(snam)
p 684 448 100 1024 1 name:$(tcs)$(cad)
use bc200tr 16 -72 -100 0 frame
xform 0 1696 1232
[comments]
