[schematic2]
uniq 29
[tools]
[detail]
w 1702 1010 -100 0 c#26 ecad8.ecad8#28.VAL 1344 1008 2096 1008 outhier.VAL2.p
w 1790 914 -100 0 c#27 ecad8.ecad8#28.MESS 1344 976 1376 976 1376 912 2240 912 outhier.MESS2.p
w 846 980 -100 0 c#25 inhier.ICID2.P 624 912 704 912 704 976 1024 976 ecad8.ecad8#28.ICID
w 806 1010 -100 0 c#24 inhier.DIR2.P 624 1008 1024 1008 ecad8.ecad8#28.DIR
w 550 1682 100 0 n#6 ecad8.ecad8#16.VAL 192 1680 944 1680 outhier.VAL1.p
w 638 1586 100 0 n#9 ecad8.ecad8#16.MESS 192 1648 224 1648 224 1584 1088 1584 outhier.MESS1.p
w -306 1652 100 0 n#8 inhier.ICID1.P -528 1584 -448 1584 -448 1648 -128 1648 ecad8.ecad8#16.ICID
w -346 1682 100 0 n#7 inhier.DIR1.P -528 1680 -128 1680 ecad8.ecad8#16.DIR
s 1840 2000 100 0 $Id: tcsCadHandset.sch,v 1.2 2002/05/14 09:13:49 ajf Exp $
s 1808 -336 100 0 27 Nov 1997
s 1808 -304 100 0 D.L.Terrett
s 2032 -192 100 0 Gemini Telescope Control System
[cell use]
use ecad8 1048 56 100 0 ecad8#28
xform 0 1184 560
p 1120 1208 100 0 0 FTVA:LONG
p 1120 1176 100 0 0 FTVB:LONG
p 1120 1144 100 0 0 FTVC:LONG
p 1120 1112 100 0 0 FTVD:LONG
p 1120 1080 100 0 0 FTVE:LONG
p 1120 1048 100 0 0 FTVF:LONG
p 1120 1016 100 0 0 FTVG:LONG
p 1120 528 100 0 0 FTVH:LONG
p 1088 0 100 0 1 SNAM:tcsCADhandset
p 1120 120 100 0 0 def(INPA):
p 1120 -8 100 0 0 def(INPB):
p 1120 -136 100 0 0 def(INPC):
p 1120 -264 100 0 0 def(INPD):
p 1120 -392 100 0 0 def(INPE):
p 1120 -520 100 0 0 def(INPF):
p 1120 -648 100 0 0 def(INPG):
p 1120 -776 100 0 0 def(INPH):
p 1424 784 100 0 -1 def(OUTA):$(tcs)hs:$(prefix)Offset.A
p 1024 -368 100 0 0 def(OUTB):
p 1424 656 100 0 0 def(OUTC):
p 1424 592 100 0 0 def(OUTD):
p 1424 144 100 0 -1 def(STLK):$(tcs)hs:$(prefix)Offset.FLNK
p 1088 46 100 0 1 name:$(tcs)$(prefix)Handset
p 1120 -296 100 0 0 typ(INPD):path
p 1120 -552 100 0 0 typ(INPF):path
p 1120 -808 100 0 0 typ(INPH):path
p 1120 -2472 100 0 0 typ(OUTA):path
use ecad8 -104 728 100 0 ecad8#16
xform 0 32 1232
p -32 1880 100 0 0 FTVA:DOUBLE
p -32 1848 100 0 0 FTVB:LONG
p -32 1816 100 0 0 FTVC:LONG
p -32 1784 100 0 0 FTVD:LONG
p -32 1752 100 0 0 FTVE:LONG
p -32 1720 100 0 0 FTVF:LONG
p -32 1688 100 0 0 FTVG:LONG
p -32 1200 100 0 0 FTVH:LONG
p -64 672 100 0 1 SNAM:tcsCADhandConfig
p -32 792 100 0 0 def(INPA):
p -32 664 100 0 0 def(INPB):
p -32 536 100 0 0 def(INPC):
p -32 408 100 0 0 def(INPD):
p -32 280 100 0 0 def(INPE):
p -32 152 100 0 0 def(INPF):
p -32 24 100 0 0 def(INPG):
p -32 -104 100 0 0 def(INPH):
p 272 1456 100 0 -1 def(OUTA):$(tcs)hs:$(prefix)Offset.B
p 272 1392 100 0 -1 def(OUTB):$(tcs)hs:$(prefix)Offset.C
p 272 1328 100 0 -1 def(OUTC):$(tcs)hs:$(prefix)Offset.D
p -64 718 100 0 1 name:$(tcs)$(prefix)HandConfig
p -32 376 100 0 0 typ(INPD):path
p -32 120 100 0 0 typ(INPF):path
p -32 -136 100 0 0 typ(INPH):path
p -32 -1800 100 0 0 typ(OUTA):path
use outhier 2232 872 100 0 MESS2
xform 0 2224 912
use outhier 2088 968 100 0 VAL2
xform 0 2080 1008
use outhier 1080 1544 100 0 MESS1
xform 0 1072 1584
use outhier 936 1640 100 0 VAL1
xform 0 928 1680
use inhier 632 872 100 0 ICID2
xform 0 624 912
use inhier 632 968 100 0 DIR2
xform 0 624 1008
use inhier -520 1544 100 0 ICID1
xform 0 -528 1584
use inhier -520 1640 100 0 DIR1
xform 0 -528 1680
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
[comments]
