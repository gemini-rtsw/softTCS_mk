[schematic2]
uniq 1515
[tools]
[detail]
w 5828 651 100 0 n#1514 estringins.oiGuideConfig.FLNK 5984 752 6080 752 6080 640 5648 640 5648 528 5728 528 estringins.aoGuideConfig.SLNK
w 5124 2139 100 0 n#1512 egenSub.driveM2S.OUTE 4864 2128 5456 2128 5456 1680 5664 1680 eais.ytiltChopB.SLNK
w 5140 2203 100 0 n#1511 egenSub.driveM2S.OUTD 4864 2192 5488 2192 5488 1936 5664 1936 eais.xtiltChopB.SLNK
w 5156 2267 100 0 n#1510 egenSub.driveM2S.OUTC 4864 2256 5520 2256 5520 2160 5664 2160 eais.ytiltChopA.SLNK
w 5156 2331 100 0 n#1509 egenSub.driveM2S.OUTB 4864 2320 5520 2320 5520 2384 5664 2384 eais.xtiltChopA.SLNK
w 5452 1275 100 0 n#1503 estringins.centralBaffle.FLNK 4928 976 5248 976 5248 1264 5728 1264 estringins.p1GuideConfig.SLNK
w 5828 891 100 0 n#1502 estringins.p2GuideConfig.FLNK 5984 1008 6080 1008 6080 880 5648 880 5648 752 5728 752 estringins.oiGuideConfig.SLNK
w 5828 1147 100 0 n#1501 estringins.p1GuideConfig.FLNK 5984 1264 6080 1264 6080 1136 5648 1136 5648 1008 5728 1008 estringins.p2GuideConfig.SLNK
w 4788 1115 100 0 n#1497 estringins.deployBaffle.FLNK 4928 1264 5056 1264 5056 1104 4592 1104 4592 976 4672 976 estringins.centralBaffle.SLNK
w 4436 1019 100 0 n#1496 inhier.c#1495.P 4272 1008 4672 1008 estringins.centralBaffle.INP
w 4436 1307 100 0 n#1493 inhier.c#1492.P 4272 1296 4672 1296 estringins.deployBaffle.INP
w 4972 1691 100 0 n#1489 egenSub.driveM2S.FLNK 4864 1680 5152 1680 outhier.FLNK.p
w 4388 1723 100 0 n#1488 inhier.SLNK.P 4272 1712 4576 1712 egenSub.driveM2S.SLNK
w 5116 2420 100 0 n#1333 egenSub.driveM2S.VALA 4864 2416 5440 2416 outhier.c#1332.p
s 6944 464 100 0 Drive M2 
s 6576 352 100 0 Chris Mayer
s 6576 400 100 0 Sciences Ltd.
s 6576 432 100 0 Observatory
s 6576 464 100 0 Copyright
s 6576 2656 100 0 $Id: tcsDriveM2.sch,v 1.3 2002/11/13 05:03:11 cjm Exp $
[cell use]
use estringins 5728 455 100 0 aoGuideConfig
xform 0 5856 528
p 5712 608 100 0 -1 DESC:Altair guide status
p 5728 622 100 0 0 VAL:
p 5328 560 100 0 -1 def(INP):$(m2)guideConfigProc.VALD
p 5728 560 75 1280 -1 palrm(INP):MS
p 5696 560 75 1280 -1 pproc(INP):CA
use estringins 5728 679 100 0 oiGuideConfig
xform 0 5856 752
p 5712 832 100 0 -1 DESC:OIWFS guide status
p 5728 846 100 0 0 VAL:
p 5328 784 100 0 -1 def(INP):$(m2)guideConfigProc.VALC
p 5728 784 75 1280 -1 palrm(INP):MS
p 5696 784 75 1280 -1 pproc(INP):CA
use estringins 5728 935 100 0 p2GuideConfig
xform 0 5856 1008
p 5712 1088 100 0 -1 DESC:PWFS2 guide status
p 5728 1102 100 0 0 VAL:
p 5328 1040 100 0 -1 def(INP):$(m2)guideConfigProc.VALB
p 5728 1040 75 1280 -1 palrm(INP):MS
p 5696 1040 75 1280 -1 pproc(INP):CA
use estringins 5728 1191 100 0 p1GuideConfig
xform 0 5856 1264
p 5712 1344 100 0 -1 DESC:PWFS1 guide status
p 5728 1358 100 0 0 VAL:
p 5328 1296 100 0 -1 def(INP):$(m2)guideConfigProc.VALA
p 5728 1296 75 1280 -1 palrm(INP):MS
p 5696 1296 75 1280 -1 pproc(INP):CA
use estringins 4672 903 100 0 centralBaffle
xform 0 4800 976
p 4656 1056 100 0 -1 DESC:Central baffle psoition
p 4672 1070 100 0 0 VAL:Unknown
p 4336 1024 100 0 -1 def(INP):$(m2)CentralBafflePos
p 4672 1008 75 1280 -1 palrm(INP):MS
p 4640 1008 75 1280 -1 pproc(INP):CA
use estringins 4672 1191 100 0 deployBaffle
xform 0 4800 1264
p 4640 1376 100 0 -1 DESC:Position of deployable baffle
p 4864 1152 100 0 1 SCAN:1 second
p 4672 1358 100 0 0 VAL:Unknown
p 4304 1344 100 0 -1 def(INP):$(m2)DeployBafflePos
p 4672 1296 75 1280 -1 palrm(INP):MS
p 4640 1296 75 1280 -1 pproc(INP):CA
use eais 5664 1607 100 0 ytiltChopB
xform 0 5792 1680
p 5408 1230 100 0 0 ADEL:0.005
p 5664 1776 100 0 -1 DESC:Chop B ytilt demand
p 5408 1422 100 0 0 EGU:arcsec
p 5408 1198 100 0 0 MDEL:0.005
use eais 5664 1863 100 0 xtiltChopB
xform 0 5792 1936
p 5408 1486 100 0 0 ADEL:0.005
p 5664 2032 100 0 -1 DESC:Chop B xtilt demand
p 5408 1678 100 0 0 EGU:arcsec
p 5408 1454 100 0 0 MDEL:0.005
use eais 5664 2311 100 0 xtiltChopA
xform 0 5792 2384
p 5408 1934 100 0 0 ADEL:0.005
p 5680 2464 100 0 -1 DESC:Chop A xtilt demand
p 5408 2126 100 0 0 EGU:arcsec
p 5408 1902 100 0 0 MDEL:0.005
use eais 5664 2087 100 0 ytiltChopA
xform 0 5792 2160
p 5408 1710 100 0 0 ADEL:0.005
p 5680 2224 100 0 -1 DESC:Chop A ytilt demand
p 5408 1902 100 0 0 EGU:arcsec
p 5408 1678 100 0 0 MDEL:0.005
use inhier 4256 967 100 0 c#1495
xform 0 4272 1008
use inhier 4256 1255 100 0 c#1492
xform 0 4272 1296
use inhier 4256 1671 100 0 SLNK
xform 0 4272 1712
use outhier 5120 1639 100 0 FLNK
xform 0 5136 1680
use outhier 5432 2376 100 0 c#1332
xform 0 5424 2416
use bc200tr 4000 184 -100 0 frame
xform 0 5680 1488
use egenSub 4600 1624 100 0 driveM2S
xform 0 4720 2048
p 4288 2190 100 0 0 DISV:1
p 5232 2430 100 0 -1 NOVA:14
p 4288 2174 100 0 0 PREC:14
p 4656 1854 100 0 -1 SNAM:tcsDriveM2S
p 4992 2430 100 0 -1 def(OUTA):$(m2)followA.J
p 4864 2394 75 0 -1 pproc(OUTA):CA
p 4864 2330 75 0 -1 pproc(OUTB):PP
p 4864 2266 75 0 -1 pproc(OUTC):PP
p 4864 2202 75 0 -1 pproc(OUTD):PP
p 4864 2138 75 0 -1 pproc(OUTE):PP
[comments]
