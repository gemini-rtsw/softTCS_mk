[schematic2]
uniq 115
[tools]
[detail]
w 1858 523 100 0 n#114 ecad20.ecad20#72.VALL 800 1088 1184 1088 1184 512 2592 512 2592 640 2752 640 eaos.oi.DOL
w 1874 779 100 0 n#113 ecad20.ecad20#72.VALK 800 1152 1216 1152 1216 768 2592 768 2592 896 2752 896 eaos.p2.DOL
w 1858 1067 100 0 n#112 ecad20.ecad20#72.VALJ 800 1216 1248 1216 1248 1056 2528 1056 2528 1184 2752 1184 eaos.p1.DOL
w 2858 747 100 0 n#111 eaos.p2.FLNK 3008 896 3152 896 3152 736 2624 736 2624 608 2752 608 eaos.oi.SLNK
w 2850 1035 100 0 n#110 eaos.p1.FLNK 3008 1184 3136 1184 3136 1024 2624 1024 2624 864 2752 864 eaos.p2.SLNK
w 2306 683 100 0 n#109 eaos.sign.FLNK 2112 672 2560 672 2560 1152 2752 1152 eaos.p1.SLNK
w 1890 763 100 0 n#108 eaos.oiwfsw.FLNK 2112 912 2144 912 2144 752 1696 752 1696 640 1856 640 eaos.sign.SLNK
w 1090 363 100 0 n#104 ecad20.ecad20#72.STLK 800 352 1440 352 1440 2000 1824 2000 elongouts.abswfserr.SLNK
w 1538 683 100 0 n#103 ecad20.ecad20#72.VALI 800 1280 1280 1280 1280 672 1856 672 eaos.sign.DOL
w 1554 923 100 0 n#101 ecad20.ecad20#72.VALG 800 1408 1312 1408 1312 912 1856 912 eaos.oiwfsw.DOL
w 1042 1483 100 0 n#100 ecad20.ecad20#72.VALF 800 1472 1344 1472 1344 1216 1840 1216 1840 1184 eaos.p2wfsw.DOL
w 1064 1547 100 0 n#99 ecad20.ecad20#72.VALE 800 1536 1376 1536 1376 1440 1840 1440 eaos.p1wfsw.DOL
w 1064 1611 100 0 n#98 ecad20.ecad20#72.VALD 800 1600 1376 1600 1376 1744 1824 1744 elongouts.probno.DOL
w 1048 1675 100 0 n#97 ecad20.ecad20#72.VALC 800 1664 1344 1664 1344 2032 1824 2032 elongouts.abswfserr.DOL
w 888 1963 100 0 n#96 ecad20.ecad20#72.MESS 800 1952 1024 1952 1024 1872 1248 1872 outhier.MESS.p
w 1000 1995 100 0 n#95 ecad20.ecad20#72.VAL 800 1984 1248 1984 outhier.VAL.p
w 384 1963 100 0 n#94 inhier.ICID.P 240 1872 336 1872 336 1952 480 1952 ecad20.ecad20#72.ICID
w 336 1995 100 0 n#93 inhier.DIR.P 240 1984 480 1984 ecad20.ecad20#72.DIR
w 1896 1035 100 0 n#70 eaos.p2wfsw.FLNK 2096 1184 2144 1184 2144 1024 1696 1024 1696 880 1856 880 eaos.oiwfsw.SLNK
w 1896 1291 100 0 n#69 eaos.p1wfsw.FLNK 2096 1440 2144 1440 2144 1280 1696 1280 1696 1152 1840 1152 eaos.p2wfsw.SLNK
w 1904 1891 100 0 n#64 elongouts.abswfserr.FLNK 2080 2032 2160 2032 2160 1888 1696 1888 1696 1712 1824 1712 elongouts.probno.SLNK
w 1896 1611 100 0 abswfserr elongouts.probno.FLNK 2080 1744 2144 1744 2144 1600 1696 1600 1696 1408 1840 1408 eaos.p1wfsw.SLNK
s 2592 2400 100 0 $Id: tcsCadWfsGuideMode.sch,v 1.3 2006/04/21 09:20:14 cjm Exp $
s 896 2128 100 0 generated.
s 896 2160 100 0 the seq record ensures that a Busy to Idle transition is
s 896 2192 100 0 complete by the time the CAD subroutine is executed but
s 896 2224 100 0 delay parameter. In practice the command is already 
s 896 2256 100 0 is set to IDLE after a short time interval set by the 
s 896 2288 100 0 The CAR record is set to BUSY by the start link of the CAD. It
s 896 2320 100 0 that sends no commands to any TCS subsystems. 
s 896 2352 100 0 This schematic implements an internal TCS command i.e. one
s 2848 208 100 0 Gemini Telescope Control System
[cell use]
use eaos 1856 791 100 0 oiwfsw
xform 0 1984 880
p 1904 960 100 0 -1 DESC:OIWFS weighting
p 1600 862 100 0 0 OMSL:closed_loop
p 2176 832 100 0 -1 def(OUT):$(tcs)ak:wfsguide:oiweight
p 2112 848 75 768 -1 pproc(OUT):PP
use eaos 1840 1319 100 0 p1wfsw
xform 0 1968 1408
p 1888 1488 100 0 -1 DESC:P1 weighting
p 1584 1390 100 0 0 OMSL:closed_loop
p 2160 1360 100 0 -1 def(OUT):$(tcs)ak:wfsguide:p1weight
p 2096 1376 75 768 -1 pproc(OUT):PP
use eaos 1840 1063 100 0 p2wfsw
xform 0 1968 1152
p 1872 1232 100 0 -1 DESC:PWFS2 weighting
p 1584 1134 100 0 0 OMSL:closed_loop
p 2160 1104 100 0 -1 def(OUT):$(tcs)ak:wfsguide:p2weight
p 2096 1120 75 768 -1 pproc(OUT):PP
use eaos 1856 551 100 0 sign
xform 0 1984 640
p 1904 720 100 0 -1 DESC:Sign of errors
p 1824 366 100 0 0 EGU:units
p 1600 622 100 0 0 OMSL:closed_loop
p 1600 494 100 0 0 PREC:1
p 2176 592 100 0 -1 def(OUT):$(tcs)ak:wfsguide:sign
p 2112 608 75 768 -1 pproc(OUT):PP
use eaos 2752 1063 100 0 p1
xform 0 2880 1152
p 2736 1248 100 0 -1 DESC:Flag for P1 probe guiding
p 2720 878 100 0 0 EGU:units
p 2496 1134 100 0 0 OMSL:closed_loop
p 2976 1072 100 0 -1 def(OUT):$(sad)pwfs1ProbeGuiding
p 2864 1056 100 1024 0 name:$(tcs)$(cad):$(I)
p 3008 1120 75 768 -1 pproc(OUT):CA
use eaos 2752 775 100 0 p2
xform 0 2880 864
p 2736 960 100 0 -1 DESC:Flag for P2 probe guiding
p 2720 590 100 0 0 EGU:units
p 2496 846 100 0 0 OMSL:closed_loop
p 2976 768 100 0 -1 def(OUT):$(sad)pwfs2ProbeGuiding
p 2864 768 100 1024 0 name:$(tcs)$(cad):$(I)
p 3008 832 75 768 -1 pproc(OUT):CA
use eaos 2752 519 100 0 oi
xform 0 2880 608
p 2736 704 100 0 -1 DESC:Flag for OI probe guiding
p 2720 334 100 0 0 EGU:units
p 2496 590 100 0 0 OMSL:closed_loop
p 2976 512 100 0 -1 def(OUT):$(sad)oiwfsProbeGuiding
p 2864 512 100 1024 0 name:$(tcs)$(cad):$(I)
p 2720 640 75 1280 -1 pproc(DOL):NPP
p 3008 576 75 768 -1 pproc(OUT):CA
use ecad20 480 263 100 0 ecad20#72
xform 0 640 1152
p 448 2048 100 0 -1 DESC:Implement the wfsGuideMode command
p 656 1664 100 0 -1 FTVC:LONG
p 656 1600 100 0 -1 FTVD:LONG
p 672 1344 100 0 0 FTVE:DOUBLE
p 576 1568 100 0 0 FTVF:DOUBLE
p 576 1536 100 0 0 FTVG:DOUBLE
p 576 1472 100 0 0 FTVI:DOUBLE
p 576 1440 100 0 0 FTVJ:DOUBLE
p 576 1408 100 0 0 FTVK:DOUBLE
p 576 1376 100 0 0 FTVL:DOUBLE
p 576 992 100 0 0 PREC:2
p 576 864 100 0 1 SNAM:$(snam)
p 640 224 100 1024 1 name:$(tcs)$(cad)
use elongouts 1848 1912 100 0 abswfserr
xform 0 1952 2000
p 1744 2094 100 0 -1 DESC:absortion of WFS signal into probe
p 1664 1918 100 0 0 OMSL:closed_loop
p 2176 1966 100 0 -1 def(OUT):$(tcs)ak:wfsguide:enable
p 1936 1904 100 1024 0 name:$(tcs)$(I)
p 2080 1968 75 768 -1 pproc(OUT):PP
use elongouts 1848 1624 100 0 probno
xform 0 1952 1712
p 1744 1806 100 0 -1 DESC:Select WFS probe to control
p 1664 1630 100 0 0 OMSL:closed_loop
p 2176 1678 100 0 -1 def(OUT):$(tcs)ak:fast.J
p 1936 1616 100 1024 0 name:$(tcs)$(I)
p 2080 1680 75 768 -1 pproc(OUT):PP
use outhier 1240 1832 100 0 MESS
xform 0 1232 1872
use outhier 1240 1944 100 0 VAL
xform 0 1232 1984
use inhier 248 1832 100 0 ICID
xform 0 240 1872
use inhier 248 1944 100 0 DIR
xform 0 240 1984
use bc200tr 16 -72 -100 0 frame
xform 0 1696 1232
[comments]
