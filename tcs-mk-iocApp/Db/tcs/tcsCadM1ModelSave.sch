[schematic2]
uniq 7
[tools]
[detail]
w 432 1155 100 0 n#1 ecad8.ecad8#23.VALA 288 1152 576 1152 576 1072 992 1072 estringouts.outa.DOL
w 432 483 100 0 n#2 ecad8.ecad8#23.STLK 288 480 576 480 576 1040 992 1040 estringouts.outa.SLNK
w 1296 1347 100 0 n#3 ecad8.ecad8#23.VAL 288 1344 2304 1344 outhier.VAL.p
w 552 1315 100 0 n#4 ecad8.ecad8#23.MESS 288 1312 816 1312 816 1248 2304 1248 outhier.MESS.p
w -392 1251 100 0 n#5 inhier.ICID.P -432 1248 -352 1248 -352 1312 -32 1312 ecad8.ecad8#23.ICID
w -232 1347 100 0 n#6 inhier.DIR.P -432 1344 -32 1344 ecad8.ecad8#23.DIR
s 8 1664 200 0 Trigger downstream processing on START only
s 1808 2000 100 0 $Id: tcsCadM1ModelSave.sch,v 1.1 2013/09/11 15:43:46 cjm Exp $
s 1808 -336 100 0 20 October 1996
s 2032 -192 100 0 Gemini Telescope Control System
[cell use]
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use estringouts 992 967 100 0 outa
xform 0 1120 1040
p 1008 1120 100 0 -1 DESC:Output VALA from CAD
p 928 846 100 0 0 OMSL:closed_loop
p 928 1006 100 0 0 VAL:
p 1344 1024 100 0 -1 def(OUT):$(outa)
p 1104 960 100 1024 0 name:$(tcs)$(cad)$(I)
p 1256 1032 75 768 -1 pproc(OUT):PP
use outhier 2296 1208 100 0 MESS
xform 0 2288 1248
use outhier 2296 1304 100 0 VAL
xform 0 2288 1344
use ecad8 -8 392 100 0 ecad8#23
xform 0 128 896
p -80 1438 100 0 -1 DESC:Set output on START only
p 80 1142 100 0 0 FTVA:STRING
p 80 1086 100 0 0 FTVB:STRING
p 160 686 100 0 0 FTVH:STRING
p 64 736 100 0 0 PREC:4
p 48 574 100 0 -1 SNAM:$(snam)
p 352 1118 100 0 0 def(OUTA):$(outa)
p 352 1054 100 0 -1 def(OUTB):0.0
p 352 990 100 0 -1 def(OUTC):0.0
p 352 926 100 0 -1 def(OUTD):0.0
p 352 862 100 0 -1 def(OUTE):0.0
p 352 798 100 0 -1 def(OUTF):0.0
p 352 734 100 0 0 def(OUTG):0.0
p 368 670 100 0 0 def(OUTH):0.0
p 32 334 100 0 1 name:$(tcs)$(cad)
p 288 1120 75 768 -1 pproc(OUTA):NPP
p 288 1056 75 768 -1 pproc(OUTB):NPP
p 288 672 75 768 -1 pproc(OUTH):NPP
use inhier -424 1208 100 0 ICID
xform 0 -432 1248
use inhier -424 1304 100 0 DIR
xform 0 -432 1344
[comments]
