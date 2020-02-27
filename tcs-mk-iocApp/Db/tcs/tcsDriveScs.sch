[schematic2]
uniq 12
[tools]
[detail]
w 3048 1003 100 0 n#11 ecalcs.m2CalcDummy.FLNK 2880 1952 2976 1952 2976 992 3168 992 egenSub.issueM2Move.SLNK
w 2520 1707 100 0 n#10 ecalcs.m2CalcTrigger.VAL 2432 1920 2496 1920 2496 1696 2592 1696 ecalcs.m2CalcDummy.SDIS
w 2510 1739 100 0 n#9 ecalcs.m2CalcTrigger.FLNK 2432 1952 2464 1952 2464 1728 2592 1728 ecalcs.m2CalcDummy.SLNK
w 1806 1963 100 0 n#7 ecalcs.m2CalcCounter.FLNK 1664 1952 1984 1952 1984 1728 2144 1728 ecalcs.m2CalcTrigger.SLNK
w 1822 1931 100 0 n#5 junction 1728 1920 1952 1920 1952 2112 2144 2112 ecalcs.m2CalcTrigger.INPA
w 1486 2187 100 0 n#5 ecalcs.m2CalcCounter.VAL 1664 1920 1728 1920 1728 2176 1280 2176 1280 2112 1376 2112 ecalcs.m2CalcCounter.INPA
w 1230 2091 100 0 n#4 elongins.m2ComaInt.VAL 1120 2080 1376 2080 ecalcs.m2CalcCounter.INPB
s 3008 576 100 0 m2NomPosn command.
s 3008 608 100 0 It is also processed whenever the user issues the
s 3008 640 100 0 corrrections are enabled.
s 3008 672 100 0 by m2ComaInt provided that the model
s 3008 704 100 0 This record processes at an interval set
s 1760 2368 100 0 stage is fixed it is not expected to be used
s 1760 2416 100 0 the coma of the telescope by tilting M2. Once the XY
s 1760 2464 100 0 This schematic provides a temporary fix to correct
s 3120 2576 100 0 $Id: tcsDriveScs.sch,v 1.1 1999/03/12 09:31:34 cjm Exp $
s 3392 320 100 0 Correct Coma with Tilt
s 3360 384 100 0 Gemini Telescope Control System
[cell use]
use ecalcs 2592 1639 100 0 m2CalcDummy
xform 0 2736 1904
p 2672 1792 100 0 1 DISV:0
use ecalcs 2144 1639 100 0 m2CalcTrigger
xform 0 2288 1904
p 2224 1824 100 0 -1 CALC:A=0&&B?1:0
p 1792 2080 100 0 -1 def(INPB):$(tcs)im:m2ComaCorrFlag
use ecalcs 1376 1639 100 0 m2CalcCounter
xform 0 1520 1904
p 1472 1792 100 0 1 CALC:(A+1)%MAX(B,1)
p 1552 1680 100 0 1 SCAN:1 second
use elongins 864 2023 100 0 m2ComaInt
xform 0 992 2096
p 816 2208 100 0 -1 DESC:Update interval of M2 coma tilts
p 928 1920 100 0 1 EGU:seconds
use egenSub 3168 903 100 0 issueM2Move
xform 0 3312 1328
p 3184 1760 100 0 -1 DESC:Issue move command to M2
p 3248 1120 100 0 1 FTVJ:STRING
p 3232 848 100 0 1 SNAM:tcsOpticsM2Move
p 2800 1648 100 0 -1 def(INPA):$(tcs)im:m2ComaCorrFlag
p 3584 1664 100 0 -1 def(OUTA):$(m2)move.A
p 3584 1600 100 0 -1 def(OUTB):$(m2)move.B
p 3584 1536 100 0 -1 def(OUTC):$(m2)move.C
p 3584 1472 100 0 -1 def(OUTD):$(m2)move.D
p 3584 1408 100 0 -1 def(OUTE):$(m2)move.E
p 3584 1344 100 0 -1 def(OUTF):$(m2)move.F
p 3584 1280 100 0 -1 def(OUTG):$(m2)move.G
p 3584 1216 100 0 -1 def(OUTH):$(m2)move.H
p 3584 1152 100 0 -1 def(OUTI):$(m2)move.I
p 3584 1088 100 0 -1 def(OUTJ):$(m2)move.DIR
p 3456 1098 75 0 -1 pproc(OUTJ):PP
use bc200tr 544 104 -100 0 frame
xform 0 2224 1408
[comments]
