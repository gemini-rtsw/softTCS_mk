[schematic2]
uniq 65
[tools]
[detail]
w 328 731 100 0 n#64 estringouts.midPlateName.FLNK 480 848 576 848 576 720 128 720 128 592 224 592 estringouts.lowPlateName.SLNK
w 328 987 100 0 n#63 estringouts.upPlateName.FLNK 480 1120 576 1120 576 976 128 976 128 832 224 832 estringouts.midPlateName.SLNK
w 136 635 100 0 n#62 ecad20.ecad20#29.VALG 0 800 96 800 96 624 224 624 estringouts.lowPlateName.DOL
w 88 875 100 0 n#61 ecad20.ecad20#29.VALF 0 864 224 864 estringouts.midPlateName.DOL
w 136 1147 100 0 n#60 ecad20.ecad20#29.VALE 0 928 96 928 96 1136 224 1136 estringouts.upPlateName.DOL
w 1408 1451 100 0 n#59 estringouts.defUpPlateName.FLNK 1296 1440 1568 1440 1568 1296 1696 1296 esirs.upperPlateName.SLNK
w 1360 587 100 0 n#54 estringouts.defLowPlateName.FLNK 1280 576 1488 576 1488 384 1696 384 esirs.lowerPlateName.SLNK
w 1360 1067 100 0 n#53 estringouts.defMidPlateName.FLNK 1280 1056 1488 1056 1488 864 1696 864 esirs.middlePlateName.SLNK
w 40 -245 100 0 n#38 ecad20.ecad20#29.STLK 0 -256 128 -256 efanouts.f.SLNK
w 2016 -37 100 0 c#25 tcscar.tcscar#24.VAL 2000 -48 2080 -48 2080 -80 2160 -80 outhier.VAL.p
w 2056 -5 100 0 FLNK tcscar.tcscar#24.FLNK 2000 -16 2160 -16 outhier.FLNK.p
w 498 -264 100 0 n#15 efanouts.f.LNK2 368 -208 496 -208 496 -368 608 -368 eseqs.d.SLNK
s 1552 -528 100 0 Sciences Ltd.
s 1552 -496 100 0 Observatory
s 1552 -464 100 0 Copyright
s 160 1600 250 0 Simulation of GPOL Identify Command
s 1792 -544 100 0 command
s 1792 -512 100 0 Implementation of GPOL Identify
s 1840 -464 100 0 Gemini Telescope Control System
s 1552 1728 100 0 $Id: gpIdentifyCad.sch,v 1.1 2002/04/16 16:18:43 cjm Exp $
s -768 1568 100 0 Fields E, F and G are used to provide new plate names
s -768 1536 100 0 In the real GPOL these fields are not used.
[cell use]
use estringouts 224 519 100 0 lowPlateName
xform 0 352 592
p 224 672 100 0 -1 DESC:Name of lower plate
p 160 398 100 0 0 OMSL:closed_loop
p 400 512 100 0 0 PINI:NO
p 160 558 100 0 0 VAL:plate3
p 192 26 100 0 0 def(OUT):$(prefix)sad:lowerPlateName
p 336 512 100 1024 0 name:$(prefix)$(I)
p 480 576 75 768 -1 pproc(OUT):PP
use estringouts 1024 487 100 0 defLowPlateName
xform 0 1152 560
p 1040 640 100 0 -1 DESC:Current lower plate name
p 1232 464 100 0 1 PINI:YES
p 960 526 100 0 0 VAL:Unknown
p 992 -6 100 0 0 def(OUT):$(prefix)sad:lowerPlateName
p 1136 480 100 1024 0 name:$(prefix)$(I)
p 1280 544 75 768 -1 pproc(OUT):NPP
use estringouts 224 759 100 0 midPlateName
xform 0 352 832
p 224 912 100 0 -1 DESC:Name of middle plate
p 160 638 100 0 0 OMSL:closed_loop
p 400 752 100 0 0 PINI:NO
p 160 798 100 0 0 VAL:plate1
p 192 266 100 0 0 def(OUT):$(prefix)sad:middlePlateName
p 336 752 100 1024 0 name:$(prefix)$(I)
p 480 816 75 768 -1 pproc(OUT):PP
use estringouts 1024 967 100 0 defMidPlateName
xform 0 1152 1040
p 1040 1120 100 0 -1 DESC:Current middle plate name
p 1232 944 100 0 1 PINI:YES
p 960 1006 100 0 0 VAL:Unknown
p 992 474 100 0 0 def(OUT):$(prefix)sad:middlePlateName
p 1136 960 100 1024 0 name:$(prefix)$(I)
p 1280 1024 75 768 -1 pproc(OUT):NPP
use estringouts 224 1031 100 0 upPlateName
xform 0 352 1104
p 224 1184 100 0 -1 DESC:Name of upper plate
p 160 910 100 0 0 OMSL:closed_loop
p 400 1024 100 0 0 PINI:NO
p 160 1070 100 0 0 VAL:calibrator
p 192 538 100 0 0 def(OUT):$(prefix)sad:upperPlateName
p 336 1024 100 1024 0 name:$(prefix)$(I)
p 480 1088 75 768 -1 pproc(OUT):PP
use estringouts 1040 1351 100 0 defUpPlateName
xform 0 1168 1424
p 1056 1504 100 0 -1 DESC:Current upper plate name
p 1264 1344 100 0 1 PINI:YES
p 976 1390 100 0 0 VAL:Unknown
p 1008 858 100 0 0 def(OUT):$(prefix)sad:upperPlateName
p 1152 1344 100 1024 0 name:$(prefix)$(I)
p 1296 1408 75 768 -1 pproc(OUT):NPP
use esirs 1696 295 100 0 lowerPlateName
xform 0 1904 448
p 1808 448 100 0 -1 DESC:Lower plate name
p 1632 32 100 0 0 FDSC:
p 1808 288 100 1024 0 name:$(prefix)sad:$(I)
use esirs 1696 775 100 0 middlePlateName
xform 0 1904 928
p 1808 928 100 0 -1 DESC:Middle plate name
p 1632 512 100 0 0 FDSC:
p 1808 768 100 1024 0 name:$(prefix)sad:$(I)
use esirs 1696 1207 100 0 upperPlateName
xform 0 1904 1360
p 1808 1360 100 0 -1 DESC:Upper plate name
p 1632 944 100 0 0 FDSC:
p 1808 1200 100 1024 0 name:$(prefix)sad:$(I)
use bc200tr -1024 -744 -100 0 frame
xform 0 656 560
use ecad20 -320 -345 100 0 ecad20#29
xform 0 -160 544
p -320 -144 100 0 1 SNAM:tcsGpGenericCAD
p -208 -352 100 1024 1 name:$(prefix)$(command)
use outhier 2128 -121 100 0 VAL
xform 0 2144 -80
use outhier 2128 -57 100 0 FLNK
xform 0 2144 -16
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
p 1008 -80 100 0 1 def(LNK2):$(prefix)upPlateName.PROC
p 1008 -112 100 0 0 def(LNK3):0.0
p 1008 -144 100 0 0 def(LNK4):0.0
p 608 -16 75 1280 -1 palrm(SELL):NMS
use efanouts 152 -392 100 0 f
xform 0 248 -240
p -16 -1044 100 0 0 PV:$(prefix)$(command):
p 64 -98 100 0 1 def(LNK1):$(prefix)$(command)C:ms1.PROC
[comments]
