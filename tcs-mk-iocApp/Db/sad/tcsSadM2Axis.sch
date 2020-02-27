[schematic2]
uniq 17
[tools]
[detail]
w 4096 2050 100 0 n#16 esirs.ErrorCorr.FLNK 4016 2048 4224 2048 outhier.FLNK.p
w 3456 1890 100 0 n#15 esirs.Pos.FLNK 3184 2048 3360 2048 3360 1888 3600 1888 esirs.ErrorCorr.SLNK
w 2592 1890 100 0 n#12 esirs.Demand.FLNK 2336 2048 2464 2048 2464 1888 2768 1888 esirs.Pos.SLNK
w 2990 2290 100 0 n#9 esirs.ModelCorr.FLNK 4096 2672 4224 2672 4224 2288 1792 2288 1792 1888 1920 1888 esirs.Demand.SLNK
w 1734 2514 100 0 n#5 inhier.SLNK.P 1584 2512 1920 2512 esirs.Nominal.SLNK
w 3478 2514 100 0 n#4 esirs.TempCorr.FLNK 3184 2672 3312 2672 3312 2512 3680 2512 esirs.ModelCorr.SLNK
w 2590 2514 100 0 n#3 esirs.Nominal.FLNK 2336 2672 2448 2672 2448 2512 2768 2512 esirs.TempCorr.SLNK
s 1872 1456 100 0 each time the relevant CAD record is executed
s 1872 1488 100 0 N.B. The user offset is not scanned but set instead
s 4032 3088 100 0 tcsSadM2Axis.sch
s 4176 832 100 0 TCS M2 Records for each axis
s 4160 896 100 0 Gemini Telescope Control System
[cell use]
use esirs 3624 1800 100 0 ErrorCorr
xform 0 3808 1952
p 3728 2126 100 0 -1 DESC:Axis error correction
p 3664 1694 100 0 1 EGU:$(units)
p 3536 1536 100 0 0 FDSC:Error correction to M2 axis
p 3536 1504 100 0 0 FTVL:DOUBLE
p 3536 1184 100 0 0 MDEL:0.0005
p 3792 1728 100 0 0 PREC:3
p 3376 2078 100 0 -1 def(INP):$(top)m2$(axis)ErrorCorr
p 3792 1744 100 1024 1 name:$(sad)m2$(axis)$(I)
use esirs 1944 1016 100 0 UserOffset
xform 0 2128 1168
p 2064 1342 100 0 -1 DESC:User offset
p 1984 910 100 0 1 EGU:$(units)
p 1856 752 100 0 0 FDSC:User offset applied to M2 axis
p 1856 720 100 0 0 FTVL:DOUBLE
p 1856 400 100 0 0 MDEL:0.0005
p 1871 656 100 0 0 PREC:3
p 1984 958 100 0 1 PV:$(sad)m2$(axis)
use esirs 1944 1800 100 0 Demand
xform 0 2128 1952
p 2048 2126 100 0 -1 DESC:Total axis demand
p 1984 1694 100 0 1 EGU:$(units)
p 1856 1504 100 0 0 FTVL:DOUBLE
p 1856 1184 100 0 0 MDEL:0.0005
p 2112 1728 100 0 0 PREC:3
p 1984 1742 100 0 1 PV:$(sad)m2$(axis)
p 1648 2046 100 0 -1 def(INP):$(rec1)$(field4)
use esirs 3704 2424 100 0 ModelCorr
xform 0 3888 2576
p 3776 2734 100 0 -1 DESC:Axis Model correction
p 3744 2334 100 0 1 EGU:$(units)
p 3616 2128 100 0 0 FTVL:DOUBLE
p 3616 1808 100 0 0 MDEL:0.0005
p 3872 2352 100 0 0 PREC:3
p 3744 2366 100 0 1 PV:$(sad)m2$(axis)
p 3392 2670 100 0 -1 def(INP):$(rec1)$(field3)
use esirs 2792 2424 100 0 TempCorr
xform 0 2976 2576
p 2832 2734 100 0 -1 DESC:Axis temperature correction
p 2832 2318 100 0 1 EGU:$(units)
p 2704 2128 100 0 0 FTVL:DOUBLE
p 2704 1808 100 0 0 MDEL:0.0005
p 2960 2352 100 0 0 PREC:3
p 2832 2366 100 0 1 PV:$(sad)m2$(axis)
p 2496 2670 100 0 -1 def(INP):$(rec1)$(field2)
use esirs 1944 2424 100 0 Nominal
xform 0 2128 2576
p 2016 2734 100 0 -1 DESC:Nominal axis position
p 2000 2318 100 0 1 EGU:$(units)
p 1856 2128 100 0 0 FTVL:DOUBLE
p 1856 1808 100 0 0 MDEL:0.0005
p 2112 2352 100 0 0 PREC:3
p 2000 2366 100 0 1 PV:$(sad)m2$(axis)
p 1632 2670 100 0 -1 def(INP):$(rec1)$(field1)
use esirs 2792 1800 100 0 Pos
xform 0 2976 1952
p 2896 2126 100 0 -1 DESC:Current Position
p 2832 1694 100 0 1 EGU:$(units)
p 2704 1504 100 0 0 FTVL:DOUBLE
p 2704 1184 100 0 0 MDEL:0.0005
p 2960 1728 100 0 0 PREC:3
p 2544 2078 100 0 -1 def(INP):$(top)m2$(axis)Pos
p 2960 1744 100 1024 1 name:$(sad)m2$(axis)$(I)
use inhier 1592 2472 100 0 SLNK
xform 0 1584 2512
use outhier 4216 2008 100 0 FLNK
xform 0 4208 2048
use bc200tr 1328 616 -100 0 frame
xform 0 3008 1920
[comments]
