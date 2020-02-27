[schematic2]
uniq 68
[tools]
[detail]
w 674 816 100 0 n#67 ecad20.ecad20#66.STLK 336 112 672 112 672 1472 1040 1472 estringouts.null.SLNK
w 1112 1362 100 0 n#64 estringouts.null.FLNK 1296 1488 1360 1488 1360 1360 912 1360 912 1232 1040 1232 elongouts.busy.SLNK
w 1544 738 100 0 n#63 elongouts.start.FLNK 1296 736 1840 736 1840 944 1936 944 tcsSubCadWait.tcsSubCadWait#55.START
w 1112 1106 100 0 n#61 elongouts.busy.FLNK 1296 1264 1360 1264 1360 1104 912 1104 912 960 1040 960 elongouts.mark.SLNK
w 968 1266 100 0 n#59 hwin.hwin#58.in 944 1264 1040 1264 elongouts.busy.DOL
w 968 738 100 0 n#54 hwin.hwin#52.in 944 736 1040 736 elongouts.start.DOL
w 968 994 100 0 n#53 hwin.hwin#51.in 944 992 1040 992 elongouts.mark.DOL
w 1112 834 100 0 n#49 elongouts.mark.FLNK 1296 992 1360 992 1360 832 912 832 912 704 1040 704 elongouts.start.SLNK
w 1320 1746 100 0 n#46 ecad20.ecad20#66.VAL 336 1744 2352 1744 outhier.VAL.p
w 1590 1652 100 0 n#9 ecad20.ecad20#66.MESS 336 1712 864 1712 864 1648 2352 1648 outhier.MESS.p
w -162 1716 100 0 n#8 inhier.ICID.P -384 1648 -304 1648 -304 1712 16 1712 ecad20.ecad20#66.ICID
w -202 1746 100 0 n#7 inhier.DIR.P -384 1744 16 1744 ecad20.ecad20#66.DIR
s 1008 64 100 0 when the STLK link is triggered.
s 1008 96 100 0 be cloned from this one where the outputs are only sent 
s 1008 128 100 0 this might cause a problem then a custom schematic should
s 1008 160 100 0 innocuous but will leave the subsystem CAD marked. If
s 1008 192 100 0 as in the last valid command. This is fairly
s 1008 224 100 0 rejected by the TCS. The data sent will be the same
s 1008 256 100 0 fields of the subsystem CAD even if the command is
s 1008 288 100 0 Note that the output links will send data to the input
s 1808 608 100 0 well as command rejection.
s 1808 640 100 0 This symbol handles timeouts on command acknowledgement as
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -336 100 0 20 October 1996
s 1808 2000 100 0 $Id: tcsMechanismCad20.sch,v 1.1.1.1 1998/11/08 00:20:43 epics Exp $
s 656 1936 200 0 Trigger a subsystem CAD
[cell use]
use ecad20 40 24 100 0 ecad20#66
xform 0 176 912
p 112 752 100 0 0 PREC:4
p 156 0 100 1024 1 name:$(tcs)$(cad)
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
p 112 1648 100 0 0 DESC:Trigger a subsystem CAD on START
p 416 686 100 0 -1 def(OUTN):$(outn)
use estringouts 1064 1400 100 0 null
xform 0 1168 1472
p 976 1438 100 0 0 VAL:
p 1072 1566 100 0 -1 DESC:Supply an empty string
p 1440 1454 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
p 1152 1392 100 1024 0 name:$(tcs)$(cad)$(I)
use hwin 776 952 100 0 hwin#51
xform 0 848 992
p 755 984 100 0 -1 val(in):$(CAD_MARK)
use hwin 776 696 100 0 hwin#52
xform 0 848 736
p 755 728 100 0 -1 val(in):$(CAD_START)
use hwin 776 1224 100 0 hwin#58
xform 0 848 1264
p 755 1256 100 0 -1 val(in):$(CAR_BUSY)
use elongouts 1064 872 100 0 mark
xform 0 1168 960
p 1088 1054 100 0 -1 DESC:Mark directive
p 880 878 100 0 0 OMSL:closed_loop
p 1376 926 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1264 864 100 1024 1 name:$(tcs)$(cad)$(I)
p 1296 928 75 768 -1 pproc(OUT):PP
use elongouts 1064 616 100 0 start
xform 0 1168 704
p 1088 798 100 0 -1 DESC:Start Directive
p 880 622 100 0 0 OMSL:closed_loop
p 1376 670 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1280 608 100 1024 1 name:$(tcs)$(cad)$(I)
p 1296 672 75 768 -1 pproc(OUT):PP
use elongouts 1064 1144 100 0 busy
xform 0 1168 1232
p 1088 1326 100 0 -1 DESC:Busy state
p 880 1150 100 0 0 OMSL:closed_loop
p 1376 1198 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
p 1264 1136 100 1024 1 name:$(tcs)$(cad)$(I)
p 1296 1200 75 768 -1 pproc(OUT):PP
use tcsSubCadWait 1960 712 100 0 tcsSubCadWait#55
xform 0 2072 856
p 2016 1038 100 0 -1 seta:top $(tcs)$(cad):
p 2016 1006 100 0 -1 setb:index 0
use outhier 2344 1704 100 0 VAL
xform 0 2336 1744
use outhier 2344 1608 100 0 MESS
xform 0 2336 1648
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -376 1704 100 0 DIR
xform 0 -384 1744
use inhier -376 1608 100 0 ICID
xform 0 -384 1648
[comments]
