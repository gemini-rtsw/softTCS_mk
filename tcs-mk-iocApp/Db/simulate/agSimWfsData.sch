[schematic2]
uniq 69
[tools]
[detail]
w 72 2251 100 0 n#73 junction 32 2512 32 2240 160 2240 agWfsExpectedZernikes.agWfsExpectedZernikes#68.PROBE
w 354 2944 100 0 n#73 inhier.PROBE.P -144 2512 352 2512 352 3328 736 3328 egenSub.ttfZero.INPA
w 992 2514 100 0 n#73 junction 352 2512 1680 2512 1680 3312 2016 3312 egenSubD.ttf.INPA
w 1808 2347 100 0 n#73 junction 1680 2512 1680 2336 1984 2336 egenSubD.ao.INPA
w 2424 1771 100 0 c#4 egenSubD.ao.VALJ 2272 1760 2624 1760 outhier.c#4.p
w 1352 3218 100 0 n#64 eaos.ttfZ2.SLNK 1232 3104 1184 3104 1184 3216 1568 3216 1568 3328 1488 3328 eaos.ttfZ1.FLNK
w 1360 2978 100 0 n#63 eaos.ttfZ2.FLNK 1488 3136 1584 3136 1584 2976 1184 2976 1184 2896 1232 2896 eaos.ttfZ3.SLNK
w 584 2786 100 0 n#62 inhier.ttfdatra.P 480 2784 736 2784 egenSub.ttfZero.J
w 1170 2984 100 0 n#61 egenSub.ttfZero.FLNK 1024 2624 1168 2624 1168 3296 1232 3296 eaos.ttfZ1.SLNK
w 1090 3104 100 0 n#38 egenSub.ttfZero.VALC 1024 3232 1088 3232 1088 2928 1232 2928 eaos.ttfZ3.DOL
w 1138 3240 100 0 n#37 egenSub.ttfZero.VALB 1024 3296 1136 3296 1136 3136 1232 3136 eaos.ttfZ2.DOL
w 1072 3362 100 0 n#36 egenSub.ttfZero.VALA 1024 3360 1168 3360 1168 3328 1232 3328 eaos.ttfZ1.DOL
w 2440 2770 100 0 n#66 egenSubD.ttf.OUTI 2304 2768 2624 2768 outhier.c#5.p
s 2416 1784 120 0 Data to TCS
s 2416 2800 120 0 Data to TCS
s 448 2832 120 0 Data from TCS
s 2208 3616 100 0 $Id: agSimWfsData.sch,v 1.7 2010/02/01 15:00:21 ajf Exp $
s 2256 1280 100 0 9 Dec 1997
s 2256 1312 100 0 P.B. Taylor
s 2512 1376 100 0 WFS continuous data
s 2528 1344 100 0 simulated records
s 2560 1424 130 0 Gemini TCS
s 192 3515 150 0 continuous data
s 192 3563 150 0 Simulated WFS
s 1472 3563 150 0 Simulated WFS
s 1472 3515 150 0 continuous data
s 192 3472 150 0 from TCS to A&G
s 1472 3472 150 0 from A&G to TCS
[cell use]
use agWfsExpectedZernikes 160 2039 100 0 agWfsExpectedZernikes#68
xform 0 296 2232
use egenSubD 1984 1543 100 0 ao
xform 0 2128 1968
p 2032 2384 100 0 -1 DESC:Generate aO data
p 2112 1744 100 0 1 NOVJ:40
p 1696 2094 100 0 0 PREC:14
p 2080 2064 100 0 -1 SCAN:1 second
p 2080 1824 100 0 -1 SNAM:tcsAgsAo
p 1700 2346 100 0 0 def(INPA):0.000000000000000e+00
p 1700 2314 100 0 0 def(INPB):$(tcs)omSim:z1
p 1700 2282 100 0 0 def(INPC):$(tcs)omSim:z2
p 1700 2250 100 0 0 def(INPD):$(tcs)omSim:z3
p 1700 2218 100 0 0 def(INPE):$(tcs)omSim:z4
p 1700 2186 100 0 0 def(INPF):$(tcs)omSim:z6
p 1700 2154 100 0 0 def(INPG):$(tcs)omSim:z8
p 1700 2122 100 0 0 def(INPH):$(tcs)omSim:z9
p 1700 2090 100 0 0 def(INPI):$(tcs)omSim:z11
p 1700 2058 100 0 0 def(INPJ):$(tcs)omSim:z13
p 1700 2026 100 0 0 def(INPK):$(tcs)omSim:z15
p 1700 1994 100 0 0 def(INPL):$(tcs)omSim:z16
p 1700 1962 100 0 0 def(INPM):$(tcs)omSim:z18
p 1700 1930 100 0 0 def(INPN):$(tcs)omSim:zErr
use egenSubD 2016 2519 100 0 ttf
xform 0 2160 2944
p 1859 3259 100 0 0 DESC:Generate tip/tilt/focus data
p 1793 1813 100 0 0 NOE:1
p 2096 3152 100 0 1 NOF:8
p 2096 3120 100 0 1 NOG:8
p 2096 3088 100 0 1 NOH:8
p 2160 2736 100 0 1 NOVJ:8
p 1728 3070 100 0 0 PREC:9
p 2112 2880 100 0 -1 SCAN:1 second
p 2112 2816 100 0 -1 SNAM:tcsAgsTtf
p 1732 3322 100 0 0 def(INPA):0.000000000000000e+00
p 1732 3290 100 0 0 def(INPB):$(tcs)omSim:z1
p 1732 3258 100 0 0 def(INPC):$(tcs)omSim:z2
p 1732 3226 100 0 0 def(INPD):$(tcs)omSim:z3
p 1732 3194 100 0 0 def(INPE):$(tcs)omSim:zErr
p 1632 3152 100 0 -1 def(INPF):$(tcs)sky:simulate.VALD
p 1632 3120 100 0 -1 def(INPG):$(tcs)sky:simulate.VALE
p 1632 3088 100 0 -1 def(INPH):$(tcs)sky:simulate.VALF
p 1732 3066 100 0 0 def(INPI):$(tcs)drives:p1x
p 1732 3034 100 0 0 def(INPJ):$(tcs)drives:p1y
p 1732 3002 100 0 0 def(INPK):$(tcs)drives:p2x
p 1732 2970 100 0 0 def(INPL):$(tcs)drives:p2y
p 1732 2938 100 0 0 def(INPM):$(tcs)drives:oix
p 1732 2906 100 0 0 def(INPN):$(tcs)drives:oiy
p 1968 3194 75 0 -1 pproc(INPE):NPP
p 1968 3162 75 0 -1 pproc(INPF):CA
p 1968 3130 75 0 -1 pproc(INPG):CA
p 1968 3098 75 0 -1 pproc(INPH):CA
p 1968 3066 75 0 -1 pproc(INPI):CA
p 1968 3034 75 0 -1 pproc(INPJ):CA
p 1968 3002 75 0 -1 pproc(INPK):CA
p 1968 2970 75 0 -1 pproc(INPL):CA
p 1968 2938 75 0 -1 pproc(INPM):CA
p 1968 2906 75 0 -1 pproc(INPN):CA
use eaos 1256 2808 100 0 ttfZ3
xform 0 1360 2896
p 976 2334 100 0 0 MDEL:0.0001
p 976 2878 100 0 0 OMSL:closed_loop
p 976 2750 100 0 0 PREC:9
use eaos 1256 3016 100 0 ttfZ2
xform 0 1360 3104
p 976 2542 100 0 0 MDEL:0.0001
p 976 3086 100 0 0 OMSL:closed_loop
p 976 2958 100 0 0 PREC:9
use eaos 1256 3208 100 0 ttfZ1
xform 0 1360 3296
p 976 2734 100 0 0 MDEL:0.0001
p 976 3278 100 0 0 OMSL:closed_loop
p 976 3150 100 0 0 PREC:9
p 976 3406 100 0 0 SCAN:Passive
use inhier -136 2472 100 0 PROBE
xform 0 -144 2512
use inhier 488 2744 100 0 ttfdatra
xform 0 480 2784
use outhier 2616 1720 100 0 c#4
xform 0 2608 1760
use outhier 2616 2728 100 0 c#5
xform 0 2608 2768
use bc200tr -368 1144 -100 0 frame
xform 0 1312 2448
use egenSub 760 2568 100 0 ttfZero
xform 0 880 2992
p 513 2085 100 0 0 FTJ:DOUBLE
p 816 2750 100 0 1 NOJ:8
p 448 3118 100 0 0 PREC:9
p 832 3198 100 0 -1 SCAN:.05 second
p 800 2910 100 0 -1 SNAM:tcsAgsTtfZero
p 848 3022 100 0 1 Type:genSub
p 848 2560 100 1024 0 name:$(top)$(I)
[comments]
