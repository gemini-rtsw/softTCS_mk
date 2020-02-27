[schematic2]
uniq 18
[tools]
[detail]
w 3288 5771 100 0 n#17 inhier.c#16.P 2944 5760 3680 5760 egenSub.test.INPC
w 3288 5835 100 0 n#15 inhier.c#14.P 2944 5824 3680 5824 egenSub.test.INPB
w 3592 5899 100 0 n#13 hwin.hwin#12.in 3552 5888 3680 5888 egenSub.test.INPA
w 3520 5227 100 0 n#11 inhier.SLNK.P 3408 5216 3680 5216 egenSub.test.SLNK
w 4200 5931 100 0 n#10 egenSub.test.VALA 3968 5920 4480 5920 4480 5760 4672 5760 ecalcs.filt.INPA
w 4446 5643 100 0 n#9 inhier.INPE.P 4256 5632 4672 5632 ecalcs.filt.INPE
w 4486 5675 100 0 n#8 inhier.INPD.P 4336 5664 4672 5664 ecalcs.filt.INPD
w 4446 5707 100 0 n#7 inhier.INPC.P 4256 5696 4672 5696 ecalcs.filt.INPC
w 4486 5739 100 0 n#5 inhier.INPB.P 4336 5728 4672 5728 ecalcs.filt.INPB
w 4126 5195 100 0 n#4 egenSub.test.FLNK 3968 5184 4320 5184 4320 5376 4672 5376 ecalcs.filt.SLNK
w 5166 5467 100 0 n#3 ecalcs.filt.VAL 4960 5568 5088 5568 5088 5456 5280 5456 outhier.VAL.p
w 5166 5723 100 0 n#2 ecalcs.filt.FLNK 4960 5600 5088 5600 5088 5712 5280 5712 outhier.FLNK.p
s 5216 6848 100 0 $Id: tcsMountOffLoad.sch,v 1.1 2002/05/21 21:33:43 cjm Exp $
s 5216 4624 100 0 Observatory
s 5216 4592 100 0 Sciences Ltd.
s 5216 4656 100 0 Copyright
s 5456 4656 100 0 Gemini Telescope Control System
s 5456 4592 100 0 Compute mount offload
s 4032 6720 200 0 Compute Mount Offloads
[cell use]
use inhier 3392 5175 100 0 SLNK
xform 0 3408 5216
use inhier 4240 5591 100 0 INPE
xform 0 4256 5632
use inhier 4368 5680 100 0 INPD
xform 0 4336 5664
use inhier 4240 5655 100 0 INPC
xform 0 4256 5696
use inhier 4368 5744 100 0 INPB
xform 0 4336 5728
use inhier 2928 5783 100 0 c#14
xform 0 2944 5824
use inhier 2928 5719 100 0 c#16
xform 0 2944 5760
use hwin 3360 5847 100 0 hwin#12
xform 0 3456 5888
p 3363 5880 100 0 -1 val(in):$(index)
use outhier 5248 5671 100 0 FLNK
xform 0 5264 5712
use outhier 5248 5415 100 0 VAL
xform 0 5264 5456
use ecalcs 4672 5287 100 0 filt
xform 0 4816 5552
p 4579 5768 100 0 0 CALC:$(calc)
p 4608 5824 100 0 -1 DESC:Calculate collimation adjustment
p 4384 5406 100 0 0 PREC:14
p 4800 5424 100 1024 0 name:$(top)$(coll)$(I)
use egenSub 3680 5127 100 0 test
xform 0 3824 5552
p 3680 5984 100 0 -1 DESC:Test if SCS data has changed
p 3457 4901 100 0 0 FTA:LONG
p 3392 5678 100 0 0 PREC:14
p 3744 5056 100 0 1 SNAM:tcsTestOffLoad
p 2992 5840 100 0 -1 def(INPB):$(m2)xTiltGuide
p 2992 5776 100 0 -1 def(INPC):$(m2)yTiltGuide
p 3792 5120 100 1024 0 name:$(top)$(coll)$(I)
p 3664 5834 75 0 -1 palrm(INPB):MS
p 3664 5770 75 0 -1 palrm(INPC):MS
p 3632 5834 75 0 -1 pproc(INPB):CA
p 3632 5770 75 0 -1 pproc(INPC):CA
use bc200tr 2640 4376 -100 0 frame
xform 0 4320 5680
[comments]
