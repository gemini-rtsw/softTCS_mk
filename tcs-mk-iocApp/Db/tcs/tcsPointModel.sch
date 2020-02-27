[schematic2]
uniq 1425
[tools]
[detail]
w -972 1131 100 0 n#1423 eaos.parsel.VAL -880 848 -704 848 -704 1120 -1168 1120 -1168 1648 -1056 1648 ecalcs.par1fan.INPA
w -372 411 100 0 n#1423 tcsGenParams.tcsGenParams#1397.SEL 32 400 -704 400 -704 848 junction
w -1028 1019 100 0 n#1422 eaos.parsel.FLNK -880 880 -768 880 -768 1008 -1216 1008 -1216 1264 -1056 1264 ecalcs.par1fan.SLNK
w 668 203 100 0 n#1419 efanouts.slnkfan.LNK2 -592 192 2000 192 2000 528 3328 528 3328 1056 3408 1056 egenSubD.model.SLNK
w 3332 1883 100 0 n#1419 tcsCollParam.tcsCollParam#1392.FLNK 2688 2720 3328 2720 3328 1056 junction
w 2668 2283 100 0 n#1419 tcsCollParam.tcsCollParam#1393.FLNK 1920 2416 2080 2416 2080 2272 3328 2272 junction
w 2652 1243 100 0 n#1419 tcsIaParam.tcsIaParam#1424.FLNK 1232 1392 1424 1392 1424 1072 2048 1072 2048 1232 3328 1232 junction
w -988 155 100 0 SLNK inhier.SLNK.P -1072 144 -832 144 efanouts.slnkfan.SLNK
w -604 1963 100 0 n#1342 ecalcs.par1fan.VAL -768 1456 -640 1456 -640 1952 -496 1952 efanouts.parl1sel.SELL
w -604 2523 100 0 n#1342 junction -640 1952 -640 2512 -496 2512 efanouts.pars1sel.SELL
w -108 1587 100 0 n#1394 junction -112 2720 -112 464 32 464 tcsGenParams.tcsGenParams#1397.VAL
w 1324 2427 100 0 n#1394 tcsCollParam.tcsCollParam#1393.NEW 1440 2416 1296 2416 1296 2720 junction
w 628 1403 100 0 n#1394 tcsIaParam.tcsIaParam#1424.NEW 752 1392 592 1392 592 2720 junction
w 796 2731 100 0 n#1394 eaos.newval.VAL -528 2720 2208 2720 tcsCollParam.tcsCollParam#1392.NEW
w 1252 2603 100 0 n#1395 efanouts.parl1sel.LNK1 -304 1952 368 1952 368 2592 2208 2592 tcsCollParam.tcsCollParam#1392.LOCAL
w -100 347 100 0 n#1390 efanouts.pars1sel.FLNK -304 2544 -160 2544 -160 336 32 336 tcsGenParams.tcsGenParams#1397.NEW
w 1306 2171 -100 0 CEINC inhier.CEINC.P 1104 2832 1232 2832 1232 2160 1440 2160 tcsCollParam.tcsCollParam#1393.INCR
w 2074 2475 -100 0 CAINC inhier.CAINC.P 1840 2880 2000 2880 2000 2464 2208 2464 tcsCollParam.tcsCollParam#1392.INCR
w 1164 2235 100 0 n#1347 efanouts.lreset.LNK2 720 2976 960 2976 960 2224 1440 2224 tcsCollParam.tcsCollParam#1393.RESET
w 1572 2539 100 0 n#1346 efanouts.lreset.LNK1 720 3008 1008 3008 1008 2528 2208 2528 tcsCollParam.tcsCollParam#1392.RESET
w 884 2299 100 0 n#1332 efanouts.parl1sel.LNK2 -304 1920 416 1920 416 2288 1440 2288 tcsCollParam.tcsCollParam#1393.LOCAL
w 380 1339 100 0 n#1331 efanouts.pars1sel.LNK3 -304 2448 112 2448 112 1328 752 1328 tcsIaParam.tcsIaParam#1424.SESSION
w 788 2363 100 0 n#1327 efanouts.pars1sel.LNK2 -304 2480 224 2480 224 2352 1440 2352 tcsCollParam.tcsCollParam#1393.SESSION
w 2324 1195 100 0 n#1326 tcsIaParam.tcsIaParam#1424.VAL 1232 1328 1504 1328 1504 1184 3216 1184 3216 1696 3408 1696 egenSubD.model.INPC
w 2556 2171 100 0 n#1322 tcsCollParam.tcsCollParam#1393.VAL 1920 2352 2000 2352 2000 2160 3184 2160 3184 1728 3408 1728 egenSubD.model.INPB
w 1156 2667 100 0 n#1310 efanouts.pars1sel.LNK1 -304 2512 192 2512 192 2656 2208 2656 tcsCollParam.tcsCollParam#1392.SESSION
w 2940 2667 100 0 n#1275 tcsCollParam.tcsCollParam#1392.VAL 2688 2656 3232 2656 3232 1760 3408 1760 egenSubD.model.INPA
w -684 1883 100 0 n#1286 efanouts.setsel.LNK2 -880 2208 -752 2208 -752 1872 -544 1872 efanouts.parl1sel.SLNK
w -684 2443 100 0 n#1284 efanouts.setsel.LNK1 -880 2240 -752 2240 -752 2432 -544 2432 efanouts.pars1sel.SLNK
s 2576 3088 100 0 $Id: tcsPointModel.sch,v 1.7 2000/07/19 00:12:09 dlt Exp $
[cell use]
use tcsIaParam 752 1015 100 0 tcsIaParam#1424
xform 0 992 1232
p 896 1440 100 0 -1 seta:top $(top)ia:
p 528 1264 100 0 -1 setb:descr az index error
p 528 1232 100 0 -1 setc:units arcsec
p 528 1200 100 0 -1 setd:scale 4.84813681109536e-6
p 528 1168 100 0 -1 sete:sadname azIndexError
use efanouts -832 7 100 0 slnkfan
xform 0 -712 160
use efanouts -1120 2023 100 0 setsel
xform 0 -1000 2176
p -1234 2441 100 0 0 DESC:Selects the parameter set
p -1264 2142 100 0 0 SELM:Specified
use efanouts -544 2295 100 0 pars1sel
xform 0 -424 2448
p -658 2713 100 0 0 DESC:Selects the parameter being set
p -688 2414 100 0 0 SELM:Specified
use efanouts -544 1735 100 0 parl1sel
xform 0 -424 1888
p -658 2153 100 0 0 DESC:Selects the local parameter being set
p -688 1854 100 0 0 SELM:Specified
use efanouts 480 2791 100 0 lreset
xform 0 600 2944
p 366 3209 100 0 0 DESC:resets local parameters
use tcsGenParams 32 215 100 0 tcsGenParams#1397
xform 0 144 368
use egenSubD 3408 967 100 0 model
xform 0 3552 1392
p 3251 1707 100 0 0 DESC:Updates pointing model adjustments
p 3472 1360 100 0 1 SNAM:tcsModelAdjust
use bd200tr -1408 -136 -100 0 frame
xform 0 1232 1568
use tcsCollParam 1440 2039 100 0 tcsCollParam#1393
xform 0 1680 2256
p 1568 2464 100 0 -1 seta:top $(top)ce:
p 1840 2288 100 0 -1 setb:descr Vertical collimation
p 1840 2256 100 0 -1 setc:units arcsec
p 1840 2224 100 0 -1 setd:scale 4.84813681109536e-6
p 1840 2192 100 0 -1 sete:sadname collErrEl
use tcsCollParam 2208 2343 100 0 tcsCollParam#1392
xform 0 2448 2560
p 2336 2768 100 0 -1 seta:top $(top)ca:
p 2608 2592 100 0 -1 setb:descr Horizontal collimation
p 2608 2560 100 0 -1 setc:units arcsec
p 2608 2528 100 0 -1 setd:scale 4.84813681109536e-6
p 2608 2496 100 0 -1 sete:sadname collErrAz
use ecalcs -1056 1175 100 0 par1fan
xform 0 -912 1440
p -960 1376 100 0 -1 CALC:A<4?A:0
use inhier 1088 2791 100 0 CEINC
xform 0 1104 2832
use inhier 1824 2839 100 0 CAINC
xform 0 1840 2880
use inhier -1088 103 100 0 SLNK
xform 0 -1072 144
use eaos -1136 759 100 0 parsel
xform 0 -1008 848
p -1356 1034 100 0 0 DESC:parameter selection
p -1392 830 100 0 0 OMSL:closed_loop
use eaos -784 2631 100 0 newval
xform 0 -656 2720
p -832 2848 100 0 0 DESC:new pointing parameter value
p -816 2446 100 0 0 EGU:
p -1040 2702 100 0 0 OMSL:closed_loop
p -1152 2752 100 0 0 def(DOL):0.000000000000000e+00
[comments]
