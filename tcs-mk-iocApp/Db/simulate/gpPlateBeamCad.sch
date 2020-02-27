[schematic2]
uniq 57
[tools]
[detail]
w 1336 235 100 0 n#56 efanouts.f2.LNK3 1280 224 1440 224 1440 720 1520 720 estringouts.lowBeam.SLNK
w 1320 267 100 0 n#55 efanouts.f2.LNK2 1280 256 1408 256 1408 976 1520 976 estringouts.midBeam.SLNK
w 1424 1211 100 0 n#54 efanouts.f2.LNK1 1280 288 1376 288 1376 1200 1520 1200 estringouts.upBeam.SLNK
w 840 635 100 0 n#36 junction 448 688 448 624 1280 624 1280 688 1520 688 estringouts.lowBeam.SDIS
w -200 1067 100 0 n#36 ecad20.ecad20#29.VALC -448 1056 96 1056 96 688 544 688 estringouts.lowPark.SDIS
w 824 891 100 0 n#34 junction 416 944 416 880 1280 880 1280 944 1520 944 estringouts.midBeam.SDIS
w -168 1131 100 0 n#34 ecad20.ecad20#29.VALB -448 1120 160 1120 160 944 544 944 estringouts.midPark.SDIS
w 824 1131 100 0 n#31 junction 416 1184 416 1120 1280 1120 1280 1168 1520 1168 estringouts.upBeam.SDIS
w 24 1195 100 0 n#31 ecad20.ecad20#29.VALA -448 1184 544 1184 estringouts.upPark.SDIS
w 904 395 100 0 n#53 eseqs.d.LNK2 864 384 992 384 992 208 1040 208 efanouts.f2.SLNK
w 272 171 100 0 n#44 efanouts.f.LNK5 176 160 416 160 416 720 544 720 estringouts.lowPark.SLNK
w 256 203 100 0 n#43 efanouts.f.LNK4 176 192 384 192 384 976 544 976 estringouts.midPark.SLNK
w 424 1227 100 0 n#42 efanouts.f.LNK3 176 224 352 224 352 1216 544 1216 estringouts.upPark.SLNK
w 288 267 100 0 n#41 efanouts.f.LNK2 176 256 448 256 448 96 544 96 eseqs.d.SLNK
w -360 -245 100 0 n#37 ecad20.ecad20#29.STLK -448 -256 -224 -256 -224 208 -64 208 efanouts.f.SLNK
w 832 -213 100 0 c#25 tcscar.tcscar#24.VAL 816 -224 896 -224 896 -256 976 -256 outhier.VAL.p
w 872 -181 100 2 FLNK tcscar.tcscar#24.FLNK 816 -192 976 -192 outhier.FLNK.p
s 1728 1728 100 0 gpMechCad.sch
s 1840 -464 100 0 Gemini Telescope Control System
s 1792 -512 100 0 Generic CAD/CAR for subsystem
s 1792 -544 100 0 simulators
s 160 1600 250 0 Simulated GPOL plateBeam Command
[cell use]
use efanouts 1040 71 100 0 f2
xform 0 1160 224
p 1152 64 100 1024 0 name:$(prefix)$(command):$(I)
use efanouts -40 72 100 0 f
xform 0 56 224
p -208 -580 100 0 0 PV:$(prefix)$(command):
p -128 366 100 0 1 def(LNK1):$(prefix)$(command)C:ms1.PROC
use estringouts 1520 647 100 0 lowBeam
xform 0 1648 720
p 1520 784 100 0 -1 DESC:Close the lower beam switch
p 1680 558 100 0 0 DISV:0
p 1456 686 100 0 0 VAL:CLOSED
p 1888 704 100 0 -1 def(OUT):$(prefix)carLowBeamSwitch
p 1632 640 100 1024 0 name:$(prefix)$(command):$(I)
p 1776 704 75 768 -1 pproc(OUT):PP
use estringouts 1520 903 100 0 midBeam
xform 0 1648 976
p 1520 1040 100 0 -1 DESC:Close the middle beam switch
p 1680 814 100 0 0 DISV:0
p 1456 942 100 0 0 VAL:CLOSED
p 1888 960 100 0 -1 def(OUT):$(prefix)carMidBeamSwitch
p 1632 896 100 1024 0 name:$(prefix)$(command):$(I)
p 1776 960 75 768 -1 pproc(OUT):PP
use estringouts 1520 1127 100 0 upBeam
xform 0 1648 1200
p 1520 1264 100 0 -1 DESC:Close the upper beam switch
p 1680 1038 100 0 0 DISV:0
p 1456 1166 100 0 0 VAL:CLOSED
p 1888 1184 100 0 -1 def(OUT):$(prefix)carUpBeamSwitch
p 1632 1120 100 1024 0 name:$(prefix)$(command):$(I)
p 1776 1184 75 768 -1 pproc(OUT):PP
use estringouts 544 1143 100 0 upPark
xform 0 672 1216
p 544 1280 100 0 -1 DESC:Open the park switch
p 704 1054 100 0 0 DISV:0
p 480 1182 100 0 0 VAL:OPEN
p 912 1200 100 0 -1 def(OUT):$(prefix)carUpParkSwitch
p 656 1136 100 1024 0 name:$(prefix)$(command):$(I)
p 800 1200 75 768 -1 pproc(OUT):PP
use estringouts 544 903 100 0 midPark
xform 0 672 976
p 544 1040 100 0 -1 DESC:Open the middle park switch
p 704 814 100 0 0 DISV:0
p 480 942 100 0 0 VAL:OPEN
p 912 960 100 0 -1 def(OUT):$(prefix)carMidParkSwitch
p 656 896 100 1024 0 name:$(prefix)$(command):$(I)
p 800 960 75 768 -1 pproc(OUT):PP
use estringouts 544 647 100 0 lowPark
xform 0 672 720
p 544 784 100 0 -1 DESC:Open the lower park switch
p 704 558 100 0 0 DISV:0
p 480 686 100 0 0 VAL:OPEN
p 912 704 100 0 -1 def(OUT):$(prefix)carLowParkSwitch
p 656 640 100 1024 0 name:$(prefix)$(command):$(I)
p 800 704 75 768 -1 pproc(OUT):PP
use bc200tr -1024 -744 -100 0 frame
xform 0 656 560
use ecad20 -768 -345 100 0 ecad20#29
xform 0 -608 544
p -640 1168 100 0 1 FTVA:LONG
p -640 1120 100 0 1 FTVB:LONG
p -640 1072 100 0 1 FTVC:LONG
p -768 -144 100 0 1 SNAM:tcsGpplateMoveCAD
p -656 -352 100 1024 1 name:$(prefix)$(command)
use outhier 944 -233 100 0 FLNK
xform 0 960 -192
use outhier 944 -297 100 0 VAL
xform 0 960 -256
use tcscar 400 -377 100 0 tcscar#24
xform 0 608 -256
p 464 -384 100 0 1 seta:car $(command)C
use eseqs 568 8 100 0 d
xform 0 704 256
p 640 222 100 0 1 DLY1:$(delay)
p 160 -2468 100 0 0 PV:$(prefix)$(command):
p 944 414 100 0 -1 def(LNK1):$(prefix)$(command)C:ms2.PROC
p 544 448 75 1280 -1 palrm(SELL):NMS
p 880 384 75 1024 -1 pproc(LNK2):PP
[comments]
