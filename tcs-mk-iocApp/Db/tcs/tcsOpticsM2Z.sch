[schematic2]
uniq 118
[tools]
[detail]
w 1922 1739 100 0 n#117 egenSub.M2ZValues.OUTA 1824 1728 2080 1728 eaos.m2ZInsOffset.SLNK
w 1290 1067 100 0 n#115 inhier.SLNK.P 1104 1056 1536 1056 egenSub.M2ZValues.SLNK
w 2034 1035 100 0 n#114 egenSub.M2ZValues.FLNK 1824 1024 2304 1024 outhier.FLNK.p
s 2592 2352 100 0 $Id: tcsOpticsM2Z.sch,v 1.1 2002/11/18 21:01:06 cjm Exp $
s 2896 96 100 0 Optics control system
s 2848 160 100 0 Gemini Telescope Control system
[cell use]
use eaos 2080 1639 100 0 m2ZInsOffset
xform 0 2208 1728
p 2032 1824 100 0 -1 DESC:Current instrument focus offset
p 2048 1454 100 0 0 EGU:mm
p 1824 1166 100 0 0 MDEL:0.0005
p 1824 1582 100 0 0 PREC:3
use outhier 2272 983 100 0 FLNK
xform 0 2288 1024
use inhier 1088 1015 100 0 SLNK
xform 0 1104 1056
use egenSub 1536 967 100 0 M2ZValues
xform 0 1680 1392
p 1379 1707 100 0 0 DESC:Provide status values
p 1696 912 100 0 1 SNAM:tcsOpticsM2ZValues
p 1824 1738 75 0 -1 pproc(OUTA):PP
use bc200tr 0 -120 -100 0 frame
xform 0 1680 1184
[comments]
