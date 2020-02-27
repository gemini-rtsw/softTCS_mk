[schematic2]
uniq 28
[tools]
[detail]
w 1096 1371 100 0 n#27 eais.updateInterval.VAL 912 1184 1024 1184 1024 1360 1216 1360 egenSubD.aoZernikes.INPP
w 1048 1403 100 0 n#25 elongins.numZernikes.VAL 928 1392 1216 1392 egenSubD.aoZernikes.INPO
w 1048 1851 100 0 n#23 elongins.correct.VAL 928 1840 1216 1840 egenSubD.aoZernikes.INPA
w -32 1083 100 0 n#17 ebos.startLoop.VAL -96 1072 80 1072 efanouts.startFan.SDIS
s 2032 2064 100 0 $Id: gems.sch,v 1.1 2009/12/01 14:09:34 cjm Exp $
s 2016 -128 100 0 Copyright
s 2016 -160 100 0 Observatory
s 2016 -192 100 0 Sciences Ltd.
[cell use]
use eais 656 1127 100 0 updateInterval
xform 0 784 1200
p 656 1264 100 0 -1 DESC:Zernike update interval
p 400 942 100 0 0 EGU:secs
p 768 1120 100 1024 0 name:$(gems)$(I)
use elongins 672 1783 100 0 correct
xform 0 800 1856
p 672 1936 100 0 -1 DESC:Turn corrections on/off
p 416 1854 100 0 0 EGU:units
p 784 1776 100 1024 0 name:$(gems)$(I)
use elongins 672 1335 100 0 numZernikes
xform 0 800 1408
p 704 1488 100 0 -1 DESC:Number of Zernikes
p 416 1406 100 0 0 EGU:units
p 784 1328 100 1024 0 name:$(gems)$(I)
use egenSubD 1216 1047 100 0 aoZernikes
xform 0 1360 1472
p 1296 1920 100 0 -1 DESC:Supply aO data
p 993 821 100 0 0 FTA:LONG
p 993 725 100 0 0 FTO:LONG
p 1328 1360 100 0 1 NOVJ:40
p 1376 960 100 0 1 SCAN:1 second
p 1408 1008 100 0 1 SNAM:tcsGemsZernikes
p 932 1818 100 0 0 def(INPB):$(tcs)omSim:z1
p 932 1786 100 0 0 def(INPC):$(tcs)omSim:z2
p 932 1754 100 0 0 def(INPD):$(tcs)omSim:z3
p 932 1722 100 0 0 def(INPE):$(tcs)omSim:z4
p 932 1690 100 0 0 def(INPF):$(tcs)omSim:z6
p 932 1658 100 0 0 def(INPG):$(tcs)omSim:z8
p 932 1626 100 0 0 def(INPH):$(tcs)omSim:z9
p 932 1594 100 0 0 def(INPI):$(tcs)omSim:z11
p 932 1562 100 0 0 def(INPJ):$(tcs)omSim:z13
p 932 1530 100 0 0 def(INPK):$(tcs)omSim:z15
p 932 1498 100 0 0 def(INPL):$(tcs)omSim:z16
p 932 1466 100 0 0 def(INPM):$(tcs)omSim:z18
p 932 1434 100 0 0 def(INPN):$(tcs)omSim:zErr
p 1328 1040 100 1024 0 name:$(gems)$(I)
use egenSub 1216 7 100 0 rotCorrections
xform 0 1360 432
p 1168 864 100 0 -1 DESC:Generate rotator guide corrections
p 1296 784 100 0 -1 FTA:LONG
p 993 -219 100 0 0 FTVA:LONG
p 993 -859 100 0 0 NOVJ:3
p 928 558 100 0 0 PREC:14
p 1440 -64 100 0 1 SCAN:1 second
p 1440 -16 100 0 1 SNAM:tcsGemsRotCorrections
p 1328 0 100 1024 0 name:$(gems)$(I)
use efanouts 80 903 100 0 startFan
xform 0 200 1056
p -34 1321 100 0 0 DESC:Simulator fanout
p -32 976 100 0 1 SCAN:.05 second
p 192 896 100 1024 0 name:$(top)$(subsys)$(I)
use ebos -352 983 100 0 startLoop
xform 0 -224 1072
p -584 1228 100 0 0 DESC:Disable/enable simulation loop
p -672 926 100 0 0 ONAM:enabled
p -672 958 100 0 0 ZNAM:disabled
p -240 976 100 1024 0 name:$(top)$(subsys)$(I)
use simSwitch -256 1607 100 0 simSwitch#13
xform 0 -96 1776
p -236 1580 100 0 1 seta:scanloc $(top)$(subsys)startFan.SCAN
use bc200tr -560 -408 -100 0 frame
xform 0 1120 896
[comments]
