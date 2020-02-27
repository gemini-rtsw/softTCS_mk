[schematic2]
uniq 7
[tools]
[detail]
s 2448 2288 100 0 $Id: tcsSadEcsParams.sch,v 1.1.1.1 1998/11/08 00:20:15 epics Exp $
s 2688 96 100 0 Gemini Telescope Control System
[cell use]
use esirs 1816 872 100 0 shutterDriveMode
xform 0 2000 1024
p 1888 1182 100 0 -1 DESC:Shutter Drive Mode
p 1728 608 100 0 0 FDSC:Shutter drive mode, FullyOpen-Tracking
p 1904 864 100 1024 0 name:$(sad)$(I)
p 1872 926 100 0 1 FTVL:STRING
use esirs 408 872 100 0 domeVignette
xform 0 592 1024
p 464 1182 100 0 -1 DESC:Dome vignette fraction
p 464 926 100 0 1 FTVL:DOUBLE
p 576 800 100 0 0 PREC:2
p 320 256 100 0 0 MDEL:0.005
p 496 864 100 1024 0 name:$(sad)$(I)
use esirs 408 1448 100 0 carouselAz
xform 0 592 1600
p 464 1774 100 0 -1 DESC:Carousel demand azimuth
p 480 1598 100 0 1 EGU:degs
p 480 1502 100 0 1 FTVL:DOUBLE
p 496 1440 100 1024 0 name:$(sad)$(I)
p 576 1376 100 0 0 PREC:2
p 320 1184 100 0 0 FDSC:Demanded dome azimuth 
use esirs 1144 1448 100 0 topShtrPosDem
xform 0 1328 1600
p 1200 1774 100 0 -1 DESC:Top shutter demand elevation
p 1216 1598 100 0 1 EGU:degs
p 1216 1502 100 0 1 FTVL:DOUBLE
p 1232 1440 100 1024 0 name:$(sad)$(I)
p 1312 1376 100 0 0 PREC:2
p 1056 1184 100 0 0 FDSC:Elev. demand of bottom edge
use esirs 1816 1448 100 0 botShtrPosDem
xform 0 2000 1600
p 1872 1774 100 0 -1 DESC:Bottom shutter demand elevation
p 1888 1598 100 0 1 EGU:degs
p 1888 1502 100 0 1 FTVL:DOUBLE
p 1904 1440 100 1024 0 name:$(sad)$(I)
p 1984 1376 100 0 0 PREC:2
p 1728 1184 100 0 0 FDSC:Elevation demand for top edge
use esirs 1144 872 100 0 carouselDriveMode
xform 0 1328 1024
p 1216 1182 100 0 -1 DESC:Carousel Drive Mode
p 1056 608 100 0 0 FDSC:Carousel Drive Mode
p 1232 864 100 1024 0 name:$(sad)$(I)
p 1200 926 100 0 1 FTVL:STRING
use esirs 404 457 100 0 encTempTarget
xform 0 588 609
p 460 767 100 0 -1 DESC:Enclosure Target Temperature
p 460 511 100 0 1 FTVL:DOUBLE
p 572 385 100 0 0 PREC:1
p 316 -159 100 0 0 MDEL:0.1
p 492 449 100 1024 0 name:$(sad)$(I)
use bc200tr -144 -184 -100 0 frame
xform 0 1536 1120
[comments]
