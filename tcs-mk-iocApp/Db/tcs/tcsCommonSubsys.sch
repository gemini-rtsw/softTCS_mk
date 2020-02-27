[schematic2]
uniq 15
[tools]
[detail]
w 296 219 100 0 n#1 inhier.PRESENCE.P 136 216 456 216 elongouts.elongouts#2.DOL
w 1936 27 100 0 n#2 ecalcs.ecalcs#6.FLNK 1840 24 2032 24 2032 -40 2280 -40 elongins.elongins#9.SLNK
w 2728 -21 100 0 n#3 elongins.elongins#9.FLNK 2536 -24 2920 -24 outhier.TIMED_OUT.p
w 1132 187 100 0 n#4 elongouts.elongouts#2.VAL 712 184 1552 184 ecalcs.ecalcs#6.INPA
w 2060 -5 100 0 n#5 ecalcs.ecalcs#6.VAL 1840 -8 2280 -8 elongins.elongins#9.INP
w 2256 931 100 0 n#6 elongouts.elongouts#19.OUT 2104 928 2408 928 outhier.STATE.p
w 2256 995 100 0 n#7 elongouts.elongouts#19.FLNK 2104 992 2408 992 outhier.FLNK.p
w 1676 963 100 0 n#8 inhier.SLNK.P 1504 960 1848 960 elongouts.elongouts#19.SLNK
w 1676 995 100 0 n#9 inhier.SUBSYS_STATE.P 1504 992 1848 992 elongouts.elongouts#19.DOL
w 330 -142 -100 0 n#4 eseqs.eseqs#4.DOL1 320 -152 216 -152 216 16 832 16 832 184 junction
w 1170 -174 -100 0 n#10 elongouts.elongouts#3.VAL 1160 -184 1224 -184 1224 -64 176 -64 176 -184 320 -184 eseqs.eseqs#4.DOL2
w 650 -134 -100 0 n#11 eseqs.eseqs#4.LNK1 640 -152 824 -152 824 -184 904 -184 elongouts.elongouts#3.SLNK
w 642 -174 -100 0 n#12 eseqs.eseqs#4.LNK2 640 -184 768 -184 768 -520 904 -520 elongouts.elongouts#5.SLNK
w 1170 -502 -100 0 n#13 elongouts.elongouts#5.VAL 1160 -520 1304 -520 1304 152 1552 152 ecalcs.ecalcs#6.INPB
w 1178 -478 -100 0 n#14 elongouts.elongouts#5.FLNK 1160 -488 1384 -488 1384 -200 1552 -200 ecalcs.ecalcs#6.SLNK
[cell use]
use bc200tr -112 -840 100 0 bc200tr#15
xform 0 1568 440
use elongouts 456 120 100 0 elongouts#2
xform 0 584 184
p 519 87 100 1024 -1 name:$(tcs)$(subnam)Present
p 471 265 100 0 -1 DESC:Pulls in the system heartbeat
p 337 310 75 1280 0 palrm(DOL):MS
p 158 198 100 0 0 def(DOL):0.000000000000000e+00
p 338 328 75 1280 0 pproc(DOL):CA
p 536 149 100 0 -1 SCAN:1 second
p 296 102 100 0 0 OMSL:closed_loop
use elongouts 904 -248 100 0 elongouts#3
xform 0 1032 -184
p 967 -303 100 0 0 OMSL:supervisory
p 969 -277 100 1024 -1 name:$(tcs)$(subnam)PresentCopy
use eseqs 320 -536 100 0 eseqs#4
xform 0 480 -312
p 443 -248 100 0 1 DLY1:0.1
p 429 -382 100 0 -1 SCAN:10 second
p 365 -566 100 1024 -1 name:$(tcs)$(subnam)PresentWait
p 648 -144 75 1024 0 pproc(LNK1):PP
p 680 -144 75 1024 0 palrm(LNK1):NMS
p 444 -274 100 0 1 DLY2:9.1
p 648 -176 75 1024 0 pproc(LNK2):PP
p 680 -176 75 1024 0 palrm(LNK2):NMS
use elongouts 904 -584 100 0 elongouts#5
xform 0 1032 -520
p 744 -602 100 0 0 OMSL:supervisory
p 966 -614 100 1024 -1 name:$(tcs)$(subnam)DelayedPres
use ecalcs 1552 -264 100 0 ecalcs#6
xform 0 1696 -24
p 1641 21 100 0 -1 CALC:(A=B)||(C=3)
p 1499 -281 100 1024 -1 name:$(tcs)$(subnam)TimeoutCalc
p 1174 112 100 0 1 def(INPC):$(tcs)$(subnam)Present.SEVR
p 1264 -10 100 0 0 def(INPB):0.000000000000000e+00
use ebos 416 936 100 0 ebos#7
xform 0 544 1000
p 408 1092 100 0 -1 DESC:$(subnam) Simulate flag
p 410 866 100 0 1 ONAM:True
p 545 867 100 0 1 OSV:MINOR
p 431 913 100 1024 -1 name:$(tcs)$(subnam)IntSimulate
p 414 887 100 0 1 ZNAM:False
p 96 982 100 0 0 PINI:NO
p 546 887 100 0 1 ZSV:NO_ALARM
use elongins 2280 -88 100 0 elongins#9
xform 0 2408 -40
p 2024 -170 100 0 0 DISV:1
p 2258 -152 100 0 1 HIHI:1
p 2364 -152 100 0 1 HHSV:MAJOR
p 2392 -120 100 1024 -1 name:$(tcs)$(subnam)TimedOut
p 2277 31 100 0 -1 DESC:Indicates subsystem has timed out
use inhier 160 222 100 0 PRESENCE
xform 0 136 216
use outhier 2301 939 100 0 STATE
xform 0 2392 928
use outhier 2302 999 100 0 FLNK
xform 0 2392 992
use outhier 2776 -16 100 0 TIMED_OUT
xform 0 2904 -24
use elongouts 1872 872 100 0 elongouts#19
xform 0 1976 960
p 1800 1054 100 0 -1 DESC:Reflect subsystem state
p 1752 846 100 0 0 IVOA:Set output to IVOV
p 1592 444 100 0 0 IVOV:0
p 1528 910 100 0 0 OMSL:closed_loop
p 1928 910 100 0 -1 SCAN:Passive
p 1528 1006 100 0 0 def(DOL):
p 1960 864 100 1024 -1 name:$(tcs)$(subnam)State
p 1848 992 75 1280 -1 palrm(DOL):MS
p 1816 992 75 1280 -1 pproc(DOL):CA
use inhier 1529 1000 100 0 SUBSYS_STATE
xform 0 1504 992
use inhier 1534 965 100 0 SLNK
xform 0 1504 960
[comments]
