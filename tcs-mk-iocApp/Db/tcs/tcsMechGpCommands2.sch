[schematic2]
uniq 126
[tools]
[detail]
w 1776 1282 100 0 n#92 eapply.apply882.OCLD 1024 1280 2576 1280 2576 1936 2656 1936 tcsMechanismCad.tcsMechanismCad#125.ICID
w 1752 1316 100 0 n#91 eapply.apply882.OUTD 1024 1312 2528 1312 2528 2016 2656 2016 tcsMechanismCad.tcsMechanismCad#125.DIR
w 1664 2388 100 0 n#90 tcsMechanismCad.tcsMechanismCad#125.MESS 2880 1936 3024 1936 3024 2384 352 2384 352 1280 640 1280 eapply.apply882.INMD
w 1656 2356 100 0 n#89 eapply.apply882.INPD 640 1312 384 1312 384 2352 2976 2352 2976 2016 2880 2016 tcsMechanismCad.tcsMechanismCad#125.VAL
w 1528 1346 100 0 n#87 eapply.apply882.OCLC 1024 1344 2080 1344 2080 1936 2112 1936 tcsMechanismCad.tcsMechanismCad#124.ICID
w 1512 1380 100 0 n#86 eapply.apply882.OUTC 1024 1376 2048 1376 2048 2016 2112 2016 tcsMechanismCad.tcsMechanismCad#124.DIR
w 1304 1410 100 0 n#85 eapply.apply882.OCLB 1024 1408 1632 1408 1632 1936 1696 1936 tcsGpolPlateMoveCad.tcsGpolPlateMoveCad#123.ICID
w 1288 1444 100 0 n#84 eapply.apply882.OUTB 1024 1440 1600 1440 1600 2016 1696 2016 tcsGpolPlateMoveCad.tcsGpolPlateMoveCad#123.DIR
w 1400 2324 100 0 n#83 tcsMechanismCad.tcsMechanismCad#124.MESS 2336 1936 2448 1936 2448 2320 400 2320 400 1344 640 1344 eapply.apply882.INMC
w 1384 2292 100 0 n#80 tcsMechanismCad.tcsMechanismCad#124.VAL 2336 2016 2400 2016 2400 2288 416 2288 416 1376 640 1376 eapply.apply882.INPC
w 1216 2260 100 0 n#121 tcsGpolPlateMoveCad.tcsGpolPlateMoveCad#123.MESS 1920 1936 2032 1936 2032 2256 448 2256 448 1408 640 1408 eapply.apply882.INMB
w 1216 2228 100 0 n#122 tcsGpolPlateMoveCad.tcsGpolPlateMoveCad#123.VAL 1920 2016 2000 2016 2000 2224 480 2224 480 1440 640 1440 eapply.apply882.INPB
w 1016 2196 100 0 n#108 tcsMechanismCad.tcsMechanismCad#119.MESS 1504 1936 1568 1936 1568 2192 512 2192 512 1472 640 1472 eapply.apply882.INMA
w 1008 2164 100 0 n#107 tcsMechanismCad.tcsMechanismCad#119.VAL 1504 2016 1536 2016 1536 2160 528 2160 528 1504 640 1504 eapply.apply882.INPA
w 1186 1728 100 0 n#19 eapply.apply882.OCLA 1024 1472 1184 1472 1184 1936 1280 1936 tcsMechanismCad.tcsMechanismCad#119.ICID
w 1154 1784 100 0 n#18 eapply.apply882.OUTA 1024 1504 1152 1504 1152 2016 1280 2016 tcsMechanismCad.tcsMechanismCad#119.DIR
w 374 1570 100 0 n#4 inhier.ICID.P 80 1472 144 1472 144 1568 640 1568 eapply.apply882.CLID
w 342 1602 100 0 n#3 inhier.DIR.P 80 1600 640 1600 eapply.apply882.DIR
w 1934 1570 100 0 n#2 eapply.apply882.MESS 1024 1568 2880 1568 2880 1472 3040 1472 outhier.MESS.p
w 2014 1602 100 0 n#1 eapply.apply882.VAL 1024 1600 3040 1600 outhier.VAL.p
s 2752 224 100 0 TCS commands
s 2848 264 200 0 Gemini TCS
s 2560 2432 100 0 TCS Mechanism Control Commands 1
s 2560 2464 100 0 $Id: tcsMechGpCommands2.sch,v 1.3 2010/01/28 13:45:02 ajf Exp $
[cell use]
use tcsMechanismCad 2112 1591 100 0 tcsMechanismCad#124
xform 0 2232 1872
p 2112 1584 100 0 1 seta:cad gpolInit
p 2112 1552 100 0 1 setb:prefix gp
p 2112 1520 100 0 1 setc:subsys $(gp)
p 2112 1488 100 0 1 setd:subcad init
p 2112 1456 100 0 1 sete:outa $(subsys)$(subcad).T
p 2212 1484 100 0 0 setf:outb 0.0
p 2232 1464 100 0 0 setg:outc 0.0
p 2252 1444 100 0 0 seth:outd 0.0
p 2272 1424 100 0 0 seti:oute 0.0
p 2292 1404 100 0 0 setj:outf 0.0
p 2112 1424 100 0 1 setk:snam tcsCADmechCad
p 2332 1364 100 0 0 setl:timeout 3.0
p 2352 1344 100 0 0 setm:text GPOL
use tcsMechanismCad 1280 1591 100 0 tcsMechanismCad#119
xform 0 1400 1872
p 1280 1584 100 0 1 seta:cad gpolIdentify
p 1280 1552 100 0 1 setb:prefix gp
p 1280 1520 100 0 1 setc:subsys $(gp)
p 1280 1488 100 0 1 setd:subcad identify
p 1280 1456 100 0 1 sete:outa $(subsys)$(subcad).T
p 1380 1484 100 0 0 setf:outb 0.0
p 1400 1464 100 0 0 setg:outc 0.0
p 1420 1444 100 0 0 seth:outd 0.0
p 1440 1424 100 0 0 seti:oute 0.0
p 1460 1404 100 0 0 setj:outf 0.0
p 1280 1424 100 0 1 setk:snam tcsCADmechCad
p 1500 1364 100 0 0 setl:timeout 3.0
p 1520 1344 100 0 0 setm:text GPOL
use tcsMechanismCad 2656 1591 100 0 tcsMechanismCad#125
xform 0 2776 1872
p 2656 1584 100 0 1 seta:cad gpolPlateSeq
p 2656 1552 100 0 1 setb:prefix gp
p 2656 1520 100 0 1 setc:subsys $(gp)
p 2656 1488 100 0 1 setd:subcad seq
p 2656 1456 100 0 1 sete:outa $(subsys)$(subcad).A
p 2756 1484 100 0 0 setf:outb $(subsys)$(subcad).B
p 2776 1464 100 0 0 setg:outc $(subsys)$(subcad).C
p 2796 1444 100 0 0 seth:outd $(subsys)$(subcad).D
p 2816 1424 100 0 0 seti:oute $(subsys)$(subcad).E
p 2836 1404 100 0 0 setj:outf $(subsys)$(subcad).F
p 2656 1424 100 0 1 setk:snam tcsCADgpolPlateSeq
p 2876 1364 100 0 0 setl:timeout 3.0
p 2896 1344 100 0 0 setm:text GPOL
use tcsGpolPlateMoveCad 1680 1591 100 0 tcsGpolPlateMoveCad#123
xform 0 1824 1872
p 1696 1584 100 0 1 seta:cad gpolPlateMove
p 1696 1552 100 0 1 setb:prefix gp
p 1696 1520 100 0 1 setc:subsys $(gp)
p 1716 1500 100 0 0 setd:timeout 3.0
p 1736 1480 100 0 0 sete:text GPOL
use outhier 3032 1432 100 0 MESS
xform 0 3024 1472
use outhier 3032 1560 100 0 VAL
xform 0 3024 1600
use eapply 664 968 100 0 apply882
xform 0 832 1328
p 780 1012 100 0 0 DESC:First apply for TCS commands
use inhier 88 1432 100 0 ICID
xform 0 80 1472
use inhier 88 1560 100 0 DIR
xform 0 80 1600
use bc200tr -48 -8 -100 0 frame
xform 0 1632 1296
[comments]
