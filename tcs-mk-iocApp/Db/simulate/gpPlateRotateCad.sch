[schematic2]
uniq 75
[tools]
[detail]
w 408 1307 100 0 n#74 ecad20.ecad20#29.VALF 0 864 256 864 256 1296 608 1296 esirs.upperPlatePeriod.INP
w 136 619 100 0 n#73 ecad20.ecad20#29.VALJ 0 608 320 608 320 384 608 384 esirs.lowerPlatePeriod.INP
w 136 747 100 0 n#72 ecad20.ecad20#29.VALH 0 736 320 736 320 864 608 864 esirs.middlePlatePeriod.INP
w 800 539 100 0 n#71 esirs.middlePlatePeriod.FLNK 1024 864 1120 864 1120 528 528 528 528 224 608 224 esirs.lowerPlatePeriod.SLNK
w 800 1019 100 0 n#66 esirs.upperPlatePeriod.FLNK 1024 1296 1120 1296 1120 1008 528 1008 528 704 608 704 esirs.middlePlatePeriod.SLNK
w 408 -133 100 0 n#65 efanouts.f.FLNK 368 -144 496 -144 496 1136 608 1136 esirs.upperPlatePeriod.SLNK
w 40 -245 100 0 n#38 ecad20.ecad20#29.STLK 0 -256 128 -256 efanouts.f.SLNK
w 2016 -37 100 0 c#25 tcscar.tcscar#24.VAL 2000 -48 2080 -48 2080 -80 2160 -80 outhier.VAL.p
w 2056 -5 100 0 FLNK tcscar.tcscar#24.FLNK 2000 -16 2160 -16 outhier.FLNK.p
w 498 -264 100 0 n#15 efanouts.f.LNK2 368 -208 496 -208 496 -368 608 -368 eseqs.d.SLNK
s 1552 1728 100 0 $Id: gpPlateRotateCad.sch,v 1.1 2002/04/16 16:22:40 cjm Exp $
s 1840 -464 100 0 Gemini Telescope Control System
s 1792 -512 100 0 Implementation of GPOL plateRotate
s 1792 -544 100 0 command
s 160 1600 250 0 Simulation of GPOL plateRotate Command
s 1552 -464 100 0 Copyright
s 1552 -496 100 0 Observatory
s 1552 -528 100 0 Sciences Ltd.
[cell use]
use esirs 608 1047 100 0 upperPlatePeriod
xform 0 816 1200
p 720 1200 100 0 -1 DESC:Upper plate period
p 768 1152 100 0 1 EGU:seconds
p 544 784 100 0 0 FDSC:
p 544 752 100 0 0 FTVL:DOUBLE
p 800 976 100 0 0 PREC:2
p 720 1040 100 1024 0 name:$(prefix)sad:$(I)
use esirs 608 615 100 0 middlePlatePeriod
xform 0 816 768
p 720 768 100 0 -1 DESC:Middle plate period
p 752 720 100 0 1 EGU:seconds
p 544 352 100 0 0 FDSC:
p 544 320 100 0 0 FTVL:DOUBLE
p 800 544 100 0 0 PREC:2
p 720 608 100 1024 0 name:$(prefix)sad:$(I)
use esirs 608 135 100 0 lowerPlatePeriod
xform 0 816 288
p 720 288 100 0 -1 DESC:Lower plate period
p 752 240 100 0 1 EGU:seconds
p 544 -128 100 0 0 FDSC:
p 544 -160 100 0 0 FTVL:LONG
p 800 64 100 0 0 PREC:2
p 720 128 100 1024 0 name:$(prefix)sad:$(I)
use bc200tr -1024 -744 -100 0 frame
xform 0 656 560
use ecad20 -320 -345 100 0 ecad20#29
xform 0 -160 544
p -320 -144 100 0 1 SNAM:tcsGpGenericCAD
p -208 -352 100 1024 1 name:$(prefix)$(command)
use outhier 2128 -57 100 0 FLNK
xform 0 2144 -16
use outhier 2128 -121 100 0 VAL
xform 0 2144 -80
use tcscar 1584 -201 100 0 tcscar#24
xform 0 1792 -80
p 1648 -208 100 0 1 seta:car $(command)C
use eseqs 632 -456 100 0 d
xform 0 768 -208
p 704 -242 100 0 1 DLY1:$(delay)
p 704 -288 100 0 0 DLY2:0.0
p 224 -2420 100 0 0 DLY3:0.0
p 224 -2452 100 0 0 DLY4:0.0
p 224 -2932 100 0 0 PV:$(prefix)$(command):
p 1008 -50 100 0 -1 def(LNK1):$(prefix)$(command)C:ms2.PROC
p 1008 -80 100 0 0 def(LNK2):0.0
p 1008 -112 100 0 0 def(LNK3):0.0
p 1008 -144 100 0 0 def(LNK4):0.0
p 608 -16 75 1280 -1 palrm(SELL):NMS
use efanouts 152 -392 100 0 f
xform 0 248 -240
p -16 -1044 100 0 0 PV:$(prefix)$(command):
p 64 -98 100 0 1 def(LNK1):$(prefix)$(command)C:ms1.PROC
[comments]
