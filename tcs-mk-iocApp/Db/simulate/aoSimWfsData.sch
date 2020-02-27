[schematic2]
uniq 73
[tools]
[detail]
w 840 2411 100 0 n#71 eais.updateInterval.VAL 736 2240 800 2240 800 2400 928 2400 egenSubD.aoZernikes.INPP
w 840 2443 100 0 n#69 elongins.numZernikes.VAL 736 2464 800 2464 800 2432 928 2432 egenSubD.aoZernikes.INPO
w 1368 2315 100 0 n#67 egenSubD.aoZernikes.VALJ 1216 2304 1568 2304 outhier.c#4.p
s 2224 3616 100 0 $Id: aoSimWfsData.sch,v 1.3 2002/11/08 12:22:03 cjm Exp $
s 896 3520 200 0 Simulate provision of WFS data
s 1360 2328 120 0 Data to TCS
s 2256 1280 100 0 9 Dec 1997
s 2256 1312 100 0 P.B. Taylor
s 2512 1376 100 0 WFS continuous data
s 2528 1344 100 0 simulated records
s 2560 1424 130 0 Gemini TCS
[cell use]
use egenSub 2048 2087 100 0 imageDistort
xform 0 2192 2512
p 2000 2944 100 0 -1 DESC:Simulate transform coefficients
p 2176 2864 100 0 1 NOVA:3
p 2176 2304 100 0 1 NOVJ:6
p 2288 2048 100 0 1 SNAM:tcsAOsetTransform
p 2160 2080 100 1024 0 name:$(ao)$(I)
use eais 480 2183 100 0 updateInterval
xform 0 608 2256
p 464 2336 100 0 -1 DESC:Zernike update interval
p 224 1998 100 0 0 EGU:secs
p 224 2094 100 0 0 PREC:1
p 592 2176 100 1024 0 name:$(ao)$(I)
use elongins 480 2407 100 0 numZernikes
xform 0 608 2480
p 480 2544 100 0 -1 DESC:Number of Zernikes 
p 224 2478 100 0 0 EGU:units
p 592 2400 100 1024 0 name:$(ao)$(I)
use egenSubD 928 2087 100 0 aoZernikes
xform 0 1072 2512
p 976 2928 100 0 -1 DESC:Supply aO data
p 1008 2880 100 0 -1 FTA:LONG
p 1008 2432 100 0 -1 FTO:LONG
p 1056 2288 100 0 1 NOVJ:40
p 640 2638 100 0 0 PREC:14
p 1152 2016 100 0 1 SCAN:1 second
p 1152 2064 100 0 1 SNAM:tcsAoZernikes
p 672 2880 100 0 -1 def(INPA):$(ao)correct.VALA
p 644 2858 100 0 0 def(INPB):$(tcs)omSim:z1
p 644 2826 100 0 0 def(INPC):$(tcs)omSim:z2
p 644 2794 100 0 0 def(INPD):$(tcs)omSim:z3
p 644 2762 100 0 0 def(INPE):$(tcs)omSim:z4
p 644 2730 100 0 0 def(INPF):$(tcs)omSim:z6
p 644 2698 100 0 0 def(INPG):$(tcs)omSim:z8
p 644 2666 100 0 0 def(INPH):$(tcs)omSim:z9
p 644 2634 100 0 0 def(INPI):$(tcs)omSim:z11
p 644 2602 100 0 0 def(INPJ):$(tcs)omSim:z13
p 644 2570 100 0 0 def(INPK):$(tcs)omSim:z15
p 644 2538 100 0 0 def(INPL):$(tcs)omSim:z16
p 644 2506 100 0 0 def(INPM):$(tcs)omSim:z18
p 644 2474 100 0 0 def(INPN):$(tcs)omSim:zErr
p 1040 2080 100 1024 0 name:$(ao)$(I)
use outhier 1560 2264 100 0 c#4
xform 0 1552 2304
use bc200tr -368 1144 -100 0 frame
xform 0 1312 2448
[comments]
