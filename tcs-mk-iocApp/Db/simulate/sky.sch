[schematic2]
uniq 71
[tools]
[detail]
w 936 1131 100 0 n#70 eaos.oscperiod.VAL 768 768 832 768 832 1120 1088 1120 egenSubD.getProbe.INPN
w 680 1163 100 0 n#69 eaos.seeingperiod.VAL 192 768 320 768 320 1152 1088 1152 egenSubD.getProbe.INPM
w 664 1195 100 0 n#68 eaos.seeing.VAL 192 1024 288 1024 288 1184 1088 1184 egenSubD.getProbe.INPL
w 616 1291 100 0 n#67 eaos.oscamp.VAL 192 1280 1088 1280 egenSubD.getProbe.INPI
w 896 1323 100 0 n#66 eaos.cebase.VAL 672 1600 752 1600 752 1312 1088 1312 egenSubD.getProbe.INPH
w 656 1355 100 0 n#65 eaos.cabase.VAL 192 1600 272 1600 272 1344 1088 1344 egenSubD.getProbe.INPG
w 1624 843 100 0 n#57 egenSubD.getProbe.FLNK 1376 800 1472 800 1472 832 1824 832 egenSubD.simulate.SLNK
w 1440 1915 100 0 n#18 egenSub.genStars.FLNK 1120 1888 1328 1888 1328 1904 1600 1904 egenSub.displayCat.SLNK
w 936 1787 100 0 n#18 egenSub.getStars.FLNK 352 1904 592 1904 592 1776 1328 1776 1328 1888 junction
s 2224 2832 100 0 $Id: sky.sch,v 1.5 2006/04/21 09:49:08 cjm Exp $
s 960 1680 100 0 Inputs G,H and I are initialised on startup by pvload
s 976 1648 100 0 Inputs G and H are the base values of CA and CE
s 976 1616 100 0 Input I is the random component of Ca and CE
[cell use]
use eaos -64 935 100 0 seeing
xform 0 64 1024
p -48 1120 100 0 -1 DESC:Rms seeing value
p -320 782 100 0 0 DRVH:3.0
p -96 750 100 0 0 EGU:arcsec
p -320 846 100 0 0 EGUF:3.0
p -320 878 100 0 0 PREC:2
p 48 928 100 1024 0 name:$(top)sky:$(I)
use eaos -64 1511 100 0 cabase
xform 0 64 1600
p -48 1696 100 0 -1 DESC:Base CA value
p -320 1358 100 0 0 DRVH:0.0
p -96 1326 100 0 0 EGU:arcsec
p -320 1422 100 0 0 EGUF:0.0
p -320 1454 100 0 0 PREC:2
p 48 1504 100 1024 0 name:$(top)sky:$(I)
use eaos 416 1511 100 0 cebase
xform 0 544 1600
p 432 1696 100 0 -1 DESC:Base CE value
p 160 1358 100 0 0 DRVH:0.0
p 384 1326 100 0 0 EGU:arcsec
p 160 1422 100 0 0 EGUF:0.0
p 160 1454 100 0 0 PREC:2
p 528 1504 100 1024 0 name:$(top)sky:$(I)
use eaos -64 1191 100 0 oscamp
xform 0 64 1280
p -80 1360 100 0 -1 DESC:Mount oscillation amplitude
p -320 1038 100 0 0 DRVH:3.0
p -96 1006 100 0 0 EGU:arcsec
p -320 1102 100 0 0 EGUF:3.0
p -320 1134 100 0 0 PREC:2
p 48 1184 100 1024 0 name:$(top)sky:$(I)
use eaos 512 679 100 0 oscperiod
xform 0 640 768
p 496 848 100 0 -1 DESC:Mount oscillation period
p 256 526 100 0 0 DRVH:20.0
p 480 494 100 0 0 EGU:secs
p 256 590 100 0 0 EGUF:20.0
p 256 622 100 0 0 PREC:2
p 624 672 100 1024 0 name:$(top)sky:$(I)
use eaos -64 679 100 0 seeingperiod
xform 0 64 768
p -80 848 100 0 -1 DESC:Seeing period
p -320 526 100 0 0 DRVH:20.0
p -96 494 100 0 0 EGU:secs
p -320 590 100 0 0 EGUF:20.0
p -320 622 100 0 0 PREC:2
p 48 672 100 1024 0 name:$(top)sky:$(I)
use egenSubD 1088 743 100 0 getProbe
xform 0 1232 1168
p 800 1294 100 0 0 PREC:14
p 1216 736 100 0 1 SNAM:tcsSkyGetProbe
p 960 1536 100 0 -1 def(INPA):$(ag)p1:x
p 960 1504 100 0 -1 def(INPB):$(ag)p1:y
p 960 1472 100 0 -1 def(INPC):$(ag)p2:x
p 960 1440 100 0 -1 def(INPD):$(ag)p2:y
p 960 1408 100 0 -1 def(INPE):$(ag)oi:x
p 960 1376 100 0 -1 def(INPF):$(ag)oi:y
p 816 1248 100 0 -1 def(INPJ):$(top)om:ceOpticsSky
p 816 1216 100 0 -1 def(INPK):$(top)om:caOpticsSky
p 1200 736 100 1024 0 name:$(top)sky:$(I)
use egenSubD 1848 744 100 0 simulate
xform 0 1968 1168
p 1667 1483 100 0 0 DESC:Simulate sky data
p 1536 1182 100 0 0 EFLG:ON CHANGE
p 1601 517 100 0 0 FTK:LONG
p 1601 517 100 0 0 FTL:LONG
p 1601 485 100 0 0 FTM:LONG
p 1601 453 100 0 0 FTN:LONG
p 1601 69 100 0 0 NON:1
p 1601 37 100 0 0 NOO:12
p 1601 165 100 0 0 NOVA:58
p 1601 69 100 0 0 NOVD:8
p 1601 37 100 0 0 NOVE:8
p 1601 5 100 0 0 NOVF:8
p 1601 -27 100 0 0 NOVG:8
p 1536 1294 100 0 0 PREC:14
p 1904 1118 100 0 -1 SNAM:tcsSkySimulate
p 1552 1534 100 0 -1 def(INPA):$(tcs)m2Scale
p 1552 1502 100 0 -1 def(INPB):$(mc)followA.VALA
p 1552 1470 100 0 -1 def(INPC):$(mc)followA.VALB
p 1552 1438 100 0 -1 def(INPD):$(mc)followA.VALC
p 1488 1406 100 0 -1 def(INPE):$(tcs)ak:pm:par3:value
p 1552 1374 100 0 -1 def(INPF):$(cr)followA.VALA
p 1552 1342 100 0 -1 def(INPG):$(cr)followA.VALB
p 1552 1310 100 0 -1 def(INPH):$(cr)followA.VALC
p 1568 1278 100 0 -1 def(INPI):$(m2)xTiltPos.VAL
p 1568 1246 100 0 -1 def(INPJ):$(m2)yTiltPos.VAL
p 1536 1214 100 0 -1 def(INPK):$(pwfs1)measuring
p 1536 1182 100 0 -1 def(INPL):$(pwfs2)measuring
p 1536 1152 100 0 -1 def(INPM):$(oiwfs)measuring
p 1552 1120 100 0 -1 def(INPN):$(nici)measuring
p 1488 1056 100 0 -1 def(INPO):$(tcs)ak:astCtx.VALB
p 1488 1056 100 0 0 def(INPP):0.0000000000000e+00
p 1440 1024 100 0 -1 def(INPQ):$(tcs)drives:driveM2S.VALH
p 1440 992 100 0 -1 def(INPR):$(tcs)drives:driveM2S.VALI
p 2224 1470 100 0 0 def(OUTB):0.000000000000000e+00
p 2224 1406 100 0 0 def(OUTC):0.0000000000000000+00
p 1936 736 100 1024 0 name:$(top)sky:$(I)
use simSwitch 2360 840 100 0 simSwitch#22
xform 0 2496 1008
p 2320 830 100 0 1 seta:subsys sky:
p 2320 798 100 0 1 setb:scanloc $(top)$(subsys)getProbe.SCAN
use egenSub 88 1848 100 0 getStars
xform 0 208 2272
p -159 1621 100 0 0 FTA:DOUBLE
p -159 1365 100 0 0 FTJ:STRING
p -159 1269 100 0 0 NOA:1
p -159 981 100 0 0 NOJ:1
p -159 1237 100 0 0 NOVB:20
p -159 1205 100 0 0 NOVC:20
p -159 1173 100 0 0 NOVD:
p -159 981 100 0 0 NOVJ:1
p -159 949 100 0 0 PV:$(top)sky:
p 144 2190 100 0 -1 SNAM:tcsSkyGetStars
p -224 2608 100 0 -1 def(INPA):$(tcs)sourceA.VALC
p -224 2544 100 0 -1 def(INPB):$(tcs)sourceA.VALD
p 16 2618 75 0 -1 pproc(INPA):NPP
use egenSub 832 1831 100 0 genStars
xform 0 976 2256
p 609 1573 100 0 0 FTC:LONG
p 609 1605 100 0 0 FTVA:DOUBLE
p 609 1221 100 0 0 NOVB:1
p 609 1189 100 0 0 NOVC:1
p 629 945 100 0 0 PV:$(top)sky:
p 544 2206 100 0 0 SNAM:tcsSkyGenStars
p 528 2592 100 0 -1 def(INPA):$(tcs)sourceA.VALC
p 528 2544 100 0 -1 def(INPB):$(tcs)sourceA.VALD
use egenSub 1600 1815 100 0 displayCat
xform 0 1744 2240
p 1377 1589 100 0 0 FTVA:LONG
p 1377 1205 100 0 0 NOVB:20
p 1377 1173 100 0 0 NOVC:20
p 1397 929 100 0 0 PV:$(top)sky:
p 1312 2190 100 0 0 SNAM:tcsSkyDisplayCat
use bc200tr -352 360 -100 0 frame
xform 0 1328 1664
[comments]
