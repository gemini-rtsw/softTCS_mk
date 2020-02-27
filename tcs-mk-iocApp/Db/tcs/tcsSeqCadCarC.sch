[schematic2]
uniq 45
[tools]
[detail]
w 1296 818 100 0 n#44 eaos.Busy.OUT 1200 816 1440 816 1440 656 1552 656 ecars.ecars#14.IVAL
w 664 50 100 0 n#42 efanouts.Fan.LNK2 480 224 576 224 576 48 800 48 tcsAllSubsysCad.tcsAllSubsysCad#36.slnk
w 578 576 100 0 n#41 efanouts.Fan.LNK1 480 256 576 256 576 848 944 848 eaos.Busy.SLNK
w 920 882 100 0 n#39 hwin.hwin#22.in 944 880 944 880 eaos.Busy.DOL
w 210 232 100 0 n#33 ecad2.ecad2#8.STLK 160 240 208 240 208 176 240 176 efanouts.Fan.SLNK
w 224 690 100 0 n#30 ecad2.ecad2#8.MESS 160 688 336 688 336 816 464 816 outhier.MESS.p
w 306 832 100 0 n#29 ecad2.ecad2#8.VAL 160 720 304 720 304 896 464 896 outhier.VAL.p
w -360 658 100 0 n#28 inhier.ICID.P -400 656 -272 656 -272 688 -160 688 ecad2.ecad2#8.ICID
w -288 722 100 0 n#27 inhier.DIR.P -400 736 -368 736 -368 720 -160 720 ecad2.ecad2#8.DIR
s 848 688 100 0 - it must be set IDLE from elsewhere
s 912 720 100 0 CAR record is only set BUSY
s 1216 1168 100 0 $id$
s 752 928 100 0 BUSY
s 1440 -128 100 0 triggering subsystem CADs
s 1440 -96 100 0 Generic CAD/CAR for sequence command
s 1488 -48 100 0 Gemini Telescope Control System
[cell use]
use eaos 968 760 100 0 Busy
xform 0 1072 848
p 724 1034 100 0 0 DESC:Sets CAR record to BUSY
p 688 830 100 0 0 OMSL:closed_loop
p 1168 944 100 1024 1 name:$(tcs)$(seqcommand)$(I)
p 1200 816 75 768 -1 pproc(OUT):PP
use tcsAllSubsysCad 824 -152 100 0 tcsAllSubsysCad#36
xform 0 872 -16
p 736 -146 100 0 1 seta:cad $(seqcommand)
use efanouts 264 40 100 0 Fan
xform 0 360 192
p 272 0 100 0 1 name:$(tcs)$(seqcommand)$(I)
use outhier 456 856 100 0 VAL
xform 0 448 896
use outhier 456 776 100 0 MESS
xform 0 448 816
use inhier -392 696 100 0 DIR
xform 0 -400 736
use inhier -392 616 100 0 ICID
xform 0 -400 656
use hwin 776 840 100 0 hwin#22
xform 0 848 880
p 766 808 100 0 0 typ(in):val
p 755 872 100 0 -1 val(in):$(CAR_BUSY)
use ecars 1576 376 100 0 ecars#14
xform 0 1712 544
p 1552 366 100 0 1 name:$(tcs)$(seqcommand)C
use bb200tr -560 -328 -100 0 frame
xform 0 720 496
use ecad2 -136 152 100 0 ecad2#8
xform 0 0 464
p -96 952 100 0 0 FTVA:STRING
p -128 398 100 0 -1 SNAM:tcsCAD$(seqcommand)
p -256 526 100 0 0 def(INPA):
p 240 510 100 0 0 def(OUTA):
p -144 94 100 0 1 name:$(tcs)$(seqcommand)
p 160 496 75 768 -1 pproc(OUTA):PP
p -96 -168 100 0 0 typ(INPA):path
[comments]
