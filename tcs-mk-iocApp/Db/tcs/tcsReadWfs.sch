[schematic2]
uniq 8
[tools]
[detail]
w 5948 347 100 0 n#1 inhier.c#1590.P 5808 336 6160 336 6160 1376 6240 1376 esubs.setP1Integrating.INPD
w 6028 555 100 0 n#2 ebis.oiIntegrating.VAL 5984 544 6144 544 6144 1408 6240 1408 esubs.setP1Integrating.INPC
w 6020 811 100 0 n#3 ebis.p2Integrating.VAL 5984 800 6128 800 6128 1440 6240 1440 esubs.setP1Integrating.INPB
w 6012 1067 100 0 n#4 ebis.p1Integrating.VAL 5984 1056 6112 1056 6112 1472 6240 1472 esubs.setP1Integrating.INPA
w 6124 971 100 0 n#5 esubs.setP1Integrating.FLNK 6528 1312 6688 1312 6688 960 5632 960 5632 816 5728 816 ebis.p2Integrating.SLNK
w 6076 1099 100 0 n#6 ebis.p1Integrating.FLNK 5984 1088 6240 1088 esubs.setP1Integrating.SLNK
w 5804 715 100 0 n#7 ebis.p2Integrating.FLNK 5984 832 6048 832 6048 704 5632 704 5632 560 5728 560 ebis.oiIntegrating.SLNK
s 7424 -48 100 0 Gemini Telescope Control System
s 7168 2144 100 0 $Id: tcsReadWfs.sch,v 1.5 2013/05/10 23:30:31 gemvx Exp $
s 7424 -112 100 0 Schematic to read A&G data
[cell use]
use bc200tr 4592 -328 -100 0 frame
xform 0 6272 976
use egenSub 7072 807 100 0 setRTCurrentLims
xform 0 7216 1232
p 6849 581 100 0 0 FTA:LONG
p 7152 1664 100 0 1 SCAN:1 second
p 7104 1712 100 0 1 SNAM:setRTCurrentLimits
p 6752 1600 100 0 -1 def(INPA):$(ag)p2:setOrient.VALA
p 7184 800 100 1024 0 name:$(top)$(I)
use inhier 5792 295 100 0 c#1590
xform 0 5808 336
use esubs 6240 999 100 0 setP1Integrating
xform 0 6384 1264
p 6208 1536 100 0 -1 DESC:Set m1AoAverage flag
p 5952 1118 100 0 0 INAM:tcsNullInit
p 6368 1056 100 0 1 SNAM:tcsOpticsAoAv
p 5856 352 100 0 -1 def(INPD):$(tcs)hr:dc:ao.VALA
use ebis 5728 999 100 0 p1Integrating
xform 0 5856 1072
p 5744 1152 100 0 -1 DESC:Is PWFS1 integrating?
p 5504 910 100 0 0 ONAM:Yes
p 5504 942 100 0 0 ZNAM:No
p 5456 1120 100 0 -1 def(INP):$(pwfs1)measuring
p 5728 1104 75 1280 -1 palrm(INP):MS
p 5696 1104 75 1280 -1 pproc(INP):CA
p 5504 1070 100 0 1 SCAN:1 second
use ebis 5728 743 100 0 p2Integrating
xform 0 5856 816
p 5744 896 100 0 -1 DESC:Is PWFS2 integrating?
p 5504 654 100 0 0 ONAM:Yes
p 5504 686 100 0 0 ZNAM:No
p 5456 864 100 0 -1 def(INP):$(pwfs2)measuring
p 5728 848 75 1280 -1 palrm(INP):MS
p 5696 848 75 1280 -1 pproc(INP):CA
use ebis 5728 487 100 0 oiIntegrating
xform 0 5856 560
p 5744 640 100 0 -1 DESC:Is OIWFS integrating?
p 5504 398 100 0 0 ONAM:Yes
p 5504 430 100 0 0 ZNAM:No
p 5456 608 100 0 -1 def(INP):$(oiwfs)measuring
p 5728 592 75 1280 -1 palrm(INP):MS
p 5696 592 75 1280 -1 pproc(INP):CA
[comments]
