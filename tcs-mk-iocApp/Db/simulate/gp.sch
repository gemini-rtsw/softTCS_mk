[schematic2]
uniq 263
[tools]
[detail]
w 1930 -1301 100 0 n#261 gpSimMechs.gpSimMechs#223.VAL 1824 -1312 2096 -1312 2096 -816 2144 -816 esels.bdValsSel.INPC
w 1946 -1093 100 0 n#260 gpSystem.gpSystem#235.VAL 1824 -1136 1872 -1136 1872 -1104 2080 -1104 2080 -784 2144 -784 esels.bdValsSel.INPB
w 1914 -677 100 0 n#258 gpParkAll.gpParkAll#229.VAL 1808 -688 2080 -688 2080 -752 2144 -752 esels.bdValsSel.INPA
w 1882 -1381 100 0 n#257 gpSimMechs.gpSimMechs#223.FLNK 1824 -1392 2000 -1392 2000 -1136 2144 -1136 esels.bdValsSel.SLNK
w 1890 -1061 100 0 n#257 gpSystem.gpSystem#235.FLNK 1824 -1072 2016 -1072 2016 -1136 junction
w 1898 -565 100 0 n#257 gpParkAll.gpParkAll#229.FLNK 1808 -576 2048 -576 2048 -1136 junction
w 2938 -949 100 0 n#211 eaos.bdValOut.OUT 2816 -960 3120 -960 3120 -928 3280 -928 ecars.activeC.IVAL
w 2474 -862 100 0 n#207 esels.bdValsSel.VAL 2432 -928 2464 -928 2464 -864 2544 -864 2544 -896 2560 -896 eaos.bdValOut.DOL
w 2434 -894 100 0 n#206 esels.bdValsSel.FLNK 2432 -896 2496 -896 2496 -928 2560 -928 eaos.bdValOut.SLNK
s 3664 -1888 100 0 GPOL subsystem simulator
s 3424 384 100 0 $Id: gp.sch,v 1.2 2002/07/02 07:41:53 cjm Exp $
s 3632 -1808 100 0 Gemini Telescope Control System
s 2384 -96 100 0 Dummy for sequence program only
[cell use]
use ebos 2448 -297 100 0 startLoop
xform 0 2576 -208
p 2148 -808 100 0 1 PV:$(gp)
use gpSystem 1624 -1256 100 0 gpSystem#235
xform 0 1712 -1136
use gpParkAll 1672 -744 100 0 gpParkAll#229
xform 0 1728 -616
use bc200tr 800 -2088 -100 0 frame
xform 0 2480 -784
use gpSimMechs 1624 -1480 100 0 gpSimMechs#223
xform 0 1712 -1376
p 1600 -1504 100 0 1 seta:prefix $(gp)
use esels 2168 -1208 100 0 bdValsSel
xform 0 2288 -944
p 2560 -240 100 0 0 PV:$(gp)
p 2224 -898 100 0 -1 SELM:High Signal
use eaos 2584 -1016 100 0 bdValOut
xform 0 2688 -928
p 2304 -946 100 0 0 OMSL:closed_loop
p 2304 -1522 100 0 0 PV:$(gp)
p 2816 -960 75 768 -1 pproc(OUT):PP
use ecars 3304 -1208 100 0 activeC
xform 0 3440 -1040
p 3271 -1960 100 0 0 PV:$(gp)
[comments]
