[schematic2]
uniq 44
[tools]
[detail]
w 3106 1144 100 0 n#43 ecalcs.amMean.VAL 3072 1200 3104 1200 3104 1040 3168 1040 outhier.AMMEAN.p
w 3106 1304 100 0 n#42 ecalcs.amMean.FLNK 3072 1232 3104 1232 3104 1328 3168 1328 outhier.FLNK.p
w 1568 2002 100 0 n#39 efanouts.endFan.LNK2 496 2000 2688 2000 2688 1008 2784 1008 ecalcs.amMean.SLNK
w 2658 1048 100 0 n#19 junction 2416 688 2656 688 2656 1360 2784 1360 ecalcs.amMean.INPB
w 2152 978 100 0 n#19 ecalcs.counter.VAL 2336 688 2416 688 2416 976 1936 976 1936 880 2048 880 ecalcs.counter.INPA
w 2582 1394 100 0 n#1 junction 2416 1392 2784 1392 ecalcs.amMean.INPA
w 2142 1682 100 0 n#1 ecalcs.amSum.VAL 2336 1392 2416 1392 2416 1680 1904 1680 1904 1584 2048 1584 ecalcs.amSum.INPA
w 1794 888 100 0 n#29 efanouts.fan.LNK2 1632 1248 1792 1248 1792 480 junction
w 1424 482 100 0 n#29 eaos.initCounter.OUT 1072 480 1824 480 1824 496 2048 496 ecalcs.counter.SLNK
w 1704 1282 100 0 n#27 efanouts.fan.LNK1 1632 1280 1824 1280 1824 1200 junction
w 1424 738 100 0 n#27 eaos.initAmSum.OUT 1072 736 1824 736 1824 1200 2048 1200 ecalcs.amSum.SLNK
w 642 1816 100 0 n#15 efanouts.endFan.LNK1 496 2032 640 2032 640 1552 352 1552 352 1376 junction
w 272 1378 100 0 n#15 inhier.PAUSE.P 144 1376 448 1376 elongouts.disable.SLNK
w 192 1954 100 0 n#36 inhier.END.P 176 1952 256 1952 efanouts.endFan.SLNK
w 768 1714 100 0 n#33 inhier.AIRMASS.P 208 1712 1376 1712 1376 1552 2048 1552 ecalcs.amSum.INPB
w 354 984 100 0 n#16 efanouts.beginFan.FLNK 448 768 512 768 512 864 352 864 352 1056 junction
w 272 1058 100 0 n#16 inhier.CONTINUE.P 144 1056 448 1056 elongouts.enable.SLNK
w 152 658 100 0 n#31 inhier.BEGIN.P 144 656 208 656 efanouts.beginFan.SLNK
w 936 642 100 0 n#28 eaos.initAmSum.FLNK 1072 800 1184 800 1184 640 736 640 736 512 816 512 eaos.initCounter.SLNK
w 552 738 100 0 n#26 efanouts.beginFan.LNK1 448 736 704 736 704 768 816 768 eaos.initAmSum.SLNK
w 776 546 100 0 n#25 hwin.hwin#23.in 784 544 816 544 eaos.initCounter.DOL
w 776 802 100 0 n#24 hwin.hwin#22.in 784 800 816 800 eaos.initAmSum.DOL
w 834 1152 100 0 n#12 elongouts.enable.OUT 704 1024 832 1024 832 1232 junction
w 880 1234 100 0 n#12 elongouts.disable.OUT 704 1344 832 1344 832 1232 976 1232 elongouts.fanDisable.SLNK
w 392 1410 100 0 n#11 hwin.hwin#10.in 384 1408 448 1408 elongouts.disable.DOL
w 398 1090 100 0 n#8 hwin.hwin#7.in 384 1088 448 1088 elongouts.enable.DOL
w 1294 1234 100 0 n#4 elongouts.fanDisable.VAL 1232 1232 1392 1232 efanouts.fan.SDIS
s 1136 2336 200 0 Compute average airmass during an observation
s 2784 192 100 0 Gemini Telescope Control System
s 2528 2384 100 0 $Id: tcsMeanAirmass.sch,v 1.1.1.1 1998/11/08 00:20:38 epics Exp $
s 1248 2272 100 0 The BEGIN link initialises the airmass sum and counter and
s 1248 2240 100 0 then enables the 1 Hz loop that integrates the airmass during
s 1248 2208 100 0 the observation. The END link disables the 1 Hz integrator
s 1248 2176 100 0 and computes the mean airmass by dividing the integral by
s 1248 2144 100 0 the number of samples. The PAUSE and CONTINUE links stop
s 1248 2112 100 0 and start the integrator respectively.
[cell use]
use outhier 3160 1288 100 0 FLNK
xform 0 3152 1328
use outhier 3160 1000 100 0 AMMEAN
xform 0 3152 1040
use ecalcs 2808 920 100 0 amMean
xform 0 2928 1184
p 2832 878 100 0 1 CALC:B=0?0.0:A/B
p 2768 1454 100 0 -1 DESC:Compute mean airmass
p 2896 912 100 1024 0 name:$(top)$(I)
use ecalcs 2072 408 100 0 counter
xform 0 2192 672
p 2144 606 100 0 1 CALC:A+1
p 2032 942 100 0 -1 DESC:Increment counter
p 2160 400 100 1024 0 name:$(top)$(I)
use ecalcs 2072 1112 100 0 amSum
xform 0 2192 1376
p 2144 1310 100 0 1 CALC:A+B
p 2032 1646 100 0 -1 DESC:Integrate airmass
p 2160 1104 100 1024 0 name:$(top)$(I)
use inhier 184 1912 100 0 END
xform 0 176 1952
use inhier 216 1672 100 0 AIRMASS
xform 0 208 1712
use inhier 152 616 100 0 BEGIN
xform 0 144 656
use inhier 152 1016 100 0 CONTINUE
xform 0 144 1056
use inhier 152 1336 100 0 PAUSE
xform 0 144 1376
use efanouts 280 1816 100 0 endFan
xform 0 376 1968
p 336 1934 100 0 0 DISV:1
p 336 2142 100 0 0 SCAN:Passive
p 112 1934 100 0 0 SELM:All
p 368 1808 100 1024 0 name:$(top)$(I)
use efanouts 232 520 100 0 beginFan
xform 0 328 672
p 288 638 100 0 0 DISV:1
p 288 846 100 0 0 SCAN:Passive
p 320 512 100 1024 0 name:$(top)$(I)
use efanouts 1416 1064 100 0 fan
xform 0 1512 1216
p 1472 1182 100 0 1 DISV:0
p 1472 1390 100 0 1 SCAN:1 second
p 1504 1056 100 1024 0 name:$(top)$(I)
use hwin 616 504 100 0 hwin#23
xform 0 688 544
p 595 536 100 0 -1 val(in):0
use hwin 616 760 100 0 hwin#22
xform 0 688 800
p 595 792 100 0 -1 val(in):0.0
use hwin 216 1368 100 0 hwin#10
xform 0 288 1408
p 195 1400 100 0 -1 val(in):0
use hwin 216 1048 100 0 hwin#7
xform 0 288 1088
p 195 1080 100 0 -1 val(in):1
use eaos 840 424 100 0 initCounter
xform 0 944 512
p 832 606 100 0 -1 DESC:Initial counter value
p 784 238 100 0 0 EGU:none
p 560 494 100 0 0 OMSL:closed_loop
p 928 416 100 1024 0 name:$(top)$(I)
p 1072 480 75 768 -1 pproc(OUT):PP
use eaos 840 680 100 0 initAmSum
xform 0 944 768
p 832 862 100 0 -1 DESC:Initial airmass sum
p 784 494 100 0 0 EGU:none
p 560 750 100 0 0 OMSL:closed_loop
p 928 672 100 1024 0 name:$(top)$(I)
p 1072 736 75 768 -1 pproc(OUT):PP
use elongouts 472 1288 100 0 disable
xform 0 576 1376
p 432 1470 100 0 -1 DESC:Disable airmass calculation
p 288 1294 100 0 0 OMSL:closed_loop
p 560 1280 100 1024 0 name:$(top)$(I)
p 704 1344 75 768 -1 pproc(OUT):PP
use elongouts 472 968 100 0 enable
xform 0 576 1056
p 432 1150 100 0 -1 DESC:Enable airmass calculation
p 288 974 100 0 0 OMSL:closed_loop
p 560 960 100 1024 0 name:$(top)$(I)
p 704 1024 75 768 -1 pproc(OUT):PP
use elongouts 1000 1144 100 0 fanDisable
xform 0 1104 1232
p 880 1342 100 0 -1 DESC:Disable flag for mean airmass calc
p 1088 1136 100 1024 0 name:$(top)$(I)
use bc200tr -48 -88 -100 0 frame
xform 0 1632 1216
[comments]
