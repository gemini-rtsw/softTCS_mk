[schematic2]
uniq 44
[tools]
[detail]
w 120 -693 100 0 STAT inhier.STAT.P 0 -704 288 -704 288 -608 448 -608 ecalcs.stop.INPB
w 284 -277 100 0 STAT junction 288 -608 288 64 432 64 ecalcs.start.INPB
w 840 -757 100 0 SPID junction 768 -768 960 -768 outhier.SPID.p
w 552 -509 100 0 SPID ecalcs.stop.VAL 736 -768 768 -768 768 -512 384 -512 384 -576 448 -576 ecalcs.stop.INPA
w 840 -85 100 0 STID junction 768 -96 960 -96 outhier.STID.p
w 552 171 100 0 STID ecalcs.start.VAL 720 -96 768 -96 768 160 384 160 384 96 432 96 ecalcs.start.INPA
w 252 -757 100 0 SPIN inhier.SPIN.P 0 -544 192 -544 192 -960 448 -960 ecalcs.stop.SLNK
w 192 -285 100 0 STIN inhier.STIN.P 0 -288 432 -288 ecalcs.start.SLNK
s 1360 816 100 0 $Id: tcsCadPlus.sch,v 1.1.1.1 1998/11/08 00:20:30 epics Exp $
n -96 -224 256 128 100
This represents the contents
of a hierarchical symbol
"cadplus", to be used to
count the number of START
and STOP activations of each
CAD record. 
_
[cell use]
use bc200tr -1248 -1656 -100 0 frame
xform 0 432 -352
p 1328 -1488 100 0 1 author:S.M.Beard
p 1552 -1488 100 0 -1 border:C
p 1312 -1520 100 0 1 checked:S.M.Beard
p 1584 -1488 100 0 -1 date:21 Jun 96
p 1552 -1376 100 0 -1 project:Core Instrument Control System
p 1552 -1440 100 0 -1 title:CAD start and stop counter
use outhier 928 -809 100 0 SPID
xform 0 944 -768
use outhier 928 -137 100 0 STID
xform 0 944 -96
use inhier -16 -745 100 0 STAT
xform 0 0 -704
use inhier -16 -585 100 0 SPIN
xform 0 0 -544
use inhier -16 -329 100 0 STIN
xform 0 0 -288
use ecalcs 448 -1049 100 0 stop
xform 0 592 -784
p 512 -1072 100 0 1 CALC:B=0?A+1:A
p 640 -1120 100 1024 1 name:$(tcs)$(cad)P:$(I)
use ecalcs 432 -377 100 0 start
xform 0 576 -112
p 496 -400 100 0 1 CALC:B=0?A+1:A
p 656 -448 100 1024 1 name:$(tcs)$(cad)P:$(I)
[comments]
