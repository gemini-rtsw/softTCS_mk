[schematic2]
uniq 88
[tools]
[detail]
w 320 1643 100 0 n#81 ecad20.gsaoiodgwSetup.MESS 176 1632 512 1632 512 1584 672 1584 outhier.MESS.p
w 400 1675 100 0 n#80 ecad20.gsaoiodgwSetup.VAL 176 1664 672 1664 outhier.VAL.p
w -288 1643 100 0 n#79 inhier.ICID.P -496 1584 -384 1584 -384 1632 -144 1632 ecad20.gsaoiodgwSetup.ICID
w -344 1675 100 0 n#78 inhier.DIR.P -496 1664 -144 1664 ecad20.gsaoiodgwSetup.DIR
s 2032 -192 100 0 Gemini Telescope Control System
s 1808 -336 100 0 23 November 2009
s 1808 2000 100 0 $Id: tcsGsaoiOdgwSetupCad.sch,v 1.2 2010/02/26 19:05:54 gemvx Exp $
s 368 1856 200 0 Trigger the GSAOI seqODGW CAD
s 1824 -192 100 0 Copyright
s 1824 -224 100 0 Observatory
s 1824 -256 100 0 Sciences Ltd.
[cell use]
use outhier 664 1624 100 0 VAL
xform 0 656 1664
use outhier 664 1544 100 0 MESS
xform 0 656 1584
use ecad20 -144 -57 100 0 gsaoiodgwSetup
xform 0 16 832
p -176 1760 100 0 -1 DESC:Implement the gsaoiodgwSetup command
p -48 1408 100 0 0 FTVA:STRING
p -48 1376 100 0 0 FTVB:LONG
p -48 1344 100 0 0 FTVC:LONG
p -48 1312 100 0 0 FTVD:DOUBLE
p -48 1280 100 0 0 FTVE:LONG
p -48 1248 100 0 0 FTVF:LONG
p -48 1216 100 0 0 FTVG:LONG
p -48 1184 100 0 0 FTVH:LONG
p -48 1152 100 0 0 FTVI:LONG
p -48 1120 100 0 0 FTVJ:LONG
p -48 1088 100 0 0 FTVK:LONG
p -48 960 100 0 0 FTVO:DOUBLE
p -144 -112 100 0 1 SNAM:tcsCADgsaoiodgwSetup
p -144 -96 100 0 0 def(OUTA):
p -32 -64 100 1024 0 name:$(tcs)$(I)
use bc200tr -784 -472 -100 0 frame
xform 0 896 832
use inhier -488 1624 100 0 DIR
xform 0 -496 1664
use inhier -488 1544 100 0 ICID
xform 0 -496 1584
[comments]
