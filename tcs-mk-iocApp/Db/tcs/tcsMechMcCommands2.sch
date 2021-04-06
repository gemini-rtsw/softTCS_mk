[schematic2]
uniq 98
[tools]
[detail]
w 1304 1410 100 0 n#1 eapply.apply812.OCLB 1024 1408 1632 1408 1632 1936 1696 1936 tcsMechanismCad.tcsMechanismCad#95.ICID
w 1288 1444 100 0 n#2 eapply.apply812.OUTB 1024 1440 1600 1440 1600 2016 1696 2016 tcsMechanismCad.tcsMechanismCad#95.DIR
w 1216 2260 100 0 n#3 tcsMechanismCad.tcsMechanismCad#95.MESS 1920 1936 2032 1936 2032 2256 448 2256 448 1408 640 1408 eapply.apply812.INMB
w 1216 2228 100 0 n#4 tcsMechanismCad.tcsMechanismCad#95.VAL 1920 2016 2000 2016 2000 2224 480 2224 480 1440 640 1440 eapply.apply812.INPB
w 374 1570 100 0 n#5 inhier.ICID.P 80 1472 144 1472 144 1568 640 1568 eapply.apply812.CLID
w 342 1602 100 0 n#6 inhier.DIR.P 80 1600 640 1600 eapply.apply812.DIR
w 1934 1570 100 0 n#7 eapply.apply812.MESS 1024 1568 2880 1568 2880 1472 3040 1472 outhier.MESS.p
w 2014 1602 100 0 n#8 eapply.apply812.VAL 1024 1600 3040 1600 outhier.VAL.p
s 2560 2432 100 0 $Id: tcsMechMcCommands2.sch,v 1.3 2010/01/28 13:45:02 ajf Exp $
s 2848 264 200 0 Gemini TCS
s 2752 224 100 0 TCS commands to mount
[cell use]
use bc200tr -48 -8 -100 0 frame
xform 0 1632 1296
use tcsMechanismCad 1696 1591 100 0 tcsMechanismCad#95
xform 0 1816 1872
p 1696 1584 100 0 1 seta:cad mountDatum
p 1696 1568 100 0 1 setb:prefix mc
p 1696 1536 100 0 1 setc:subsys $(mc)
p 1696 1504 100 0 1 setd:subcad datum
p 1696 1472 100 0 1 sete:outa $(subsys)$(subcad).A
p 1696 1440 100 0 1 setf:outb $(subsys)$(subcad).B
p 1696 1408 100 0 1 setg:outc $(subsys)$(subcad).C
p 1756 1412 100 0 0 seth:outd 0.0
p 1776 1392 100 0 0 seti:oute 0.0
p 1796 1372 100 0 0 setj:outf 0.0
p 1696 1376 100 0 1 setk:snam tcsCADmechCad
p 1836 1332 100 0 0 setl:timeout 3.0
p 1856 1312 100 0 0 setm:text mount
use tcsMechanismCad 1280 1591 100 0 tcsMechanismCad#97
xform 0 1400 1872
p 1280 1584 100 0 1 seta:cad mountLog
p 1280 1568 100 0 1 setb:prefix mc
p 1280 1536 100 0 1 setc:subsys $(mc)
p 1280 1504 100 0 1 setd:subcad log
p 1280 1472 100 0 1 sete:outa $(subsys)$(subcad).A
p 1280 1440 100 0 1 setf:outb $(subsys)$(subcad).B
p 1280 1408 100 0 1 setg:outc $(subsys)$(subcad).C
p 1340 1412 100 0 0 seth:outd 0.0
p 1360 1392 100 0 0 seti:oute 0.0
p 1380 1372 100 0 0 setj:outf 0.0
p 1280 1376 100 0 1 setk:snam tcsCADmechCad
p 1420 1332 100 0 0 setl:timeout 3.0
p 1440 1312 100 0 0 setm:text mount
use outhier 3032 1560 100 0 VAL
xform 0 3024 1600
use outhier 3032 1432 100 0 MESS
xform 0 3024 1472
use eapply 664 968 100 0 apply812
xform 0 832 1328
p 780 1012 100 0 0 DESC:First apply for TCS commands
use inhier 88 1560 100 0 DIR
xform 0 80 1600
use inhier 88 1432 100 0 ICID
xform 0 80 1472
use bc200tr -48 -8 -100 0 frame
xform 0 1632 1296
[comments]
