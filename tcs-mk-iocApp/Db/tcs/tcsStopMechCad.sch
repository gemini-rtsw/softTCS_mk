[schematic2]
uniq 68
[tools]
[detail]
w 760 1083 100 0 n#67 ecad8.ecad8#23.STLK 288 480 576 480 576 1072 992 1072 estringouts.null.SLNK
w 1064 962 100 0 n#64 estringouts.null.FLNK 1248 1088 1312 1088 1312 960 864 960 864 832 992 832 elongouts.busy.SLNK
w 1496 338 100 0 n#63 elongouts.stop.FLNK 1248 336 1792 336 1792 544 1888 544 tcsSubCadWait.tcsSubCadWait#55.START
w 1064 706 100 0 n#61 elongouts.busy.FLNK 1248 864 1312 864 1312 704 864 704 864 560 992 560 elongouts.mark.SLNK
w 920 866 100 0 n#59 hwin.hwin#58.in 896 864 992 864 elongouts.busy.DOL
w 920 338 100 0 n#54 hwin.hwin#52.in 896 336 992 336 elongouts.stop.DOL
w 920 594 100 0 n#53 hwin.hwin#51.in 896 592 992 592 elongouts.mark.DOL
w 1064 434 100 0 n#49 elongouts.mark.FLNK 1248 592 1312 592 1312 432 864 432 864 304 992 304 elongouts.stop.SLNK
w 1272 1346 100 0 n#46 ecad8.ecad8#23.VAL 288 1344 2304 1344 outhier.VAL.p
w 1542 1252 100 0 n#9 ecad8.ecad8#23.MESS 288 1312 816 1312 816 1248 2304 1248 outhier.MESS.p
w -210 1316 100 0 n#8 inhier.ICID.P -432 1248 -352 1248 -352 1312 -32 1312 ecad8.ecad8#23.ICID
w -250 1346 100 0 n#7 inhier.DIR.P -432 1344 -32 1344 ecad8.ecad8#23.DIR
s 384 1536 100 0 activated by a start directive.
s 384 1568 100 0 stop directive to a subsystem it is 
s 384 1600 100 0 Note that though this schematic sends a
s 368 1856 200 0 Trigger a subsystem CAD
s 1808 2000 100 0 $Id: tcsStopMechCad.sch,v 1.4 2015/11/20 17:58:57 gemvx Exp $
s 1808 -336 100 0 20 October 1996
s 2032 -192 100 0 Gemini Telescope Control System
s 1760 240 100 0 This symbol handles timeouts on command acknowledgement as
s 1760 208 100 0 well as command rejection.
s -224 224 100 0 Note that the output links will send data to the input
s -224 192 100 0 fields of the subsystem CAD even if the command is
s -224 160 100 0 rejected by the TCS. The data sent will be the same
s -224 128 100 0 as in the last valid command. This is fairly
s -224 96 100 0 innocuous but will leave the subsystem CAD marked. If
s -224 64 100 0 this might cause a problem then a custom schematic should
s -224 32 100 0 be cloned from this one where the outputs are only sent 
s -224 0 100 0 when the SPLK link is triggered.
[cell use]
use estringouts 1016 1000 100 0 null
xform 0 1120 1072
p 1024 1166 100 0 -1 DESC:Supply an empty string
p 928 1038 100 0 0 VAL:
p 1392 1054 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
p 1104 992 100 1024 0 name:$(tcs)$(cad)$(subcad)$(I)
use hwin 728 824 100 0 hwin#58
xform 0 800 864
p 707 856 100 0 -1 val(in):$(CAR_BUSY)
use hwin 728 296 100 0 hwin#52
xform 0 800 336
p 707 328 100 0 -1 val(in):$(CAD_START)
use hwin 728 552 100 0 hwin#51
xform 0 800 592
p 707 584 100 0 -1 val(in):$(CAD_MARK)
use elongouts 1016 744 100 0 busy
xform 0 1120 832
p 1040 926 100 0 -1 DESC:Busy state
p 832 750 100 0 0 OMSL:closed_loop
p 1328 798 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
p 1216 736 100 1024 1 name:$(tcs)$(cad)$(subcad)$(I)
p 1248 800 75 768 -1 pproc(OUT):PP
use elongouts 1016 216 100 0 stop
xform 0 1120 304
p 1040 398 100 0 -1 DESC:Stop Directive
p 832 222 100 0 0 OMSL:closed_loop
p 1328 270 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1232 208 100 1024 1 name:$(tcs)$(cad)$(subcad)$(I)
p 1248 272 75 768 -1 pproc(OUT):PP
use elongouts 1016 472 100 0 mark
xform 0 1120 560
p 1040 654 100 0 -1 DESC:Mark directive
p 832 478 100 0 0 OMSL:closed_loop
p 1328 526 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1216 464 100 1024 1 name:$(tcs)$(cad)$(subcad)$(I)
p 1248 528 75 768 -1 pproc(OUT):PP
use tcsSubCadWait 1912 312 100 0 tcsSubCadWait#55
xform 0 2024 456
p 1984 622 100 0 -1 seta:top $(tcs)$(cad):
p 1984 590 100 0 -1 setb:index 1
use outhier 2296 1208 100 0 MESS
xform 0 2288 1248
use outhier 2296 1304 100 0 VAL
xform 0 2288 1344
use ecad8 -8 392 100 0 ecad8#23
xform 0 128 896
p -80 1438 100 0 -1 DESC:Triggers a subsystem CAD to stop
p 80 1142 100 0 0 FTVA:STRING
p 80 1086 100 0 0 FTVB:STRING
p 160 686 100 0 0 FTVH:STRING
p 64 736 100 0 0 PREC:4
p 48 574 100 0 -1 SNAM:$(snam)
p 352 1118 100 0 -1 def(OUTA):$(outa)
p 352 1054 100 0 -1 def(OUTB):$(outb)
p 352 990 100 0 -1 def(OUTC):$(outc)
p 352 926 100 0 -1 def(OUTD):$(outd)
p 352 862 100 0 -1 def(OUTE):$(oute)
p 352 798 100 0 -1 def(OUTF):$(outf)
p 352 734 100 0 0 def(OUTG):0.0
p 368 670 100 0 0 def(OUTH):0.0
p 32 334 100 0 1 name:$(tcs)$(cad)
p 288 1120 75 768 -1 pproc(OUTA):NPP
p 288 1056 75 768 -1 pproc(OUTB):NPP
p 288 672 75 768 -1 pproc(OUTH):NPP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -424 1208 100 0 ICID
xform 0 -432 1248
use inhier -424 1304 100 0 DIR
xform 0 -432 1344
[comments]
