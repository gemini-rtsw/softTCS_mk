[schematic2]
uniq 60
[tools]
[detail]
w 1368 267 100 0 n#59 efanouts.f2.LNK3 1312 256 1472 256 1472 720 1568 720 estringouts.lowPark.SLNK
w 1352 299 100 0 n#58 efanouts.f2.LNK2 1312 288 1440 288 1440 944 1568 944 estringouts.midPark.SLNK
w 1464 1227 100 0 n#57 efanouts.f2.LNK1 1312 320 1408 320 1408 1216 1568 1216 estringouts.upPark.SLNK
w 920 395 100 0 n#55 eseqs.d.LNK2 896 384 992 384 992 240 1072 240 efanouts.f2.SLNK
w -168 1067 100 0 n#36 ecad20.ecad20#29.VALC -416 1056 128 1056 128 688 576 688 estringouts.lowBeam.SDIS
w 872 635 100 0 n#36 junction 480 688 480 624 1312 624 1312 688 1568 688 estringouts.lowPark.SDIS
w -136 1131 100 0 n#34 ecad20.ecad20#29.VALB -416 1120 192 1120 192 944 576 944 estringouts.midBeam.SDIS
w 872 875 100 0 n#34 junction 480 944 480 864 1312 864 1312 912 1568 912 estringouts.midPark.SDIS
w 56 1195 100 0 n#31 ecad20.ecad20#29.VALA -416 1184 576 1184 estringouts.upBeam.SDIS
w 872 1131 100 0 n#31 junction 480 1184 480 1120 1312 1120 1312 1184 1568 1184 estringouts.upPark.SDIS
w 304 171 100 0 n#44 efanouts.f.LNK5 208 160 448 160 448 720 576 720 estringouts.lowBeam.SLNK
w 288 203 100 0 n#43 efanouts.f.LNK4 208 192 416 192 416 976 576 976 estringouts.midBeam.SLNK
w 456 1227 100 0 n#42 efanouts.f.LNK3 208 224 384 224 384 1216 576 1216 estringouts.upBeam.SLNK
w 320 267 100 0 n#41 efanouts.f.LNK2 208 256 480 256 480 96 576 96 eseqs.d.SLNK
w -328 -245 100 0 n#37 ecad20.ecad20#29.STLK -416 -256 -192 -256 -192 208 -32 208 efanouts.f.SLNK
w 864 -213 100 0 c#25 tcscar.tcscar#24.VAL 848 -224 928 -224 928 -256 1008 -256 outhier.VAL.p
w 904 -181 100 2 FLNK tcscar.tcscar#24.FLNK 848 -192 1008 -192 outhier.FLNK.p
s 160 1600 250 0 Simulated GPOL platePark Command
s 1792 -544 100 0 simulators
s 1792 -512 100 0 Generic CAD/CAR for subsystem
s 1840 -464 100 0 Gemini Telescope Control System
s 1728 1728 100 0 gpMechCad.sch
[cell use]
use efanouts -8 72 100 0 f
xform 0 88 224
p -176 -580 100 0 0 PV:$(prefix)$(command):
p -96 366 100 0 1 def(LNK1):$(prefix)$(command)C:ms1.PROC
use efanouts 1072 103 100 0 f2
xform 0 1192 256
p 1184 96 100 1024 0 name:$(prefix)$(command):$(I)
p 1344 288 75 1280 -1 pproc(LNK2):NPP
use estringouts 576 647 100 0 lowBeam
xform 0 704 720
p 576 784 100 0 -1 DESC:Open the lower beam switch
p 736 558 100 0 0 DISV:0
p 512 686 100 0 0 VAL:OPEN
p 944 704 100 0 -1 def(OUT):$(prefix)carLowBeamSwitch
p 688 640 100 1024 0 name:$(prefix)$(command):$(I)
p 832 704 75 768 -1 pproc(OUT):PP
use estringouts 576 903 100 0 midBeam
xform 0 704 976
p 576 1040 100 0 -1 DESC:Open the middle beam switch
p 736 814 100 0 0 DISV:0
p 512 942 100 0 0 VAL:OPEN
p 944 960 100 0 -1 def(OUT):$(prefix)carMidBeamSwitch
p 688 896 100 1024 0 name:$(prefix)$(command):$(I)
p 832 960 75 768 -1 pproc(OUT):PP
use estringouts 576 1143 100 0 upBeam
xform 0 704 1216
p 576 1280 100 0 -1 DESC:Open the beam switch
p 736 1054 100 0 0 DISV:0
p 512 1182 100 0 0 VAL:OPEN
p 944 1200 100 0 -1 def(OUT):$(prefix)carUpBeamSwitch
p 688 1136 100 1024 0 name:$(prefix)$(command):$(I)
p 832 1200 75 768 -1 pproc(OUT):PP
use estringouts 1568 1143 100 0 upPark
xform 0 1696 1216
p 1568 1280 100 0 -1 DESC:Close the upper park switch
p 1728 1054 100 0 0 DISV:0
p 1504 1182 100 0 0 VAL:CLOSED
p 1936 1200 100 0 -1 def(OUT):$(prefix)carUpParkSwitch
p 1680 1136 100 1024 0 name:$(prefix)$(command):$(I)
p 1824 1200 75 768 -1 pproc(OUT):PP
use estringouts 1568 871 100 0 midPark
xform 0 1696 944
p 1568 1008 100 0 -1 DESC:Close the middle park switch
p 1728 782 100 0 0 DISV:0
p 1504 910 100 0 0 VAL:CLOSED
p 1936 928 100 0 -1 def(OUT):$(prefix)carMidParkSwitch
p 1680 864 100 1024 0 name:$(prefix)$(command):$(I)
p 1824 928 75 768 -1 pproc(OUT):PP
use estringouts 1568 647 100 0 lowPark
xform 0 1696 720
p 1568 784 100 0 -1 DESC:Close the lower park switch
p 1728 558 100 0 0 DISV:0
p 1504 686 100 0 0 VAL:CLOSED
p 1936 704 100 0 -1 def(OUT):$(prefix)carLowParkSwitch
p 1680 640 100 1024 0 name:$(prefix)$(command):$(I)
p 1824 704 75 768 -1 pproc(OUT):PP
use bc200tr -1024 -744 -100 0 frame
xform 0 656 560
use ecad20 -736 -345 100 0 ecad20#29
xform 0 -576 544
p -608 1168 100 0 1 FTVA:LONG
p -608 1120 100 0 1 FTVB:LONG
p -608 1072 100 0 1 FTVC:LONG
p -736 -144 100 0 1 SNAM:tcsGpplateMoveCAD
p -624 -352 100 1024 1 name:$(prefix)$(command)
use outhier 976 -297 100 0 VAL
xform 0 992 -256
use outhier 976 -233 100 0 FLNK
xform 0 992 -192
use tcscar 432 -377 100 0 tcscar#24
xform 0 640 -256
p 496 -384 100 0 1 seta:car $(command)C
use eseqs 600 8 100 0 d
xform 0 736 256
p 672 222 100 0 1 DLY1:$(delay)
p 192 -2468 100 0 0 PV:$(prefix)$(command):
p 976 414 100 0 -1 def(LNK1):$(prefix)$(command)C:ms2.PROC
p 576 448 75 1280 -1 palrm(SELL):NMS
p 912 384 75 1024 -1 pproc(LNK2):PP
[comments]
