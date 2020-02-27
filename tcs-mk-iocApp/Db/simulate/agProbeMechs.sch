[schematic2]
uniq 21
[tools]
[detail]
w 1188 692 100 0 n#20 genericcad.genericcad#5.VLNK 1032 680 1032 688 1392 688 1392 1024 junction
w 1188 1018 100 0 n#20 genericcad.genericcad#4.VLNK 1032 1016 1392 1016 1392 1200 junction
w 1204 1394 100 0 n#20 genericcad.genericcad#3.VLNK 1032 1384 1064 1384 1064 1392 1392 1392 junction
w 1204 1698 100 0 n#20 genericcad.genericcad#2.VLNK 1032 1704 1064 1704 1064 1696 1392 1696 junction
w 1204 2002 100 0 n#20 genericcad.genericcad#1.VLNK 1032 2008 1064 2008 1064 2000 1392 2000 junction
w 1394 1788 100 0 n#20 genericcad.genericcad#0.VLNK 1032 2328 1392 2328 1392 1200 1744 1200 esels.agBdSelect.SLNK
w 2096 1410 100 0 n#19 esels.agBdSelect.VAL 2032 1408 2208 1408 2208 1392 2320 1392 outhier.VAL.p
w 2096 1442 -100 0 FLNK esels.agBdSelect.FLNK 2032 1440 2208 1440 2208 1456 2320 1456 outhier.FLNK.p
w 1554 1036 100 0 n#13 genericcad.genericcad#5.VAL 1032 600 1552 600 1552 1424 1744 1424 esels.agBdSelect.INPF
w 1522 1220 100 0 n#11 genericcad.genericcad#4.VAL 1032 936 1520 936 1520 1456 1744 1456 esels.agBdSelect.INPE
w 1236 1308 100 0 n#10 genericcad.genericcad#3.VAL 1032 1304 1488 1304 1488 1488 1744 1488 esels.agBdSelect.INPD
w 1242 1626 100 0 n#9 genericcad.genericcad#2.VAL 1032 1624 1488 1624 1488 1520 1744 1520 esels.agBdSelect.INPC
w 1258 1930 100 0 n#8 genericcad.genericcad#1.VAL 1032 1928 1520 1928 1520 1552 1744 1552 esels.agBdSelect.INPB
w 1554 1934 100 0 n#7 genericcad.genericcad#0.VAL 1032 2248 1552 2248 1552 1584 1744 1584 esels.agBdSelect.INPA
s 192 2352 150 0 Set of mechanism commands
s 192 2304 150 0 simulating A&G Beam
s 192 2256 150 0 Direction mechanism control
[cell use]
use outhier 2352 1376 100 0 VAL
xform 0 2304 1392
use outhier 2352 1456 100 0 FLNK
xform 0 2304 1456
use esels 1768 1128 -100 0 agBdSelect
xform 0 1888 1392
p 1824 1422 100 0 -1 SELM:High Signal
p 1856 1120 100 1024 -1 name:$(ag)$(mech)BdValSel
use genericcad 808 536 100 0 genericcad#5
xform 0 896 640
p 784 526 100 0 -1 seta:command $(mech)Define
p 784 494 100 0 -1 setb:delay 0.5
p 784 462 100 0 0 setc:outa 0.0
p 784 430 100 0 0 setd:snam tcsAgGenericCAD
use genericcad 808 872 100 0 genericcad#4
xform 0 896 976
p 784 862 100 0 -1 seta:command $(mech)Test
p 784 830 100 0 -1 setb:delay 2.0
p 784 798 100 0 0 setc:outa 0.0
p 784 430 100 0 0 setd:snam tcsAgGenericCAD
use genericcad 808 1240 100 0 genericcad#3
xform 0 896 1344
p 784 1230 100 0 -1 seta:command $(mech)Park
p 784 1198 100 0 -1 setb:delay 5.0
p 784 1166 100 0 0 setc:outa 0.0
p 784 430 100 0 0 setd:snam tcsAgGenericCAD
use genericcad 808 1560 100 0 genericcad#2
xform 0 896 1664
p 784 1550 100 0 -1 seta:command $(mech)Datum
p 784 1518 100 0 -1 setb:delay 5.0
p 784 1486 100 0 0 setc:outa 0.0
p 784 430 100 0 0 setd:snam tcsAgGenericCAD
use genericcad 808 1864 100 0 genericcad#1
xform 0 896 1968
p 784 1854 100 0 -1 seta:command $(mech)Eng
p 784 1822 100 0 -1 setb:delay 0.5
p 784 1790 100 0 0 setc:outa 0.0
p 784 430 100 0 0 setd:snam tcsAgGenericCAD
use genericcad 808 2184 100 0 genericcad#0
xform 0 896 2288
p 784 2174 100 0 -1 seta:command $(mech)Sel
p 784 2142 100 0 -1 setb:delay 0.5
p 784 2110 100 0 0 setc:outa 0.0
p 784 2110 100 0 -1 setd:snam tcsAG$(mech)SelCAD
use bc200tr -16 -24 -100 0 frame
xform 0 1664 1280
[comments]
