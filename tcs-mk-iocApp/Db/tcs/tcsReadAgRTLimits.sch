[schematic2]
uniq 1604
[tools]
[detail]
w 6540 715 100 0 n#1603 egenSub.setRTPosns.FLNK 6432 704 6720 704 outhier.FLNK.p
w 5964 747 100 0 n#1602 inhier.SLNK.P 5856 736 6144 736 egenSub.setRTPosns.SLNK
w 5964 1355 100 0 n#1601 inhier.P2RT.P 5856 1344 6144 1344 egenSub.setRTPosns.INPB
w 5964 1419 100 0 n#1600 inhier.P1RT.P 5856 1408 6144 1408 egenSub.setRTPosns.INPA
s 7424 -112 100 0 Schematic to read A&G data
s 7168 2144 100 0 $Id: tcsReadAgRTLimits.sch,v 1.1 2008/05/01 15:29:47 cjm Exp $
s 7424 -48 100 0 Gemini Telescope Control System
s 5888 1952 200 0 Fetch and store the rotary table angles
[cell use]
use outhier 6688 663 100 0 FLNK
xform 0 6704 704
use inhier 5840 1367 100 0 P1RT
xform 0 5856 1408
use inhier 5840 1303 100 0 P2RT
xform 0 5856 1344
use inhier 5840 695 100 0 SLNK
xform 0 5856 736
use egenSub 6144 647 100 0 setRTPosns
xform 0 6288 1072
p 6176 1504 100 0 -1 DESC:Store RT posns
p 6304 576 100 0 1 SCAN:Passive
p 6304 608 100 0 1 SNAM:tcsProbeRTPosns
use bc200tr 4592 -328 -100 0 frame
xform 0 6272 976
[comments]
