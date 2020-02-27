[schematic2]
uniq 665
[tools]
[detail]
s -2688 96 100 0 GAOS Defaults
s -672 1680 100 0 M2 defaults
s -1840 1680 100 0 Rotator Defaults
s -2752 1680 100 0 Mount defaults
s -2368 1856 200 0 (used when there is no connection to a subsystem)
s -2208 1952 300 0 TCS Internal Defaults
s -448 -176 100 0 TCS Internal Defaults
s -704 -224 100 0 30 Oct 96
s -496 -112 100 0 Gemini Telescope Control System
s -2720 752 100 0 A&G Defaults
s -736 2080 100 0 $Id: tcsDefaults.sch,v 1.4 2016/05/09 16:08:19 gemvx Exp $
s -1904 752 100 0 Enclosure defualts
s -1792 96 100 0 AOM Defaults
[cell use]
use estringouts -1872 967 100 0 ephFolder
xform 0 -1744 1040
p -1872 1120 100 0 -1 DESC:Ephemeris Folder
p -1792 928 100 1024 1 name:$(top)$(I)
use tcsDefaultsAg -2776 -152 100 0 tcsDefaultsAg#659
xform 0 -2624 -48
p -2688 -2 100 0 -1 seta:top $(top)aowfs
use tcsDefaultsAg -2776 216 100 0 tcsDefaultsAg#648
xform 0 -2624 320
p -2688 366 100 0 -1 seta:top $(top)oiwfs
use tcsDefaultsAg -2504 472 100 0 tcsDefaultsAg#647
xform 0 -2352 576
p -2416 622 100 0 -1 seta:top $(top)pwfs2
use tcsDefaultsAg -3016 472 100 0 tcsDefaultsAg#646
xform 0 -2864 576
p -2928 622 100 0 -1 seta:top $(top)pwfs1
use tcsDefaultsAg -2312 -152 100 0 tcsDefaultsAg#661
xform 0 -2160 -48
p -2224 -2 100 0 -1 seta:top $(top)aomngsPr1
use tcsDefaultsAg -1864 -152 100 0 tcsDefaultsAg#662
xform 0 -1712 -48
p -1776 -2 100 0 -1 seta:top $(top)aomngsPr2
use tcsDefaultsAg -1416 -152 100 0 tcsDefaultsAg#663
xform 0 -1264 -48
p -1328 -2 100 0 -1 seta:top $(top)aomngsPr3
use tcsDefaultsEcs -1944 488 100 0 tcsDefaultsEcs#657
xform 0 -1792 592
use eaos -392 424 100 0 m2MaxTiltZ
xform 0 -288 512
p -480 606 100 0 -1 DESC:Max. Z for max. tilt
p -672 270 100 0 0 DRVH:5.0
p -448 238 100 0 0 EGU:mm
p -672 334 100 0 0 EGUF:5.0
p -448 462 100 0 0 HIGH:5.0
p -448 526 100 0 0 HIHI:5.0
p -448 622 100 0 0 HOPR:5.0
p -672 366 100 0 0 PREC:2
use eaos -392 680 100 0 m2MinTiltZ
xform 0 -288 768
p -480 862 100 0 -1 DESC:Maximum Z for min. tilt
p -672 526 100 0 0 DRVH:10.0
p -448 494 100 0 0 EGU:mm
p -672 590 100 0 0 EGUF:10.0
p -448 718 100 0 0 HIGH:10.0
p -448 782 100 0 0 HIHI:10.0
p -448 878 100 0 0 HOPR:10.0
p -672 622 100 0 0 PREC:2
use eaos -952 424 100 0 m2MaxTilt
xform 0 -848 512
p -1040 606 100 0 -1 DESC:Maximum tilt (arcsec)
p -1232 270 100 0 0 DRVH:3600.0
p -1008 238 100 0 0 EGU:arcsec
p -1232 334 100 0 0 EGUF:3600.0
p -1008 462 100 0 0 HIGH:3600.0
p -1008 526 100 0 0 HIHI:3600.0
p -1008 622 100 0 0 HOPR:3600.0
p -1232 366 100 0 0 PREC:2
use eaos -952 680 100 0 m2MinTilt
xform 0 -848 768
p -1040 862 100 0 -1 DESC:Minimum Tilt (arcsec)
p -1232 526 100 0 0 DRVH:10.0
p -1008 494 100 0 0 EGU:arcsec
p -1232 590 100 0 0 EGUF:10.0
p -1008 718 100 0 0 HIGH:10.0
p -1008 782 100 0 0 HIHI:10.0
p -1008 878 100 0 0 HOPR:10.0
p -1232 622 100 0 0 PREC:2
use eaos -392 936 100 0 m2MaxChopFreqThrow
xform 0 -288 1024
p -480 1118 100 0 -1 DESC:Max. throw at min. freq. (arcsec)
p -672 782 100 0 0 DRVH:60.0
p -448 750 100 0 0 EGU:arcsec
p -672 846 100 0 0 EGUF:60.0
p -448 974 100 0 0 HIGH:60.0
p -448 1038 100 0 0 HIHI:60.0
p -448 1134 100 0 0 HOPR:60.0
p -672 878 100 0 0 PREC:2
use eaos -408 1192 100 0 m2BreakChopFreqThrow
xform 0 -304 1280
p -496 1374 100 0 -1 DESC:Max. throw at break freq. (arcsec)
p -688 1038 100 0 0 DRVH:130.0
p -464 1006 100 0 0 EGU:arcsec
p -688 1102 100 0 0 EGUF:130.0
p -464 1230 100 0 0 HIGH:130.0
p -464 1294 100 0 0 HIHI:130.0
p -464 1390 100 0 0 HOPR:130.0
p -688 1134 100 0 0 PREC:2
use eaos -952 1192 100 0 m2BreakChopFreq
xform 0 -848 1280
p -976 1358 100 0 -1 DESC:Default chop freq. at break (Hz)
p -1232 1038 100 0 0 DRVH:10.0
p -1008 1006 100 0 0 EGU:Hz
p -1232 1102 100 0 0 EGUF:10.0
p -1008 1230 100 0 0 HIGH:10.0
p -1008 1294 100 0 0 HIHI:10.0
p -1008 1390 100 0 0 HOPR:10.0
p -1232 1134 100 0 0 PREC:2
use eaos -2568 1160 100 0 elveldef
xform 0 -2464 1248
p -2592 1342 100 0 -1 DESC:Default elevation velocity
p -2848 1006 100 0 0 DRVH:2.0
p -2624 974 100 0 0 EGU:Degrees/s
p -2848 1070 100 0 0 EGUF:2.0
p -2624 1198 100 0 0 HIGH:2.0
p -2624 1262 100 0 0 HIHI:2.0
p -2624 1358 100 0 0 HOPR:2.0
p -2848 1102 100 0 0 PREC:2
p -2480 1120 100 1024 1 name:$(tcs)$(I)
use eaos -2568 1416 100 0 azveldef
xform 0 -2464 1504
p -2608 1598 100 0 -1 DESC:Default Mount azimuth velocity
p -2848 1262 100 0 0 DRVH:4.0
p -2848 1230 100 0 0 DRVL:0.0
p -2624 1230 100 0 0 EGU:Degrees/s
p -2848 1326 100 0 0 EGUF:4.0
p -2848 1294 100 0 0 EGUL:0.0
p -2624 1454 100 0 0 HIGH:4.0
p -2624 1518 100 0 0 HIHI:4.0
p -2624 1614 100 0 0 HOPR:4.0
p -2624 1582 100 0 0 LOPR:0.0
p -2848 1358 100 0 0 PREC:2
p -2480 1376 100 1024 1 name:$(tcs)$(I)
use eaos -2072 1416 100 0 rmadef
xform 0 -1968 1504
p -2064 1598 100 0 -1 DESC:Default Rotator PA
p -2352 1262 100 0 0 DRVH:270.0
p -2352 1230 100 0 0 DRVL:-270.0
p -2128 1230 100 0 0 EGU:Degrees
p -2352 1326 100 0 0 EGUF:270.0
p -2352 1294 100 0 0 EGUL:-270.0
p -2128 1454 100 0 0 HIGH:270.0
p -2128 1518 100 0 0 HIHI:270.0
p -2128 1614 100 0 0 HOPR:270.0
p -2128 1486 100 0 0 LOLO:-270.0
p -2128 1582 100 0 0 LOPR:-270.0
p -2128 1422 100 0 0 LOW:-270.0
p -2352 1358 100 0 0 PREC:3
p -1984 1376 100 1024 1 name:$(tcs)$(I)
use eaos -3016 1416 100 0 azdef
xform 0 -2912 1504
p -3040 1598 100 0 -1 DESC:Default Mount azimuth
p -3296 1262 100 0 0 DRVH:360.0
p -3296 1230 100 0 0 DRVL:-180.0
p -3072 1230 100 0 0 EGU:Degrees
p -3296 1326 100 0 0 EGUF:360.0
p -3296 1294 100 0 0 EGUL:-180.0
p -3072 1454 100 0 0 HIGH:360.0
p -3072 1518 100 0 0 HIHI:360.0
p -3072 1614 100 0 0 HOPR:360.0
p -3072 1486 100 0 0 LOLO:-180.0
p -3072 1582 100 0 0 LOPR:-180.0
p -3072 1422 100 0 0 LOW:-180.0
p -3296 1358 100 0 0 PREC:3
p -2928 1376 100 1024 1 name:$(tcs)$(I)
use eaos -3032 1160 100 0 eldef
xform 0 -2928 1248
p -3040 1342 100 0 -1 DESC:Default Mount Elevation
p -3312 1006 100 0 0 DRVH:90.0
p -3088 974 100 0 0 EGU:Degrees
p -3312 1070 100 0 0 EGUF:90.0
p -3088 1198 100 0 0 HIGH:90.0
p -3088 1262 100 0 0 HIHI:90.0
p -3088 1358 100 0 0 HOPR:90.0
p -3312 1102 100 0 0 PREC:3
p -2944 1120 100 1024 1 name:$(tcs)$(I)
use eaos -1640 1416 100 0 paveldef
xform 0 -1536 1504
p -1664 1598 100 0 -1 DESC:Default Rotator velocity
p -1920 1262 100 0 0 DRVH:5.0
p -1920 1230 100 0 0 DRVL:0.0
p -1696 1230 100 0 0 EGU:Degrees/s
p -1920 1326 100 0 0 EGUF:5.0
p -1920 1294 100 0 0 EGUL:0.0
p -1696 1454 100 0 0 HIGH:5.0
p -1696 1518 100 0 0 HIHI:5.0
p -1696 1614 100 0 0 HOPR:5.0
p -1696 1582 100 0 0 LOPR:0.0
p -1920 1358 100 0 0 PREC:2
p -1552 1376 100 1024 1 name:$(tcs)$(I)
use eaos -408 1416 100 0 m2MinChopFreqThrow
xform 0 -304 1504
p -496 1598 100 0 -1 DESC:Max. throw at min. freq. (arcsec)
p -688 1262 100 0 0 DRVH:130.0
p -464 1230 100 0 0 EGU:arcsec
p -688 1326 100 0 0 EGUF:130.0
p -464 1454 100 0 0 HIGH:130.0
p -464 1518 100 0 0 HIHI:130.0
p -464 1614 100 0 0 HOPR:130.0
p -688 1358 100 0 0 PREC:2
use eaos -936 1416 100 0 m2MinChopFreq
xform 0 -832 1504
p -960 1582 100 0 -1 DESC:Default min. chop freq. (Hz)
p -1216 1262 100 0 0 DRVH:10.0
p -992 1230 100 0 0 EGU:Hz
p -1216 1326 100 0 0 EGUF:10.0
p -992 1454 100 0 0 HIGH:10.0
p -992 1518 100 0 0 HIHI:10.0
p -992 1614 100 0 0 HOPR:10.0
p -1216 1358 100 0 0 PREC:2
use eaos -952 936 100 0 m2MaxChopFreq
xform 0 -848 1024
p -976 1102 100 0 -1 DESC:Default max. chop freq. (Hz)
p -1232 782 100 0 0 DRVH:10.0
p -1008 750 100 0 0 EGU:Hz
p -1232 846 100 0 0 EGUF:10.0
p -1008 974 100 0 0 HIGH:10.0
p -1008 1038 100 0 0 HIHI:10.0
p -1008 1134 100 0 0 HOPR:10.0
p -1232 878 100 0 0 PREC:2
use estringouts -680 168 100 0 defTopEnd
xform 0 -576 240
p -656 350 100 0 -1 DESC:Default top end
p -768 206 100 0 0 VAL:F16
p -576 112 100 1024 1 name:$(tcs)$(I)
use bc200tr -3312 -392 -100 0 frame
xform 0 -1632 912
[comments]
