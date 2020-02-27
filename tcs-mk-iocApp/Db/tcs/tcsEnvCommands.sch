[schematic2]
uniq 77
[tools]
[detail]
w 1160 459 100 0 n#76 tcsEnvCad.temperature.MESS 1824 832 1888 832 1888 448 480 448 480 1808 672 1808 eapply.apply7.INMD
w 1160 427 100 0 n#75 tcsEnvCad.temperature.VAL 1824 912 1920 912 1920 416 448 416 448 1840 672 1840 eapply.apply7.INPD
w 1424 843 100 0 n#74 eapply.apply7.OCLD 1056 1808 1296 1808 1296 832 1600 832 tcsEnvCad.temperature.ICID
w 1168 1851 100 0 n#73 eapply.apply7.OUTD 1056 1840 1328 1840 1328 912 1600 912 tcsEnvCad.temperature.DIR
w 1200 2235 100 0 n#72 tcsEnvCad.useWS.VAL 1824 1776 1920 1776 1920 2224 528 2224 528 2032 672 2032 eapply.apply7.INPA
w 1200 2267 100 0 n#71 tcsEnvCad.useWS.MESS 1824 1696 1952 1696 1952 2256 496 2256 496 2000 672 2000 eapply.apply7.INMA
w 1264 2043 100 0 n#70 eapply.apply7.OUTA 1056 2032 1520 2032 1520 1776 1600 1776 tcsEnvCad.useWS.DIR
w 1248 2011 100 0 n#69 eapply.apply7.OCLA 1056 2000 1488 2000 1488 1696 1600 1696 tcsEnvCad.useWS.ICID
w 1632 2404 100 0 n#48 tcsEnvCad.pressure.MESS 2896 1680 2976 1680 2976 2400 336 2400 336 1872 672 1872 eapply.apply7.INMC
w 1640 2372 100 0 n#47 tcsEnvCad.pressure.VAL 2896 1760 2944 1760 2944 2368 384 2368 384 1904 672 1904 eapply.apply7.INPC
w 1968 1172 100 0 n#46 eapply.apply7.OCLC 1056 1872 1360 1872 1360 1168 2624 1168 2624 1680 2672 1680 tcsEnvCad.pressure.ICID
w 1968 1204 100 0 n#45 eapply.apply7.OUTC 1056 1904 1392 1904 1392 1200 2592 1200 2592 1760 2672 1760 tcsEnvCad.pressure.DIR
w 1456 2340 100 0 n#43 eapply.apply7.INMB 672 1936 416 1936 416 2336 2544 2336 2544 1696 2416 1696 tcsEnvCad.humidity.MESS
w 1440 2290 100 0 n#42 eapply.apply7.INPB 672 1968 464 1968 464 2288 2464 2288 2464 1776 2416 1776 tcsEnvCad.humidity.VAL
w 1428 1608 100 0 n#41 eapply.apply7.OCLB 1056 1936 1424 1936 1424 1232 2080 1232 2080 1696 2192 1696 tcsEnvCad.humidity.ICID
w 1460 1640 100 0 n#13 eapply.apply7.OUTB 1056 1968 1456 1968 1456 1264 2032 1264 2032 1776 2192 1776 tcsEnvCad.humidity.DIR
w 406 2098 100 0 n#4 inhier.ICID.P 112 2000 176 2000 176 2096 672 2096 eapply.apply7.CLID
w 374 2130 100 0 n#3 inhier.DIR.P 112 2128 672 2128 eapply.apply7.DIR
w 2030 2100 100 0 n#2 eapply.apply7.MESS 1056 2096 3040 2096 3040 2000 3136 2000 outhier.MESS.p
w 2078 2130 100 0 n#1 eapply.apply7.VAL 1056 2128 3136 2128 outhier.VAL.p
s 2832 320 200 0 Gemini TCS
s 2752 224 100 0 TCS commands
s 2624 2576 100 0 $Id: tcsEnvCommands.sch,v 1.4 2002/01/17 14:34:01 ajf Exp $
[cell use]
use tcsEnvCad 1624 1352 100 0 useWS
xform 0 1712 1632
p 1600 1312 100 0 1 seta:cad useWS
p 1600 1280 100 0 1 setb:snam tcsCAD$(cad)
p 1600 1248 100 0 1 setc:slowout 0.0
p 1600 1216 100 0 1 setd:currout $(tcs)ak:envmode
p 1600 1184 100 0 1 sete:otherout 0.0
use tcsEnvCad 2696 1336 100 0 pressure
xform 0 2784 1616
p 2672 1296 100 0 1 seta:cad pressure
p 2672 1264 100 0 1 setb:snam tcsCAD$(cad)
p 2672 1232 100 0 1 setc:slowout $(tcs)ak:press
p 2672 1200 100 0 1 setd:currout $(tcs)localRemote.J
p 2672 1168 100 0 1 sete:otherout 0.0
use tcsEnvCad 2216 1352 100 0 humidity
xform 0 2304 1632
p 2192 1312 100 0 1 seta:cad humidity
p 2192 1280 100 0 1 setb:snam tcsCAD$(cad)
p 2192 1248 100 0 1 setc:slowout $(tcs)ak:rh
p 2192 1216 100 0 1 setd:currout $(tcs)localRemote.J
p 2192 1184 100 0 1 sete:otherout $(tcs)calcDewPoint.B
use tcsEnvCad 1624 488 100 0 temperature
xform 0 1712 768
p 1600 448 100 0 1 seta:cad temperature
p 1600 416 100 0 1 setb:snam tcsCAD$(cad)
p 1600 384 100 0 1 setc:slowout $(tcs)ak:temp
p 1600 318 100 0 1 setd:currout $(tcs)localRemote.J
p 1600 350 100 0 1 sete:otherout $(tcs)calcDewPoint.A
use outhier 3128 1960 100 0 MESS
xform 0 3120 2000
use outhier 3128 2088 100 0 VAL
xform 0 3120 2128
use inhier 120 1960 100 0 ICID
xform 0 112 2000
use inhier 120 2088 100 0 DIR
xform 0 112 2128
use eapply 696 1496 100 0 apply7
xform 0 864 1856
p 812 1540 100 0 0 DESC:Second apply for TCS commands
use bc200tr -32 104 -100 0 frame
xform 0 1648 1408
[comments]
