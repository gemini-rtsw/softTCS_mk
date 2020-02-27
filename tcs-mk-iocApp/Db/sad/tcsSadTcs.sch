[schematic2]
uniq 216
[tools]
[detail]
w 514 -597 100 0 n#214 esirs.astCtx.FLNK 720 -768 768 -768 768 -608 320 -608 320 -480 368 -480 tcsSadTargetArrays.tcsSadTargetArrays#213.SLNK
w -1822 459 100 0 n#209 esirs.currentHAString.FLNK -1968 608 -1856 608 -1856 448 -1728 448 esirs.parAngle.SLNK
w -1790 1131 100 0 n#206 esirs.focalLength.FLNK -1776 1408 -1664 1408 -1664 1120 -1856 1120 -1856 864 -1728 864 esirs.currentHA.SLNK
w -1902 731 100 0 n#203 esirs.currentHA.FLNK -1312 1024 -1248 1024 -1248 720 -2496 720 -2496 448 -2384 448 esirs.currentHAString.SLNK
w 178 -917 100 0 n#181 esirs.demandRma.FLNK 32 -768 112 -768 112 -928 304 -928 esirs.astCtx.SLNK
w -2110 1506 100 0 n#178 tcsSadM2.tcsSadM2#123.FLNK -1744 1808 -1664 1808 -1664 1504 -2496 1504 -2496 1248 -2192 1248 esirs.focalLength.SLNK
w -500 -853 100 0 n#160 esirs.demandEl.FLNK -624 -768 -496 -768 -496 -928 -384 -928 esirs.demandRma.SLNK
w -502 -654 100 0 n#159 esirs.demandAz.FLNK 160 -352 224 -352 224 -656 -1168 -656 -1168 -928 -1040 -928 esirs.demandEl.SLNK
w -382 -510 100 0 n#158 esirs.currentDec.FLNK -624 -352 -448 -352 -448 -512 -256 -512 esirs.demandAz.SLNK
w -502 -222 100 0 n#157 esirs.demandDec.FLNK 160 96 224 96 224 -224 -1168 -224 -1168 -512 -1040 -512 esirs.currentDec.SLNK
w -382 -62 100 0 n#156 esirs.currentRA.FLNK -624 96 -448 96 -448 -64 -256 -64 esirs.demandDec.SLNK
w -502 194 100 0 n#155 esirs.demandRA.FLNK 160 480 224 480 224 192 -1168 192 -1168 -64 -1040 -64 esirs.currentRA.SLNK
w -438 322 100 0 n#154 tcsSadTime.tcsSadTime#150.FLNK -608 480 -560 480 -560 320 -256 320 esirs.demandRA.SLNK
w -502 610 100 0 n#151 esirs.rmaError.FLNK 144 992 224 992 224 608 -1168 608 -1168 480 -1056 480 tcsSadTime.tcsSadTime#150.SLNK
w -398 834 100 0 n#149 esirs.currentRma.FLNK -624 992 -464 992 -464 832 -272 832 esirs.rmaError.SLNK
w -502 1138 100 0 n#148 esirs.elError.FLNK 144 1440 224 1440 224 1136 -1168 1136 -1168 832 -1040 832 esirs.currentRma.SLNK
w -398 1282 100 0 n#145 esirs.currentEl.FLNK -624 1440 -464 1440 -464 1280 -272 1280 esirs.elError.SLNK
w -502 1554 100 0 n#144 esirs.azError.FLNK 144 1856 224 1856 224 1552 -1168 1552 -1168 1280 -1040 1280 esirs.currentEl.SLNK
w -398 1698 100 0 n#142 esirs.currentAz.FLNK -624 1856 -464 1856 -464 1696 -272 1696 esirs.azError.SLNK
w -2302 1810 100 0 n#124 efanouts.masterTrigger.LNK1 -2352 1808 -2192 1808 tcsSadM2.tcsSadM2#123.SLNK
s 864 1952 100 0 $Id: tcsSadTcs.sch,v 1.18 2009/12/01 14:14:42 cjm Exp $
s 1712 -928 100 0 Gemini Telescope Control System
s 1760 -832 100 0 Status and Alarm Database
[cell use]
use tcsSadGsaoi 432 -201 100 0 tcsSadGsaoi#215
xform 0 656 -48
use tcsSadTargetArrays 368 -537 100 0 tcsSadTargetArrays#213
xform 0 704 -368
use tcsSadAom -1616 1671 100 0 tcsSadAom#212
xform 0 -1392 1824
use esirs 1912 8 100 0 configuredForAO
xform 0 2096 160
p 2016 318 100 0 -1 DESC:AO Configuration
p 1824 -256 100 0 0 FDSC:if TCS configured for AO
p 2000 0 100 1024 0 name:$(sad)$(I)
use esirs -1704 -24 100 0 currentZd
xform 0 -1520 128
p -1680 272 100 0 -1 DESC:Current zenith distance
p -1792 -224 100 0 0 EGU:degs
p -1792 -288 100 0 0 FDSC:Current zenith distance
p -1792 -320 100 0 0 FTVL:DOUBLE
p -1792 -640 100 0 0 MDEL:0.00005
p -1536 -96 100 0 0 PREC:4
p -1616 -32 100 1024 0 name:$(sad)$(I)
use esirs -2384 -25 100 0 nodState
xform 0 -2176 128
p -2304 272 100 0 -1 DESC:Nod state of telescope
p -2448 -288 100 0 0 FDSC:Current nod state of telescope
p -2640 272 100 0 0 def(INP):0.0
p -2272 -32 100 1024 0 name:$(sad)$(I)
use esirs 328 -1016 100 0 astCtx
xform 0 512 -864
p 416 -706 100 0 -1 DESC:Astrometry context
p 240 -1280 100 0 0 FDSC:Astrometry context
p 240 -1312 100 0 0 FTVL:DOUBLE
p 255 -1536 100 0 0 HIGH:0.0
p 255 -1472 100 0 0 HIHI:0.0
p 255 -1504 100 0 0 LOLO:0.0
p 255 -1568 100 0 0 LOW:0.0
p 496 -1088 100 0 0 NELM:39
p 255 -1376 100 0 0 PREC:14
p 255 -992 100 0 0 SCAN:Passive
p 496 -914 100 0 -1 SNAM:
p 400 -770 100 0 -1 def(INP):$(top)ak:astCtx.VALA
p 416 -1024 100 1024 0 name:$(sad)$(I)
use esirs 1912 360 100 0 airMassNow
xform 0 2096 512
p 1936 656 100 0 -1 DESC:Air mass at current elevation
p 1824 160 100 0 0 EGU:none
p 1824 64 100 0 0 FTVL:DOUBLE
p 2080 288 100 0 0 PREC:3
p 2000 352 100 1024 0 name:$(sad)$(I)
use esirs 928 551 100 0 pointObs
xform 0 1136 704
p 864 448 100 0 0 DESC:Pointing observation
p 1024 640 100 0 1 FTVL:DOUBLE
p 1024 592 100 0 1 NELM:15
p 1120 480 100 0 0 PREC:14
p 1040 544 100 1024 0 name:$(sad)$(I)
use esirs 936 1416 100 0 name
xform 0 1120 1568
p 1040 1726 100 0 -1 DESC:Name of telescope
p 848 1152 100 0 0 FDSC:Compulsory name record as per ICD2
p 1024 1408 100 1024 0 name:$(sad)$(I)
use esirs -248 744 100 0 rmaError
xform 0 -64 896
p -336 704 100 0 0 ADEL:0.0005
p -176 1054 100 0 -1 DESC:Rotator mechanical angle error
p -192 798 100 0 1 EGU:degrees
p -336 480 100 0 0 FDSC:Rotator mechanical angle error
p -336 448 100 0 0 FTVL:DOUBLE
p -336 128 100 0 0 MDEL:0.0005
p -80 672 100 0 0 PREC:3
p -192 990 100 0 -1 def(INP):$(top)rmaError
p -160 736 100 1024 0 name:$(sad)$(I)
p -272 992 75 1280 -1 palrm(INP):MS
use esirs -1016 744 100 0 currentRma
xform 0 -832 896
p -1104 704 100 0 0 ADEL:0.0005
p -912 1054 100 0 -1 DESC:Current rotator mechanical angle
p -1104 544 100 0 0 EGU:Degrees
p -1104 480 100 0 0 FDSC:Current rotator mechanical angle
p -1104 448 100 0 0 FTVL:DOUBLE
p -960 880 100 0 1 HHSV:MAJOR
p -960 848 100 0 1 HIGH:267.0
p -960 816 100 0 1 HIHI:270.0
p -960 784 100 0 1 HSV:MINOR
p -816 880 100 0 1 LLSV:MAJOR
p -816 848 100 0 1 LOLO:-270.0
p -816 816 100 0 1 LOW:-267.0
p -816 784 100 0 1 LSV:MINOR
p -1104 128 100 0 0 MDEL:0.0005
p -848 672 100 0 0 PREC:3
p -960 990 100 0 -1 def(INP):$(top)currentRma
p -928 736 100 1024 0 name:$(sad)$(I)
p -1040 992 75 1280 -1 palrm(INP):MS
use esirs -248 1192 100 0 elError
xform 0 -64 1344
p -176 1502 100 0 -1 DESC:Current elevation error
p -336 928 100 0 0 FDSC:Mount elevation error
p -144 1360 100 0 -1 SNAM:sirSDegsSigned
p -192 1438 100 0 -1 def(INP):$(top)elError
p -160 1184 100 1024 0 name:$(sad)$(I)
p -272 1440 75 1280 -1 palrm(INP):MS
use esirs -248 1608 100 0 azError
xform 0 -64 1760
p -176 1918 100 0 -1 DESC:Current azimuth error
p -336 1344 100 0 0 FDSC:Mount azimuth error
p -144 1760 100 0 -1 SNAM:sirSDegsSigned
p -192 1854 100 0 -1 def(INP):$(top)azError
p -160 1600 100 1024 0 name:$(sad)$(I)
p -272 1856 75 1280 -1 palrm(INP):MS
use esirs -1016 1192 100 0 currentEl
xform 0 -832 1344
p -912 1502 100 0 -1 DESC:Current Elevation
p -960 1248 100 0 1 HHSV:MAJOR
p -960 1344 100 0 1 HIGH:87.0
p -960 1312 100 0 1 HIHI:90.0
p -960 1280 100 0 1 HSV:MINOR
p -816 1344 100 0 1 LLSV:MAJOR
p -816 1312 100 0 1 LOLO:15.0
p -816 1280 100 0 1 LOW:18.0
p -816 1248 100 0 1 LSV:MINOR
p -928 1376 100 0 -1 SNAM:sirSDegsSigned
p -960 1438 100 0 -1 def(INP):$(top)currentEl
p -928 1184 100 1024 0 name:$(sad)$(I)
p -1040 1440 75 1280 -1 palrm(INP):MS
use esirs -1016 1608 100 0 currentAz
xform 0 -832 1760
p -928 1918 100 0 -1 DESC:Current Azimuth
p -1104 1344 100 0 0 FDSC:Current mount AZ as sexagesimal
p -960 1728 100 0 1 HHSV:MAJOR
p -960 1696 100 0 1 HIGH:357.0
p -960 1664 100 0 1 HIHI:360.0
p -960 1632 100 0 1 HSV:MINOR
p -816 1728 100 0 1 LLSV:MAJOR
p -816 1696 100 0 1 LOLO:-180.0
p -816 1664 100 0 1 LOW:-177.0
p -816 1632 100 0 1 LSV:MINOR
p -912 1758 100 0 1 SCAN:1 second
p -912 1792 100 0 -1 SNAM:sirSDegsSigned
p -960 1854 100 0 -1 def(INP):$(top)currentAz
p -928 1600 100 1024 0 name:$(sad)$(I)
p -1040 1856 75 1280 -1 palrm(INP):MS
use esirs -1016 -152 100 0 currentRA
xform 0 -832 0
p -896 158 100 0 -1 DESC:Current RA
p -1089 -512 100 0 0 PREC:14
p -960 94 100 0 -1 def(INP):$(top)currentRA
p -928 -160 100 1024 0 name:$(sad)$(I)
use esirs 1880 -664 100 0 health
xform 0 2064 -512
p 1904 -354 100 0 -1 DESC:TCS system health status record
p 1807 -992 100 0 0 FTVL:STRING
p 1807 -1248 100 0 0 HHSV:NO_ALARM
p 1807 -1184 100 0 0 HIGH:0
p 1807 -1120 100 0 0 HIHI:0
p 1807 -1280 100 0 0 HSV:NO_ALARM
p 1807 -1152 100 0 0 LOLO:0
p 1807 -1024 100 0 0 PREC:0
p 2000 -546 100 0 0 SCAN:Passive
p 1807 -1056 100 0 0 SNAM:
p 1568 -386 100 0 0 def(INP):0.0
p 1968 -672 100 1024 0 name:$(sad)$(I)
p 1856 -416 75 1280 -1 palrm(INP):NMS
use esirs -1016 -600 100 0 currentDec
xform 0 -832 -448
p -992 -290 100 0 -1 DESC:Display current actual Dec
p -1089 -960 100 0 0 PREC:14
p -1089 -576 100 0 0 SCAN:Passive
p -880 -482 100 0 -1 SNAM:
p -960 -354 100 0 -1 def(INP):$(top)currentDec
p -928 -608 100 1024 0 name:$(sad)$(I)
use esirs -232 -152 100 0 demandDec
xform 0 -48 0
p -144 158 100 0 -1 DESC:Display current Dec
p -305 -512 100 0 0 PREC:14
p -305 -128 100 0 0 SCAN:Passive
p -112 -34 100 0 -1 SNAM:
p -176 94 100 0 -1 def(INP):$(top)demandDec
p -144 -160 100 1024 0 name:$(sad)$(I)
use esirs -1016 -1016 100 0 demandEl
xform 0 -832 -864
p -960 -706 100 0 -1 DESC:Demand mount elevation
p -1104 -1280 100 0 0 FDSC:Demand mount elevation
p -960 -880 100 0 1 HHSV:MAJOR
p -960 -912 100 0 1 HIGH:87.0
p -960 -944 100 0 1 HIHI:90.0
p -960 -976 100 0 1 HSV:MINOR
p -800 -880 100 0 1 LLSV:MAJOR
p -800 -912 100 0 1 LOLO:15.0
p -800 -944 100 0 1 LOW:18.0
p -800 -976 100 0 1 LSV:MINOR
p -1089 -1376 100 0 0 PREC:14
p -1089 -992 100 0 0 SCAN:Passive
p -912 -832 100 0 -1 SNAM:sirSDegsSigned
p -960 -770 100 0 -1 def(INP):$(top)demandEl
p -928 -1024 100 1024 0 name:$(sad)$(I)
use esirs -232 -600 100 0 demandAz
xform 0 -48 -448
p -176 -274 100 0 -1 DESC:Demand mount azimuth
p -320 -864 100 0 0 FDSC:Demand mount azimuth
p -176 -464 100 0 1 HHSV:MAJOR
p -176 -496 100 0 1 HIGH:357.0
p -176 -528 100 0 1 HIHI:360.0
p -176 -560 100 0 1 HSV:MINOR
p -32 -464 100 0 1 LLSV:MAJOR
p -32 -496 100 0 1 LOLO:-180.0
p -32 -528 100 0 1 LOW:-177.0
p -32 -560 100 0 1 LSV:MINOR
p -305 -960 100 0 0 PREC:14
p -305 -576 100 0 0 SCAN:Passive
p -128 -416 100 0 -1 SNAM:sirSDegsSigned
p -176 -354 100 0 -1 def(INP):$(top)demandAz
p -144 -608 100 1024 0 name:$(sad)$(I)
use esirs -360 -1016 100 0 demandRma
xform 0 -176 -864
p -448 -1056 100 0 0 ADEL:0.0005
p -272 -706 100 0 -1 DESC:Demand rotator Mechanical Angle
p -448 -1280 100 0 0 FDSC:Demand rotator mechanical angle
p -448 -1312 100 0 0 FTVL:DOUBLE
p -304 -864 100 0 1 HHSV:MAJOR
p -304 -896 100 0 1 HIGH:267.0
p -304 -928 100 0 1 HIHI:270.0
p -304 -960 100 0 1 HSV:MINOR
p -160 -864 100 0 1 LLSV:MAJOR
p -160 -896 100 0 1 LOLO:-270.0
p -160 -928 100 0 1 LOW:-267.0
p -160 -976 100 0 1 LSV:MINOR
p -448 -1632 100 0 0 MDEL:0.0005
p -433 -1376 100 0 0 PREC:3
p -433 -992 100 0 0 SCAN:Passive
p -288 -770 100 0 -1 def(INP):$(top)demandRma
p -272 -1024 100 1024 0 name:$(sad)$(I)
use esirs -232 232 100 0 demandRA
xform 0 -48 384
p -80 542 100 0 -1 DESC:Demand RA
p -320 -64 100 0 0 FTVL:STRING
p -305 -128 100 0 0 PREC:14
p -176 478 100 0 -1 def(INP):$(top)demandRA
p -144 224 100 1024 0 name:$(sad)$(I)
use esirs -2408 -792 100 0 debugLevelS
xform 0 -2224 -640
p -2304 -498 100 0 -1 DESC:TCS Debug level
p -2481 -1793 100 0 0 PV:$(top)
use esirs -2168 1160 100 0 focalLength
xform 0 -1984 1312
p -2096 1454 100 0 -1 DESC:Effective focal length
p -1808 1454 100 0 -1 EGU:mm
p -2256 864 100 0 0 FTVL:DOUBLE
p -2256 544 100 0 0 MDEL:0.05
p -2000 1088 100 0 0 PREC:3
p -2241 159 100 0 0 PV:$(sad)
p -2464 1406 100 0 -1 def(INP):$(top)om:m2Z.VALE
use esirs -2408 -1144 100 0 state
xform 0 -2224 -992
p -2272 -834 100 0 -1 DESC:TCS State
p -2320 -1152 100 1024 0 name:$(sad)$(I)
use esirs -1768 -1144 100 0 interlockState
xform 0 -1584 -992
p -1696 -834 100 0 -1 DESC:Interlock state of TCS
p -1856 -1408 100 0 0 FDSC:Interlock state of TCS due to GIS
p -1856 -1440 100 0 0 FTVL:LONG
p -1680 -1152 100 1024 0 name:$(sad)$(I)
use esirs 952 968 100 0 heartbeat
xform 0 1136 1120
p 1056 1278 100 0 -1 DESC:Heartbeat
p 864 704 100 0 0 FDSC:heartbeat incrementing at 1 Hz
p 1024 1022 100 0 1 FTVL:LONG
p 1040 960 100 1024 0 name:$(sad)$(I)
use esirs 1912 712 100 0 absorbFocus
xform 0 2096 864
p 2016 1022 100 0 -1 DESC:Absorb focus errors flag
p 1824 448 100 0 0 FDSC:focus errors are absorbed into TCS
p 2000 704 100 1024 0 name:$(sad)$(I)
use esirs 1304 -248 100 0 comaCorrect
xform 0 1488 -96
p 1408 62 100 0 -1 DESC:Coma corrections
p 1216 -512 100 0 0 FDSC:coma is corrected by M2
p 1392 -256 100 1024 0 name:$(sad)$(I)
use esirs 1912 1080 100 0 absorbTipTilt
xform 0 2096 1232
p 2016 1390 100 0 -1 DESC:Absorb tip/tilt flag
p 1824 816 100 0 0 FDSC:DC tip/tilt is aborbed by mount
p 2000 1072 100 1024 0 name:$(sad)$(I)
use esirs 1306 -670 100 0 inPosition
xform 0 1490 -518
p 1337 -361 100 0 -1 DESC:TCS mechanisms in position
p 1218 -934 100 0 0 FDSC:
p 1394 -678 100 1024 0 name:$(sad)$(I)
use esirs -1728 775 100 0 currentHA
xform 0 -1520 928
p -1632 1072 100 0 -1 DESC:Hour angle of target
p -1648 816 100 0 1 EGU:hours
p -1792 512 100 0 0 FDSC:Current HA of source A 
p -1792 480 100 0 0 FTVL:DOUBLE
p -1792 160 100 0 0 MDEL:0.00005
p -1536 704 100 0 0 PREC:4
p -1648 1024 100 0 -1 def(INP):$(top)currentHA
p -1616 768 100 1024 0 name:$(sad)$(I)
use esirs -2384 359 100 0 currentHAString
xform 0 -2176 512
p -2240 656 100 0 -1 DESC:Target HA
p -2448 96 100 0 0 FDSC:Target HA as a sexagesimal string
p -2304 608 100 0 -1 def(INP):$(top)currentHAString
p -2272 352 100 1024 0 name:$(sad)$(I)
use esirs 952 168 100 0 programID
xform 0 1136 320
p 1056 478 100 0 -1 DESC:Program ID
p 864 -96 100 0 0 FDSC:name record as per ICD2
p 1040 160 100 1024 0 name:$(sad)$(I)
use esirs -1728 359 100 0 parAngle
xform 0 -1520 512
p -1792 320 100 0 0 ADEL:0.00005
p -1616 656 100 0 -1 DESC:Parallactic angle
p -1648 400 100 0 1 EGU:degs
p -1792 96 100 0 0 FDSC:parallactic angle of source A
p -1792 64 100 0 0 FTVL:DOUBLE
p -1792 -256 100 0 0 MDEL:0.00005
p -1536 288 100 0 0 PREC:4
p -1648 608 100 0 -1 def(INP):$(top)parAngle
p -1616 352 100 1024 0 name:$(sad)$(I)
use tcsSadAo -1808 -393 100 0 tcsSadAo#210
xform 0 -1584 -240
use tcsSadEnv -2480 -393 100 0 tcsSadEnv#197
xform 0 -2256 -240
use tcsSadAg 1888 1415 100 0 tcsSadAg#182
xform 0 2112 1568
use tcsSadPointing 1360 231 100 0 tcsSadPointing#175
xform 0 1584 384
use tcsSadRotator 1360 551 100 0 tcsSadRotator#174
xform 0 1584 704
use tcsSadM1 1880 -312 100 0 tcsSadM1#173
xform 0 2080 -176
use tcsSadTimeLimits 1384 840 100 0 tcsSadTimeLimits#170
xform 0 1584 992
use tcsSadObserving 1384 1128 100 0 tcsSadObserving#169
xform 0 1584 1280
use tcsSadEcsParams 1384 1416 100 0 tcsSadEcsParams#168
xform 0 1584 1568
use tcsSadTime -1032 264 100 0 tcsSadTime#150
xform 0 -832 400
use tcsSadTargetParams -1784 -792 100 0 tcsSadTargetParams#137
xform 0 -1584 -640
use tcsSadM2 -2168 1656 100 0 tcsSadM2#123
xform 0 -1968 1760
use efanouts -2568 1592 100 0 masterTrigger
xform 0 -2472 1744
p -2528 1902 100 0 -1 DESC:Master SAD trigger
p -2736 940 100 0 0 PV:$(sad)
p -2496 1550 100 0 1 SCAN:1 second
use bd200tr -2784 -1288 -100 0 frame
xform 0 -144 416
[comments]
