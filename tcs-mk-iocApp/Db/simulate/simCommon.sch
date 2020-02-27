[schematic2]
uniq 106
[tools]
[detail]
w 1202 1515 100 0 n#105 esels.InPosSelect.FLNK 1184 1504 1280 1504 1280 1312 1376 1312 esirs.inPosition.SLNK
w 1250 1483 100 0 n#104 esels.InPosSelect.VAL 1184 1472 1376 1472 esirs.inPosition.INP
w 674 1387 100 0 n#103 ebos.InPosFake.VAL 640 1376 768 1376 768 1616 896 1616 esels.InPosSelect.INPB
w 578 1547 100 0 INPOS inhier.INPOS.P 480 1536 736 1536 736 1648 896 1648 esels.InPosSelect.INPA
w 746 1691 100 0 n#101 ebos.InPosOverride.VAL 656 1680 896 1680 esels.InPosSelect.NVL
w -2216 -805 100 0 n#96 ecalcs.present.FLNK -2448 -624 -2288 -624 -2288 -816 -2096 -816 esirs.heartBeat.SLNK
w -2624 -366 100 0 n#51 ecalcs.present.VAL -2448 -656 -2352 -656 -2352 -368 -2848 -368 -2848 -464 -2736 -464 ecalcs.present.INPA
w -2248 -645 100 0 n#51 junction -2352 -656 -2096 -656 esirs.heartBeat.INP
w -1520 1012 100 0 n#92 tcscar.tcscar#4.FLNK -1344 1248 -1200 1248 -1200 1008 -1792 1008 -1792 800 -1616 800 efanouts.efanouts#83.SLNK
w -140 -48 100 0 n#62 genericcad.genericcad#33.VLNK -160 -240 -144 -240 -144 96 junction
w -1168 -94 100 0 n#62 genericcad.genericcad#32.VLNK -1824 -96 -464 -96 -464 96 junction
w -1152 226 100 0 n#62 genericcad.genericcad#48.VLNK -1824 240 -1792 240 -1792 224 -464 224 junction
w -1160 578 100 0 n#62 simDatum.simDatum#81.VLNK -1808 576 -464 576 -464 416 junction
w -462 280 100 0 n#62 genericcad.genericcad#23.VLNK -704 416 -464 416 -464 96 junction
w -352 98 100 0 n#62 genericcad.genericcad#30.VLNK -704 112 -672 112 -672 96 16 96 esels.simCommonSel.SLNK
w -1166 736 100 0 n#62 efanouts.efanouts#83.LNK2 -1376 848 -1168 848 -1168 576 junction
w -1527 194 100 0 n#90 genericcad.genericcad#48.FLNK -1822 209 -1790 209 -1790 192 -1216 192 junction
w -1543 -125 100 0 n#90 genericcad.genericcad#32.FLNK -1822 -127 -1216 -127 junction
w -1212 8 100 0 n#90 efanouts.efanouts#83.LNK1 -1376 880 -1216 880 -1216 -912 -1104 -912 egenSub.simStop.SLNK
w -1535 547 100 0 n#90 simDatum.simDatum#81.FLNK -1806 545 -1216 545 junction
w -656 628 100 0 n#82 tcscar.tcscar#4.VAL -1344 1216 -944 1216 -944 624 -320 624 -320 288 16 288 esels.simCommonSel.INPG
w -744 -238 100 0 n#80 egenSub.simStop.OUTA -816 -240 -624 -240 outhier.c#79.p
w 320 338 100 0 n#72 esels.simCommonSel.FLNK 304 336 384 336 384 400 464 400 outhier.FLNK.p
w 360 306 100 0 n#68 esels.simCommonSel.VAL 304 304 464 304 outhier.VAL.p
w -108 24 100 0 n#60 genericcad.genericcad#33.VAL -160 -320 -112 -320 -112 320 16 320 esels.simCommonSel.INPF
w -664 -44 100 0 n#59 genericcad.genericcad#32.VAL -1824 -176 -1104 -176 -1104 -48 -176 -48 -176 352 16 352 esels.simCommonSel.INPE
w -480 34 100 0 n#58 genericcad.genericcad#30.VAL -704 32 -208 32 -208 384 16 384 esels.simCommonSel.INPD
w -672 274 100 0 n#57 genericcad.genericcad#48.VAL -1824 160 -1072 160 -1072 272 -224 272 -224 416 16 416 esels.simCommonSel.INPC
w -504 338 100 0 n#56 genericcad.genericcad#23.VAL -704 336 -256 336 -256 448 16 448 esels.simCommonSel.INPB
w -992 498 100 0 n#53 simDatum.simDatum#81.VAL -1808 496 -128 496 -128 480 16 480 esels.simCommonSel.INPA
w -1960 1058 100 0 n#42 ecad2.init.STLK -2032 1056 -1840 1056 -1840 1152 -1760 1152 tcscar.tcscar#4.START
s 1152 -880 100 0 Common subsystem CAD/CAR records
s 1136 -736 100 0 Gemini Telescope Control System
s -2032 -480 100 0 This record is currently only
s -2032 -512 100 0 relevant for Altair
[cell use]
use ebos 384 1287 100 0 InPosFake
xform 0 512 1376
p 368 1472 100 0 -1 DESC:Fake in position signal
p 64 1230 100 0 0 ONAM:inpos
p 64 1262 100 0 0 ZNAM:outpos
p 496 1280 100 1024 0 name:$(top)$(subsys)$(I)
use ebos 400 1591 100 0 InPosOverride
xform 0 528 1680
p 400 1760 100 0 -1 DESC:Select in position source
p 80 1534 100 0 0 ONAM:enable
p 80 1566 100 0 0 ZNAM:disable
p 512 1584 100 1024 0 name:$(top)$(subsys)$(I)
use esels 896 1191 100 0 InPosSelect
xform 0 1040 1456
p 689 1654 100 0 0 DESC:Over ride inPosition status
p 1056 1248 100 0 1 SCAN:1 second
p 1056 1200 100 0 1 SELM:Specified
p 1008 1184 100 1024 0 name:$(top)$(subsys)$(I)
use esirs 1400 1224 100 0 inPosition
xform 0 1584 1376
p 1327 1120 100 0 0 DESC:inPosition SIR record in simulation
p 1327 1104 100 0 0 FDSC:
p 1327 896 100 0 0 FTVL:LONG
p 1456 1534 100 0 1 PV:$(top)$(subsys)
p 1568 1088 100 0 0 SCAN:Passive
use esirs -456 -856 100 0 followS
xform 0 -272 -704
p -529 -1184 100 0 0 FTVL:STRING
p -529 -1536 100 0 0 LLSV:MAJOR
p -529 -1344 100 0 0 LOLO:0.5
p -529 -1408 100 0 0 LOW:0.5
p -529 -1504 100 0 0 LSV:MAJOR
p -368 -546 100 0 1 PV:$(top)$(subsys)
use esirs -728 744 100 0 health
xform 0 -544 896
p -801 640 100 0 0 DESC:MC health record in simulation
p -801 624 100 0 0 FDSC:MC health (simulation)
p -616 808 100 0 1 FTVL:$(ft)
p -672 1054 100 0 1 PV:$(top)$(subsys)
use esirs -728 1160 100 0 state
xform 0 -544 1312
p -801 1056 100 0 0 DESC:Application state
p -801 1040 100 0 0 FDSC:The internal state of the application
p -801 832 100 0 0 FTVL:LONG
p -672 1470 100 0 1 PV:$(top)$(subsys)
use esirs -2096 -905 100 0 heartBeat
xform 0 -1888 -752
p -2000 -592 100 0 -1 DESC:Heart beat record
p -2160 -1200 100 0 0 FTVL:LONG
p -1984 -912 100 1024 0 name:$(prefix)sad:$(I)
use inhier 464 1495 100 0 INPOS
xform 0 480 1536
use efanouts -1592 664 100 0 efanouts#83
xform 0 -1496 816
p -1504 656 100 1024 1 name:$(top)$(subsys)initFan
use simDatum -2072 440 100 0 simDatum#81
xform 0 -1944 536
p -2016 702 100 0 0 seta:prefix $(top)$(subsys)
p -2080 686 100 0 -1 setc:delay 5.0
p -2080 654 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2080 622 100 0 -1 sete:outa 0.0
use outhier -632 -280 100 0 c#79
xform 0 -640 -240
use outhier 456 360 100 0 FLNK
xform 0 448 400
use outhier 464 256 160 0 VAL
xform 0 448 304
use bd200tr -3200 -1256 -100 0 frame
xform 0 -560 448
use egenSub -1080 -1000 100 0 simStop
xform 0 -960 -576
p -1327 -1227 100 0 0 FTVA:STRING
p -1024 -786 100 0 0 INAM:tcsSimNullInit
p -1327 -1131 100 0 0 PV:$(top)$(subsys)
p -1040 -786 100 0 -1 SNAM:tcs$(snam)Stop
p -800 -194 100 0 -1 def(OUTA):$(top)$(subsys)followS.VAL
p -816 -230 75 0 -1 pproc(OUTA):PP
use esels -16 32 100 0 simCommonSel
xform 0 160 288
p -207 -107 100 0 0 PV:$(top)$(subsys)
p 112 318 100 0 -1 SELM:High Signal
use ecalcs -2712 -936 100 0 present
xform 0 -2592 -672
p -2608 -706 100 0 -1 CALC:A+1
p -2768 -962 100 0 1 PV:$(top)$(subsys)
p -2640 -754 100 0 -1 SCAN:1 second
use genericcad -2088 104 100 0 genericcad#48
xform 0 -1960 200
p -2032 366 100 0 0 seta:prefix $(top)$(subsys)
p -2096 382 100 0 -1 setb:command reboot
p -2096 350 100 0 -1 setc:delay 0.3
p -2096 318 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2096 286 100 0 -1 sete:outa 0.0
use genericcad -2088 -232 100 0 genericcad#32
xform 0 -1960 -136
p -2032 30 100 0 0 seta:prefix $(top)$(subsys)
p -2096 46 100 0 -1 setb:command stop
p -2096 14 100 0 -1 setc:delay 1.0
p -2096 -18 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2096 -50 100 0 -1 sete:outa 0.0
use genericcad -968 280 100 0 genericcad#23
xform 0 -840 376
p -912 542 100 0 0 seta:prefix $(top)$(subsys)
p -912 510 100 0 -1 setb:command test
p -912 478 100 0 -1 setc:delay 3.0
p -912 446 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -912 414 100 0 0 sete:outa 0.0
use genericcad -968 -24 100 0 genericcad#30
xform 0 -840 72
p -912 238 100 0 0 seta:prefix $(top)$(subsys)
p -1008 238 100 0 -1 setb:command follow
p -1008 206 100 0 -1 setc:delay 0.0
p -1008 174 100 0 -1 setd:snam tcs$(snam)FollowCAD
p -1008 142 100 0 -1 sete:outa $(top)$(subsys)followS.VAL
use genericcad -424 -376 100 0 genericcad#33
xform 0 -296 -280
p -448 -416 100 0 0 seta:prefix $(top)$(subsys)
p -448 -130 100 0 -1 setb:command debug
p -448 -162 100 0 -1 setc:delay 0.1
p -448 -194 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -448 -448 100 0 0 sete:outa 0.0
use ecad2 -2328 968 100 0 init
xform 0 -2192 1280
p -2384 928 100 0 0 PV:$(top)$(subsys)
p -2336 1150 100 0 -1 SNAM:tcs$(snam)GenericCAD
use tcscar -1736 1080 100 0 tcscar#4
xform 0 -1552 1184
p -1696 1070 100 0 -1 seta:prefix $(top)$(subsys)
p -1696 1038 100 0 -1 setb:car initC
[comments]
