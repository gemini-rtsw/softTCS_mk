[schematic2]
uniq 160
[tools]
[detail]
w 1666 379 100 0 n#159 tcsMechOiwfsCommands.tcsMechOiwfsCommands#157.MESS 2464 1552 2672 1552 2672 368 720 368 720 1920 1024 1920 eapply.apply857.INMC
w 1666 347 100 0 n#158 tcsMechOiwfsCommands.tcsMechOiwfsCommands#157.VAL 2464 1648 2688 1648 2688 336 704 336 704 1952 1024 1952 eapply.apply857.INPC
w 1634 1766 100 0 n#105 eapply.apply857.OCLC 1408 1920 1632 1920 1632 1552 1888 1552 tcsMechOiwfsCommands.tcsMechOiwfsCommands#157.ICID
w 1668 1830 100 0 n#103 eapply.apply857.OUTC 1408 1952 1664 1952 1664 1648 1888 1648 tcsMechOiwfsCommands.tcsMechOiwfsCommands#157.DIR
w 1536 1988 100 0 n#99 eapply.apply857.OCLB 1408 1984 1712 1984 1712 1760 1888 1760 tcsMechPwfs2Commands.tcsMechPwfs2Commands#153.ICID
w 1568 2020 100 0 n#97 eapply.apply857.OUTB 1408 2016 1776 2016 1776 1856 1888 1856 tcsMechPwfs2Commands.tcsMechPwfs2Commands#153.DIR
w 1672 306 100 0 n#96 tcsMechPwfs2Commands.tcsMechPwfs2Commands#153.MESS 2464 1760 2704 1760 2704 304 688 304 688 1984 1024 1984 eapply.apply857.INMB
w 1672 290 100 0 n#95 tcsMechPwfs2Commands.tcsMechPwfs2Commands#153.VAL 2464 1856 2720 1856 2720 288 672 288 672 2016 1024 2016 eapply.apply857.INPB
w 1672 274 100 0 n#71 tcsMechPwfs1Commands.tcsMechPwfs1Commands#152.MESS 2464 1968 2736 1968 2736 272 656 272 656 2048 1024 2048 eapply.apply857.INMA
w 2088 2146 100 0 n#46 eapply.apply857.MESS 1408 2144 2816 2144 2816 2096 2976 2096 outhier.MESS.p
w 1592 2050 100 0 n#45 eapply.apply857.OCLA 1408 2048 1824 2048 1824 1968 1888 1968 tcsMechPwfs1Commands.tcsMechPwfs1Commands#152.ICID
w 1600 2082 100 0 n#44 eapply.apply857.OUTA 1408 2080 1840 2080 1840 2064 1888 2064 tcsMechPwfs1Commands.tcsMechPwfs1Commands#152.DIR
w 1672 260 100 0 n#39 tcsMechPwfs1Commands.tcsMechPwfs1Commands#152.VAL 2464 2064 2752 2064 2752 256 640 256 640 2080 1024 2080 eapply.apply857.INPA
w 2168 2178 100 0 n#22 eapply.apply857.VAL 1408 2176 2976 2176 outhier.VAL.p
w 744 2146 100 0 n#21 inhier.ICID.P 384 1936 512 1936 512 2144 1024 2144 eapply.apply857.CLID
w 680 2178 100 0 n#20 inhier.DIR.P 384 2176 1024 2176 eapply.apply857.DIR
s 2624 2352 100 0 $Id: tcsMechAgCommands4.sch,v 1.4 1999/11/27 12:18:35 cjm Exp $
s 2848 112 100 0 TCS commands
s 2840 32 100 0 C
s 2944 152 200 0 Gemini TCS
[cell use]
use tcsMechOiwfsCommands 1888 1463 100 0 tcsMechOiwfsCommands#157
xform 0 2176 1584
use tcsMechPwfs2Commands 1888 1671 100 0 tcsMechPwfs2Commands#153
xform 0 2176 1792
use tcsMechPwfs1Commands 1888 1879 100 0 tcsMechPwfs1Commands#152
xform 0 2176 2000
use outhier 2968 2136 100 0 VAL
xform 0 2960 2176
use outhier 2968 2056 100 0 MESS
xform 0 2960 2096
use inhier 392 2136 100 0 DIR
xform 0 384 2176
use inhier 392 1896 100 0 ICID
xform 0 384 1936
use eapply 1048 1544 100 0 apply857
xform 0 1216 1904
p 1164 1588 100 0 0 DESC:Top TCS command Apply
use bc200tr 32 -120 -100 0 frame
xform 0 1712 1184
[comments]
