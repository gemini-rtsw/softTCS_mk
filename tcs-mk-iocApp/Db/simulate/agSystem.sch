[schematic2]
uniq 15
[tools]
[detail]
w 1290 635 100 0 n#1 esels.esels#107.VAL 1152 432 1248 432 1248 624 1392 624 esirs.inPosition.INP
w 1242 475 100 0 n#2 esels.esels#107.FLNK 1152 464 1392 464 esirs.inPosition.SLNK
w -1512 -366 100 0 n#3 egenSub.simStop.OUTC -1584 -368 -1392 -368 outhier.c#105.p
w -1512 -302 100 0 n#4 egenSub.simStop.OUTB -1584 -304 -1392 -304 outhier.c#102.p
w -2295 194 100 0 n#5 genericcad.genericcad#48.FLNK -2590 209 -2558 209 -2558 192 -1984 192 junction
w -1980 198 100 0 n#5 genericcad.genericcad#96.FLNK -2158 1249 -1984 1249 -1984 -912 -1872 -912 egenSub.simStop.SLNK
w -1016 98 100 0 n#6 genericcad.genericcad#23.VLNK -1472 416 -1232 416 -1232 96 -752 96 esels.simCommonSel.SLNK
w -908 -48 100 0 n#6 genericcad.genericcad#33.VLNK -928 -240 -912 -240 -912 96 junction
w -1920 226 100 0 n#6 genericcad.genericcad#48.VLNK -2592 240 -2560 240 -2560 224 -1232 224 junction
w -1672 546 100 0 n#6 genericcad.genericcad#96.VLNK -2160 1280 -2064 1280 -2064 544 -1232 544 -1232 416 junction
w -1384 658 100 0 n#7 genericcad.genericcad#96.VAL -2160 1200 -1760 1200 -1760 656 -960 656 -960 288 -752 288 esels.simCommonSel.INPG
w -1512 -238 100 0 n#8 egenSub.simStop.OUTA -1584 -240 -1392 -240 outhier.c#79.p
w -448 338 100 0 n#9 esels.simCommonSel.FLNK -464 336 -384 336 -384 400 -304 400 outhier.FLNK.p
w -408 306 100 0 n#10 esels.simCommonSel.VAL -464 304 -304 304 outhier.VAL.p
w -876 24 100 0 n#11 genericcad.genericcad#33.VAL -928 -320 -880 -320 -880 320 -752 320 esels.simCommonSel.INPF
w -1440 274 100 0 n#12 genericcad.genericcad#48.VAL -2592 160 -1840 160 -1840 272 -992 272 -992 416 -752 416 esels.simCommonSel.INPC
w -1272 338 100 0 n#13 genericcad.genericcad#23.VAL -1472 336 -1024 336 -1024 448 -752 448 esels.simCommonSel.INPB
w -528 1458 100 0 n#14 ecalcs.present.VAL -352 1168 -256 1168 -256 1456 -752 1456 -752 1360 -640 1360 ecalcs.present.INPA
s 1152 -880 100 0 Common subsystem CAD/CAR records
s 1136 -736 100 0 Gemini Telescope Control System
s -608 1568 100 0 subsys.sch
[cell use]
use bd200tr -3200 -1256 -100 0 frame
xform 0 -560 448
use esels 864 151 100 0 esels#107
xform 0 1008 416
p 1008 192 100 0 1 SCAN:1 second
p 1008 144 100 0 1 SELM:Low Signal
p 560 608 100 0 -1 def(INPA):$(p1)inPosition
p 560 560 100 0 -1 def(INPB):$(p2)inPosition
p 560 512 100 0 -1 def(INPC):$(oi)inPosition
p 976 144 100 1024 0 name:$(ag)selInPos
use esels -784 32 100 0 simCommonSel
xform 0 -608 288
p -854 32 100 0 -1 PV:$(ag)
p -656 318 100 0 -1 SELM:High Signal
use esirs -1496 744 100 0 health
xform 0 -1312 896
p -1569 640 100 0 0 DESC:MC health record in simulation
p -1569 624 100 0 0 FDSC:MC health (simulation)
p -1569 416 100 0 0 FTVL:STRING
p -1566 744 100 0 -1 PV:$(ag)
use esirs -1496 1160 100 0 state
xform 0 -1312 1312
p -1569 1056 100 0 0 DESC:Application state
p -1569 1040 100 0 0 FDSC:The internal state of the application
p -1569 832 100 0 0 FTVL:LONG
p -1566 1160 100 0 -1 PV:$(ag)
use esirs 1416 376 100 0 inPosition
xform 0 1600 528
p 1343 272 100 0 0 DESC:Application state
p 1343 256 100 0 0 FDSC:Whether all A&G probes are in position
p 1343 48 100 0 0 FTVL:LONG
p 1346 376 100 0 -1 PV:$(ag)
use outhier -1400 -280 100 0 c#79
xform 0 -1408 -240
use outhier -312 360 100 0 FLNK
xform 0 -320 400
use outhier -304 256 160 0 VAL
xform 0 -320 304
use outhier -1400 -344 100 0 c#102
xform 0 -1408 -304
use outhier -1400 -408 100 0 c#105
xform 0 -1408 -368
use genericcad -2424 1144 100 0 genericcad#96
xform 0 -2296 1240
p -2368 1406 100 0 0 seta:prefix $(ag)
p -2432 1422 100 0 -1 setb:command init
p -2432 1390 100 0 -1 setc:delay 5.0
p -2432 1358 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2432 1326 100 0 -1 sete:outa 0.0
use genericcad -2856 104 100 0 genericcad#48
xform 0 -2728 200
p -2800 366 100 0 0 seta:prefix $(ag)
p -2864 382 100 0 -1 setb:command reboot
p -2864 350 100 0 -1 setc:delay 0.3
p -2864 318 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2864 286 100 0 -1 sete:outa 0.0
use genericcad -1736 280 100 0 genericcad#23
xform 0 -1608 376
p -1680 542 100 0 0 seta:prefix $(ag)
p -1680 510 100 0 -1 setb:command test
p -1680 478 100 0 -1 setc:delay 3.0
p -1680 446 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -1680 414 100 0 0 sete:outa 0.0
use genericcad -1192 -376 100 0 genericcad#33
xform 0 -1064 -280
p -1216 -416 100 0 0 seta:prefix $(ag)
p -1216 -130 100 0 -1 setb:command debug
p -1216 -162 100 0 -1 setc:delay 0.1
p -1216 -194 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -1216 -448 100 0 0 sete:outa 0.0
use egenSub -1848 -1000 100 0 simStop
xform 0 -1728 -576
p -2095 -1227 100 0 0 FTVA:STRING
p -2095 -1227 100 0 0 FTVB:STRING
p -2095 -1259 100 0 0 FTVC:STRING
p -1792 -786 100 0 0 INAM:tcsSimNullInit
p -1918 -1000 100 0 -1 PV:$(ag)
p -1808 -786 100 0 -1 SNAM:tcs$(snam)Stop
p -1568 -194 100 0 -1 def(OUTA):$(p1)followS.VAL
p -1568 -274 100 0 -1 def(OUTB):$(p2)followS.VAL
p -1568 -338 100 0 -1 def(OUTC):$(oi)followS.VAL
p -1584 -230 75 0 -1 pproc(OUTA):PP
p -1584 -294 75 0 -1 pproc(OUTB):PP
p -1584 -358 75 0 -1 pproc(OUTC):PP
use ecalcs -616 888 100 0 present
xform 0 -496 1152
p -512 1118 100 0 -1 CALC:A+1
p -686 888 100 0 -1 PV:$(ag)
p -544 1070 100 0 -1 SCAN:1 second
[comments]
