[schematic2]
uniq 154
[tools]
[detail]
w 1154 -581 100 0 n#152 ecalcs.setPark.VAL 864 -656 1072 -656 1072 -592 1296 -592 elongins.probeParked.INP
w 1050 -613 100 0 n#151 ecalcs.setPark.FLNK 864 -624 1296 -624 elongins.probeParked.SLNK
w 482 -581 100 0 n#147 junction 448 192 448 -592 576 -592 ecalcs.setPark.INPE
w 410 203 100 0 n#147 eaos.defpark2.VAL 320 192 560 192 ecad4.park.INPB
w 466 -549 100 0 n#149 junction 416 256 416 -560 576 -560 ecalcs.setPark.INPD
w 458 267 100 0 n#149 eaos.defpark1.VAL 320 432 416 432 416 256 560 256 ecad4.park.INPA
w 370 -37 100 0 n#148 eaos.eaos#124.VAL 320 -48 480 -48 480 128 560 128 ecad4.park.INPC
w 338 -517 100 0 n#145 inhier.Y.P -48 -592 160 -592 160 -528 576 -528 ecalcs.setPark.INPC
w 234 -485 100 0 n#143 inhier.X.P -48 -496 576 -496 ecalcs.setPark.INPB
w 434 -453 100 0 n#141 hwin.hwin#140.in 352 -464 576 -464 ecalcs.setPark.INPA
w 1098 -126 100 0 n#136 ecad4.park.STLK 880 -128 1376 -128 1376 272 1744 272 elongouts.elongouts#119.SLNK
w 1672 50 100 0 n#118 hwin.hwin#122.in 1648 48 1744 48 elongouts.elongouts#120.DOL
w 1672 306 100 0 n#117 hwin.hwin#121.in 1648 304 1744 304 elongouts.elongouts#119.DOL
w 1816 146 100 0 n#115 elongouts.elongouts#119.FLNK 2000 304 2064 304 2064 144 1616 144 1616 16 1744 16 elongouts.elongouts#120.SLNK
w 1050 194 100 0 n#113 ecad4.park.OUTB 880 192 1280 192 outhier.c#110.p
w 1050 258 100 0 n#112 ecad4.park.OUTA 880 256 1280 256 outhier.c#109.p
s 704 1024 200 0 Issue Park command and set park status
s 1936 1104 100 0 $Id: probePark.sch,v 1.4 2002/11/14 16:49:21 dlt Exp $
[cell use]
use elongins 1296 -697 100 0 probeParked
xform 0 1424 -624
p 1085 -423 100 0 0 DESC:Parked state
p 1408 -704 100 1024 0 name:$(prefix)$(I)
use inhier -64 -633 100 0 Y
xform 0 -48 -592
use inhier -64 -537 100 0 X
xform 0 -48 -496
use hwin 160 -505 100 0 hwin#140
xform 0 256 -464
p 163 -472 100 0 -1 val(in):0.1
use hwin 1480 8 100 0 hwin#122
xform 0 1552 48
p 1459 40 100 0 -1 val(in):$(CAD_START)
use hwin 1480 264 100 0 hwin#121
xform 0 1552 304
p 1459 296 100 0 -1 val(in):$(CAD_MARK)
use ecalcs 576 -937 100 0 setPark
xform 0 720 -672
p 768 -832 100 0 1 CALC:(ABS(B-D) < A) && (ABS(C-E) < A)?1:0
p 576 -368 100 0 -1 DESC:Calculate parked state
p 768 -880 100 0 1 SCAN:1 second
p 688 -944 100 1024 0 name:$(prefix)$(I)
use elongouts 1768 -72 100 0 elongouts#120
xform 0 1872 16
p 1792 110 100 0 -1 DESC:Start Directive
p 1584 158 100 0 0 EGU:units
p 1584 -66 100 0 0 OMSL:closed_loop
p 1584 190 100 0 0 PINI:NO
p 2080 -18 100 0 -1 def(OUT):$(prefix)probeMove.DIR
p 1856 -80 100 1024 -1 name:$(prefix)startPark
p 2000 -16 75 768 -1 pproc(OUT):PP
use elongouts 1768 184 100 0 elongouts#119
xform 0 1872 272
p 1792 366 100 0 -1 DESC:Mark directive
p 1584 190 100 0 0 OMSL:closed_loop
p 2080 238 100 0 -1 def(OUT):$(prefix)probeMove.DIR
p 1856 176 100 1024 -1 name:$(prefix)markPark
p 2000 240 75 768 -1 pproc(OUT):PP
use outhier 1272 216 100 0 c#109
xform 0 1264 256
use outhier 1272 152 100 0 c#110
xform 0 1264 192
use eaos 88 -136 -100 0 eaos#124
xform 0 192 -48
p 0 -130 100 0 -1 name:$(prefix)ParkZ
use eaos 88 344 -100 0 defpark1
xform 0 192 432
p 0 350 100 0 -1 name:$(prefix)ParkX
use eaos 88 104 -100 0 defpark2
xform 0 192 192
p 0 110 100 0 -1 name:$(prefix)ParkY
use bc200tr -640 -1368 -100 0 frame
xform 0 1040 -64
use ecad4 584 -216 -100 0 park
xform 0 720 160
p 624 712 100 0 0 FTVA:STRING
p 656 -82 100 0 -1 SNAM:tcs$(snam)GenericCAD
p 960 270 100 0 -1 def(OUTA):$(prefix)probeMove.A
p 960 206 100 0 -1 def(OUTB):$(prefix)probeMove.B
p 960 142 100 0 0 def(OUTC):0.0
p 668 -224 100 1024 -1 name:$(prefix)probePark
p 880 256 75 768 -1 pproc(OUTA):NPP
p 976 -480 100 0 0 typ(OUTB):path
[comments]
