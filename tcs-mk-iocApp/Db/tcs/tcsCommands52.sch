[schematic2]
uniq 97
[tools]
[detail]
w 1608 2139 100 0 n#79 tcsCadFollow.tcsCadFollow#74.MESS 2560 1824 2640 1824 2640 2128 624 2128 624 1120 784 1120 eapply.apply52.INMC
w 1600 2123 100 0 n#78 tcsCadFollow.tcsCadFollow#74.VAL 2560 1904 2608 1904 2608 2112 640 2112 640 1152 784 1152 eapply.apply52.INPC
w 1704 1131 100 0 n#77 eapply.apply52.OCLC 1168 1120 2288 1120 2288 1824 2336 1824 tcsCadFollow.tcsCadFollow#74.ICID
w 1688 1163 100 0 n#76 eapply.apply52.OUTC 1168 1152 2256 1152 2256 1904 2336 1904 tcsCadFollow.tcsCadFollow#74.DIR
w 1416 2107 100 0 n#73 tcsCadFollow.tcsCadFollow#91.MESS 2144 1824 2224 1824 2224 2096 656 2096 656 1184 784 1184 eapply.apply52.INMB
w 1408 2091 100 0 n#72 tcsCadFollow.tcsCadFollow#91.VAL 2144 1904 2192 1904 2192 2080 672 2080 672 1216 784 1216 eapply.apply52.INPB
w 1496 1195 100 0 n#71 eapply.apply52.OCLB 1168 1184 1872 1184 1872 1824 1920 1824 tcsCadFollow.tcsCadFollow#91.ICID
w 1480 1227 100 0 n#70 eapply.apply52.OUTB 1168 1216 1840 1216 1840 1904 1920 1904 tcsCadFollow.tcsCadFollow#91.DIR
w 1224 2075 100 0 n#68 tcsCadFollow.tcsCadFollow#96.MESS 1728 1824 1808 1824 1808 2064 688 2064 688 1248 784 1248 eapply.apply52.INMA
w 1216 2059 100 0 n#67 tcsCadFollow.tcsCadFollow#96.VAL 1728 1904 1776 1904 1776 2048 704 2048 704 1280 784 1280 eapply.apply52.INPA
w 1280 1259 100 0 n#66 eapply.apply52.OCLA 1168 1248 1440 1248 1440 1824 1504 1824 tcsCadFollow.tcsCadFollow#96.ICID
w 1264 1291 100 0 n#65 eapply.apply52.OUTA 1168 1280 1408 1280 1408 1904 1504 1904 tcsCadFollow.tcsCadFollow#96.DIR
w 2102 1346 100 0 n#8 eapply.apply52.MESS 1168 1344 3072 1344 3072 1280 3248 1280 outhier.MESS.p
w 2190 1378 100 0 n#7 eapply.apply52.VAL 1168 1376 3248 1376 outhier.VAL.p
w 582 1346 100 0 n#4 inhier.ICID.P 256 1296 416 1296 416 1344 784 1344 eapply.apply52.CLID
w 502 1378 100 0 n#3 inhier.DIR.P 256 1376 784 1376 eapply.apply52.DIR
s 2784 2240 100 0 $Id: tcsCommands52.sch,v 1.2 2010/01/28 13:45:01 ajf Exp $
s 2992 16 100 0 TCS commands
s 2976 64 200 0 Gemini TCS
[cell use]
use tcsCadFollow 1504 1479 100 0 tcsCadFollow#96
xform 0 1616 1760
p 1536 1632 100 0 -1 seta:cad ngs1Follow
p 1520 1600 100 0 -1 setb:snam tcsCADfollow
p 1504 1472 100 0 1 setc:prefix ngs1
p 1504 1440 100 0 1 setd:subsys $(aom)
p 1504 1408 100 0 1 sete:text NGSPR1
p 1520 1568 100 0 1 setf:stop ngsPr1Stop
p 1520 1520 100 0 1 setg:follow ngsPr1Follow
use tcsCadFollow 1920 1479 100 0 tcsCadFollow#91
xform 0 2032 1760
p 1952 1632 100 0 -1 seta:cad ngs2Follow
p 1936 1600 100 0 -1 setb:snam tcsCADfollow
p 1920 1472 100 0 1 setc:prefix ngs2
p 1920 1440 100 0 1 setd:subsys $(aom)
p 1920 1408 100 0 1 sete:text NGSPR2
p 1936 1568 100 0 1 setf:stop ngsPr2Stop
p 1936 1520 100 0 1 setg:follow ngsPr2Follow
use tcsCadFollow 2336 1479 100 0 tcsCadFollow#74
xform 0 2448 1760
p 2368 1632 100 0 -1 seta:cad ngs3Follow
p 2352 1600 100 0 -1 setb:snam tcsCADfollow
p 2336 1472 100 0 1 setc:prefix ngs3
p 2336 1440 100 0 1 setd:subsys $(aom)
p 2336 1408 100 0 1 sete:text NGSPR3
p 2352 1568 100 0 1 setf:stop ngsPr3Stop
p 2352 1520 100 0 1 setg:follow ngsPr3Follow
use bc200tr 96 -200 -100 0 frame
xform 0 1776 1104
use outhier 3240 1336 100 0 VAL
xform 0 3232 1376
use outhier 3240 1240 100 0 MESS
xform 0 3232 1280
use inhier 264 1336 100 0 DIR
xform 0 256 1376
use inhier 264 1256 100 0 ICID
xform 0 256 1296
use eapply 808 744 100 0 apply52
xform 0 976 1104
[comments]
