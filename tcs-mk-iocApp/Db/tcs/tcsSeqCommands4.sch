[schematic2]
uniq 62
[tools]
[detail]
w 784 355 100 0 n#48 tcsSeqCadCarA.tcsSeqCadCarA#61.MESS 1224 816 1376 816 1376 352 240 352 240 1392 416 1392 eapply.apply4.INMD
w 784 339 100 0 n#47 tcsSeqCadCarA.tcsSeqCadCarA#61.VAL 1224 896 1408 896 1408 336 208 336 208 1424 416 1424 eapply.apply4.INPD
w 860 1099 100 0 n#44 eapply.apply4.OCLD 800 1392 864 1392 864 816 1000 816 tcsSeqCadCarA.tcsSeqCadCarA#61.ICID
w 876 1155 100 0 n#43 eapply.apply4.OUTD 800 1424 880 1424 880 896 1000 896 tcsSeqCadCarA.tcsSeqCadCarA#61.DIR
w 1320 2355 100 0 n#38 eapply.apply4.INMB 416 1520 208 1520 208 2352 2480 2352 2480 2064 2328 2064 tcsSeqCadCarA.tcsSeqCadCarA#60.MESS
w 1320 2323 100 0 n#37 eapply.apply4.INPB 416 1552 240 1552 240 2320 2448 2320 2448 2144 2328 2144 tcsSeqCadCarA.tcsSeqCadCarA#60.VAL
w 776 2274 100 0 n#36 eapply.apply4.INPA 416 1616 288 1616 288 2272 1312 2272 1312 2144 1264 2144 tcsSeqCadCarB.tcsSeqCadCarB#59.VAL
w 792 2292 100 0 n#35 eapply.apply4.INMA 416 1584 272 1584 272 2288 1360 2288 1360 2064 1264 2064 tcsSeqCadCarB.tcsSeqCadCarB#59.MESS
w 1392 1523 100 0 n#33 eapply.apply4.OCLB 800 1520 2032 1520 2032 2064 2104 2064 tcsSeqCadCarA.tcsSeqCadCarA#60.ICID
w 1368 1555 100 0 n#32 eapply.apply4.OUTB 800 1552 1984 1552 1984 2144 2104 2144 tcsSeqCadCarA.tcsSeqCadCarA#60.DIR
w 850 1904 100 0 n#31 eapply.apply4.OUTA 800 1616 848 1616 848 2144 1040 2144 tcsSeqCadCarB.tcsSeqCadCarB#59.DIR
w 882 1848 100 0 n#30 eapply.apply4.OCLA 800 1584 880 1584 880 2064 1040 2064 tcsSeqCadCarB.tcsSeqCadCarB#59.ICID
w 1976 1428 100 0 n#27 eapply.apply4.MESS 800 1680 928 1680 928 1424 3072 1424 outhier.MESS.p
w 1984 1490 100 0 n#26 eapply.apply4.VAL 800 1712 944 1712 944 1488 3072 1488 outhier.VAL.p
w 248 1682 100 0 n#25 inhier.ICID.P 16 1584 128 1584 128 1680 416 1680 eapply.apply4.CLID
w 192 1714 100 0 n#24 inhier.DIR.P 16 1712 416 1712 eapply.apply4.DIR
s 1376 1760 100 0 set by the pvload file at startup
s 1376 1792 100 0 The values of the default parameters are
s 1376 1824 100 0 is specified to have none.
s 1376 1856 100 0 parameters but the datum sequence command
s 1376 1888 100 0 because the mount datum command needs 
s 1376 1920 100 0 N.B. default parameters are sent to the mount
s 2672 2592 100 0 $Id: tcsSeqCommands4.sch,v 1.3 2010/01/28 13:45:03 ajf Exp $
s 2784 392 200 0 Gemini TCS
s 2496 248 100 0 P B Taylor
s 2688 280 100 0 C
s 2728 280 100 0 16 Jan 97
s 2768 336 100 0 OCS Sequence commands
[cell use]
use tcsSeqCadCarA 2152 1720 100 0 tcsSeqCadCarA#60
xform 0 2248 2000
p 2128 1680 100 0 -1 seta:seqcommand verify
p 2128 1648 100 0 -1 setb:carname verifyC
p 2128 1616 100 0 -1 setc:delay 0.5
use tcsSeqCadCarA 1048 472 100 0 tcsSeqCadCarA#61
xform 0 1144 752
p 1024 432 100 0 -1 seta:seqcommand endVerify
p 1024 400 100 0 -1 setb:carname endVerifyC
p 1024 368 100 0 -1 setc:delay 0.5
use tcsSeqCadCarB 1064 1720 100 0 tcsSeqCadCarB#59
xform 0 1160 2000
p 1040 1680 100 0 1 seta:seqcommand datum
p 1040 1648 100 0 1 setb:delay 0.5
p 1040 1616 100 0 0 setc:outa 0.0
p 1040 1616 100 0 1 setd:outb $(mc)datum.A
p 1040 1584 100 0 1 sete:outc $(mc)datum.B
p 1040 1552 100 0 1 setf:outd $(mc)datum.C
use outhier 3064 1448 100 0 VAL
xform 0 3056 1488
use outhier 3064 1384 100 0 MESS
xform 0 3056 1424
use inhier 24 1672 100 0 DIR
xform 0 16 1712
use inhier 24 1544 100 0 ICID
xform 0 16 1584
use eapply 440 1080 100 0 apply4
xform 0 608 1440
p 556 1124 100 0 0 DESC:Apply record for OCS sequence commands
use bc200tr -112 120 -100 0 frame
xform 0 1568 1424
[comments]
