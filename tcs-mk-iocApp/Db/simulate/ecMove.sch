[schematic2]
uniq 115
[tools]
[detail]
w 410 -142 100 0 n#114 ecad4.park.OUTC 240 -144 640 -144 outhier.c#111.p
w 410 -78 100 0 n#113 ecad4.park.OUTB 240 -80 640 -80 outhier.c#110.p
w 410 -14 100 0 n#112 ecad4.park.OUTA 240 -16 640 -16 outhier.c#109.p
s 1216 -640 100 0 Gemini Telescope Control System
s 976 592 100 0 $Id: ecMove.sch,v 1.1.1.1 1998/11/08 00:20:21 epics Exp $
s -128 416 200 0 Simple mechanism CAD
[cell use]
use bb200tr -816 -920 -100 0 frame
xform 0 464 -96
use outhier 632 -184 100 0 c#111
xform 0 624 -144
use outhier 632 -120 100 0 c#110
xform 0 624 -80
use outhier 632 -56 100 0 c#109
xform 0 624 -16
use ecad4 -56 -488 -100 0 park
xform 0 80 -112
p 0 -274 100 0 1 SNAM:$(snam)
p 320 -2 100 0 -1 def(OUTA):$(outa)
p 240 -16 75 768 -1 pproc(OUTA):PP
p 320 -66 100 0 -1 def(OUTB):$(outb)
p 320 -130 100 0 -1 def(OUTC):$(outc)
p -16 440 100 0 0 FTVA:LONG
p 32 -496 100 1024 1 name:$(prefix)move$(pmech)
p 80 176 100 256 -1 Type:cad
p -144 -1008 100 0 0 SIMS:NO_ALARM
p -144 -912 100 0 0 PREC:14
[comments]
