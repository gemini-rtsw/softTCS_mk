[schematic2]
uniq 193
[tools]
[detail]
w 1858 859 100 0 n#192 elongouts.setDatum.FLNK 1728 912 1824 912 1824 848 1952 848 elongins.Datumed.SLNK
w 1810 891 100 0 n#191 elongouts.setDatum.VAL 1728 880 1952 880 elongins.Datumed.INP
w 1378 635 100 0 n#189 efanouts.CtrlFan.LNK1 1376 624 1440 624 1440 880 1472 880 elongouts.setDatum.SLNK
w 1394 923 100 0 n#188 hwin.hwin#180.in 1376 912 1472 912 elongouts.setDatum.DOL
w 1858 -245 100 0 n#186 elongouts.setInit.VAL 1792 -256 1984 -256 elongins.Initialized.INP
w 1890 -277 100 0 n#185 elongouts.setInit.FLNK 1792 -224 1856 -224 1856 -288 1984 -288 elongins.Initialized.SLNK
w 1394 571 100 0 n#184 efanouts.CtrlFan.LNK3 1376 560 1472 560 1472 -256 1536 -256 elongouts.setInit.SLNK
w 1458 -213 100 0 n#183 hwin.hwin#176.in 1440 -224 1536 -224 elongouts.setInit.DOL
w 1938 395 100 0 n#173 estringouts.setParkY.FLNK 1984 480 2048 480 2048 384 1888 384 1888 256 1984 256 elongouts.elongouts#119.SLNK
w 1194 171 100 0 n#172 ecad4.park.VALC 880 160 1568 160 1568 496 1728 496 estringouts.setParkY.DOL
w 1818 571 100 0 n#171 estringouts.setParkX.FLNK 1984 656 2048 656 2048 560 1648 560 1648 464 1728 464 estringouts.setParkY.SLNK
w 2114 459 100 0 n#170 estringouts.setParkY.OUT 1984 448 2304 448 outhier.c#110.p
w 1178 235 100 0 n#167 ecad4.park.VALB 880 224 1536 224 1536 672 1728 672 estringouts.setParkX.DOL
w 1586 651 100 0 n#165 efanouts.CtrlFan.LNK2 1376 592 1504 592 1504 640 1728 640 estringouts.setParkX.SLNK
w 2114 635 100 0 n#164 estringouts.setParkX.OUT 1984 624 2304 624 outhier.c#109.p
w 1026 635 100 0 n#159 ecad4.park.VALA 880 288 928 288 928 624 1184 624 efanouts.CtrlFan.SELL
w 922 -117 100 0 n#158 ecad4.park.STLK 880 -128 1024 -128 1024 544 1136 544 efanouts.CtrlFan.SLNK
w 450 -581 100 0 n#155 junction 384 128 384 -592 576 -592 ecalcs.setPark.INPE
w 442 139 100 0 n#155 eaos.defpark2.VAL 320 192 384 192 384 128 560 128 ecad4.park.INPC
w 474 -549 100 0 n#154 junction 432 192 432 -560 576 -560 ecalcs.setPark.INPD
w 466 203 100 0 n#154 eaos.defpark1.VAL 320 432 432 432 432 192 560 192 ecad4.park.INPB
w 1154 -581 100 0 n#152 ecalcs.setPark.VAL 864 -656 1072 -656 1072 -592 1296 -592 elongins.Parked.INP
w 1050 -613 100 0 n#151 ecalcs.setPark.FLNK 864 -624 1296 -624 elongins.Parked.SLNK
w 338 -517 100 0 n#145 inhier.Y.P -48 -592 160 -592 160 -528 576 -528 ecalcs.setPark.INPC
w 234 -485 100 0 n#143 inhier.X.P -48 -496 576 -496 ecalcs.setPark.INPB
w 434 -453 100 0 n#141 hwin.hwin#140.in 352 -464 576 -464 ecalcs.setPark.INPA
w 1912 34 100 0 n#118 hwin.hwin#122.in 1888 32 1984 32 elongouts.elongouts#120.DOL
w 1912 290 100 0 n#117 hwin.hwin#121.in 1888 288 1984 288 elongouts.elongouts#119.DOL
w 2056 130 100 0 n#115 elongouts.elongouts#119.FLNK 2240 288 2304 288 2304 128 1856 128 1856 0 1984 0 elongouts.elongouts#120.SLNK
s 704 1024 200 0 Issue Ctrl command and set probe status
s 1936 1104 100 0 $Id: aomNgsCtrl.sch,v 1.1 2007/12/18 09:48:13 cjm Exp $
[cell use]
use elongouts 1472 791 100 0 setDatum
xform 0 1600 880
p 1312 798 100 0 0 OMSL:closed_loop
p 1584 784 100 1024 0 name:$(prefix)$(I)
use elongouts 1536 -345 100 0 setInit
xform 0 1664 -256
p 1376 -338 100 0 0 OMSL:closed_loop
p 1648 -352 100 1024 0 name:$(prefix)$(I)
use elongouts 2008 -88 100 0 elongouts#120
xform 0 2112 0
p 2032 94 100 0 -1 DESC:Start Directive
p 1824 142 100 0 0 EGU:units
p 1824 -82 100 0 0 OMSL:closed_loop
p 1824 174 100 0 0 PINI:NO
p 2320 -34 100 0 -1 def(OUT):$(prefix)Mv.DIR
p 2096 -96 100 1024 -1 name:$(prefix)startPark
p 2240 -32 75 768 -1 pproc(OUT):PP
use elongouts 2008 168 100 0 elongouts#119
xform 0 2112 256
p 2032 350 100 0 -1 DESC:Mark directive
p 1824 174 100 0 0 OMSL:closed_loop
p 2320 222 100 0 -1 def(OUT):$(prefix)Mv.DIR
p 2096 160 100 1024 -1 name:$(prefix)markPark
p 2240 224 75 768 -1 pproc(OUT):PP
use hwin 1184 871 100 0 hwin#180
xform 0 1280 912
p 1187 904 100 0 -1 val(in):1
use hwin 1248 -265 100 0 hwin#176
xform 0 1344 -224
p 1251 -232 100 0 -1 val(in):1
use hwin 160 -505 100 0 hwin#140
xform 0 256 -464
p 163 -472 100 0 -1 val(in):0.1
use hwin 1720 -8 100 0 hwin#122
xform 0 1792 32
p 1699 24 100 0 -1 val(in):$(CAD_START)
use hwin 1720 248 100 0 hwin#121
xform 0 1792 288
p 1699 280 100 0 -1 val(in):$(CAD_MARK)
use elongins 1952 775 100 0 Datumed
xform 0 2080 848
p 1741 1049 100 0 0 DESC:Parked state
p 2064 768 100 1024 0 name:$(prefix)$(I)
use elongins 1984 -361 100 0 Initialized
xform 0 2112 -288
p 1773 -87 100 0 0 DESC:Parked state
p 2096 -368 100 1024 0 name:$(prefix)$(I)
use elongins 1296 -697 100 0 Parked
xform 0 1424 -624
p 1085 -423 100 0 0 DESC:Parked state
p 1408 -704 100 1024 0 name:$(prefix)$(I)
use estringouts 1728 391 100 0 setParkY
xform 0 1856 464
p 1760 528 100 0 -1 DESC:Set Y move demand
p 1664 270 100 0 0 OMSL:closed_loop
p 1664 430 100 0 0 VAL:0.0
p 2080 464 100 0 -1 def(OUT):$(prefix)Mv.B
p 1840 384 100 1024 0 name:$(prefix)$(I)
use estringouts 1728 567 100 0 setParkX
xform 0 1856 640
p 1760 704 100 0 -1 DESC:Set X move demand
p 1664 446 100 0 0 OMSL:closed_loop
p 1664 606 100 0 0 VAL:0.0
p 2080 640 100 0 -1 def(OUT):$(prefix)Mv.A
p 1840 560 100 1024 0 name:$(prefix)$(I)
use efanouts 1136 407 100 0 CtrlFan
xform 0 1256 560
p 1022 825 100 0 0 DESC:Select control mode
p 992 526 100 0 0 SELM:Specified
p 1248 400 100 1024 0 name:$(prefix)$(I)
use inhier -64 -633 100 0 Y
xform 0 -48 -592
use inhier -64 -537 100 0 X
xform 0 -48 -496
use ecalcs 576 -937 100 0 setPark
xform 0 720 -672
p 768 -832 100 0 1 CALC:(ABS(B-D) < A) && (ABS(C-E) < A)?1:0
p 576 -368 100 0 -1 DESC:Calculate parked state
p 768 -880 100 0 1 SCAN:1 second
p 688 -944 100 1024 0 name:$(prefix)$(I)
use outhier 2296 584 100 0 c#109
xform 0 2288 624
use outhier 2296 408 100 0 c#110
xform 0 2288 448
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
p 496 -256 100 0 0 DESC:NGS probe Ctrl command
p 624 712 100 0 0 FTVA:LONG
p 656 -82 100 0 -1 SNAM:tcsAomCtrlCAD
p 960 270 100 0 0 def(OUTA):0.0
p 960 206 100 0 0 def(OUTB):0.0
p 960 142 100 0 0 def(OUTC):0.0
p 668 -224 100 1024 -1 name:$(prefix)Ctrl
p 880 256 75 768 -1 pproc(OUTA):NPP
p 976 -480 100 0 0 typ(OUTB):path
[comments]
