[schematic2]
uniq 56
[tools]
[detail]
w 648 210 100 0 n#55 ecad20.ecad20#23.STLK 288 96 512 96 512 208 832 208 elongouts.mark.SLNK
w 760 -14 100 0 n#54 hwin.hwin#52.in 736 -16 832 -16 elongouts.start.DOL
w 760 242 100 0 n#53 hwin.hwin#51.in 736 240 832 240 elongouts.mark.DOL
w 904 82 100 0 n#49 elongouts.mark.FLNK 1088 240 1152 240 1152 80 704 80 704 -48 832 -48 elongouts.start.SLNK
w 1272 1730 100 0 n#46 ecad20.ecad20#23.VAL 288 1728 2304 1728 outhier.VAL.p
w 1542 1636 100 0 n#9 ecad20.ecad20#23.MESS 288 1696 816 1696 816 1632 2304 1632 outhier.MESS.p
w -210 1700 100 0 n#8 inhier.ICID.P -432 1632 -352 1632 -352 1696 -32 1696 ecad20.ecad20#23.ICID
w -250 1730 100 0 n#7 inhier.DIR.P -432 1728 -32 1728 ecad20.ecad20#23.DIR
s 368 1856 200 0 Trigger a subsystem CAD20
s 1808 2000 100 0 $id$
s 1808 -336 100 0 20 October 1996
s 2032 -192 100 0 Gemini Telescope Control System
[cell use]
use hwin 568 -56 100 0 hwin#52
xform 0 640 -16
p 547 -24 100 0 -1 val(in):3
use hwin 568 200 100 0 hwin#51
xform 0 640 240
p 547 232 100 0 -1 val(in):0
use elongouts 856 -136 100 0 start
xform 0 960 -48
p 880 46 100 0 -1 DESC:Start Directive
p 672 -130 100 0 0 OMSL:closed_loop
p 1168 -82 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1072 -144 100 1024 1 name:$(tcs)$(cad)$(I)
p 1088 -80 75 768 -1 pproc(OUT):PP
use elongouts 856 120 100 0 mark
xform 0 960 208
p 880 302 100 0 -1 DESC:Mark directive
p 672 126 100 0 0 OMSL:closed_loop
p 1168 174 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1056 112 100 1024 1 name:$(tcs)$(cad)$(I)
p 1088 176 75 768 -1 pproc(OUT):PP
use tcsSubcadWait 1464 600 100 0 tcsSubcadWait#45
xform 0 1544 744
use outhier 2296 1592 100 0 MESS
xform 0 2288 1632
use outhier 2296 1688 100 0 VAL
xform 0 2288 1728
use ecad20 48 480 100 0 ecad20#23
xform 0 128 896
p -80 1790 100 0 -1 DESC:Triggers a subsystem CAD on START only
p 80 1142 100 0 0 FTVA:STRING
p 80 1086 100 0 0 FTVB:STRING
p 160 686 100 0 0 FTVH:STRING
p 48 574 100 0 -1 SNAM:$(snam)
p 368 1502 100 0 -1 def(OUTA):$(outa)
p 368 1438 100 0 -1 def(OUTB):$(outb)
p 368 1374 100 0 -1 def(OUTC):$(outc)
p 368 1310 100 0 -1 def(OUTD):$(outd)
p 368 1246 100 0 -1 def(OUTE):$(oute)
p 368 1182 100 0 -1 def(OUTF):$(outf)
p 368 1118 100 0 -1 def(OUTG):$(outg)
p 368 1054 100 0 -1 def(OUTH):$(outh)
p 368 990 100 0 -1 def(OUTI):$(outi)
p 368 926 100 0 -1 def(OUTJ):$(outj)
p 368 862 100 0 -1 def(OUTK):$(outk)
p 368 798 100 0 -1 def(OUTL):$(outl)
p 368 734 100 0 -1 def(OUTM):$(outm)
p 368 670 100 0 -1 def(OUTN):$(outn)
p 352 222 100 0 0 def(OUTO):0.0
p -32 -18 100 0 1 name:$(tcs)$(cad)
p 320 1184 75 768 -1 palrm(OUTF):NMS
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -424 1592 100 0 ICID
xform 0 -432 1632
use inhier -424 1688 100 0 DIR
xform 0 -432 1728
[comments]
