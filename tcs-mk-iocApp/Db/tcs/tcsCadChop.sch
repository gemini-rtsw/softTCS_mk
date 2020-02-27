[schematic2]
uniq 71
[tools]
[detail]
w 1416 -117 100 0 n#70 elongouts.start.FLNK 1152 -128 1728 -128 1728 864 1904 864 tcsSubCadWait.tcsSubCadWait#69.START
w 1000 -5 100 0 n#68 elongouts.busy.FLNK 1152 160 1248 160 1248 -16 800 -16 800 -160 896 -160 elongouts.start.SLNK
w 1000 267 100 0 n#67 estringouts.null.FLNK 1152 384 1248 384 1248 256 800 256 800 128 896 128 elongouts.busy.SLNK
w 1000 507 100 0 n#66 estringouts.decsReset.FLNK 1152 640 1248 640 1248 496 800 496 800 368 896 368 estringouts.null.SLNK
w 792 -117 100 0 n#65 hwin.hwin#64.in 736 -128 896 -128 elongouts.start.DOL
w 792 171 100 0 n#62 hwin.hwin#61.in 736 160 896 160 elongouts.busy.DOL
w 752 667 100 0 n#55 ecad8.ecad8#23.VALE 560 1232 656 1232 656 656 896 656 estringouts.decsReset.DOL
w 760 891 100 0 n#54 ecad8.ecad8#23.VALD 560 1296 672 1296 672 880 896 880 estringouts.decsPause.DOL
w 768 1083 100 0 n#53 ecad8.ecad8#23.VALC 560 1360 688 1360 688 1072 896 1072 estringouts.decsFreeze.DOL
w 776 1275 100 0 n#52 ecad8.ecad8#23.VALB 560 1424 704 1424 704 1264 896 1264 estringouts.decsDemand.DOL
w 1000 747 100 0 n#51 estringouts.decsPause.FLNK 1152 864 1248 864 1248 736 800 736 800 624 896 624 estringouts.decsReset.SLNK
w 1000 955 100 0 n#50 estringouts.decsFreeze.FLNK 1152 1056 1248 1056 1248 944 800 944 800 848 896 848 estringouts.decsPause.SLNK
w 1000 1147 100 0 n#49 estringouts.decsDemand.FLNK 1152 1248 1248 1248 1248 1136 800 1136 800 1040 896 1040 estringouts.decsFreeze.SLNK
w 1000 1339 100 0 n#48 estringouts.chopDemand.FLNK 1152 1440 1248 1440 1248 1328 800 1328 800 1232 896 1232 estringouts.decsDemand.SLNK
w 784 1467 100 0 n#47 ecad8.ecad8#23.VALA 560 1488 720 1488 720 1456 896 1456 estringouts.chopDemand.DOL
w 784 1435 100 0 n#46 ecad8.ecad8#23.STLK 560 816 720 816 720 1424 896 1424 estringouts.chopDemand.SLNK
w 1296 1682 100 0 n#34 ecad8.ecad8#23.VAL 560 1680 2080 1680 outhier.VAL.p
w 1318 1586 100 0 n#9 ecad8.ecad8#23.MESS 560 1648 592 1648 592 1584 2080 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad8.ecad8#23.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad8.ecad8#23.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1792 2000 100 0 $Id: tcsCadChop.sch,v 1.4 2000/06/19 00:52:59 cjm Exp $
s 1808 -336 100 0 20 October 1996
[cell use]
use tcsSubCadWait 1904 631 100 0 tcsSubCadWait#69
xform 0 2040 776
p 1968 608 100 0 1 seta:top $(tcs)$(cad):
p 1968 576 100 0 1 setb:index 0
use hwin 544 -169 100 0 hwin#64
xform 0 640 -128
p 547 -136 100 0 -1 val(in):$(CAD_START)
use hwin 544 119 100 0 hwin#61
xform 0 640 160
p 547 152 100 0 -1 val(in):$(CAR_BUSY)
use elongouts 896 -249 100 0 start
xform 0 1024 -160
p 960 -64 100 0 -1 DESC:Busy state
p 736 -242 100 0 0 OMSL:closed_loop
p 1232 -192 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 1152 -192 75 768 -1 pproc(OUT):PP
use elongouts 896 39 100 0 busy
xform 0 1024 128
p 960 224 100 0 -1 DESC:Busy state
p 736 46 100 0 0 OMSL:closed_loop
p 1232 96 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
p 1152 96 75 768 -1 pproc(OUT):PP
use estringouts 896 295 100 0 null
xform 0 1024 368
p 848 448 100 0 -1 DESC:Supply an empty string
p 832 334 100 0 0 VAL:
p 1232 352 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
p 1008 288 100 1024 0 name:$(top)$(cad)$(I)
use estringouts 896 551 100 0 decsReset
xform 0 1024 624
p 928 688 100 0 -1 DESC:DECS reset On/Off
p 832 430 100 0 0 OMSL:closed_loop
p 832 590 100 0 0 VAL:Off
p 1232 608 100 0 -1 def(OUT):$(m2)chopControl.E
use estringouts 896 775 100 0 decsPause
xform 0 1024 848
p 928 912 100 0 -1 DESC:DECS pause On/Off
p 832 654 100 0 0 OMSL:closed_loop
p 832 814 100 0 0 VAL:Off
p 1232 832 100 0 -1 def(OUT):$(m2)chopControl.D
use estringouts 896 967 100 0 decsFreeze
xform 0 1024 1040
p 928 1104 100 0 -1 DESC:DECS freeze On/Off
p 832 846 100 0 0 OMSL:closed_loop
p 832 1006 100 0 0 VAL:Off
p 1232 1024 100 0 -1 def(OUT):$(m2)chopControl.C
use estringouts 896 1159 100 0 decsDemand
xform 0 1024 1232
p 928 1296 100 0 -1 DESC:DECS demand On/Off
p 832 1038 100 0 0 OMSL:closed_loop
p 832 1198 100 0 0 VAL:Off
p 1232 1216 100 0 -1 def(OUT):$(m2)chopControl.B
use estringouts 896 1351 100 0 chopDemand
xform 0 1024 1424
p 912 1504 100 0 -1 DESC:Chop demand On/Off
p 832 1230 100 0 0 OMSL:closed_loop
p 832 1390 100 0 0 VAL:Off
p 1232 1408 100 0 -1 def(OUT):$(m2)chopControl.A
use outhier 2072 1544 100 0 MESS
xform 0 2064 1584
use outhier 2072 1640 100 0 VAL
xform 0 2064 1680
use ecad8 264 728 100 0 ecad8#23
xform 0 400 1232
p 304 1790 100 0 -1 DESC:Implements chop command
p 336 1880 100 0 0 FTVA:STRING
p 432 1166 100 0 -1 FTVF:LONG
p 320 910 100 0 1 SNAM:$(snam)
p 640 1454 100 0 0 def(OUTA):0.0
p 304 670 100 0 1 name:$(tcs)$(cad)
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -152 1640 100 0 DIR
xform 0 -160 1680
use inhier -152 1544 100 0 ICID
xform 0 -160 1584
[comments]
