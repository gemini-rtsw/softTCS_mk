[schematic2]
uniq 20
[tools]
[detail]
w 1608 258 100 0 n#19 eaos.fieldRadius.VAL 1184 256 2080 256 2080 784 2240 784 egenSub.updateEcsDefs.INPF
w 1600 546 100 0 n#18 eaos.minSlitHeight.VAL 1184 544 2064 544 2064 848 2240 848 egenSub.updateEcsDefs.INPE
w 1832 706 100 0 n#17 eaos.minScatWidth.VAL 1664 704 2048 704 2048 912 2240 912 egenSub.updateEcsDefs.INPD
w 1640 898 100 0 n#16 eaos.beamDiameter.VAL 1184 832 1312 832 1312 896 2016 896 2016 976 2240 976 egenSub.updateEcsDefs.INPC
w 1800 1026 100 0 n#15 eaos.slitWidth.VAL 1664 1024 1984 1024 1984 1040 2240 1040 egenSub.updateEcsDefs.INPB
w 1624 1250 100 0 n#14 eaos.encRadius.VAL 1184 1120 1312 1120 1312 1248 1984 1248 1984 1104 2240 1104 egenSub.updateEcsDefs.INPA
s 32 464 100 0 if neccessary be different between GemNorth and GemSouth.
s 32 496 100 0 them as EPICS records allows them to be easily setup and
s 32 528 100 0 accurately determined during commissioning. Providing
s 32 560 100 0 They are not expected to change once they have been
s 32 592 100 0 implementation of the various enclosure and shutter modes.
s 32 624 100 0 These records are internal to the TCS and are used in the
s 80 1616 100 0 available
s 80 1648 100 0 sensibly to user requests until the subsystem is
s 80 1680 100 0 can not connect to the ECS. This allows the TCS to respond
s 80 1712 100 0 The first block of records below are only used if the TCS
s 1344 2160 200 0 Enclosure defaults
s 2656 112 100 0 Gemini Telescope Control System
s 2432 2304 100 0 $Id: tcsDefaultsEcs.sch,v 1.4 2003/03/13 01:19:39 cjm Exp $
[cell use]
use egenSub 2264 344 100 0 updateEcsDefs
xform 0 2384 768
p 2192 1230 100 0 -1 DESC:Set default enclosure parameters
p 2017 117 100 0 0 FTVA:STRING
p 2272 302 100 0 1 SNAM:tcsEcsUpdateDefs
p 2560 1575 100 0 0 def(INPA):0.0
p 2625 1102 100 0 -1 def(OUTA):0.0
use eaos 952 168 100 0 fieldRadius
xform 0 1056 256
p 1008 350 100 0 -1 DESC:Radius of accessible field
p 672 14 100 0 0 DRVH:9.0
p 672 -18 100 0 0 DRVL:0.0
p 1008 286 100 0 1 EGU:arcmin
p 672 78 100 0 0 EGUF:9.0
p 672 46 100 0 0 EGUL:0.0
p 672 110 100 0 0 PREC:1
use eaos 952 456 100 0 minSlitHeight
xform 0 1056 544
p 1008 638 100 0 -1 DESC:Minimum slit height
p 672 302 100 0 0 DRVH:10000
p 672 270 100 0 0 DRVL:8200
p 1008 574 100 0 1 EGU:mm
p 672 366 100 0 0 EGUF:10000
p 672 334 100 0 0 EGUL:8200
p 672 398 100 0 0 PREC:1
use eaos 1432 616 100 0 minScatWidth
xform 0 1536 704
p 1472 798 100 0 -1 DESC:Adjustment for minimum scatter
p 1152 462 100 0 0 DRVH:1000
p 1152 430 100 0 0 DRVL:0
p 1488 734 100 0 1 EGU:mm
p 1152 526 100 0 0 EGUF:1000
p 1152 494 100 0 0 EGUL:0
p 1152 558 100 0 0 PREC:1
use eaos 952 744 100 0 beamDiameter
xform 0 1056 832
p 928 926 100 0 -1 DESC:Diameter of entrance aperture
p 672 590 100 0 0 DRVH:8500
p 672 558 100 0 0 DRVL:7900
p 1008 862 100 0 1 EGU:mm
p 672 654 100 0 0 EGUF:8500
p 672 622 100 0 0 EGUL:7900
use eaos 1432 936 100 0 slitWidth
xform 0 1536 1024
p 1488 1118 100 0 -1 DESC:Slit Width
p 1152 782 100 0 0 DRVH:9400
p 1152 750 100 0 0 DRVL:9200
p 1488 1054 100 0 1 EGU:mm
p 1152 846 100 0 0 EGUF:9400
p 1152 814 100 0 0 EGUL:9200
p 1152 878 100 0 0 PREC:1
use eaos 952 1032 100 0 encRadius
xform 0 1056 1120
p 992 1214 100 0 -1 DESC:Enclosure radius
p 672 878 100 0 0 DRVH:21500
p 672 846 100 0 0 DRVL:16000
p 1008 1150 100 0 1 EGU:mm
p 672 942 100 0 0 EGUF:21500
p 672 910 100 0 0 EGUL:16000
p 672 974 100 0 0 PREC:1
use eaos 1464 1704 100 0 maxBotShtr
xform 0 1568 1792
p 1392 1902 100 0 -1 DESC:Maximum elevation of bottom shutter
p 1504 1870 100 0 1 EGU:degrees
p 1184 1646 100 0 0 PREC:1
use eaos 952 1704 100 0 minBotShtr
xform 0 1056 1792
p 880 1902 100 0 -1 DESC:Minimum elevation of bottom shutter
p 992 1870 100 0 1 EGU:degrees
p 672 1646 100 0 0 PREC:1
use eaos 952 1384 100 0 minTopShtr
xform 0 1056 1472
p 880 1582 100 0 -1 DESC:Minimum elevation of top shutter
p 992 1550 100 0 1 EGU:degrees
p 672 1326 100 0 0 PREC:1
use eaos 1464 1384 100 0 maxTopShtr
xform 0 1568 1472
p 1392 1582 100 0 -1 DESC:Maximum elevation of top shutter
p 1504 1550 100 0 1 EGU:degrees
p 1184 1326 100 0 0 PREC:1
use eaos 2104 1736 100 0 domePos
xform 0 2208 1824
p 2032 1934 100 0 -1 DESC:Default dome azimuth position
p 2144 1902 100 0 1 EGU:degrees
p 1824 1678 100 0 0 PREC:1
use eaos 2744 1736 100 0 botShtrPos
xform 0 2848 1824
p 2672 1934 100 0 -1 DESC:Default bottom shutter elevation
p 2784 1902 100 0 1 EGU:degrees
p 2464 1678 100 0 0 PREC:1
use eaos 2744 1384 100 0 topShtrPos
xform 0 2848 1472
p 2672 1582 100 0 -1 DESC:Default top shutter elevation
p 2784 1550 100 0 1 EGU:degrees
p 2464 1326 100 0 0 PREC:1
use bc200tr -144 -168 -100 0 frame
xform 0 1536 1136
[comments]
