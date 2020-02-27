[schematic2]
uniq 19
[tools]
[detail]
w 376 683 100 0 n#18 estringouts.estringouts#15.FLNK 624 816 704 816 704 672 96 672 96 560 368 560 eaos.eaos#1.SLNK
w 832 795 100 0 n#16 estringouts.estringouts#15.OUT 624 784 1088 784 outhier.fmark.p
w 112 772 100 0 n#14 inhier.SubCadStart.P 0 768 272 768 272 800 368 800 estringouts.estringouts#15.SLNK
w 838 530 100 0 n#7 eaos.eaos#1.OUT 624 528 1088 528 outhier.fstart.p
w 350 594 100 0 n#5 hwin.START.in 368 592 368 592 eaos.eaos#1.DOL
s 1008 1344 100 0 $Id: tcsStartSubCAD.sch,v 1.4 2007/12/18 11:19:17 cjm Exp $
s 1248 112 100 0 Issue Subsystem CAD (no parameters)
[cell use]
use estringouts 368 727 100 0 estringouts#15
xform 0 496 800
p 320 880 100 0 -1 DESC:Mark the subsystem follow CAD
p 304 766 100 0 0 VAL:$(CAD_MARK)
p 720 800 100 0 -1 def(OUT):$(subsys)$(subcad).T
p 496 720 100 1024 1 name:$(tcs)$(prefix)M$(subcad)
p 624 784 75 768 -1 pproc(OUT):CA
use inhier -64 704 100 0 SubCadStart
xform 0 0 768
use bb200tr -752 -168 -100 0 frame
xform 0 528 656
use outhier 1080 744 100 0 fmark
xform 0 1072 784
use outhier 1080 488 100 0 fstart
xform 0 1072 528
use hwin 200 552 100 0 START
xform 0 272 592
p 190 520 100 0 0 typ(in):val
p 144 590 100 0 -1 val(in):$(CAD_START)
use eaos 392 472 100 0 eaos#1
xform 0 496 560
p 112 542 100 0 0 OMSL:closed_loop
p 768 542 100 0 -1 def(OUT):$(subsys)$(subcad).DIR
p 352 462 100 0 1 name:$(tcs)$(prefix)S$(subcad)
p 624 528 75 768 -1 pproc(OUT):CA
[comments]
