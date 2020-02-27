[schematic2]
uniq 117
[tools]
[detail]
w -310 -206 100 0 n#116 eaos.defpark1.VAL -480 -208 -80 -208 ecad4.park.INPD
w 410 -142 100 0 n#114 ecad4.park.OUTC 240 -144 640 -144 outhier.c#111.p
w 410 -78 100 0 n#113 ecad4.park.OUTB 240 -80 640 -80 outhier.c#110.p
w 410 -14 100 0 n#112 ecad4.park.OUTA 240 -16 640 -16 outhier.c#109.p
s -848 -416 100 0 of specifying explicitly the park position
s -848 -384 100 0 mechanisms where the user is not given the option
s -848 -352 100 0 The default position is used for those
s -208 496 150 0 Implement a park command for the ECS
s 752 640 100 0 $Id: ecPark.sch,v 1.1.1.1 1998/11/08 00:20:21 epics Exp $
s 976 -592 100 0 Gemini Telescope Control System
[cell use]
use bb200tr -1040 -872 -100 0 frame
xform 0 240 -48
use outhier 632 -184 100 0 c#111
xform 0 624 -144
use outhier 632 -120 100 0 c#110
xform 0 624 -80
use outhier 632 -56 100 0 c#109
xform 0 624 -16
use ecad4 -56 -488 -100 0 park
xform 0 80 -112
p 16 -354 100 0 -1 SNAM:$(snam)
p 320 -2 100 0 -1 def(OUTA):$(outa)
p 240 -16 75 768 -1 pproc(OUTA):NPP
p 320 -66 100 0 -1 def(OUTB):$(outb)
p 320 -130 100 0 -1 def(OUTC):$(outc)
p -16 440 100 0 0 FTVA:STRING
p 32 -496 100 1024 1 name:$(prefix)park$(pmech)
p 80 176 100 256 -1 Type:cad
p -144 -1008 100 0 0 SIMS:NO_ALARM
p -144 -784 100 0 0 FTVD:LONG
p 352 -210 100 0 -1 def(OUTD):$(outd)
p 240 -208 75 768 -1 pproc(OUTD):PP
use eaos -712 -296 -100 0 defpark1
xform 0 -608 -208
p -800 -290 100 0 1 name:$(prefix)$(defpark1)
[comments]
