[schematic2]
uniq 21
[tools]
[detail]
w 1552 1347 100 0 n#1 eapply.apply874.OCLC 1024 1344 2080 1344 2080 1936 2112 1936 tcsCadaoSfoLoop.tcsCadaoSfoLoop#120.ICID
w 1536 1379 100 0 n#2 eapply.apply874.OUTC 1024 1376 2048 1376 2048 2016 2112 2016 tcsCadaoSfoLoop.tcsCadaoSfoLoop#120.DIR
w 1328 1411 100 0 n#3 eapply.apply874.OCLB 1024 1408 1632 1408 1632 1936 1696 1936 tcsMechanismCad.tcsMechanismCad#118.ICID
w 1312 1443 100 0 n#4 eapply.apply874.OUTB 1024 1440 1600 1440 1600 2016 1696 2016 tcsMechanismCad.tcsMechanismCad#118.DIR
w 2392 1939 100 0 n#5 tcsCadaoSfoLoop.tcsCadaoSfoLoop#120.MESS 2336 1936 2448 1936 2448 2320 400 2320 400 1344 640 1344 eapply.apply874.INMC
w 2368 2019 100 0 n#6 tcsCadaoSfoLoop.tcsCadaoSfoLoop#120.VAL 2336 2016 2400 2016 2400 2288 416 2288 416 1376 640 1376 eapply.apply874.INPC
w 1976 1939 100 0 n#7 tcsMechanismCad.tcsMechanismCad#118.MESS 1920 1936 2032 1936 2032 2256 448 2256 448 1408 640 1408 eapply.apply874.INMB
w 1960 2019 100 0 n#8 tcsMechanismCad.tcsMechanismCad#118.VAL 1920 2016 2000 2016 2000 2224 480 2224 480 1440 640 1440 eapply.apply874.INPB
w 1536 1939 100 0 n#9 tcsMechanismCad.tcsMechanismCad#117.MESS 1504 1936 1568 1936 1568 2192 512 2192 512 1472 640 1472 eapply.apply874.INMA
w 1520 2019 100 0 n#10 tcsMechanismCad.tcsMechanismCad#117.VAL 1504 2016 1536 2016 1536 2160 528 2160 528 1504 640 1504 eapply.apply874.INPA
w 1104 1475 100 0 n#11 eapply.apply874.OCLA 1024 1472 1184 1472 1184 1936 1280 1936 tcsMechanismCad.tcsMechanismCad#117.ICID
w 1088 1507 100 0 n#12 eapply.apply874.OUTA 1024 1504 1152 1504 1152 2016 1280 2016 tcsMechanismCad.tcsMechanismCad#117.DIR
w 112 1475 100 0 n#13 inhier.ICID.P 80 1472 144 1472 144 1568 640 1568 eapply.apply874.CLID
w 360 1603 100 0 n#14 inhier.DIR.P 80 1600 640 1600 eapply.apply874.DIR
w 1952 1571 100 0 n#15 eapply.apply874.MESS 1024 1568 2880 1568 2880 1472 3040 1472 outhier.MESS.p
w 2032 1603 100 0 n#16 eapply.apply874.VAL 1024 1600 3040 1600 outhier.VAL.p
w 1034 1314 -100 0 n#17 eapply.apply874.OUTD 1024 1312 2504 1312 2504 2016 2600 2016 tcsMechCad.tcsMechCad#121.DIR
w 1034 1290 -100 0 n#18 eapply.apply874.OCLD 1024 1280 2544 1280 2544 1936 2600 1936 tcsMechCad.tcsMechCad#121.ICID
w 2834 2026 -100 0 n#19 tcsMechCad.tcsMechCad#121.VAL 2824 2016 2856 2016 2856 2344 376 2344 376 1312 640 1312 eapply.apply874.INPD
w 2834 1938 -100 0 n#20 tcsMechCad.tcsMechCad#121.MESS 2824 1936 2880 1936 2880 2360 360 2360 360 1280 640 1280 eapply.apply874.INMD
s 2752 224 100 0 TCS commands
s 2848 264 200 0 Gemini TCS
s 2560 2432 100 0 $Id: tcsMechAoCommands4.sch,v 1.4 2014/02/08 02:10:21 gemvx Exp $
[cell use]
use bc200tr -48 -8 -100 0 frame
xform 0 1632 1296
use tcsCadaoSfoLoop 2112 1591 100 0 tcsCadaoSfoLoop#120
xform 0 2224 1872
p 2112 1584 100 0 1 seta:cad aoSFOLoop
p 2112 1552 100 0 1 setb:snam tcsCADaoSFOLoop
use tcsMechanismCad 1696 1591 100 0 tcsMechanismCad#118
xform 0 1816 1872
p 1696 1584 100 0 1 seta:cad aoTTGSLoop
p 1696 1552 100 0 1 setb:prefix ao
p 1696 1520 100 0 1 setc:subsys $(ao)wfcs:
p 1696 1504 100 0 1 setd:subcad strapCorrCtl
p 1796 1484 100 0 0 sete:outa $(subsys)$(subcad).A
p 1816 1464 100 0 0 setf:outb 0.0
p 1836 1444 100 0 0 setg:outc 0.0
p 1856 1424 100 0 0 seth:outd 0.0
p 1876 1404 100 0 0 seti:oute 0.0
p 1896 1384 100 0 0 setj:outf 0.0
p 1696 1472 100 0 1 setk:snam tcsCADaoTTGSLoop
p 1696 1440 100 0 1 setl:timeout 3.0
p 1956 1324 100 0 0 setm:text Altair
use tcsMechanismCad 1280 1591 100 0 tcsMechanismCad#117
xform 0 1400 1872
p 1280 1584 100 0 1 seta:cad aoFlexFile
p 1280 1552 100 0 1 setb:prefix ao
p 1280 1520 100 0 1 setc:subsys $(ao)
p 1280 1504 100 0 1 setd:subcad ncpa
p 1380 1484 100 0 0 sete:outa $(subsys)$(subcad).A
p 1400 1464 100 0 0 setf:outb $(subsys)$(subcad).B
p 1420 1444 100 0 0 setg:outc 0.0
p 1440 1424 100 0 0 seth:outd 0.0
p 1460 1404 100 0 0 seti:oute 0.0
p 1480 1384 100 0 0 setj:outf 0.0
p 1280 1472 100 0 1 setk:snam tcsCADaoFlexFile
p 1280 1440 100 0 1 setl:timeout 3.0
p 1540 1324 100 0 0 setm:text Altair
use outhier 3032 1432 100 0 MESS
xform 0 3024 1472
use outhier 3032 1560 100 0 VAL
xform 0 3024 1600
use eapply 664 968 100 0 apply874
xform 0 832 1328
p 780 1012 100 0 0 DESC:First apply for TCS commands
use inhier 88 1432 100 0 ICID
xform 0 80 1472
use inhier 88 1560 100 0 DIR
xform 0 80 1600
use tcsMechCad 2600 1616 100 0 tcsMechCad#121
xform 0 2712 1872
p 2606 1581 100 0 1 seta:cad aoLgsttfSource
p 2608 1547 100 0 1 setb:prefix ao
p 2608 1517 100 0 1 setc:subsys $(ao)
p 2615 1489 100 0 1 setd:subcad lgsttSource
p 2606 1459 100 0 1 sete:outa $(subsys)$(subcad).A
p 2608 1392 100 0 1 setf:outb $(subsys)$(subcad).B
p 0 0 100 0 0 setg:outc 0.0
p 0 0 100 0 0 seth:outd 0.0
p 0 0 100 0 0 seti:oute 0.0
p 0 0 100 0 0 setj:outf 0.0
p 2610 1432 100 0 1 setk:snam tcsCADaoLgsttfSource
[comments]
