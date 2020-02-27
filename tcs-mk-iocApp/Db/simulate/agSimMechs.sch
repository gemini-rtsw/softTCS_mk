[schematic2]
uniq 4
[tools]
[detail]
w 812 2290 100 0 n#1 inhier.NPROBE.P 736 2288 936 2288 agMechCad.agMechCad#21.CPROBE
w 1312 1426 100 0 n#2 tcscar.tcscar#27.VAL 1248 1424 1424 1424 1424 1408 1536 1408 outhier.VAL.p
w 1312 1458 -100 0 FLNK#3 tcscar.tcscar#27.FLNK 1248 1456 1424 1456 1424 1472 1536 1472 outhier.FLNK.p
s 2560 2448 100 0 $Id: agSimMechs.sch,v 1.5 2010/06/11 15:43:43 cjm Exp $
s 192 2256 150 0 mechanism control
s 192 2304 150 0 simulating A&G
s 192 2352 150 0 Set of commands
[cell use]
use bc200tr -16 -24 -100 0 frame
xform 0 1664 1280
use estringouts 1368 2216 100 0 estringouts#34
xform 0 1472 2288
p 1280 2254 100 0 0 VAL:
p 1456 2208 100 1024 -1 name:$(prefix)$(mech)Name
use inhier 744 2248 100 0 NPROBE
xform 0 736 2288
use tcscar 856 1272 100 0 tcscar#27
xform 0 1040 1392
p 912 1262 100 0 1 seta:car $(mech)C
use agMechCad 952 984 100 0 agMechCad#26
xform 0 1080 1080
p 968 966 100 0 -1 seta:command $(mech)Define
p 968 934 100 0 -1 setb:delay 0.5
p 968 902 100 0 0 setc:outa 0.0
p 968 870 100 0 0 setd:snam tcsAgGenericCAD
use agMechCad 944 712 100 0 agMechCad#25
xform 0 1072 808
p 960 694 100 0 -1 seta:command $(mech)Test
p 960 662 100 0 -1 setb:delay 2.0
p 960 630 100 0 0 setc:outa 0.0
p 960 262 100 0 0 setd:snam tcsAgGenericCAD
use agMechCad 952 488 100 0 agMechCad#24
xform 0 1080 584
p 968 470 100 0 -1 seta:command $(mech)Park
p 968 438 100 0 -1 setb:delay 5.0
p 976 400 100 0 -1 setc:outa $(prefix)$(mech)Name
p 976 368 100 0 -1 setd:snam tcsAgParkCAD
use agMechCad 936 1640 100 0 agMechCad#23
xform 0 1064 1736
p 952 1622 100 0 -1 seta:command $(mech)Datum
p 952 1590 100 0 -1 setb:delay 5.0
p 952 1558 100 0 0 setc:outa 0.0
p 952 502 100 0 0 setd:snam tcsAgGenericCAD
use agMechCad 928 1880 100 0 agMechCad#22
xform 0 1056 1976
p 944 1862 100 0 -1 seta:command $(mech)Eng
p 944 1830 100 0 -1 setb:delay 0.5
p 944 1798 100 0 0 setc:outa 0.0
p 944 438 100 0 0 setd:snam tcsAgGenericCAD
use agMechCad 928 2200 100 0 agMechCad#21
xform 0 1056 2296
p 944 2182 100 0 -1 seta:command $(mech)Sel
p 944 2150 100 0 -1 setb:delay $(delay)
p 944 2078 100 0 -1 setc:outa $(prefix)$(mech)Name
p 944 2118 100 0 -1 setd:snam tcsAG$(mech)SelCAD
use outhier 1568 1472 100 0 FLNK
xform 0 1520 1472
use outhier 1568 1392 100 0 VAL
xform 0 1520 1408
[comments]
