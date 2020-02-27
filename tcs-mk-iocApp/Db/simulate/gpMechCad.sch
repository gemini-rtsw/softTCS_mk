[schematic2]
uniq 30
[tools]
[detail]
w 1392 859 100 0 c#25 tcscar.tcscar#24.VAL 1376 848 1456 848 1456 816 1536 816 outhier.VAL.p
w 1432 891 100 0 FLNK tcscar.tcscar#24.FLNK 1376 880 1536 880 outhier.FLNK.p
w 1026 312 100 0 n#15 efanouts.f.LNK2 896 368 1024 368 1024 208 1136 208 eseqs.d.SLNK
w 454 -261 100 0 n#3 ecad20.ecad20#29.STLK 288 -272 656 -272 656 320 efanouts.f.SLNK
s 1728 1728 100 0 gpMechCad.sch
s 1840 -464 100 0 Gemini Telescope Control System
s 1792 -512 100 0 Generic CAD/CAR for subsystem
s 1792 -544 100 0 simulators
s 160 1600 250 0 Generic Simulated GPOL CAD
[cell use]
use bc200tr -1024 -744 -100 0 frame
xform 0 656 560
use ecad20 -32 -361 100 0 ecad20#29
xform 0 128 528
p -32 -160 100 0 1 SNAM:tcsGpGenericCAD
p 80 -368 100 1024 1 name:$(prefix)$(command)
use outhier 1504 839 100 0 FLNK
xform 0 1520 880
use outhier 1504 775 100 0 VAL
xform 0 1520 816
use tcscar 960 695 100 0 tcscar#24
xform 0 1168 816
p 1024 688 100 0 1 seta:car $(command)C
use eseqs 1160 120 100 0 d
xform 0 1296 368
p 1232 334 100 0 1 DLY1:$(delay)
p 752 -2356 100 0 0 PV:$(prefix)$(command):
p 1536 526 100 0 -1 def(LNK1):$(prefix)$(command)C:ms2.PROC
p 1136 560 75 1280 -1 palrm(SELL):NMS
use efanouts 680 184 100 0 f
xform 0 776 336
p 512 -468 100 0 0 PV:$(prefix)$(command):
p 592 478 100 0 1 def(LNK1):$(prefix)$(command)C:ms1.PROC
[comments]
