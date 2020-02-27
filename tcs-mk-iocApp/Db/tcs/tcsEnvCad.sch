[schematic2]
uniq 44
[tools]
[detail]
w 706 1032 100 0 n#43 ecad8.ecad8#23.STLK 544 688 704 688 704 1328 1008 1328 eaos.Slow.SLNK
w 818 1064 100 0 n#42 ecad8.ecad8#23.VALC 544 1232 816 1232 816 848 1024 848 eaos.Current.DOL
w 672 1298 100 0 n#41 ecad8.ecad8#23.VALB 544 1296 848 1296 848 1104 1008 1104 eaos.Other.DOL
w 752 1362 100 0 n#40 ecad8.ecad8#23.VALA 544 1360 1008 1360 eaos.Slow.DOL
w 1200 946 100 0 n#39 eaos.Other.FLNK 1264 1104 1552 1104 1552 944 896 944 896 816 1024 816 eaos.Current.SLNK
w 1200 1202 100 0 n#36 eaos.Slow.FLNK 1264 1360 1552 1360 1552 1200 896 1200 896 1072 1008 1072 eaos.Other.SLNK
w 1206 1554 100 0 n#6 ecad8.ecad8#23.VAL 544 1552 1904 1552 outhier.VAL.p
w 1302 1458 100 0 n#9 ecad8.ecad8#23.MESS 544 1520 576 1520 576 1456 2064 1456 outhier.MESS.p
w 46 1524 100 0 n#8 inhier.ICID.P -176 1456 -96 1456 -96 1520 224 1520 ecad8.ecad8#23.ICID
w 6 1554 100 0 n#7 inhier.DIR.P -176 1552 224 1552 ecad8.ecad8#23.DIR
s 1728 1056 100 0 SAD.
s 1728 1088 100 0 trigger processing that will then cause a write to the 
s 1728 1120 100 0 The Current records output link is PP in order to 
s 1824 -352 100 0 12 May 1997
s 2032 -192 100 0 Gemini Telescope Control System
s 1888 2000 100 0 $Id: tcsEnvCad.sch,v 1.2 1999/01/21 01:16:59 dlt Exp $
s 2064 -256 100 0 General Environment Command
s 128 1872 300 0 Schematic to implement the Environment Commands
s 1728 1280 100 0 Note that outputs are driven from the start link of the 
s 1728 1248 100 0 CAD. The output links of the CAD can't be used directly
s 1728 1216 100 0 as these fire off whether the command is accepted or not.
s -16 416 100 0 The CAD routine writes out three versions of the output
s -16 384 100 0 data. These three versions may all be in different units.
[cell use]
use eaos 1048 728 100 0 Current
xform 0 1152 816
p 1072 910 100 0 -1 DESC:Output for SAD
p 768 798 100 0 0 OMSL:closed_loop
p 768 670 100 0 0 PREC:1
p 1376 782 100 0 -1 def(OUT):$(currout)
p 1312 720 100 1024 1 name:$(tcs)$(cad)$(I)
p 1280 784 75 768 -1 pproc(OUT):PP
use eaos 1032 1240 100 0 Slow
xform 0 1136 1328
p 1040 1422 100 0 -1 DESC:Output for slow loop
p 752 1310 100 0 0 OMSL:closed_loop
p 752 1182 100 0 0 PREC:1
p 1360 1294 100 0 -1 def(OUT):$(slowout)
p 1232 1232 100 1024 1 name:$(tcs)$(cad)$(I)
p 1264 1296 75 768 -1 pproc(OUT):PP
use eaos 1032 984 100 0 Other
xform 0 1136 1072
p 1072 1166 100 0 -1 DESC:Other output
p 752 1054 100 0 0 OMSL:closed_loop
p 1360 1054 100 0 -1 def(OUT):$(otherout)
p 1312 976 100 1024 1 name:$(tcs)$(cad)$(I)
use ecad8 248 600 100 0 ecad8#23
xform 0 384 1104
p 336 1310 100 0 1 FTVA:DOUBLE
p 336 1278 100 0 1 FTVB:DOUBLE
p 336 1246 100 0 1 FTVC:DOUBLE
p 304 782 100 0 1 SNAM:$(snam)
p 640 1326 100 0 0 def(OUTA):0.0
p 640 1262 100 0 0 def(OUTB):0.0
p 288 542 100 0 1 name:$(tcs)$(cad)
p 544 1328 75 768 -1 pproc(OUTA):NPP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 2056 1416 100 0 MESS
xform 0 2048 1456
use outhier 1896 1512 100 0 VAL
xform 0 1888 1552
use inhier -168 1416 100 0 ICID
xform 0 -176 1456
use inhier -168 1512 100 0 DIR
xform 0 -176 1552
[comments]
