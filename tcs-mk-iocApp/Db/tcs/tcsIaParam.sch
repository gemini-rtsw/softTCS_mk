[schematic2]
uniq 1328
[tools]
[detail]
w 1444 3515 100 0 n#1325 ecalcs.netint.INPA 1600 3504 1360 3504 1360 3296 1216 3296 eaos.session.VAL
w 1324 3339 100 0 n#1323 eaos.session.FLNK 1216 3328 1504 3328 1504 3120 1600 3120 ecalcs.netint.SLNK
w 1956 3195 -100 0 VAL ecalcs.netint.VAL 1888 3312 1952 3312 1952 3104 2144 3104 outhier.VAL.p
w 1980 3355 -100 0 off ecalcs.netint.FLNK 1888 3344 2144 3344 outhier.FLNK.p
w 350 3339 -100 0 SESSION inhier.SESSION.P 224 3328 560 3328 eaos.snew.SLNK
w 284 3467 -100 0 n#1327 inhier.NEW.P 224 3456 416 3456 416 3360 560 3360 eaos.snew.DOL
w 852 3307 100 0 n#1326 eaos.snew.OUT 816 3296 960 3296 eaos.session.SLNK
[cell use]
use eaos 960 3207 100 0 session
xform 0 1088 3296
p 740 3482 100 0 0 DESC:net $(descr)
p 928 3022 100 0 0 EGU:$(units)
p 704 3278 100 0 0 OMSL:closed_loop
p 704 3150 100 0 0 PREC:3
p 1280 3264 100 0 -1 def(OUT):$(sad)$(sadname)
p 1216 3264 75 768 -1 pproc(OUT):PP
use eaos 560 3239 100 0 snew
xform 0 688 3328
p 340 3514 100 0 0 DESC:New value of pointing parameter
p 528 3054 100 0 0 EGU:$(units)
p 304 3310 100 0 0 OMSL:closed_loop
p 528 3360 75 1280 -1 pproc(DOL):PP
p 816 3296 75 768 -1 pproc(OUT):PP
use inhier 208 3287 100 0 SESSION
xform 0 224 3328
use inhier 208 3415 100 0 NEW
xform 0 224 3456
use ecalcs 1600 3031 100 0 netint
xform 0 1744 3296
p 1696 3408 100 0 -1 CALC:A*$(scale)
p 1393 3462 100 0 0 DESC:net value of $(descr)
p 1312 3182 100 0 0 EGU:
p 1712 3280 100 0 0 PREC:0
use outhier 2112 3063 100 0 VAL
xform 0 2128 3104
use outhier 2112 3303 100 0 FLNK
xform 0 2128 3344
use eborderB -528 1943 100 0 eborderB#1308
xform 0 1152 3248
p 1744 2576 100 768 -1 author:D Terrett
p 1728 2544 100 768 -1 date:8 Aug 1997
p 1888 2624 200 768 -1 file:tcsIaParam.sch
p 1680 2672 100 0 -1 page:
p 1600 2688 100 0 -1 pages:
p 2320 2096 100 0 0 revision:$Revision: 1.1 $
p 1744 2736 150 768 -1 system:
[comments]
