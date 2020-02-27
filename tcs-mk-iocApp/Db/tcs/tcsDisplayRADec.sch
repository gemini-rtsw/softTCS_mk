[schematic2]
uniq 14
[tools]
[detail]
w 754 -53 100 0 n#1 egenSub.DisplayRADec.VALH 352 768 608 768 608 -64 960 -64 esirs.currentRA.INP
w 770 395 100 0 n#2 egenSub.DisplayRADec.VALG 352 832 640 832 640 384 960 384 esirs.demandRA.INP
w 498 1035 100 0 n#3 egenSub.DisplayRADec.VALD 352 1024 704 1024 704 832 960 832 esirs.currentDec.INP
w 530 1163 100 0 n#4 egenSub.DisplayRADec.VALB 352 1152 768 1152 768 1248 960 1248 esirs.demandDec.INP
w 530 491 100 0 n#5 egenSub.DisplayRADec.FLNK 352 480 768 480 768 1088 960 1088 esirs.demandDec.SLNK
w -118 1003 100 0 RPA inhier.RPA.P -240 992 64 992 egenSub.DisplayRADec.INPD
w -118 1067 100 0 EL inhier.EL.P -240 1056 64 1056 egenSub.DisplayRADec.INPC
w -112 1131 100 0 AZ inhier.AZ.P -240 1120 64 1120 egenSub.DisplayRADec.INPB
w -112 1195 100 0 TAPPL inhier.TAPPL.P -240 1184 64 1184 egenSub.DisplayRADec.INPA
w 1560 -62 100 0 n#6 esirs.currentRA.FLNK 1376 -64 1792 -64 outhier.FLNK.p
w 1128 50 100 0 n#7 esirs.demandRA.FLNK 1376 384 1472 384 1472 48 832 48 832 -224 960 -224 esirs.currentRA.SLNK
w 1128 498 100 0 n#8 esirs.currentDec.FLNK 1376 832 1472 832 1472 496 832 496 832 224 960 224 esirs.demandRA.SLNK
w 1128 930 100 0 n#9 esirs.demandDec.FLNK 1376 1248 1472 1248 1472 928 832 928 832 672 960 672 esirs.currentDec.SLNK
w 1472 -94 100 0 n#10 esirs.currentRA.VAL 1376 -96 1616 -96 outhier.CURRENTRA.p
w 1472 802 100 0 n#11 esirs.currentDec.VAL 1376 800 1616 800 outhier.CURRENTDEC.p
w 1472 1218 100 0 n#12 esirs.demandDec.VAL 1376 1216 1616 1216 outhier.DEMANDDEC.p
w 1472 354 100 0 n#13 esirs.demandRA.VAL 1376 352 1616 352 outhier.DEMANDRA.p
s -272 896 100 0 use timeStamped positions?
s 304 1408 100 0 added a flag to input F. (1:timestamped, 0:simple)
s 304 1440 100 0 AWE: changed INPA to $(mc)azcapturedTime
s 1888 992 100 0 of the OCS.
s 1888 1040 100 0 values from them at 1Hz to meet the constraints
s 1888 1088 100 0 screens. Corresponding records in the TCS SAD pull
s 1888 1136 100 0 The SIR records here are used by the TCS engineering
s 592 1696 300 0 Generate RA and Dec strings
s 1952 1856 100 0 $Id: tcsDisplayRADec.sch,v 1.7 2013/05/09 22:31:11 gemvx Exp $
s 2208 -336 100 0 Gemini Telescope Control System
s 2192 -400 100 0 Display RA and Dec. information
s -304 1440 100 0 INPA was set to $(mc)timeCurrentPos
s -304 1408 100 0 This record does not yet exist in the MCS
s -304 1376 100 0 THis did not matter until GEM8.5 which puts
s -304 1344 100 0 a record into an invalid state and doesn't process
s -304 1312 100 0 if a link isn't present.
[cell use]
use bc200tr -624 -616 -100 0 frame
xform 0 1056 688
use egenSub 64 423 100 0 DisplayRADec
xform 0 208 848
p 32 1280 100 0 -1 DESC:Display demand and current RA/Dec
p 144 896 100 0 -1 FTF:LONG
p -159 37 100 0 0 FTVG:STRING
p -159 5 100 0 0 FTVH:STRING
p -159 -27 100 0 0 FTVI:STRING
p -159 -59 100 0 0 FTVJ:STRING
p 160 992 100 0 1 NOD:3
p 160 944 100 0 1 NOE:6
p -224 974 100 0 0 PREC:14
p 160 832 100 0 1 SCAN:.5 second
p 80 352 100 0 1 SNAM:tcsDisplayRADec
p -224 1054 100 0 0 def(INPA):$(mc)azcapturedTime
p -224 1022 100 0 0 def(INPB):$(mc)azCurrentPos
p -224 990 100 0 0 def(INPC):$(mc)elCurrentPos
p -224 958 100 0 0 def(INPD):$(cr)crtimeStampedPos.VALA
p -224 926 100 0 0 def(INPE):$(mc)timeStampedPos.VALA
use outhier 1784 -104 100 0 FLNK
xform 0 1776 -64
use outhier 1608 760 100 0 CURRENTDEC
xform 0 1600 800
use outhier 1608 -136 100 0 CURRENTRA
xform 0 1600 -96
use outhier 1608 1176 100 0 DEMANDDEC
xform 0 1600 1216
use outhier 1608 312 100 0 DEMANDRA
xform 0 1600 352
use esirs 984 -312 100 0 currentRA
xform 0 1168 -160
p 1120 -2 100 0 -1 DESC:Current RA
p 896 -576 100 0 0 FDSC:Current RA for mount
p 1280 -336 100 1024 1 name:$(tcs)$(I)
p 960 -64 75 1280 -1 palrm(INP):MS
use esirs 984 584 100 0 currentDec
xform 0 1168 736
p 1120 894 100 0 -1 DESC:Current Dec.
p 896 320 100 0 0 FDSC:Current declination of mount
p 896 224 100 0 0 HIGH:90.0
p 896 192 100 0 0 HIHI:90.0
p 896 64 100 0 0 LOLO:-90.0
p 896 32 100 0 0 LOW:-90.0
p 1152 512 100 0 0 PREC:14
p 1088 718 100 0 -1 SNAM:sirSDegsSigned
p 1248 576 100 1024 1 name:$(tcs)$(I)
p 960 832 75 1280 -1 palrm(INP):MS
use esirs 984 1000 100 0 demandDec
xform 0 1168 1152
p 1120 1310 100 0 -1 DESC:Demand Dec
p 896 736 100 0 0 FDSC:Demand Dec for mount
p 896 640 100 0 0 HIGH:90.0
p 896 608 100 0 0 HIHI:90.0
p 896 480 100 0 0 LOLO:-90.0
p 896 448 100 0 0 LOW:-90.0
p 1152 928 100 0 0 PREC:14
p 1088 1134 100 0 -1 SNAM:sirSDegsSigned
p 1248 976 100 1024 1 name:$(tcs)$(I)
use esirs 984 136 100 0 demandRA
xform 0 1168 288
p 1120 446 100 0 -1 DESC:Demand RA
p 896 -128 100 0 0 FDSC:Demand RA for mount
p 1248 112 100 1024 1 name:$(tcs)$(I)
use inhier -232 952 100 0 RPA
xform 0 -240 992
use inhier -232 1144 100 0 TAPPL
xform 0 -240 1184
use inhier -232 1080 100 0 AZ
xform 0 -240 1120
use inhier -232 1016 100 0 EL
xform 0 -240 1056
[comments]
