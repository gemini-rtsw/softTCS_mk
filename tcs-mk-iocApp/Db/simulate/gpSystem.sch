[schematic2]
uniq 126
[tools]
[detail]
w -888 1035 100 0 n#62 ecars.ecars#122.FLNK -1136 1024 -592 1024 -592 416 junction
w -248 98 100 0 n#62 gpGenericCad8.gpGenericCad8#23.VLNK -704 416 -464 416 -464 96 16 96 esels.simCommonSel.SLNK
w -140 -48 100 0 n#62 gpGenericCad8.gpGenericCad8#33.VLNK -160 -240 -144 -240 -144 96 junction
w -1152 226 100 0 n#62 gpGenericCad8.gpGenericCad8#48.VLNK -1824 240 -1792 240 -1792 224 -464 224 junction
w -512 -21 100 0 n#62 gpGenericCad8.gpGenericCad8#109.VLNK -752 -32 -224 -32 -224 96 junction
w -1160 795 100 0 n#62 gpGenericCad8.gpGenericCad8#107.VLNK -1792 784 -480 784 -480 416 junction
w -606 587 100 0 n#125 ecars.ecars#122.VAL -1136 1248 -832 1248 -832 576 -320 576 -320 240 -80 240 -80 352 16 352 esels.simCommonSel.INPE
w -2156 1179 100 2 n#116 hwin.hwin#115.in -2160 1184 -2160 1184 elongouts.elongouts#113.DOL
w -2278 1163 100 0 n#114 ecad2.init.STLK -2464 960 -2336 960 -2336 1152 -2160 1152 elongouts.elongouts#113.SLNK
w -502 -101 100 0 n#110 gpGenericCad8.gpGenericCad8#109.VAL -752 -112 -192 -112 -192 320 16 320 esels.simCommonSel.INPF
w -790 619 100 0 n#108 gpGenericCad8.gpGenericCad8#107.VAL -1792 704 -1392 704 -1392 608 -128 608 -128 480 16 480 esels.simCommonSel.INPA
w 320 338 100 0 n#72 esels.simCommonSel.FLNK 304 336 384 336 384 400 464 400 outhier.FLNK.p
w 360 306 100 0 n#68 esels.simCommonSel.VAL 304 304 464 304 outhier.VAL.p
w -72 395 100 0 n#60 gpGenericCad8.gpGenericCad8#33.VAL -160 -320 -112 -320 -112 384 16 384 esels.simCommonSel.INPD
w -672 274 100 0 n#57 gpGenericCad8.gpGenericCad8#48.VAL -1824 160 -1072 160 -1072 272 -224 272 -224 416 16 416 esels.simCommonSel.INPC
w -504 338 100 0 n#56 gpGenericCad8.gpGenericCad8#23.VAL -704 336 -256 336 -256 448 16 448 esels.simCommonSel.INPB
s 1152 -880 100 0 Common subsystem CAD/CAR records
s 1136 -736 100 0 Gemini Telescope Control System
[cell use]
use ecars -1456 967 100 0 ecars#122
xform 0 -1296 1136
p -1344 960 100 1024 1 name:$(prefix)initC
use hwin -2352 1143 100 0 hwin#115
xform 0 -2256 1184
p -2349 1176 100 0 -1 val(in):$(CAR_BUSY)
use elongouts -2160 1063 100 0 elongouts#113
xform 0 -2032 1152
p -2144 1232 100 0 1 OMSL:closed_loop
p -1888 1104 100 0 -1 def(OUT):$(prefix)initC.IVAL
p -2048 1056 100 1024 1 name:$(prefix)initSetBusy
p -1904 1120 75 768 -1 pproc(OUT):PP
use ecad2 -2784 871 -100 0 init
xform 0 -2624 1184
p -2848 1072 100 0 1 SNAM:tcs$(snam)GenericCAD
p -2672 864 100 1024 1 name:$(prefix)init
use gpSimSad -688 1143 100 0 gpSimSad#111
xform 0 -432 1344
p -668 1116 100 0 1 seta:top $(sadtop)
use gpGenericCad8 -2056 648 100 0 gpGenericCad8#107
xform 0 -1928 744
p -2000 910 100 0 0 seta:prefix $(top)$(subsys)
p -2064 926 100 0 -1 setb:command datum
p -2064 894 100 0 -1 setc:delay 5.0
p -2064 862 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2064 830 100 0 -1 sete:outa 0.0
use gpGenericCad8 -2088 104 100 0 gpGenericCad8#48
xform 0 -1960 200
p -2032 366 100 0 0 seta:prefix $(top)$(subsys)
p -2096 382 100 0 -1 setb:command reboot
p -2096 350 100 0 -1 setc:delay 0.3
p -2096 318 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -2096 286 100 0 -1 sete:outa 0.0
use gpGenericCad8 -968 280 100 0 gpGenericCad8#23
xform 0 -840 376
p -912 542 100 0 0 seta:prefix $(top)$(subsys)
p -912 510 100 0 -1 setb:command test
p -912 478 100 0 -1 setc:delay 3.0
p -912 446 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -912 414 100 0 0 sete:outa 0.0
use gpGenericCad8 -424 -376 100 0 gpGenericCad8#33
xform 0 -296 -280
p -448 -416 100 0 0 seta:prefix $(top)$(subsys)
p -448 -130 100 0 -1 setb:command debug
p -448 -162 100 0 -1 setc:delay 0.1
p -448 -194 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -448 -448 100 0 0 sete:outa 0.0
use gpGenericCad8 -1016 -168 100 0 gpGenericCad8#109
xform 0 -888 -72
p -960 94 100 0 0 seta:prefix $(top)$(subsys)
p -1024 110 100 0 -1 setb:command stop
p -1024 78 100 0 -1 setc:delay 2.0
p -1024 46 100 0 -1 setd:snam tcs$(snam)GenericCAD
p -1024 14 100 0 -1 sete:outa 0.0
use outhier 456 360 100 0 FLNK
xform 0 448 400
use outhier 464 256 160 0 VAL
xform 0 448 304
use bd200tr -3200 -1256 -100 0 frame
xform 0 -560 448
use esels -16 32 100 0 simCommonSel
xform 0 160 288
p -207 -107 100 0 0 PV:$(top)$(subsys)
p 112 318 100 0 -1 SELM:High Signal
[comments]
