[schematic2]
uniq 2
[tools]
[detail]
w 2054 1771 100 0 n#1 inhier.TEMP1.P 1904 1760 2240 1760 eaos.ExtTemp1.SLNK
s 2208 2272 200 0 Node Box Records
s 3168 1072 100 0 Node box schematic
s 3168 1136 100 0 Gemini TCS PCS Internal simulation
s 2912 1072 100 0 Sciences Ltd.
s 2912 1104 100 0 Observatory
s 2912 1136 100 0 Copyright
s 2912 2368 100 0 $Id: m1NodeBox.sch,v 1.1 2002/02/22 10:59:50 cjm Exp $
[cell use]
use inhier 1888 1719 100 0 TEMP1
xform 0 1904 1760
use eaos 2240 1671 100 0 ExtTemp1
xform 0 2368 1760
p 2224 1856 100 0 -1 DESC:External Temperature sensor
p 2208 1486 100 0 0 EGU:deg C
use bb200tr 1136 856 -100 0 frame
xform 0 2416 1680
[comments]
