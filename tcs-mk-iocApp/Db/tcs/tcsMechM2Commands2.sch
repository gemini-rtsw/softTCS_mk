[schematic2]
uniq 126
[tools]
[detail]
w 1378 2322 100 0 n#109 tcsMechanismCad20.tcsMechanismCad20#117.MESS 2336 1936 2416 1936 2416 2320 400 2320 400 1344 640 1344 eapply.apply832.INMC
w 1386 2290 100 0 n#108 tcsMechanismCad20.tcsMechanismCad20#117.VAL 2336 2016 2400 2016 2400 2288 432 2288 432 1376 640 1376 eapply.apply832.INPC
w 1776 1282 100 0 n#92 eapply.apply832.OCLD 1024 1280 2576 1280 2576 1936 2656 1936 tcsMechanismCad.tcsMechanismCad#119.ICID
w 1752 1316 100 0 n#91 eapply.apply832.OUTD 1024 1312 2528 1312 2528 2016 2656 2016 tcsMechanismCad.tcsMechanismCad#119.DIR
w 1664 2388 100 0 n#90 tcsMechanismCad.tcsMechanismCad#119.MESS 2880 1936 3024 1936 3024 2384 352 2384 352 1280 640 1280 eapply.apply832.INMD
w 1656 2356 100 0 n#89 eapply.apply832.INPD 640 1312 384 1312 384 2352 2976 2352 2976 2016 2880 2016 tcsMechanismCad.tcsMechanismCad#119.VAL
w 1528 1346 100 0 n#87 eapply.apply832.OCLC 1024 1344 2080 1344 2080 1936 2112 1936 tcsMechanismCad20.tcsMechanismCad20#117.ICID
w 1512 1380 100 0 n#86 eapply.apply832.OUTC 1024 1376 2048 1376 2048 2016 2112 2016 tcsMechanismCad20.tcsMechanismCad20#117.DIR
w 1304 1410 100 0 n#85 eapply.apply832.OCLB 1024 1408 1632 1408 1632 1936 1696 1936 tcsMechanismCad.tcsMechanismCad#116.ICID
w 1288 1444 100 0 n#84 eapply.apply832.OUTB 1024 1440 1600 1440 1600 2016 1696 2016 tcsMechanismCad.tcsMechanismCad#116.DIR
w 1216 2260 100 0 n#79 tcsMechanismCad.tcsMechanismCad#116.MESS 1920 1936 2032 1936 2032 2256 448 2256 448 1408 640 1408 eapply.apply832.INMB
w 1216 2228 100 0 n#78 tcsMechanismCad.tcsMechanismCad#116.VAL 1920 2016 2000 2016 2000 2224 480 2224 480 1440 640 1440 eapply.apply832.INPB
w 1008 436 100 0 n#123 eapply.apply832.INPH 640 1056 512 1056 512 432 1552 432 1552 912 1488 912 tcsMechanismCad.tcsMechanismCad#125.VAL
w 1016 452 100 0 n#124 eapply.apply832.INMH 640 1024 544 1024 544 448 1536 448 1536 832 1488 832 tcsMechanismCad.tcsMechanismCad#125.MESS
w 1122 1008 100 0 n#53 eapply.apply832.OUTH 1024 1056 1120 1056 1120 912 1264 912 tcsMechanismCad.tcsMechanismCad#125.DIR
w 1090 952 100 0 n#52 eapply.apply832.OCLH 1024 1024 1088 1024 1088 832 1264 832 tcsMechanismCad.tcsMechanismCad#125.ICID
w 1016 2196 100 0 n#21 tcsMechanismCad.tcsMechanismCad#102.MESS 1504 1936 1568 1936 1568 2192 512 2192 512 1472 640 1472 eapply.apply832.INMA
w 1008 2164 100 0 n#20 tcsMechanismCad.tcsMechanismCad#102.VAL 1504 2016 1536 2016 1536 2160 528 2160 528 1504 640 1504 eapply.apply832.INPA
w 1186 1728 100 0 n#19 eapply.apply832.OCLA 1024 1472 1184 1472 1184 1936 1280 1936 tcsMechanismCad.tcsMechanismCad#102.ICID
w 1154 1784 100 0 n#18 eapply.apply832.OUTA 1024 1504 1152 1504 1152 2016 1280 2016 tcsMechanismCad.tcsMechanismCad#102.DIR
w 374 1570 100 0 n#4 inhier.ICID.P 80 1472 144 1472 144 1568 640 1568 eapply.apply832.CLID
w 342 1602 100 0 n#3 inhier.DIR.P 80 1600 640 1600 eapply.apply832.DIR
w 1934 1570 100 0 n#2 eapply.apply832.MESS 1024 1568 2880 1568 2880 1472 3040 1472 outhier.MESS.p
w 2014 1602 100 0 n#1 eapply.apply832.VAL 1024 1600 3040 1600 outhier.VAL.p
s 2560 2432 100 0 $Id: tcsMechM2Commands2.sch,v 1.6 2010/01/28 13:45:02 ajf Exp $
s 2848 264 200 0 Gemini TCS
s 2752 224 100 0 TCS commands
[cell use]
use tcsMechanismCad 1288 488 100 0 tcsMechanismCad#125
xform 0 1384 768
p 1264 478 100 0 1 seta:cad clearTiltGuide
p 1264 446 100 0 1 setb:prefix m2
p 1264 414 100 0 1 setc:subsys $(m2)
p 1264 382 100 0 1 setd:subcad clearTiltGuide
p 1264 320 100 0 1 sete:outa $(subsys)$(subcad).T
p 1264 318 100 0 0 setf:outb 0.0
p 1264 286 100 0 0 setg:outc 0.0
p 1264 254 100 0 0 seth:outd 0.0
p 1264 222 100 0 0 seti:oute 0.0
p 1264 190 100 0 0 setj:outf 0.0
p 1264 350 100 0 1 setk:snam tcsCADmechCad
p 1264 126 100 0 0 setl:timeout 3.0
p 1264 94 100 0 0 setm:text Secondary
use tcsMechanismCad 1304 1592 100 0 tcsMechanismCad#102
xform 0 1400 1872
p 1280 1582 100 0 1 seta:cad m2Init
p 1280 1550 100 0 1 setb:prefix m2
p 1280 1518 100 0 1 setc:subsys $(m2)
p 1280 1486 100 0 1 setd:subcad init
p 1280 1424 100 0 1 sete:outa $(subsys)$(subcad).T
p 1280 1422 100 0 0 setf:outb 0.0
p 1280 1390 100 0 0 setg:outc 0.0
p 1280 1358 100 0 0 seth:outd 0.0
p 1280 1326 100 0 0 seti:oute 0.0
p 1280 1294 100 0 0 setj:outf 0.0
p 1280 1454 100 0 1 setk:snam tcsCADmechCad
p 1280 1230 100 0 0 setl:timeout 3.0
p 1280 1198 100 0 0 setm:text Secondary
use tcsMechanismCad 1720 1592 100 0 tcsMechanismCad#116
xform 0 1816 1872
p 1696 1582 100 0 1 seta:cad clearGuideFocus
p 1696 1550 100 0 1 setb:prefix m2
p 1696 1518 100 0 1 setc:subsys $(m2)
p 1696 1486 100 0 1 setd:subcad clearGuideFocus
p 1696 1424 100 0 1 sete:outa $(subsys)$(subcad).T
p 1696 1422 100 0 0 setf:outb 0.0
p 1696 1390 100 0 0 setg:outc 0.0
p 1696 1358 100 0 0 seth:outd 0.0
p 1696 1326 100 0 0 seti:oute 0.0
p 1696 1294 100 0 0 setj:outf 0.0
p 1696 1454 100 0 1 setk:snam tcsCADmechCad
p 1696 1230 100 0 0 setl:timeout 3.0
p 1696 1198 100 0 0 setm:text Secondary
use tcsMechanismCad 2680 1592 100 0 tcsMechanismCad#119
xform 0 2776 1872
p 2656 1582 100 0 1 seta:cad m2GuideReset
p 2656 1550 100 0 1 setb:prefix m2
p 2656 1518 100 0 1 setc:subsys $(m2)
p 2656 1486 100 0 1 setd:subcad guideConfigReset
p 2656 1424 100 0 1 sete:outa $(subsys)$(subcad).A
p 2656 1422 100 0 0 setf:outb 0.0
p 2656 1390 100 0 0 setg:outc 0.0
p 2656 1358 100 0 0 seth:outd 0.0
p 2656 1326 100 0 0 seti:oute 0.0
p 2656 1294 100 0 0 setj:outf 0.0
p 2656 1454 100 0 1 setk:snam tcsCAD$(cad)
p 2656 1230 100 0 0 setl:timeout 3.0
p 2656 1198 100 0 0 setm:text Secondary
use tcsMechanismCad20 2112 1591 100 0 tcsMechanismCad20#117
xform 0 2232 1872
p 2112 1584 100 0 1 seta:cad m2SetController
p 2112 1552 100 0 1 setb:prefix m2
p 2112 1520 100 0 1 setc:subsys $(m2)
p 2112 1488 100 0 1 setd:subcad setController
p 2192 1504 100 0 0 sete:outa $(subsys)$(subcad).A
p 2212 1484 100 0 0 setf:outb $(subsys)$(subcad).B
p 2232 1464 100 0 0 setg:outc $(subsys)$(subcad).C
p 2252 1444 100 0 0 seth:outd $(subsys)$(subcad).F
p 2272 1424 100 0 0 seti:oute $(subsys)$(subcad).G
p 2292 1404 100 0 0 setj:outf $(subsys)$(subcad).H
p 2312 1384 100 0 0 setk:outg $(subsys)$(subcad).M
p 2332 1364 100 0 0 setl:outh $(subsys)$(subcad).N
p 2352 1344 100 0 0 setm:outi $(subsys)$(subcad).O
p 2372 1324 100 0 0 setn:outj 0.0
p 2392 1304 100 0 0 seto:outk 0.0
p 2412 1284 100 0 0 setp:outl 0.0
p 2432 1264 100 0 0 setq:outm 0.0
p 2452 1244 100 0 0 setr:outn 0.0
p 2112 1456 100 0 1 sett:snam tcsCADmechCad20
p 2492 1204 100 0 0 setu:timeout 3.0
p 2512 1184 100 0 0 setv:text Secondary
use outhier 3032 1560 100 0 VAL
xform 0 3024 1600
use outhier 3032 1432 100 0 MESS
xform 0 3024 1472
use eapply 664 968 100 0 apply832
xform 0 832 1328
p 780 1012 100 0 0 DESC:First apply for TCS commands
use inhier 88 1560 100 0 DIR
xform 0 80 1600
use inhier 88 1432 100 0 ICID
xform 0 80 1472
use bc200tr -48 -8 -100 0 frame
xform 0 1632 1296
[comments]
