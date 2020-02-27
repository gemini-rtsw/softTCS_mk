[schematic2]
uniq 17
[tools]
[detail]
w 1832 619 100 0 n#1 ecad20.dataODGW.OUTJ 1392 1088 1600 1088 1600 608 2112 608 gsaoiProbe.gsaoiProbe#9.Y
w 1848 683 100 0 n#2 ecad20.dataODGW.OUTI 1392 1152 1632 1152 1632 672 2112 672 gsaoiProbe.gsaoiProbe#9.X
w 1856 971 100 0 n#3 ecad20.dataODGW.OUTH 1392 1216 1664 1216 1664 960 2096 960 gsaoiProbe.gsaoiProbe#8.Y
w 1872 1035 100 0 n#4 ecad20.dataODGW.OUTG 1392 1280 1696 1280 1696 1024 2096 1024 gsaoiProbe.gsaoiProbe#8.X
w 1888 1291 100 0 n#5 ecad20.dataODGW.OUTF 1392 1344 1728 1344 1728 1280 2096 1280 gsaoiProbe.gsaoiProbe#7.Y
w 1552 1419 100 0 n#6 ecad20.dataODGW.OUTE 1392 1408 1760 1408 1760 1344 2096 1344 gsaoiProbe.gsaoiProbe#7.X
w 1824 1579 100 0 n#7 ecad20.dataODGW.OUTD 1392 1472 1600 1472 1600 1568 2096 1568 gsaoiProbe.gsaoiProbe#6.Y
w 1808 1643 100 0 n#8 ecad20.dataODGW.OUTC 1392 1536 1568 1536 1568 1632 2096 1632 gsaoiProbe.gsaoiProbe#6.X
w 1800 1867 100 0 n#9 ecad20.dataODGW.OUTA 1392 1664 1536 1664 1536 1856 2112 1856 eaos.d_gdr_winSizeS.SLNK
w -32 1083 100 0 n#10 ebos.startLoop.VAL -96 1072 80 1072 efanouts.startFan.SDIS
w -142 738 100 0 n#11 gsaoiSystem.gsaoiSystem#49.FLNK -152 728 -64 728 -64 264 40 264 esels.bdValsSel.SLNK
w -150 346 100 0 n#11 gsaoiSimFilters.gsaoiSimFilters#50.FLNK -160 336 -64 336 junction
w -142 674 100 0 n#12 gsaoiSystem.gsaoiSystem#49.VAL -152 664 -48 664 -48 648 40 648 esels.bdValsSel.INPA
w -150 282 100 0 n#13 gsaoiSimFilters.gsaoiSimFilters#50.VAL -160 272 -96 272 -96 616 40 616 esels.bdValsSel.INPB
w 338 514 100 0 n#14 esels.bdValsSel.FLNK 328 504 384 504 384 464 432 464 eaos.bdValOut.SLNK
w 338 482 100 0 n#15 esels.bdValsSel.VAL 328 472 360 472 360 496 432 496 eaos.bdValOut.DOL
w 698 442 100 0 n#16 eaos.bdValOut.OUT 688 432 728 432 728 320 328 320 328 224 432 224 ecars.activeC.IVAL
s 2016 -192 100 0 Sciences Ltd.
s 2016 -160 100 0 Observatory
s 2016 -128 100 0 Copyright
s 2032 2064 100 0 $Id: gsaoi.sch,v 1.10 2010/06/15 14:08:13 cjm Exp $
[cell use]
use bc200tr -560 -408 -100 0 frame
xform 0 1120 896
use gsaoiSystem -376 543 100 0 gsaoiSystem#49
xform 0 -264 664
use gsaoiseqODGW 1680 -41 100 0 gsaoiseqODGW#36
xform 0 1792 240
use ecad20 1072 167 100 0 dataODGW
xform 0 1232 1056
p 1168 1792 100 0 0 DESC:GSAOI ODGW Data Command
p 1216 127 100 0 1 SNAM:tcsGsaoidataODGWCAD
p 1184 160 100 1024 0 name:$(gsaoi)dc:$(I)
p 1392 1664 75 768 -1 pproc(OUTA):PP
p 1392 1600 75 768 -1 pproc(OUTB):PP
p 1392 1536 75 768 -1 pproc(OUTC):PP
p 1392 1408 75 768 -1 pproc(OUTE):PP
p 1392 1344 75 768 -1 pproc(OUTF):PP
p 1392 1280 75 768 -1 pproc(OUTG):PP
p 1392 1152 75 768 -1 pproc(OUTI):PP
p 1392 1088 75 768 -1 pproc(OUTJ):PP
p 1392 1024 75 768 -1 pproc(OUTK):PP
p 1392 896 75 768 -1 pproc(OUTM):PP
p 1392 832 75 768 -1 pproc(OUTN):PP
p 1392 768 75 768 -1 pproc(OUTO):PP
p 1392 640 75 768 -1 pproc(OUTQ):PP
p 1400 1480 75 768 -1 pproc(OUTD):PP
p 1400 1224 75 768 -1 pproc(OUTH):PP
use eaos 2112 1767 100 0 d_gdr_winSizeS
xform 0 2240 1856
p 2128 1952 100 0 -1 DESC:Extent of guide region
p 2080 1582 100 0 0 EGU:pixels
p 2224 1760 100 1024 0 name:$(prefix)sad:dc:$(I)
use efanouts 80 903 100 0 startFan
xform 0 200 1056
p -34 1321 100 0 0 DESC:Simulator fanout
p -32 976 100 0 1 SCAN:.05 second
p 192 896 100 1024 0 name:$(prefix)$(I)
use ebos -352 983 100 0 startLoop
xform 0 -224 1072
p -584 1228 100 0 0 DESC:Disable/enable simulation loop
p -672 926 100 0 0 ONAM:enabled
p -672 958 100 0 0 ZNAM:disabled
p -240 976 100 1024 0 name:$(prefix)$(I)
use simSwitch -256 1607 100 0 simSwitch#13
xform 0 -96 1776
p -236 1580 100 0 1 seta:scanloc $(prefix)startFan.SCAN
use gsaoiProbe 2064 1415 100 0 gsaoiProbe#6
xform 0 2256 1568
p 2176 1728 100 0 -1 seta:top $(prefix)sad:dc:
p 2176 1696 100 0 -1 setb:window 1
use gsaoiProbe 2064 1127 100 0 gsaoiProbe#7
xform 0 2256 1280
p 2176 1440 100 0 -1 seta:top $(prefix)sad:dc:
p 2176 1408 100 0 -1 setb:window 2
use gsaoiProbe 2064 807 100 0 gsaoiProbe#8
xform 0 2256 960
p 2192 1120 100 0 -1 seta:top $(prefix)sad:dc:
p 2176 1072 100 0 -1 setb:window 3
use gsaoiProbe 2080 455 100 0 gsaoiProbe#9
xform 0 2272 608
p 2176 768 100 0 -1 seta:top $(prefix)sad:dc:
p 2176 736 100 0 -1 setb:window 4
use gsaoiSimFilters -384 176 100 0 gsaoiSimFilters#50
xform 0 -272 272
p -370 399 100 0 1 seta:prefix $(prefix)cc:
p -368 429 100 0 1 setc:
use esels 102 189 100 0 bdValsSel
xform 0 184 456
p 152 184 100 1024 0 name:$(prefix)$(I)
p 106 517 100 0 1 SELM:High Signal
use ecars 497 -58 100 0 activeC
xform 0 592 112
p 544 -64 100 1024 0 name:$(prefix)$(I)
use eaos 500 373 100 0 bdValOut
xform 0 560 464
p 696 440 75 768 -1 pproc(OUT):PP
p 491 543 100 0 1 OMSL:closed_loop
p 544 368 100 1024 0 name:$(prefix)$(I)
[comments]
