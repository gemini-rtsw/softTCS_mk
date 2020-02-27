[schematic2]
uniq 28
[tools]
[detail]
w 1064 1227 100 0 n#27 estringouts.planetObjectName.FLNK 1216 1392 1344 1392 1344 1216 832 1216 832 1104 960 1104 estringouts.planetBrightness.SLNK
w 676 1219 100 0 n#25 ecad4.ecad4#20.STLK 560 1072 672 1072 672 1376 960 1376 estringouts.planetObjectName.SLNK
w 672 1435 100 0 n#24 ecad4.ecad4#20.VALB 560 1424 832 1424 832 1408 960 1408 estringouts.planetObjectName.DOL
w 918 1682 100 0 n#6 ecad4.ecad4#20.VAL 560 1680 1312 1680 outhier.VAL.p
w 1006 1586 100 0 n#9 ecad4.ecad4#20.MESS 560 1648 592 1648 592 1584 1456 1584 outhier.MESS.p
w 62 1652 100 0 n#8 inhier.ICID.P -160 1584 -80 1584 -80 1648 240 1648 ecad4.ecad4#20.ICID
w 22 1682 100 0 n#7 inhier.DIR.P -160 1680 240 1680 ecad4.ecad4#20.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 P.B. Taylor
s 1808 -336 100 0 16 July 1996
s 1920 2000 100 0 $Id: tcsCadPlanet.sch,v 1.2 2007/01/09 10:25:20 cjm Exp $
[cell use]
use estringouts 960 1031 100 0 planetBrightness
xform 0 1088 1104
p 1088 1072 100 0 0 DESC:Default planet brightness
p 448 1120 100 0 0 OMSL:supervisory
p 896 1070 100 0 0 VAL:Unspecified
p 1280 1088 100 0 -1 def(OUT):$(sad)sourceABrightness
p 1056 992 100 1024 1 name:$(tcs)$(I)
p 1216 1088 75 768 -1 pproc(OUT):PP
use estringouts 960 1303 100 0 planetObjectName
xform 0 1088 1376
p 448 1392 100 0 0 OMSL:closed_loop
p 1280 1360 100 0 -1 def(OUT):$(sad)sourceAObjectName
p 1056 1264 100 1024 1 name:$(tcs)$(I)
p 1216 1360 75 768 -1 pproc(OUT):PP
use ecad4 264 984 100 0 ecad4#20
xform 0 400 1360
p 288 1744 100 0 -1 DESC:Implement planet command
p 304 1912 100 0 0 FTVA:STRING
p 304 1880 100 0 0 FTVB:STRING
p 304 1848 100 0 0 FTVC:STRING
p 304 1816 100 0 0 FTVD:STRING
p 480 960 100 0 1 SNAM:tcsCADplanet
p 640 1392 100 0 0 def(OUTB):0.0
p 464 464 100 0 0 def(STLK):0.0
p 288 958 100 0 1 name:$(tcs)planet
p 560 1392 75 768 -1 pproc(OUTB):PP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 1304 1640 100 0 VAL
xform 0 1296 1680
use outhier 1448 1544 100 0 MESS
xform 0 1440 1584
use inhier -152 1640 100 0 DIR
xform 0 -160 1680
use inhier -152 1544 100 0 ICID
xform 0 -160 1584
[comments]
