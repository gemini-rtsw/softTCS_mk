[schematic2]
uniq 58
[tools]
[detail]
w 1832 939 100 0 n#57 ecalcs.aoMoving.VAL 2032 640 2080 640 2080 928 1632 928 1632 832 1744 832 ecalcs.aoMoving.INPA
w 1584 459 100 0 n#56 elongouts.nActs.OUT 1472 448 1744 448 ecalcs.aoMoving.SLNK
w 1016 491 100 0 n#55 elongouts.CarVals.FLNK 640 512 864 512 864 480 1216 480 elongouts.nActs.SLNK
w 1160 523 100 0 n#53 hwin.hwin#52.in 1152 512 1216 512 elongouts.nActs.DOL
w 754 1256 100 0 n#48 inhier.IVAL.P 480 1424 752 1424 752 1040 junction
w 754 768 100 0 n#48 elongouts.CarVals.OUT 640 448 752 448 752 1040 880 1040 ecars.ecars#14.IVAL
w 0 338 100 0 n#47 ecad20.ecad20#44.STLK -192 336 240 336 240 480 384 480 elongouts.CarVals.SLNK
w 288 514 100 0 n#46 hwin.hwin#22.in 240 512 384 512 elongouts.CarVals.DOL
w 1232 1042 100 0 n#42 ecars.ecars#14.VAL 1200 1040 1312 1040 outhier.VAL.p
w 1232 818 100 0 n#40 ecars.ecars#14.FLNK 1200 816 1312 816 outhier.FLNK.p
s 1632 288 100 0 Simulates moving actuators
s 1792 2368 100 0 $Id: m1FigureCad.sch,v 1.4 1999/03/12 09:23:44 cjm Exp $
s 2080 96 100 0 delay as specified macro
s 2048 128 100 0 General simulated CAD 20 with
s 32 544 100 0 BUSY
s 2048 176 100 0 Gemini Telescope Control System
[cell use]
use ecalcs 1744 359 100 0 aoMoving
xform 0 1888 624
p 1936 432 100 0 1 CALC:MAX(A-20,0)
p 1936 400 100 0 1 SCAN:1 second
p 1856 352 100 1024 0 name:$(prefix)$(I)
use hwin 960 471 100 0 hwin#52
xform 0 1056 512
p 963 504 100 0 -1 val(in):120
use elongouts 1216 391 100 0 nActs
xform 0 1344 480
p 1232 592 100 0 -1 DESC:Number of actuators
p 1056 398 100 0 0 OMSL:closed_loop
p 1328 384 100 1024 0 name:$(prefix)$(cadname)$(I)
use egenSubC 1536 1319 100 0 ZernikeSum
xform 0 1680 1744
p 1379 2059 100 0 0 DESC:Make total figure offsets available
p 1616 1264 100 0 1 SCAN:1 second
p 1616 1232 100 0 1 SNAM:tcsM1FigureTotals
p 1648 1312 100 1024 0 name:$(prefix)aos:$(I)
use inhier 488 1384 100 0 IVAL
xform 0 480 1424
use elongouts 408 392 100 0 CarVals
xform 0 512 480
p 416 590 100 0 -1 DESC:Drives CAR to BUSY
p 224 398 100 0 0 OMSL:closed_loop
p 496 384 100 1024 0 name:$(prefix)$(cadname)$(I)
p 640 448 75 768 -1 pproc(OUT):PP
use bc200tr -784 -104 -100 0 frame
xform 0 896 1200
use ecad20 -488 248 100 0 ecad20#44
xform 0 -352 1136
p -416 1712 100 0 0 FTVA:STRING
p -416 1680 100 0 0 FTVB:DOUBLE
p -416 1648 100 0 0 FTVC:DOUBLE
p -416 1616 100 0 0 FTVD:DOUBLE
p -416 1584 100 0 0 FTVE:DOUBLE
p -416 1552 100 0 0 FTVF:DOUBLE
p -416 1520 100 0 0 FTVG:DOUBLE
p -416 1488 100 0 0 FTVH:DOUBLE
p -416 1456 100 0 0 FTVI:DOUBLE
p -416 1424 100 0 0 FTVJ:DOUBLE
p -416 1392 100 0 0 FTVK:DOUBLE
p -416 1360 100 0 0 FTVL:DOUBLE
p -416 1328 100 0 0 FTVM:DOUBLE
p -416 1296 100 0 0 FTVN:DOUBLE
p -416 1264 100 0 0 FTVO:DOUBLE
p -416 976 100 0 0 PREC:14
p -560 446 100 0 1 SNAM:tcs$(substring)$(cadname)CAD
p -400 240 100 1024 1 name:$(prefix)$(cadname)
use outhier 1304 776 100 0 FLNK
xform 0 1296 816
use outhier 1304 1000 100 0 VAL
xform 0 1296 1040
use hwin 72 472 100 0 hwin#22
xform 0 144 512
p 62 440 100 0 0 typ(in):val
p 51 504 100 0 -1 val(in):$(CAR_BUSY)
use ecars 904 760 100 0 ecars#14
xform 0 1040 928
p 880 750 100 0 1 name:$(prefix)$(cadname)C
[comments]
