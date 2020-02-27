[schematic2]
uniq 25
[tools]
[detail]
w 82 267 100 0 n#1 egenSub.DisplayTime.OUTH 384 720 512 720 512 256 -288 256 -288 96 -192 96 eaos.parAngle.SLNK
w -182 1467 100 0 n#2 inhier.c#124.P -336 1456 32 1456 32 1168 96 1168 egenSub.DisplayTime.INPA
w 1194 -309 100 0 n#3 egenSub.DisplayTime.VALG 384 816 544 816 544 -320 1904 -320 1904 -112 1984 -112 estringouts.engDate.DOL
w 1890 -133 100 0 n#4 estringouts.currentHAString.FLNK 1760 -128 1856 -128 1856 -144 1984 -144 estringouts.engDate.SLNK
w 2338 -117 100 0 n#5 estringouts.engDate.FLNK 2240 -128 2496 -128 outhier.FLNK.p
w 962 -277 100 0 n#6 egenSub.DisplayTime.VALF 384 880 576 880 576 -288 1408 -288 1408 -112 1504 -112 estringouts.currentHAString.DOL
w 738 -117 100 0 n#7 egenSub.DisplayTime.VALE 384 944 608 944 608 -128 928 -128 eaos.currentHA.DOL
w 1138 -5 100 0 n#8 esirs.LST.FLNK 1488 288 1552 288 1552 -16 784 -16 784 -160 928 -160 eaos.currentHA.SLNK
w 1234 -117 100 0 n#9 eaos.currentHA.FLNK 1184 -128 1344 -128 1344 -144 1504 -144 estringouts.currentHAString.SLNK
w 826 299 100 0 n#10 egenSub.DisplayTime.VALD 384 1008 640 1008 640 288 1072 288 esirs.LST.INP
w 850 715 100 0 n#11 egenSub.DisplayTime.VALC 384 1072 704 1072 704 704 1056 704 esirs.date.INP
w 1330 843 100 0 n#12 esirs.UTC.FLNK 1856 1152 1920 1152 1920 832 800 832 800 544 1056 544 esirs.date.SLNK
w 1906 1131 100 0 n#13 esirs.UTC.VAL 1856 1120 2016 1120 outhier.UTCTime.p
w 1202 1067 100 0 n#14 eaos.MJD.VAL 1152 1056 1312 1056 1312 1152 1440 1152 esirs.UTC.INP
w 1330 1003 100 0 n#15 eaos.MJD.FLNK 1152 1088 1280 1088 1280 992 1440 992 esirs.UTC.SLNK
w 546 1147 100 0 n#16 egenSub.DisplayTime.VALB 384 1136 768 1136 768 1088 896 1088 eaos.MJD.DOL
w 810 1595 100 0 n#17 egenSub.DisplayTime.VALA 384 1200 640 1200 640 1584 1040 1584 esirs.localTime.INP
w 1154 1307 100 0 n#18 esirs.localTime.FLNK 1456 1584 1568 1584 1568 1296 800 1296 800 1056 896 1056 eaos.MJD.SLNK
w 826 1435 100 0 n#19 egenSub.DisplayTime.FLNK 384 464 672 464 672 1424 1040 1424 esirs.localTime.SLNK
w -56 1115 100 0 n#20 eais.tzone.VAL -160 1104 96 1104 egenSub.DisplayTime.INPB
w 1600 258 100 0 n#21 esirs.LST.VAL 1488 256 1760 256 1760 176 2016 176 outhier.LAST.p
w 1720 674 100 0 n#22 esirs.date.VAL 1472 672 2016 672 outhier.DATE.p
w 1712 1554 100 0 n#23 esirs.localTime.VAL 1456 1552 2016 1552 outhier.LTIME.p
w 1208 418 100 0 n#24 esirs.date.FLNK 1472 704 1552 704 1552 416 912 416 912 128 1072 128 esirs.LST.SLNK
s 2192 -400 100 0 display date and time information
s 2208 -336 100 0 Gemini Telescope Control System
s 2144 1856 100 0 $Id: tcsDisplayTime.sch,v 1.5 2011/04/27 12:33:48 cjm Exp $
s 528 1760 400 0 Display Dates and Times
[cell use]
use bc200tr -624 -616 -100 0 frame
xform 0 1056 688
use eaos -192 7 100 0 parAngle
xform 0 -64 96
p -448 -434 100 0 0 ADEL:0.00005
p -208 192 100 0 -1 DESC:Current parallactic angle
p -224 -178 100 0 0 EGU:degs
p -448 -466 100 0 0 MDEL:0.00005
p -448 -50 100 0 0 PREC:4
p -80 0 100 1024 0 name:$(tcs)$(I)
use inhier -352 1415 100 0 c#124
xform 0 -336 1456
use estringouts 1504 -217 100 0 currentHAString
xform 0 1632 -144
p 1488 -64 100 0 -1 DESC:HA as sexagesimal string
p 1440 -338 100 0 0 OMSL:closed_loop
p 1440 -178 100 0 0 VAL:00:00:00.00
p 1616 -224 100 1024 0 name:$(tcs)$(I)
use estringouts 1984 -217 100 0 engDate
xform 0 2112 -144
p 1968 -64 100 0 -1 DESC:Current date
p 1920 -338 100 0 0 OMSL:closed_loop
p 1920 -178 100 0 0 VAL:2000 Jan 1
p 2096 -224 100 1024 0 name:$(tcs)$(I)
use eaos 928 -249 100 0 currentHA
xform 0 1056 -160
p 944 -64 100 0 -1 DESC:HA of source A
p 896 -434 100 0 0 EGU:hours
p 672 -178 100 0 0 OMSL:closed_loop
p 672 -306 100 0 0 PREC:14
p 1040 -256 100 1024 0 name:$(tcs)$(I)
use eaos 896 967 100 0 MJD
xform 0 1024 1056
p 912 1152 100 0 -1 DESC:MJD on UTC timescale
p 864 782 100 0 0 EGU:days
p 640 1038 100 0 0 OMSL:closed_loop
p 640 910 100 0 0 PREC:14
p 1008 960 100 1024 0 name:$(tcs)$(I)
use egenSub 96 407 100 0 DisplayTime
xform 0 240 832
p 80 1280 100 0 -1 DESC:Generate time related items
p -127 149 100 0 0 FTVC:STRING
p -127 117 100 0 0 FTVD:STRING
p 240 528 100 0 0 FTVF:STRING
p -127 21 100 0 0 FTVG:STRING
p -192 958 100 0 0 PREC:14
p 256 352 100 0 1 SCAN:.5 second
p -192 782 100 0 0 SNAM:tcsDisplayTime
p -256 1472 100 0 -1 def(INPA):$(tcs)ak:tlatm
p 384 794 75 0 -1 pproc(OUTG):NPP
p 384 730 75 0 -1 pproc(OUTH):PP
use outhier 2008 1512 100 0 LTIME
xform 0 2000 1552
use outhier 2008 1080 100 0 UTCTime
xform 0 2000 1120
use outhier 2008 632 100 0 DATE
xform 0 2000 672
use outhier 2008 136 100 0 LAST
xform 0 2000 176
use outhier 2488 -168 100 0 FLNK
xform 0 2480 -128
use esirs 1064 1336 100 0 localTime
xform 0 1248 1488
p 1088 1646 100 0 -1 DESC:Convert local time to a string
p 976 1072 100 0 0 FDSC:Convert local time to a string
p 1232 1264 100 0 0 PREC:14
p 1168 1502 100 0 -1 SNAM:sirDisplayTime
p 1312 1328 100 1024 1 name:$(tcs)$(I)
use esirs 1464 904 100 0 UTC
xform 0 1648 1056
p 1520 1214 100 0 -1 DESC:Convert UTC to a string
p 1376 640 100 0 0 FDSC:Convert UTC to a string
p 1584 1070 100 0 -1 SNAM:sirDisplayTime
p 1728 896 100 1024 1 name:$(tcs)$(I)
use esirs 1080 456 100 0 date
xform 0 1264 608
p 1200 766 100 0 -1 DESC:Current Date
p 1344 448 100 1024 1 name:$(tcs)$(I)
use esirs 1096 40 100 0 LST
xform 0 1280 192
p 1168 366 100 0 -1 DESC:Current Sidereal Time
p 1408 32 100 1024 1 name:$(tcs)$(I)
use estringins -392 552 100 0 tzonestr
xform 0 -288 624
p -448 702 100 0 -1 DESC:String to describe time zone
use eais -392 1048 100 0 tzone
xform 0 -288 1120
p -416 1214 100 0 -1 DESC:Hours West of Greenwich
p -672 862 100 0 0 EGU:hours
use egenSub 2256 788 100 0 CheckTime
xform 0 2368 1216
p 2001 565 100 0 0 FTVA:STRING
p 2001 565 100 0 0 FTVB:STRING
p 2261 1645 100 0 -1 DESC:Check on time calculation
p 2423 775 100 0 1 SNAM:tcsCheckTime
[comments]
