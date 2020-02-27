[schematic2]
uniq 98
[tools]
[detail]
w 1068 972 100 0 n#97 ecad8.ecad8#0.STLK 857 961 1328 961 1328 1600 1504 1600 eaos.RminCopy.SLNK
w 1624 1483 100 0 n#96 eaos.RminCopy.FLNK 1760 1632 1888 1632 1888 1472 1408 1472 1408 1312 1504 1312 eaos.RmaxCopy.SLNK
w 1028 1580 100 0 n#95 ecad8.ecad8#0.VALB 857 1569 1248 1569 1248 1344 1504 1344 eaos.RmaxCopy.DOL
w 1172 1643 100 0 n#94 ecad8.ecad8#0.VALA 857 1633 889 1633 889 1632 1504 1632 eaos.RminCopy.DOL
w 1928 1291 100 0 n#93 eaos.RmaxCopy.OUT 1760 1280 2144 1280 eaos.Rmax.SLNK
w 1928 1579 100 0 n#92 eaos.RminCopy.OUT 1760 1568 2144 1568 eaos.Rmin.SLNK
w 1028 1797 100 0 n#18 ecad8.ecad8#0.MESS 857 1793 1248 1793 1248 1728 1376 1728 outhier.MESS.p
w 1092 1829 100 0 n#17 ecad8.ecad8#0.VAL 857 1825 1376 1825 1376 1824 outhier.VAL.p
w 322 1715 100 0 n#4 inhier.ICID.P 228 1713 452 1713 452 1793 537 1793 ecad8.ecad8#0.ICID
w 322 1859 100 0 n#3 inhier.DIR.P 228 1857 452 1857 452 1825 537 1825 ecad8.ecad8#0.DIR
s 160 2080 100 0 confusing so the command was split into two.
s 160 2112 100 0 for both probes at the same time. This was found
s 160 2144 100 0 Note, this schematic used to set the limits
s 656 512 100 0 clear and start.
s 640 544 100 0 is not an option as these would fire for both 
s 640 576 100 0 Driving the ao records direct from the output links
s 640 608 100 0 successful start from setting all the ao records to 0.0.
s 640 640 100 0 This in particular prevents a clear issued before a 
s 640 672 100 0 The ao records are only triggerred by a successful start.
s 2704 400 100 0 Gemini Telescope Control System
s 2448 2592 100 0 $Id: tcsCadSetProbeLimits.sch,v 1.3 2009/10/30 17:34:23 cjm Exp $
s 2016 1072 100 0 N.B. These records are also written to by the state program
s 2016 1040 100 0 tcsSeqInit. This happens whenever the state program detects a change
s 2016 1008 100 0 in the physical limits held by the A&G and these limits are
s 2016 976 100 0 in conflict with the user limits set by this CAD.
s 160 2368 100 0 This schematic implements the setProbeLimits CAD command. Which
s 160 2336 100 0 allows the user to specify user limits for the radial limits
s 160 2304 100 0 of both PWFS1 and PWFS2.
s 160 2240 100 0 The CAD record checks the limits input for consistency with the physical 
s 160 2208 100 0 limits returned from the A&G subsystem.
s 2016 928 100 0 The records RminCopy and RmaxCopy are needed as they need to 
s 2016 896 100 0 operate in closed_loop whereas the records Rmin and Rmax
s 2016 864 100 0 have to be supervisory if they are to be written to by the sequence program.
[cell use]
use bc200tr -112 120 -100 0 frame
xform 0 1568 1424
use eaos 2144 1479 100 0 Rmin
xform 0 2272 1568
p 2128 1664 100 0 -1 DESC:Min. allowed radius of $(wfs)
p 2112 1294 100 0 0 EGU:mm
p 1888 1006 100 0 0 MDEL:0.005
p 1888 1550 100 0 0 OMSL:supervisory
p 1888 1422 100 0 0 PREC:2
p 2480 1536 100 0 -1 def(OUT):$(sad)$(wfs)Rmin
p 2240 1520 100 1024 0 name:$(tcs)$(wfs)$(I)
p 2400 1536 75 768 -1 pproc(OUT):PP
use eaos 2144 1191 100 0 Rmax
xform 0 2272 1280
p 2128 1376 100 0 -1 DESC:Max. allowed radius of $(wfs)
p 2112 1006 100 0 0 EGU:mm
p 1888 718 100 0 0 MDEL:0.005
p 1888 1262 100 0 0 OMSL:supervisory
p 1888 1134 100 0 0 PREC:2
p 2480 1248 100 0 -1 def(OUT):$(sad)$(wfs)Rmax
p 2240 1232 100 1024 0 name:$(tcs)$(wfs)$(I)
p 2400 1248 75 768 -1 pproc(OUT):PP
use eaos 1504 1511 100 0 RminCopy
xform 0 1632 1600
p 1488 1696 100 0 -1 DESC:Min. allowed radius of $(wfs)
p 1472 1326 100 0 0 EGU:mm
p 1248 1038 100 0 0 MDEL:0.005
p 1248 1582 100 0 0 OMSL:closed_loop
p 1248 1454 100 0 0 PREC:2
p 1840 1568 100 0 0 def(OUT):0.0
p 1600 1552 100 1024 0 name:$(tcs)$(wfs)$(I)
p 1504 1568 75 1280 -1 palrm(SDIS):NMS
p 1760 1568 75 768 -1 pproc(OUT):PP
use eaos 1504 1223 100 0 RmaxCopy
xform 0 1632 1312
p 1488 1408 100 0 -1 DESC:Max. allowed radius of $(wfs)
p 1472 1038 100 0 0 EGU:mm
p 1248 750 100 0 0 MDEL:0.005
p 1248 1294 100 0 0 OMSL:closed_loop
p 1248 1166 100 0 0 PREC:2
p 1840 1280 100 0 0 def(OUT):0.0
p 1600 1264 100 1024 0 name:$(tcs)$(wfs)$(I)
p 1504 1280 75 1280 -1 palrm(SDIS):NMS
p 1760 1280 75 768 -1 pproc(OUT):PP
use outhier 1368 1688 100 0 MESS
xform 0 1360 1728
use outhier 1368 1784 100 0 VAL
xform 0 1360 1824
use inhier 236 1673 100 0 ICID
xform 0 228 1713
use inhier 236 1817 100 0 DIR
xform 0 228 1857
use ecad8 561 873 100 0 ecad8#0
xform 0 697 1377
p 553 1919 100 0 -1 DESC:Implement the setProbeLimits command
p 640 1600 100 0 1 FTVA:DOUBLE
p 640 1568 100 0 1 FTVB:DOUBLE
p 640 1536 100 0 0 FTVC:STRING
p 640 1504 100 0 0 FTVD:STRING
p 633 1441 100 0 0 FTVE:STRING
p 633 1217 100 0 0 PREC:3
p 633 1087 100 0 1 SNAM:$(snam)
p 677 801 100 1024 1 name:$(tcs)$(cad)
p 857 1601 75 768 -1 pproc(OUTA):NPP
p 857 1537 75 768 -1 pproc(OUTB):NPP
p 857 1473 75 768 -1 pproc(OUTC):NPP
p 857 1409 75 768 -1 pproc(OUTD):NPP
[comments]
