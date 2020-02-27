[schematic2]
uniq 278
[tools]
[detail]
w 994 1659 100 0 n#256 esirs.present.FLNK 1216 2048 1296 2048 1296 1648 752 1648 752 1216 864 1216 ecalcs.binHeartBeat.SLNK
w 466 2347 100 0 n#125 junction 704 2048 704 2336 288 2336 288 2240 384 2240 ecalcs.ticker.INPA
w 706 2059 100 0 n#125 ecalcs.ticker.VAL 672 2048 800 2048 esirs.present.INP
w 746 1611 100 0 n#125 junction 688 2048 688 1600 864 1600 ecalcs.binHeartBeat.INPA
w 740 1979 100 0 n#126 ecalcs.ticker.FLNK 672 2080 736 2080 736 1888 800 1888 esirs.present.SLNK
s 1088 3168 140 0 gpSimSad.sch
[cell use]
use esirs -1104 1639 100 0 name
xform 0 -896 1792
p -800 1568 100 0 0 EGU:units
p -1040 1600 100 0 1 FDSC:GPOL System name
p -1040 1568 100 0 1 FTVL:STRING
p -896 1568 100 0 0 PREC:0
p -1040 1536 100 0 1 SCAN:Passive
p -1104 1888 75 1280 -1 palrm(INP):MS
use esirs -1104 567 100 0 state
xform 0 -896 720
p -800 496 100 0 0 EGU:units
p -1040 528 100 0 1 FDSC:GPOL System state
p -1040 496 100 0 1 FTVL:STRING
p -896 496 100 0 0 PREC:0
p -1040 464 100 0 1 SCAN:Passive
p -1104 816 75 1280 -1 palrm(INP):MS
use esirs 800 1799 100 0 present
xform 0 1008 1952
p 1104 1728 100 0 1 EGU:Ticks
p 864 1760 100 0 1 FDSC:Heart Beat
p 864 1728 100 0 1 FTVL:LONG
p 1008 1728 100 0 1 PREC:0
p 864 1696 100 0 1 SCAN:Passive
use esirs -1088 2135 100 0 health
xform 0 -880 2288
p -784 2064 100 0 0 EGU:units
p -1024 2096 100 0 1 FDSC:GPOL System health
p -1024 2064 100 0 1 FTVL:STRING
p -880 2064 100 0 0 PREC:0
p -1024 2032 100 0 1 SCAN:Passive
p -1088 2384 75 1280 -1 palrm(INP):MS
use bd200tr -3008 -72 -100 0 frame
xform 0 -368 1632
use ecalcs 384 1767 100 0 ticker
xform 0 528 2032
p 448 1744 100 0 1 CALC:A<100?A+1:0
p 96 1918 100 0 0 EGU:Ticks
p 448 1712 100 0 1 SCAN:1 second
use ecalcs 864 1127 100 0 binHeartBeat
xform 0 1008 1392
p 960 1440 100 0 1 CALC:A%2
p 880 1088 100 0 1 PV:$(sadtop)
[comments]
