[schematic2]
uniq 23
[tools]
[detail]
w 3512 2843 100 0 n#20 esirs.InputFrame.VAL 3488 2832 3584 2832 3584 2864 3648 2864 esirs.RaDecSys.INP
w 3576 2715 100 0 n#19 esirs.InputFrame.FLNK 3488 2864 3552 2864 3552 2704 3648 2704 esirs.RaDecSys.SLNK
s 3744 976 100 0 Gemini Telescope Control System
s 3712 912 100 0 SAD Parameters for Virtual Telescope
s 2192 3088 300 0 SAD Parameters for Target
s 1040 3152 100 0 This schematic holds the SAD records for each virtual 
s 1040 3120 100 0 telescope. These records are written to asynchronously
s 1040 3088 100 0 each time the user inputs new valid data to the corresponding
s 1040 3056 100 0 CAD record. The schematic is instantiated once for each
s 1040 3024 100 0 virtual telescope
s 3472 3168 100 0 $Id: tcsSadSourceParams.sch,v 1.6 2016/05/09 16:08:19 gemvx Exp $
[cell use]
use esirs 2456 904 100 0 Ephemeris
xform 0 2640 1056
p 2528 1216 100 0 -1 DESC:Ephemeris File Name
p 2592 1070 100 0 0 EGU:
p 2368 640 100 0 0 FDSC:Ephemeris File Name
p 2592 1038 100 0 1 FTVL:STRING
p 2624 832 100 0 0 PREC:8
p 2544 896 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 3112 1736 100 0 Brightness
xform 0 3296 1888
p 3184 2048 100 0 -1 DESC:Brightness of object
p 3024 1472 100 0 0 FDSC:Descr. string describing brightness
p 3200 1728 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 1848 2184 100 0 Epoch
xform 0 2032 2336
p 1936 2510 100 0 -1 DESC:Epoch of target coordinates
p 1984 2350 100 0 1 EGU:years
p 1760 1920 100 0 0 FDSC:Epoch of target coordinates
p 1984 2318 100 0 1 FTVL:STRING
p 2016 2112 100 0 0 PREC:8
p 1936 2176 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 1160 2184 100 0 Equinox
xform 0 1344 2336
p 1248 2510 100 0 -1 DESC:Equinox for target coordinates
p 1296 2350 100 0 1 EGU:years
p 1072 1920 100 0 0 FDSC:Equinox for target coordinates
p 1296 2318 100 0 1 FTVL:STRING
p 1328 2112 100 0 0 PREC:8
p 1248 2176 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 2456 2616 100 0 Dec
xform 0 2640 2768
p 2544 2942 100 0 -1 DESC:Demand Dec of target
p 2592 2782 100 0 1 EGU:degs
p 2368 2352 100 0 0 FDSC:Demand Dec of target
p 2592 2750 100 0 1 FTVL:DOUBLE
p 2624 2544 100 0 0 PREC:8
p 2544 2608 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 1848 2616 100 0 RA
xform 0 2032 2768
p 1936 2942 100 0 -1 DESC:Demand RA of target
p 1984 2782 100 0 1 EGU:degs
p 1760 2352 100 0 0 FDSC:Demand RA of target
p 1984 2750 100 0 1 FTVL:DOUBLE
p 2016 2544 100 0 0 PREC:8
p 1936 2608 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 1160 2616 100 0 ObjectName
xform 0 1344 2768
p 1296 2926 100 0 -1 DESC:Object name
p 1072 2352 100 0 0 FDSC:Name of target
p 1248 2608 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 3096 2616 100 0 InputFrame
xform 0 3280 2768
p 3152 2942 100 0 -1 DESC:Coordinate frame of target
p 3008 2352 100 0 0 FDSC:Coordinate frame of target
p 3184 2608 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 2456 2184 100 0 Parallax
xform 0 2640 2336
p 2544 2510 100 0 -1 DESC:Parallax of target
p 2576 2350 100 0 1 EGU:arcsec
p 2368 1920 100 0 0 FDSC:Parallax of target
p 2576 2318 100 0 1 FTVL:DOUBLE
p 2544 2176 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 3112 2184 100 0 RV
xform 0 3296 2336
p 3200 2510 100 0 -1 DESC:Radial velocity of target
p 3232 2350 100 0 1 EGU:Km/sec
p 3024 1920 100 0 0 FDSC:Radial velocity of target
p 3232 2318 100 0 1 FTVL:DOUBLE
p 3200 2176 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 1160 1736 100 0 PMRA
xform 0 1344 1888
p 1248 2062 100 0 -1 DESC:Proper motion in RA
p 1280 1902 100 0 1 EGU:s/year
p 1072 1472 100 0 0 FDSC:Proper motion in RA
p 1280 1870 100 0 1 FTVL:DOUBLE
p 1328 1664 100 0 0 PREC:5
p 1248 1728 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 1848 1736 100 0 PMDec
xform 0 2032 1888
p 1936 2062 100 0 -1 DESC:Proper motion in Declination
p 1968 1902 100 0 1 EGU:arcsec/year
p 1760 1472 100 0 0 FDSC:Proper motion in declination
p 1968 1870 100 0 1 FTVL:DOUBLE
p 2016 1664 100 0 0 PREC:4
p 1936 1728 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 2456 1736 100 0 Wavelength
xform 0 2640 1888
p 2544 2062 100 0 -1 DESC:Effective wavelength of target
p 2576 1902 100 0 1 EGU:Angstroms
p 2368 1472 100 0 0 FDSC:Effective wavelength of target
p 2576 1870 100 0 1 FTVL:DOUBLE
p 2544 1728 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 1176 1320 100 0 DiffEpoch
xform 0 1360 1472
p 1168 1646 100 0 -1 DESC:Epoch of differential track rate
p 1216 1454 100 0 1 EGU:Years (TT scale as MJD)
p 1088 1056 100 0 0 FDSC:Epoch of differential track rate
p 1296 1486 100 0 1 FTVL:DOUBLE
p 1344 1248 100 0 0 PREC:6
p 1264 1312 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 1848 1320 100 0 DiffRA
xform 0 2032 1472
p 1936 1646 100 0 -1 DESC:Differential track rate in RA
p 1968 1486 100 0 1 EGU:s/s
p 1760 1056 100 0 0 FDSC:Differential track rate in RA
p 1968 1454 100 0 1 FTVL:DOUBLE
p 2016 1248 100 0 0 PREC:11
p 1936 1312 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 2456 1320 100 0 DiffDec
xform 0 2640 1472
p 2544 1646 100 0 -1 DESC:Differential track rate in Dec.
p 2576 1486 100 0 1 EGU:arcsec/s
p 2368 1056 100 0 0 FDSC:Differential track rate in Dec.
p 2576 1454 100 0 1 FTVL:DOUBLE
p 2080 1472 100 0 0 PREC:10
p 2544 1312 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 3064 1320 100 0 DiffFrame
xform 0 3248 1472
p 3120 1646 100 0 -1 DESC:Coordinate frame of diff. track rate
p 2976 1056 100 0 0 FDSC:Coordinate frame of diff. track rate
p 3152 1312 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 3704 1320 100 0 DiffEquinox
xform 0 3888 1472
p 3728 1646 100 0 -1 DESC:Equinox for diff. track rate
p 3840 1486 100 0 1 EGU:years
p 3616 1056 100 0 0 FDSC:Equinox for diff. track rate
p 3840 1454 100 0 1 FTVL:STRING
p 3872 1248 100 0 0 PREC:8
p 3792 1312 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 1176 904 100 0 TrackEq
xform 0 1360 1056
p 1200 1230 100 0 -1 DESC:Equinox for tracking frame
p 1312 1070 100 0 1 EGU:years
p 1088 640 100 0 0 FDSC:Equinox for tracking frame
p 1312 1038 100 0 1 FTVL:STRING
p 1344 832 100 0 0 PREC:8
p 1264 896 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 1848 904 100 0 TrackFrame
xform 0 2032 1056
p 1904 1230 100 0 -1 DESC:Tracking Frame
p 1760 640 100 0 0 FDSC:Tracking Frame
p 1936 896 100 1024 0 name:$(sad)$(vt)$(I)
use esirs 3672 2616 100 0 RaDecSys
xform 0 3856 2768
p 3728 2942 100 0 -1 DESC:Coordinate frame of target
p 3584 2352 100 0 0 FDSC:Coord. frame of target in FITS
p 3776 2768 100 0 1 SNAM:sirRaDecSys
p 3760 2608 100 1024 0 name:$(sad)$(vt)$(I)
use bc200tr 896 696 -100 0 frame
xform 0 2576 2000
[comments]
