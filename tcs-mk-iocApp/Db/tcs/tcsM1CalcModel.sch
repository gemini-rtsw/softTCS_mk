[schematic2]
uniq 31
[tools]
[detail]
w 2392 1067 100 0 FLNK egenSubC.m1CalcModel.FLNK 2304 1056 2528 1056 outhier.FLNK.p
w 1624 75 100 0 FLNK egenSubC.restoreM1.FLNK 896 64 2400 64 2400 1056 junction
w -184 779 100 0 n#21 inhier.c#20.P -384 768 64 768 egenSub.ao.INPA
w 1784 715 100 0 n#17 ecalcs.m1CalcDummy2.FLNK 1760 704 1856 704 1856 1088 junction
w 1912 1099 100 0 n#17 ecalcs.m1CalcDummy1.FLNK 1760 1440 1856 1440 1856 1088 2016 1088 egenSubC.m1CalcModel.SLNK
w 1368 1227 100 0 n#16 ecalcs.m1CalcTrigger.FLNK 1248 1472 1312 1472 1312 1216 1472 1216 ecalcs.m1CalcDummy1.SLNK
w 1384 1195 100 0 n#15 ecalcs.m1CalcTrigger.VAL 1248 1440 1344 1440 1344 1184 1472 1184 ecalcs.m1CalcDummy1.SDIS
w 766 1259 100 0 n#5 ecalcs.m1CalcCounter.FLNK 352 1472 608 1472 608 1248 960 1248 ecalcs.m1CalcTrigger.SLNK
w 142 1707 100 0 n#2 ecalcs.m1CalcCounter.VAL 352 1440 384 1440 384 1696 -64 1696 -64 1632 64 1632 ecalcs.m1CalcCounter.INPA
w 718 1643 100 0 n#2 junction 384 1440 512 1440 512 1632 960 1632 ecalcs.m1CalcTrigger.INPA
w -82 1611 100 0 n#3 elongins.m1Interval.VAL -192 1600 64 1600 ecalcs.m1CalcCounter.INPB
s 672 1952 100 0 m1Interval
s 672 1984 100 0 command is enabled and periodically at an interval set by 
s 672 2016 100 0 M1 figure correction. The model is calculated as soon as the m1FigUpdates
s 672 2048 100 0 This schematic controls the calculation of the
s 1344 192 100 0 then the record doesn't process and so the forward link isn't triggered.
s 1344 224 100 0 command. If the FigUpdatesFlag is set to 0 (disable)
s 1344 256 100 0 link is executed by the m1FigUpdates
s 1344 288 100 0 This record is triggered each time the start
s 2176 -64 100 0 Gemini Telescope Control System
s 2208 -128 100 0 Calculate M1 open loop model
s 1952 2128 100 0 $Id: tcsM1CalcModel.sch,v 1.6 2004/05/28 14:29:59 cjm Exp $
s -320 -112 100 0 This record is written to by the tcsReadHrwfs sequence program.
s -320 -144 100 0 It simply copies data from its input to its output when it processes.
s -320 -176 100 0 It is simply there to provide a similar interface to the PWFS's etc.
s 736 -96 100 0 This record is triggered by the sequence program tcsSeqInit
s 736 -128 100 0 in the state set m1s when pvload is executed.
[cell use]
use egenSubC 608 7 100 0 restoreM1
xform 0 752 432
p 640 864 100 0 -1 DESC:Saved M1 Optics model
p 320 558 100 0 0 PREC:10
p 736 -32 100 0 1 SNAM:tcsOpticsM1Restore
use egenSubC 2016 999 100 0 m1CalcModel
xform 0 2160 1424
p 1936 1856 100 0 -1 DESC:Calculate M1 open loop figure corrs
p 2112 1056 100 0 0 DISV:1
p 2096 1792 100 0 1 FTA:LONG
p 2112 1760 100 0 1 FTB:LONG
p 1728 1550 100 0 0 PREC:14
p 2080 944 100 0 1 SNAM:tcsOpticsM1CalcFig
p 1712 1760 100 0 -1 def(INPB):$(tcs)im:m1GuideOn
use inhier -400 727 100 0 c#20
xform 0 -384 768
use egenSub 64 7 100 0 ao
xform 0 208 432
p 96 864 100 0 -1 DESC:Provide HRWFS data
p -159 -219 100 0 0 FTA:LONG
p -159 -219 100 0 0 FTB:LONG
p -159 -219 100 0 0 FTVA:LONG
p -159 -859 100 0 0 NOJ:40
p 192 224 100 0 1 NOVJ:40
p 128 -32 100 0 1 SNAM:tcsOpticsHrwfsData
p -256 784 100 0 -1 def(INPA):$(tcs)im:m1GuideOn
p 176 0 100 1024 0 name:$(tcs)hr:dc:$(I)
use ecalcs 1472 391 100 0 m1CalcDummy2
xform 0 1616 656
p 1379 872 100 0 0 CALC:A
p 1344 928 100 0 -1 DESC:Dummy record to break processing chain
p 1552 528 100 0 1 DISV:0
p 976 432 100 0 1 def(SDIS):$(tcs)im:m1FigUpdatesFlag
use ecalcs 64 1159 100 0 m1CalcCounter
xform 0 208 1424
p 144 1344 100 0 1 CALC:(A+1)%MAX(B,1)
p -143 1590 100 0 0 DESC:Counter
p 256 1184 100 0 1 SCAN:1 second
use ecalcs 960 1159 100 0 m1CalcTrigger
xform 0 1104 1424
p 1056 1344 100 0 -1 CALC:A=0&&B?1:0
p 960 1712 100 0 -1 DESC:Trigger model calculation
p 576 1600 100 0 -1 def(INPB):$(tcs)im:m1FigUpdatesFlag
use ecalcs 1472 1127 100 0 m1CalcDummy1
xform 0 1616 1392
p 1379 1608 100 0 0 CALC:A
p 1344 1664 100 0 -1 DESC:Dummy record to break processing chain
p 1552 1264 100 0 1 DISV:0
use outhier 2496 1015 100 0 FLNK
xform 0 2512 1056
use elongins -448 1543 100 0 m1Interval
xform 0 -320 1616
p -496 1712 100 0 -1 DESC:Update interval of M1 open loop 
p -384 1504 100 0 1 EGU:seconds
p -704 1582 100 0 0 HOPR:1000
use bc200tr -624 -344 -100 0 frame
xform 0 1056 960
[comments]
