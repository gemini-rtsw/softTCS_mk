[schematic2]
uniq 44
[tools]
[detail]
w -3368 1355 100 0 n#43 esirs.aoConfig.OMSS -3488 736 -3424 736 -3424 1344 -3264 1344 egenSub.setHealth.INPH
w -3384 1419 100 0 n#42 esirs.aoConfig.VAL -3488 768 -3456 768 -3456 1408 -3264 1408 egenSub.setHealth.INPG
w -3448 811 100 0 n#40 esirs.aoConfig.FLNK -3488 800 -3360 800 -3360 1120 -3264 1120 egenSub.setHealth.SLNK
w -4696 171 100 0 n#39 inhier.SLNK.P -4832 160 -4512 160 egenSub.checkAOConfig.SLNK
w -4168 139 100 0 n#36 egenSub.checkAOConfig.FLNK -4224 128 -4064 128 -4064 640 -3904 640 esirs.aoConfig.SLNK
w -4168 875 100 0 n#35 egenSub.checkAOConfig.VALA -4224 864 -4064 864 -4064 800 -3904 800 esirs.aoConfig.INP
w -4088 779 100 0 n#34 egenSub.checkAOConfig.OUTB -4224 768 -3904 768 esirs.aoConfig.IMSS
w -3872 1339 100 0 n#31 inhier.c#29.P -4144 1328 -3552 1328 -3552 1472 -3264 1472 egenSub.setHealth.INPF
w -3888 1435 100 0 n#30 inhier.c#28.P -4144 1424 -3584 1424 -3584 1536 -3264 1536 egenSub.setHealth.INPE
w -2152 1467 100 0 n#27 esirs.health.FLNK -2304 1824 -2240 1824 -2240 1456 -2016 1456 outhier.FLNK.p
w -2120 1659 100 0 n#26 esirs.health.OMSS -2304 1760 -2176 1760 -2176 1648 -2016 1648 outhier.MESS.p
w -2184 1803 100 0 n#25 esirs.health.VAL -2304 1792 -2016 1792 outhier.HLTH.p
w -3904 1531 100 0 n#14 inhier.c#10.P -4144 1520 -3616 1520 -3616 1600 -3264 1600 egenSub.setHealth.INPD
w -3920 1627 100 0 n#13 inhier.c#9.P -4144 1616 -3648 1616 -3648 1664 -3264 1664 egenSub.setHealth.INPC
w -3576 1739 100 0 n#12 tcsTime.tcsTime#8.OMSS -3840 1728 -3264 1728 egenSub.setHealth.INPB
w -3576 1803 100 0 n#11 tcsTime.tcsTime#8.TIMEHEALTH -3840 1792 -3264 1792 egenSub.setHealth.INPA
w -2802 1835 100 0 n#4 esirs.health.INP -2720 1824 -2848 1824 -2848 1760 -2976 1760 egenSub.setHealth.VALB
w -2914 1099 100 0 n#3 egenSub.setHealth.FLNK -2976 1088 -2816 1088 -2816 1664 -2720 1664 esirs.health.SLNK
w -2866 1803 100 0 n#2 egenSub.setHealth.OUTA -2976 1792 -2720 1792 esirs.health.IMSS
s -2464 2096 100 0 $Id: tcsInternalHealth.sch,v 1.5 2006/11/24 11:14:15 cjm Exp $
s -2464 -96 100 0 Copyright
s -2464 -128 100 0 Observatory
s -2464 -160 100 0 Sciences Ltd.
s -2240 -96 100 0 Gemini TCS
s -2240 -160 100 0 Combine internal health records
[cell use]
use egenSub -3264 1031 100 0 setHealth
xform 0 -3120 1456
p -3280 1888 100 0 -1 DESC:Generate internal health state
p -3487 805 100 0 0 FTA:STRING
p -3487 805 100 0 0 FTB:STRING
p -3487 773 100 0 0 FTC:STRING
p -3487 741 100 0 0 FTD:STRING
p -3487 709 100 0 0 FTE:STRING
p -3487 645 100 0 0 FTF:STRING
p -3136 1344 100 0 0 FTG:STRING
p -3487 613 100 0 0 FTH:STRING
p -3487 805 100 0 0 FTVA:STRING
p -3487 805 100 0 0 FTVB:STRING
p -3487 773 100 0 0 FTVC:LONG
p -3487 741 100 0 0 FTVD:LONG
p -3487 709 100 0 0 FTVE:LONG
p -3487 645 100 0 0 FTVF:LONG
p -3487 645 100 0 0 FTVG:LONG
p -3200 928 100 0 1 SCAN:Passive
p -3200 976 100 0 1 SNAM:tcsCombIntHealth
p -4080 1632 100 0 -1 def(INPC):$(tcs)om:tt:health
p -4096 1536 100 0 -1 def(INPD):$(tcs)om:tt:health.OMSS
p -4096 1440 100 0 -1 def(INPE):$(tcs)ak:solsys.VALA
p -4096 1344 100 0 -1 def(INPF):$(tcs)ak:solsys.VALB
use egenSub -4512 71 100 0 checkAOConfig
xform 0 -4368 496
p -4544 928 100 0 -1 DESC:Generate AO configuration health
p -4735 -155 100 0 0 FTVA:STRING
p -4735 -155 100 0 0 FTVB:STRING
p -4272 64 100 0 1 SNAM:tcsCheckAOConfig
use esirs -2720 1575 100 0 health
xform 0 -2512 1728
p -2624 1888 100 0 -1 DESC:TCS Internal health
p -2784 1312 100 0 0 FDSC:Overall internal health of the TCS
use esirs -3904 551 100 0 aoConfig
xform 0 -3696 704
p -3824 864 100 0 -1 DESC:AO configuration health
p -3968 288 100 0 0 FDSC:Health status of TCS AO configuration
use inhier -4160 1575 100 0 c#9
xform 0 -4144 1616
use inhier -4160 1479 100 0 c#10
xform 0 -4144 1520
use inhier -4848 119 100 0 SLNK
xform 0 -4832 160
use inhier -4160 1383 100 0 c#28
xform 0 -4144 1424
use inhier -4160 1287 100 0 c#29
xform 0 -4144 1328
use outhier -2048 1751 100 0 HLTH
xform 0 -2032 1792
use outhier -2048 1607 100 0 MESS
xform 0 -2032 1648
use outhier -2048 1415 100 0 FLNK
xform 0 -2032 1456
use tcsTime -4160 1671 100 0 tcsTime#8
xform 0 -4000 1760
p -4144 1856 100 0 1 seta:top $(tcs)TIME:
use bc200tr -5056 -376 -100 0 frame
xform 0 -3376 928
[comments]
