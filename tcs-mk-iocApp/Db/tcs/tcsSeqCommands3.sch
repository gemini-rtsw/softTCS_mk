[schematic2]
uniq 68
[tools]
[detail]
w 1233 274 100 0 n#67 tcsSeqPark.tcsSeqPark#61.VAL 2349 896 2427 896 2427 272 87 272 87 1487 416 1487 416 1488 eapply.apply3.INPC
w 1244 311 100 0 n#66 tcsSeqPark.tcsSeqPark#61.MESS 2349 816 2409 816 2409 309 127 309 127 1450 416 1450 416 1456 eapply.apply3.INMC
w 1394 1300 100 0 n#65 eapply.apply3.OCLC 800 1456 898 1456 898 1298 1938 1298 1938 816 2125 816 tcsSeqPark.tcsSeqPark#61.ICID
w 1420 1344 100 0 n#64 eapply.apply3.OUTC 800 1488 800 1491 918 1491 918 1340 1971 1340 1971 897 2125 897 2125 896 tcsSeqPark.tcsSeqPark#61.DIR
w 1388 1906 100 0 n#60 tcsSeqCadCarA.tcsSeqCadCarA#53.STLK 1304 1904 1520 1904 outhier.STOPSTLK.p
w 784 356 100 0 n#48 tcsSeqCadCarA.tcsSeqCadCarA#58.MESS 1224 816 1376 816 1376 352 240 352 240 1392 416 1392 eapply.apply3.INMD
w 784 340 100 0 n#47 tcsSeqCadCarA.tcsSeqCadCarA#58.VAL 1224 896 1408 896 1408 336 208 336 208 1424 416 1424 eapply.apply3.INPD
w 866 1128 100 0 n#44 eapply.apply3.OCLD 800 1392 864 1392 864 816 1000 816 tcsSeqCadCarA.tcsSeqCadCarA#58.ICID
w 882 1184 100 0 n#43 eapply.apply3.OUTD 800 1424 880 1424 880 896 1000 896 tcsSeqCadCarA.tcsSeqCadCarA#58.DIR
w 1320 2354 100 0 n#38 eapply.apply3.INMB 416 1520 208 1520 208 2352 2480 2352 2480 2064 2328 2064 tcsSeqCadCarA.tcsSeqCadCarA#57.MESS
w 1320 2322 100 0 n#37 eapply.apply3.INPB 416 1552 240 1552 240 2320 2448 2320 2448 2144 2328 2144 tcsSeqCadCarA.tcsSeqCadCarA#57.VAL
w 776 2274 100 0 n#36 eapply.apply3.INPA 416 1616 288 1616 288 2272 1312 2272 1312 2144 1240 2144 tcsSeqCadCarA.tcsSeqCadCarA#53.VAL
w 792 2290 100 0 n#35 eapply.apply3.INMA 416 1584 272 1584 272 2288 1360 2288 1360 2064 1240 2064 tcsSeqCadCarA.tcsSeqCadCarA#53.MESS
w 1392 1522 100 0 n#33 eapply.apply3.OCLB 800 1520 2032 1520 2032 2064 2104 2064 tcsSeqCadCarA.tcsSeqCadCarA#57.ICID
w 1368 1554 100 0 n#32 eapply.apply3.OUTB 800 1552 1984 1552 1984 2144 2104 2144 tcsSeqCadCarA.tcsSeqCadCarA#57.DIR
w 850 1904 100 0 n#31 eapply.apply3.OUTA 800 1616 848 1616 848 2144 1016 2144 tcsSeqCadCarA.tcsSeqCadCarA#53.DIR
w 882 1848 100 0 n#30 eapply.apply3.OCLA 800 1584 880 1584 880 2064 1016 2064 tcsSeqCadCarA.tcsSeqCadCarA#53.ICID
w 1976 1428 100 0 n#27 eapply.apply3.MESS 800 1680 928 1680 928 1424 3072 1424 outhier.MESS.p
w 1984 1490 100 0 n#26 eapply.apply3.VAL 800 1712 944 1712 944 1488 3072 1488 outhier.VAL.p
w 248 1682 100 0 n#25 inhier.ICID.P 16 1584 128 1584 128 1680 416 1680 eapply.apply3.CLID
w 192 1714 100 0 n#24 inhier.DIR.P 16 1712 416 1712 eapply.apply3.DIR
s 2464 2592 100 0 $Id: tcsSeqCommands3.sch,v 1.1.1.1 1998/11/08 00:20:46 epics Exp $
s 2784 392 200 0 Gemini TCS
s 2496 248 100 0 P B Taylor
s 2688 280 100 0 C
s 2728 280 100 0 20 Jun 96
s 2768 336 100 0 OCS Sequence commands
[cell use]
use tcsSeqPark 2149 472 100 0 tcsSeqPark#61
xform 0 2245 752
p 2125 432 100 0 1 seta:seqcommand park
p 2125 400 100 0 1 setb:delay 0.5
use outhier 1512 1864 100 0 STOPSTLK
xform 0 1504 1904
use outhier 3064 1448 100 0 VAL
xform 0 3056 1488
use outhier 3064 1384 100 0 MESS
xform 0 3056 1424
use tcsSeqCadCarA 1064 1720 100 0 tcsSeqCadCarA#53
xform 0 1160 2000
p 1040 1680 100 0 1 seta:seqcommand stop
p 1040 1648 100 0 1 setb:carname observeC
p 1040 1616 100 0 1 setc:delay 0.5
use tcsSeqCadCarA 2152 1720 100 0 tcsSeqCadCarA#57
xform 0 2248 2000
p 2128 1680 100 0 1 seta:seqcommand guide
p 2128 1648 100 0 1 setb:carname guideC
p 2128 1616 100 0 1 setc:delay 0.5
use tcsSeqCadCarA 1048 472 100 0 tcsSeqCadCarA#58
xform 0 1144 752
p 1024 432 100 0 1 seta:seqcommand endGuide
p 1024 400 100 0 1 setb:carname endGuideC
p 1024 368 100 0 1 setc:delay 0.5
use inhier 24 1672 100 0 DIR
xform 0 16 1712
use inhier 24 1544 100 0 ICID
xform 0 16 1584
use eapply 440 1080 100 0 apply3
xform 0 608 1440
p 556 1124 100 0 0 DESC:Apply record for OCS sequence commands
use bc200tr -112 120 -100 0 frame
xform 0 1568 1424
[comments]
