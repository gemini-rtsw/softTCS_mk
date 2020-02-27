[schematic2]
uniq 81
[tools]
[detail]
w -64 1515 100 0 n#80 inhier.SLNK.P -176 1504 96 1504 tcsVtDifTrack.tcsVtDifTrack#53.SLNK
w 768 331 100 0 n#79 tcsVtDifTrack.tcsVtDifTrack#71.FLNK 1440 512 1536 512 1536 320 48 320 48 0 96 0 tcsVtDifTrack.tcsVtDifTrack#74.SLNK
w 760 811 100 0 n#78 tcsVtDifTrack.tcsVtDifTrack#63.FLNK 1440 1024 1536 1024 1536 800 32 800 32 512 96 512 tcsVtDifTrack.tcsVtDifTrack#68.SLNK
w 752 1323 100 0 n#77 tcsVtDifTrack.tcsVtDifTrack#57.FLNK 1440 1504 1520 1504 1520 1312 32 1312 32 1024 96 1024 tcsVtDifTrack.tcsVtDifTrack#60.SLNK
w 744 523 100 0 n#76 tcsVtDifTrack.tcsVtDifTrack#68.FLNK 448 512 1088 512 tcsVtDifTrack.tcsVtDifTrack#71.SLNK
w 24 139 100 0 n#73 hwin.hwin#75.in 0 128 96 128 tcsVtDifTrack.tcsVtDifTrack#74.VT
w 1016 651 100 0 n#70 hwin.hwin#72.in 992 640 1088 640 tcsVtDifTrack.tcsVtDifTrack#71.VT
w 24 651 100 0 n#67 hwin.hwin#69.in 0 640 96 640 tcsVtDifTrack.tcsVtDifTrack#68.VT
w 744 1035 100 0 n#66 tcsVtDifTrack.tcsVtDifTrack#60.FLNK 448 1024 1088 1024 tcsVtDifTrack.tcsVtDifTrack#63.SLNK
w 744 1515 100 0 n#65 tcsVtDifTrack.tcsVtDifTrack#53.FLNK 448 1504 1088 1504 tcsVtDifTrack.tcsVtDifTrack#57.SLNK
w 1016 1163 100 0 n#62 hwin.hwin#64.in 992 1152 1088 1152 tcsVtDifTrack.tcsVtDifTrack#63.VT
w 24 1163 100 0 n#59 hwin.hwin#61.in 0 1152 96 1152 tcsVtDifTrack.tcsVtDifTrack#60.VT
w 1016 1643 100 0 n#56 hwin.hwin#58.in 992 1632 1088 1632 tcsVtDifTrack.tcsVtDifTrack#57.VT
w 24 1643 100 0 n#55 hwin.hwin#54.in 0 1632 96 1632 tcsVtDifTrack.tcsVtDifTrack#53.VT
s 1792 2000 100 0 $Id: tcsUpdateDifTrack.sch,v 1.1 2004/08/05 09:54:19 cjm Exp $
s 1808 -336 100 0 4 August 2004
s 1808 -304 100 0 C. J. Mayer
s 2032 -192 100 0 Gemini Telescope Control System
s 1792 -192 100 0 Copyright
s 1792 -224 100 0 Observatory
s 1792 -256 100 0 Sciences Ltd.
[cell use]
use inhier -192 1463 100 0 SLNK
xform 0 -176 1504
use hwin -192 1591 100 0 hwin#54
xform 0 -96 1632
p -189 1624 100 0 -1 val(in):0
use hwin 800 1591 100 0 hwin#58
xform 0 896 1632
p 803 1624 100 0 -1 val(in):1
use hwin -192 1111 100 0 hwin#61
xform 0 -96 1152
p -189 1144 100 0 -1 val(in):2
use hwin 800 1111 100 0 hwin#64
xform 0 896 1152
p 803 1144 100 0 -1 val(in):3
use hwin -192 599 100 0 hwin#69
xform 0 -96 640
p -189 632 100 0 -1 val(in):4
use hwin 800 599 100 0 hwin#72
xform 0 896 640
p 803 632 100 0 -1 val(in):5
use hwin -192 87 100 0 hwin#75
xform 0 -96 128
p -189 120 100 0 -1 val(in):6
use tcsVtDifTrack 96 1447 100 0 tcsVtDifTrack#53
xform 0 272 1568
p 116 1420 100 0 1 seta:vt mount
use tcsVtDifTrack 1088 1447 100 0 tcsVtDifTrack#57
xform 0 1264 1568
p 1108 1420 100 0 1 seta:vt sourceA
use tcsVtDifTrack 96 967 100 0 tcsVtDifTrack#60
xform 0 272 1088
p 116 940 100 0 1 seta:vt sourceB
use tcsVtDifTrack 1088 967 100 0 tcsVtDifTrack#63
xform 0 1264 1088
p 1108 940 100 0 1 seta:vt sourceC
use tcsVtDifTrack 96 455 100 0 tcsVtDifTrack#68
xform 0 272 576
p 116 428 100 0 1 seta:vt pwfs1
use tcsVtDifTrack 1088 455 100 0 tcsVtDifTrack#71
xform 0 1264 576
p 1108 428 100 0 1 seta:vt pwfs2
use tcsVtDifTrack 96 -57 100 0 tcsVtDifTrack#74
xform 0 272 64
p 116 -84 100 0 1 seta:vt oiwfs
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
[comments]
