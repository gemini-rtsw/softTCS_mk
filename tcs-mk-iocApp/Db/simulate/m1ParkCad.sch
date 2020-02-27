[schematic2]
uniq 94
[tools]
[detail]
w 872 411 100 0 n#93 efanouts.Fan.FLNK 832 1392 960 1392 960 848 704 848 704 400 1088 400 eseqs.CarVals.SLNK
w 1200 1339 100 0 n#92 efanouts.Fan.LNK2 832 1328 1616 1328 1616 1984 1952 1984 elongouts.ApssOnVal.SLNK
w 2048 1595 100 0 n#91 elongouts.AosOnVal.FLNK 2208 1760 2288 1760 2288 1584 1856 1584 1856 1472 1952 1472 elongouts.PssOnVal.SLNK
w 2048 1851 100 0 n#90 elongouts.ApssOnVal.FLNK 2208 2016 2288 2016 2288 1840 1856 1840 1856 1728 1952 1728 elongouts.AosOnVal.SLNK
w 1896 1515 100 0 n#89 hwin.hwin#83.in 1888 1504 1952 1504 elongouts.PssOnVal.DOL
w 1896 1771 100 0 n#88 hwin.hwin#82.in 1888 1760 1952 1760 elongouts.AosOnVal.DOL
w 1896 2027 100 0 n#87 hwin.hwin#81.in 1888 2016 1952 2016 elongouts.ApssOnVal.DOL
w 1000 2027 100 0 n#75 hwin.hwin#70.in 992 2016 1056 2016 elongouts.ApssOffVal.DOL
w 1000 1771 100 0 n#74 hwin.hwin#71.in 992 1760 1056 1760 elongouts.AosOffVal.DOL
w 1000 1515 100 0 n#73 hwin.hwin#72.in 992 1504 1056 1504 elongouts.PssOffVal.DOL
w 1152 1595 100 0 n#69 elongouts.AosOffVal.FLNK 1312 1760 1392 1760 1392 1584 960 1584 960 1472 1056 1472 elongouts.PssOffVal.SLNK
w 1152 1851 100 0 n#68 elongouts.ApssOffVal.FLNK 1312 2016 1392 2016 1392 1840 960 1840 960 1728 1056 1728 elongouts.AosOffVal.SLNK
w 968 1995 100 0 n#67 efanouts.Fan.LNK1 832 1360 928 1360 928 1984 1056 1984 elongouts.ApssOffVal.SLNK
w -48 1147 100 0 n#63 ecad4.ecad4#43.VALB -96 1136 48 1136 48 1440 192 1440 ecalcs.Calc.INPA
w 200 1563 100 0 n#62 elongouts.pssOut.FLNK 352 1760 432 1760 432 1552 16 1552 16 1056 192 1056 ecalcs.Calc.SLNK
w 200 1883 100 0 n#61 elongouts.apssOut.FLNK 352 2048 432 2048 432 1872 16 1872 16 1728 96 1728 elongouts.pssOut.SLNK
w 16 2027 100 0 n#60 ecad4.ecad4#43.STLK -96 784 -16 784 -16 2016 96 2016 elongouts.apssOut.SLNK
w 560 1371 100 0 n#59 ecalcs.Calc.VAL 480 1248 528 1248 528 1360 640 1360 efanouts.Fan.SELL
w 512 1291 100 0 n#58 ecalcs.Calc.FLNK 480 1280 592 1280 efanouts.Fan.SLNK
w 24 1771 100 0 n#55 hwin.hwin#53.in 0 1760 96 1760 elongouts.pssOut.DOL
w 24 2059 100 0 n#54 hwin.hwin#52.in 0 2048 96 2048 elongouts.apssOut.DOL
w 1016 635 100 0 n#48 hwin.hwin#45.in 960 512 992 512 992 624 1088 624 eseqs.CarVals.DOL4
w 1008 667 100 0 n#47 hwin.hwin#44.in 960 592 976 592 976 656 1088 656 eseqs.CarVals.DOL3
w 2240 738 100 0 n#42 ecars.ecars#14.VAL 2208 736 2320 736 outhier.VAL.p
w 2240 514 100 0 n#40 ecars.ecars#14.FLNK 2208 512 2320 512 outhier.FLNK.p
w 1456 690 100 0 n#26 eseqs.CarVals.LNK2 1408 688 1552 688 1552 736 junction
w 1640 747 100 0 n#26 eseqs.CarVals.LNK1 1408 720 1440 720 1440 736 1888 736 ecars.ecars#14.IVAL
w 1024 690 100 0 n#25 hwin.hwin#24.in 1008 672 1008 688 1088 688 eseqs.CarVals.DOL2
w 1064 722 100 0 n#23 hwin.hwin#22.in 1088 720 1088 720 eseqs.CarVals.DOL1
s 784 704 100 0 IDLE
s 880 752 100 0 BUSY
s 2032 -32 100 0 Gemini Telescope Control System
s 2032 -80 100 0 Simulated Park command
s 1760 2176 100 0 $Id: m1ParkCad.sch,v 1.2 1999/03/01 07:23:52 cjm Exp $
[cell use]
use hwin 840 632 100 0 hwin#24
xform 0 912 672
p 830 600 100 0 0 typ(in):val
p 819 664 100 0 -1 val(in):$(CAR_IDLE)
use hwin 920 680 100 0 hwin#22
xform 0 992 720
p 910 648 100 0 0 typ(in):val
p 899 712 100 0 -1 val(in):$(CAR_BUSY)
use hwin 768 551 100 0 hwin#44
xform 0 864 592
p 771 584 100 0 -1 val(in):1
use hwin 768 471 100 0 hwin#45
xform 0 864 512
p 771 504 100 0 -1 val(in):1
use hwin -192 2007 100 0 hwin#52
xform 0 -96 2048
p -189 2040 100 0 -1 val(in):0
use hwin -192 1719 100 0 hwin#53
xform 0 -96 1760
p -189 1752 100 0 -1 val(in):0
use hwin 800 1975 100 0 hwin#70
xform 0 896 2016
p 803 2008 100 0 -1 val(in):0
use hwin 800 1719 100 0 hwin#71
xform 0 896 1760
p 803 1752 100 0 -1 val(in):0
use hwin 800 1463 100 0 hwin#72
xform 0 896 1504
p 803 1496 100 0 -1 val(in):0
use hwin 1696 1975 100 0 hwin#81
xform 0 1792 2016
p 1699 2008 100 0 -1 val(in):1
use hwin 1696 1719 100 0 hwin#82
xform 0 1792 1760
p 1699 1752 100 0 -1 val(in):1
use hwin 1696 1463 100 0 hwin#83
xform 0 1792 1504
p 1699 1496 100 0 -1 val(in):1
use elongouts 96 1927 100 0 apssOut
xform 0 224 2016
p -19 2361 100 0 0 DESC:Set out of position
p -64 1934 100 0 0 OMSL:closed_loop
p 464 1984 100 0 -1 def(OUT):$(m1)apss:inPosition
p 208 1920 100 1024 0 name:$(m1)$(cadname)$(I)
p 352 1984 75 768 -1 pproc(OUT):PP
use elongouts 96 1639 100 0 pssOut
xform 0 224 1728
p -19 2073 100 0 0 DESC:Set out of position
p -64 1646 100 0 0 OMSL:closed_loop
p 464 1696 100 0 -1 def(OUT):$(m1)pss:inPosnBO
p 208 1632 100 1024 0 name:$(m1)$(cadname)$(I)
p 352 1696 75 768 -1 pproc(OUT):PP
use elongouts 1056 1895 100 0 ApssOffVal
xform 0 1184 1984
p 941 2329 100 0 0 DESC:APSS Off
p 896 1902 100 0 0 OMSL:closed_loop
p 1424 1952 100 0 -1 def(OUT):$(m1)apssOn
p 1168 1888 100 1024 0 name:$(m1)$(cadname)$(I)
p 1312 1952 75 768 -1 pproc(OUT):PP
use elongouts 1056 1639 100 0 AosOffVal
xform 0 1184 1728
p 941 2073 100 0 0 DESC:AOS Off
p 896 1646 100 0 0 OMSL:closed_loop
p 1424 1696 100 0 -1 def(OUT):$(m1)aosOn
p 1168 1632 100 1024 0 name:$(m1)$(cadname)$(I)
p 1312 1696 75 768 -1 pproc(OUT):PP
use elongouts 1056 1383 100 0 PssOffVal
xform 0 1184 1472
p 941 1817 100 0 0 DESC:PSS Off
p 896 1390 100 0 0 OMSL:closed_loop
p 1424 1440 100 0 -1 def(OUT):$(m1)pssOn
p 1168 1376 100 1024 0 name:$(m1)$(cadname)$(I)
p 1312 1440 75 768 -1 pproc(OUT):PP
use elongouts 1952 1895 100 0 ApssOnVal
xform 0 2080 1984
p 1837 2329 100 0 0 DESC:APSS Off
p 1792 1902 100 0 0 OMSL:closed_loop
p 2320 1952 100 0 -1 def(OUT):$(m1)apssOn
p 2064 1888 100 1024 0 name:$(m1)$(cadname)$(I)
p 2208 1952 75 768 -1 pproc(OUT):PP
use elongouts 1952 1639 100 0 AosOnVal
xform 0 2080 1728
p 1837 2073 100 0 0 DESC:AOS Off
p 1792 1646 100 0 0 OMSL:closed_loop
p 2320 1696 100 0 -1 def(OUT):$(m1)aosOn
p 2064 1632 100 1024 0 name:$(m1)$(cadname)$(I)
p 2208 1696 75 768 -1 pproc(OUT):PP
use elongouts 1952 1383 100 0 PssOnVal
xform 0 2080 1472
p 1837 1817 100 0 0 DESC:PSS Off
p 1792 1390 100 0 0 OMSL:closed_loop
p 2320 1440 100 0 -1 def(OUT):$(m1)pssOn
p 2064 1376 100 1024 0 name:$(m1)$(cadname)$(I)
p 2208 1440 75 768 -1 pproc(OUT):PP
use efanouts 592 1143 100 0 Fan
xform 0 712 1296
p 448 1262 100 0 0 SELM:Specified
p 704 1136 100 1024 0 name:$(m1)$(cadname)$(I)
use ecalcs 192 967 100 0 Calc
xform 0 336 1232
p 320 1152 100 0 -1 CALC:A+1
p -15 1398 100 0 0 DESC:Increment park index
p 304 960 100 1024 0 name:$(m1)$(cadname)$(I)
use bc200tr -816 -296 -100 0 frame
xform 0 864 1008
use ecad4 -392 696 100 0 ecad4#43
xform 0 -256 1072
p -480 496 100 0 0 FTVA:$(ftva)
p -480 464 100 0 0 FTVB:$(ftvb)
p -480 432 100 0 0 FTVC:$(ftvc)
p -480 400 100 0 0 FTVD:$(ftvd)
p -448 640 100 0 1 SNAM:tcs$(substring)$(cadname)CAD
p -256 1360 100 256 -1 Type:cad
p -304 688 100 1024 1 name:$(prefix)$(cadname)
use outhier 2312 472 100 0 FLNK
xform 0 2304 512
use outhier 2312 696 100 0 VAL
xform 0 2304 736
use ecars 1912 456 100 0 ecars#14
xform 0 2048 624
p 1888 446 100 0 1 name:$(prefix)$(cadname)C
use eseqs 1112 312 100 0 CarVals
xform 0 1248 560
p 1184 526 100 0 0 DLY1:0.0e+00
p 1168 606 100 0 1 DLY2:$(delay)
p 704 -1652 100 0 0 DLY3:0.0
p 704 -1684 100 0 0 DLY4:0.0
p 704 -1716 100 0 0 DLY5:0.0
p 1120 286 100 0 1 PV:$(prefix)$(cadname)
p 1504 656 100 0 0 def(DOL3):0.0
p 1504 624 100 0 0 def(DOL4):0.0
p 1504 592 100 0 0 def(DOL5):0.0
p 1424 718 100 0 0 def(LNK1):0.0
p 1520 656 100 0 -1 def(LNK3):$(m1)apss:inPosition
p 1520 624 100 0 -1 def(LNK4):$(m1)pss:inPosnBO
p 1520 592 100 0 0 def(LNK5):0.0
p 1088 752 75 1280 -1 palrm(SELL):NMS
p 1056 720 75 1280 -1 pproc(DOL1):NPP
p 1056 688 75 1280 -1 pproc(DOL2):NPP
p 1408 730 75 0 -1 pproc(LNK1):PP
p 1408 698 75 0 -1 pproc(LNK2):PP
p 1424 656 75 1024 -1 pproc(LNK3):PP
p 1424 624 75 1024 -1 pproc(LNK4):PP
p 1424 592 75 1024 -1 pproc(LNK5):NPP
[comments]
