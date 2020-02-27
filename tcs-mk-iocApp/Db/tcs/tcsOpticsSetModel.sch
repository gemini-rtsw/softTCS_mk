[schematic2]
uniq 36
[tools]
[detail]
w 1176 1035 100 0 n#35 eais.ast45P3.VAL 672 256 960 256 960 1024 1440 1024 egenSubD.setModel.INPN
w 600 427 100 0 n#34 eais.ast45A3.VAL 224 256 320 256 320 416 928 416 928 1056 1440 1056 egenSubD.setModel.INPM
w 1144 1099 100 0 n#33 eais.ast45P2.VAL 672 512 896 512 896 1088 1440 1088 egenSubD.setModel.INPL
w 1128 1131 100 0 n#32 eais.ast45A2.VAL 224 512 320 512 320 704 864 704 864 1120 1440 1120 egenSubD.setModel.INPK
w 1112 1163 100 0 n#27 eais.ast0P3.VAL 672 832 832 832 832 1152 1440 1152 egenSubD.setModel.INPJ
w 1096 1195 100 0 n#26 eais.ast0A3.VAL 224 832 320 832 320 992 800 992 800 1184 1440 1184 egenSubD.setModel.INPI
w 1080 1227 100 0 n#25 eais.ast0P2.VAL 672 1088 768 1088 768 1216 1440 1216 egenSubD.setModel.INPH
w 856 1259 100 0 n#24 eais.ast0A2.VAL 224 1088 320 1088 320 1248 1440 1248 egenSubD.setModel.INPG
w 1288 1291 100 0 n#19 eais.ast45Phase.VAL 1120 1568 1184 1568 1184 1280 1440 1280 egenSubD.setModel.INPF
w 1064 1323 100 0 n#18 eais.ast45Scale.VAL 704 1568 736 1568 736 1312 1440 1312 egenSubD.setModel.INPE
w 840 1355 100 0 n#17 eais.ast45Zero.VAL 256 1568 288 1568 288 1344 1440 1344 egenSubD.setModel.INPD
w 1304 1387 100 0 n#16 eais.ast0Phase.VAL 1120 1792 1216 1792 1216 1376 1440 1376 egenSubD.setModel.INPC
w 1080 1419 100 0 n#15 eais.ast0Scale.VAL 704 1792 768 1792 768 1408 1440 1408 egenSubD.setModel.INPB
w 856 1451 100 0 n#14 eais.ast0Zero.VAL 256 1808 320 1808 320 1440 1440 1440 egenSubD.setModel.INPA
s 2288 -80 100 0 Set model coefficients
s 2016 -80 100 0 Sciences Ltd.
s 2016 -48 100 0 Observatory
s 2016 -16 100 0 Copyright
s 2032 2176 100 0 $Id: tcsOpticsSetModel.sch,v 1.2 2001/04/06 16:20:58 cjm Exp $
[cell use]
use eais 416 199 100 0 ast45P3
xform 0 544 272
p 416 368 100 0 -1 DESC:P3 phase for 45 astig
p 160 14 100 0 0 EGU:degs
p 160 78 100 0 0 EGUF:360.0
p 160 46 100 0 0 EGUL:-360.0
p 160 110 100 0 0 PREC:2
use eais -32 199 100 0 ast45A3
xform 0 96 272
p -32 368 100 0 -1 DESC:A3 coefficient for 45 astig
p -288 14 100 0 0 EGU:microns
p -288 110 100 0 0 PREC:2
use eais 416 455 100 0 ast45P2
xform 0 544 528
p 416 624 100 0 -1 DESC:P2 phase for 45 astig
p 160 270 100 0 0 EGU:degs
p 160 334 100 0 0 EGUF:360.0
p 160 302 100 0 0 EGUL:-360.0
p 160 366 100 0 0 PREC:2
use eais -32 455 100 0 ast45A2
xform 0 96 528
p -32 624 100 0 -1 DESC:A2 coefficient for 45 astig
p -288 270 100 0 0 EGU:microns
p -288 366 100 0 0 PREC:2
use eais 416 775 100 0 ast0P3
xform 0 544 848
p 416 944 100 0 -1 DESC:P3 phase for 0 astig
p 160 590 100 0 0 EGU:degs
p 160 654 100 0 0 EGUF:360.0
p 160 622 100 0 0 EGUL:-360.0
p 160 686 100 0 0 PREC:2
use eais -32 775 100 0 ast0A3
xform 0 96 848
p -32 944 100 0 -1 DESC:A3 coefficient for 0 astig
p -288 590 100 0 0 EGU:microns
p -288 686 100 0 0 PREC:2
use eais 416 1031 100 0 ast0P2
xform 0 544 1104
p 416 1200 100 0 -1 DESC:P2 phase for 0 astig
p 160 846 100 0 0 EGU:degs
p 160 910 100 0 0 EGUF:360.0
p 160 878 100 0 0 EGUL:-360.0
p 160 942 100 0 0 PREC:2
use eais -32 1031 100 0 ast0A2
xform 0 96 1104
p -32 1200 100 0 -1 DESC:A2 coefficient for 0 astig
p -288 846 100 0 0 EGU:microns
p -288 942 100 0 0 PREC:2
use eais 0 1751 100 0 ast0Zero
xform 0 128 1824
p 0 1920 100 0 -1 DESC:Zero point for 0 astig
p -256 1566 100 0 0 EGU:microns
p -256 1662 100 0 0 PREC:2
use eais 448 1735 100 0 ast0Scale
xform 0 576 1808
p 448 1904 100 0 -1 DESC:Scale factor for 0 astig
p 192 1550 100 0 0 EGU:units
p 192 1646 100 0 0 PREC:2
use eais 864 1735 100 0 ast0Phase
xform 0 992 1808
p 864 1904 100 0 -1 DESC:Phase for 0 astig
p 608 1550 100 0 0 EGU:degs
p 608 1614 100 0 0 EGUF:360.0
p 608 1582 100 0 0 EGUL:-360.0
p 608 1646 100 0 0 PREC:2
use eais 0 1511 100 0 ast45Zero
xform 0 128 1584
p 0 1680 100 0 -1 DESC:Zero point for 45 astig
p -256 1326 100 0 0 EGU:microns
p -256 1422 100 0 0 PREC:2
use eais 448 1511 100 0 ast45Scale
xform 0 576 1584
p 448 1680 100 0 -1 DESC:Scale factor for 45 astig
p 192 1326 100 0 0 EGU:units
p 192 1422 100 0 0 PREC:2
use eais 864 1511 100 0 ast45Phase
xform 0 992 1584
p 864 1680 100 0 -1 DESC:Phase for 45 astig
p 608 1326 100 0 0 EGU:degs
p 608 1390 100 0 0 EGUF:360.0
p 608 1358 100 0 0 EGUL:-360.0
p 608 1422 100 0 0 PREC:2
use egenSubD 1440 647 100 0 setModel
xform 0 1584 1072
p 1472 1504 100 0 -1 DESC:Update model parameters
p 1152 1182 100 0 0 DISS:NO_ALARM
p 1472 560 100 0 1 SNAM:tcsOpticsCheckAoModel
use bc200tr -560 -296 -100 0 frame
xform 0 1120 1008
[comments]
