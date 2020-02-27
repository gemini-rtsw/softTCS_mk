[schematic2]
uniq 270
[tools]
[detail]
w 1570 -85 100 0 n#269 elongouts.measuring.VAL 1728 96 1856 96 1856 -96 1344 -96 1344 -928 1824 -928 egenSub.ttf.INPJ
w 1594 -341 100 0 n#268 inhier.c#265.P 1424 -352 1824 -352 egenSub.ttf.INPA
s 3664 -1888 100 0 GPOL subsystem simulator
s 3632 -1808 100 0 Gemini Telescope Control System
s 3392 384 100 0 $Id: nici.sch,v 1.2 2006/04/25 14:02:47 cjm Exp $
s 1376 320 100 0 This record is only used by the sky 
s 1376 288 100 0 simulator. It does not need to exist in
s 1376 256 100 0 the real NICI.
[cell use]
use inhier 1408 -393 100 0 c#265
xform 0 1424 -352
use egenSub 1824 -1113 100 0 ttf
xform 0 1968 -688
p 1920 -272 100 0 -1 DESC:WFS data
p 1601 -1595 100 0 0 FTJ:LONG
p 1920 -336 100 0 1 NOA:8
p 1952 -896 100 0 1 NOVJ:8
p 1536 -562 100 0 0 PREC:8
p 1904 -1200 100 0 1 SCAN:1 second
p 1904 -1136 100 0 1 SNAM:tcsNiciTtf
p 1504 -304 100 0 -1 def(INPA):$(tcs)sky:simulate.VALF
p 1936 -1120 100 1024 0 name:$(top)dc:$(I)
use elongouts 1472 7 100 0 measuring
xform 0 1600 96
p 1440 192 100 0 -1 DESC:Shows if NICI is integrating
use bc200tr 800 -2088 -100 0 frame
xform 0 2480 -784
[comments]
