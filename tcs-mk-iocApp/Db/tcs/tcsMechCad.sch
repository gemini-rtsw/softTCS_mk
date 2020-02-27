[schematic2]
uniq 55
[tools]
[detail]
w 696 610 100 0 n#54 hwin.hwin#52.in 672 608 768 608 elongouts.start.DOL
w 696 866 100 0 n#53 hwin.hwin#51.in 672 864 768 864 elongouts.mark.DOL
w 418 680 100 0 n#50 ecad8.ecad8#23.STLK 288 480 416 480 416 832 768 832 elongouts.mark.SLNK
w 840 706 100 0 n#49 elongouts.mark.FLNK 1024 864 1088 864 1088 704 640 704 640 576 768 576 elongouts.start.SLNK
w 1272 1346 100 0 n#46 ecad8.ecad8#23.VAL 288 1344 2304 1344 outhier.VAL.p
w 1542 1252 100 0 n#9 ecad8.ecad8#23.MESS 288 1312 816 1312 816 1248 2304 1248 outhier.MESS.p
w -210 1316 100 0 n#8 inhier.ICID.P -432 1248 -352 1248 -352 1312 -32 1312 ecad8.ecad8#23.ICID
w -250 1346 100 0 n#7 inhier.DIR.P -432 1344 -32 1344 ecad8.ecad8#23.DIR
s 368 1856 200 0 Tigger a subsystem CAD
s 1808 2000 100 0 $id$
s 1808 -336 100 0 20 October 1996
s 2032 -192 100 0 Gemini Telescope Control System
[cell use]
use hwin 504 568 100 0 hwin#52
xform 0 576 608
p 483 600 100 0 -1 val(in):$(CAD_START)
use hwin 504 824 100 0 hwin#51
xform 0 576 864
p 483 856 100 0 -1 val(in):$(CAD_MARK)
use elongouts 792 488 100 0 start
xform 0 896 576
p 816 670 100 0 -1 DESC:Start Directive
p 608 494 100 0 0 OMSL:closed_loop
p 1104 542 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1008 480 100 1024 1 name:$(tcs)$(cad)$(I)
p 1024 544 75 768 -1 pproc(OUT):PP
use elongouts 792 744 100 0 mark
xform 0 896 832
p 816 926 100 0 -1 DESC:Mark directive
p 608 750 100 0 0 OMSL:closed_loop
p 1104 798 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 992 736 100 1024 1 name:$(tcs)$(cad)$(I)
p 1024 800 75 768 -1 pproc(OUT):PP
use tcsSubcadWait 1464 600 100 0 tcsSubcadWait#45
xform 0 1544 744
use outhier 2296 1208 100 0 MESS
xform 0 2288 1248
use outhier 2296 1304 100 0 VAL
xform 0 2288 1344
use ecad8 -8 392 100 0 ecad8#23
xform 0 128 896
p -80 1438 100 0 -1 DESC:Triggers a subsystem CAD on START only
p 80 1142 100 0 0 FTVA:STRING
p 80 1086 100 0 0 FTVB:STRING
p 160 686 100 0 0 FTVH:STRING
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
p 64 736 100 0 0 PREC:4
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -424 1208 100 0 ICID
xform 0 -432 1248
use inhier -424 1304 100 0 DIR
xform 0 -432 1344
[comments]
