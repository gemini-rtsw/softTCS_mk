[schematic2]
uniq 117
[tools]
[detail]
w 1898 1419 100 0 n#116 egenSubD.egenSubD#113.OUTB 1808 1408 2048 1408 2048 400 1904 400 eaos.currentAirPressure.VAL
w 1730 1643 100 0 n#115 egenSubD.egenSubD#113.OUTA 1808 1472 1920 1472 1920 1632 1600 1632 1600 1776 1696 1776 eaos.akpress.SLNK
w 1114 1211 100 0 n#114 eais.wsPressure.FLNK 848 1200 1440 1200 1440 800 1520 800 egenSubD.egenSubD#113.SLNK
w 554 443 100 0 n#109 egenSubD.egenSubD#106.OUTB 432 432 736 432 736 352 960 352 960 224 848 224 eaos.currentRH.VAL
w 602 507 100 0 n#108 egenSubD.egenSubD#106.OUTA 432 496 832 496 832 416 1056 416 1056 304 1136 304 eaos.akrh.SLNK
w -54 -165 100 0 n#107 eais.wsHumidity.FLNK -368 464 -192 464 -192 -176 144 -176 egenSubD.egenSubD#106.SLNK
w 402 1739 100 0 n#105 egenSubD.egenSubD#102.OUTB 288 1728 576 1728 576 1664 832 1664 832 1536 768 1536 eaos.currentExternalTemp.VAL
w 402 1803 100 0 n#104 egenSubD.egenSubD#102.OUTA 288 1792 576 1792 576 1776 672 1776 eaos.akt.SLNK
w -278 1211 100 0 n#103 eais.wsTemperature.FLNK -400 1200 -96 1200 -96 1120 0 1120 egenSubD.egenSubD#102.SLNK
w 2010 1787 100 0 p eaos.akpress.VAL 1952 1776 2128 1776 outhier.p.p
w 980 1819 100 0 t eaos.akt.VAL 928 1776 976 1776 976 1872 1040 1872 outhier.t.p
w 1524 179 100 0 rh eaos.akrh.VAL 1392 304 1520 304 1520 64 1728 64 outhier.rh.p
w -120 722 100 0 n#81 ebos.envmode.VAL -656 720 464 720 464 1152 592 1152 eais.wsPressure.SDIS
w -696 610 100 0 n#81 junction -544 720 -544 608 -800 608 -800 416 -624 416 eais.wsHumidity.SDIS
w -696 962 100 0 n#81 junction -544 720 -544 960 -800 960 -800 1152 -656 1152 eais.wsTemperature.SDIS
w 616 898 100 0 n#81 junction 464 896 816 896 tcsDewPoint.tcsDewPoint#82.SDIS
w 552 722 100 0 n#81 junction 464 720 688 720 688 608 816 608 tcsWindSpeed.tcsWindSpeed#90.SDIS
w 52 272 100 0 n#79 eais.humidDefault.VAL -272 64 48 64 48 432 144 432 egenSubD.egenSubD#106.INPD
w -152 180 100 0 n#78 eais.humidMin.VAL -272 176 16 176 16 464 144 464 egenSubD.egenSubD#106.INPC
w -168 290 100 0 n#77 eais.humidMax.VAL -272 288 -16 288 -16 496 144 496 egenSubD.egenSubD#106.INPB
w 1428 1512 100 0 n#76 eais.pressDefault.VAL 1392 1568 1424 1568 1424 1408 1520 1408 egenSubD.egenSubD#113.INPD
w 1442 1584 100 0 n#75 eais.pressMin.VAL 1392 1680 1440 1680 1440 1440 1520 1440 egenSubD.egenSubD#113.INPC
w 1458 1656 100 0 n#74 eais.pressMax.VAL 1392 1792 1456 1792 1456 1472 1520 1472 egenSubD.egenSubD#113.INPB
w -208 1540 100 0 n#73 eais.tempDefault.VAL -288 1536 -80 1536 -80 1728 0 1728 egenSubD.egenSubD#102.INPD
w -224 1652 100 0 n#72 eais.tempMin.VAL -288 1648 -112 1648 -112 1760 0 1760 egenSubD.egenSubD#102.INPC
w -152 1794 100 0 n#71 eais.tempMax.VAL -288 1760 -256 1760 -256 1792 0 1792 egenSubD.egenSubD#102.INPB
w 1312 1508 100 0 n#54 eais.wsPressure.VAL 848 1168 1152 1168 1152 1504 1520 1504 egenSubD.egenSubD#113.INPA
w -120 530 100 0 n#48 eais.wsHumidity.VAL -368 432 -336 432 -336 528 144 528 egenSubD.egenSubD#106.INPA
w -172 1520 100 0 n#46 eais.wsTemperature.VAL -400 1168 -176 1168 -176 1824 0 1824 egenSubD.egenSubD#102.INPA
w -784 484 100 0 n#10 inhier.c#7.P -896 480 -624 480 eais.wsHumidity.INP
w 462 1218 100 0 n#9 inhier.c#6.P 368 1216 592 1216 eais.wsPressure.INP
w -794 1218 100 0 n#8 inhier.c#5.P -896 1216 -656 1216 eais.wsTemperature.INP
s 1616 1872 100 0 $Id: tcsEnviron.sch,v 1.3 2001/05/18 16:09:59 cjm Exp $
s 1744 -288 100 0 Gemini Telescope Control System
s 1664 192 100 0 directly by the pressure CAD.
s 1664 224 100 0 N.B. This record can also be written to
s 480 1360 100 0 N.B. This record can also be written to directly by
s 480 1328 100 0 the temperature CAD
s 592 64 100 0 N.B. This record can also be written to directly by
s 592 32 100 0 the humidity CAD
[cell use]
use egenSubD 1520 711 100 0 egenSubD#113
xform 0 1664 1136
p 1592 1000 100 0 -1 SNAM:tcsPressConv
p 1632 704 100 1024 -1 name:$(top)convPress
p 1808 1482 75 0 -1 pproc(OUTA):PP
p 1808 1418 75 0 -1 pproc(OUTB):PP
use egenSubD 144 -265 100 0 egenSubD#106
xform 0 288 160
p 216 16 100 0 -1 SNAM:tcsHumidConv
p 256 -272 100 1024 -1 name:$(top)convHumid
p 432 506 75 0 -1 pproc(OUTA):PP
p 432 442 75 0 -1 pproc(OUTB):PP
use egenSubD 0 1031 100 0 egenSubD#102
xform 0 144 1456
p 80 1360 100 0 -1 SNAM:tcsTempConv
p 112 1024 100 1024 -1 name:$(top)convTemp
p 288 1802 75 0 -1 pproc(OUTA):PP
p 288 1738 75 0 -1 pproc(OUTB):PP
use eaos 1696 1687 100 0 akpress
xform 0 1824 1776
p 1440 1758 100 0 0 OMSL:closed_loop
p 1808 1680 100 1024 0 name:$(top)press
use eaos 672 1687 100 0 akt
xform 0 800 1776
p 416 1758 100 0 0 OMSL:closed_loop
p 896 1680 100 1024 1 name:$(top)temp
use eaos 1136 215 100 0 akrh
xform 0 1264 304
p 880 286 100 0 0 OMSL:closed_loop
p 1392 208 100 1024 1 name:$(top)rh
use eaos 536 1448 100 0 currentExternalTemp
xform 0 640 1536
p 560 1630 100 0 -1 DESC:Current temperature
p 544 1406 100 0 1 EGU:deg C
p 256 1390 100 0 0 PREC:1
p 832 1502 100 0 -1 def(OUT):$(sad)currentExternalTemp
p 816 1408 100 1024 1 name:$(tcs)$(I)
p 800 1504 75 768 -1 palrm(OUT):MS
p 768 1504 75 768 -1 pproc(OUT):PP
use eaos 616 136 100 0 currentRH
xform 0 720 224
p 640 318 100 0 -1 DESC:Current relative humidity
p 336 -18 100 0 0 DRVH:100.0
p 560 -50 100 0 0 EGU:Percentage
p 336 46 100 0 0 EGUF:100.0
p 560 110 100 0 0 HHSV:MAJOR
p 560 174 100 0 0 HIGH:70.0
p 560 238 100 0 0 HIHI:85.0
p 560 78 100 0 0 HSV:MINOR
p 336 78 100 0 0 PREC:1
p 912 190 100 0 -1 def(OUT):$(sad)currentRH
p 848 128 100 1024 1 name:$(tcs)$(I)
p 880 192 75 768 -1 palrm(OUT):MS
p 848 192 75 768 -1 pproc(OUT):PP
use eaos 1672 312 100 0 currentAirPressure
xform 0 1776 400
p 1680 494 100 0 -1 DESC:Current pressure
p 1680 270 100 0 1 EGU:millibars
p 1392 254 100 0 0 PREC:1
p 1824 334 100 0 -1 def(OUT):$(sad)currentAirPressure
p 1984 272 100 1024 1 name:$(tcs)$(I)
p 1904 368 75 768 -1 pproc(OUT):PP
use ebos -888 632 100 0 envmode
xform 0 -784 720
p -864 814 100 0 -1 DESC:Environment mode
p -1232 574 100 0 0 ONAM:LOCAL
p -1008 702 100 0 0 OSV:MINOR
p -1232 606 100 0 0 ZNAM:REMOTE
p -720 654 100 0 -1 def(OUT):$(sad)useWS
p -800 624 100 1024 0 name:$(top)$(I)
p -624 688 75 768 -1 palrm(OUT):MS
p -656 688 75 768 -1 pproc(OUT):PP
use tcsWindSpeed 840 456 100 0 tcsWindSpeed#90
xform 0 1056 576
use tcsDewPoint 840 712 100 0 tcsDewPoint#82
xform 0 1088 848
use eais -608 1104 100 0 wsTemperature
xform 0 -528 1184
p -867 1257 100 0 0 DESC:Temp in from Weather Server
p -770 1304 100 0 0 DTYP:Soft Channel
p -912 926 100 0 0 EGU:Deg C
p -912 958 100 0 0 EGUL:0
p -688 1054 100 0 0 HHSV:NO_ALARM
p -688 1118 100 0 0 HIGH:0.0
p -688 1182 100 0 0 HIHI:0.0
p -688 1022 100 0 0 HSV:NO_ALARM
p -688 958 100 0 0 LLSV:NO_ALARM
p -688 1150 100 0 0 LOLO:0.0
p -688 1086 100 0 0 LOW:0.0
p -688 990 100 0 0 LSV:NO_ALARM
p -912 1022 100 0 0 PREC:2
p -608 1070 100 0 1 SCAN:1 second
p -848 1246 100 0 -1 def(INP):$(ws)temp
p -912 716 100 0 0 typ(FLNK):path
use eais 616 1112 100 0 wsPressure
xform 0 720 1184
p 381 1257 100 0 0 DESC:Pressure in millibars
p 336 926 100 0 0 EGU:mbars
p 560 1118 100 0 0 HIGH:1100.0
p 560 1022 100 0 0 HSV:MINOR
p 560 1086 100 0 0 LOW:400.0
p 560 990 100 0 0 LSV:MINOR
p 336 1022 100 0 0 PREC:2
p 608 1086 100 0 1 SCAN:1 second
p 336 1246 100 0 -1 def(INP):$(ws)press
use eais -600 376 100 0 wsHumidity
xform 0 -496 448
p -880 94 100 0 0 ASLO:1
p -672 526 100 0 -1 DESC:RH in from Weather Server
p -738 568 100 0 0 DTYP:Soft Channel
p -880 190 100 0 0 EGU:0
p -656 382 100 0 0 HIGH:0.0
p -656 286 100 0 0 HSV:NO_ALARM
p -656 350 100 0 0 LOW:0.0
p -656 254 100 0 0 LSV:NO_ALARM
p -880 286 100 0 0 PREC:5
p -832 382 100 0 1 SCAN:1 second
p -864 494 100 0 -1 def(INP):$(ws)humid
use eais -704 1776 100 0 tempMax
xform 0 -416 1776
use eais -704 1664 100 0 tempMin
xform 0 -416 1664
use eais -736 1568 100 0 tempDefault
xform 0 -416 1552
use eais 1160 1512 100 0 pressDefault
xform 0 1264 1584
use eais 1296 1744 100 0 pressMin
xform 0 1264 1696
use eais 1216 1872 100 0 pressMax
xform 0 1264 1808
use eais -704 304 100 0 humidMax
xform 0 -400 304
use eais -704 192 100 0 humidMin
xform 0 -400 192
use eais -736 80 100 0 humidDefault
xform 0 -400 80
use outhier 1720 24 100 0 rh
xform 0 1712 64
use outhier 1032 1832 100 0 t
xform 0 1024 1872
use outhier 2120 1736 100 0 p
xform 0 2112 1776
use inhier -888 1176 100 0 c#5
xform 0 -896 1216
use inhier 376 1176 100 0 c#6
xform 0 368 1216
use inhier -888 440 100 0 c#7
xform 0 -896 480
use bc200tr -1088 -568 -100 0 frame
xform 0 592 736
p -1376 -2 100 0 0 INAM:tcsNullInit
p -1376 -34 100 0 0 SNAM:
[comments]
