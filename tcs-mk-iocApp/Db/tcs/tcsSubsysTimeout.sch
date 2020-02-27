[schematic2]
uniq 31
[tools]
[detail]
w 40 875 100 0 n#29 eaos.eaos#16.FLNK 144 512 224 512 224 864 -96 864 -96 1120 junction
w -152 1131 100 0 n#29 ecalcouts.ecalcouts#28.FLNK -448 1152 -256 1152 -256 1120 0 1120 elongouts.elongouts#20.SLNK
w -880 1778 100 0 n#27 inhier.START.P -1296 1776 -416 1776 -416 1664 32 1664 elongouts.elongouts#24.SLNK
w 8 1698 100 0 n#26 hwin.hwin#25.in 32 1696 32 1696 elongouts.elongouts#24.DOL
w -24 1154 100 0 n#21 hwin.hwin#18.in 0 1152 0 1152 elongouts.elongouts#20.DOL
w -136 514 100 0 n#17 hwin.hwin#14.in -112 512 -112 512 eaos.eaos#16.DOL
w -190 418 100 0 n#13 ecalcouts.ecalcouts#30.FLNK -288 320 -192 320 -192 480 -112 480 eaos.eaos#16.SLNK
w 1022 1332 100 0 n#5 ecalcs.ecalcs#4.VAL 1232 992 1296 992 1296 1328 784 1328 784 1184 944 1184 ecalcs.ecalcs#4.INPA
s -1424 1280 120 0 or trackId changes
s 48 1232 150 0 Stop Timeout Counter
s 16 1776 150 0 Start Timeout counter
s 320 528 150 0 timeout counter
s 320 576 150 0 CAR_IDLE and stop
s 320 624 150 0 On Timeout, output
s -912 424 150 0 Wait for timeout
s -1440 1168 150 0 when activeC = BUSY
s -1424 1216 150 0 Stop Timeout Count
s 1216 768 150 0 IF B!=0 output zero
s 1216 816 150 0 IF B=0 Increment 1 per sec
s 1216 864 150 0 Timeout Counter
s 1344 -32 130 0 Gemini TCS
s 1312 -80 100 0 tcsSubsysTimeout.sch
s 1024 -144 100 0 P.B. Taylor
s 1024 -176 100 0 24 November 97
s 1296 -112 100 0 Detect subsystem timeout
s -1424 1312 120 0 Processed when activeC
s 1024 2160 100 0 $id$
[cell use]
use ecalcouts -608 135 100 0 ecalcouts#30
xform 0 -448 256
p -536 168 100 0 -1 CALC:A=3
p -520 400 100 0 1 OOPT:Transition To Non-zero
p -1008 320 100 0 -1 def(INPA):$(tcs)$(prefix)acTimeout.VAL
p -544 136 100 0 -1 name:$(tcs)$(prefix)acWaitTmo
p -656 328 75 0 -1 pproc(INPA):CPP
use ecalcouts -768 967 100 0 ecalcouts#28
xform 0 -608 1088
p -696 1000 100 0 -1 CALC:A=$(CAR_BUSY)
p -680 1232 100 0 1 OOPT:When Non-zero
p -1072 1152 100 0 -1 def(INPA):$(subsys)activeC.VAL
p -1072 1112 100 0 -1 def(INPB):$(subsys)trackId.VAL
p -704 968 100 0 -1 name:$(tcs)$(prefix)WaitBusy
p -816 1160 75 0 -1 pproc(INPA):CPP
p -816 1128 75 0 -1 pproc(INPB):CPP
use bc200tr -1568 -312 -100 0 frame
xform 0 112 992
use hwin -280 472 100 0 hwin#14
xform 0 -208 512
p -290 440 100 0 0 typ(in):val
p -301 504 100 0 -1 val(in):$(CAR_IDLE)
use hwin -168 1112 100 0 hwin#18
xform 0 -96 1152
p -189 1144 100 0 -1 val(in):1
use hwin -136 1656 100 0 hwin#25
xform 0 -64 1696
p -157 1688 100 0 -1 val(in):0
use elongouts 24 1032 100 0 elongouts#20
xform 0 128 1120
p -160 1038 100 0 0 OMSL:closed_loop
p 80 1086 100 0 1 PINI:YES
p 304 1070 100 0 -1 def(OUT):$(tcs)$(prefix)acTimeout.B
p 112 1024 100 1024 -1 name:$(tcs)$(prefix)acReset
p 256 1088 75 768 -1 pproc(OUT):PP
use elongouts 56 1576 100 0 elongouts#24
xform 0 160 1664
p 48 1536 100 0 1 DISV:$(CAR_BUSY)
p -128 1582 100 0 0 OMSL:closed_loop
p 112 1630 100 0 1 PINI:NO
p 336 1614 100 0 -1 def(OUT):$(tcs)$(prefix)acTimeout.B
p -240 1632 100 0 -1 def(SDIS):$(subsys)activeC
p 144 1568 100 1024 -1 name:$(top)$(prefix)acStart
p 288 1632 75 768 -1 pproc(OUT):PP
use inhier -1288 1736 100 0 START
xform 0 -1296 1776
use eaos -88 392 100 0 eaos#16
xform 0 16 480
p -368 462 100 0 0 OMSL:closed_loop
p 208 430 100 0 -1 def(OUT):$(tcs)$(prefix)ActiveC.IVAL
p 0 384 100 1024 -1 name:$(tcs)$(prefix)setIdle
p 144 448 75 768 -1 pproc(OUT):PP
use ecalcs 968 712 100 0 ecalcs#4
xform 0 1088 976
p 1024 1038 100 0 -1 CALC:B=0?A+1:0
p 1056 926 100 0 0 DISV:1
p 1040 1006 100 0 -1 SCAN:1 second
p 1056 704 100 1024 -1 name:$(tcs)$(prefix)acTimeout
[comments]
