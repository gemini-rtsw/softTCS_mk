[schematic2]
uniq 231
[tools]
[detail]
w 1586 459 100 0 FLNK esirs.targetG4.FLNK 1536 448 1696 448 outhier.FLNK.p
w 1042 299 100 0 n#229 esirs.targetG3.FLNK 960 448 1024 448 1024 288 1120 288 esirs.targetG4.SLNK
w 450 299 100 0 n#228 esirs.targetG2.FLNK 352 448 416 448 416 288 544 288 esirs.targetG3.SLNK
w -158 299 100 0 n#227 esirs.targetG1.FLNK -256 448 -192 448 -192 288 -64 288 esirs.targetG2.SLNK
w 82 651 100 0 n#226 esirs.targetOiwfs.FLNK 960 992 1024 992 1024 640 -800 640 -800 288 -672 288 esirs.targetG1.SLNK
w 82 1195 100 0 n#225 esirs.targetC.FLNK 960 1536 1024 1536 1024 1184 -800 1184 -800 832 -672 832 esirs.targetPwfs1.SLNK
w 450 843 100 0 n#223 esirs.targetPwfs2.FLNK 352 992 416 992 416 832 544 832 esirs.targetOiwfs.SLNK
w -158 843 100 0 n#222 esirs.targetPwfs1.FLNK -256 992 -192 992 -192 832 -64 832 esirs.targetPwfs2.SLNK
w 450 1387 100 0 n#221 esirs.targetB.FLNK 352 1536 416 1536 416 1376 544 1376 esirs.targetC.SLNK
w -158 1387 100 0 n#220 esirs.targetA.FLNK -256 1536 -192 1536 -192 1376 -64 1376 esirs.targetB.SLNK
w -822 1387 100 0 SLNK inhier.SLNK.P -912 1376 -672 1376 esirs.targetA.SLNK
s 1408 1760 100 0 $Id: tcsSadTargetArrays.sch,v 1.1 2009/10/30 17:36:00 cjm Exp $
s 1408 -432 100 0 Copyright
s 1408 -464 100 0 Observatory
s 1408 -496 100 0 Sciences Ltd.
s 1648 -496 100 0 Target array parameters
[cell use]
use outhier 1664 407 100 0 FLNK
xform 0 1680 448
use inhier -928 1335 100 0 SLNK
xform 0 -912 1376
use esirs 568 744 100 0 targetOiwfs
xform 0 752 896
p 656 1054 100 0 -1 DESC:OIWFS Target
p 480 480 100 0 0 FDSC:OIWFS Target position and offsets
p 480 448 100 0 0 FTVL:DOUBLE
p 495 224 100 0 0 HIGH:0.0
p 495 288 100 0 0 HIHI:0.0
p 495 256 100 0 0 LOLO:0.0
p 495 192 100 0 0 LOW:0.0
p 736 672 100 0 0 NELM:8
p 495 384 100 0 0 PREC:14
p 495 768 100 0 0 SCAN:Passive
p 736 846 100 0 -1 SNAM:
p 640 990 100 0 -1 def(INP):$(top)drives:end.VALG
p 656 736 100 1024 0 name:$(sad)$(I)
use esirs -648 744 100 0 targetPwfs1
xform 0 -464 896
p -560 1054 100 0 -1 DESC:PWFS1 Target
p -736 480 100 0 0 FDSC:PWFS1 Target position and offsets
p -736 448 100 0 0 FTVL:DOUBLE
p -721 224 100 0 0 HIGH:0.0
p -721 288 100 0 0 HIHI:0.0
p -721 256 100 0 0 LOLO:0.0
p -721 192 100 0 0 LOW:0.0
p -480 672 100 0 0 NELM:8
p -721 384 100 0 0 PREC:14
p -721 768 100 0 0 SCAN:Passive
p -480 846 100 0 -1 SNAM:
p -576 990 100 0 -1 def(INP):$(top)drives:end.VALE
p -560 736 100 1024 0 name:$(sad)$(I)
use esirs -40 744 100 0 targetPwfs2
xform 0 144 896
p 48 1054 100 0 -1 DESC:PWFS2 Target
p -128 480 100 0 0 FDSC:PWFS2 Target position and offsets
p -128 448 100 0 0 FTVL:DOUBLE
p -113 224 100 0 0 HIGH:0.0
p -113 288 100 0 0 HIHI:0.0
p -113 256 100 0 0 LOLO:0.0
p -113 192 100 0 0 LOW:0.0
p 128 672 100 0 0 NELM:8
p -113 384 100 0 0 PREC:14
p -113 768 100 0 0 SCAN:Passive
p 128 846 100 0 -1 SNAM:
p 32 990 100 0 -1 def(INP):$(top)drives:end.VALF
p 48 736 100 1024 0 name:$(sad)$(I)
use esirs -648 1288 100 0 targetA
xform 0 -464 1440
p -560 1598 100 0 -1 DESC:Target A
p -736 1024 100 0 0 FDSC:Target A position and offsets
p -736 992 100 0 0 FTVL:DOUBLE
p -721 768 100 0 0 HIGH:0.0
p -721 832 100 0 0 HIHI:0.0
p -721 800 100 0 0 LOLO:0.0
p -721 736 100 0 0 LOW:0.0
p -480 1216 100 0 0 NELM:8
p -721 928 100 0 0 PREC:14
p -721 1312 100 0 0 SCAN:Passive
p -480 1390 100 0 -1 SNAM:
p -576 1534 100 0 -1 def(INP):$(top)drives:end.VALB
p -560 1280 100 1024 0 name:$(sad)$(I)
use esirs -40 1288 100 0 targetB
xform 0 144 1440
p 48 1598 100 0 -1 DESC:Target B
p -128 1024 100 0 0 FDSC:Target B position and offsets
p -128 992 100 0 0 FTVL:DOUBLE
p -113 768 100 0 0 HIGH:0.0
p -113 832 100 0 0 HIHI:0.0
p -113 800 100 0 0 LOLO:0.0
p -113 736 100 0 0 LOW:0.0
p 128 1216 100 0 0 NELM:8
p -113 928 100 0 0 PREC:14
p -113 1312 100 0 0 SCAN:Passive
p 128 1390 100 0 -1 SNAM:
p 32 1534 100 0 -1 def(INP):$(top)drives:end.VALC
p 48 1280 100 1024 0 name:$(sad)$(I)
use esirs 568 1288 100 0 targetC
xform 0 752 1440
p 656 1598 100 0 -1 DESC:Target C
p 480 1024 100 0 0 FDSC:Target C position and offsets
p 480 992 100 0 0 FTVL:DOUBLE
p 495 768 100 0 0 HIGH:0.0
p 495 832 100 0 0 HIHI:0.0
p 495 800 100 0 0 LOLO:0.0
p 495 736 100 0 0 LOW:0.0
p 736 1216 100 0 0 NELM:8
p 495 928 100 0 0 PREC:14
p 495 1312 100 0 0 SCAN:Passive
p 736 1390 100 0 -1 SNAM:
p 640 1534 100 0 -1 def(INP):$(top)drives:end.VALD
p 656 1280 100 1024 0 name:$(sad)$(I)
use esirs -648 200 100 0 targetG1
xform 0 -464 352
p -560 510 100 0 -1 DESC:Target G1
p -736 -64 100 0 0 FDSC:Target A position and offsets
p -736 -96 100 0 0 FTVL:DOUBLE
p -721 -320 100 0 0 HIGH:0.0
p -721 -256 100 0 0 HIHI:0.0
p -721 -288 100 0 0 LOLO:0.0
p -721 -352 100 0 0 LOW:0.0
p -480 128 100 0 0 NELM:8
p -721 -160 100 0 0 PREC:14
p -721 224 100 0 0 SCAN:Passive
p -480 302 100 0 -1 SNAM:
p -576 446 100 0 -1 def(INP):$(top)drives:end.VALK
p -560 192 100 1024 0 name:$(sad)$(I)
use esirs -40 200 100 0 targetG2
xform 0 144 352
p 48 510 100 0 -1 DESC:Target G2
p -128 -64 100 0 0 FDSC:Target B position and offsets
p -128 -96 100 0 0 FTVL:DOUBLE
p -113 -320 100 0 0 HIGH:0.0
p -113 -256 100 0 0 HIHI:0.0
p -113 -288 100 0 0 LOLO:0.0
p -113 -352 100 0 0 LOW:0.0
p 128 128 100 0 0 NELM:8
p -113 -160 100 0 0 PREC:14
p -113 224 100 0 0 SCAN:Passive
p 128 302 100 0 -1 SNAM:
p 32 446 100 0 -1 def(INP):$(top)drives:end.VALL
p 48 192 100 1024 0 name:$(sad)$(I)
use esirs 568 200 100 0 targetG3
xform 0 752 352
p 656 510 100 0 -1 DESC:Target G3
p 480 -64 100 0 0 FDSC:Target C position and offsets
p 480 -96 100 0 0 FTVL:DOUBLE
p 495 -320 100 0 0 HIGH:0.0
p 495 -256 100 0 0 HIHI:0.0
p 495 -288 100 0 0 LOLO:0.0
p 495 -352 100 0 0 LOW:0.0
p 736 128 100 0 0 NELM:8
p 495 -160 100 0 0 PREC:14
p 495 224 100 0 0 SCAN:Passive
p 736 302 100 0 -1 SNAM:
p 640 446 100 0 -1 def(INP):$(top)drives:end.VALM
p 656 192 100 1024 0 name:$(sad)$(I)
use esirs 1144 200 100 0 targetG4
xform 0 1328 352
p 1232 510 100 0 -1 DESC:Target G4
p 1056 -64 100 0 0 FDSC:Target A position and offsets
p 1056 -96 100 0 0 FTVL:DOUBLE
p 1071 -320 100 0 0 HIGH:0.0
p 1071 -256 100 0 0 HIHI:0.0
p 1071 -288 100 0 0 LOLO:0.0
p 1071 -352 100 0 0 LOW:0.0
p 1312 128 100 0 0 NELM:8
p 1071 -160 100 0 0 PREC:14
p 1071 224 100 0 0 SCAN:Passive
p 1312 302 100 0 -1 SNAM:
p 1216 446 100 0 -1 def(INP):$(top)drives:end.VALN
p 1232 192 100 1024 0 name:$(sad)$(I)
use bc200tr -1184 -712 -100 0 frame
xform 0 496 592
[comments]
