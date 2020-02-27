[schematic2]
uniq 30
[tools]
[detail]
w -392 -53 100 0 n#29 eaos.elCurrentVel.VAL -576 -64 -160 -64 -160 672 32 672 egenSub.timeStampedPos.INPE
w -408 251 100 0 n#28 eaos.elCurrentPos.VAL -576 240 -192 240 -192 736 32 736 egenSub.timeStampedPos.INPD
w -440 1131 100 0 n#27 eaos.azcapturedTime.VAL -576 1120 -256 1120 -256 928 32 928 egenSub.timeStampedPos.INPA
w 520 235 100 0 FLNK egenSub.timeStampedPos.FLNK 320 224 768 224 outhier.FLNK.p
w 520 971 100 0 c#24 egenSub.timeStampedPos.VALA 320 960 768 960 outhier.c#24.p
w -424 555 100 0 n#21 eaos.azCurrentVel.VAL -576 544 -224 544 -224 800 32 800 egenSub.timeStampedPos.INPC
w -440 843 100 0 n#20 eaos.azCurrentPos.VAL -576 832 -256 832 -256 864 32 864 egenSub.timeStampedPos.INPB
w -344 -21 100 0 n#17 eaos.elCurrentVel.FLNK -576 -32 -64 -32 -64 256 32 256 egenSub.timeStampedPos.SLNK
w -712 91 100 0 n#15 eaos.elCurrentPos.FLNK -576 272 -480 272 -480 80 -896 80 -896 -64 -832 -64 eaos.elCurrentVel.SLNK
w -712 395 100 0 n#14 eaos.azCurrentVel.FLNK -576 576 -480 576 -480 384 -896 384 -896 240 -832 240 eaos.elCurrentPos.SLNK
w -712 699 100 0 n#13 eaos.azCurrentPos.FLNK -576 864 -480 864 -480 688 -896 688 -896 544 -832 544 eaos.azCurrentVel.SLNK
w -712 987 100 0 n#12 eaos.azcapturedTime.FLNK -576 1152 -480 1152 -480 976 -896 976 -896 832 -832 832 eaos.azCurrentPos.SLNK
w -1120 -325 100 0 SLNK inhier.SLNK.P -1264 -336 -928 -336 -928 1120 -832 1120 eaos.azcapturedTime.SLNK
w -1072 -21 100 0 ELVEL inhier.ELVEL.P -1264 -32 -832 -32 eaos.elCurrentVel.DOL
w -1066 283 100 0 EL inhier.EL.P -1264 272 -832 272 eaos.elCurrentPos.DOL
w -1066 587 100 0 AZVEL inhier.AZVEL.P -1264 576 -832 576 eaos.azCurrentVel.DOL
w -1066 875 100 0 AZ inhier.AZ.P -1264 864 -832 864 eaos.azCurrentPos.DOL
w -1066 1163 100 0 TIME inhier.TIME.P -1264 1152 -832 1152 eaos.azcapturedTime.DOL
s 1312 -816 100 0 Mount time stamped positions
s 1296 -752 100 0 Gemini Telescope Control System
s 1056 1440 100 0 IId$
[cell use]
use outhier 736 919 100 0 c#24
xform 0 752 960
use outhier 736 183 100 0 FLNK
xform 0 752 224
use eaos -832 1031 100 0 azcapturedTime
xform 0 -704 1120
p -768 1216 100 0 -1 DESC:Time stamp
p -864 846 100 0 0 EGU:secs
p -1088 1102 100 0 0 OMSL:closed_loop
p -1088 974 100 0 0 PREC:14
p -720 1024 100 1024 0 name:$(mc)$(I)
use eaos -832 743 100 0 azCurrentPos
xform 0 -704 832
p -768 928 100 0 -1 DESC:Current azimuth
p -864 558 100 0 0 EGU:degs
p -1088 814 100 0 0 OMSL:closed_loop
p -1088 686 100 0 0 PREC:14
p -720 736 100 1024 0 name:$(mc)$(I)
use eaos -832 151 100 0 elCurrentPos
xform 0 -704 240
p -768 336 100 0 -1 DESC:Current elevation
p -864 -34 100 0 0 EGU:degs
p -1088 222 100 0 0 OMSL:closed_loop
p -1088 94 100 0 0 PREC:14
p -720 144 100 1024 0 name:$(mc)$(I)
use eaos -832 -153 100 0 elCurrentVel
xform 0 -704 -64
p -768 32 100 0 -1 DESC:Current elevation velocity
p -864 -338 100 0 0 EGU:degs/s
p -1088 -82 100 0 0 OMSL:closed_loop
p -1088 -210 100 0 0 PREC:14
p -720 -160 100 1024 0 name:$(mc)$(I)
use eaos -832 455 100 0 azCurrentVel
xform 0 -704 544
p -768 640 100 0 -1 DESC:Current azimuth velocity
p -864 270 100 0 0 EGU:degs/s
p -1088 526 100 0 0 OMSL:closed_loop
p -1088 398 100 0 0 PREC:14
p -720 448 100 1024 0 name:$(mc)$(I)
use inhier -1280 1111 100 0 TIME
xform 0 -1264 1152
use inhier -1280 823 100 0 AZ
xform 0 -1264 864
use inhier -1280 535 100 0 AZVEL
xform 0 -1264 576
use inhier -1280 231 100 0 EL
xform 0 -1264 272
use inhier -1280 -73 100 0 ELVEL
xform 0 -1264 -32
use inhier -1280 -377 100 0 SLNK
xform 0 -1264 -336
use bc200tr -1536 -1032 -100 0 frame
xform 0 144 272
use egenSub 32 167 100 0 timeStampedPos
xform 0 176 592
p 48 1008 100 0 -1 DESC:Time stamped positions
p 176 944 100 0 1 NOVA:6
p -256 718 100 0 0 PREC:14
p 320 144 100 0 1 SNAM:tcsMcsTimeStampedPos
p -240 944 100 0 0 def(INPA):0.0
p -256 766 100 0 0 def(INPB):0.000000000000000e+00
p 144 160 100 1024 0 name:$(mc)$(I)
[comments]
