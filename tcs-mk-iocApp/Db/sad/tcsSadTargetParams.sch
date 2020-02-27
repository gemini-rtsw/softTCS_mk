[schematic2]
uniq 24
[tools]
[detail]
s 1328 2064 100 0 the thirteen virtual telescopes.
s 1328 2096 100 0 This schematic defines the SAD parameters for each of the 
s 1280 2208 300 0 Target SAD Parameters
s 2640 2384 100 0 tcsSadTargetParams.sch
s 2816 128 100 0 SAD Target Parameters
s 2752 192 100 0 Gemini Telescope Control System
[cell use]
use tcsSadNodChopParams 2496 487 100 0 tcsSadNodChopParams#23
xform 0 2720 624
p 2528 448 100 0 1 seta:probe g4
use tcsSadNodChopParams 1776 487 100 0 tcsSadNodChopParams#22
xform 0 2000 624
p 1796 460 100 0 1 seta:probe g3
use tcsSadNodChopParams 992 487 100 0 tcsSadNodChopParams#21
xform 0 1216 624
p 1012 460 100 0 1 seta:probe g2
use tcsSadNodChopParams 224 487 100 0 tcsSadNodChopParams#20
xform 0 448 624
p 244 460 100 0 1 seta:probe g1
use tcsSadNodChopParams 1776 151 100 0 tcsSadNodChopParams#15
xform 0 2000 288
p 1796 124 100 0 1 seta:probe oiwfs
use tcsSadNodChopParams 992 151 100 0 tcsSadNodChopParams#14
xform 0 1216 288
p 1012 124 100 0 1 seta:probe pwfs2
use tcsSadNodChopParams 224 151 100 0 tcsSadNodChopParams#13
xform 0 448 288
p 244 124 100 0 1 seta:probe pwfs1
use tcsSadSourceParams 2552 1240 100 0 tcsSadSourceParams#12
xform 0 2800 1408
p 2736 1390 100 0 1 seta:vt mount
use tcsSadSourceParams 248 1656 100 0 tcsSadSourceParams#0
xform 0 496 1824
p 432 1806 100 0 1 seta:vt sourceA
use tcsSadSourceParams 1016 1656 100 0 tcsSadSourceParams#1
xform 0 1264 1824
p 1168 1806 100 0 1 seta:vt sourceB
use tcsSadSourceParams 1816 1656 100 0 tcsSadSourceParams#2
xform 0 2064 1824
p 1984 1822 100 0 1 seta:vt sourceC
use tcsSadSourceParams 264 1224 100 0 tcsSadSourceParams#3
xform 0 512 1392
p 432 1374 100 0 1 seta:vt pwfs1
use tcsSadSourceParams 1032 1224 100 0 tcsSadSourceParams#4
xform 0 1280 1392
p 1200 1374 100 0 1 seta:vt pwfs2
use tcsSadSourceParams 1832 1240 100 0 tcsSadSourceParams#5
xform 0 2080 1408
p 2016 1390 100 0 1 seta:vt oiwfs
use tcsSadSourceParams 264 808 100 0 tcsSadSourceParams#16
xform 0 512 976
p 432 958 100 0 1 seta:vt g1
use tcsSadSourceParams 1032 808 100 0 tcsSadSourceParams#17
xform 0 1280 976
p 1200 958 100 0 1 seta:vt g2
use tcsSadSourceParams 1832 808 100 0 tcsSadSourceParams#18
xform 0 2080 976
p 2000 958 100 0 1 seta:vt g3
use tcsSadSourceParams 2552 808 100 0 tcsSadSourceParams#19
xform 0 2800 976
p 2720 958 100 0 1 seta:vt g4
use bc200tr -80 -88 -100 0 frame
xform 0 1600 1216
[comments]
