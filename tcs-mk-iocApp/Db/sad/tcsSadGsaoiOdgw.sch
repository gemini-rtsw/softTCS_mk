[schematic2]
uniq 1
[tools]
[detail]
s 2432 2288 100 0 $Id: tcsSadGsaoiOdgw.sch,v 1.2 2010/11/29 14:18:50 cjm Exp $
s 2688 96 100 0 Gemini Telescope Control System
[cell use]
use bc200tr -144 -184 -100 0 frame
xform 0 1536 1120
use esirs 1112 264 100 0 Ymax
xform 0 1296 416
p 1168 590 100 0 -1 DESC:ODGW Y max
p 1184 414 100 0 1 EGU:pixels
p 1024 0 100 0 0 FDSC:Maximum y coordinate of ODGW window
p 1184 318 100 0 1 FTVL:DOUBLE
p 1280 192 100 0 0 PREC:1
p 1200 256 100 1024 0 name:$(sad)$(odgw)$(I)
use esirs 1112 744 100 0 Ymin
xform 0 1296 896
p 1168 1070 100 0 -1 DESC:ODGW Y min
p 1184 894 100 0 1 EGU:pixels
p 1024 480 100 0 0 FDSC:Minimum y coordinate of ODGW window
p 1184 798 100 0 1 FTVL:DOUBLE
p 1280 672 100 0 0 PREC:1
p 1200 736 100 1024 0 name:$(sad)$(odgw)$(I)
use esirs 1112 1256 100 0 Xmax
xform 0 1296 1408
p 1168 1582 100 0 -1 DESC:ODGW X max
p 1184 1406 100 0 1 EGU:pixels
p 1024 992 100 0 0 FDSC:Maximum x coordinate of ODGW window
p 1184 1310 100 0 1 FTVL:DOUBLE
p 1280 1184 100 0 0 PREC:1
p 1200 1248 100 1024 0 name:$(sad)$(odgw)$(I)
use esirs 1112 1736 100 0 Xmin
xform 0 1296 1888
p 1168 2062 100 0 -1 DESC:ODGW X min
p 1184 1886 100 0 1 EGU:pixels
p 1024 1472 100 0 0 FDSC:Minimum x coordinate of ODGW window
p 1184 1790 100 0 1 FTVL:DOUBLE
p 1280 1664 100 0 0 PREC:1
p 1200 1728 100 1024 0 name:$(sad)$(odgw)$(I)
use esirs 1848 1736 100 0 Parked
xform 0 2032 1888
p 1904 2062 100 0 -1 DESC:ODGW Parked Status
p 1920 1886 100 0 0 EGU:none
p 1760 1472 100 0 0 FDSC:Minimum x coordinate of ODGW window
p 1920 1790 100 0 1 FTVL:STRING
p 2016 1664 100 0 0 PREC:1
p 1936 1728 100 1024 0 name:$(sad)$(odgw)$(I)
[comments]
