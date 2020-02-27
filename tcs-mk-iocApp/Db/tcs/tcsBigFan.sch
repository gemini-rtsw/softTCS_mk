[schematic2]
uniq 32
[tools]
[detail]
w 1208 123 100 0 n#31 efanouts.fan2.LNK6 896 448 1088 448 1088 112 1376 112 outhier.LNK12.p
w 1224 251 100 0 n#30 efanouts.fan2.LNK5 896 480 1120 480 1120 240 1376 240 outhier.LNK11.p
w 1288 347 100 0 n#27 efanouts.fan2.LNK4 896 512 1152 512 1152 336 1472 336 outhier.LNK10.p
w 1016 555 100 0 n#26 efanouts.fan2.LNK3 896 544 1184 544 1184 432 1472 432 outhier.LNK9.p
w 1032 578 100 0 n#25 efanouts.fan2.LNK2 896 576 1216 576 1216 528 1472 528 outhier.LNK8.p
w 1032 610 100 0 n#24 efanouts.fan2.LNK1 896 608 1216 608 1216 656 1472 656 outhier.LNK7.p
w 1048 866 100 0 n#23 efanouts.fan1.LNK6 896 864 1248 864 1248 784 1472 784 outhier.LNK6.p
w 1160 898 100 0 n#22 efanouts.fan1.LNK5 896 896 1472 896 outhier.LNK5.p
w 1048 930 100 0 n#21 efanouts.fan1.LNK4 896 928 1248 928 1248 1008 1472 1008 outhier.LNK4.p
w 1032 962 100 0 n#20 efanouts.fan1.LNK3 896 960 1216 960 1216 1136 1472 1136 outhier.LNK3.p
w 1016 994 100 0 n#19 efanouts.fan1.LNK2 896 992 1184 992 1184 1232 1472 1232 outhier.LNK2.p
w 1288 1330 100 0 n#18 efanouts.fan1.LNK1 896 1024 1152 1024 1152 1328 1472 1328 outhier.LNK1.p
w -56 795 100 0 n#17 inhier.SLNK.P -80 784 16 784 efanouts.fan0.SLNK
w 546 698 100 0 n#4 efanouts.fan0.LNK2 256 832 544 832 544 528 656 528 efanouts.fan2.SLNK
w 382 866 100 0 n#3 efanouts.fan0.LNK1 256 864 544 864 544 944 656 944 efanouts.fan1.SLNK
s 1776 128 100 0 Gemini Telescope Control System
s 1536 1360 100 0 $Id: tcsBigFan.sch,v 1.2 2007/12/18 10:53:33 cjm Exp $
[cell use]
use outhier 1368 72 100 0 LNK12
xform 0 1360 112
use outhier 1344 199 100 0 LNK11
xform 0 1360 240
use outhier 1464 1288 100 0 LNK1
xform 0 1456 1328
use outhier 1464 296 100 0 LNK10
xform 0 1456 336
use outhier 1464 392 100 0 LNK9
xform 0 1456 432
use outhier 1464 488 100 0 LNK8
xform 0 1456 528
use outhier 1464 616 100 0 LNK7
xform 0 1456 656
use outhier 1464 744 100 0 LNK6
xform 0 1456 784
use outhier 1464 856 100 0 LNK5
xform 0 1456 896
use outhier 1464 968 100 0 LNK4
xform 0 1456 1008
use outhier 1464 1096 100 0 LNK3
xform 0 1456 1136
use outhier 1464 1192 100 0 LNK2
xform 0 1456 1232
use inhier -72 744 100 0 SLNK
xform 0 -80 784
use efanouts 680 392 100 0 fan2
xform 0 776 544
p 720 734 100 0 -1 DESC:Top level fanout record
use efanouts 680 808 100 0 fan1
xform 0 776 960
p 720 1150 100 0 -1 DESC:Top level fanout record
use efanouts 40 648 100 0 fan0
xform 0 136 800
p 80 990 100 0 -1 DESC:Top level fanout record
use bb200tr -240 -152 -100 0 frame
xform 0 1040 672
[comments]
