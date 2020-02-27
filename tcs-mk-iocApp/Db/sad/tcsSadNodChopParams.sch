[schematic2]
uniq 54
[tools]
[detail]
w 1848 1515 100 0 n#53 esirs.nodAchopB.FLNK 2720 1888 2848 1888 2848 1504 896 1504 896 1120 1312 1120 esirs.nodBchopA.SLNK
w 2120 1131 100 0 n#52 esirs.nodBchopA.FLNK 1728 1280 1984 1280 1984 1120 2304 1120 esirs.nodBchopB.SLNK
w 2120 1739 100 0 n#48 esirs.nodAchopA.FLNK 1744 1888 1984 1888 1984 1728 2304 1728 esirs.nodAchopB.SLNK
s 2912 80 100 0 Sciences Ltd.
s 2912 112 100 0 Observatory
s 2912 144 100 0 Copyright
s 2928 2320 100 0 $Id: tcsSadNodChopParams.sch,v 1.1 2004/04/08 11:02:09 cjm Exp $
s 3200 64 100 0 TCS nod/chop SAD records
s 3168 128 100 0 Gemini Telescope Control System
[cell use]
use esirs 2304 1031 100 0 nodBchopB
xform 0 2512 1184
p 2416 1344 100 0 -1 DESC:Nod B Chop B
p 2544 1088 100 0 1 EGU:units
p 2240 768 100 0 0 FDSC:probe follows the nod B chop B state
p 2240 736 100 0 0 FTVL:LONG
p 2400 1088 100 0 1 NELM:1
p 2496 960 100 0 0 PREC:1
p 2512 1232 100 0 0 SCAN:Passive
p 1968 1328 100 0 -1 def(INP):$(top)drives:$(probe)nodBchopB
p 2416 1024 100 1024 0 name:$(sad)$(probe)$(I)
use esirs 1312 1031 100 0 nodBchopA
xform 0 1520 1184
p 1424 1344 100 0 -1 DESC:Nod B Chop A
p 1552 1088 100 0 1 EGU:units
p 1248 768 100 0 0 FDSC:probe follows the nod B chop A state
p 1248 736 100 0 0 FTVL:LONG
p 1408 1088 100 0 1 NELM:1
p 1504 960 100 0 0 PREC:1
p 1504 1008 100 0 0 SCAN:Passive
p 976 1328 100 0 -1 def(INP):$(top)drives:$(probe)nodBchopA
p 1424 1024 100 1024 0 name:$(sad)$(probe)$(I)
use esirs 2304 1639 100 0 nodAchopB
xform 0 2512 1792
p 2416 1952 100 0 -1 DESC:Nod A Chop B
p 2544 1696 100 0 1 EGU:units
p 2240 1376 100 0 0 FDSC:probe follows the nod A chop B state
p 2240 1344 100 0 0 FTVL:LONG
p 2400 1696 100 0 1 NELM:1
p 2496 1568 100 0 0 PREC:1
p 2496 1616 100 0 0 SCAN:Passive
p 1968 1936 100 0 -1 def(INP):$(top)drives:$(probe)nodAchopB
p 2416 1632 100 1024 0 name:$(sad)$(probe)$(I)
use esirs 1328 1639 100 0 nodAchopA
xform 0 1536 1792
p 1440 1952 100 0 -1 DESC:Nod A Chop A
p 1568 1696 100 0 1 EGU:units
p 1264 1376 100 0 0 FDSC:probe follows the nod A chop A state
p 1264 1344 100 0 0 FTVL:LONG
p 1424 1696 100 0 1 NELM:1
p 1520 1568 100 0 0 PREC:1
p 1520 1616 100 0 1 SCAN:1 second
p 992 1936 100 0 -1 def(INP):$(top)drives:$(probe)nodAchopA
p 1440 1632 100 1024 0 name:$(sad)$(probe)$(I)
use bc200tr 336 -152 -100 0 frame
xform 0 2016 1152
[comments]
