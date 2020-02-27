[schematic2]
uniq 33
[tools]
[detail]
w 2008 651 100 0 n#32 inhier.SLNK.P 1808 624 1952 624 1952 640 2112 640 egenSubD.loadCoeffs.SLNK
w 2552 619 100 0 n#31 egenSubD.loadCoeffs.FLNK 2400 608 2752 608 outhier.FLNK.p
w 1936 715 100 0 INDEX inhier.INDEX.P 1808 704 2112 704 egenSubD.loadCoeffs.INPU
w 1728 939 100 0 n#28 eais.Z19.VAL 992 64 1392 64 1392 928 2112 928 egenSubD.loadCoeffs.INPN
w 896 203 100 0 n#27 eais.Z18.VAL 480 192 1360 192 1360 960 2112 960 egenSubD.loadCoeffs.INPM
w 1696 1003 100 0 n#26 eais.Z17.VAL 992 320 1328 320 1328 992 2112 992 egenSubD.loadCoeffs.INPL
w 864 427 100 0 n#25 eais.Z16.VAL 480 416 1296 416 1296 1024 2112 1024 egenSubD.loadCoeffs.INPK
w 1664 1067 100 0 n#24 eais.Z15.VAL 992 576 1264 576 1264 1056 2112 1056 egenSubD.loadCoeffs.INPJ
w 1648 1099 100 0 n#23 eais.Z14.VAL 480 672 1232 672 1232 1088 2112 1088 egenSubD.loadCoeffs.INPI
w 1632 1131 100 0 n#22 eais.Z13.VAL 992 800 1200 800 1200 1120 2112 1120 egenSubD.loadCoeffs.INPH
w 1624 1163 100 0 n#21 eais.Z12.VAL 480 928 1184 928 1184 1152 2112 1152 egenSubD.loadCoeffs.INPG
w 1616 1195 100 0 n#20 eais.Z11.VAL 992 1056 1168 1056 1168 1184 2112 1184 egenSubD.loadCoeffs.INPF
w 1608 1227 100 0 n#19 eais.Z10.VAL 480 1184 1152 1184 1152 1216 2112 1216 egenSubD.loadCoeffs.INPE
w 1776 1259 100 0 n#18 eais.Z9.VAL 992 1312 1488 1312 1488 1248 2112 1248 egenSubD.loadCoeffs.INPD
w 968 1451 100 0 n#17 eais.Z8.VAL 480 1440 1504 1440 1504 1280 2112 1280 egenSubD.loadCoeffs.INPC
w 1792 1323 100 0 n#16 eais.Z5.VAL 992 1568 1520 1568 1520 1312 2112 1312 egenSubD.loadCoeffs.INPB
w 984 1707 100 0 n#15 eais.Z4.VAL 480 1696 1536 1696 1536 1344 2112 1344 egenSubD.loadCoeffs.INPA
s 2480 -112 100 0 Gemini Telescope Control
s 2496 -176 100 0 Load M1 model coefficients
s 1056 1920 100 0 This schematic loads the coefficients of the models
s 1056 1888 100 0 that describe the zernike corrections as a function of elevation
[cell use]
use inhier 1792 663 100 0 INDEX
xform 0 1808 704
use inhier 1792 583 100 0 SLNK
xform 0 1808 624
use outhier 2720 567 100 0 FLNK
xform 0 2736 608
use eais 224 1639 100 0 Z4
xform 0 352 1712
p 13 1785 100 0 0 DESC:Coefficient of Zernike model
p -32 1454 100 0 0 EGU:microns
p -32 1550 100 0 0 PREC:2
use eais 224 1383 100 0 Z8
xform 0 352 1456
p 13 1529 100 0 0 DESC:Coefficient of Zernike model
p -32 1198 100 0 0 EGU:microns
p -32 1294 100 0 0 PREC:2
use eais 224 615 100 0 Z14
xform 0 352 688
p 13 761 100 0 0 DESC:Coefficient of Zernike model
p -32 430 100 0 0 EGU:microns
p -32 526 100 0 0 PREC:2
use eais 736 1255 100 0 Z9
xform 0 864 1328
p 525 1401 100 0 0 DESC:Coefficient of Zernike model
p 480 1070 100 0 0 EGU:microns
p 480 1166 100 0 0 PREC:2
use eais 224 1127 100 0 Z10
xform 0 352 1200
p 13 1273 100 0 0 DESC:Coefficient of Zernike model
p -32 942 100 0 0 EGU:microns
p -32 1038 100 0 0 PREC:2
use eais 736 999 100 0 Z11
xform 0 864 1072
p 525 1145 100 0 0 DESC:Coefficient of Zernike model
p 480 814 100 0 0 EGU:microns
p 480 910 100 0 0 PREC:2
use eais 224 871 100 0 Z12
xform 0 352 944
p 13 1017 100 0 0 DESC:Coefficient of Zernike model
p -32 686 100 0 0 EGU:microns
p -32 782 100 0 0 PREC:2
use eais 736 1511 100 0 Z5
xform 0 864 1584
p 525 1657 100 0 0 DESC:Coefficient of Zernike model
p 480 1326 100 0 0 EGU:microns
p 480 1422 100 0 0 PREC:2
use eais 224 135 100 0 Z18
xform 0 352 208
p 13 281 100 0 0 DESC:Coefficient of Zernike model
p -32 -50 100 0 0 EGU:microns
p -32 46 100 0 0 PREC:2
use eais 224 359 100 0 Z16
xform 0 352 432
p 13 505 100 0 0 DESC:Coefficient of Zernike model
p -32 174 100 0 0 EGU:microns
p -32 270 100 0 0 PREC:2
use eais 736 743 100 0 Z13
xform 0 864 816
p 525 889 100 0 0 DESC:Coefficient of Zernike model
p 480 558 100 0 0 EGU:microns
p 480 654 100 0 0 PREC:2
use eais 736 519 100 0 Z15
xform 0 864 592
p 525 665 100 0 0 DESC:Coefficient of Zernike model
p 480 334 100 0 0 EGU:microns
p 480 430 100 0 0 PREC:2
use eais 736 263 100 0 Z17
xform 0 864 336
p 525 409 100 0 0 DESC:Coefficient of Zernike model
p 480 78 100 0 0 EGU:microns
p 480 174 100 0 0 PREC:2
use eais 736 7 100 0 Z19
xform 0 864 80
p 525 153 100 0 0 DESC:Coefficient of Zernike model
p 480 -178 100 0 0 EGU:microns
p 480 -82 100 0 0 PREC:2
use egenSubD 2112 551 100 0 loadCoeffs
xform 0 2256 976
p 1955 1291 100 0 0 DESC:Load coefficients of M1 figure model
p 2192 704 100 0 1 FTU:DOUBLE
p 2176 496 100 0 1 SNAM:$(snam)
use bc200tr -352 -392 -100 0 frame
xform 0 1328 912
[comments]
