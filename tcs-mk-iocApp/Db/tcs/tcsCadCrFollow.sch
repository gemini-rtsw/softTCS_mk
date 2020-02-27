[schematic2]
uniq 57
[tools]
[detail]
w 1168 1163 100 0 n#55 junction 1120 1280 1120 1152 1264 1152 ecalcs.calc.INPA
w 1672 1291 100 0 n#55 ecad8.follow.VALA 912 1280 2480 1280 tcsStopFollow.tcsStopFollow#8.Action
w 2224 1227 100 0 n#56 efanouts.fan.FLNK 1936 992 2016 992 2016 1216 2480 1216 tcsStopFollow.tcsStopFollow#8.Slnk
w 2000 971 100 0 n#54 efanouts.fan.LNK1 1936 960 2112 960 estringouts.crBrake.SLNK
w 1632 891 100 0 n#53 ecalcs.calc.FLNK 1552 992 1616 992 1616 880 1696 880 efanouts.fan.SLNK
w 1624 971 100 0 n#52 ecalcs.calc.VAL 1552 960 1744 960 efanouts.fan.SELL
w 992 619 100 0 n#51 ecad8.follow.STLK 912 608 1120 608 1120 768 1264 768 ecalcs.calc.SLNK
w 1016 1451 100 0 n#45 ecad8.follow.MESS 912 1440 1168 1440 1168 1392 1360 1392 outhier.MESS.p
w 1112 1483 100 0 n#44 ecad8.follow.VAL 912 1472 1360 1472 outhier.VAL.p
w 216 1394 100 0 n#24 inhier.ICID.P -16 1392 496 1392 496 1440 592 1440 ecad8.follow.ICID
w 264 1474 100 0 n#23 inhier.DIR.P -16 1472 592 1472 ecad8.follow.DIR
s 960 1920 100 0 specifies whether the brakes should be applied when a stop command is given.
s 960 1952 100 0 command due to its stop command having a parameter. The parameter
s 960 1984 100 0 The Cass Rotator requires a special schematic to implement the follow
s 2288 2112 100 0 $Id: tcsCadCrFollow.sch,v 1.1 2000/01/30 00:01:02 cjm Exp $
s 2592 -144 100 0 Cass rotator follow Command
s 2512 -80 100 0 Gemini Telescope Control System
[cell use]
use estringouts 2112 887 100 0 crBrake
xform 0 2240 960
p 2139 1000 100 0 0 DESC:Brake string
p 2048 926 100 0 0 VAL:YES
p 2464 944 100 0 -1 def(OUT):$(cr)stop.B
p 2224 880 100 1024 0 name:$(tcs)$(cad):$(I)
use efanouts 1696 743 100 0 fan
xform 0 1816 896
p 1552 862 100 0 0 SELM:Specified
p 1808 736 100 1024 0 name:$(tcs)$(cad):$(I)
use ecalcs 1264 679 100 0 calc
xform 0 1408 944
p 1360 864 100 0 1 CALC:A?0:1
p 1360 800 100 1024 0 name:$(tcs)$(cad):$(I)
use bc200tr -288 -360 -100 0 frame
xform 0 1392 944
use tcsStopFollow 2504 1128 100 0 tcsStopFollow#8
xform 0 2560 1232
use outhier 1352 1352 100 0 MESS
xform 0 1344 1392
use outhier 1352 1432 100 0 VAL
xform 0 1344 1472
use inhier -8 1352 100 0 ICID
xform 0 -16 1392
use inhier -8 1432 100 0 DIR
xform 0 -16 1472
use ecad8 616 520 -100 0 follow
xform 0 752 1024
p 688 1672 100 0 0 FTVA:DOUBLE
p 688 1640 100 0 0 FTVB:DOUBLE
p 688 1608 100 0 0 FTVC:DOUBLE
p 688 1576 100 0 0 FTVD:DOUBLE
p 688 1544 100 0 0 FTVE:DOUBLE
p 688 1512 100 0 0 FTVF:DOUBLE
p 688 1480 100 0 0 FTVG:DOUBLE
p 688 1448 100 0 0 FTVH:DOUBLE
p 688 1960 100 0 0 SNAM:$(snam)
p 688 -3224 100 0 0 def(SPLK):0.0
p 688 776 100 0 0 def(STLK):0.0
p 688 494 100 0 -1 name:$(tcs)$(cad)
p 912 1248 75 768 -1 pproc(OUTA):NPP
p 912 1184 75 768 -1 pproc(OUTB):NPP
p 912 1120 75 768 -1 pproc(OUTC):NPP
p 912 1056 75 768 -1 pproc(OUTD):NPP
p 912 992 75 768 -1 pproc(OUTE):NPP
p 912 928 75 768 -1 pproc(OUTF):NPP
p 912 864 75 768 -1 pproc(OUTG):NPP
p 912 800 75 768 -1 pproc(OUTH):NPP
p 688 -2904 100 0 0 typ(OUTH):path
[comments]
