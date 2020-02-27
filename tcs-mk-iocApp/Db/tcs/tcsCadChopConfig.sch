[schematic2]
uniq 83
[tools]
[detail]
w 696 1451 100 0 n#82 ecad8.ecad8#23.VALE 304 1360 432 1360 432 1440 1008 1440 1008 1488 estringouts.mode.SDIS
w 1104 619 100 0 n#81 ecad8.ecad8#23.VALD 304 1424 624 1424 624 608 1632 608 eaos.dutyCycle1.DOL
w 1696 763 100 0 n#80 eaos.freq1.FLNK 1888 928 1968 928 1968 752 1472 752 1472 576 1632 576 eaos.dutyCycle1.SLNK
w 1184 -85 100 0 n#79 elongouts.start.FLNK 928 -96 1488 -96 1488 224 1664 224 tcsSubCadWait.tcsSubCadWait#78.START
w 768 -5 100 0 n#77 elongouts.busy.FLNK 928 128 1040 128 1040 -16 544 -16 544 -128 672 -128 elongouts.start.SLNK
w 768 219 100 0 n#76 estringouts.null.FLNK 928 320 1040 320 1040 208 544 208 544 96 672 96 elongouts.busy.SLNK
w 1232 427 100 0 n#75 eaos.dutyCycle1.FLNK 1888 608 1968 608 1968 416 544 416 544 304 672 304 estringouts.null.SLNK
w 552 -85 100 0 n#74 hwin.hwin#72.in 480 -96 672 -96 elongouts.start.DOL
w 552 139 100 0 n#73 hwin.hwin#71.in 480 128 672 128 elongouts.busy.DOL
w 1040 1051 100 0 n#47 junction 656 1040 1472 1040 1472 928 1632 928 eaos.freq1.DOL
w 658 1232 100 0 n#47 ecad8.ecad8#23.VALC 304 1488 656 1488 656 928 1008 928 eaos.freq.DOL
w 1512 907 100 0 n#60 eaos.freq.FLNK 1264 928 1440 928 1440 896 1632 896 eaos.freq1.SLNK
w 1056 1371 100 0 n#46 junction 688 1360 1472 1360 1472 1264 1632 1264 estringouts.sync1.DOL
w 472 1554 100 0 n#46 ecad8.ecad8#23.VALB 304 1552 688 1552 688 1264 1008 1264 estringouts.sync.DOL
w 1080 1627 100 0 n#41 junction 736 1616 1472 1616 1472 1552 1632 1552 estringouts.mode1.DOL
w 496 1618 100 0 n#41 ecad8.ecad8#23.VALA 304 1616 736 1616 736 1552 1008 1552 estringouts.mode.DOL
w 1408 1115 100 0 n#58 estringouts.sync1.FLNK 1888 1248 1968 1248 1968 1104 896 1104 896 896 1008 896 eaos.freq.SLNK
w 1512 1243 100 0 n#57 estringouts.sync.FLNK 1264 1248 1440 1248 1440 1232 1632 1232 estringouts.sync1.SLNK
w 1408 1419 100 0 n#56 estringouts.mode1.FLNK 1888 1536 1968 1536 1968 1408 896 1408 896 1232 1008 1232 estringouts.sync.SLNK
w 1512 1531 100 0 n#54 estringouts.mode.FLNK 1264 1536 1440 1536 1440 1520 1632 1520 estringouts.mode1.SLNK
w 738 1256 100 0 n#40 ecad8.ecad8#23.STLK 304 944 736 944 736 1520 1008 1520 estringouts.mode.SLNK
w 1040 1810 100 0 n#34 ecad8.ecad8#23.VAL 304 1808 1824 1808 outhier.VAL.p
w 1062 1714 100 0 n#9 ecad8.ecad8#23.MESS 304 1776 336 1776 336 1712 1824 1712 outhier.MESS.p
w -194 1780 100 0 n#8 inhier.ICID.P -416 1712 -336 1712 -336 1776 -16 1776 ecad8.ecad8#23.ICID
w -234 1810 100 0 n#7 inhier.DIR.P -416 1808 -16 1808 ecad8.ecad8#23.DIR
s 896 640 100 0 up from the SCS.
s 896 672 100 0 duty cycle to the SAD. This is now picked
s 896 704 100 0 Note that we no longer have to write the
s -576 368 100 0 is sent before the first valid START.
s -576 400 100 0 the subsystem CAD to get marked and it can be sent null data if the CLEAR
s -576 432 100 0 also fire when a CLEAR directive is issued for example. This causes
s -576 464 100 0 when a START directive is received. The output links of a CAD  
s -576 496 100 0 to ensure that data is only written to the SAD and the SCS
s -576 528 100 0 This somewhat complicated schematic is implemented this way
s 1808 -336 100 0 20 October 1996
s 1792 2000 100 0 $Id: tcsCadChopConfig.sch,v 1.5 2003/04/09 10:09:33 dlt Exp $
s 2032 -192 100 0 Gemini Telescope Control System
s 976 1680 100 0 This record is disabled when the 
s 976 1648 100 0 when the chop mode is NONE
[cell use]
use tcsSubCadWait 1664 -9 100 0 tcsSubCadWait#78
xform 0 1800 136
p 1728 -16 100 0 1 seta:top $(tcs)$(cad):
p 1728 -64 100 0 1 setb:index 0
use hwin 288 -137 100 0 hwin#72
xform 0 384 -96
p 291 -104 100 0 -1 val(in):$(CAD_START)
use hwin 288 87 100 0 hwin#71
xform 0 384 128
p 291 120 100 0 -1 val(in):$(CAR_BUSY)
use elongouts 672 7 100 0 busy
xform 0 800 96
p 736 176 100 0 -1 DESC:Busy state
p 512 14 100 0 0 OMSL:closed_loop
p 1008 64 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IVAL
p 784 0 100 1024 0 name:$(top)$(cad)$(I)
p 928 64 75 768 -1 pproc(OUT):PP
use elongouts 672 -217 100 0 start
xform 0 800 -128
p 736 -48 100 0 -1 DESC:Start directive
p 512 -210 100 0 0 OMSL:closed_loop
p 1008 -160 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 784 -224 100 1024 0 name:$(top)$(cad)$(I)
p 928 -160 75 768 -1 pproc(OUT):PP
use estringouts 1656 1160 100 0 sync1
xform 0 1760 1232
p 1648 1310 100 0 -1 DESC:Writes sync source to SCS
p 1568 1038 100 0 0 OMSL:closed_loop
p 1568 1198 100 0 0 VAL:
p 1984 1200 100 0 -1 def(OUT):$(m2)chopConfig.B
use estringouts 1656 1448 100 0 mode1
xform 0 1760 1520
p 1648 1598 100 0 -1 DESC:Writes chop mode to SCS
p 1792 1358 100 0 0 DISV:1
p 1568 1326 100 0 0 OMSL:closed_loop
p 1568 1486 100 0 0 VAL:
p 1984 1502 100 0 -1 def(OUT):$(m2)chopConfig.A
p 1888 1504 75 768 -1 pproc(OUT):NPP
use estringouts 1032 1448 100 0 mode
xform 0 1136 1520
p 1024 1598 100 0 -1 DESC:Writes chop mode to SAD
p 1168 1358 100 0 0 DISV:3
p 944 1326 100 0 0 OMSL:closed_loop
p 944 1486 100 0 0 VAL:
p 1280 1472 100 0 -1 def(OUT):$(sad)chopMode
p 1264 1504 75 768 -1 pproc(OUT):PP
use estringouts 1032 1160 100 0 sync
xform 0 1136 1232
p 1024 1310 100 0 -1 DESC:Writes sync source to SAD
p 944 1038 100 0 0 OMSL:closed_loop
p 944 1198 100 0 0 VAL:
p 1280 1184 100 0 -1 def(OUT):$(sad)chopSync
p 1264 1216 75 768 -1 pproc(OUT):PP
use estringouts 672 231 100 0 null
xform 0 800 304
p 672 384 100 0 -1 DESC:Supply an empty string
p 608 270 100 0 0 VAL:
p 1008 288 100 0 -1 def(OUT):$(tcs)$(prefix)CommSentC.IMSS
p 784 224 100 1024 0 name:$(top)$(cad)$(I)
use eaos 1656 488 100 0 dutyCycle1
xform 0 1760 576
p 1632 670 100 0 -1 DESC:Writes chop duty cycle to SCS
p 1600 302 100 0 0 EGU:percentage
p 1376 558 100 0 0 OMSL:closed_loop
p 2000 542 100 0 -1 def(OUT):$(m2)chopConfig.D
use eaos 1656 808 100 0 freq1
xform 0 1760 896
p 1632 990 100 0 -1 DESC:Writes chop frequency to SCS
p 1600 622 100 0 0 EGU:Hz
p 1376 878 100 0 0 OMSL:closed_loop
p 1984 862 100 0 -1 def(OUT):$(m2)chopConfig.C
use eaos 1032 808 100 0 freq
xform 0 1136 896
p 1008 990 100 0 -1 DESC:Writes chop frequency to SAD
p 976 622 100 0 0 EGU:Hz
p 752 878 100 0 0 OMSL:closed_loop
p 1280 832 100 0 -1 def(OUT):$(sad)chopFreq
p 1264 864 75 768 -1 pproc(OUT):PP
use ecad8 8 856 100 0 ecad8#23
xform 0 144 1360
p -32 1918 100 0 -1 DESC:Implements the TCS chopConfig command
p 144 1614 100 0 -1 FTVA:STRING
p 160 1534 100 0 -1 FTVB:STRING
p 160 1486 100 0 -1 FTVC:DOUBLE
p 160 1422 100 0 -1 FTVD:DOUBLE
p 176 1358 100 0 -1 FTVE:LONG
p 176 1294 100 0 0 FTVF:STRING
p 176 1166 100 0 0 FTVH:STRING
p 80 2104 100 0 0 PREC:5
p 64 1038 100 0 1 SNAM:$(snam)
p 384 1614 100 0 0 def(OUTA):0.0
p 384 1534 100 0 0 def(OUTB):0.0
p 384 1438 100 0 0 def(OUTC):0.0
p 384 1390 100 0 0 def(OUTD):0.0
p 368 1326 100 0 0 def(OUTE):0.0
p 384 1198 100 0 0 def(OUTG):0.0
p 48 798 100 0 1 name:$(tcs)$(cad)
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 1816 1672 100 0 MESS
xform 0 1808 1712
use outhier 1816 1768 100 0 VAL
xform 0 1808 1808
use inhier -408 1672 100 0 ICID
xform 0 -416 1712
use inhier -408 1768 100 0 DIR
xform 0 -416 1808
[comments]
