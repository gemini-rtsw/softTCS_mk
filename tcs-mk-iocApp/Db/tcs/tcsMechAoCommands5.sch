[schematic2]
uniq 123
[tools]
[detail]
w 1528 1346 100 0 n#87 eapply.apply875.OCLC 1024 1344 2080 1344 2080 1936 2112 1936 tcsMechanismCad.tcsMechanismCad#122.ICID
w 1512 1380 100 0 n#86 eapply.apply875.OUTC 1024 1376 2048 1376 2048 2016 2112 2016 tcsMechanismCad.tcsMechanismCad#122.DIR
w 1304 1410 100 0 n#85 eapply.apply875.OCLB 1024 1408 1632 1408 1632 1936 1696 1936 tcsMechanismCad.tcsMechanismCad#121.ICID
w 1288 1444 100 0 n#84 eapply.apply875.OUTB 1024 1440 1600 1440 1600 2016 1696 2016 tcsMechanismCad.tcsMechanismCad#121.DIR
w 1400 2324 100 0 n#83 tcsMechanismCad.tcsMechanismCad#122.MESS 2336 1936 2448 1936 2448 2320 400 2320 400 1344 640 1344 eapply.apply875.INMC
w 1384 2292 100 0 n#80 tcsMechanismCad.tcsMechanismCad#122.VAL 2336 2016 2400 2016 2400 2288 416 2288 416 1376 640 1376 eapply.apply875.INPC
w 1216 2260 100 0 n#79 tcsMechanismCad.tcsMechanismCad#121.MESS 1920 1936 2032 1936 2032 2256 448 2256 448 1408 640 1408 eapply.apply875.INMB
w 1216 2228 100 0 n#78 tcsMechanismCad.tcsMechanismCad#121.VAL 1920 2016 2000 2016 2000 2224 480 2224 480 1440 640 1440 eapply.apply875.INPB
w 1016 2196 100 0 n#21 tcsMechanismCad.tcsMechanismCad#117.MESS 1504 1936 1568 1936 1568 2192 512 2192 512 1472 640 1472 eapply.apply875.INMA
w 1008 2164 100 0 n#20 tcsMechanismCad.tcsMechanismCad#117.VAL 1504 2016 1536 2016 1536 2160 528 2160 528 1504 640 1504 eapply.apply875.INPA
w 1186 1728 100 0 n#19 eapply.apply875.OCLA 1024 1472 1184 1472 1184 1936 1280 1936 tcsMechanismCad.tcsMechanismCad#117.ICID
w 1154 1784 100 0 n#18 eapply.apply875.OUTA 1024 1504 1152 1504 1152 2016 1280 2016 tcsMechanismCad.tcsMechanismCad#117.DIR
w 374 1570 100 0 n#4 inhier.ICID.P 80 1472 144 1472 144 1568 640 1568 eapply.apply875.CLID
w 342 1602 100 0 n#3 inhier.DIR.P 80 1600 640 1600 eapply.apply875.DIR
w 1934 1570 100 0 n#2 eapply.apply875.MESS 1024 1568 2880 1568 2880 1472 3040 1472 outhier.MESS.p
w 2014 1602 100 0 n#1 eapply.apply875.VAL 1024 1600 3040 1600 outhier.VAL.p
s 2752 224 100 0 TCS commands
s 2848 264 200 0 Gemini TCS
s 2560 2432 100 0 $Id: tcsMechAoCommands5.sch,v 1.2 2010/01/28 13:45:01 ajf Exp $
[cell use]
use tcsMechanismCad 2112 1591 100 0 tcsMechanismCad#122
xform 0 2232 1872
p 2112 1584 100 0 1 seta:cad ngsPr3Park
p 2112 1552 100 0 1 setb:prefix aom
p 2112 1520 100 0 1 setc:subsys $(aom)
p 2112 1504 100 0 1 setd:subcad ngsPr3Ctrl
p 2212 1484 100 0 0 sete:outa $(subsys)$(subcad).A
p 2232 1464 100 0 0 setf:outb 0.0
p 2252 1444 100 0 0 setg:outc 0.0
p 2272 1424 100 0 0 seth:outd 0.0
p 2292 1404 100 0 0 seti:oute 0.0
p 2312 1384 100 0 0 setj:outf 0.0
p 2112 1472 100 0 1 setk:snam tcsCADngsPark
p 2112 1440 100 0 1 setl:timeout 3.0
p 2372 1324 100 0 0 setm:text Canopus
use tcsMechanismCad 1696 1591 100 0 tcsMechanismCad#121
xform 0 1816 1872
p 1696 1584 100 0 1 seta:cad ngsPr2Park
p 1696 1552 100 0 1 setb:prefix aom
p 1696 1520 100 0 1 setc:subsys $(aom)
p 1696 1504 100 0 1 setd:subcad ngsPr2Ctrl
p 1796 1484 100 0 0 sete:outa $(subsys)$(subcad).A
p 1816 1464 100 0 0 setf:outb 0.0
p 1836 1444 100 0 0 setg:outc 0.0
p 1856 1424 100 0 0 seth:outd 0.0
p 1876 1404 100 0 0 seti:oute 0.0
p 1896 1384 100 0 0 setj:outf 0.0
p 1696 1472 100 0 1 setk:snam tcsCADngsPark
p 1696 1440 100 0 1 setl:timeout 3.0
p 1956 1324 100 0 0 setm:text Canopus
use tcsMechanismCad 1280 1591 100 0 tcsMechanismCad#117
xform 0 1400 1872
p 1280 1584 100 0 1 seta:cad ngsPr1Park
p 1280 1552 100 0 1 setb:prefix aom
p 1280 1520 100 0 1 setc:subsys $(aom)
p 1280 1504 100 0 1 setd:subcad ngsPr1Ctrl
p 1380 1484 100 0 0 sete:outa $(subsys)$(subcad).A
p 1400 1464 100 0 0 setf:outb 0.0
p 1420 1444 100 0 0 setg:outc 0.0
p 1440 1424 100 0 0 seth:outd 0.0
p 1460 1404 100 0 0 seti:oute 0.0
p 1480 1384 100 0 0 setj:outf 0.0
p 1280 1472 100 0 1 setk:snam tcsCADngsPark
p 1280 1440 100 0 1 setl:timeout 3.0
p 1540 1324 100 0 0 setm:text Canopus
use outhier 3032 1432 100 0 MESS
xform 0 3024 1472
use outhier 3032 1560 100 0 VAL
xform 0 3024 1600
use eapply 664 968 100 0 apply875
xform 0 832 1328
p 780 1012 100 0 0 DESC:First apply for TCS commands
use inhier 88 1432 100 0 ICID
xform 0 80 1472
use inhier 88 1560 100 0 DIR
xform 0 80 1600
use bc200tr -48 -8 -100 0 frame
xform 0 1632 1296
[comments]
