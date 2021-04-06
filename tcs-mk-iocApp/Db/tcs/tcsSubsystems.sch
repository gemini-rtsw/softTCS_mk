[schematic2]
uniq 1
[tools]
[detail]
s 1392 -64 100 0 Subsystem simulation records
s 1408 -16 100 0 Gemini Telescope Control System
s 1280 1216 100 0 $Id: tcsSubsystems.sch,v 1.8 2010/02/26 19:05:55 gemvx Exp $
[cell use]
use bb200tr -624 -296 -100 0 frame
xform 0 656 528
use tcsGGFollowStat 1504 503 100 0 tcsGGFollowStat#13
xform 0 1632 648
use tcsGsaoiSubsys -128 39 100 0 tcsGsaoiSubsys#12
xform 0 48 128
p -108 12 100 0 1 seta:subnam gsaoi
p -112 -16 100 0 1 setb:subsys $(gsaoi)sad:dc:
p -112 -48 100 0 1 setc:noFollow 0
p -112 -80 100 0 1 setd:record heartBeat
use tcsAomSubsys 448 39 100 0 tcsAomSubsys#11
xform 0 624 128
p 576 96 100 0 -1 seta:subnam aom
p 576 64 100 0 -1 setb:subsys $(aom)
p 576 32 100 0 -1 setc:noFollow 0
p 576 0 100 0 -1 setd:record heartbeat
use tcsSubsys -104 904 100 0 tcsSubsys#0
xform 0 48 992
p 0 942 100 0 -1 seta:subnam mc
p 0 910 100 0 -1 setb:subsys $(mc)
p 0 880 100 0 -1 setc:noFollow 0
p 0 848 100 0 -1 setd:record present
use tcsSubsys 472 904 100 0 tcsSubsys#1
xform 0 624 992
p 576 958 100 0 -1 seta:subnam cr
p 576 926 100 0 -1 setb:subsys $(cr)
p 576 896 100 0 -1 setc:noFollow 0
p 576 864 100 0 -1 setd:record present
use tcsSubsys -104 616 100 0 tcsSubsys#3
xform 0 48 704
p 0 670 100 0 -1 seta:subnam ao
p 0 638 100 0 -1 setb:subsys $(ao)
p 0 608 100 0 -1 setc:noFollow 0
p 0 576 100 0 -1 setd:record sad:heartBeat
use tcsSubsys 472 616 100 0 tcsSubsys#4
xform 0 624 704
p 576 670 100 0 -1 seta:subnam ec
p 576 638 100 0 -1 setb:subsys $(ec)
p 576 608 100 0 -1 setc:noFollow 1
p 576 576 100 0 -1 setd:record present
use tcsSubsys 1048 616 100 0 tcsSubsys#5
xform 0 1200 704
p 1152 670 100 0 -1 seta:subnam m1
p 1152 638 100 0 -1 setb:subsys $(m1)
p 1152 608 100 0 -1 setc:noFollow 1
p 1152 576 100 0 -1 setd:record present
use tcsSubsys -104 328 100 0 tcsSubsys#6
xform 0 48 416
p 0 382 100 0 -1 seta:subnam m2
p 0 350 100 0 -1 setb:subsys $(m2)
p 0 320 100 0 -1 setc:noFollow 0
p 0 288 100 0 -1 setd:record present
use tcsSubsys 472 328 100 0 tcsSubsys#7
xform 0 624 416
p 576 382 100 0 -1 seta:subnam ws
p 576 350 100 0 -1 setb:subsys $(ws)
p 576 288 100 0 -1 setc:noFollow 1
p 576 256 100 0 -1 setd:record present
use tcsSubsys 1048 328 100 0 tcsSubsys#9
xform 0 1200 416
p 1152 382 100 0 -1 seta:subnam gp
p 1152 350 100 0 -1 setb:subsys $(gp)sad:
p 1152 304 100 0 -1 setc:noFollow 1
p 1152 272 100 0 -1 setd:record present
use tcsAgSubsys 1048 904 100 0 tcsAgSubsys#8
xform 0 1200 992
p 1152 958 100 0 -1 seta:subnam ag
p 1152 926 100 0 -1 setb:subsys $(ag)
p 1152 896 100 0 -1 setc:noFollow 0
p 1152 864 100 0 -1 setd:record present
[comments]
