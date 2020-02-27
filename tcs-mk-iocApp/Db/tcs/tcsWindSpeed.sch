[schematic2]
uniq 14
[tools]
[detail]
w 1680 1835 100 0 n#13 eais.wsWindDirection.VAL 1584 1824 1824 1824 1824 1696 1968 1696 eaos.currentWindDir.DOL
w 2136 1835 100 0 n#12 eaos.currentWindSpeed.FLNK 2224 2240 2464 2240 2464 1824 1856 1824 1856 1664 1968 1664 eaos.currentWindDir.SLNK
w 1840 2251 100 0 n#10 eais.wsWindSpeed.VAL 1584 2176 1760 2176 1760 2240 1968 2240 eaos.currentWindSpeed.DOL
w 1702 1867 100 0 n#9 eais.wsWindDirection.FLNK 1584 1856 1856 1856 1856 2208 1968 2208 eaos.currentWindSpeed.SLNK
w 1454 1995 100 0 n#8 eais.wsWindSpeed.FLNK 1584 2208 1728 2208 1728 1984 1216 1984 1216 1840 1328 1840 eais.wsWindDirection.SLNK
w 1102 2171 100 0 n#6 inhier.SDIS.P 912 2160 1328 2160 eais.wsWindSpeed.SDIS
s 2384 2320 100 0 from elsewhere
s 2384 2352 100 0 possibility at a later date to set the wind speed 
s 2384 2384 100 0 then written to the record windSpeed to allow the
s 2384 2416 100 0 N.B. The data is pulled from the weather server and
s 2352 2512 100 0 $Id: tcsWindSpeed.sch,v 1.4 2002/02/18 14:48:23 cjm Exp $
s 2672 1216 100 0 Wind Speed Alarm
s 2624 1280 100 0 Gemini Telescope Control System
[cell use]
use eaos 1992 2120 100 0 currentWindSpeed
xform 0 2096 2208
p 1984 2318 100 0 -1 DESC:Current Wind Speed
p 2048 2046 100 0 1 EGU:Km/h
p 2192 1982 100 0 1 HHSV:MAJOR
p 2048 2014 100 0 1 HIGH:40.0
p 2048 1982 100 0 1 HIHI:90.0
p 2192 2014 100 0 1 HSV:MINOR
p 1712 2190 100 0 0 OMSL:closed_loop
p 1712 2062 100 0 0 PREC:1
p 2320 2174 100 0 -1 def(OUT):$(sad)currentWindSpeed
p 2320 2112 100 1024 1 name:$(tcs)$(I)
p 2256 2176 75 768 -1 palrm(OUT):MS
p 2224 2176 75 768 -1 pproc(OUT):CA
use eaos 1992 1576 100 0 currentWindDir
xform 0 2096 1664
p 1984 1774 100 0 -1 DESC:Current Wind Direction
p 2048 1502 100 0 1 EGU:degs
p 2192 1438 100 0 0 HHSV:NO_ALARM
p 2048 1470 100 0 0 HIGH:0.0
p 2048 1438 100 0 0 HIHI:0.0
p 2192 1470 100 0 0 HSV:NO_ALARM
p 1712 1646 100 0 0 OMSL:closed_loop
p 1712 1518 100 0 0 PREC:1
p 2320 1630 100 0 -1 def(OUT):$(sad)currentWindDir
p 2320 1568 100 1024 1 name:$(tcs)$(I)
p 2256 1632 75 768 -1 palrm(OUT):MS
p 2224 1632 75 768 -1 pproc(OUT):CA
use eais 1328 2119 100 0 wsWindSpeed
xform 0 1456 2192
p 1072 1742 100 0 0 ADEL:0.1
p 1296 2272 100 0 -1 DESC:Wind speed from weather server
p 1392 2064 100 0 1 EGU:km/hr
p 1072 1710 100 0 0 MDEL:0.1
p 1072 2030 100 0 0 PREC:2
p 1392 2032 100 0 1 SCAN:1 second
p 1072 2224 100 0 -1 def(INP):$(ws)windSpeed
p 1440 2112 100 1024 0 name:$(tcs)$(I)
use eais 1328 1767 100 0 wsWindDirection
xform 0 1456 1840
p 1072 1390 100 0 0 ADEL:0.1
p 1296 1920 100 0 -1 DESC:Wind direction from weather server
p 1392 1712 100 0 1 EGU:degs
p 1072 1358 100 0 0 MDEL:0.1
p 1072 1678 100 0 0 PREC:2
p 1392 1680 100 0 0 SCAN:Passive
p 976 1872 100 0 -1 def(INP):$(ws)windDirection
p 1440 1760 100 1024 0 name:$(tcs)$(I)
use inhier 920 2120 100 0 SDIS
xform 0 912 2160
use bb200tr 576 1000 -100 0 frame
xform 0 1856 1824
[comments]
