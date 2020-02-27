[schematic2]
uniq 34
[tools]
[detail]
w 1560 1035 100 0 n#33 esirs.caguide.FLNK 1824 1344 1856 1344 1856 1024 1312 1024 1312 768 1408 768 esirs.ceguide.SLNK
w 1560 1451 100 0 n#32 esirs.celocal.FLNK 1824 1760 1856 1760 1856 1440 1312 1440 1312 1184 1408 1184 esirs.caguide.SLNK
w 1560 1867 100 0 n#31 esirs.calocal.FLNK 1824 2144 1856 2144 1856 1856 1312 1856 1312 1600 1408 1600 esirs.celocal.SLNK
s 1184 2272 200 0 SIR records related to the rotator
s 2592 2432 100 0 $Id:
s 2816 240 100 0 Gemini Telescope Control System
[cell use]
use esirs 1432 680 100 0 ceguide
xform 0 1616 832
p 1472 990 100 0 -1 DESC:Guiding adjustment to CE
p 1552 782 100 0 1 EGU:arcsec
p 1344 416 100 0 0 FDSC:Guiding adjustment to CE
p 1344 384 100 0 0 FTVL:DOUBLE
p 1600 608 100 0 0 PREC:2
p 1600 416 100 0 0 def(INP):$(top)ak:guide:ce
p 1520 672 100 1024 0 name:$(sad)$(I)
use esirs 1432 1096 100 0 caguide
xform 0 1616 1248
p 1472 1406 100 0 -1 DESC:Guiding adjustment to CA
p 1552 1198 100 0 1 EGU:arcsec
p 1344 832 100 0 0 FDSC:Guiding adjustment to CA
p 1344 800 100 0 0 FTVL:DOUBLE
p 1600 1024 100 0 0 PREC:2
p 1600 832 100 0 0 def(INP):$(top)ak:guide:ca
p 1520 1088 100 1024 0 name:$(sad)$(I)
use esirs 1432 1512 100 0 celocal
xform 0 1616 1664
p 1472 1822 100 0 -1 DESC:Local adjustment to CE
p 1552 1614 100 0 1 EGU:arcsec
p 1344 1248 100 0 0 FDSC:Local adjustment to CE
p 1344 1216 100 0 0 FTVL:DOUBLE
p 1600 1440 100 0 0 PREC:2
p 1600 1248 100 0 0 def(INP):$(top)ak:pm:ce:local
p 1520 1504 100 1024 0 name:$(sad)$(I)
use esirs 1432 1896 100 0 calocal
xform 0 1616 2048
p 1472 2206 100 0 -1 DESC:Local adjustment to CA
p 1552 1998 100 0 1 EGU:arcsec
p 1344 1632 100 0 0 FDSC:Local adjustment to CA
p 1344 1600 100 0 0 FTVL:DOUBLE
p 1600 1824 100 0 0 PREC:2
p 1536 2048 100 0 1 SCAN:1 second
p 1488 2128 100 0 0 def(INP):$(top)ak:pm:ca:local
p 1520 1888 100 1024 0 name:$(sad)$(I)
use esirs 1984 327 100 0 tlr
xform 0 2192 480
p 1920 224 100 0 0 DESC:Troposheric lapse rate
p 2128 432 100 0 1 EGU:Deg K/metre
p 2048 640 100 0 -1 FDSC:Tropospheric lapse rate
p 1920 32 100 0 0 FTVL:DOUBLE
p 2176 256 100 0 0 PREC:6
p 2096 320 100 1024 0 name:$(sad)$(I)
use esirs 1984 711 100 0 delut
xform 0 2192 864
p 1920 608 100 0 0 DESC:UT1-UTC
p 2128 816 100 0 1 EGU:seconds
p 2048 1024 100 0 -1 FDSC:UT1-UTC
p 1920 416 100 0 0 FTVL:DOUBLE
p 2176 640 100 0 0 PREC:4
p 2096 704 100 1024 0 name:$(sad)$(I)
use esirs 1984 1111 100 0 delat
xform 0 2192 1264
p 1920 1008 100 0 0 DESC:TAI-UTC
p 2128 1216 100 0 1 EGU:seconds
p 2048 1424 100 0 -1 FDSC:TAI-UTC
p 1920 816 100 0 0 FTVL:DOUBLE
p 2176 1040 100 0 0 PREC:3
p 2096 1104 100 1024 0 name:$(sad)$(I)
use esirs 1984 1511 100 0 djmls
xform 0 2192 1664
p 1920 1408 100 0 0 DESC:MJD followinf next leap second
p 2128 1616 100 0 1 EGU:days
p 2048 1824 100 0 -1 FDSC:MJD following next leap second
p 1920 1216 100 0 0 FTVL:DOUBLE
p 2176 1440 100 0 0 PREC:0
p 2096 1504 100 1024 0 name:$(sad)$(I)
use esirs 1984 1895 100 0 ttmtai
xform 0 2192 2048
p 1920 1792 100 0 0 DESC:TT-TAI
p 2128 2000 100 0 1 EGU:seconds
p 2048 2208 100 0 -1 FDSC:TT_TAI
p 1920 1600 100 0 0 FTVL:DOUBLE
p 2176 1824 100 0 0 PREC:6
p 2096 1888 100 1024 0 name:$(sad)$(I)
use esirs 2688 327 100 0 ypm
xform 0 2896 480
p 2624 224 100 0 0 DESC:Y component of polar motion
p 2832 432 100 0 1 EGU:arcsec
p 2752 640 100 0 -1 FDSC:Y component of polar motion
p 2624 32 100 0 0 FTVL:DOUBLE
p 2880 256 100 0 0 PREC:3
p 2800 320 100 1024 0 name:$(sad)$(I)
use esirs 2672 711 100 0 xpm
xform 0 2880 864
p 2608 608 100 0 0 DESC:X component of polar motion
p 2816 816 100 0 1 EGU:arcsec
p 2736 1024 100 0 -1 FDSC:X component of polar motion
p 2608 416 100 0 0 FTVL:DOUBLE
p 2864 640 100 0 0 PREC:3
p 2784 704 100 1024 0 name:$(sad)$(I)
use esirs 2672 1111 100 0 height
xform 0 2880 1264
p 2608 1008 100 0 0 DESC:Height above sea level
p 2816 1216 100 0 1 EGU:metres
p 2736 1424 100 0 -1 FDSC:Height above sea level
p 2608 816 100 0 0 FTVL:DOUBLE
p 2864 1040 100 0 0 PREC:6
p 2784 1104 100 1024 0 name:$(sad)$(I)
use esirs 2672 1511 100 0 tlatm
xform 0 2880 1664
p 2608 1408 100 0 0 DESC:Telescope mean latitude
p 2816 1616 100 0 1 EGU:degrees
p 2736 1824 100 0 -1 FDSC:Telescope mean latitude
p 2608 1216 100 0 0 FTVL:DOUBLE
p 2864 1440 100 0 0 PREC:9
p 2784 1504 100 1024 0 name:$(sad)$(I)
use esirs 2672 1895 100 0 tlongm
xform 0 2880 2048
p 2608 1792 100 0 0 DESC:Telescope mean longitude
p 2816 2000 100 0 1 EGU:degrees
p 2736 2208 100 0 -1 FDSC:Telescope mean longitude
p 2608 1600 100 0 0 FTVL:DOUBLE
p 2864 1824 100 0 0 PREC:10
p 2784 1888 100 1024 0 name:$(sad)$(I)
use esirs 328 1528 100 0 collErrEl
xform 0 512 1680
p 368 1838 100 0 -1 DESC:Collimation error in elevation
p 448 1630 100 0 1 EGU:arcsec
p 240 1264 100 0 0 FDSC:Collimation error in elevation
p 240 1232 100 0 0 FTVL:DOUBLE
p 496 1456 100 0 0 PREC:2
p 416 1520 100 1024 0 name:$(sad)$(I)
use esirs 344 1896 100 0 collErrAz
xform 0 528 2048
p 384 2206 100 0 -1 DESC:Collimation error in azimuth
p 464 1998 100 0 1 EGU:arcsec
p 256 1632 100 0 0 FDSC:Collimation error in azimuth
p 256 1600 100 0 0 FTVL:DOUBLE
p 512 1824 100 0 0 PREC:2
p 432 1888 100 1024 0 name:$(sad)$(I)
use esirs 888 1896 100 0 azIndexError
xform 0 1072 2048
p 928 2206 100 0 -1 DESC:Azimuth index error
p 1008 1998 100 0 1 EGU:arcsec
p 800 1632 100 0 0 FDSC:Azimuth index error
p 800 1600 100 0 0 FTVL:DOUBLE
p 1056 1824 100 0 0 PREC:2
p 976 1888 100 1024 0 name:$(sad)$(I)
use bc200tr 0 -40 -100 0 frame
xform 0 1680 1264
[comments]
