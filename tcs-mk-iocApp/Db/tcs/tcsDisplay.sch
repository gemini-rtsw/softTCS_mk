[schematic2]
uniq 13
[tools]
[detail]
w 2018 427 100 0 n#1 egenSub.egenSub#132.VALB 1856 672 1952 672 1952 416 2144 416 eaos.eaos#136.DOL
w 2242 555 100 0 n#2 eaos.eaos#135.FLNK 2400 736 2528 736 2528 544 2016 544 2016 384 2144 384 eaos.eaos#136.SLNK
w 1970 747 100 0 n#3 egenSub.egenSub#132.VALA 1856 736 2144 736 eaos.eaos#135.DOL
w 2034 715 100 0 n#4 egenSub.egenSub#132.FLNK 1856 0 1984 0 1984 704 2144 704 eaos.eaos#135.SLNK
w 2 811 100 0 n#5 efanouts.displayScan.FLNK -64 800 128 800 128 640 224 640 tcsDisplayAzEl.tcsDisplayAzEl#128.SLNK
w 1850 1227 100 0 n#6 egenSubD.egenSubD#123.VALA 1696 1792 1792 1792 1792 1216 1968 1216 esirs.mountEqx.INP
w 1834 1547 100 0 n#7 egenSubD.egenSubD#123.FLNK 1696 1056 1760 1056 1760 1536 1968 1536 esirs.mountFrame.SLNK
w -78 43 100 0 n#8 ebis.mcDatumL.FLNK 64 256 160 256 160 32 -256 32 -256 -80 -192 -80 ebis.crDatumL.SLNK
w 2120 1346 100 0 n#9 esirs.mountFrame.FLNK 2384 1696 2448 1696 2448 1344 1840 1344 1840 1056 1968 1056 esirs.mountEqx.SLNK
w 1224 1698 100 0 n#10 inhier.c#56.P 1120 1696 1376 1696 1376 1760 1408 1760 egenSubD.egenSubD#123.INPB
w 1240 1794 100 0 n#11 inhier.c#55.P 1120 1792 1408 1792 egenSubD.egenSubD#123.INPA
w 1490 43 100 0 n#12 tcsDisplayRADec.tcsDisplayRADec#76.FLNK 1392 736 1472 736 1472 32 1568 32 egenSub.egenSub#132.SLNK
s 640 1696 400 0 display
s 1952 1856 100 0 $Id: tcsDisplay.sch,v 1.12 2013/05/20 12:22:28 cjm Exp $
s 2208 -336 100 0 Gemini Telescope Control System
s 2192 -400 100 0 display time and telescope postion
[cell use]
use bc200tr -624 -616 -100 0 frame
xform 0 1056 688
use eaos 2144 615 100 0 eaos#135
xform 0 2272 704
p 2192 784 100 0 -1 DESC:Telescope RA
p 2112 430 100 0 0 EGU:degrees
p 1888 142 100 0 0 MDEL:0.000005
p 1888 686 100 0 0 OMSL:closed_loop
p 1888 558 100 0 0 PREC:5
p 2256 608 100 1024 -1 name:$(tcs)telescopeRA
use eaos 2144 295 100 0 eaos#136
xform 0 2272 384
p 2192 480 100 0 -1 DESC:Telescope Dec
p 2112 110 100 0 0 EGU:degrees
p 1888 -178 100 0 0 MDEL:0.000005
p 1888 366 100 0 0 OMSL:closed_loop
p 1888 238 100 0 0 PREC:5
p 2256 288 100 1024 -1 name:$(tcs)telescopeDec
use egenSub 1568 -57 100 0 egenSub#132
xform 0 1712 368
p 1584 800 100 0 -1 DESC:Generate Telescope RA & Dec
p 1280 494 100 0 0 PREC:14
p 1632 -96 100 0 1 SNAM:tcsDisplayTelescopeRADec
p 1680 -64 100 1024 -1 name:$(top)DisplayTelRADec
use tcsDisplayAzEl 256 615 100 0 tcsDisplayAzEl#128
xform 0 432 688
use esirs 1992 968 100 0 mountEqx
xform 0 2176 1120
p 2112 1278 100 0 -1 DESC:Mount equinox
p 2256 960 100 1024 1 name:$(tcs)$(I)
use esirs 1992 1448 100 0 mountFrame
xform 0 2176 1600
p 2128 1758 100 0 -1 DESC:Mount frame
p 2160 1376 100 0 0 PREC:2
p 2096 1582 100 0 -1 SNAM:sirDisplayFrame
p 1808 1744 100 0 -1 def(INP):$(tcs)drives:driveMCS.VALE
p 2304 1440 100 1024 1 name:$(tcs)$(I)
use egenSubD 1408 999 100 0 egenSubD#123
xform 0 1552 1424
p 1488 1680 100 0 1 FTVA:STRING
p 1488 1768 100 0 -1 SCAN:.5 second
p 1480 1728 100 0 -1 SNAM:tcsDisplayEqx
p 1040 1824 100 0 -1 def(INPA):$(tcs)drives:driveMCS.VALE
p 1032 1728 100 0 -1 def(INPB):$(tcs)drives:driveMCS.VALF
p 1520 992 100 1024 -1 name:$(top)DisplayEqx
use ebis -192 -153 100 0 crDatumL
xform 0 -64 -80
p -208 0 100 0 -1 DESC:Datum state of Cass Rotator
p -192 -256 100 0 1 ONAM:DATUMED
p -192 -208 100 0 1 ZNAM:NOT DATUMED
p -432 -48 100 0 -1 def(INP):$(cr)crDatumL
use ebis -192 167 100 0 mcDatumL
xform 0 -64 240
p -176 320 100 0 -1 DESC:Datum state of mount
p -192 80 100 0 1 ONAM:DATUMED
p -416 238 100 0 0 SCAN:1 second
p -192 112 100 0 1 ZNAM:NOT DATUMED
p -448 272 100 0 -1 def(INP):$(mc)mcDatumL
use tcsDisplayRADec 760 360 100 0 tcsDisplayRADec#76
xform 0 1064 576
use tcsDisplayTime 472 1160 100 0 tcsDisplayTime#75
xform 0 744 1376
use efanouts -280 552 100 0 displayScan
xform 0 -184 704
p -240 878 100 0 -1 DESC:Drive display records
p -256 510 100 0 1 SCAN:.1 second
p -32 544 100 1024 1 name:$(tcs)$(I)
use inhier 1128 1656 100 0 c#56
xform 0 1120 1696
use inhier 1128 1752 100 0 c#55
xform 0 1120 1792
[comments]
