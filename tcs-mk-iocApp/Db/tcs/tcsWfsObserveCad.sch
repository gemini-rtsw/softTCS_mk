[schematic2]
uniq 13
[tools]
[detail]
w 472 117 100 0 n#1 ecad20.ecad20#66.STLK 336 112 608 112 608 784 992 784 estringouts.null.SLNK
w 1064 674 100 0 n#2 estringouts.null.FLNK 1248 800 1312 800 1312 672 864 672 864 544 992 544 elongouts.busy.SLNK
w 1496 50 100 0 n#3 elongouts.start.FLNK 1248 48 1792 48 1792 256 1888 256 tcsSubCadWait.tcsSubCadWait#55.START
w 1064 418 100 0 n#4 elongouts.busy.FLNK 1248 576 1312 576 1312 416 864 416 864 272 992 272 elongouts.mark.SLNK
w 920 578 100 0 n#5 hwin.hwin#58.in 896 576 992 576 elongouts.busy.DOL
w 920 50 100 0 n#6 hwin.hwin#52.in 896 48 992 48 elongouts.start.DOL
w 920 306 100 0 n#7 hwin.hwin#51.in 896 304 992 304 elongouts.mark.DOL
w 1064 146 100 0 n#8 elongouts.mark.FLNK 1248 304 1312 304 1312 144 864 144 864 16 992 16 elongouts.start.SLNK
w 1320 1746 100 0 n#9 ecad20.ecad20#66.VAL 336 1744 2352 1744 outhier.VAL.p
w 1590 1652 100 0 n#10 ecad20.ecad20#66.MESS 336 1712 864 1712 864 1648 2352 1648 outhier.MESS.p
w -162 1716 100 0 n#11 inhier.ICID.P -384 1648 -304 1648 -304 1712 16 1712 ecad20.ecad20#66.ICID
w -202 1746 100 0 n#12 inhier.DIR.P -384 1744 16 1744 ecad20.ecad20#66.DIR
s 1696 1280 100 0 vertsion of the SCS that doesn't support this command
s 1696 1312 100 0 this point as we may be connected to a
s 1696 1344 100 0 Note there is no attempt to trap errors at
s 656 1936 200 0 Trigger a subsystem CAD
s 1808 2000 100 0 $Id: tcsWfsObserveCad.sch,v 1.2 2005/12/01 15:02:08 cjm Exp $
s 1808 -336 100 0 20 October 1996
s 2032 -192 100 0 Gemini Telescope Control System
s 1760 -48 100 0 This symbol handles timeouts on command acknowledgement as
s 1760 -80 100 0 well as command rejection.
[cell use]
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use hwin 728 536 100 0 hwin#58
xform 0 800 576
p 707 568 100 0 -1 val(in):$(CAR_BUSY)
use hwin 728 8 100 0 hwin#52
xform 0 800 48
p 707 40 100 0 -1 val(in):$(CAD_START)
use hwin 728 264 100 0 hwin#51
xform 0 800 304
p 707 296 100 0 -1 val(in):$(CAD_MARK)
use elongouts 1016 456 100 0 busy
xform 0 1120 544
p 1040 638 100 0 -1 DESC:Busy state
p 832 462 100 0 0 OMSL:closed_loop
p 1328 510 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
p 1216 448 100 1024 1 name:$(tcs)$(cad)$(I)
p 1248 512 75 768 -1 pproc(OUT):PP
use elongouts 1016 -72 100 0 start
xform 0 1120 16
p 1040 110 100 0 -1 DESC:Start Directive
p 832 -66 100 0 0 OMSL:closed_loop
p 1328 -18 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1232 -80 100 1024 1 name:$(tcs)$(cad)$(I)
p 1248 -16 75 768 -1 pproc(OUT):CA
use elongouts 1016 184 100 0 mark
xform 0 1120 272
p 1040 366 100 0 -1 DESC:Mark directive
p 832 190 100 0 0 OMSL:closed_loop
p 1328 238 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1216 176 100 1024 1 name:$(tcs)$(cad)$(I)
p 1248 240 75 768 -1 pproc(OUT):CA
use estringouts 1016 712 100 0 null
xform 0 1120 784
p 976 848 100 0 -1 DESC:Supply an empty string
p 928 750 100 0 0 VAL:
p 1392 766 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
p 1104 704 100 1024 0 name:$(tcs)$(cad)$(I)
use ecad20 40 24 100 0 ecad20#66
xform 0 176 912
p 112 1648 100 0 0 DESC:Trigger a subsystem CAD on START
p 112 752 100 0 0 PREC:4
p 112 206 100 0 -1 SNAM:$(snam)
p 416 1518 100 0 -1 def(OUTA):$(outa)
p 416 1454 100 0 -1 def(OUTB):$(outb)
p 416 1390 100 0 -1 def(OUTC):$(outc)
p 416 1326 100 0 -1 def(OUTD):$(outd)
p 416 1262 100 0 -1 def(OUTE):$(oute)
p 416 1198 100 0 -1 def(OUTF):$(outf)
p 416 1134 100 0 -1 def(OUTG):$(outg)
p 416 1070 100 0 -1 def(OUTH):$(outh)
p 416 1006 100 0 -1 def(OUTI):$(outi)
p 416 942 100 0 -1 def(OUTJ):$(outj)
p 416 878 100 0 -1 def(OUTK):$(outk)
p 432 814 100 0 -1 def(OUTL):$(outl)
p 432 750 100 0 -1 def(OUTM):$(outm)
p 416 686 100 0 -1 def(OUTN):$(outn)
p 156 0 100 1024 1 name:$(tcs)$(cad)
use tcsSubCadWait 1912 24 100 0 tcsSubCadWait#55
xform 0 2024 168
p 1968 350 100 0 -1 seta:top $(tcs)$(cad):
p 1968 318 100 0 -1 setb:index 0
use outhier 2344 1608 100 0 MESS
xform 0 2336 1648
use outhier 2344 1704 100 0 VAL
xform 0 2336 1744
use inhier -376 1608 100 0 ICID
xform 0 -384 1648
use inhier -376 1704 100 0 DIR
xform 0 -384 1744
[comments]
