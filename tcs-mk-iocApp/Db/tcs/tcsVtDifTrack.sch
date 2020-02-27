[schematic2]
uniq 53
[tools]
[detail]
w 128 1227 100 0 n#52 inhier.VT.P -48 1216 352 1216 egenSub.SetDiff.INPA
w 128 555 100 0 n#51 inhier.SLNK.P -48 544 352 544 egenSub.SetDiff.SLNK
w 1016 267 100 0 n#50 egenSub.SetDiff.VALE 640 992 800 992 800 256 1280 256 eaos.DiffDec.DOL
w 1032 555 100 0 n#49 egenSub.SetDiff.VALD 640 1056 832 1056 832 544 1280 544 eaos.DiffRA.DOL
w 1048 875 100 0 n#48 egenSub.SetDiff.VALC 640 1120 864 1120 864 864 1280 864 eaos.DiffEpoch.DOL
w 792 1195 100 0 n#47 egenSub.SetDiff.VALB 640 1184 992 1184 992 1168 1280 1168 estringouts.DiffEquinox.DOL
w 1048 1467 100 0 n#46 egenSub.SetDiff.VALA 640 1248 864 1248 864 1456 1280 1456 estringouts.DiffFrame.DOL
w 808 523 100 0 n#45 egenSub.SetDiff.FLNK 640 512 1024 512 1024 1424 1280 1424 estringouts.DiffFrame.SLNK
w 1816 267 100 0 n#44 eaos.DiffDec.FLNK 1536 256 2144 256 outhier.FLNK.p
w 1376 386 100 0 n#35 eaos.DiffRA.FLNK 1536 544 1616 544 1616 384 1184 384 1184 224 1280 224 eaos.DiffDec.SLNK
w 1376 690 100 0 n#34 eaos.DiffEpoch.FLNK 1536 864 1616 864 1616 688 1184 688 1184 512 1280 512 eaos.DiffRA.SLNK
w 1376 1010 100 0 n#33 estringouts.DiffEquinox.FLNK 1536 1152 1616 1152 1616 1008 1184 1008 1184 832 1280 832 eaos.DiffEpoch.SLNK
w 1376 1282 100 0 n#32 estringouts.DiffFrame.FLNK 1536 1440 1616 1440 1616 1280 1184 1280 1184 1136 1280 1136 estringouts.DiffEquinox.SLNK
s 1792 -256 100 0 Sciences Ltd.
s 1792 -224 100 0 Observatory
s 1792 -192 100 0 Copyright
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 C. J. Mayer
s 1808 -336 100 0 4 August 2004
s 1792 2000 100 0 $Id: tcsVtDifTrack.sch,v 1.2 2005/12/23 14:22:10 cjm Exp $
[cell use]
use egenSub 352 455 100 0 SetDiff
xform 0 496 880
p 320 1312 100 0 -1 DESC:Update differential track items
p 129 229 100 0 0 FTA:LONG
p 129 229 100 0 0 FTVA:STRING
p 129 229 100 0 0 FTVB:STRING
p 64 1006 100 0 0 PREC:14
p 544 432 100 0 1 SNAM:tcsGetDiffTrack
p 464 448 100 1024 0 name:$(top)$(vt)$(I)
use eaos 1304 744 100 0 DiffEpoch
xform 0 1408 832
p 1328 926 100 0 -1 DESC:Reference epoch of differential track
p 1392 798 100 0 -1 EGU:MJD
p 1024 814 100 0 0 OMSL:closed_loop
p 1024 686 100 0 0 PREC:10
p 1632 798 100 0 -1 def(OUT):$(sad)$(vt)DiffEpoch
p 1552 736 100 1024 1 name:$(top)$(vt)$(I)
p 1536 800 75 768 -1 pproc(OUT):PP
use eaos 1304 424 100 0 DiffRA
xform 0 1408 512
p 1328 606 100 0 -1 DESC:Differential track rate in RA
p 1376 478 100 0 -1 EGU:sec/sec
p 1024 494 100 0 0 OMSL:closed_loop
p 1024 366 100 0 0 PREC:11
p 1616 478 100 0 -1 def(OUT):$(sad)$(vt)DiffRA
p 1536 416 100 1024 1 name:$(top)$(vt)$(I)
p 1536 480 75 768 -1 pproc(OUT):PP
use eaos 1304 136 100 0 DiffDec
xform 0 1408 224
p 1328 318 100 0 -1 DESC:Differential track rate in Dec.
p 1360 190 100 0 -1 EGU:arcsec/s
p 1024 206 100 0 0 OMSL:closed_loop
p 1024 78 100 0 0 PREC:10
p 1632 190 100 0 -1 def(OUT):$(sad)$(vt)DiffDec
p 1536 128 100 1024 1 name:$(top)$(vt)$(I)
p 1536 192 75 768 -1 pproc(OUT):PP
use estringouts 1304 1352 100 0 DiffFrame
xform 0 1408 1424
p 1296 1502 100 0 -1 DESC:Differential track frame
p 1216 1230 100 0 0 OMSL:closed_loop
p 1216 1390 100 0 0 VAL:Undefined
p 1632 1406 100 0 -1 def(OUT):$(sad)$(vt)DiffFrame
p 1568 1344 100 1024 1 name:$(top)$(vt)$(I)
p 1536 1408 75 768 -1 pproc(OUT):PP
use estringouts 1304 1064 100 0 DiffEquinox
xform 0 1408 1136
p 1296 1214 100 0 -1 DESC:Equinox of differential track frame
p 1216 942 100 0 0 OMSL:closed_loop
p 1216 1102 100 0 0 VAL:Undefined
p 1632 1118 100 0 -1 def(OUT):$(sad)$(vt)DiffEquinox
p 1568 1056 100 1024 1 name:$(top)$(vt)$(I)
p 1536 1120 75 768 -1 pproc(OUT):PP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 2136 216 100 0 FLNK
xform 0 2128 256
use inhier -40 1176 100 0 VT
xform 0 -48 1216
use inhier -32 496 100 0 SLNK
xform 0 -48 544
[comments]
