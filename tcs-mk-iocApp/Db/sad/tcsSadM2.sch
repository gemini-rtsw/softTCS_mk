[schematic2]
uniq 35
[tools]
[detail]
w 1392 379 100 0 n#34 esirs.m2ZInsOffset.FLNK 1184 528 1248 528 1248 368 1584 368 esirs.chopDutyCycle.SLNK
w 2032 699 100 0 n#33 esirs.m2Magnification.FLNK 3360 992 3456 992 3456 688 656 688 656 368 768 368 esirs.m2ZInsOffset.SLNK
w 2872 427 100 0 n#31 esirs.chopState.FLNK 2672 576 2720 576 2720 416 3072 416 esirs.chopBeam.SLNK
w 2136 419 100 0 n#29 esirs.chopDutyCycle.FLNK 2000 528 2064 528 2064 416 2256 416 esirs.chopState.SLNK
w 3112 1090 100 0 n#24 esirs.m2Scale.FLNK 3360 1376 3456 1376 3456 1088 2816 1088 2816 832 2944 832 esirs.m2Magnification.SLNK
w 2008 1538 100 0 n#19 tcsSadM2Axis.tcsSadM2Axis#6.FLNK 3344 2080 3456 2080 3456 1536 608 1536 608 1344 736 1344 tcsSadM2Tilt.tcsSadM2Tilt#14.SLNK
w 2504 1355 100 0 n#17 tcsSadM2Tilt.tcsSadM2Tilt#15.FLNK 2432 1344 2624 1344 outhier.FLNK.p
w 1560 1346 100 0 n#16 tcsSadM2Tilt.tcsSadM2Tilt#14.FLNK 1472 1344 1696 1344 tcsSadM2Tilt.tcsSadM2Tilt#15.SLNK
w 2502 2082 100 0 n#7 tcsSadM2Axis.tcsSadM2Axis#2.FLNK 2432 2080 2608 2080 tcsSadM2Axis.tcsSadM2Axis#6.SLNK
w 622 2082 100 0 n#4 inhier.SLNK.P 544 2080 736 2080 tcsSadM2Axis.tcsSadM2Axis#1.SLNK
w 1566 2082 100 0 n#3 tcsSadM2Axis.tcsSadM2Axis#1.FLNK 1472 2080 1696 2080 tcsSadM2Axis.tcsSadM2Axis#2.SLNK
s 2928 2320 100 0 $Id: tcsSadM2.sch,v 1.5 2002/11/18 21:03:43 cjm Exp $
s 3200 64 100 0 TCS M2 related SAD records
s 3168 128 100 0 Gemini Telescope Control System
[cell use]
use esirs 792 280 100 0 m2ZInsOffset
xform 0 976 432
p 832 592 100 0 -1 DESC:M2 Instrument focus offset
p 704 80 100 0 0 EGU:mm
p 768 206 100 0 0 FDSC:Focus offset for current instrument
p 864 366 100 0 1 FTVL:DOUBLE
p 704 -336 100 0 0 MDEL:0.0005
p 960 208 100 0 0 PREC:3
p 864 398 100 0 0 SCAN:Passive
p 496 560 100 0 -1 def(INP):$(top)om:m2ZInsOffset
p 880 272 100 1024 0 name:$(sad)$(I)
use esirs 1608 280 100 0 chopDutyCycle
xform 0 1792 432
p 1520 240 100 0 0 ADEL:0.01
p 1696 590 100 0 -1 DESC:Chop duty cycle
p 1520 80 100 0 0 EGU:percent
p 1520 16 100 0 0 FDSC:The duty cycle of the chop throw
p 1520 -16 100 0 0 FTVL:DOUBLE
p 1520 -336 100 0 0 MDEL:0.01
p 1776 208 100 0 0 PREC:2
p 1248 528 100 0 -1 def(INP):$(top)om:chopDutyCycle
p 1696 272 100 1024 0 name:$(sad)$(I)
use esirs 2968 744 100 0 m2Magnification
xform 0 3152 896
p 3088 1054 100 0 -1 DESC:M2 Magnification
p 2944 670 100 0 0 FDSC:Nominal M2 magnification 
p 3040 830 100 0 1 FTVL:DOUBLE
p 2880 128 100 0 0 MDEL:0.000005
p 3136 672 100 0 0 PREC:5
p 3040 862 100 0 0 SCAN:Passive
p 2608 990 100 0 -1 def(INP):$(top)m2Magnification
p 3056 736 100 1024 0 name:$(sad)$(I)
use esirs 2968 1128 100 0 m2Scale
xform 0 3152 1280
p 3088 1438 100 0 -1 DESC:M2 Scale factor
p 2944 1054 100 0 0 FDSC:Sky tilt * m2Scale = M2 tilt
p 3040 1214 100 0 1 FTVL:DOUBLE
p 2880 512 100 0 0 MDEL:0.000005
p 3136 1056 100 0 0 PREC:5
p 3040 1246 100 0 1 SCAN:1 second
p 2704 1374 100 0 -1 def(INP):$(top)m2Scale
p 3056 1120 100 1024 0 name:$(sad)$(I)
use esirs 2280 328 100 0 chopState
xform 0 2464 480
p 2368 638 100 0 -1 DESC:Chop state demand
p 2192 64 100 0 0 FDSC:Whether chopping is on or off
p 1920 576 100 0 -1 def(INP):$(top)om:chopping
p 2368 320 100 1024 0 name:$(sad)$(I)
use esirs 3096 328 100 0 chopBeam
xform 0 3280 480
p 3184 638 100 0 -1 DESC:Chop beam demand
p 3008 64 100 0 0 FDSC:Which chop beam is selected
p 2736 576 100 0 -1 def(INP):$(top)om:chopBeam
p 3184 320 100 1024 0 name:$(sad)$(I)
use tcsSadM2Demands 2264 -24 100 0 tcsSadM2Demands#20
xform 0 2448 112
use tcsSadM2Tilt 760 968 100 0 tcsSadM2Tilt#14
xform 0 1104 1200
p 800 926 100 0 -1 seta:axis XTilt
p 800 894 100 0 -1 setb:units arcsec
p 800 862 100 0 -1 setc:rec1 $(top)om:m2Tilt.
p 1200 926 100 0 -1 setd:field1 VALG
p 1200 894 100 0 -1 sete:field2 VALA
p 1200 862 100 0 -1 setf:field3 VALC
p 1200 830 100 0 -1 setg:field4 VALE
use tcsSadM2Tilt 1720 968 100 0 tcsSadM2Tilt#15
xform 0 2064 1200
p 1760 926 100 0 -1 seta:axis YTilt
p 1760 894 100 0 -1 setb:units arcsec
p 1760 862 100 0 -1 setc:rec1 $(top)om:m2Tilt.
p 2160 926 100 0 -1 setd:field1 VALH
p 2160 894 100 0 -1 sete:field2 VALB
p 2160 862 100 0 -1 setf:field3 VALD
p 2160 830 100 0 -1 setg:field4 VALF
use tcsSadM2Axis 2632 1704 100 0 tcsSadM2Axis#6
xform 0 2976 1936
p 2688 1662 100 0 -1 seta:axis Z
p 2688 1630 100 0 -1 setb:units mm
p 2688 1598 100 0 -1 setc:rec1 $(top)om:m2Z.
p 3088 1662 100 0 -1 setd:field1 VALD
p 3088 1630 100 0 -1 sete:field2 VALA
p 3088 1598 100 0 -1 setf:field3 VALB
p 3088 1566 100 0 -1 setg:field4 VALC
use tcsSadM2Axis 760 1704 100 0 tcsSadM2Axis#1
xform 0 1104 1936
p 816 1694 100 0 -1 seta:axis X
p 816 1662 100 0 -1 setb:units mm
p 816 1630 100 0 -1 setc:rec1 $(top)om:m2XY.
p 1136 1694 100 0 -1 setd:field1 VALG
p 1136 1662 100 0 -1 sete:field2 VALA
p 1136 1630 100 0 -1 setf:field3 VALC
p 1136 1598 100 0 -1 setg:field4 VALE
use tcsSadM2Axis 1720 1704 100 0 tcsSadM2Axis#2
xform 0 2064 1936
p 1776 1678 100 0 -1 seta:axis Y
p 1776 1646 100 0 -1 setb:units mm
p 1776 1614 100 0 -1 setc:rec1 $(top)om:m2XY.
p 2128 1678 100 0 -1 setd:field1 VALH
p 2128 1646 100 0 -1 sete:field2 VALB
p 2128 1614 100 0 -1 setf:field3 VALD
p 2128 1566 100 0 -1 setg:field4 VALF
use outhier 2616 1304 100 0 FLNK
xform 0 2608 1344
use inhier 552 2040 100 0 SLNK
xform 0 544 2080
use bc200tr 336 -152 -100 0 frame
xform 0 2016 1152
[comments]
