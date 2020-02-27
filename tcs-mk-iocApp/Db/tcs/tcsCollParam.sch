[schematic2]
uniq 1325
[tools]
[detail]
w 1628 3099 100 0 n#1317 ecalcs.add.VAL 1584 3344 1632 3344 1632 2864 1744 2864 ecalcs.netint.INPA
w 1652 3347 100 0 n#1317 junction 1632 3344 1744 3344 eaos.net.DOL
w 1780 3075 100 0 n#1323 eaos.net.FLNK 2000 3344 2112 3344 2112 3072 1520 3072 1520 2480 1744 2480 ecalcs.netint.SLNK
w 1596 3379 100 0 n#1322 ecalcs.add.FLNK 1584 3376 1680 3376 1680 3312 1744 3312 eaos.net.SLNK
w -476 2539 -100 0 INCR inhier.INCR.P -576 2528 -304 2528 eais.inc.SLNK
w 4 3163 -100 0 RESET inhier.RESET.P -240 3152 320 3152 eaos.lreset.SLNK
w 2100 2555 -100 0 VAL ecalcs.netint.VAL 2032 2672 2096 2672 2096 2464 2288 2464 outhier.VAL.p
w 2124 2715 -100 0 off ecalcs.netint.FLNK 2032 2704 2288 2704 outhier.FLNK.p
w -116 3291 -100 0 LOCAL inhier.LOCAL.P -240 3280 80 3280 80 3344 320 3344 eaos.lnew.SLNK
w -116 3451 -100 0 SESSION inhier.SESSION.P -240 3440 80 3440 80 3568 320 3568 eaos.snew.SLNK
w 4 3611 -100 0 NEW inhier.NEW.P -240 3600 320 3600 eaos.snew.DOL
w 164 3483 -100 0 NEW junction 160 3600 160 3376 320 3376 eaos.lnew.DOL
w 1108 3547 100 0 n#1276 eaos.session.VAL 992 3536 1296 3536 ecalcs.add.INPA
w 620 3539 100 0 n#1291 eaos.snew.OUT 576 3536 736 3536 eaos.session.SLNK
w 1100 3355 100 0 n#1277 eaos.session.FLNK 992 3568 1104 3568 1104 3152 1296 3152 ecalcs.add.SLNK
w 1012 3347 100 0 n#1277 eaos.local.FLNK 992 3344 1104 3344 junction
w 668 3123 100 0 n#1294 eaos.upd.OUT 912 2752 992 2752 992 2944 672 2944 672 3312 junction
w 620 3315 100 0 n#1294 eaos.lnew.OUT 576 3312 736 3312 eaos.local.SLNK
w 644 3211 100 0 n#1294 eaos.lreset.OUT 576 3120 640 3120 640 3312 junction
w 548 2563 100 0 n#1302 ecalcs.adder.FLNK 496 2352 544 2352 544 2784 656 2784 eaos.upd.SLNK
w 596 2563 100 0 n#1303 ecalcs.adder.VAL 496 2320 592 2320 592 2816 656 2816 eaos.upd.DOL
w 20 2331 100 0 n#1305 eais.inc.FLNK -48 2544 16 2544 16 2128 208 2128 ecalcs.adder.SLNK
w 44 2523 100 0 n#1306 eais.inc.VAL -48 2512 208 2512 ecalcs.adder.INPA
w 516 2579 100 0 n#1297 junction 1024 3312 1024 2576 80 2576 80 2480 208 2480 ecalcs.adder.INPB
w 1156 3403 100 0 n#1297 eaos.local.VAL 992 3312 1152 3312 1152 3504 1296 3504 ecalcs.add.INPB
[cell use]
use eaos 656 2695 100 0 upd
xform 0 784 2784
p 436 2970 100 0 0 DESC:updated local value
p 624 2510 100 0 0 EGU:$(units)
p 400 2766 100 0 0 OMSL:closed_loop
p 912 2752 75 768 -1 pproc(OUT):PP
use eaos 736 3447 100 0 session
xform 0 864 3536
p 516 3722 100 0 0 DESC:session $(descr)
p 704 3262 100 0 0 EGU:$(units)
p 480 3518 100 0 0 OMSL:closed_loop
p 480 3390 100 0 0 PREC:3
use eaos 320 3479 100 0 snew
xform 0 448 3568
p 100 3754 100 0 0 DESC:New value of pointing parameter
p 288 3294 100 0 0 EGU:$(units)
p 64 3550 100 0 0 OMSL:closed_loop
p 288 3600 75 1280 -1 pproc(DOL):PP
p 576 3536 75 768 -1 pproc(OUT):PP
use eaos 736 3223 100 0 local
xform 0 864 3312
p 516 3498 100 0 0 DESC:Local adj to $(descr)
p 704 3038 100 0 0 EGU:$(units)
p 480 3294 100 0 0 OMSL:closed_loop
p 480 3166 100 0 0 PREC:3
use eaos 320 3255 100 0 lnew
xform 0 448 3344
p 100 3530 100 0 0 DESC:New value of local parameter
p 288 3070 100 0 0 EGU:$(units)
p 64 3326 100 0 0 OMSL:closed_loop
p 288 3376 75 1280 -1 pproc(DOL):PP
p 576 3312 75 768 -1 pproc(OUT):PP
use eaos 320 3063 100 0 lreset
xform 0 448 3152
p 100 3338 100 0 0 DESC:resets local parameter
p 288 2878 100 0 0 EGU:$(units)
p 64 3134 100 0 0 OMSL:closed_loop
p 576 3120 75 768 -1 pproc(OUT):PP
use eaos 1744 3223 100 0 net
xform 0 1872 3312
p 1524 3498 100 0 0 DESC:net $(descr)
p 1712 3038 100 0 0 EGU:$(units)
p 1488 3294 100 0 0 OMSL:closed_loop
p 1488 3166 100 0 0 PREC:3
p 2064 3280 100 0 -1 def(OUT):$(sad)$(sadname)
p 2000 3280 75 768 -1 pproc(OUT):PP
use inhier -256 3111 100 0 RESET
xform 0 -240 3152
use inhier -256 3559 100 0 NEW
xform 0 -240 3600
use inhier -256 3399 100 0 SESSION
xform 0 -240 3440
use inhier -256 3239 100 0 LOCAL
xform 0 -240 3280
use inhier -592 2487 100 0 INCR
xform 0 -576 2528
use ecalcs 208 2039 100 0 adder
xform 0 352 2304
p 336 2352 100 0 -1 CALC:A+B
p 1 2470 100 0 0 DESC:adds increment to current local value
p -80 2190 100 0 0 EGU:$(units)
use ecalcs 1296 3063 100 0 add
xform 0 1440 3328
p 1392 3440 100 0 -1 CALC:A+B
p 1089 3494 100 0 0 DESC:net value of $(descr)
p 1008 3214 100 0 0 EGU:
p 1008 3182 100 0 0 PREC:3
use ecalcs 1744 2391 100 0 netint
xform 0 1888 2656
p 1840 2768 100 0 -1 CALC:A*$(scale)
p 1537 2822 100 0 0 DESC:net value of $(descr)
p 1456 2542 100 0 0 EGU:
p 1856 2640 100 0 0 PREC:0
use outhier 2256 2663 100 0 FLNK
xform 0 2272 2704
use outhier 2256 2423 100 0 VAL
xform 0 2272 2464
use eborderC -832 1623 100 0 eborderC#1308
xform 0 848 2928
p 1744 1776 100 768 -1 author:D Terrett
p 1728 1744 100 768 -1 date:15 March 1999
p 1968 1824 200 768 -1 file:tcsPointParam.sch
p 2016 1776 100 0 -1 revision:$Revision: 1.1 $
use eais -304 2455 100 0 inc
xform 0 -176 2528
p -515 2601 100 0 0 DESC:increments pointing parameter
p -560 2270 100 0 0 EGU:$(units)
[comments]
