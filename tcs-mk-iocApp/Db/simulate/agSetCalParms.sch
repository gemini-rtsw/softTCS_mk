[schematic2]
uniq 11
[tools]
[detail]
w 848 1147 100 0 n#10 eaos.RTMin.VAL 576 1024 768 1024 768 1136 976 1136 egenSubD.probeCalParm.INPM
w 854 1179 100 0 n#9 eaos.RTMax.VAL 576 1280 768 1280 768 1168 976 1168 egenSubD.probeCalParm.INPL
s 1952 2080 100 0 $Id: agSetCalParms.sch,v 1.2 2010/02/26 19:03:27 gemvx Exp $
s 1968 -112 100 0 Copyright
s 1968 -144 100 0 Observatory
s 1968 -176 100 0 Sciences Ltd.
s 736 1920 200 0 Mimic Probe Calibration Parameters
[cell use]
use egenSubD 976 727 100 0 probeCalParm
xform 0 1120 1152
p 960 1584 100 0 -1 DESC:Mimic A&G CalParms functions
p 1200 656 100 0 1 SCAN:1 second
p 1200 704 100 0 1 SNAM:tcsAgsSetCalParms
use eaos 320 935 100 0 RTMin
xform 0 448 1024
p 320 1136 100 0 -1 DESC:Rotary Table Lower Limit
p 288 750 100 0 0 EGU:degrees
p 64 878 100 0 0 PREC:2
use eaos 320 1191 100 0 RTMax
xform 0 448 1280
p 320 1392 100 0 -1 DESC:Rotary Table Upper Limit
p 288 1006 100 0 0 EGU:degrees
p 64 1134 100 0 0 PREC:2
use bc200tr -624 -392 -100 0 frame
xform 0 1056 912
[comments]
