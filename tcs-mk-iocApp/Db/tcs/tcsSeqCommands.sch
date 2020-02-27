[schematic2]
uniq 59
[tools]
[detail]
w 2656 1282 100 0 n#51 tcsSeqCommands2.tcsSeqCommands2#56.CONTSTLK 2464 1280 2896 1280 2896 1440 2928 1440 tcsObserve.tcsObserve#47.CONTINUE
w 2648 1314 100 0 n#50 tcsSeqCommands2.tcsSeqCommands2#56.PAUSESTLK 2464 1312 2880 1312 2880 1504 2928 1504 tcsObserve.tcsObserve#47.PAUSE
w 2640 1010 100 0 n#49 tcsSeqCommands3.tcsSeqCommands3#57.STOPSTLK 2464 1008 2864 1008 2864 1344 junction
w 2640 1346 100 0 n#49 tcsSeqCommands2.tcsSeqCommands2#56.ABORTSTLK 2464 1344 2864 1344 2864 1376 junction
w 2640 1378 100 0 n#49 tcsSeqCommands2.tcsSeqCommands2#56.ENDSTLK 2464 1376 2864 1376 2864 1568 2928 1568 tcsObserve.tcsObserve#47.OBSEND
w 2640 1778 100 0 n#48 tcsSeqCommands1.tcsSeqCommands1#55.OBSSTLK 2464 1776 2864 1776 2864 1696 2928 1696 tcsObserve.tcsObserve#47.OBSBEGIN
w 1672 258 100 0 n#39 tcsSeqCommands1.tcsSeqCommands1#55.VAL 2464 1824 2752 1824 2752 256 640 256 640 2080 1024 2080 eapply.apply.INPA
w 1672 290 100 0 n#38 tcsSeqCommands1.tcsSeqCommands1#55.MESS 2464 1728 2720 1728 2720 288 672 288 672 2048 1024 2048 eapply.apply.INMA
w 1672 324 100 0 n#37 tcsSeqCommands2.tcsSeqCommands2#56.VAL 2464 1504 2688 1504 2688 320 704 320 704 2016 1024 2016 eapply.apply.INPB
w 1672 356 100 0 n#36 tcsSeqCommands2.tcsSeqCommands2#56.MESS 2464 1408 2656 1408 2656 352 736 352 736 1984 1024 1984 eapply.apply.INMB
w 1672 386 100 0 n#35 tcsSeqCommands3.tcsSeqCommands3#57.VAL 2464 1056 2624 1056 2624 384 768 384 768 1952 1024 1952 eapply.apply.INPC
w 1672 418 100 0 n#34 tcsSeqCommands3.tcsSeqCommands3#57.MESS 2464 960 2592 960 2592 416 800 416 800 1920 1024 1920 eapply.apply.INMC
w 1672 450 100 0 n#33 tcsSeqCommands4.tcsSeqCommands4#58.VAL 2464 704 2560 704 2560 448 832 448 832 1888 1024 1888 eapply.apply.INPD
w 1672 482 100 0 n#32 tcsSeqCommands4.tcsSeqCommands4#58.MESS 2464 608 2528 608 2528 480 864 480 864 1856 1024 1856 eapply.apply.INMD
w 1602 1256 100 0 n#31 eapply.apply.OCLD 1408 1856 1600 1856 1600 608 1888 608 tcsSeqCommands4.tcsSeqCommands4#58.ICID
w 1634 1320 100 0 n#30 eapply.apply.OUTD 1408 1888 1632 1888 1632 704 1888 704 tcsSeqCommands4.tcsSeqCommands4#58.DIR
w 1666 1464 100 0 n#29 eapply.apply.OCLC 1408 1920 1664 1920 1664 960 1888 960 tcsSeqCommands3.tcsSeqCommands3#57.ICID
w 1698 1528 100 0 n#28 eapply.apply.OUTC 1408 1952 1696 1952 1696 1056 1888 1056 tcsSeqCommands3.tcsSeqCommands3#57.DIR
w 1730 1720 100 0 n#27 eapply.apply.OCLB 1408 1984 1728 1984 1728 1408 1888 1408 tcsSeqCommands2.tcsSeqCommands2#56.ICID
w 1762 1784 100 0 n#26 eapply.apply.OUTB 1408 2016 1760 2016 1760 1504 1888 1504 tcsSeqCommands2.tcsSeqCommands2#56.DIR
w 1576 2050 100 0 n#25 eapply.apply.OCLA 1408 2048 1792 2048 1792 1728 1888 1728 tcsSeqCommands1.tcsSeqCommands1#55.ICID
w 1592 2082 100 0 n#24 eapply.apply.OUTA 1408 2080 1824 2080 1824 1824 1888 1824 tcsSeqCommands1.tcsSeqCommands1#55.DIR
w 2040 2146 100 0 n#23 eapply.apply.MESS 1408 2144 2720 2144 2720 2000 2976 2000 outhier.MESS.p
w 2168 2178 100 0 n#22 eapply.apply.VAL 1408 2176 2976 2176 outhier.VAL.p
w 744 2146 100 0 n#21 inhier.ICID.P 384 1936 512 1936 512 2144 1024 2144 eapply.apply.CLID
w 680 2178 100 0 n#20 inhier.DIR.P 384 2176 1024 2176 eapply.apply.DIR
s 2920 96 100 0 OCS Sequence commands
s 2840 32 100 0 C
s 2944 152 200 0 Gemini TCS
s 2624 2352 100 0 $Id: tcsSeqCommands.sch,v 1.1.1.1 1998/11/08 00:20:45 epics Exp $
[cell use]
use tcsSeqCommands4 1888 519 100 0 tcsSeqCommands4#58
xform 0 2176 640
use tcsSeqCommands3 1888 871 100 0 tcsSeqCommands3#57
xform 0 2176 992
use tcsSeqCommands2 1888 1191 100 0 tcsSeqCommands2#56
xform 0 2176 1376
use tcsSeqCommands1 1888 1639 100 0 tcsSeqCommands1#55
xform 0 2176 1760
use ebos 592 15 100 0 dbReloading
xform 0 696 103
p 704 176 100 1024 1 name:$(tcs)$(I)
use tcsObserve 2952 1352 100 0 tcsObserve#47
xform 0 3072 1600
p 3008 1840 100 0 -1 seta:top $(tcs)observe:
use ecars 216 72 100 0 guideC
xform 0 352 240
p 256 400 100 0 1 name:$(tcs)$(I)
use ecars 216 456 100 0 endGuideC
xform 0 352 624
p 256 784 100 0 1 name:$(tcs)$(I)
use ecars 232 840 100 0 verifyC
xform 0 368 1008
p 288 1168 100 0 1 name:$(tcs)$(I)
use ecars 232 1192 100 0 endVerifyC
xform 0 368 1360
p 288 1520 100 0 1 name:$(tcs)$(I)
use ecars 232 1544 100 0 observeC
xform 0 368 1712
p 272 1872 100 0 1 name:$(tcs)$(I)
use outhier 2968 2136 100 0 VAL
xform 0 2960 2176
use outhier 2968 1960 100 0 MESS
xform 0 2960 2000
use inhier 392 2136 100 0 DIR
xform 0 384 2176
use inhier 392 1896 100 0 ICID
xform 0 384 1936
use eapply 1048 1544 100 0 apply
xform 0 1216 1904
p 1164 1588 100 0 0 DESC:Top OCS Sequence command Apply
use bc200tr 32 -120 -100 0 frame
xform 0 1712 1184
[comments]
