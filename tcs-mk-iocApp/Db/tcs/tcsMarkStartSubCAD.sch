[schematic2]
uniq 24
[tools]
[detail]
w 776 610 100 0 n#23 eaos.eaos#1.FLNK 912 864 1056 864 1056 608 544 608 544 480 640 480 tcsSubCadWait.tcsSubCadWait#22.START
w 120 866 100 0 n#21 eaos.Busy.FLNK -96 864 384 864 384 1072 656 1072 eaos.eaos#0.SLNK
w -232 962 100 0 n#20 estringouts.Null.FLNK -96 1088 -32 1088 -32 960 -384 960 -384 832 -352 832 eaos.Busy.SLNK
w -480 1074 100 0 n#19 inhier.SubCadStart.P -560 1072 -352 1072 estringouts.Null.SLNK
w -416 866 100 0 n#18 hwin.hwin#17.in -432 864 -352 864 eaos.Busy.DOL
w 1126 1042 100 0 n#8 eaos.eaos#0.OUT 912 1040 1376 1040 outhier.fmark.p
w 1126 802 100 0 n#7 eaos.eaos#1.OUT 912 800 1376 800 outhier.fstart.p
w 718 948 100 0 n#6 eaos.eaos#0.FLNK 912 1104 1056 1104 1056 944 416 944 416 800 592 800 592 832 656 832 eaos.eaos#1.SLNK
w 638 866 100 0 n#5 hwin.START.in 656 864 656 864 eaos.eaos#1.DOL
w 638 1106 100 0 n#3 hwin.MARK.in 656 1104 656 1104 eaos.eaos#0.DOL
s 1008 1344 100 0 $Id: tcsMarkStartSubCAD.sch,v 1.1.1.1 1998/11/08 00:20:38 epics Exp $
s 1248 112 100 0 Issue Subsystem CAD (no parameters)
[cell use]
use tcsSubCadWait 664 248 100 0 tcsSubCadWait#22
xform 0 776 392
p 704 238 100 0 -1 setb:timeout 3.0
p 704 206 100 0 -1 setc:top $(top)$(prefix)$(cad)
p 704 174 100 0 -1 setd:index 2
use hwin 488 1064 100 0 MARK
xform 0 560 1104
p 478 1032 100 0 0 typ(in):val
p 432 1102 100 0 -1 val(in):$(CAD_MARK)
use hwin 488 824 100 0 START
xform 0 560 864
p 478 792 100 0 0 typ(in):val
p 432 862 100 0 -1 val(in):$(CAD_START)
use hwin -600 824 100 0 hwin#17
xform 0 -528 864
p -621 856 100 0 -1 val(in):$(CAR_BUSY)
use eaos 680 744 100 0 eaos#1
xform 0 784 832
p 400 814 100 0 0 OMSL:closed_loop
p 1056 814 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 640 734 100 0 1 name:$(tcs)$(prefix)S$(subcad)
p 912 800 75 768 -1 pproc(OUT):PP
use eaos 680 984 100 0 eaos#0
xform 0 784 1072
p 400 1054 100 0 0 OMSL:closed_loop
p 400 1086 100 0 0 PINI:NO
p 1088 1054 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 608 974 100 0 1 name:$(tcs)$(prefix)M$(subcad)
p 912 1040 75 768 -1 pproc(OUT):PP
use eaos -328 744 100 0 Busy
xform 0 -224 832
p -288 926 100 0 -1 DESC:Output BUSY
p -608 814 100 0 0 OMSL:closed_loop
p -244 704 100 1024 1 name:$(tcs)$(prefix)$(subcad)$(I)
p -96 800 75 768 -1 pproc(OUT):PP
p -32 798 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
use estringouts -328 1000 100 0 Null
xform 0 -224 1072
p -416 1038 100 0 0 VAL:
p -336 1166 100 0 -1 DESC:Output an empty string
p -244 960 100 1024 1 name:$(tcs)$(prefix)$(subcad)$(I)
p -16 1038 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
use inhier -624 1008 100 0 SubCadStart
xform 0 -560 1072
use bb200tr -752 -168 -100 0 frame
xform 0 528 656
use outhier 1368 1000 100 0 fmark
xform 0 1360 1040
use outhier 1368 760 100 0 fstart
xform 0 1360 800
[comments]
