[schematic2]
uniq 10
[tools]
[detail]
s 800 1936 200 0 Read M2 PID parameters
s 2192 -112 100 0 Gemini TCS
s 1936 -176 100 0 Sciences Ltd.
s 1936 -144 100 0 Observatory
s 1936 -112 100 0 Copyright
s 1920 2080 100 0 $Id: tcsOpticsM2PID.sch,v 1.1 2002/11/23 12:46:17 cjm Exp $
[cell use]
use eais 1664 807 100 0 focusD
xform 0 1792 880
p 1712 960 100 0 -1 DESC:D term Z focus
p 1408 622 100 0 0 EGU:units
p 1408 718 100 0 0 PREC:5
p 1328 928 100 0 -1 def(INP):$(m2)setController.O
p 1776 800 100 1024 0 name:$(top)$(I)
p 1632 912 75 1280 -1 pproc(INP):CPP
use eais 1664 1127 100 0 focusI
xform 0 1792 1200
p 1712 1280 100 0 -1 DESC:I term Z focus
p 1408 942 100 0 0 EGU:units
p 1408 1038 100 0 0 PREC:5
p 1328 1248 100 0 -1 def(INP):$(m2)setController.N
p 1776 1120 100 1024 0 name:$(top)$(I)
p 1632 1232 75 1280 -1 pproc(INP):CPP
use eais 1664 1479 100 0 focusP
xform 0 1792 1552
p 1712 1632 100 0 -1 DESC:P term Z focus
p 1408 1294 100 0 0 EGU:units
p 1408 1390 100 0 0 PREC:5
p 1328 1600 100 0 -1 def(INP):$(m2)setController.M
p 1776 1472 100 1024 0 name:$(top)$(I)
p 1632 1584 75 1280 -1 pproc(INP):CPP
use eais 896 807 100 0 ytiltD
xform 0 1024 880
p 944 960 100 0 -1 DESC:D term Y tilt
p 640 622 100 0 0 EGU:units
p 640 718 100 0 0 PREC:5
p 560 928 100 0 -1 def(INP):$(m2)setController.H
p 1008 800 100 1024 0 name:$(top)$(I)
p 864 912 75 1280 -1 pproc(INP):CPP
use eais 896 1127 100 0 ytiltI
xform 0 1024 1200
p 944 1280 100 0 -1 DESC:I term Y tilt
p 640 942 100 0 0 EGU:units
p 640 1038 100 0 0 PREC:5
p 560 1248 100 0 -1 def(INP):$(m2)setController.G
p 1008 1120 100 1024 0 name:$(top)$(I)
p 864 1232 75 1280 -1 pproc(INP):CPP
use eais 896 1479 100 0 ytiltP
xform 0 1024 1552
p 944 1632 100 0 -1 DESC:P term Y tilt
p 640 1294 100 0 0 EGU:units
p 640 1390 100 0 0 PREC:5
p 560 1600 100 0 -1 def(INP):$(m2)setController.F
p 1008 1472 100 1024 0 name:$(top)$(I)
p 864 1584 75 1280 -1 pproc(INP):CPP
use eais 96 807 100 0 xtiltD
xform 0 224 880
p 144 960 100 0 -1 DESC:D term X tilt
p -160 622 100 0 0 EGU:units
p -160 718 100 0 0 PREC:5
p -240 928 100 0 -1 def(INP):$(m2)setController.C
p 208 800 100 1024 0 name:$(top)$(I)
p 64 912 75 1280 -1 pproc(INP):CPP
use eais 96 1127 100 0 xtiltI
xform 0 224 1200
p 144 1280 100 0 -1 DESC:I term X tilt
p -160 942 100 0 0 EGU:units
p -160 1038 100 0 0 PREC:5
p -240 1248 100 0 -1 def(INP):$(m2)setController.B
p 208 1120 100 1024 0 name:$(top)$(I)
p 64 1232 75 1280 -1 pproc(INP):CPP
use eais 96 1479 100 0 xtiltP
xform 0 224 1552
p 144 1632 100 0 -1 DESC:P term X tilt
p -160 1294 100 0 0 EGU:units
p -160 1390 100 0 0 PREC:5
p -240 1600 100 0 -1 def(INP):$(m2)setController.A
p 208 1472 100 1024 0 name:$(top)$(I)
p 64 1584 75 1280 -1 pproc(INP):CPP
use bc200tr -640 -392 -100 0 frame
xform 0 1040 912
[comments]
