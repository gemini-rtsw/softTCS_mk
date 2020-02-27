[schematic2]
uniq 87
[tools]
[detail]
w 944 1067 100 0 n#86 ecad8.ecad8#23.VALF 160 1056 1776 1056 1776 1344 1888 1344 eaos.valf.DOL
w 656 1131 100 0 n#85 ecad8.ecad8#23.VALE 160 1120 1200 1120 1200 1344 1312 1344 eaos.vale.DOL
w 312 1195 100 0 n#84 ecad8.ecad8#23.VALD 160 1184 512 1184 512 1344 736 1344 eaos.vald.DOL
w 1320 -165 100 0 n#83 elongouts.start.FLNK 1120 -176 1568 -176 1568 240 1760 240 tcsSubCadWait.tcsSubCadWait#55.START
w 344 715 100 0 n#82 ecad8.ecad8#23.STLK 160 704 576 704 576 880 864 880 eevents.event.SLNK
w 792 923 100 0 n#81 hwin.hwin#80.in 704 960 768 960 768 912 864 912 eevents.event.INP
w 936 731 100 0 n#77 eevents.event.FLNK 1152 912 1184 912 1184 720 736 720 736 560 864 560 estringouts.null.SLNK
w 936 450 100 0 n#64 estringouts.null.FLNK 1120 576 1184 576 1184 448 736 448 736 320 864 320 elongouts.busy.SLNK
w 936 194 100 0 n#61 elongouts.busy.FLNK 1120 352 1184 352 1184 192 736 192 736 48 864 48 elongouts.mark.SLNK
w 792 354 100 0 n#59 hwin.hwin#58.in 768 352 864 352 elongouts.busy.DOL
w 792 -174 100 0 n#54 hwin.hwin#52.in 768 -176 864 -176 elongouts.start.DOL
w 792 82 100 0 n#53 hwin.hwin#51.in 768 80 864 80 elongouts.mark.DOL
w 936 -78 100 0 n#49 elongouts.mark.FLNK 1120 80 1184 80 1184 -80 736 -80 736 -208 864 -208 elongouts.start.SLNK
w 1144 1570 100 0 n#46 ecad8.ecad8#23.VAL 160 1568 2176 1568 outhier.VAL.p
w 1414 1476 100 0 n#9 ecad8.ecad8#23.MESS 160 1536 688 1536 688 1472 2176 1472 outhier.MESS.p
w -338 1540 100 0 n#8 inhier.ICID.P -560 1472 -480 1472 -480 1536 -160 1536 ecad8.ecad8#23.ICID
w -378 1570 100 0 n#7 inhier.DIR.P -560 1568 -160 1568 ecad8.ecad8#23.DIR
s 368 1856 200 0 Trigger a subsystem CAD
s 1808 2000 100 0 $Id: tcsMechSadCad.sch,v 1.1 1998/12/18 09:10:39 epics Exp $
s 1808 -336 100 0 20 October 1996
s 2032 -192 100 0 Gemini Telescope Control System
s 1632 -64 100 0 This symbol handles timeouts on command acknowledgement as
s 1632 -96 100 0 well as command rejection.
s -352 448 100 0 Note that the output links will send data to the input
s -352 416 100 0 fields of the subsystem CAD even if the command is
s -352 384 100 0 rejected by the TCS. The data sent will be the same
s -352 352 100 0 as in the last valid command. This is fairly
s -352 320 100 0 innocuous but will leave the subsystem CAD marked. If
s -352 288 100 0 this might cause a problem then a custom schematic should
s -352 256 100 0 be cloned from this one where the outputs are only sent 
s -352 224 100 0 when the STLK link is triggered.
s 352 1776 100 0 This schematic is a derivative of tcsMechanismCad
s 352 1744 100 0 As well as driving the CAD it also updates the specified SAD items.
s 352 1712 100 0 Note that seq records are used between the CAD and the SAD to
s 352 1680 100 0 split any lock sets.
[cell use]
use hwin 512 919 100 0 hwin#80
xform 0 608 960
p 515 952 100 0 -1 val(in):1
use eaos 1888 1223 100 0 valf
xform 0 2016 1312
p 1668 1498 100 0 0 DESC:Output of CAD
p 1856 1038 100 0 0 EGU:degs
p 2144 1408 100 0 1 EVNT:1
p 1632 1294 100 0 0 OMSL:closed_loop
p 1952 1408 100 0 1 SCAN:Event
p 2240 1280 100 0 -1 def(OUT):$(outf)
p 2000 1216 100 1024 0 name:$(tcs)$(cad)$(I)
use eaos 1312 1223 100 0 vale
xform 0 1440 1312
p 1092 1498 100 0 0 DESC:Output of CAD
p 1280 1038 100 0 0 EGU:degs
p 1568 1408 100 0 1 EVNT:1
p 1056 1294 100 0 0 OMSL:closed_loop
p 1376 1408 100 0 1 SCAN:Event
p 1664 1280 100 0 -1 def(OUT):$(oute)
p 1424 1216 100 1024 0 name:$(tcs)$(cad)$(I)
use eaos 736 1223 100 0 vald
xform 0 864 1312
p 516 1498 100 0 0 DESC:Output of CAD
p 704 1038 100 0 0 EGU:degs
p 992 1408 100 0 1 EVNT:1
p 480 1294 100 0 0 OMSL:closed_loop
p 800 1408 100 0 1 SCAN:Event
p 1088 1280 100 0 -1 def(OUT):$(outd)
p 848 1216 100 1024 0 name:$(tcs)$(cad)$(I)
use eevents 864 791 100 0 event
xform 0 1008 880
p 976 784 100 1024 0 name:$(tcs)$(cad)$(I)
use estringouts 888 488 100 0 null
xform 0 992 560
p 896 654 100 0 -1 DESC:Supply an empty string
p 800 526 100 0 0 VAL:
p 1264 542 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
p 976 480 100 1024 0 name:$(tcs)$(cad)$(I)
use hwin 600 312 100 0 hwin#58
xform 0 672 352
p 579 344 100 0 -1 val(in):$(CAR_BUSY)
use hwin 600 -216 100 0 hwin#52
xform 0 672 -176
p 579 -184 100 0 -1 val(in):$(CAD_START)
use hwin 600 40 100 0 hwin#51
xform 0 672 80
p 579 72 100 0 -1 val(in):$(CAD_MARK)
use elongouts 888 232 100 0 busy
xform 0 992 320
p 912 414 100 0 -1 DESC:Busy state
p 704 238 100 0 0 OMSL:closed_loop
p 1200 286 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
p 1088 224 100 1024 1 name:$(tcs)$(cad)$(I)
p 1120 288 75 768 -1 pproc(OUT):PP
use elongouts 888 -296 100 0 start
xform 0 992 -208
p 912 -114 100 0 -1 DESC:Start Directive
p 704 -290 100 0 0 OMSL:closed_loop
p 1200 -242 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1104 -304 100 1024 1 name:$(tcs)$(cad)$(I)
p 1120 -240 75 768 -1 pproc(OUT):PP
use elongouts 888 -40 100 0 mark
xform 0 992 48
p 912 142 100 0 -1 DESC:Mark directive
p 704 -34 100 0 0 OMSL:closed_loop
p 1200 14 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1088 -48 100 1024 1 name:$(tcs)$(cad)$(I)
p 1120 16 75 768 -1 pproc(OUT):PP
use tcsSubCadWait 1784 8 100 0 tcsSubCadWait#55
xform 0 1896 152
p 1856 318 100 0 -1 seta:top $(tcs)$(cad):
p 1856 286 100 0 -1 setb:index 0
use outhier 2168 1432 100 0 MESS
xform 0 2160 1472
use outhier 2168 1528 100 0 VAL
xform 0 2160 1568
use ecad8 -136 616 100 0 ecad8#23
xform 0 0 1120
p -208 1662 100 0 -1 DESC:Triggers a subsystem CAD on START only
p -48 1366 100 0 0 FTVA:STRING
p -48 1310 100 0 0 FTVB:STRING
p -64 1216 100 0 0 FTVD:DOUBLE
p -64 1184 100 0 0 FTVE:DOUBLE
p -64 1152 100 0 0 FTVF:DOUBLE
p 32 910 100 0 0 FTVH:STRING
p -64 960 100 0 0 PREC:4
p -80 798 100 0 -1 SNAM:$(snam)
p 224 1342 100 0 -1 def(OUTA):$(outa)
p 224 1278 100 0 -1 def(OUTB):$(outb)
p 224 1214 100 0 -1 def(OUTC):$(outc)
p 224 1150 100 0 0 def(OUTD):0.0
p 224 1086 100 0 0 def(OUTE):0.0
p 224 1022 100 0 0 def(OUTF):0.0
p 224 958 100 0 0 def(OUTG):0.0
p 240 894 100 0 0 def(OUTH):0.0
p -96 558 100 0 1 name:$(tcs)$(cad)
p 160 1344 75 768 -1 pproc(OUTA):NPP
p 160 1280 75 768 -1 pproc(OUTB):NPP
p 160 896 75 768 -1 pproc(OUTH):NPP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -552 1432 100 0 ICID
xform 0 -560 1472
use inhier -552 1528 100 0 DIR
xform 0 -560 1568
[comments]
