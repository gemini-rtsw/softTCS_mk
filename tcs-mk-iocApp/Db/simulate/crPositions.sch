[schematic2]
uniq 15
[tools]
[detail]
w 196 963 100 0 POS junction 192 1424 192 512 944 512 eaos.crCurrentPos.DOL
w -256 1435 100 0 POS inhier.POS.P -656 1424 192 1424 192 1504 928 1504 egenSub.crtimeStampedPos.INPB
w 120 139 100 0 ERR inhier.ERR.P -656 128 944 128 eaos.crPosError.DOL
w -208 1291 100 0 VEL inhier.VEL.P -656 1280 288 1280 288 1440 928 1440 egenSub.crtimeStampedPos.INPC
w 118 1579 100 0 TIME inhier.TIME.P -656 1568 928 1568 egenSub.crtimeStampedPos.INPA
w 1086 299 100 0 n#8 eaos.crCurrentPos.FLNK 1200 512 1408 512 1408 288 800 288 800 96 944 96 eaos.crPosError.SLNK
w 1086 651 100 0 n#7 egenSub.crtimeStampedPos.FLNK 1216 864 1408 864 1408 640 800 640 800 480 944 480 eaos.crCurrentPos.SLNK
w 118 907 100 0 SLNK inhier.SLNK.P -656 896 928 896 egenSub.crtimeStampedPos.SLNK
s 1616 1968 100 0 $Id: crPositions.sch,v 1.4 1999/11/21 00:47:12 cjm Exp $
s 1856 -288 100 0 Cass. Rotator positions & velocities
s 1888 -224 100 0 Gemini Telescope Control System
s 384 1856 200 0 Cass Rotator Positions
[cell use]
use inhier -672 1383 100 0 POS
xform 0 -656 1424
use inhier -672 87 100 0 ERR
xform 0 -656 128
use inhier -672 855 100 0 SLNK
xform 0 -656 896
use inhier -672 1527 100 0 TIME
xform 0 -656 1568
use inhier -672 1239 100 0 VEL
xform 0 -656 1280
use egenSub 928 807 100 0 crtimeStampedPos
xform 0 1072 1232
p 848 1680 100 0 -1 DESC:Provide time stamped position & velocity
p 1072 1584 100 0 1 NOVA:3
p 928 736 100 0 1 SNAM:tcsCrsTimeStampedPos
p 1040 800 100 1024 0 name:$(cr)$(I)
use eaos 944 391 100 0 crCurrentPos
xform 0 1072 480
p 976 576 100 0 -1 DESC:Current Position
p 912 206 100 0 0 EGU:degs
p 688 462 100 0 0 OMSL:closed_loop
p 1056 384 100 1024 0 name:$(cr)$(I)
use eaos 944 7 100 0 crPosError
xform 0 1072 96
p 976 192 100 0 -1 DESC:Current Position Error
p 912 -178 100 0 0 EGU:degs
p 688 78 100 0 0 OMSL:closed_loop
p 1056 0 100 1024 0 name:$(cr)$(I)
use bc200tr -960 -504 -100 0 frame
xform 0 720 800
[comments]
