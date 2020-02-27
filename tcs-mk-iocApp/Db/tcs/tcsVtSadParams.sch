[schematic2]
uniq 99
[tools]
[detail]
w -304 1067 100 0 VT inhier.VT.P -400 1056 -160 1056 egenSubC.SetSAD.INPB
w 552 251 100 0 n#94 egenSubC.SetSAD.VALI 128 832 352 832 352 240 800 240 eaos.RV.DOL
w 1336 363 100 0 n#93 eaos.PMDec.FLNK 1968 576 2048 576 2048 352 672 352 672 208 800 208 eaos.RV.SLNK
w 904 395 100 0 n#91 egenSubC.SetSAD.VALH 128 864 384 864 384 384 1472 384 1472 576 1712 576 eaos.PMDec.DOL
w 584 555 100 0 n#90 egenSubC.SetSAD.VALG 128 896 416 896 416 544 800 544 eaos.PMRA.DOL
w 1360 555 100 0 n#89 eaos.PMRA.FLNK 1056 544 1712 544 eaos.PMDec.SLNK
w 1336 683 100 0 n#88 eaos.Parallax.FLNK 1968 864 2048 864 2048 672 672 672 672 512 800 512 eaos.PMRA.SLNK
w 936 715 100 0 n#85 egenSubC.SetSAD.VALF 128 928 448 928 448 704 1472 704 1472 864 1712 864 eaos.Parallax.DOL
w 1360 843 100 0 n#84 estringouts.estringouts#61.FLNK 1056 832 1712 832 eaos.Parallax.SLNK
w 280 1035 100 0 n#83 egenSubC.SetSAD.VALC 128 1024 480 1024 480 1264 784 1264 estringouts.InputFrame.DOL
w 280 971 100 0 n#82 egenSubC.SetSAD.VALE 128 960 480 960 480 848 800 848 estringouts.estringouts#61.DOL
w 1336 971 100 0 n#81 estringouts.Equinox.FLNK 1968 1264 2048 1264 2048 960 672 960 672 816 800 816 estringouts.estringouts#61.SLNK
w 776 1003 100 0 n#80 egenSubC.SetSAD.VALD 128 992 1472 992 1472 1280 1712 1280 estringouts.Equinox.DOL
w 1352 1259 100 0 n#79 estringouts.InputFrame.FLNK 1040 1248 1712 1248 estringouts.Equinox.SLNK
w 1336 1419 100 0 n#78 eaos.Dec.FLNK 1968 1632 2048 1632 2048 1408 672 1408 672 1232 784 1232 estringouts.InputFrame.SLNK
w 464 1579 100 0 n#77 egenSubC.SetSAD.FLNK 128 352 192 352 192 1568 784 1568 eaos.RA.SLNK
w 1352 1611 100 0 n#76 eaos.RA.FLNK 1040 1600 1712 1600 eaos.Dec.SLNK
w 696 1451 100 0 n#73 egenSubC.SetSAD.VALB 128 1056 288 1056 288 1440 1152 1440 1152 1632 1712 1632 eaos.Dec.DOL
w 496 1611 100 0 n#71 egenSubC.SetSAD.VALA 128 1088 256 1088 256 1600 784 1600 eaos.RA.DOL
s 1792 -256 100 0 Sciences Ltd.
s 1792 -224 100 0 Observatory
s 1792 -192 100 0 Copyright
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -304 100 0 C. J. Mayer
s 1808 -336 100 0 22 December 2006
s 1792 2000 100 0 $Id: tcsVtSadParams.sch,v 1.1 2007/01/09 10:16:25 cjm Exp $
s 480 1920 200 0 This schematic is invoked at the end of
s 480 1856 200 0 configuration checking if the configuration
s 480 1776 200 0 contains a planet or orbit command
[cell use]
use eaos 824 120 100 0 RV
xform 0 928 208
p 848 302 100 0 -1 DESC:Radial velocity
p 896 174 100 0 -1 EGU:km/s
p 544 190 100 0 0 OMSL:closed_loop
p 544 62 100 0 0 PREC:14
p 1136 176 100 0 -1 def(OUT):$(sad)$(vt)RV
p 1056 112 100 1024 0 name:$(tcs)orb:$(vt)$(I)
p 1056 176 75 768 -1 pproc(OUT):PP
use eaos 1736 456 100 0 PMDec
xform 0 1840 544
p 1760 638 100 0 -1 DESC:Proper Motion (Dec)
p 1808 510 100 0 -1 EGU:arcsec/yr
p 1456 526 100 0 0 OMSL:closed_loop
p 1456 398 100 0 0 PREC:14
p 1856 496 100 0 -1 def(OUT):$(sad)$(vt)PMDec
p 1968 448 100 1024 0 name:$(tcs)orb:$(vt)$(I)
p 1968 512 75 768 -1 pproc(OUT):PP
use eaos 824 424 100 0 PMRA
xform 0 928 512
p 848 606 100 0 -1 DESC:Proper Motion (RA)
p 896 478 100 0 -1 EGU:s/year
p 544 494 100 0 0 OMSL:closed_loop
p 544 366 100 0 0 PREC:14
p 1136 478 100 0 -1 def(OUT):$(sad)$(vt)PMRA
p 1056 416 100 1024 0 name:$(tcs)orb:$(vt)$(I)
p 1056 480 75 768 -1 pproc(OUT):PP
use egenSubC -160 295 100 0 SetSAD
xform 0 -16 720
p -144 1152 100 0 -1 DESC:Update target parameters
p -383 37 100 0 0 FTVC:STRING
p -383 5 100 0 0 FTVD:STRING
p -383 -27 100 0 0 FTVE:STRING
p 32 272 100 0 1 SNAM:tcsSetSadParams
p -48 288 100 1024 0 name:$(top)$(vt)$(I)
use eaos 1736 744 100 0 Parallax
xform 0 1840 832
p 1760 926 100 0 -1 DESC:Parallax
p 1808 798 100 0 -1 EGU:arcsecs
p 1456 814 100 0 0 OMSL:closed_loop
p 1456 686 100 0 0 PREC:14
p 2048 798 100 0 -1 def(OUT):$(sad)$(vt)Parallax
p 1968 736 100 1024 0 name:$(tcs)orb:$(vt)$(I)
p 1968 800 75 768 -1 pproc(OUT):PP
use estringouts 808 1160 100 0 InputFrame
xform 0 912 1232
p 816 1296 100 0 -1 DESC:Input track frame
p 720 1038 100 0 0 OMSL:closed_loop
p 720 1198 100 0 0 VAL:FK5
p 1136 1214 100 0 -1 def(OUT):$(sad)$(vt)InputFrame
p 1072 1152 100 1024 1 name:$(tcs)orb:$(vt)$(I)
p 1040 1216 75 768 -1 pproc(OUT):PP
use estringouts 1736 1176 100 0 Equinox
xform 0 1840 1248
p 1728 1326 100 0 -1 DESC:Equinox of track frame
p 1648 1054 100 0 0 OMSL:closed_loop
p 1648 1214 100 0 0 VAL:J2000.0
p 2064 1230 100 0 -1 def(OUT):$(sad)$(vt)Equinox
p 2000 1168 100 1024 1 name:$(tcs)orb:$(vt)$(I)
p 1968 1232 75 768 -1 pproc(OUT):PP
use estringouts 824 744 100 0 estringouts#61
xform 0 928 816
p 816 894 100 0 -1 DESC:Epoch of track frame
p 736 622 100 0 0 OMSL:closed_loop
p 736 782 100 0 0 VAL:J2000.0
p 1152 798 100 0 -1 def(OUT):$(sad)$(vt)Epoch
p 1088 736 100 1024 1 name:$(tcs)orb:$(vt)$(I)
p 1056 800 75 768 -1 pproc(OUT):PP
use eaos 808 1480 100 0 RA
xform 0 912 1568
p 832 1662 100 0 -1 DESC:Right Ascension
p 880 1534 100 0 -1 EGU:degrees
p 528 1550 100 0 0 OMSL:closed_loop
p 528 1422 100 0 0 PREC:14
p 1120 1534 100 0 -1 def(OUT):$(sad)$(vt)RA
p 1040 1472 100 1024 1 name:$(tcs)orb:$(vt)$(I)
p 1040 1536 75 768 -1 pproc(OUT):PP
use eaos 1736 1512 100 0 Dec
xform 0 1840 1600
p 1760 1694 100 0 -1 DESC:Declination
p 1792 1566 100 0 -1 EGU:degrees
p 1456 1582 100 0 0 OMSL:closed_loop
p 1456 1454 100 0 0 PREC:14
p 2064 1566 100 0 -1 def(OUT):$(sad)$(vt)Dec
p 1968 1504 100 1024 1 name:$(tcs)orb:$(vt)$(I)
p 1968 1568 75 768 -1 pproc(OUT):PP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -392 1016 100 0 VT
xform 0 -400 1056
[comments]
