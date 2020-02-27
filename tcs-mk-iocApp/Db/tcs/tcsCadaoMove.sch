[schematic2]
uniq 88
[tools]
[detail]
w 1064 299 100 0 n#87 elongouts.busy.FLNK 1248 576 1312 576 1312 288 864 288 864 32 992 32 elongouts.start.SLNK
w 1136 955 100 0 n#86 ecad8.ecad8#23.VALF 288 832 816 832 816 944 1504 944 1504 1088 1600 1088 eaos.outf.DOL
w 2056 1035 100 0 n#85 eaos.outf.OUT 1856 1024 2304 1024 outhier.c#84.p
w 1400 939 100 0 n#83 eaos.outf.FLNK 1856 1088 1984 1088 1984 928 864 928 864 784 992 784 estringouts.null.SLNK
w 1400 1067 100 0 n#82 estringouts.outa.FLNK 1248 1056 1600 1056 eaos.outf.SLNK
w 1480 75 100 0 n#80 elongouts.start.FLNK 1248 64 1760 64 1760 256 1888 256 tcsSubCadWait.tcsSubCadWait#55.START
w 760 1083 100 0 n#72 ecad8.ecad8#23.VALA 288 1152 576 1152 576 1072 992 1072 estringouts.outa.DOL
w 760 1051 100 0 n#70 ecad8.ecad8#23.STLK 288 480 576 480 576 1040 992 1040 estringouts.outa.SLNK
w 1064 674 100 0 n#64 estringouts.null.FLNK 1248 800 1312 800 1312 672 864 672 864 544 992 544 elongouts.busy.SLNK
w 920 578 100 0 n#59 hwin.hwin#58.in 896 576 992 576 elongouts.busy.DOL
w 920 66 100 0 n#54 hwin.hwin#52.in 896 64 992 64 elongouts.start.DOL
w 1272 1346 100 0 n#46 ecad8.ecad8#23.VAL 288 1344 2304 1344 outhier.VAL.p
w 1542 1252 100 0 n#9 ecad8.ecad8#23.MESS 288 1312 816 1312 816 1248 2304 1248 outhier.MESS.p
w -210 1316 100 0 n#8 inhier.ICID.P -432 1248 -352 1248 -352 1312 -32 1312 ecad8.ecad8#23.ICID
w -250 1346 100 0 n#7 inhier.DIR.P -432 1344 -32 1344 ecad8.ecad8#23.DIR
s 480 1760 100 0 This is a custom version of tcsmechanismAss
s 1760 -80 100 0 well as command rejection.
s 1760 -48 100 0 This symbol handles timeouts on command acknowledgement as
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -336 100 0 20 October 1996
s 1808 2000 100 0 $Id: tcsCadaoMove.sch,v 1.1 2002/10/02 08:30:44 cjm Exp $
s 368 1856 200 0 Trigger a subsystem assembly record
s -224 128 100 0 This schematic is derived from tcsMechanismCad. The outa parameter
s -224 96 100 0 is handled differently for historic reasons. At one time the CAD
s -224 64 100 0 fired all its outputs even if the command was rejected or cleared.
s -224 32 100 0 since many TCS commands had only one parameter this prevented most
s -224 0 100 0 subsystem commands being marked under these circumstances. The CAD was
s -224 -32 100 0 modified from GEM8.4 to prevent this.
s -224 -96 100 0 Since the TCS's simulation of Altair does not include assebly records,
s -224 -128 100 0 the link to the MODE field will be disconnected when using the simulator.
[cell use]
use outhier 2296 1304 100 0 VAL
xform 0 2288 1344
use outhier 2296 1208 100 0 MESS
xform 0 2288 1248
use outhier 2272 983 100 0 c#84
xform 0 2288 1024
use eaos 1600 967 100 0 outf
xform 0 1728 1056
p 1632 1152 100 0 -1 DESC:Na layer altitude
p 1568 782 100 0 0 EGU:km
p 1344 1038 100 0 0 OMSL:closed_loop
p 2032 1040 100 0 -1 def(OUT):$(tcs)sodium
p 1712 960 100 1024 0 name:$(tcs)$(cad)$(I)
p 1856 1024 75 768 -1 pproc(OUT):PP
use hwin 728 24 100 0 hwin#52
xform 0 800 64
p 707 56 100 0 -1 val(in):$(CAD_START)
use hwin 728 536 100 0 hwin#58
xform 0 800 576
p 707 568 100 0 -1 val(in):$(CAR_BUSY)
use elongouts 1016 -56 100 0 start
xform 0 1120 32
p 1040 126 100 0 -1 DESC:Start Directive
p 832 -50 100 0 0 OMSL:closed_loop
p 1328 -2 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1232 -64 100 1024 1 name:$(tcs)$(cad)$(I)
p 1248 0 75 768 -1 pproc(OUT):CA
use elongouts 1016 456 100 0 busy
xform 0 1120 544
p 1040 638 100 0 -1 DESC:Busy state
p 832 462 100 0 0 OMSL:closed_loop
p 1328 510 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
p 1216 448 100 1024 1 name:$(tcs)$(cad)$(I)
p 1248 512 75 768 -1 pproc(OUT):PP
use estringouts 1016 712 100 0 null
xform 0 1120 784
p 1024 878 100 0 -1 DESC:Supply an empty string
p 928 750 100 0 0 VAL:
p 1392 766 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
p 1104 704 100 1024 0 name:$(tcs)$(cad)$(I)
use estringouts 992 967 100 0 outa
xform 0 1120 1040
p 1008 1120 100 0 -1 DESC:Output VALA from CAD
p 928 846 100 0 0 OMSL:closed_loop
p 928 1006 100 0 0 VAL:
p 1344 1024 100 0 -1 def(OUT):$(outa)
p 1104 960 100 1024 0 name:$(tcs)$(cad)$(I)
p 1248 1024 75 768 -1 pproc(OUT):CA
use tcsSubCadWait 1912 24 100 0 tcsSubCadWait#55
xform 0 2024 168
p 1984 334 100 0 -1 seta:top $(tcs)$(cad):
p 1984 302 100 0 -1 setb:index 0
use ecad8 -8 392 100 0 ecad8#23
xform 0 128 896
p -80 1438 100 0 -1 DESC:Triggers a subsystem CAD on START only
p 80 1142 100 0 0 FTVA:STRING
p 80 1086 100 0 0 FTVB:STRING
p 160 686 100 0 0 FTVH:STRING
p 64 736 100 0 0 PREC:4
p 48 574 100 0 -1 SNAM:$(snam)
p 352 1118 100 0 0 def(OUTA):0.0
p 352 1054 100 0 -1 def(OUTB):$(outb)
p 352 990 100 0 -1 def(OUTC):$(outc)
p 352 926 100 0 -1 def(OUTD):$(outd)
p 352 862 100 0 -1 def(OUTE):$(oute)
p 352 798 100 0 -1 def(OUTF):$(outf)
p 352 734 100 0 0 def(OUTG):0.0
p 368 670 100 0 0 def(OUTH):0.0
p 32 334 100 0 1 name:$(tcs)$(cad)
p 288 1120 75 768 -1 pproc(OUTA):NPP
p 288 1056 75 768 -1 pproc(OUTB):CA
p 288 992 75 768 -1 pproc(OUTC):CA
p 288 928 75 768 -1 pproc(OUTD):CA
p 288 864 75 768 -1 pproc(OUTE):CA
p 288 800 75 768 -1 pproc(OUTF):CA
p 288 672 75 768 -1 pproc(OUTH):NPP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -424 1304 100 0 DIR
xform 0 -432 1344
use inhier -424 1208 100 0 ICID
xform 0 -432 1248
[comments]
