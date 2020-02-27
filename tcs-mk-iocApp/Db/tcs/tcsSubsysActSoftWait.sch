[schematic2]
uniq 30
[tools]
[detail]
w 2320 949 100 0 n#1 ecars.CommSentC.FLNK 2288 944 2352 944 2352 1136 2400 1136 eaos.CarOut.SLNK
w 2320 1179 100 0 n#2 ecars.CommSentC.VAL 2288 1168 2400 1168 eaos.CarOut.DOL
w 1144 1771 100 0 n#3 eaos.eaos#5.FLNK 1472 1952 1600 1952 1600 1760 736 1760 736 1568 0 1568 0 992 192 992 ecalcs.ActCalc.SLNK
w 344 1547 100 0 n#4 junction 704 1824 704 1536 32 1536 32 1376 192 1376 ecalcs.ActCalc.INPA
w 936 1963 100 0 n#4 ecalcouts.ecalcouts#79.VAL 512 1824 704 1824 704 1952 1216 1952 eaos.eaos#5.DOL
w 1656 2347 100 0 n#5 estringouts.estringouts#14.OUT 1632 2336 1728 2336 1728 2096 junction
w 1232 2107 100 0 n#5 tcsSubsysCarToggle.tcsSubsysCarToggle#82.MESS 544 2096 1968 2096 ecars.ecars#24.IMSS
w 1608 1899 100 0 n#6 eaos.eaos#5.OUT 1472 1888 1792 1888 1792 2160 junction
w 1232 2171 100 0 n#6 tcsSubsysCarToggle.tcsSubsysCarToggle#82.OUT 544 2160 1968 2160 ecars.ecars#24.IVAL
w 1416 2027 100 0 n#7 estringouts.estringouts#14.FLNK 1632 2368 1760 2368 1760 2016 1120 2016 1120 1920 1216 1920 eaos.eaos#5.SLNK
w 568 1899 100 0 n#8 ecalcouts.ecalcouts#79.FLNK 512 1888 672 1888 672 2352 junction
w 936 2363 100 0 n#8 tcsSubsysCarToggle.tcsSubsysCarToggle#82.TRIG 544 2352 1376 2352 estringouts.estringouts#14.SLNK
w 1112 2331 100 0 n#9 tcsSubsysCarToggle.tcsSubsysCarToggle#82.DISV 544 2416 896 2416 896 2320 1376 2320 estringouts.estringouts#14.SDIS
w 1168 2395 100 0 n#10 inhier.c#21.P 1008 2384 1376 2384 estringouts.estringouts#14.DOL
w 1080 1195 100 0 n#11 efanouts.ActFan.LNK1 832 1184 1376 1184 estringouts.ActNull.SLNK
w 48 1659 100 0 n#12 ecalcouts.ecalcouts#79.OUT 512 1760 576 1760 576 1648 -432 1648 -432 2336 -320 2336 ecars.RawActiveC.IVAL
w 1248 642 100 0 n#13 tcsTimeOut.tcsTimeOut#54.EXPIRED 928 608 1152 608 1152 640 1392 640 estringouts.ActTout.SLNK
w 1048 770 100 0 n#14 eaos.ActIdle.FLNK 1632 944 1696 944 1696 768 448 768 448 416 480 416 tcsTimeOut.tcsTimeOut#54.STOP
w 1248 1650 100 0 n#15 inhier.RESET.P 1168 1648 1376 1648 estringouts.ResetNull.SLNK
w 1728 1378 100 0 n#16 eaos.ResetIdle.OUT 1632 1376 1872 1376 1872 1168 junction
w 1874 632 100 0 n#16 eaos.ActErr.OUT 1648 336 1872 336 1872 880 junction
w 1874 1048 100 0 n#16 eaos.ActIdle.OUT 1632 880 1872 880 1872 1168 1968 1168 ecars.CommSentC.IVAL
w 1810 1424 100 0 n#17 estringouts.ResetNull.OUT 1632 1632 1808 1632 1808 1168 junction
w 1810 888 100 0 n#17 estringouts.ActTout.OUT 1648 624 1808 624 1808 1104 junction
w 1696 1170 100 0 n#17 estringouts.ActNull.OUT 1632 1168 1808 1168 1808 1104 1968 1104 ecars.CommSentC.IMSS
w 1296 1442 100 0 n#18 hwin.hwin#65.in 1264 1440 1376 1440 eaos.ResetIdle.DOL
w 1496 1554 100 0 n#19 estringouts.ResetNull.FLNK 1632 1664 1728 1664 1728 1552 1312 1552 1312 1408 1376 1408 eaos.ResetIdle.SLNK
w 1480 514 100 0 n#20 estringouts.ActTout.FLNK 1648 656 1696 656 1696 512 1312 512 1312 368 1392 368 eaos.ActErr.SLNK
w 296 546 100 0 n#21 eaos.StartTimer.FLNK 240 544 400 544 400 608 480 608 tcsTimeOut.tcsTimeOut#54.START
w 1320 402 100 0 n#22 hwin.hwin#57.in 1296 400 1392 400 eaos.ActErr.DOL
w 530 1184 100 0 n#23 ecalcs.ActCalc.FLNK 480 1216 528 1216 528 1104 592 1104 efanouts.ActFan.SLNK
w 536 1186 100 0 n#24 ecalcs.ActCalc.VAL 480 1184 640 1184 efanouts.ActFan.SELL
w 1480 1058 100 0 n#25 estringouts.ActNull.FLNK 1632 1200 1696 1200 1696 1056 1312 1056 1312 912 1376 912 eaos.ActIdle.SLNK
w 1296 946 100 0 n#26 hwin.hwin#40.in 1264 944 1376 944 eaos.ActIdle.DOL
w 2408 1938 100 0 n#27 ecars.ecars#24.FLNK 2288 1936 2576 1936 outhier.FLNK.p
w 2408 2098 100 0 n#28 ecars.ecars#24.OMSS 2288 2096 2576 2096 outhier.OMSS.p
w 2408 2162 100 0 n#29 ecars.ecars#24.VAL 2288 2160 2576 2160 outhier.VAL.p
s -416 2480 100 0 activeC.
s -416 2512 100 0 subsystems that reflect only mechanism activity in
s -416 2544 100 0 It looks for activity both on softC and activeC for
s -416 2576 100 0 This schematic is a derivative of tcsSubsysActWait.
s 1984 1600 100 0 before any new commands are issued.
s 1984 1632 100 0 is issued. This ensures CommSentC always gets set to IDLE
s 1984 1664 100 0 The reset line will be trigerred each time a new configuration
s 2032 2592 100 0 $Id: tcsSubsysActSoftWait.sch,v 1.3 2004/08/05 09:56:10 cjm Exp $
s 2640 272 100 0 1
s 2528 272 100 0 1
s 2272 400 100 0 Gemini Telescope Control System
s 688 2544 200 0 Reflect subsystem activity into the TCS
s 2000 2480 100 0 The CommSentC CAR record is set to IDLE whenever the
s 2000 2448 100 0 subsystem activeC CAR record transitions to BUSY.
s 2000 2416 100 0 Note that the internal TCS ActiveC record is set BUSY
s 2000 2384 100 0 first so that overall applyC remains BUSY.
[cell use]
use bc200tr -544 120 -100 0 frame
xform 0 1136 1424
use eaos 1400 1320 100 0 ResetIdle
xform 0 1504 1408
p 1392 1502 100 0 -1 DESC:Set output to CAR_IDLE
p 1344 1134 100 0 0 EGU:none
p 1120 1390 100 0 0 OMSL:closed_loop
p 1120 1422 100 0 0 PINI:NO
p 1088 1470 100 0 0 def(DOL):0.0
p 1808 1390 100 0 0 def(OUT):0.0
p 1568 1312 100 1024 0 name:$(top)$(prefix)$(I)
p 1632 1376 75 768 -1 pproc(OUT):PP
use eaos 1416 280 100 0 ActErr
xform 0 1520 368
p 1408 462 100 0 -1 DESC:Set output to CAR_ERROR
p 1360 94 100 0 0 EGU:none
p 1136 350 100 0 0 OMSL:closed_loop
p 1136 382 100 0 0 PINI:NO
p 1104 430 100 0 0 def(DOL):0.0
p 1824 350 100 0 0 def(OUT):0.0
p 1584 272 100 1024 0 name:$(top)$(prefix)$(I)
p 1648 336 75 768 -1 pproc(OUT):PP
use eaos 8 424 100 0 StartTimer
xform 0 112 512
p -48 622 100 0 -1 DESC:Dummy record to trigger timer
p 96 416 100 1024 0 name:$(top)$(prefix)$(I)
use eaos 1240 1832 100 0 eaos#5
xform 0 1344 1920
p 960 1902 100 0 0 OMSL:closed_loop
p 960 1934 100 0 0 PINI:YES
p 928 1982 100 0 0 def(DOL):0.0
p 1648 1902 100 0 0 def(OUT):0.0
p 1408 1824 100 1024 1 name:$(top)$(prefix)ActWao
p 1472 1888 75 768 -1 pproc(OUT):PP
use eaos 1400 824 100 0 ActIdle
xform 0 1504 912
p 1392 1006 100 0 -1 DESC:Set output to CAR_IDLE
p 1344 638 100 0 0 EGU:none
p 1120 894 100 0 0 OMSL:closed_loop
p 1120 926 100 0 0 PINI:NO
p 1088 974 100 0 0 def(DOL):0.0
p 1808 894 100 0 0 def(OUT):0.0
p 1568 816 100 1024 0 name:$(top)$(prefix)$(I)
p 1632 880 75 768 -1 pproc(OUT):PP
use eaos 2400 1047 100 0 CarOut
xform 0 2528 1136
p 2352 1248 100 0 -1 DESC:Provides output link for CAR
p 2368 862 100 0 0 EGU:units
p 2144 1118 100 0 0 OMSL:closed_loop
p 2240 816 100 0 1 def(OUT):$(tcs)softC:valCombine.$(field)
p 2512 1040 100 1024 0 name:$(top)$(prefix)$(I)
p 2656 1104 75 768 -1 pproc(OUT):PP
p 0 0 100 0 0 pproc(SDIS):NPP
p 0 0 100 0 0 palrm(SDIS):NMS
use ecars -320 2055 100 0 RawActiveC
xform 0 -160 2224
p -272 2384 100 0 -1 DESC:Raw subsystem CAR state
p -208 2048 100 1024 0 name:$(top)$(prefix)$(I)
use ecars 1992 888 100 0 CommSentC
xform 0 2128 1056
p 2048 1246 100 0 -1 DESC:Command sent CAR
p 2080 880 100 1024 0 name:$(tcs)$(prefix)$(I)
use ecars 1992 1880 100 0 ecars#24
xform 0 2128 2048
p 2088 1872 100 1024 -1 name:$(top)$(prefix)ActiveC
use tcsSubsysCarToggle 256 2039 100 0 tcsSubsysCarToggle#82
xform 0 400 2256
p 256 2464 100 0 1 seta:top $(top)$(prefix)
use ecalcouts 192 1703 100 0 ecalcouts#79
xform 0 352 1824
p 280 2000 100 0 1 CALC:(A=2 || B=2)?2:MAX(A,B)
p 280 1968 100 0 1 OOPT:On Change
p -128 1896 100 0 -1 def(INPA):$(subsys)activeC.VAL
p -104 1864 100 0 -1 def(INPB):$(subsys)softC.VAL
p 256 1704 100 0 -1 name:$(top)$(prefix)ActWait
p 144 1896 75 0 -1 pproc(INPA):CPP
p 144 1864 75 0 -1 pproc(INPB):CPP
p 512 1776 75 0 -1 pproc(OUT):PP
use inhier 1176 1608 100 0 RESET
xform 0 1168 1648
use inhier 1016 2344 100 0 c#21
xform 0 1008 2384
use hwin 1096 1400 100 0 hwin#65
xform 0 1168 1440
p 1075 1432 100 0 -1 val(in):$(CAR_IDLE)
use hwin 1128 360 100 0 hwin#57
xform 0 1200 400
p 1107 392 100 0 -1 val(in):$(CAR_ERROR)
use hwin 1096 904 100 0 hwin#40
xform 0 1168 944
p 1075 936 100 0 -1 val(in):$(CAR_IDLE)
use estringouts 1400 1576 100 0 ResetNull
xform 0 1504 1648
p 1403 1688 100 0 0 DESC:Empty string
p 1312 1454 100 0 0 OMSL:supervisory
p 1312 1614 100 0 0 VAL:
p 1040 1710 100 0 0 def(DOL):0.0
p 1696 1646 100 0 0 def(OUT):0.0
p 1460 1568 100 1024 0 name:$(top)$(prefix)$(I)
p 1632 1632 75 768 -1 pproc(OUT):NPP
use estringouts 1416 568 100 0 ActTout
xform 0 1520 640
p 1440 718 100 0 -1 DESC:Timeout string
p 1328 446 100 0 0 OMSL:supervisory
p 1328 606 100 0 0 VAL:$(text) timed out
p 1056 702 100 0 0 def(DOL):0.0
p 1712 638 100 0 0 def(OUT):0.0
p 1476 560 100 1024 0 name:$(top)$(prefix)$(I)
p 1648 624 75 768 -1 pproc(OUT):NPP
use estringouts 1400 2280 100 0 estringouts#14
xform 0 1504 2352
p 1312 2158 100 0 0 OMSL:closed_loop
p 1040 2414 100 0 -1 def(DOL):$(subsys)activeC.OMSS
p 1696 2350 100 0 0 def(OUT):0.0
p 1460 2272 100 1024 1 name:$(top)$(prefix)ActWso
p 1632 2336 75 768 -1 pproc(OUT):NPP
use estringouts 1400 1112 100 0 ActNull
xform 0 1504 1184
p 1403 1224 100 0 0 DESC:Empty string
p 1312 990 100 0 0 OMSL:supervisory
p 1312 1150 100 0 0 VAL:
p 1040 1246 100 0 0 def(DOL):0.0
p 1696 1182 100 0 0 def(OUT):0.0
p 1460 1104 100 1024 0 name:$(top)$(prefix)$(I)
p 1632 1168 75 768 -1 pproc(OUT):NPP
use tcsTimeOut 504 360 100 0 tcsTimeOut#54
xform 0 704 512
p 640 478 100 0 -1 seta:timeout 3.0
p 640 446 100 0 0 setb:top $(top)$(prefix)
use efanouts 616 968 100 0 ActFan
xform 0 712 1120
p 448 1086 100 0 0 SELM:Specified
p 704 960 100 1024 0 name:$(top)$(prefix)$(I)
use ecalcs 216 904 100 0 ActCalc
xform 0 336 1168
p 256 1086 100 0 1 CALC:A=2?1:0
p 352 1392 100 0 -1 DESC:Check if subsystem has changed to BUSY
p 304 896 100 1024 0 name:$(top)$(prefix)$(I)
use outhier 2568 2120 100 0 VAL
xform 0 2560 2160
use outhier 2568 2056 100 0 OMSS
xform 0 2560 2096
use outhier 2568 1896 100 0 FLNK
xform 0 2560 1936
[comments]
