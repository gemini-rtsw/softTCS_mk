[schematic2]
uniq 114
[tools]
[detail]
w -222 331 100 0 n#113 ecad20.ecad20#29.VALQ -256 320 -128 320 -128 -16 -32 -16 efanouts.f.SELL
w 1442 683 100 0 n#112 estringouts.middleSensorState.FLNK 1600 800 1696 800 1696 672 1248 672 1248 304 1344 304 estringouts.lowerSensorState.SLNK
w 1442 1131 100 0 n#111 estringouts.upperSensorState.FLNK 1600 1248 1696 1248 1696 1120 1248 1120 1248 784 1344 784 estringouts.middleSensorState.SLNK
w 1122 1243 100 0 n#110 esirs.lowerPlateAngle.FLNK 768 544 960 544 960 1232 1344 1232 estringouts.upperSensorState.SLNK
w 370 139 100 0 n#109 ecad20.ecad20#29.VALT -256 128 1056 128 1056 336 1344 336 estringouts.lowerSensorState.DOL
w 354 203 100 0 n#108 ecad20.ecad20#29.VALS -256 192 1024 192 1024 816 1344 816 estringouts.middleSensorState.DOL
w 338 267 100 0 n#107 ecad20.ecad20#29.VALR -256 256 992 256 992 1264 1344 1264 estringouts.upperSensorState.DOL
w 626 -101 100 0 n#106 efanouts.f.LNK4 160 -112 1152 -112 1152 48 1344 48 estringouts.lowerSensorOpen.SLNK
w 610 -69 100 0 n#105 efanouts.f.LNK3 160 -80 1120 -80 1120 528 1344 528 estringouts.middleSensorOpen.SLNK
w 594 -37 100 0 n#104 efanouts.f.LNK2 160 -48 1088 -48 1088 1008 1344 1008 estringouts.upperSensorOpen.SLNK
w 232 -133 100 0 n#99 efanouts.f.LNK5 160 -144 352 -144 352 -544 544 -544 eseqs.d.SLNK
w 1640 299 100 0 n#95 estringouts.lowerSensorState.OUT 1600 288 1728 288 1728 176 junction
w 1640 43 100 0 n#95 estringouts.lowerSensorOpen.OUT 1600 32 1728 32 1728 176 1824 176 estringinval.lowerSensor.SLNK
w 1640 779 100 0 n#93 estringouts.middleSensorState.OUT 1600 768 1728 768 1728 656 junction
w 1640 523 100 0 n#93 estringouts.middleSensorOpen.OUT 1600 512 1728 512 1728 656 1824 656 estringinval.middleSensor.SLNK
w 1640 1003 100 0 n#90 estringouts.upperSensorOpen.OUT 1600 992 1728 992 1728 1104 junction
w 1640 1227 100 0 n#90 estringouts.upperSensorState.OUT 1600 1216 1728 1216 1728 1104 1824 1104 estringinval.upperSensor.SLNK
w 152 555 100 0 n#72 ecad20.ecad20#29.VALJ -256 768 0 768 0 544 352 544 esirs.lowerPlateAngle.INP
w 152 1467 100 0 n#71 ecad20.ecad20#29.VALF -256 1024 0 1024 0 1456 352 1456 esirs.upperPlateAngle.INP
w -120 907 100 0 n#70 ecad20.ecad20#29.VALH -256 896 64 896 64 1024 352 1024 esirs.middlePlateAngle.INP
w 544 699 100 0 n#69 esirs.middlePlateAngle.FLNK 768 1024 896 1024 896 688 240 688 240 384 352 384 esirs.lowerPlateAngle.SLNK
w 544 1147 100 0 n#68 esirs.upperPlateAngle.FLNK 768 1456 896 1456 896 1136 240 1136 240 864 352 864 esirs.middlePlateAngle.SLNK
w -192 -85 100 0 n#38 ecad20.ecad20#29.STLK -256 -96 -80 -96 efanouts.f.SLNK
w 2000 -181 100 0 c#25 tcscar.tcscar#24.VAL 1984 -192 2064 -192 2064 -224 2144 -224 outhier.VAL.p
w 2040 -149 100 0 FLNK tcscar.tcscar#24.FLNK 1984 -160 2144 -160 outhier.FLNK.p
s 1552 1728 100 0 $Id: gpPlateAngle.sch,v 1.2 2002/05/21 21:41:37 cjm Exp $
s 1840 -464 100 0 Gemini Telescope Control System
s 1792 -512 100 0 Implementation of GPOL Identify
s 1792 -544 100 0 command
s 160 1600 250 0 Simulation of GPOL plateAngle Command
s 1552 -464 100 0 Copyright
s 1552 -496 100 0 Observatory
s 1552 -528 100 0 Sciences Ltd.
[cell use]
use estringouts 1344 231 100 0 lowerSensorState
xform 0 1472 304
p 1371 344 100 0 0 DESC:Lower Hall sensor state
p 1280 110 100 0 0 OMSL:closed_loop
p 1280 270 100 0 0 VAL:OPEN
p 1456 224 100 1024 0 name:$(prefix)$(I)
p 1600 288 75 768 -1 pproc(OUT):PP
use estringouts 1344 711 100 0 middleSensorState
xform 0 1472 784
p 1371 824 100 0 0 DESC:Middle Hall sensor state
p 1280 590 100 0 0 OMSL:closed_loop
p 1280 750 100 0 0 VAL:OPEN
p 1456 704 100 1024 0 name:$(prefix)$(I)
p 1600 768 75 768 -1 pproc(OUT):PP
use estringouts 1344 1159 100 0 upperSensorState
xform 0 1472 1232
p 1371 1272 100 0 0 DESC:Upper Hall sensor state
p 1280 1038 100 0 0 OMSL:closed_loop
p 1280 1198 100 0 0 VAL:OPEN
p 1456 1152 100 1024 0 name:$(prefix)$(I)
p 1600 1216 75 768 -1 pproc(OUT):PP
use estringouts 1344 -25 100 0 lowerSensorOpen
xform 0 1472 48
p 1371 88 100 0 0 DESC:Open string
p 1568 -32 100 0 1 PINI:YES
p 1280 14 100 0 0 VAL:OPEN
p 1456 -32 100 1024 0 name:$(prefix)$(I)
p 1600 32 75 768 -1 pproc(OUT):PP
use estringouts 1344 455 100 0 middleSensorOpen
xform 0 1472 528
p 1371 568 100 0 0 DESC:Open string
p 1584 448 100 0 1 PINI:YES
p 1280 494 100 0 0 VAL:OPEN
p 1456 448 100 1024 0 name:$(prefix)$(I)
p 1600 512 75 768 -1 pproc(OUT):PP
use estringouts 1344 935 100 0 upperSensorOpen
xform 0 1472 1008
p 1371 1048 100 0 0 DESC:Open string
p 1568 928 100 0 1 PINI:YES
p 1280 974 100 0 0 VAL:OPEN
p 1456 928 100 1024 0 name:$(prefix)$(I)
p 1600 992 75 768 -1 pproc(OUT):PP
use estringinval 1824 103 100 0 lowerSensor
xform 0 1952 176
p 1824 256 100 0 -1 DESC:Lower plate hall sensor
p 1824 270 100 0 0 VAL:OPEN
p 1936 96 100 1024 0 name:$(prefix)sad:$(I)
use estringinval 1824 583 100 0 middleSensor
xform 0 1952 656
p 1824 736 100 0 -1 DESC:Middle plate hall sensor
p 1824 750 100 0 0 VAL:OPEN
p 1936 576 100 1024 0 name:$(prefix)sad:$(I)
use estringinval 1824 1031 100 0 upperSensor
xform 0 1952 1104
p 1824 1184 100 0 -1 DESC:Upper plate hall sensor
p 1824 1198 100 0 0 VAL:OPEN
p 1936 1024 100 1024 0 name:$(prefix)sad:$(I)
use esirs 352 1207 100 0 upperPlateAngle
xform 0 560 1360
p 464 1360 100 0 -1 DESC:Upper plate angle
p 528 1296 100 0 1 EGU:degs
p 288 944 100 0 0 FDSC:
p 288 912 100 0 0 FTVL:DOUBLE
p 544 1136 100 0 0 PREC:2
p 464 1200 100 1024 0 name:$(prefix)sad:$(I)
use esirs 352 775 100 0 middlePlateAngle
xform 0 560 928
p 464 928 100 0 -1 DESC:Middle plate angle
p 512 864 100 0 1 EGU:degs
p 288 512 100 0 0 FDSC:
p 288 480 100 0 0 FTVL:DOUBLE
p 544 704 100 0 0 PREC:2
p 464 768 100 1024 0 name:$(prefix)sad:$(I)
use esirs 352 295 100 0 lowerPlateAngle
xform 0 560 448
p 464 448 100 0 -1 DESC:Lower plate angle
p 288 96 100 0 0 EGU:degs
p 288 32 100 0 0 FDSC:
p 288 0 100 0 0 FTVL:DOUBLE
p 544 224 100 0 0 PREC:2
p 464 288 100 1024 0 name:$(prefix)sad:$(I)
use bc200tr -1024 -744 -100 0 frame
xform 0 656 560
use ecad20 -576 -185 100 0 ecad20#29
xform 0 -416 704
p -592 1616 100 0 -1 DESC:Simulation of plateAngle command
p -448 320 100 0 1 FTVQ:LONG
p -512 -288 100 0 1 INAM:tcsGpInitplateAngleCAD
p -512 -240 100 0 1 SNAM:tcsGpplateAngleCAD
p -464 -192 100 1024 1 name:$(prefix)$(command)
use outhier 2112 -201 100 0 FLNK
xform 0 2128 -160
use outhier 2112 -265 100 0 VAL
xform 0 2128 -224
use tcscar 1568 -345 100 0 tcscar#24
xform 0 1776 -224
p 1632 -352 100 0 1 seta:car $(command)C
use eseqs 568 -632 100 0 d
xform 0 704 -384
p 640 -418 100 0 1 DLY1:$(delay)
p 640 -464 100 0 0 DLY2:0.0
p 160 -2596 100 0 0 DLY3:0.0
p 160 -2628 100 0 0 DLY4:0.0
p 160 -3108 100 0 0 PV:$(prefix)$(command):
p 944 -226 100 0 -1 def(LNK1):$(prefix)$(command)C:ms2.PROC
p 944 -256 100 0 1 def(LNK2):$(prefix)sad:upperPlateAngle.PROC
p 944 -288 100 0 0 def(LNK3):0.0
p 944 -320 100 0 0 def(LNK4):0.0
p 544 -192 75 1280 -1 palrm(SELL):NMS
use efanouts -56 -232 100 0 f
xform 0 40 -80
p -224 -884 100 0 0 PV:$(prefix)$(command):
p 112 -240 100 0 1 SELM:Mask
p 256 -16 100 0 1 def(LNK1):$(prefix)$(command)C:ms1.PROC
[comments]
