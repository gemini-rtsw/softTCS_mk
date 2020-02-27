[schematic2]
uniq 21
[tools]
[detail]
w 2008 2083 100 0 n#1 tcsCadRotGuideMode.tcsCadRotGuideMode#132.VAL 1984 2080 2032 2080 2032 2304 480 2304 480 1312 640 1312 eapply.apply6.INPB
w 2024 2003 100 0 n#2 tcsCadRotGuideMode.tcsCadRotGuideMode#132.MESS 1984 2000 2064 2000 2064 2320 464 2320 464 1280 640 1280 eapply.apply6.INMB
w 1520 2067 100 0 n#3 tcsCad4.tcsCad4#127.VAL 1504 2064 1536 2064 1536 2240 544 2240 544 1376 640 1376 eapply.apply6.INPA
w 1536 1987 100 0 n#4 tcsCad4.tcsCad4#127.MESS 1504 1984 1568 1984 1568 2272 512 2272 512 1344 640 1344 eapply.apply6.INMA
w 1104 1347 100 0 n#5 eapply.apply6.OCLA 1024 1344 1184 1344 1184 1984 1280 1984 tcsCad4.tcsCad4#127.ICID
w 1088 1379 100 0 n#6 eapply.apply6.OUTA 1024 1376 1152 1376 1152 2064 1280 2064 tcsCad4.tcsCad4#127.DIR
w 1344 1283 100 0 n#7 eapply.apply6.OCLB 1024 1280 1664 1280 1664 2000 1760 2000 tcsCadRotGuideMode.tcsCadRotGuideMode#132.ICID
w 1312 1315 100 0 n#8 eapply.apply6.OUTB 1024 1312 1600 1312 1600 2080 1760 2080 tcsCadRotGuideMode.tcsCadRotGuideMode#132.DIR
w 2504 2003 100 0 n#9 tcsCadRotGuideConfig.tcsCadRotGuideConfig#137.MESS 2448 2000 2560 2000 2560 2384 400 2384 400 1216 640 1216 eapply.apply6.INMC
w 2488 2083 100 0 n#10 tcsCadRotGuideConfig.tcsCadRotGuideConfig#137.VAL 2448 2080 2528 2080 2528 2352 432 2352 432 1248 640 1248 eapply.apply6.INPC
w 1584 1219 100 0 n#11 eapply.apply6.OCLC 1024 1216 2144 1216 2144 2000 2224 2000 tcsCadRotGuideConfig.tcsCadRotGuideConfig#137.ICID
w 1568 1251 100 0 n#12 eapply.apply6.OUTC 1024 1248 2112 1248 2112 2080 2224 2080 tcsCadRotGuideConfig.tcsCadRotGuideConfig#137.DIR
w 112 1347 100 0 n#13 inhier.ICID.P 80 1344 144 1344 144 1440 640 1440 eapply.apply6.CLID
w 360 1475 100 0 n#14 inhier.DIR.P 80 1472 640 1472 eapply.apply6.DIR
w 1952 1443 100 0 n#15 eapply.apply6.MESS 1024 1440 2880 1440 2880 1344 3040 1344 outhier.MESS.p
w 2032 1475 100 0 n#16 eapply.apply6.VAL 1024 1472 3040 1472 outhier.VAL.p
w 1034 938 -100 0 n#17 eapply.apply6.OUTH 1024 928 1232 928 1232 816 1280 816 tcsCadM1ModelSave.tcsCadM1ModelSave#138.DIR
w 1034 906 -100 0 n#18 eapply.apply6.OCLH 1024 896 1200 896 1200 736 1280 736 tcsCadM1ModelSave.tcsCadM1ModelSave#138.ICID
w 1514 746 -100 0 n#19 tcsCadM1ModelSave.tcsCadM1ModelSave#138.MESS 1504 736 1536 736 1536 384 528 384 528 896 640 896 eapply.apply6.INMH
w 1514 826 -100 0 n#20 tcsCadM1ModelSave.tcsCadM1ModelSave#138.VAL 1504 816 1552 816 1552 368 512 368 512 928 640 928 eapply.apply6.INPH
s 2560 2480 100 0 $Id: tcsImCommands6.sch,v 1.4 2013/10/15 12:40:05 cjm Exp $
s 2896 272 200 0 Gemini TCS
s 2928 224 100 0 TCS commands
[cell use]
use bc200tr -16 8 -100 0 frame
xform 0 1664 1312
use tcsCadRotGuideConfig 2224 1655 100 0 tcsCadRotGuideConfig#137
xform 0 2336 1936
p 2224 1648 100 0 -1 seta:cad rotGuideConfig
p 2224 1616 100 0 -1 setb:snam tcsCADrotGuideConfig
use tcsCadRotGuideMode 1760 1655 100 0 tcsCadRotGuideMode#132
xform 0 1872 1936
p 1744 1648 100 0 -1 seta:cad rotGuideMode
p 1744 1616 100 0 -1 setb:snam tcsCADrotGuideMode
use tcsCad4 1280 1639 100 0 tcsCad4#127
xform 0 1392 1920
p 1380 1564 100 0 0 set0:ftva STRING
p 1400 1544 100 0 0 set1:ftvb LONG
p 1420 1524 100 0 0 set2:ftvc DOUBLE
p 1440 1504 100 0 0 set3:ftvd LONG
p 1280 1632 100 0 1 seta:cad zeroRotGuide
p 1280 1600 100 0 1 setb:snam tcsCADzeroRotGuide
use outhier 3032 1432 100 0 VAL
xform 0 3024 1472
use outhier 3032 1304 100 0 MESS
xform 0 3024 1344
use inhier 88 1432 100 0 DIR
xform 0 80 1472
use inhier 88 1304 100 0 ICID
xform 0 80 1344
use eapply 664 840 100 0 apply6
xform 0 832 1200
p 780 884 100 0 0 DESC:First apply for TCS commands
use tcsCadM1ModelSave 1280 416 100 0 tcsCadM1ModelSave#138
xform 0 1392 672
p 1280 395 100 0 1 seta:cad m1ModelSave
p 1279 348 100 0 1 setb:snam tcsCADm1ModelSave
p 1280 320 100 0 1 setc:outa 0.0
[comments]
