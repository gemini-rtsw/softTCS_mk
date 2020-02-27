[schematic2]
uniq 5
[tools]
[detail]
w 1274 1402 100 0 n#1 estringinval.StringState.FLNK 1264 1392 1440 1392 1440 960 1680 960 egenSub.convertState.SLNK
w 1274 1370 100 0 n#2 estringinval.StringState.VAL 1264 1360 1536 1360 1536 1632 1680 1632 egenSub.convertState.INPA
w 1978 1674 100 0 n#3 egenSub.convertState.VALA 1968 1664 2160 1664 outhier.STATE.p
w 1978 938 100 0 n#4 egenSub.convertState.FLNK 1968 928 2136 928 outhier.FLNK.p
s 2592 2440 100 0 $Id: tcsGsaoiState.sch,v 1.1 2010/04/12 12:40:19 cjm Exp $
s 2592 256 100 0 Copyright
s 2584 216 100 0 Observatory
s 2592 176 100 0 Sciences Ltd.
[cell use]
use bc200tr 0 0 100 0 bc200tr#1
xform 0 1680 1280
use estringinval 1071 1303 100 0 StringState
xform 0 1136 1376
p 1059 1446 100 0 -1 DESC:State of GSAOI
p 1008 1470 100 0 0 VAL:INITIALISING
p 936 1416 75 1280 -1 pproc(INP):CA
p 1071 1303 100 0 -1 PV:
p 1120 1296 100 1024 0 name:$(tcs)$(subnam)$(I)
p 1170 1273 100 0 1 SCAN:1 second
p 754 1393 100 0 -1 def(INP):$(subsys)state
use egenSub 1779 870 100 0 convertState
xform 0 1824 1296
p 1771 1730 100 0 -1 DESC:Interpret State
p 1835 828 100 0 1 SNAM:tcsStateIndex
p 1457 645 100 0 0 FTA:STRING
p 1457 645 100 0 0 FTVA:LONG
p 1792 864 100 1024 0 name:$(tcs)$(subnam)$(I)
use outhier 2129 1614 100 0 STATE
xform 0 2144 1664
use outhier 2105 885 100 0 FLNK
xform 0 2120 928
[comments]
