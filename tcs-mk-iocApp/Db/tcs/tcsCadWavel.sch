[schematic2]
uniq 62
[tools]
[detail]
w 704 1315 100 0 n#30 ecad4.ecad4#61.STLK 352 928 512 928 512 1312 944 1312 eaos.Wavelength.SLNK
w 624 1346 100 0 n#29 ecad4.ecad4#61.VALA 352 1344 944 1344 eaos.Wavelength.DOL
w 710 1538 100 0 n#6 ecad4.ecad4#61.VAL 352 1536 1104 1536 outhier.VAL.p
w 798 1442 100 0 n#9 ecad4.ecad4#61.MESS 352 1504 384 1504 384 1440 1248 1440 outhier.MESS.p
w -146 1508 100 0 n#8 inhier.ICID.P -368 1440 -288 1440 -288 1504 32 1504 ecad4.ecad4#61.ICID
w -186 1538 100 0 n#7 inhier.DIR.P -368 1536 32 1536 ecad4.ecad4#61.DIR
s 1920 2000 100 0 $Id: tcsCadWavel.sch,v 1.1.1.1 1998/11/08 00:20:31 epics Exp $
s 1808 -336 100 0 11 june 1997
s 1808 -304 100 0 D.L. Terrett
s 2032 -192 100 0 Gemini Telescope Control System
s -560 1904 100 0 This schematic implements the wavel command for each
s -560 1872 100 0 virtual telescope. The output records downstream of the CAD 
s -560 1840 100 0 write to the status alarm database. They are only 
s -560 1808 100 0 triggered if the start link of the CAD is triggered i.e.
s -560 1776 100 0 only if the command is accepted. The output links of the
s -560 1744 100 0 CAD can't be used directly since these are triggered
s -560 1712 100 0 both at preset and at start
[cell use]
use ecad4 32 839 100 0 ecad4#61
xform 0 192 1216
p 160 1136 100 0 0 FTVA:DOUBLE
p 48 800 100 0 1 SNAM:tcsCADwavel
p 144 832 100 1024 1 name:$(tcs)$(cad)
p 352 1312 75 768 -1 pproc(OUTA):PP
p 352 1248 75 768 -1 pproc(OUTB):NPP
use eaos 968 1224 100 0 Wavelength
xform 0 1072 1312
p 1024 1390 100 0 -1 DESC:Target wavelength
p 1024 1278 100 0 -1 EGU:Angstroms
p 688 1294 100 0 0 OMSL:closed_loop
p 1296 1278 100 0 -1 def(OUT):$(sad)$(vt)Wavelength
p 1088 1168 100 1024 1 name:$(top)$(vt)$(I)
p 1200 1280 75 768 -1 pproc(OUT):PP
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use outhier 1240 1400 100 0 MESS
xform 0 1232 1440
use outhier 1096 1496 100 0 VAL
xform 0 1088 1536
use inhier -360 1400 100 0 ICID
xform 0 -368 1440
use inhier -360 1496 100 0 DIR
xform 0 -368 1536
[comments]
