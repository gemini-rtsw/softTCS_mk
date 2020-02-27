[schematic2]
uniq 1292
[tools]
[detail]
w 5948 3403 100 0 FLNK esubs.initsource.FLNK 5824 3392 6144 3392 outhier.FLNK.p
w 4832 3155 100 0 SLNK inhier.SLNK.P 4576 3152 5136 3152 5136 3168 5536 3168 esubs.initsource.SLNK
w 5420 3987 100 0 n#1129 tcsDeg2rad.tcsDeg2rad#1290.VAL 5104 4464 5424 4464 5424 3520 5536 3520 esubs.initsource.INPB
w 5452 4107 100 0 n#1265 tcsDeg2rad.tcsDeg2rad#1289.VAL 5120 4672 5456 4672 5456 3552 5536 3552 esubs.initsource.INPA
w 4804 4674 100 0 n#1179 eais.initaz.VAL 4800 4672 4880 4672 tcsDeg2rad.tcsDeg2rad#1289.INP
w 4788 4466 100 0 n#1182 eais.initel.VAL 4784 4464 4864 4464 tcsDeg2rad.tcsDeg2rad#1290.INP
w 5388 3859 100 0 n#1258 tcsDeg2rad.tcsDeg2rad#1291.VAL 5104 4240 5392 4240 5392 3488 5536 3488 esubs.initsource.INPC
w 4788 4243 100 0 n#1260 eais.initrma.VAL 4784 4240 4864 4240 tcsDeg2rad.tcsDeg2rad#1291.INP
s 5744 4880 100 0 $Id: tcsInitSource.sch,v 1.1.1.1 1998/11/08 00:20:37 epics Exp $
[cell use]
use tcsDeg2rad 4864 4151 100 0 tcsDeg2rad#1291
xform 0 4984 4232
p 4880 4320 100 0 -1 seta:top $(top)initrma:
use tcsDeg2rad 4864 4375 100 0 tcsDeg2rad#1290
xform 0 4984 4456
p 4880 4544 100 0 -1 seta:top $(top)initel:
use tcsDeg2rad 4880 4583 100 0 tcsDeg2rad#1289
xform 0 5000 4664
p 4896 4752 100 0 -1 seta:top $(top)initaz:
use eais 4568 4616 100 0 initaz
xform 0 4672 4688
p 4472 4770 100 0 0 primitive:eai
use eais 4552 4408 100 0 initel
xform 0 4656 4480
use eais 4528 4183 100 0 initrma
xform 0 4656 4256
p 4317 4329 100 0 0 DESC:Default rotator PA
p 4272 3998 100 0 0 EGU:degrees
p 4272 4062 100 0 0 EGUF:270.0
p 4272 4030 100 0 0 EGUL:-270.0
p 4496 4190 100 0 0 HIGH:270.0
p 4496 4254 100 0 0 HIHI:270.0
p 4272 3966 100 0 0 HOPR:270.0
p 4496 4222 100 0 0 LOLO:-270.0
p 4272 3934 100 0 0 LOPR:-270.0
p 4496 4158 100 0 0 LOW:-270.0
p 4272 4094 100 0 0 PREC:3
use outhier 6112 3351 100 0 FLNK
xform 0 6128 3392
use inhier 4560 3111 100 0 SLNK
xform 0 4576 3152
use eborderC 3088 2407 100 0 tcsInitSource
xform 0 4768 3712
p 5728 2576 100 768 -1 author:D.L.Terrett
p 5648 2528 100 768 -1 date:1997/04/28
p 5888 2608 200 768 -1 file:tcsInitSource
use esubs 5560 3080 100 0 initsource
xform 0 5680 3344
p 5248 3198 100 0 0 INAM:tcsNullInit
p 5600 3294 100 0 -1 SNAM:tcsInitSource
p 5504 3552 75 1280 -1 pproc(INPA):PP
p 5504 3520 75 1280 -1 pproc(INPB):PP
p 5504 3488 75 1280 -1 pproc(INPC):PP
[comments]
