[schematic2]
uniq 8
[tools]
[detail]
w -1038 299 100 0 n#1 esels.InPosSelect.FLNK -1056 288 -960 288 -960 96 -864 96 esirs.inPosition.SLNK
w -990 267 100 0 n#2 esels.InPosSelect.VAL -1056 256 -864 256 esirs.inPosition.INP
w -1566 171 100 0 n#3 ebos.InPosFake.VAL -1600 160 -1472 160 -1472 400 -1344 400 esels.InPosSelect.INPB
w -1662 331 100 0 INPOS#4 inhier.INPOS.P -1760 320 -1504 320 -1504 432 -1344 432 esels.InPosSelect.INPA
w -1494 475 100 0 n#5 ebos.InPosOverride.VAL -1584 464 -1344 464 esels.InPosSelect.NVL
w -1464 875 100 0 n#6 ecalcs.present.FLNK -1696 1056 -1536 1056 -1536 864 -1344 864 esirs.heartBeat.SLNK
w -1496 1035 100 0 n#7 junction -1600 1024 -1344 1024 esirs.heartBeat.INP
w -1872 1314 100 0 n#7 ecalcs.present.VAL -1696 1024 -1600 1024 -1600 1312 -2096 1312 -2096 1216 -1984 1216 ecalcs.present.INPA
s -176 -352 100 0 Sciences Ltd.
s -176 -320 100 0 Observatory
s -176 -288 100 0 Copyright
s -160 1904 100 0 $Id: gsaoiSimStandard.sch,v 1.3 2010/06/15 14:11:42 cjm Exp $
[cell use]
use bc200tr -2752 -568 -100 0 frame
xform 0 -1072 736
use ebos -1840 375 100 0 InPosOverride
xform 0 -1712 464
p -1840 544 100 0 -1 DESC:Select in position source
p -2160 318 100 0 0 ONAM:enable
p -2160 350 100 0 0 ZNAM:disable
p -1728 368 100 1024 0 name:$(top)$(subsys)$(I)
use ebos -1856 71 100 0 InPosFake
xform 0 -1728 160
p -1872 256 100 0 -1 DESC:Fake in position signal
p -2176 14 100 0 0 ONAM:inpos
p -2176 46 100 0 0 ZNAM:outpos
p -1744 64 100 1024 0 name:$(top)$(subsys)$(I)
use esels -1344 -25 100 0 InPosSelect
xform 0 -1200 240
p -1551 438 100 0 0 DESC:Over ride inPosition status
p -1184 32 100 0 1 SCAN:1 second
p -1184 -16 100 0 1 SELM:Specified
p -1232 -32 100 1024 0 name:$(top)$(subsys)$(I)
use esirs -1344 775 100 0 heartBeat
xform 0 -1136 928
p -1248 1088 100 0 -1 DESC:Heart beat record
p -1408 480 100 0 0 FTVL:LONG
p -1232 768 100 1024 0 name:$(gsaoi)sad:dc:$(I)
use esirs -676 1158 100 0 state
xform 0 -544 1312
p -801 1056 100 0 0 DESC:Application state
p -801 1040 100 0 0 FDSC:The internal state of the application
p -613 1228 100 0 1 FTVL:STRING
p -640 1152 100 1024 0 name:$(gsaoi)sad:dc:$(I)
p -816 832 100 0 -1 HHSV:NO_ALARM
use esirs -600 752 100 0 health
xform 0 -416 904
p -673 648 100 0 0 DESC:AOM health record in simulation
p -673 632 100 0 0 FDSC:AOM health (simulation)
p -488 816 100 0 1 FTVL:STRING
p -512 744 100 1024 0 name:$(gsaoi)sad:dc:$(I)
use esirs -840 8 100 0 inPosition
xform 0 -656 160
p -913 -96 100 0 0 DESC:inPosition SIR record in simulation
p -913 -112 100 0 0 FDSC:
p -913 -320 100 0 0 FTVL:LONG
p -966 8 100 0 1 PV:$(prefix)
p -672 -128 100 0 0 SCAN:Passive
use inhier -1776 279 100 0 INPOS
xform 0 -1760 320
use ecalcs -1960 744 100 0 present
xform 0 -1840 1008
p -1856 974 100 0 -1 CALC:A+1
p -2016 718 100 0 1 PV:$(top)$(subsys)
p -1888 926 100 0 -1 SCAN:1 second
[comments]
