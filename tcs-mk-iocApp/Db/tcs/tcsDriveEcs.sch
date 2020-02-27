[schematic2]
uniq 29
[tools]
[detail]
w 4492 539 100 0 n#1 efanouts.moveFan.LNK2 4400 528 4656 528 4656 672 4848 672 tcsDriveShtrs.tcsDriveShtrs#1531.SLNK
w 4628 883 100 0 n#2 efanouts.moveFan.LNK1 4400 560 4624 560 4624 1216 4848 1216 tcsDriveDome.tcsDriveDome#1526.SLNK
w 3276 1643 100 0 ELLIMIT inhier.ELLIMIT.P 2976 1632 3648 1632 3648 1184 3792 1184 egenSub.driveECS.INPA
w 3404 379 100 0 SLNK inhier.SLNK.P 3184 368 3696 368 3696 512 3792 512 egenSub.driveECS.SLNK
w 4268 898 100 0 n#3 egenSub.driveECS.VALF 4080 896 4528 896 4528 736 4848 736 tcsDriveShtrs.tcsDriveShtrs#1531.BOT
w 4284 962 100 0 n#4 egenSub.driveECS.VALE 4080 960 4560 960 4560 800 4848 800 tcsDriveShtrs.tcsDriveShtrs#1531.TOP
w 4300 1026 100 0 n#5 egenSub.driveECS.VALD 4080 1024 4592 1024 4592 608 4848 608 tcsDriveShtrs.tcsDriveShtrs#1531.SDIS
w 4300 1090 100 0 n#6 egenSub.driveECS.VALC 4080 1088 4592 1088 4592 1280 4848 1280 tcsDriveDome.tcsDriveDome#1526.DOL
w 4428 1154 100 0 n#7 egenSub.driveECS.VALB 4080 1152 4848 1152 tcsDriveDome.tcsDriveDome#1526.SDIS
w 5458 -52 100 0 n#8 ecalcs.westVentGatePos.FLNK 5856 576 5888 576 5888 176 5456 176 5456 -352 5568 -352 ecalcs.eastVentGatePos.SLNK
w 5458 636 100 0 n#9 eais.botShtrErr.FLNK 5856 992 5888 992 5888 848 5456 848 5456 352 5568 352 ecalcs.westVentGatePos.SLNK
w 5684 1106 100 0 n#10 eais.topShtrErr.FLNK 5856 1216 5888 1216 5888 1104 5552 1104 5552 976 5600 976 eais.botShtrErr.SLNK
w 5684 1330 100 0 n#11 eais.domeErr.FLNK 5856 1440 5888 1440 5888 1328 5552 1328 5552 1200 5600 1200 eais.topShtrErr.SLNK
w 3420 674 100 0 n#12 eais.botShtrPos.VAL 3312 672 3600 672 3600 928 3792 928 egenSub.driveECS.INPE
w 3396 866 100 0 n#13 eais.topShtrPos.VAL 3296 864 3568 864 3568 992 3792 992 egenSub.driveECS.INPD
w 3420 1090 100 0 n#14 eais.domePos.VAL 3296 1088 3616 1088 3616 1056 3792 1056 egenSub.driveECS.INPC
w 3618 1316 100 0 n#15 tcsDeg2rad.tcsDeg2rad#1492.VAL 3456 1440 3616 1440 3616 1120 3792 1120 egenSub.driveECS.INPB
w 2884 722 100 0 n#16 inhier.c#1452.P 2784 720 3056 720 eais.botShtrPos.INP
w 2876 914 100 0 n#17 inhier.c#1450.P 2784 912 3040 912 eais.topShtrPos.INP
w 2876 1138 100 0 n#18 inhier.c#1449.P 2784 1136 3040 1136 eais.domePos.INP
w 3372 578 100 0 n#19 inhier.c#1480.P 3184 576 3632 576 3632 864 3792 864 egenSub.driveECS.INPF
w 3388 498 100 0 n#20 inhier.c#1481.P 3184 496 3664 496 3664 800 3792 800 egenSub.driveECS.INPG
w 4018 108 100 0 n#21 egenSub.driveECS.OUTJ 4080 608 4448 608 4448 336 4016 336 4016 -192 4160 -192 eaos.timeToDomeLimit.SLNK
w 4034 -44 100 0 n#22 egenSub.driveECS.OUTI 4080 672 4464 672 4464 320 4032 320 4032 -480 4160 -480 ebos.domeLimitValid.SLNK
w 4482 548 100 0 n#23 egenSub.driveECS.OUTH 4080 736 4480 736 4480 288 4064 288 4064 128 4160 128 eaos.domeVignette.SLNK
w 4498 588 100 0 n#24 egenSub.driveECS.OUTG 4080 800 4496 800 4496 304 4048 304 4048 -16 4128 -16 outhier.c#1488.p
w 4780 1618 100 0 n#25 egenSub.driveECS.OUTA 4080 1184 4560 1184 4560 1616 5072 1616 outhier.c#1405.p
w 3132 1442 100 0 n#26 eaos.moveTol.VAL 3120 1440 3216 1440 tcsDeg2rad.tcsDeg2rad#1492.INP
w 3132 1474 100 0 n#27 eaos.moveTol.FLNK 3120 1472 3216 1472 tcsDeg2rad.tcsDeg2rad#1492.SLNK
w 4084 482 100 0 n#28 egenSub.driveECS.FLNK 4080 480 4160 480 efanouts.moveFan.SLNK
s 5440 -496 100 0 Gemini Telescope Control System
s 5216 1696 100 0 $Id: tcsDriveEcs.sch,v 1.4 2014/09/18 15:10:11 cjm Exp $
s 3728 1536 100 0 Note that driveECS always outputs a stream of demands. These
s 3728 1504 100 0 will only be acted on however if the ECS is in following mode.
s 3728 1472 100 0 The record trigger additional downstream processing if the
s 3728 1440 100 0 outputs on VALB or VALD are not equal to 1. This happens
s 3744 1408 100 0 when the algorithms in tcsDriveECS compute that a move
s 3728 1376 100 0 command is needed for either the dome or shutters.
s 4880 1392 100 0 We normally expect this symbol
s 4880 1360 100 0 to be disabled
s 4880 928 100 0 We normally expect this symbol
s 4880 896 100 0 to be disabled
[cell use]
use bc200tr 2640 -776 -100 0 frame
xform 0 4320 528
use tcsDriveShtrs 4872 584 100 0 tcsDriveShtrs#1531
xform 0 5008 720
use tcsDriveDome 4872 1064 100 0 tcsDriveDome#1526
xform 0 5008 1200
use tcsEcsThermalMode 3064 -632 100 0 tcsEcsThermalMode#1525
xform 0 3200 -528
use ecalcs 5592 -440 100 0 eastVentGatePos
xform 0 5712 -176
p 5651 -130 100 0 1 CALC:A/100.0
p 5568 94 100 0 -1 DESC:East vent gate position
p 5280 -290 100 0 0 EGU:fraction
p 5280 -450 100 0 0 MDEL:0.005
p 5280 -322 100 0 0 PREC:2
p 5376 62 100 0 -1 def(INPA):$(ec)eastVentGatePos
p 5680 -448 100 1024 0 name:$(tcs)$(I)
use ecalcs 5592 264 100 0 westVentGatePos
xform 0 5712 528
p 5651 574 100 0 1 CALC:A/100.0
p 5568 798 100 0 -1 DESC:West vent gate position
p 5280 414 100 0 0 EGU:fraction
p 5280 254 100 0 0 MDEL:0.005
p 5280 382 100 0 0 PREC:2
p 5376 766 100 0 -1 def(INPA):$(ec)westVentGatePos
p 5680 256 100 1024 0 name:$(tcs)$(I)
use eais 5624 904 100 0 botShtrErr
xform 0 5728 976
p 5600 1054 100 0 -1 DESC:Bottom shutter position error
p 5344 718 100 0 0 EGU:degrees
p 5344 494 100 0 0 MDEL:0.05
p 5344 814 100 0 0 PREC:1
p 5344 974 100 0 0 SCAN:Passive
p 5376 1038 100 0 -1 def(INP):$(ec)botShtrErr
p 5712 896 100 1024 0 name:$(tcs)$(I)
use eais 5624 1128 100 0 topShtrErr
xform 0 5728 1200
p 5600 1278 100 0 -1 DESC:Top shutter position error
p 5344 942 100 0 0 EGU:degrees
p 5344 718 100 0 0 MDEL:0.05
p 5344 1038 100 0 0 PREC:1
p 5344 1198 100 0 0 SCAN:Passive
p 5376 1262 100 0 -1 def(INP):$(ec)topShtrErr
p 5712 1120 100 1024 0 name:$(tcs)$(I)
use eais 5624 1352 100 0 domeErr
xform 0 5728 1424
p 5600 1502 100 0 -1 DESC:Dome position error
p 5344 1166 100 0 0 EGU:degrees
p 5344 942 100 0 0 MDEL:0.05
p 5344 1262 100 0 0 PREC:1
p 5344 1422 100 0 0 SCAN:1 second
p 5376 1486 100 0 -1 def(INP):$(ec)domeErr
p 5712 1344 100 1024 0 name:$(tcs)$(I)
use eais 3064 1032 100 0 domePos
xform 0 3168 1104
p 3040 1182 100 0 -1 DESC:Current dome position
p 2784 846 100 0 0 EGU:degrees
p 2784 622 100 0 0 MDEL:0.05
p 2784 942 100 0 0 PREC:1
p 2816 1166 100 0 -1 def(INP):$(ec)domePos
p 3152 1024 100 1024 0 name:$(tcs)$(I)
use eais 3064 808 100 0 topShtrPos
xform 0 3168 880
p 3040 958 100 0 -1 DESC:Top shutter position
p 2784 622 100 0 0 EGU:degrees
p 2784 398 100 0 0 MDEL:0.05
p 2784 718 100 0 0 PREC:1
p 2816 942 100 0 -1 def(INP):$(ec)topShtrPos
p 3152 800 100 1024 0 name:$(tcs)$(I)
use eais 3080 616 100 0 botShtrPos
xform 0 3184 688
p 3120 750 100 0 -1 DESC:Current bottom shutter position
p 2800 430 100 0 0 EGU:degrees
p 2800 206 100 0 0 MDEL:0.05
p 2800 526 100 0 0 PREC:1
p 2832 750 100 0 -1 def(INP):$(ec)botShtrPos
p 3168 608 100 1024 0 name:$(tcs)$(I)
use ebos 4184 -568 100 0 domeLimitValid
xform 0 4288 -480
p 4160 -386 100 0 -1 DESC:Flag for dome limit validity
p 4176 -642 100 0 1 ONAM:Valid
p 4176 -610 100 0 1 ZNAM:Invalid
p 4416 -512 75 768 -1 pproc(OUT):NPP
use eaos 4184 40 100 0 domeVignette
xform 0 4288 128
p 4176 222 100 0 -1 DESC:Dome vignette fraction
p 4128 -146 100 0 0 EGU:None
p 4128 14 100 0 0 HHSV:MINOR
p 4128 142 100 0 0 HIHI:1.01
p 3904 -434 100 0 0 MDEL:0.005
p 3904 -18 100 0 0 PREC:2
p 4496 94 100 0 -1 def(OUT):$(sad)domeVignette
p 4272 32 100 1024 0 name:$(tcs)$(I)
p 4448 96 75 768 -1 palrm(OUT):MS
p 4416 96 75 768 -1 pproc(OUT):PP
p 4128 78 100 0 0 HIGH:0.0000001
p 4128 -18 100 0 0 HSV:MINOR
use eaos 2888 1352 100 0 moveTol
xform 0 2992 1440
p 2784 1534 100 0 -1 DESC:Tolerance for moves in BASIC mode
p 2768 1230 100 0 1 DRVH:2.0
p 2928 1230 100 0 1 DRVL:0.1
p 3088 1294 100 0 1 EGU:degrees
p 2768 1294 100 0 1 EGUF:2.0
p 2768 1262 100 0 1 EGUL:0.1
p 2928 1294 100 0 1 HOPR:2.0
p 2928 1262 100 0 1 LOPR:0.1
p 2608 1294 100 0 0 PREC:2
p 2976 1344 100 1024 0 name:$(top)$(I)
use eaos 4184 -280 100 0 timeToDomeLimit
xform 0 4288 -192
p 4176 -98 100 0 -1 DESC:Time to next enclosure move
p 4400 -274 100 0 1 EGU:Seconds
p 4128 -306 100 0 0 HHSV:NO_ALARM
p 4128 -242 100 0 0 HIGH:86400.0
p 4128 -178 100 0 0 HIHI:86400.0
p 4336 -322 100 0 1 LLSV:MAJOR
p 4192 -322 100 0 1 LOLO:10.0
p 4192 -354 100 0 1 LOW:30.0
p 4336 -354 100 0 1 LSV:MINOR
p 3904 -754 100 0 0 MDEL:0.05
p 3904 -338 100 0 0 PREC:1
p 4496 -226 100 0 -1 def(OUT):$(sad)timeToDomeLimit
p 4272 -288 100 1024 0 name:$(tcs)$(I)
p 4448 -224 75 768 -1 palrm(OUT):MS
p 4416 -224 75 768 -1 pproc(OUT):PP
use tcsDeg2rad 3216 1351 100 0 tcsDeg2rad#1492
xform 0 3336 1432
p 3232 1520 100 0 -1 seta:top $(top)moveTol:
use outhier 4120 -56 100 0 c#1488
xform 0 4112 -16
use outhier 5064 1576 100 0 c#1405
xform 0 5056 1616
use inhier 3192 456 100 0 c#1481
xform 0 3184 496
use inhier 3192 536 100 0 c#1480
xform 0 3184 576
use inhier 2792 680 100 0 c#1452
xform 0 2784 720
use inhier 2792 872 100 0 c#1450
xform 0 2784 912
use inhier 2792 1096 100 0 c#1449
xform 0 2784 1136
use inhier 3192 328 100 0 SLNK
xform 0 3184 368
use inhier 2984 1592 100 0 ELLIMIT
xform 0 2976 1632
use efanouts 4184 344 100 0 moveFan
xform 0 4280 496
p 4272 336 100 1024 0 name:$(top)$(I)
use egenSub 3816 424 100 0 driveECS
xform 0 3936 848
p 3504 990 100 0 0 DISV:1
p 3952 1134 100 0 -1 FTVB:LONG
p 3952 1022 100 0 -1 FTVD:LONG
p 3952 670 100 0 -1 FTVI:LONG
p 4448 1230 100 0 -1 NOVA:6
p 3504 974 100 0 0 PREC:14
p 3872 622 100 0 -1 SNAM:tcsDriveECS
p 3280 1182 100 0 0 def(INPC):0.0
p 3264 1102 100 0 0 def(INPD):0.0
p 3264 1022 100 0 0 def(INPE):0.0
p 3296 590 100 0 -1 def(INPF):$(mc)azCurrentPos
p 3264 510 100 0 -1 def(INPG):$(mc)elCurrentPos
p 4208 1230 100 0 -1 def(OUTA):$(ec)followA.F
p 4176 -18 100 0 -1 def(OUTG):$(tcs)domeVignette.HIHI
p 3904 416 100 1024 0 name:$(top)$(I)
p 3744 1066 75 0 -1 pproc(INPC):PP
p 3744 1002 75 0 -1 pproc(INPD):PP
p 3744 938 75 0 -1 pproc(INPE):PP
p 3744 618 75 0 -1 pproc(INPJ):NPP
p 4080 810 75 0 -1 pproc(OUTG):PP
p 4080 682 75 0 -1 pproc(OUTI):PP
p 4080 618 75 0 -1 pproc(OUTJ):PP
[comments]
