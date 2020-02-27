[schematic2]
uniq 130
[tools]
[detail]
w 106 11 100 0 n#129 eaos.eaos#128.VAL 32 -128 96 -128 96 0 176 0 ecad4.park.INPC
w 666 11 100 0 n#125 ecad4.park.OUTC 496 0 896 0 outhier.c#124.p
w 730 -254 100 0 n#123 ecad4.park.STLK 496 -256 1024 -256 1024 144 1360 144 elongouts.elongouts#119.SLNK
w 1288 -78 100 0 n#118 hwin.hwin#122.in 1264 -80 1360 -80 elongouts.elongouts#120.DOL
w 1288 178 100 0 n#117 hwin.hwin#121.in 1264 176 1360 176 elongouts.elongouts#119.DOL
w 1432 18 100 0 n#115 elongouts.elongouts#119.FLNK 1616 176 1680 176 1680 16 1232 16 1232 -112 1360 -112 elongouts.elongouts#120.SLNK
w 666 66 100 0 n#113 ecad4.park.OUTB 496 64 896 64 outhier.c#110.p
w 666 130 100 0 n#112 ecad4.park.OUTA 496 128 896 128 outhier.c#109.p
w 50 114 100 0 n#105 eaos.defpark2.VAL 32 112 128 112 128 64 176 64 ecad4.park.INPB
w 114 246 100 0 n#104 eaos.defpark1.VAL 32 304 112 304 112 128 176 128 ecad4.park.INPA
s 64 576 100 0 is provided for up to three axes.
s 64 608 100 0 is normally the move command. A default park position
s 64 640 100 0 by sending a command through another CAD. The CAD
s 64 672 100 0 This simple simulation of the park command works
s 1952 -1056 100 0 Simulated Park command
s 1712 1200 100 0 $Id: park.sch,v 1.2 2002/04/04 14:50:50 cjm Exp $
[cell use]
use eaos -200 -216 -100 0 eaos#128
xform 0 -96 -128
p -444 58 100 0 0 DESC:3rd axis default park position
p -256 -402 100 0 0 EGU:mm
p -288 -210 100 0 -1 name:$(prefix)$(defpark3)
use outhier 864 -41 100 0 c#124
xform 0 880 0
use bc200tr -880 -1272 -100 0 frame
xform 0 800 32
use bc200tr -880 -1272 -100 0 frame
xform 0 800 32
use hwin 1096 136 100 0 hwin#121
xform 0 1168 176
p 1075 168 100 0 -1 val(in):0
use hwin 1096 -120 100 0 hwin#122
xform 0 1168 -80
p 1075 -88 100 0 -1 val(in):3
use elongouts 1384 56 100 0 elongouts#119
xform 0 1488 144
p 1408 238 100 0 -1 DESC:Mark directive
p 1200 62 100 0 0 OMSL:closed_loop
p 1696 110 100 0 -1 def(OUT):$(outa)
p 1472 48 100 1024 -1 name:$(prefix)markPark
p 1616 112 75 768 -1 pproc(OUT):PP
use elongouts 1384 -200 100 0 elongouts#120
xform 0 1488 -112
p 1408 -18 100 0 -1 DESC:Start Directive
p 1200 -194 100 0 0 OMSL:closed_loop
p 1696 -146 100 0 -1 def(OUT):$(outa)
p 1472 -208 100 1024 -1 name:$(prefix)startPark
p 1616 -144 75 768 -1 pproc(OUT):PP
use outhier 888 24 100 0 c#110
xform 0 880 64
use outhier 888 88 100 0 c#109
xform 0 880 128
use ecad4 200 -344 -100 0 park
xform 0 336 32
p 240 584 100 0 0 FTVA:STRING
p 192 -114 100 0 -1 SNAM:tcs$(snam)GenericCAD
p 576 142 100 0 -1 def(OUTA):$(outb)
p 576 78 100 0 -1 def(OUTB):$(outc)
p 576 16 100 0 -1 def(OUTC):$(outd)
p 284 -352 100 1024 -1 name:$(prefix)park
p 496 128 75 768 -1 pproc(OUTA):NPP
use eaos -200 24 -100 0 defpark2
xform 0 -96 112
p -288 30 100 0 -1 name:$(prefix)$(defpark2)
use eaos -200 216 -100 0 defpark1
xform 0 -96 304
p -288 222 100 0 -1 name:$(prefix)$(defpark1)
[comments]
