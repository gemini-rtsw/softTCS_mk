[schematic2]
uniq 66
[tools]
[detail]
w 536 1083 100 0 n#65 efanouts.prepFan.LNK1 480 656 528 656 528 1072 592 1072 elongins.matId.SLNK
w 408 1115 100 0 n#64 ecad8.ecad8#44.VALA 112 816 272 816 272 1104 592 1104 elongins.matId.INP
w 400 443 100 0 n#62 efanouts.prepFan.LNK3 480 592 592 592 592 432 256 432 256 -48 576 -48 eseqs.CV.SLNK
w 784 603 100 0 n#61 efanouts.prepFan.LNK2 480 624 672 624 672 592 944 592 eseqs.prepWait.SLNK
w 128 123 100 0 n#58 ecad8.ecad8#44.SPLK 112 112 192 112 192 144 junction
w 128 155 100 0 n#58 ecad8.ecad8#44.STLK 112 144 192 144 192 576 240 576 efanouts.prepFan.SLNK
w 1400 930 100 0 n#45 eseqs.prepWait.LNK1 1264 912 1296 912 1296 928 1552 928 ecars.prepareCm_BUSY.IVAL
w 1312 882 100 0 n#45 eseqs.prepWait.LNK2 1264 880 1408 880 1408 928 junction
w 880 882 100 0 n#52 hwin.hwin#55.in 864 864 864 880 944 880 eseqs.prepWait.DOL2
w 920 914 100 0 n#51 eseqs.prepWait.DOL1 944 912 944 912 hwin.hwin#56.in
w 1536 290 100 0 n#42 ecars.ecars#14.VAL 1504 288 1616 288 outhier.VAL.p
w 1536 66 100 0 n#40 ecars.ecars#14.FLNK 1504 64 1616 64 outhier.FLNK.p
w 944 242 100 0 n#26 eseqs.CV.LNK2 896 240 1040 240 1040 288 junction
w 1032 290 100 0 n#26 eseqs.CV.LNK1 896 272 928 272 928 288 1184 288 ecars.ecars#14.IVAL
w 512 242 100 0 n#25 hwin.hwin#24.in 496 224 496 240 576 240 eseqs.CV.DOL2
w 552 274 100 0 n#23 hwin.hwin#22.in 576 272 576 272 eseqs.CV.DOL1
s 1520 -128 100 0 specified as parameter
s 1472 -96 100 0 Generate simulated CAD8 with delay
s 1216 1184 100 0 $Id: aoPrepareCmCad.sch,v 1.2 2010/01/29 12:01:59 ajf Exp $
s 240 208 100 0 IDLE
s 320 256 100 0 BUSY
s 1488 -48 100 0 Gemini Telescope Control System
s 608 848 100 0 IDLE
s 688 896 100 0 BUSY
[cell use]
use elongins 592 999 100 0 matId
xform 0 720 1072
p 720 1056 100 1024 0 name:$(prefix)$(I)
use efanouts 240 439 100 0 prepFan
xform 0 360 592
p 352 432 100 1024 0 name:$(prefix)$(I)
use hwin 328 184 100 0 hwin#24
xform 0 400 224
p 318 152 100 0 0 typ(in):val
p 307 216 100 0 -1 val(in):$(CAR_IDLE)
use hwin 408 232 100 0 hwin#22
xform 0 480 272
p 398 200 100 0 0 typ(in):val
p 387 264 100 0 -1 val(in):$(CAR_BUSY)
use hwin 696 824 100 0 hwin#55
xform 0 768 864
p 686 792 100 0 0 typ(in):val
p 675 856 100 0 -1 val(in):$(CAR_IDLE)
use hwin 776 872 100 0 hwin#56
xform 0 848 912
p 766 840 100 0 0 typ(in):val
p 755 904 100 0 -1 val(in):$(CAR_BUSY)
use eseqs 600 -136 100 0 CV
xform 0 736 112
p 672 78 100 0 0 DLY1:0.0e+00
p 656 158 100 0 1 DLY2:$(delay)
p 608 -162 100 0 1 PV:$(prefix)$(cadname)
p 912 270 100 0 0 def(LNK1):0.0
p 576 304 75 1280 -1 palrm(SELL):NMS
p 544 272 75 1280 -1 pproc(DOL1):NPP
p 544 240 75 1280 -1 pproc(DOL2):NPP
p 896 282 75 0 -1 pproc(LNK1):PP
p 896 250 75 0 -1 pproc(LNK2):PP
use eseqs 968 504 100 0 prepWait
xform 0 1104 752
p 1040 718 100 0 0 DLY1:0.0e+00
p 1024 798 100 0 1 DLY2:5.0
p 1280 910 100 0 0 def(LNK1):0.0
p 1056 496 100 1024 0 name:$(prefix)$(I)
p 944 944 75 1280 -1 palrm(SELL):NMS
p 912 912 75 1280 -1 pproc(DOL1):NPP
p 912 880 75 1280 -1 pproc(DOL2):NPP
p 1264 922 75 0 -1 pproc(LNK1):PP
p 1264 890 75 0 -1 pproc(LNK2):PP
use ecars 1208 8 100 0 ecars#14
xform 0 1344 176
p 1184 -2 100 0 1 name:$(prefix)$(cadname)C
use ecars 1576 648 100 0 prepareCm_BUSY
xform 0 1712 816
p 1552 638 100 0 0 name:$(prefix)$(I)
use outhier 1608 24 100 0 FLNK
xform 0 1600 64
use outhier 1608 248 100 0 VAL
xform 0 1600 288
use ecad8 -184 56 100 0 ecad8#44
xform 0 -48 560
p -112 752 100 0 0 FTVA:$(ftva)
p -112 720 100 0 0 FTVB:$(ftvb)
p -112 688 100 0 0 FTVC:$(ftvc)
p -112 656 100 0 0 FTVD:$(ftvd)
p -112 624 100 0 0 FTVE:$(ftve)
p -240 16 100 0 1 SNAM:tcs$(substring)$(cadname)CAD
p -96 48 100 1024 1 name:$(prefix)$(cadname)
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
[comments]
