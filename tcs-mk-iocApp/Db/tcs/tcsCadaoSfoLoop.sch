[schematic2]
uniq 68
[tools]
[detail]
w 1156 1643 100 0 n#62 ecad8.ecad8#0.VALA 857 1633 889 1633 889 1632 1472 1632 elongouts.Demand.DOL
w 1028 972 100 0 n#61 ecad8.ecad8#0.STLK 857 961 1248 961 1248 1600 1472 1600 elongouts.Demand.SLNK
w 1912 1579 100 0 n#54 elongouts.Demand.OUT 1728 1568 2144 1568 outhier.c#53.p
w 1028 1797 100 0 n#18 ecad8.ecad8#0.MESS 857 1793 1248 1793 1248 1728 1376 1728 outhier.MESS.p
w 1092 1829 100 0 n#17 ecad8.ecad8#0.VAL 857 1825 1376 1825 1376 1824 outhier.VAL.p
w 322 1715 100 0 n#4 inhier.ICID.P 228 1713 452 1713 452 1793 537 1793 ecad8.ecad8#0.ICID
w 322 1859 100 0 n#3 inhier.DIR.P 228 1857 452 1857 452 1825 537 1825 ecad8.ecad8#0.DIR
s 1376 2112 100 0 In effect this command acts like a TCS immediate command.
s 1376 2176 100 0 to provide the correct protocol to the OCS.
s 1376 2208 100 0 and we rely instead on the busy/idle transtion of the TCS
s 1376 2240 100 0 Note that because of this there is no trigger of the Altair CAR
s 1376 2304 100 0 it simply writes directly into an Altair records.
s 1376 2336 100 0 it does not trigger a command in the Altair subsystem. Instead,
s 1376 2368 100 0 This TCS command is different from nearly all others in that
s 2592 144 100 0 Sciences Ltd.
s 2592 176 100 0 Observatory
s 2592 208 100 0 Copyright
s 2608 2400 100 0 $Id: tcsCadaoSfoLoop.sch,v 1.1 2006/12/12 15:02:29 cjm Exp $
s 2848 208 100 0 Gemini Telescope Control System
[cell use]
use elongouts 1472 1511 100 0 Demand
xform 0 1600 1600
p 1504 1680 100 0 -1 DESC:SFO Loop demand
p 1312 1518 100 0 0 OMSL:closed_loop
p 1792 1600 100 0 -1 def(OUT):$(ao)cc:lgszoomSfoLoop
p 1584 1504 100 1024 0 name:$(tcs)$(cad)$(I)
p 1728 1568 75 768 -1 pproc(OUT):CA
use outhier 1368 1784 100 0 VAL
xform 0 1360 1824
use outhier 1368 1688 100 0 MESS
xform 0 1360 1728
use outhier 2112 1527 100 0 c#53
xform 0 2128 1568
use inhier 236 1817 100 0 DIR
xform 0 228 1857
use inhier 236 1673 100 0 ICID
xform 0 228 1713
use ecad8 561 873 100 0 ecad8#0
xform 0 697 1377
p 553 1919 100 0 -1 DESC:Implement aoSFOLoop
p 640 1600 100 0 1 FTVA:LONG
p 640 1536 100 0 0 FTVB:DOUBLE
p 640 1472 100 0 0 FTVC:DOUBLE
p 633 1473 100 0 0 FTVD:STRING
p 633 1441 100 0 0 FTVE:STRING
p 633 1217 100 0 0 PREC:4
p 633 1087 100 0 1 SNAM:$(snam)
p 677 801 100 1024 1 name:$(tcs)$(cad)
use bc200tr 16 -72 -100 0 frame
xform 0 1696 1232
[comments]
