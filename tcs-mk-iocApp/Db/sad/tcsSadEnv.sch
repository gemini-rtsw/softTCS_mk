[schematic2]
uniq 200
[tools]
[detail]
s 608 1744 100 0 $Id: tcsSadEnv.sch,v 1.3 2002/10/02 08:34:03 cjm Exp $
s 864 -512 100 0 Gemini Telescope Control System
s 896 -448 100 0 Status and Alarm Database
[cell use]
use esirs 440 136 100 0 sodiumRange
xform 0 624 288
p 512 446 100 0 -1 DESC:Sodium layer range
p 512 286 100 0 1 EGU:km
p 352 -128 100 0 0 FDSC:Distance to sodium layer
p 367 -192 100 0 0 FTVL:DOUBLE
p 352 -480 100 0 0 MDEL:0.005
p 367 -224 100 0 0 PREC:2
p 512 254 100 0 1 SNAM:
p 528 128 100 1024 0 name:$(sad)$(I)
use esirs 440 552 100 0 sodiumAltitude
xform 0 624 704
p 512 862 100 0 -1 DESC:Sodium layer altitude
p 512 702 100 0 1 EGU:km
p 352 288 100 0 0 FDSC:Height of sodium layer above sea-level
p 367 224 100 0 0 FTVL:DOUBLE
p 352 -64 100 0 0 MDEL:0.005
p 367 192 100 0 0 PREC:2
p 512 670 100 0 1 SNAM:
p 528 544 100 1024 0 name:$(sad)$(I)
use esirs -808 936 100 0 currentDewPoint
xform 0 -624 1088
p -720 1246 100 0 -1 DESC:Current Dew Point
p -736 1070 100 0 1 EGU:deg C
p -896 640 100 0 0 FTVL:DOUBLE
p -640 864 100 0 0 PREC:1
p -1072 1182 100 0 0 def(INP):0.0
p -720 928 100 1024 0 name:$(sad)$(I)
use esirs -808 136 100 0 currentRH
xform 0 -624 288
p -752 462 100 0 -1 DESC:Current relative humidity
p -720 302 100 0 1 EGU:percentage
p -881 -192 100 0 0 FTVL:DOUBLE
p -881 -224 100 0 0 PREC:1
p -720 270 100 0 1 SNAM:
p -720 128 100 1024 0 name:$(sad)$(I)
use esirs -168 552 100 0 currentAirPressure
xform 0 16 704
p -96 862 100 0 -1 DESC:Current air pressure
p -96 702 100 0 1 EGU:millibars
p -241 224 100 0 0 FTVL:DOUBLE
p -241 192 100 0 0 PREC:2
p -96 670 100 0 1 SNAM:
p -80 544 100 1024 0 name:$(sad)$(I)
use esirs -808 552 100 0 currentExternalTemp
xform 0 -624 704
p -752 862 100 0 -1 DESC:Current air temperature
p -736 718 100 0 1 EGU:deg C
p -881 224 100 0 0 FTVL:LONG
p -881 192 100 0 0 PREC:2
p -736 686 100 0 1 SNAM:
p -720 544 100 1024 0 name:$(sad)$(I)
use esirs -168 936 100 0 currentWindSpeed
xform 0 16 1088
p -80 1246 100 0 -1 DESC:Current wind speed
p -80 1086 100 0 1 EGU:Km/h
p -256 640 100 0 0 FTVL:DOUBLE
p 0 864 100 0 0 PREC:1
p -80 928 100 1024 0 name:$(sad)$(I)
use esirs -168 136 100 0 useWS
xform 0 16 288
p -64 462 100 0 -1 DESC:Environment Mode
p -256 -64 100 0 0 EGU:none
p 0 64 100 0 0 PREC:1
p -80 128 100 1024 0 name:$(sad)$(I)
use esirs 440 936 100 0 currentWindDir
xform 0 624 1088
p 528 1246 100 0 -1 DESC:Current wind direction
p 528 1086 100 0 1 EGU:degs
p 352 640 100 0 0 FTVL:DOUBLE
p 608 864 100 0 0 PREC:1
p 528 928 100 1024 0 name:$(sad)$(I)
use bc200tr -1968 -728 -100 0 frame
xform 0 -288 576
[comments]
