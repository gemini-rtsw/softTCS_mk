[schematic2]
uniq 29
[tools]
[detail]
w 1762 1578 100 0 n#1 eais.acoeff.FLNK 1752 1568 1800 1568 1800 1432 1424 1432 1424 1312 1504 1312 eais.bcoeff.SLNK
w 1770 1338 100 0 n#2 eais.bcoeff.FLNK 1760 1328 1784 1328 1784 1176 1424 1176 1424 1048 1504 1048 eais.ccoeff.SLNK
w 1770 1074 100 0 n#3 eais.ccoeff.FLNK 1760 1064 1776 1064 1776 904 1432 904 1432 784 1504 784 eais.dcoeff.SLNK
w 1770 810 100 0 n#4 eais.dcoeff.FLNK 1760 800 1760 800 1760 800 1768 800 1768 640 1424 640 1424 512 1504 512 eais.ecoeff.SLNK
w 1770 538 100 0 n#5 eais.ecoeff.FLNK 1760 528 1784 528 1784 368 1432 368 1432 256 1496 256 eais.fcoeff.SLNK
w -118 1626 100 0 n#6 inhier.Port.P -128 1616 0 1616 edfans.dfanPort.DOL
w -110 1154 100 0 n#7 inhier.Window.P -120 1144 0 1144 edfans.dfanWind.DOL
w -118 1562 100 0 n#8 inhier.SLNK.P -240 1552 -88 1552 -88 1584 0 1584 edfans.dfanPort.SLNK
w 266 1754 100 0 n#9 edfans.dfanPort.FLNK 256 1744 352 1744 352 1328 -48 1328 -48 1112 0 1112 edfans.dfanWind.SLNK
w 266 1658 100 0 n#10 edfans.dfanPort.OUTA 256 1648 392 1648 392 1416 504 1416 egenSub.getCoeffs.A
w 266 1186 100 0 n#11 edfans.dfanWind.OUTA 256 1176 408 1176 408 1352 504 1352 egenSub.getCoeffs.B
w 1762 1546 100 0 n#12 eais.acoeff.VAL 1752 1536 1952 1536 1952 1136 2200 1136 egenSub.modCoeffs.INPC
w 1770 1306 100 0 n#13 eais.bcoeff.VAL 1760 1296 1944 1296 1944 1072 2200 1072 egenSub.modCoeffs.INPD
w 1770 1042 100 0 n#14 eais.ccoeff.VAL 1760 1032 2120 1032 2120 1008 2200 1008 egenSub.modCoeffs.INPE
w 1770 778 100 0 n#15 eais.dcoeff.VAL 1760 768 2072 768 2072 944 2200 944 egenSub.modCoeffs.INPF
w 1770 506 100 0 n#16 eais.ecoeff.VAL 1760 496 2104 496 2104 880 2200 880 egenSub.modCoeffs.INPG
w 1762 250 100 0 n#17 eais.fcoeff.VAL 1752 240 1848 240 1848 704 2120 704 2120 816 2200 816 egenSub.modCoeffs.INPH
w 266 1282 100 0 n#18 edfans.dfanWind.FLNK 256 1272 352 1272 352 712 504 712 egenSub.getCoeffs.SLNK
w 802 1394 100 0 n#19 egenSub.getCoeffs.OUTA 792 1384 824 1384 hwout.hwout#1.outp
w 802 1330 100 0 n#20 egenSub.getCoeffs.OUTB 792 1320 808 1320 808 1320 824 1320 hwout.hwout#5.outp
w 802 1266 100 0 n#21 egenSub.getCoeffs.OUTC 792 1256 832 1256 hwout.hwout#9.outp
w 802 1202 100 0 n#22 egenSub.getCoeffs.OUTD 792 1192 832 1192 hwout.hwout#15.outp
w 802 1138 100 0 n#23 egenSub.getCoeffs.OUTE 792 1128 832 1128 hwout.hwout#19.outp
w 802 1074 100 0 n#24 egenSub.getCoeffs.OUTF 792 1064 808 1064 808 1064 832 1064 hwout.hwout#23.outp
w 1762 282 100 0 n#25 eais.fcoeff.FLNK 1752 272 2152 272 2152 592 2200 592 egenSub.modCoeffs.SLNK
w 266 1154 100 0 n#26 edfans.dfanWind.OUTB 256 1144 416 1144 416 1832 2064 1832 2064 1232 2200 1232 egenSub.modCoeffs.B
w 266 1626 100 0 n#27 edfans.dfanPort.OUTB 256 1616 408 1616 408 1880 2104 1880 2104 1296 2200 1296 egenSub.modCoeffs.A
w 802 690 100 0 n#28 egenSub.getCoeffs.FLNK 792 680 1304 680 1304 1552 1496 1552 eais.acoeff.SLNK
s 1968 2160 100 0 $Id: tcsGsaoiOdgwCoeffs.sch,v 1.2 2010/06/08 14:57:57 cjm Exp $
s 1984 -32 100 0 Copyright
s 1984 -64 100 0 Observatory
s 1984 -96 100 0 Sciences Ltd.
s 568 1992 200 0 Fetch TCS to GSAOI Pixel transformation coefficients
[cell use]
use bc200tr -608 -312 -100 0 frame
xform 0 1072 992
use egenSub 504 623 100 0 getCoeffs
xform 0 648 1048
p 536 1480 100 0 -1 DESC:Fetch ODGW coefficients
p 600 1400 100 0 -1 FTA:LONG
p 216 1174 100 0 0 PREC:14
p 680 584 100 0 1 SNAM:tcsProbeOdgwCoeffs
p 616 616 100 1024 0 name:$(top)p$(gsaoiport):$(odgw)$(I)
p 281 397 100 0 0 FTB:LONG
use inhier -186 1610 100 0 Port
xform 0 -128 1616
use inhier -256 1511 100 0 SLNK
xform 0 -240 1552
use inhier -206 1136 100 0 Window
xform 0 -120 1144
use eais 1496 1479 100 0 acoeff
xform 0 1624 1552
p 1480 1632 100 0 -1 DESC:Transform Coefficient
p 1240 1294 100 0 0 EGU:pixels
p 1240 1390 100 0 0 PREC:1
p 1618 1470 100 0 1 SCAN:Passive
p 1080 1616 100 0 0 def(INP):0.000000000000000e+00
p 1464 1584 75 1280 0 pproc(INP):NPP
p 1608 1472 100 1024 0 name:$(top)p$(gsaoiport):$(odgw)$(I)
use eais 1504 1239 100 0 bcoeff
xform 0 1632 1312
p 1488 1392 100 0 -1 DESC:Transform Coefficient
p 1248 1054 100 0 0 EGU:pixels
p 1248 1150 100 0 0 PREC:1
p 1626 1230 100 0 1 SCAN:Passive
p 1088 1376 100 0 0 def(INP):0.000000000000000e+00
p 1472 1344 75 1280 0 pproc(INP):NPP
p 1616 1232 100 1024 0 name:$(top)p$(gsaoiport):$(odgw)$(I)
use eais 1504 975 100 0 ccoeff
xform 0 1632 1048
p 1488 1128 100 0 -1 DESC:Transform Coefficient
p 1248 790 100 0 0 EGU:pixels
p 1248 886 100 0 0 PREC:1
p 1626 966 100 0 1 SCAN:Passive
p 1088 1112 100 0 0 def(INP):0.000000000000000e+00
p 1472 1080 75 1280 0 pproc(INP):NPP
p 1616 968 100 1024 0 name:$(top)p$(gsaoiport):$(odgw)$(I)
use eais 1504 711 100 0 dcoeff
xform 0 1632 784
p 1488 864 100 0 -1 DESC:Transform Coefficient
p 1248 526 100 0 0 EGU:pixels
p 1248 622 100 0 0 PREC:1
p 1626 702 100 0 1 SCAN:Passive
p 1088 848 100 0 0 def(INP):0.000000000000000e+00
p 1472 816 75 1280 0 pproc(INP):NPP
p 1616 704 100 1024 0 name:$(top)p$(gsaoiport):$(odgw)$(I)
use eais 1504 439 100 0 ecoeff
xform 0 1632 512
p 1488 592 100 0 -1 DESC:Transform Coefficient
p 1248 254 100 0 0 EGU:pixels
p 1248 350 100 0 0 PREC:1
p 1626 430 100 0 1 SCAN:Passive
p 1088 576 100 0 0 def(INP):0.000000000000000e+00
p 1472 544 75 1280 0 pproc(INP):NPP
p 1616 432 100 1024 0 name:$(top)p$(gsaoiport):$(odgw)$(I)
use eais 1496 183 100 0 fcoeff
xform 0 1624 256
p 1480 336 100 0 -1 DESC:Transform Coefficient
p 1240 -2 100 0 0 EGU:pixels
p 1240 94 100 0 0 PREC:1
p 1618 174 100 0 1 SCAN:Passive
p 1080 320 100 0 0 def(INP):0.000000000000000e+00
p 1464 288 75 1280 0 pproc(INP):NPP
p 1608 176 100 1024 0 name:$(top)p$(gsaoiport):$(odgw)$(I)
use egenSub 2188 505 100 0 modCoeffs
xform 0 2344 928
p 2312 496 100 1024 0 name:$(top)p$(gsaoiport):$(odgw)$(I)
p 1977 277 100 0 0 FTA:LONG
p 1977 277 100 0 0 FTB:LONG
p 2243 1369 100 0 1 SNAM:tcsModifyOdgwCoeffs
use edfans 107 1391 100 0 dfanPort
xform 0 128 1584
p 112 1360 100 1024 0 name:$(top)p$(gsaoiport):$(odgw)$(I)
p 6 1763 100 768 1 OMSL:closed_loop
use edfans 89 920 100 0 dfanWind
xform 0 128 1112
p 112 888 100 1024 0 name:$(top)p$(gsaoiport):$(odgw)$(I)
p -49 935 100 768 0 OMSL:supervisory
use hwout 824 1368 100 0 hwout#1
xform 0 920 1384
p 793 1351 100 0 -1 val(outp):$(top)p$(gsaoiport):$(odgw)acoeff
use hwout 824 1304 100 0 hwout#5
xform 0 920 1320
p 793 1287 100 0 -1 val(outp):$(top)p$(gsaoiport):$(odgw)bcoeff
use hwout 832 1240 100 0 hwout#9
xform 0 928 1256
p 801 1223 100 0 -1 val(outp):$(top)p$(gsaoiport):$(odgw)ccoeff
use hwout 832 1176 100 0 hwout#15
xform 0 928 1192
p 801 1159 100 0 -1 val(outp):$(top)p$(gsaoiport):$(odgw)dcoeff
use hwout 832 1112 100 0 hwout#19
xform 0 928 1128
p 801 1095 100 0 -1 val(outp):$(top)p$(gsaoiport):$(odgw)ecoeff
use hwout 832 1048 100 0 hwout#23
xform 0 928 1064
p 801 1031 100 0 -1 val(outp):$(top)p$(gsaoiport):$(odgw)fcoeff
[comments]
