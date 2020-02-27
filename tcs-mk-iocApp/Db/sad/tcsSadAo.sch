[schematic2]
uniq 18
[tools]
[detail]
s 2432 48 100 0 Sciences Ltd.
s 2432 80 100 0 Observatory
s 2432 112 100 0 Copyright
s 2448 2288 100 0 $Id: tcsSadAo.sch,v 1.1 2002/11/08 12:13:47 cjm Exp $
s 96 1936 100 0 of the same name in the main TCS database. 
s 96 1984 100 0 The four records below are written to by records
s 2688 96 100 0 Gemini Telescope Control System
[cell use]
use esirs 248 1512 100 0 aoXmin
xform 0 432 1664
p 304 1838 100 0 -1 DESC:Altair lower X limit
p 320 1662 100 0 1 EGU:mm
p 160 1248 100 0 0 FDSC:Min. X coord to which Altair  
p 320 1566 100 0 1 FTVL:DOUBLE
p 416 1440 100 0 0 PREC:2
p 336 1504 100 1024 0 name:$(sad)$(I)
use esirs 1016 1512 100 0 aoXmax
xform 0 1200 1664
p 1072 1838 100 0 -1 DESC:Altair upper X limit
p 1088 1662 100 0 1 EGU:mm
p 928 1248 100 0 0 FDSC:Max. X coord to which Altair  
p 1088 1566 100 0 1 FTVL:DOUBLE
p 1184 1440 100 0 0 PREC:2
p 1104 1504 100 1024 0 name:$(sad)$(I)
use esirs 1784 1512 100 0 aoYmin
xform 0 1968 1664
p 1840 1838 100 0 -1 DESC:Altair lower Y limit
p 1856 1662 100 0 1 EGU:mm
p 1696 1248 100 0 0 FDSC:Min. Y coor to which Altair
p 1856 1566 100 0 1 FTVL:DOUBLE
p 1952 1440 100 0 0 PREC:2
p 1872 1504 100 1024 0 name:$(sad)$(I)
use esirs 2456 1512 100 0 aoYmax
xform 0 2640 1664
p 2512 1838 100 0 -1 DESC:Altair upper Y limit
p 2528 1662 100 0 1 EGU:mm
p 2368 1248 100 0 0 FDSC:Max. Y coord to which Altair  
p 2528 1566 100 0 1 FTVL:DOUBLE
p 2624 1440 100 0 0 PREC:2
p 2544 1504 100 1024 0 name:$(sad)$(I)
use bc200tr -144 -184 -100 0 frame
xform 0 1536 1120
[comments]
