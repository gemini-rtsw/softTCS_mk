[schematic2]
uniq 112
[tools]
[detail]
w 1170 411 100 0 n#109 tcsMechanismCad.tcsMechanismCad#103.VAL 1888 912 1952 912 1952 400 448 400 448 1120 640 1120 eapply.apply851.INPG
w 1170 427 100 0 n#107 tcsMechanismCad.tcsMechanismCad#103.MESS 1888 832 1920 832 1920 416 480 416 480 1088 640 1088 eapply.apply851.INMG
w 1528 1346 100 0 n#87 eapply.apply851.OCLC 1024 1344 2080 1344 2080 1936 2112 1936 tcsMechanismCad.tcsMechanismCad#101.ICID
w 1512 1380 100 0 n#86 eapply.apply851.OUTC 1024 1376 2048 1376 2048 2016 2112 2016 tcsMechanismCad.tcsMechanismCad#101.DIR
w 1304 1410 100 0 n#85 eapply.apply851.OCLB 1024 1408 1632 1408 1632 1936 1696 1936 tcsMechanismCad.tcsMechanismCad#100.ICID
w 1288 1444 100 0 n#84 eapply.apply851.OUTB 1024 1440 1600 1440 1600 2016 1696 2016 tcsMechanismCad.tcsMechanismCad#100.DIR
w 1400 2324 100 0 n#83 tcsMechanismCad.tcsMechanismCad#101.MESS 2336 1936 2448 1936 2448 2320 400 2320 400 1344 640 1344 eapply.apply851.INMC
w 1384 2292 100 0 n#80 tcsMechanismCad.tcsMechanismCad#101.VAL 2336 2016 2400 2016 2400 2288 416 2288 416 1376 640 1376 eapply.apply851.INPC
w 1216 2260 100 0 n#79 tcsMechanismCad.tcsMechanismCad#100.MESS 1920 1936 2032 1936 2032 2256 448 2256 448 1408 640 1408 eapply.apply851.INMB
w 1216 2228 100 0 n#78 tcsMechanismCad.tcsMechanismCad#100.VAL 1920 2016 2000 2016 2000 2224 480 2224 480 1440 640 1440 eapply.apply851.INPB
w 1008 436 100 0 n#61 eapply.apply851.INPH 640 1056 512 1056 512 432 1552 432 1552 912 1488 912 tcsMechanismCad.tcsMechanismCad#102.VAL
w 1016 452 100 0 n#60 eapply.apply851.INMH 640 1024 544 1024 544 448 1536 448 1536 832 1488 832 tcsMechanismCad.tcsMechanismCad#102.MESS
w 1304 1124 100 0 n#55 eapply.apply851.OUTG 1024 1120 1632 1120 1632 912 1664 912 tcsMechanismCad.tcsMechanismCad#103.DIR
w 1288 1092 100 0 n#54 eapply.apply851.OCLG 1024 1088 1600 1088 1600 832 1664 832 tcsMechanismCad.tcsMechanismCad#103.ICID
w 1122 1008 100 0 n#53 eapply.apply851.OUTH 1024 1056 1120 1056 1120 912 1264 912 tcsMechanismCad.tcsMechanismCad#102.DIR
w 1090 952 100 0 n#52 eapply.apply851.OCLH 1024 1024 1088 1024 1088 832 1264 832 tcsMechanismCad.tcsMechanismCad#102.ICID
w 1016 2196 100 0 n#21 tcsMechanismCad.tcsMechanismCad#99.MESS 1504 1936 1568 1936 1568 2192 512 2192 512 1472 640 1472 eapply.apply851.INMA
w 1008 2164 100 0 n#20 tcsMechanismCad.tcsMechanismCad#99.VAL 1504 2016 1536 2016 1536 2160 528 2160 528 1504 640 1504 eapply.apply851.INPA
w 1186 1728 100 0 n#19 eapply.apply851.OCLA 1024 1472 1184 1472 1184 1936 1280 1936 tcsMechanismCad.tcsMechanismCad#99.ICID
w 1154 1784 100 0 n#18 eapply.apply851.OUTA 1024 1504 1152 1504 1152 2016 1280 2016 tcsMechanismCad.tcsMechanismCad#99.DIR
w 374 1570 100 0 n#4 inhier.ICID.P 80 1472 144 1472 144 1568 640 1568 eapply.apply851.CLID
w 342 1602 100 0 n#3 inhier.DIR.P 80 1600 640 1600 eapply.apply851.DIR
w 1934 1570 100 0 n#2 eapply.apply851.MESS 1024 1568 2880 1568 2880 1472 3040 1472 outhier.MESS.p
w 2014 1602 100 0 n#1 eapply.apply851.VAL 1024 1600 3040 1600 outhier.VAL.p
s 2752 224 100 0 TCS commands
s 2848 264 200 0 Gemini TCS
s 2560 2432 100 0 $Id: tcsMechAgCommands1.sch,v 1.3 2010/01/28 13:45:01 ajf Exp $
s 768 256 100 0 Note that commands with no parameters write to the T field
s 768 224 100 0 of the subsystem CAD in order to mark the record.
[cell use]
use tcsMechanismCad 1664 487 100 0 tcsMechanismCad#103
xform 0 1784 768
p 1664 480 100 0 1 seta:cad agDebug
p 1664 448 100 0 1 setb:prefix ag
p 1664 416 100 0 1 setc:subsys $(ag)
p 1664 384 100 0 1 setd:subcad debug
p 1664 320 100 0 1 sete:outa $(subsys)$(subcad).A
p 1704 344 100 0 0 setf:outb 0.0
p 1724 324 100 0 0 setg:outc 0.0
p 1744 304 100 0 0 seth:outd 0.0
p 1764 284 100 0 0 seti:oute 0.0
p 1784 264 100 0 0 setj:outf 0.0
p 1664 352 100 0 1 setk:snam tcsCADmechCad
p 1824 224 100 0 0 setl:timeout 3.0
p 1844 204 100 0 0 setm:text A&G
use tcsMechanismCad 1264 487 100 0 tcsMechanismCad#102
xform 0 1384 768
p 1264 480 100 0 1 seta:cad agTest
p 1264 448 100 0 1 setb:prefix ag
p 1264 416 100 0 1 setc:subsys $(ag)
p 1264 384 100 0 1 setd:subcad test
p 1264 320 100 0 1 sete:outa $(subsys)$(subcad).T
p 1304 344 100 0 0 setf:outb 0.0
p 1324 324 100 0 0 setg:outc 0.0
p 1344 304 100 0 0 seth:outd 0.0
p 1364 284 100 0 0 seti:oute 0.0
p 1384 264 100 0 0 setj:outf 0.0
p 1264 352 100 0 1 setk:snam tcsCADmechCad
p 1424 224 100 0 0 setl:timeout 3.0
p 1444 204 100 0 0 setm:text A&G
use tcsMechanismCad 2112 1591 100 0 tcsMechanismCad#101
xform 0 2232 1872
p 2112 1584 100 0 1 seta:cad agPark
p 2112 1552 100 0 1 setb:prefix ag
p 2112 1520 100 0 1 setc:subsys $(ag)
p 2112 1488 100 0 1 setd:subcad park
p 2112 1424 100 0 1 sete:outa $(subsys)$(subcad).T
p 2152 1448 100 0 0 setf:outb 0.0
p 2172 1428 100 0 0 setg:outc 0.0
p 2192 1408 100 0 0 seth:outd 0.0
p 2212 1388 100 0 0 seti:oute 0.0
p 2232 1368 100 0 0 setj:outf 0.0
p 2112 1456 100 0 1 setk:snam tcsCADmechCad
p 2272 1328 100 0 0 setl:timeout 3.0
p 2292 1308 100 0 0 setm:text A&G
use tcsMechanismCad 1696 1591 100 0 tcsMechanismCad#100
xform 0 1816 1872
p 1696 1584 100 0 1 seta:cad agInit
p 1696 1552 100 0 1 setb:prefix ag
p 1696 1520 100 0 1 setc:subsys $(ag)
p 1696 1488 100 0 1 setd:subcad init
p 1696 1424 100 0 1 sete:outa $(subsys)$(subcad).T
p 1736 1448 100 0 0 setf:outb 0.0
p 1756 1428 100 0 0 setg:outc 0.0
p 1776 1408 100 0 0 seth:outd 0.0
p 1796 1388 100 0 0 seti:oute 0.0
p 1816 1368 100 0 0 setj:outf 0.0
p 1696 1456 100 0 1 setk:snam tcsCADmechCad
p 1856 1328 100 0 0 setl:timeout 3.0
p 1876 1308 100 0 0 setm:text A&G
use tcsMechanismCad 1280 1591 100 0 tcsMechanismCad#99
xform 0 1400 1872
p 1280 1584 100 0 1 seta:cad agDatum
p 1280 1552 100 0 1 setb:prefix ag
p 1280 1520 100 0 1 setc:subsys $(ag)
p 1280 1488 100 0 1 setd:subcad datum
p 1280 1424 100 0 1 sete:outa $(subsys)$(subcad).T
p 1320 1448 100 0 0 setf:outb 0.0
p 1340 1428 100 0 0 setg:outc 0.0
p 1360 1408 100 0 0 seth:outd 0.0
p 1380 1388 100 0 0 seti:oute 0.0
p 1400 1368 100 0 0 setj:outf 0.0
p 1280 1456 100 0 1 setk:snam tcsCADmechCad
p 1440 1328 100 0 0 setl:timeout 3.0
p 1460 1308 100 0 0 setm:text A&G
use outhier 3032 1432 100 0 MESS
xform 0 3024 1472
use outhier 3032 1560 100 0 VAL
xform 0 3024 1600
use eapply 664 968 100 0 apply851
xform 0 832 1328
p 780 1012 100 0 0 DESC:First apply for TCS commands
use inhier 88 1432 100 0 ICID
xform 0 80 1472
use inhier 88 1560 100 0 DIR
xform 0 80 1600
use bc200tr -48 -8 -100 0 frame
xform 0 1632 1296
[comments]
