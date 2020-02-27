[schematic2]
uniq 13
[tools]
[detail]
w 6092 1715 100 0 n#1 eais.dzNoAo.VAL 5736 1704 6128 1704 6128 1704 6304 1704 egenSub.setOffsets.INPA
w 5746 1466 100 0 n#2 eais.dzAo.VAL 5736 1456 5792 1456 5792 1640 6304 1640 egenSub.setOffsets.INPB
w 5746 1274 100 0 n#3 eais.dzProbe.VAL 5736 1264 5872 1264 5872 1576 6304 1576 egenSub.setOffsets.INPC
w 5754 1050 100 0 n#4 eais.dzGsaoi.VAL 5744 1040 5944 1040 5944 1512 6304 1512 egenSub.setOffsets.INPD
w 5746 786 100 0 n#5 elongins.useGSAOIOffsets.VAL 5736 776 6016 776 6016 1448 6304 1448 egenSub.setOffsets.INPE
w 5738 570 100 0 n#6 eais.dxGsaoi.VAL 5728 560 6080 560 6080 1384 6304 1384 egenSub.setOffsets.INPF
w 5738 362 100 0 n#7 eais.dyGsaoi.VAL 5728 352 6136 352 6136 1320 6304 1320 egenSub.setOffsets.INPG
w 6602 1714 100 0 n#8 egenSub.setOffsets.OUTA 6592 1704 6856 1704 6856 1704 elongouts.usingGSAOI.SLNK
w 5738 394 100 0 n#9 eais.dyGsaoi.FLNK 5728 384 5792 384 5792 240 5392 240 5392 128 5472 128 estringins.vfiltName.SLNK
w 6602 1682 100 0 n#10 egenSub.setOffsets.VALB 6592 1672 6768 1672 6768 1552 7344 1552 eaos.aomFocusOffset.DOL
w 7114 1746 100 0 n#11 elongouts.usingGSAOI.FLNK 7104 1736 7216 1736 7216 1520 7344 1520 eaos.aomFocusOffset.SLNK
w 7122 1714 100 0 n#12 elongouts.usingGSAOI.VAL 7112 1704 7192 1704 7192 1488 7336 1488 eaos.aomFocusOffset.SDIS
s 5632 1952 200 0 Fetch and store the various focus offsets from the A&G or GSAOI
s 7424 -48 100 0 Gemini Telescope Control System
s 7168 2144 100 0 $Id: tcsReadAgOffsets.sch,v 1.5 2010/11/29 14:22:46 cjm Exp $
s 7424 -112 100 0 Schematic to read A&G data
[cell use]
use bc200tr 4592 -328 -100 0 frame
xform 0 6272 976
use eais 5480 1207 100 0 dzProbe
xform 0 5608 1280
p 5416 1360 100 0 -1 DESC:Probe offset
p 5224 1022 100 0 0 EGU:mm
p 5224 1118 100 0 0 PREC:2
p 5160 1312 100 0 -1 def(INP):$(ag)oi:dzProbe
p 5480 1312 75 1280 -1 palrm(INP):MS
p 5448 1312 75 1280 -1 pproc(INP):CPP
use eais 5480 1399 100 0 dzAo
xform 0 5608 1472
p 5416 1552 100 0 -1 DESC:Focus offset with Altair
p 5224 1214 100 0 0 EGU:mm
p 5224 1310 100 0 0 PREC:2
p 5160 1504 100 0 -1 def(INP):$(ag)oi:dzAo
p 5480 1504 75 1280 -1 palrm(INP):MS
p 5448 1504 75 1280 -1 pproc(INP):CPP
use eais 5480 1647 100 0 dzNoAo
xform 0 5608 1720
p 5416 1800 100 0 -1 DESC:Focus offset without Altair
p 5224 1462 100 0 0 EGU:mm
p 5224 1558 100 0 0 PREC:2
p 5160 1752 100 0 -1 def(INP):$(ag)oi:dzNoAo
p 5480 1752 75 1280 -1 palrm(INP):MS
p 5448 1752 75 1280 -1 pproc(INP):CPP
use egenSub 6304 943 100 0 setOffsets
xform 0 6448 1368
p 6336 1800 100 0 -1 DESC:Store focus offsets
p 6448 824 100 0 1 SCAN:1 second
p 6464 904 100 0 1 SNAM:tcsProbeSetOffsets
p 6081 621 100 0 0 FTE:LONG
p 6081 717 100 0 0 FTVA:LONG
p 6600 1714 75 0 -1 pproc(OUTA):PP
use elongins 5467 701 100 0 useGSAOIOffsets
xform 0 5608 792
use eais 5552 977 100 0 dzGsaoi
xform 0 5616 1056
p 5232 798 100 0 0 EGU:mm
p 5416 1096 75 1280 -1 pproc(INP):CPP
p 5159 1094 100 0 -1 def(INP):$(gsaoi)sad:cc:defocusZ
use eais 5536 497 100 0 dxGsaoi
xform 0 5600 576
p 5216 318 100 0 0 EGU:arcsecs
p 5400 616 75 1280 -1 pproc(INP):CPP
p 5143 614 100 0 -1 def(INP):$(gsaoi)sad:cc:defocusX
use eais 5536 289 100 0 dyGsaoi
xform 0 5600 368
p 5216 110 100 0 0 EGU:arcsecs
p 5400 408 75 1280 -1 pproc(INP):CPP
p 5143 406 100 0 -1 def(INP):$(gsaoi)sad:cc:defocusY
use elongouts 6905 1606 100 0 usingGSAOI
xform 0 6984 1704
p 6912 1788 100 0 -1 DESC:Is GSAOI in use
use estringins 5537 42 100 0 vfiltName
xform 0 5600 128
p 5526 294 100 0 0 DESC:Name of selected GSAOI filter
p 5153 160 100 0 -1 def(INP):$(gsaoi)sad:cc:vfiltName
p 5400 168 75 1280 -1 pproc(INP):CPP
use eaos 7416 1428 100 0 aomFocusOffset
xform 0 7472 1520
p 7353 1607 100 0 -1 DESC:Focus offset for AOM Zoom
p 7088 1214 100 0 0 DISV:0
p 7088 1502 100 0 0 OMSL:closed_loop
p 7608 1496 75 768 -1 pproc(OUT):CA
p 7675 1466 100 0 -1 def(OUT):$(aom)FOC_offset
[comments]
