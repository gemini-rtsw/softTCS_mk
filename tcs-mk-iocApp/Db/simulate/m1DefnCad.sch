[schematic2]
uniq 54
[tools]
[detail]
w 1058 1376 100 0 n#52 inhier.IVAL.P 720 1616 1056 1616 1056 1088 junction
w 1024 1090 100 0 n#52 elongouts.CarVals.OUT 912 1088 1184 1088 ecars.ecars#14.IVAL
w 434 752 100 0 n#51 ecad20.ecad20#44.STLK 112 336 432 336 432 1120 656 1120 elongouts.CarVals.SLNK
w 592 1154 100 0 n#50 hwin.hwin#49.in 576 1152 656 1152 elongouts.CarVals.DOL
w 1536 1090 100 0 n#42 ecars.ecars#14.VAL 1504 1088 1616 1088 outhier.VAL.p
w 1536 866 100 0 n#40 ecars.ecars#14.FLNK 1504 864 1616 864 outhier.FLNK.p
s 416 2048 100 0 it determines the mirror is in position.
s 416 2080 100 0 This latter schematic then sets the CAR back to IDLE when
s 416 2112 100 0 the rate at which the mirror reaches its demand position.
s 416 2144 100 0 m1Position schematic implements a servo that controls the
s 416 2176 100 0 and then sets the CAR record to BUSY. The 
s 2048 176 100 0 Gemini Telescope Control System
s 368 1200 100 0 BUSY
s 2048 128 100 0 General simulated CAD 20 with
s 2080 96 100 0 delay as specified macro
s 1792 2368 100 0 $Id: m1DefnCad.sch,v 1.1.1.1 1998/11/08 00:20:22 epics Exp $
s 416 2208 100 0 The CAD routine stores away the total offset demands
[cell use]
use inhier 728 1576 100 0 IVAL
xform 0 720 1616
use hwin 408 1112 100 0 hwin#49
xform 0 480 1152
p 387 1144 100 0 -1 val(in):$(CAR_BUSY)
use elongouts 680 1032 100 0 CarVals
xform 0 784 1120
p 496 1038 100 0 0 OMSL:closed_loop
p 768 1024 100 1024 0 name:$(prefix)$(cadname)$(I)
p 688 1230 100 0 -1 DESC:Set CAR to BUSY
p 912 1088 75 768 -1 pproc(OUT):PP
use outhier 1608 1048 100 0 VAL
xform 0 1600 1088
use outhier 1608 824 100 0 FLNK
xform 0 1600 864
use bc200tr -784 -104 -100 0 frame
xform 0 896 1200
use ecad20 -184 248 100 0 ecad20#44
xform 0 -48 1136
p -256 446 100 0 1 SNAM:tcs$(substring)$(cadname)CAD
p -96 240 100 1024 1 name:$(prefix)$(cadname)
p -112 1680 100 0 0 FTVB:DOUBLE
p -112 1648 100 0 0 FTVC:DOUBLE
p -112 1616 100 0 0 FTVD:DOUBLE
p -112 1584 100 0 0 FTVE:DOUBLE
p -112 1552 100 0 0 FTVF:DOUBLE
p -112 1520 100 0 0 FTVG:DOUBLE
use ecars 1208 808 100 0 ecars#14
xform 0 1344 976
p 1184 798 100 0 1 name:$(prefix)$(cadname)C
[comments]
