[schematic2]
uniq 17
[tools]
[detail]
w 1304 1410 100 0 n#1 eapply.apply862.OCLB 1024 1408 1632 1408 1632 1936 1696 1936 tcsMechanismCad.tcsMechanismCad#109.ICID
w 1288 1444 100 0 n#2 eapply.apply862.OUTB 1024 1440 1600 1440 1600 2016 1696 2016 tcsMechanismCad.tcsMechanismCad#109.DIR
w 1216 2260 100 0 n#3 tcsMechanismCad.tcsMechanismCad#109.MESS 1920 1936 2032 1936 2032 2256 448 2256 448 1408 640 1408 eapply.apply862.INMB
w 1216 2228 100 0 n#4 tcsMechanismCad.tcsMechanismCad#109.VAL 1920 2016 2000 2016 2000 2224 480 2224 480 1440 640 1440 eapply.apply862.INPB
w 1008 436 100 0 n#5 eapply.apply862.INPH 640 1056 512 1056 512 432 1552 432 1552 912 1488 912 tcsCadM1ModelRestore.tcsCadM1ModelRestore#110.VAL
w 1016 452 100 0 n#6 eapply.apply862.INMH 640 1024 544 1024 544 448 1536 448 1536 832 1488 832 tcsCadM1ModelRestore.tcsCadM1ModelRestore#110.MESS
w 1122 1008 100 0 n#7 eapply.apply862.OUTH 1024 1056 1120 1056 1120 912 1264 912 tcsCadM1ModelRestore.tcsCadM1ModelRestore#110.DIR
w 1090 952 100 0 n#8 eapply.apply862.OCLH 1024 1024 1088 1024 1088 832 1264 832 tcsCadM1ModelRestore.tcsCadM1ModelRestore#110.ICID
w 1016 2196 100 0 n#9 tcsMechanismCad.tcsMechanismCad#108.MESS 1504 1936 1568 1936 1568 2192 512 2192 512 1472 640 1472 eapply.apply862.INMA
w 1008 2164 100 0 n#10 tcsMechanismCad.tcsMechanismCad#108.VAL 1504 2016 1536 2016 1536 2160 528 2160 528 1504 640 1504 eapply.apply862.INPA
w 1186 1728 100 0 n#11 eapply.apply862.OCLA 1024 1472 1184 1472 1184 1936 1280 1936 tcsMechanismCad.tcsMechanismCad#108.ICID
w 1154 1784 100 0 n#12 eapply.apply862.OUTA 1024 1504 1152 1504 1152 2016 1280 2016 tcsMechanismCad.tcsMechanismCad#108.DIR
w 374 1570 100 0 n#13 inhier.ICID.P 80 1472 144 1472 144 1568 640 1568 eapply.apply862.CLID
w 342 1602 100 0 n#14 inhier.DIR.P 80 1600 640 1600 eapply.apply862.DIR
w 1934 1570 100 0 n#15 eapply.apply862.MESS 1024 1568 2880 1568 2880 1472 3040 1472 outhier.MESS.p
w 2014 1602 100 0 n#16 eapply.apply862.VAL 1024 1600 3040 1600 outhier.VAL.p
s 2752 224 100 0 TCS commands
s 2848 264 200 0 Gemini TCS
s 2560 2432 100 0 TCS M1 Mechanism Control 2
s 2608 2464 100 0 $Id: tcsMechM1Commands2.sch,v 1.6 2013/10/15 12:40:05 cjm Exp $
[cell use]
use bc200tr -48 -8 -100 0 frame
xform 0 1632 1296
use tcsCadM1ModelRestore 1232 487 100 0 tcsCadM1ModelRestore#110
xform 0 1376 768
p 1264 480 100 0 1 seta:cad m1ModelRestore
p 1264 448 100 0 1 setb:prefix m1
p 1264 416 100 0 1 setc:subsys $(m1)
p 1264 384 100 0 1 setd:subcad figure
p 1264 261 100 0 1 sete:outa 0.0
p 1372 340 100 0 0 setf:outb 0.0
p 1392 320 100 0 0 setg:outc 0.0
p 1412 300 100 0 0 seth:outd 0.0
p 1432 280 100 0 0 seti:oute 0.0
p 1452 260 100 0 0 setj:outf 0.0
p 1264 352 100 0 1 setk:snam tcsCADm1ModelRestore
p 1264 320 100 0 1 setl:text PCS
p 1264 288 100 0 1 setm:timeout 5.0
use tcsMechanismCad 1280 1591 100 0 tcsMechanismCad#108
xform 0 1400 1872
p 1280 1584 100 0 1 seta:cad m1ZoneMode
p 1280 1552 100 0 1 setb:prefix m1
p 1280 1520 100 0 1 setc:subsys $(m1)
p 1280 1488 100 0 1 setd:subcad mode
p 1280 1456 100 0 1 sete:outa $(subsys)$(subcad).B
p 1320 1448 100 0 0 setf:outb 0.0
p 1340 1428 100 0 0 setg:outc 0.0
p 1360 1408 100 0 0 seth:outd 0.0
p 1380 1388 100 0 0 seti:oute 0.0
p 1400 1368 100 0 0 setj:outf 0.0
p 1280 1424 100 0 1 setk:snam tcsCADmechCad
p 1440 1328 100 0 0 setl:text PCS
p 1460 1308 100 0 0 setm:timeout 3.0
use tcsMechanismCad 1696 1591 100 0 tcsMechanismCad#109
xform 0 1816 1872
p 1696 1584 100 0 1 seta:cad m1ElevSource
p 1696 1552 100 0 1 setb:prefix m1
p 1696 1520 100 0 1 setc:subsys $(m1)
p 1696 1488 100 0 1 setd:subcad elev_source
p 1696 1456 100 0 1 sete:outa $(subsys)$(subcad).B
p 1736 1448 100 0 0 setf:outb 0.0
p 1756 1428 100 0 0 setg:outc 0.0
p 1776 1408 100 0 0 seth:outd 0.0
p 1796 1388 100 0 0 seti:oute 0.0
p 1816 1368 100 0 0 setj:outf 0.0
p 1696 1424 100 0 1 setk:snam tcsCADmechCad
p 1856 1328 100 0 0 setl:text PCS
p 1876 1308 100 0 0 setm:timeout 3.0
use outhier 3032 1432 100 0 MESS
xform 0 3024 1472
use outhier 3032 1560 100 0 VAL
xform 0 3024 1600
use eapply 664 968 100 0 apply862
xform 0 832 1328
p 780 1012 100 0 0 DESC:First apply for TCS commands
use inhier 88 1432 100 0 ICID
xform 0 80 1472
use inhier 88 1560 100 0 DIR
xform 0 80 1600
[comments]
