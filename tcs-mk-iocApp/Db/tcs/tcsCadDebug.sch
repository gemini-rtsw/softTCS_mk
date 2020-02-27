[schematic2]
uniq 184
[tools]
[detail]
w 1234 -158 100 0 n#180 estringouts.debugString1.OUT 864 -160 1664 -160 1664 64 junction
w 1738 66 100 0 n#180 embbis.debugLevel.VAL 1568 64 1968 64 outhier.DBGLEVEL.p
w 346 -110 100 0 n#178 junction 144 112 144 -112 608 -112 estringouts.debugString1.DOL
w 146 614 100 0 n#178 ecad8.ecad8#23.VALA 80 1056 144 1056 144 112 608 112 estringouts.debugString.DOL
w 714 -30 100 0 n#183 estringouts.debugString.FLNK 864 96 992 96 992 -32 496 -32 496 -144 608 -144 estringouts.debugString1.SLNK
w 1042 242 100 0 n#177 estringouts.AOStart.FLNK 1568 352 1648 352 1648 240 496 240 496 80 608 80 estringouts.debugString.SLNK
w 202 610 100 0 n#176 ecad8.ecad8#23.VALH 80 608 384 608 384 368 608 368 estringouts.AODebug.DOL
w 962 354 100 0 n#175 estringouts.AODebug.FLNK 864 352 1120 352 1120 336 1312 336 estringouts.AOStart.SLNK
w 1042 466 100 0 n#174 estringouts.M1Start.FLNK 1568 576 1648 576 1648 464 496 464 496 336 608 336 estringouts.AODebug.SLNK
w 962 578 100 0 n#173 estringouts.M1Debug.FLNK 864 576 1120 576 1120 560 1312 560 estringouts.M1Start.SLNK
w 226 674 100 0 n#172 ecad8.ecad8#23.VALG 80 672 432 672 432 592 608 592 estringouts.M1Debug.DOL
w 1042 690 100 0 n#171 estringouts.M2Start.FLNK 1568 800 1648 800 1648 688 496 688 496 560 608 560 estringouts.M1Debug.SLNK
w 962 802 100 0 n#170 estringouts.M2Debug.FLNK 864 800 1120 800 1120 784 1312 784 estringouts.M2Start.SLNK
w 226 738 100 0 n#169 ecad8.ecad8#23.VALF 80 736 432 736 432 816 608 816 estringouts.M2Debug.DOL
w 1042 914 100 0 n#168 estringouts.AgStart.FLNK 1568 1024 1648 1024 1648 912 496 912 496 784 608 784 estringouts.M2Debug.SLNK
w 962 1026 100 0 n#167 estringouts.AgDebug.FLNK 864 1024 1120 1024 1120 1008 1312 1008 estringouts.AgStart.SLNK
w 210 802 100 0 n#166 ecad8.ecad8#23.VALE 80 800 400 800 400 1040 608 1040 estringouts.AgDebug.DOL
w 1042 1138 100 0 n#165 estringouts.EcStart.FLNK 1568 1248 1648 1248 1648 1136 496 1136 496 1008 608 1008 estringouts.AgDebug.SLNK
w 962 1250 100 0 n#164 estringouts.EcDebug.FLNK 864 1248 1120 1248 1120 1232 1312 1232 estringouts.EcStart.SLNK
w 354 1094 100 0 n#163 ecad8.ecad8#23.VALD 80 864 352 864 352 1264 608 1264 estringouts.EcDebug.DOL
w 1042 1362 100 0 n#162 estringouts.CrStart.FLNK 1568 1472 1648 1472 1648 1360 496 1360 496 1232 608 1232 estringouts.EcDebug.SLNK
w 962 1474 100 0 n#161 estringouts.CrDebug.FLNK 864 1472 1120 1472 1120 1456 1312 1456 estringouts.CrStart.SLNK
w 306 1238 100 0 n#160 ecad8.ecad8#23.VALC 80 928 304 928 304 1488 608 1488 estringouts.CrDebug.DOL
w 1042 1586 100 0 n#159 estringouts.McStart.FLNK 1568 1696 1648 1696 1648 1584 496 1584 496 1456 608 1456 estringouts.CrDebug.SLNK
w 962 1698 100 0 n#158 estringouts.McDebug.FLNK 864 1696 1120 1696 1120 1680 1312 1680 estringouts.McStart.SLNK
w 258 1382 100 0 n#157 ecad8.ecad8#23.VALB 80 992 256 992 256 1712 608 1712 estringouts.McDebug.DOL
w 194 1062 100 0 n#156 ecad8.ecad8#23.STLK 80 384 192 384 192 1680 608 1680 estringouts.McDebug.SLNK
w 474 1858 100 0 n#106 ecad8.ecad8#23.MESS 80 1216 128 1216 128 1856 880 1856 outhier.MESS.p
w 466 1954 100 0 n#105 ecad8.ecad8#23.VAL 80 1248 112 1248 112 1952 880 1952 outhier.VAL.p
w -418 1220 100 0 n#8 inhier.ICID.P -640 1152 -560 1152 -560 1216 -240 1216 ecad8.ecad8#23.ICID
w -458 1250 100 0 n#7 inhier.DIR.P -640 1248 -240 1248 ecad8.ecad8#23.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -336 100 0 20 October 1996
s 1808 2000 100 0 $Id: tcsCadDebug.sch,v 1.2 2005/12/01 15:08:55 cjm Exp $
[cell use]
use estringouts 632 -216 100 0 debugString1
xform 0 736 -144
p 672 -66 100 0 -1 DESC:Debug level 
p 544 -338 100 0 0 OMSL:closed_loop
p 544 -178 100 0 0 VAL:NONE
p 944 -162 100 0 0 def(OUT):0.0
p 880 -224 100 1024 1 name:$(tcs)$(I)
p 864 -160 75 768 -1 pproc(OUT):PP
use estringouts 632 264 100 0 AODebug
xform 0 736 336
p 624 414 100 0 -1 DESC:Ao Debug level demand
p 544 142 100 0 0 OMSL:closed_loop
p 944 318 100 0 -1 def(OUT):$(ao)debug.A
p 720 256 100 1024 0 name:$(top)$(cad)$(I)
p 864 320 75 768 -1 pproc(OUT):CA
use estringouts 632 488 100 0 M1Debug
xform 0 736 560
p 624 638 100 0 -1 DESC:M1 debug level demand
p 544 366 100 0 0 OMSL:closed_loop
p 944 542 100 0 -1 def(OUT):$(m1)debug.A
p 864 480 100 1024 1 name:$(tcs)$(cad)$(I)
p 864 544 75 768 -1 pproc(OUT):CA
use estringouts 632 712 100 0 M2Debug
xform 0 736 784
p 624 862 100 0 -1 DESC:M2 debug level demand
p 544 590 100 0 0 OMSL:closed_loop
p 944 766 100 0 -1 def(OUT):$(m2)debug.A
p 864 704 100 1024 1 name:$(tcs)$(cad)$(I)
use estringouts 632 936 100 0 AgDebug
xform 0 736 1008
p 624 1086 100 0 -1 DESC:A&G Debug level demand
p 544 814 100 0 0 OMSL:closed_loop
p 944 990 100 0 -1 def(OUT):$(ag)debug.A
p 864 928 100 1024 1 name:$(tcs)$(cad)$(I)
use estringouts 632 1160 100 0 EcDebug
xform 0 736 1232
p 624 1310 100 0 -1 DESC:Enclosure debug level demand
p 544 1038 100 0 0 OMSL:closed_loop
p 944 1214 100 0 -1 def(OUT):$(ec)debug.A
p 864 1152 100 1024 1 name:$(tcs)$(cad)$(I)
use estringouts 632 1384 100 0 CrDebug
xform 0 736 1456
p 624 1534 100 0 -1 DESC:Rotator debug level demand
p 544 1262 100 0 0 OMSL:closed_loop
p 944 1438 100 0 -1 def(OUT):$(cr)debug.A
p 880 1376 100 1024 1 name:$(tcs)$(cad)$(I)
use estringouts 632 1608 100 0 McDebug
xform 0 736 1680
p 624 1758 100 0 -1 DESC:Mount debug level demand
p 544 1486 100 0 0 OMSL:closed_loop
p 944 1662 100 0 -1 def(OUT):$(mc)debug.A
p 880 1600 100 1024 1 name:$(tcs)$(cad)$(I)
use estringouts 632 8 100 0 debugString
xform 0 736 80
p 672 158 100 0 -1 DESC:Debug level 
p 544 -114 100 0 0 OMSL:closed_loop
p 544 46 100 0 0 VAL:NONE
p 944 62 100 0 -1 def(OUT):$(tcs)debugLevelS
p 880 0 100 1024 1 name:$(tcs)$(I)
p 864 64 75 768 -1 pproc(OUT):PP
use estringouts 1336 1608 100 0 McStart
xform 0 1440 1680
p 1339 1720 100 0 0 DESC:Output START to subsystem CAD
p 1248 1646 100 0 0 VAL:START
p 1664 1662 100 0 -1 def(OUT):$(mc)debug.DIR
p 1568 1600 100 1024 1 name:$(tcs)$(cad)$(I)
p 1568 1664 75 768 -1 pproc(OUT):PP
use estringouts 1336 1384 100 0 CrStart
xform 0 1440 1456
p 1339 1496 100 0 0 DESC:Output START to subsystem CAD
p 1248 1422 100 0 0 VAL:START
p 1664 1438 100 0 -1 def(OUT):$(cr)debug.DIR
p 1568 1376 100 1024 1 name:$(tcs)$(cad)$(I)
p 1568 1440 75 768 -1 pproc(OUT):PP
use estringouts 1336 1160 100 0 EcStart
xform 0 1440 1232
p 1339 1272 100 0 0 DESC:Output START to subsystem CAD
p 1248 1198 100 0 0 VAL:START
p 1664 1214 100 0 -1 def(OUT):$(ec)debug.DIR
p 1568 1152 100 1024 1 name:$(tcs)$(cad)$(I)
p 1568 1216 75 768 -1 pproc(OUT):PP
use estringouts 1336 936 100 0 AgStart
xform 0 1440 1008
p 1339 1048 100 0 0 DESC:Output START to subsystem CAD
p 1248 974 100 0 0 VAL:START
p 1664 990 100 0 -1 def(OUT):$(ag)debug.DIR
p 1568 928 100 1024 1 name:$(tcs)$(cad)$(I)
p 1568 992 75 768 -1 pproc(OUT):PP
use estringouts 1336 712 100 0 M2Start
xform 0 1440 784
p 1339 824 100 0 0 DESC:Output START to subsystem CAD
p 1248 750 100 0 0 VAL:START
p 1664 766 100 0 -1 def(OUT):$(m2)debug.DIR
p 1568 704 100 1024 1 name:$(tcs)$(cad)$(I)
p 1568 768 75 768 -1 pproc(OUT):PP
use estringouts 1336 488 100 0 M1Start
xform 0 1440 560
p 1339 600 100 0 0 DESC:Output START to subsystem CAD
p 1248 526 100 0 0 VAL:START
p 1664 542 100 0 -1 def(OUT):$(m1)debug.DIR
p 1568 480 100 1024 1 name:$(tcs)$(cad)$(I)
p 1568 544 75 768 -1 pproc(OUT):CA
use estringouts 1336 264 100 0 AOStart
xform 0 1440 336
p 1339 376 100 0 0 DESC:Output START to subsystem CAD
p 1248 302 100 0 0 VAL:START
p 1664 318 100 0 -1 def(OUT):$(ao)debug.DIR
p 1568 256 100 1024 1 name:$(tcs)$(cad)$(I)
p 1568 320 75 768 -1 pproc(OUT):CA
use embbis 1336 8 100 0 debugLevel
xform 0 1440 80
p 1344 158 100 0 -1 DESC:Debug level of TCS
p 1408 -50 100 0 1 ONST:NONE
p 1296 -50 100 0 1 ONVL:1
p 1408 -114 100 0 1 SVST:FULL
p 1296 -114 100 0 1 SVVL:7
p 1408 -82 100 0 1 THST:MIN
p 1296 -82 100 0 1 THVL:3
p 1568 0 100 1024 1 name:$(tcs)$(I)
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 1960 24 100 0 DBGLEVEL
xform 0 1952 64
use outhier 872 1912 100 0 VAL
xform 0 864 1952
use outhier 872 1816 100 0 MESS
xform 0 864 1856
use ecad8 -216 296 100 0 ecad8#23
xform 0 -80 800
p -144 1448 100 0 0 FTVA:STRING
p -144 1544 100 0 0 PREC:15
p -160 478 100 0 1 SNAM:$(snam)
p 160 958 100 0 0 def(OUTB):0.0
p 160 894 100 0 0 def(OUTC):0.0
p 160 830 100 0 0 def(OUTD):0.0
p 160 766 100 0 0 def(OUTE):0.0
p 160 702 100 0 0 def(OUTF):0.0
p 160 638 100 0 0 def(OUTG):0.0
p 160 574 100 0 0 def(OUTH):0.0
p -176 238 100 0 1 name:$(tcs)$(cad)
p 80 1024 75 768 -1 pproc(OUTA):PP
use inhier -632 1208 100 0 DIR
xform 0 -640 1248
use inhier -632 1112 100 0 ICID
xform 0 -640 1152
[comments]
