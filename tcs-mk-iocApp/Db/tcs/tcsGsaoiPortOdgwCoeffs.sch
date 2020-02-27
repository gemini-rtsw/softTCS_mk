[schematic2]
uniq 14
[tools]
[detail]
w 1130 1458 100 0 n#1 hwin.hwin#64.in 1120 1448 1184 1448 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#61.Window
w 1114 1050 100 0 n#2 hwin.hwin#73.in 1104 1040 1168 1040 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#71.Window
w 1114 738 100 0 n#3 hwin.hwin#83.in 1104 728 1168 728 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#81.Window
w 1106 378 100 0 n#4 hwin.hwin#93.in 1096 368 1160 368 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#91.Window
w 1130 1498 100 0 n#5 hwin.hwin#94.in 1120 1488 1136 1488 1136 1472 1152 1472 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#61.Port
w 1114 1090 100 0 n#6 hwin.hwin#111.in 1104 1080 1112 1080 1112 1064 1136 1064 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#71.Port
w 1114 778 100 0 n#7 hwin.hwin#115.in 1104 768 1120 768 1120 752 1136 752 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#81.Port
w 1106 418 100 0 n#8 hwin.hwin#119.in 1096 408 1104 408 1104 392 1128 392 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#91.Port
w 210 850 100 0 n#9 inhier.SLNK.P 200 840 336 840 efanouts.gsaoiOdgwFan.SLNK
w 586 930 100 0 n#10 efanouts.gsaoiOdgwFan.LNK1 576 920 840 920 840 1544 1096 1544 1096 1512 1184 1512 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#61.SLNK
w 586 898 100 0 n#11 efanouts.gsaoiOdgwFan.LNK2 576 888 888 888 888 1128 1088 1128 1088 1104 1168 1104 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#71.SLNK
w 586 866 100 0 n#12 efanouts.gsaoiOdgwFan.LNK3 576 856 872 856 872 824 1088 824 1088 792 1168 792 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#81.SLNK
w 586 834 100 0 n#13 efanouts.gsaoiOdgwFan.LNK4 576 824 864 824 864 440 1112 440 1112 432 1160 432 tcsGsaoiOdgwCoeffs.tcsGsaoiOdgwCoeffs#91.SLNK
s 1968 2160 100 0 $Id: tcsGsaoiPortOdgwCoeffs.sch,v 1.1 2010/06/08 14:57:58 cjm Exp $
s 1984 -32 100 0 Copyright
s 1984 -64 100 0 Observatory
s 1984 -96 100 0 Sciences Ltd.
s 464 1976 200 0 Fetch ODGW Coeffs for all windows with GSAOI on a specific Port
[cell use]
use bc200tr -608 -312 -100 0 frame
xform 0 1072 992
use tcsGsaoiOdgwCoeffs 1120 1416 100 0 tcsGsaoiOdgwCoeffs#61
xform 0 1280 1480
use hwin 928 1432 100 0 hwin#64
xform 0 1024 1448
p 931 1440 100 0 -1 val(in):0
use tcsGsaoiOdgwCoeffs 1104 1008 100 0 tcsGsaoiOdgwCoeffs#71
xform 0 1264 1072
p 1255 1153 100 0 1 seta:odgw odgw2
use hwin 912 1024 100 0 hwin#73
xform 0 1008 1040
p 915 1032 100 0 -1 val(in):1
use tcsGsaoiOdgwCoeffs 1104 696 100 0 tcsGsaoiOdgwCoeffs#81
xform 0 1264 760
p 1255 841 100 0 1 seta:odgw odgw3
use hwin 912 712 100 0 hwin#83
xform 0 1008 728
p 915 720 100 0 -1 val(in):2
use tcsGsaoiOdgwCoeffs 1096 336 100 0 tcsGsaoiOdgwCoeffs#91
xform 0 1256 400
p 1247 481 100 0 1 seta:odgw odgw4
use hwin 904 352 100 0 hwin#93
xform 0 1000 368
p 907 360 100 0 -1 val(in):3
use hwin 928 1472 100 0 hwin#94
xform 0 1024 1488
p 931 1480 100 0 -1 val(in):$(gsaoiport)
use hwin 912 1064 100 0 hwin#111
xform 0 1008 1080
p 915 1072 100 0 -1 val(in):$(gsaoiport)
use hwin 912 752 100 0 hwin#115
xform 0 1008 768
p 915 760 100 0 -1 val(in):$(gsaoiport)
use hwin 904 392 100 0 hwin#119
xform 0 1000 408
p 907 400 100 0 -1 val(in):$(gsaoiport)
use efanouts 336 728 100 0 gsaoiOdgwFan
xform 0 456 856
p 448 696 100 1024 0 name:$(top)p$(gsaoiport):$(I)
use inhier 181 797 100 0 SLNK
xform 0 200 840
[comments]
