[schematic2]
uniq 9
[tools]
[detail]
w 854 2114 100 0 n#8 estringouts.estringouts#7.OUT 784 2112 960 2112 960 2128 1120 2128 egenSub.egenSub#4.B
w 1010 1682 100 0 n#6 ebos.ebos#0.FLNK 752 1840 1008 1840 1008 1488 1120 1488 egenSub.egenSub#4.SLNK
w 978 2002 100 0 n#5 ebos.ebos#0.VAL 752 1808 976 1808 976 2160 1120 2160 egenSub.egenSub#4.INPA
s 1984 1184 100 0 27 November 97
s 2016 1216 100 0 P.B. Taylor
s 2304 1248 100 0 on or off
s 2240 1280 100 0 Switch internal simulator
s 2336 1328 100 0 Gemini TCS
[cell use]
use estringouts 552 2056 100 0 estringouts#7
xform 0 656 2128
p 640 2048 100 1024 -1 name:$(top)$(subsys)simScanPeriod
p 784 2112 75 768 -1 pproc(OUT):PP
use egenSub 1144 1400 100 0 egenSub#4
xform 0 1264 1824
p 897 1173 100 0 0 FTA:LONG
p 897 1173 100 0 0 FTB:STRING
p 897 1173 100 0 0 FTVA:STRING
p 1184 1678 100 0 -1 SNAM:tcsSimScanControl
p 992 2094 100 0 0 def(INPB):0.0
p 1488 2174 100 0 -1 def(OUTA):$(scanloc)
p 1232 1392 100 1024 -1 name:$(top)$(subsys)scanOutput
p 1408 2170 75 0 -1 pproc(OUTA):NPP
use bb200tr 192 1048 -100 0 frame
xform 0 1472 1872
use ebos 520 1720 100 0 ebos#0
xform 0 624 1808
p 176 1662 100 0 0 ONAM:On
p 176 1694 100 0 0 ZNAM:Off
p 608 1712 100 1024 -1 name:$(top)$(subsys)simScanControl
[comments]
