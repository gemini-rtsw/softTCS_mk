[schematic2]
uniq 38
[tools]
[detail]
w 1336 971 100 0 n#37 estringouts.rotTrackEqnx.FLNK 1376 1056 1696 1056 1696 960 1024 960 1024 832 1120 832 eaos.instrAA.SLNK
w 1344 1163 100 0 n#36 estringouts.rotTrackFrame.FLNK 1376 1248 1712 1248 1712 1152 1024 1152 1024 1040 1120 1040 estringouts.rotTrackEqnx.SLNK
w 1320 1371 100 0 n#35 eaos.instrPA.FLNK 1376 1488 1664 1488 1664 1360 1024 1360 1024 1232 1120 1232 estringouts.rotTrackFrame.SLNK
w 872 1467 100 0 n#34 ecad4.ecad4#20.STLK 560 1072 672 1072 672 1456 1120 1456 eaos.instrPA.SLNK
w 836 1075 100 0 n#33 ecad4.ecad4#20.VALD 560 1296 832 1296 832 864 1120 864 eaos.instrAA.DOL
w 704 1371 100 0 n#32 ecad4.ecad4#20.VALC 560 1360 896 1360 896 1072 1120 1072 estringouts.rotTrackEqnx.DOL
w 728 1435 100 0 n#31 ecad4.ecad4#20.VALB 560 1424 944 1424 944 1264 1120 1264 estringouts.rotTrackFrame.DOL
w 816 1491 100 0 n#30 ecad4.ecad4#20.VALA 560 1488 1120 1488 eaos.instrPA.DOL
w 918 1682 100 0 n#6 ecad4.ecad4#20.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad4.ecad4#20.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad4.ecad4#20.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad4.ecad4#20.DIR
s 1920 2000 100 0 $Id: tcsCadRotator.sch,v 1.1.1.1 1998/11/08 00:20:30 epics Exp $
s 1808 -336 100 0 16 July 1996
s 1808 -304 100 0 P.B. Taylor
s 2032 -192 100 0 Gemini Telescope Control System
[cell use]
use eaos 1120 743 100 0 instrAA
xform 0 1248 832
p 1184 912 100 0 -1 DESC:Instrument alignment angle
p 1088 558 100 0 0 EGU:degrees
p 864 814 100 0 0 OMSL:closed_loop
p 1456 800 100 0 -1 def(OUT):$(sad)instrAA
p 1376 736 100 1024 1 name:$(tcs)$(I)
p 1376 800 75 768 -1 pproc(OUT):PP
use eaos 1120 1367 100 0 instrPA
xform 0 1248 1456
p 1184 1536 100 0 -1 DESC:Instrument position angle
p 1088 1182 100 0 0 EGU:degrees
p 864 1438 100 0 0 OMSL:closed_loop
p 1456 1424 100 0 -1 def(OUT):$(sad)instrPA
p 1328 1360 100 1024 1 name:$(tcs)$(I)
p 1376 1424 75 768 -1 pproc(OUT):PP
use estringouts 1120 967 100 0 rotTrackEqnx
xform 0 1248 1040
p 1184 1104 100 0 -1 DESC:Equinox of rotator tracking frame
p 1056 846 100 0 0 OMSL:closed_loop
p 1456 1024 100 0 -1 def(OUT):$(sad)rotTrackEqnx
p 1408 960 100 1024 1 name:$(tcs)$(I)
p 1376 1024 75 768 -1 pproc(OUT):PP
use estringouts 1120 1159 100 0 rotTrackFrame
xform 0 1248 1232
p 1184 1296 100 0 -1 DESC:rotator tracking frame
p 1056 1038 100 0 0 OMSL:closed_loop
p 1456 1216 100 0 -1 def(OUT):$(sad)rotTrackFrame
p 1392 1152 100 1024 1 name:$(tcs)$(I)
p 1376 1216 75 768 -1 pproc(OUT):PP
use ecad4 264 984 100 0 ecad4#20
xform 0 400 1360
p 176 944 100 0 0 DESC:Rotator CAD record
p 304 1912 100 0 0 FTVA:DOUBLE
p 304 1880 100 0 0 FTVB:STRING
p 304 1848 100 0 0 FTVC:STRING
p 304 1816 100 0 0 FTVD:DOUBLE
p 304 2200 100 0 0 SNAM:tcsCADrotator
p 464 464 100 0 0 def(STLK):0.0
p 288 976 100 0 1 name:$(tcs)rotator
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 1448 1544 100 0 MESS
xform 0 1440 1584
use outhier 1304 1640 100 0 VAL
xform 0 1296 1680
use inhier -152 1544 100 0 ICID
xform 0 -160 1584
use inhier -152 1640 100 0 DIR
xform 0 -160 1680
[comments]
