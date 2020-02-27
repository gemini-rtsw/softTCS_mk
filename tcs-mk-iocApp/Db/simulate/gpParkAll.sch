[schematic2]
uniq 155
[tools]
[detail]
w 923 -20 100 0 n#154 gpGenericCad8.gpGenericCad8#147.FLNK 498 -31 1408 -31 1408 48 1504 48 elongouts.elongouts#119.SLNK
w 1576 -78 100 0 n#115 elongouts.elongouts#119.FLNK 1760 80 1824 80 1824 -80 1376 -80 1376 -208 1504 -208 elongouts.elongouts#120.SLNK
w 1432 82 100 0 n#117 hwin.hwin#121.in 1408 80 1504 80 elongouts.elongouts#119.DOL
w 1432 -174 100 0 n#118 hwin.hwin#122.in 1408 -176 1504 -176 elongouts.elongouts#120.DOL
w 530 -78 100 0 n#153 gpGenericCad8.gpGenericCad8#147.VAL 496 -80 624 -80 624 -192 704 -192 outhier.VAL.p
w 530 2 100 0 n#152 gpGenericCad8.gpGenericCad8#147.VLNK 496 0 624 0 624 112 704 112 outhier.FLNK.p
s 2096 1104 100 0 gpParkAll.sch
[cell use]
use elongouts 1528 -296 100 0 elongouts#120
xform 0 1632 -208
p 1552 -114 100 0 -1 DESC:Start Directive
p 1344 -66 100 0 0 EGU:units
p 1344 -290 100 0 0 OMSL:closed_loop
p 1344 -34 100 0 0 PINI:NO
p 1840 -242 100 0 -1 def(OUT):$(gp)platePark.DIR
p 1616 -304 100 1024 -1 name:$(gp)plateSPark
p 1760 -240 75 768 -1 pproc(OUT):PP
use elongouts 1528 -40 100 0 elongouts#119
xform 0 1632 48
p 1552 142 100 0 -1 DESC:Mark directive
p 1344 -34 100 0 0 OMSL:closed_loop
p 1840 14 100 0 -1 def(OUT):$(gp)platePark.DIR
p 1616 -48 100 1024 -1 name:$(gp)plateMPark
p 1760 16 75 768 -1 pproc(OUT):PP
use hwin 1240 -216 100 0 hwin#122
xform 0 1312 -176
p 1219 -184 100 0 -1 val(in):$(CAD_START)
use hwin 1240 40 100 0 hwin#121
xform 0 1312 80
p 1219 72 100 0 -1 val(in):$(CAD_MARK)
use outhier 696 72 100 0 FLNK
xform 0 688 112
use outhier 696 -232 100 0 VAL
xform 0 688 -192
use gpGenericCad8 232 -136 100 0 gpGenericCad8#147
xform 0 360 -40
p 208 -176 100 0 1 seta:command park
p 208 -208 100 0 1 setb:delay 5.0
p 208 -240 100 0 1 setc:snam tcsGpGenericCAD
p 208 -272 100 0 0 setd:outa 0.0
use bc200tr -640 -1368 -100 0 frame
xform 0 1040 -64
[comments]
