[schematic2]
uniq 149
[tools]
[detail]
w 1666 340 100 0 n#148 tcsMechProbeCommands3.tcsMechProbeCommands3#144.MESS 2464 1552 2672 1552 2672 336 720 336 720 1920 1024 1920 eapply.apply85.INMC
w 1666 322 100 0 n#147 tcsMechProbeCommands3.tcsMechProbeCommands3#144.VAL 2464 1648 2688 1648 2688 320 704 320 704 1952 1024 1952 eapply.apply85.INPC
w 1634 1766 100 0 n#146 eapply.apply85.OCLC 1408 1920 1632 1920 1632 1552 1888 1552 tcsMechProbeCommands3.tcsMechProbeCommands3#144.ICID
w 1682 1830 100 0 n#145 eapply.apply85.OUTC 1408 1952 1680 1952 1680 1648 1888 1648 tcsMechProbeCommands3.tcsMechProbeCommands3#144.DIR
w 1536 1988 100 0 n#99 eapply.apply85.OCLB 1408 1984 1712 1984 1712 1760 1888 1760 tcsMechProbeCommands2.tcsMechProbeCommands2#143.ICID
w 1568 2020 100 0 n#97 eapply.apply85.OUTB 1408 2016 1776 2016 1776 1856 1888 1856 tcsMechProbeCommands2.tcsMechProbeCommands2#143.DIR
w 1672 306 100 0 n#96 tcsMechProbeCommands2.tcsMechProbeCommands2#143.MESS 2464 1760 2704 1760 2704 304 688 304 688 1984 1024 1984 eapply.apply85.INMB
w 1672 290 100 0 n#95 tcsMechProbeCommands2.tcsMechProbeCommands2#143.VAL 2464 1856 2720 1856 2720 288 672 288 672 2016 1024 2016 eapply.apply85.INPB
w 1672 274 100 0 n#71 tcsMechProbeCommands1.tcsMechProbeCommands1#142.MESS 2464 1968 2736 1968 2736 272 656 272 656 2048 1024 2048 eapply.apply85.INMA
w 2088 2146 100 0 n#46 eapply.apply85.MESS 1408 2144 2816 2144 2816 2096 2976 2096 outhier.MESS.p
w 1592 2050 100 0 n#45 eapply.apply85.OCLA 1408 2048 1824 2048 1824 1968 1888 1968 tcsMechProbeCommands1.tcsMechProbeCommands1#142.ICID
w 1600 2082 100 0 n#44 eapply.apply85.OUTA 1408 2080 1840 2080 1840 2064 1888 2064 tcsMechProbeCommands1.tcsMechProbeCommands1#142.DIR
w 1672 260 100 0 n#39 tcsMechProbeCommands1.tcsMechProbeCommands1#142.VAL 2464 2064 2752 2064 2752 256 640 256 640 2080 1024 2080 eapply.apply85.INPA
w 2168 2178 100 0 n#22 eapply.apply85.VAL 1408 2176 2976 2176 outhier.VAL.p
w 744 2146 100 0 n#21 inhier.ICID.P 384 1936 512 1936 512 2144 1024 2144 eapply.apply85.CLID
w 680 2178 100 0 n#20 inhier.DIR.P 384 2176 1024 2176 eapply.apply85.DIR
s 2944 152 200 0 Gemini TCS
s 2840 32 100 0 C
s 2704 2320 100 0 $Id: tcsMechProbeCommands.sch,v 1.1.1.1 1998/11/08 00:20:42 epics Exp $
s 2848 112 100 0 TCS commands
[cell use]
use tcsMechProbeCommands3 1912 1464 100 0 tcsMechProbeCommands3#144
xform 0 2176 1584
use tcsMechProbeCommands2 1912 1672 100 0 tcsMechProbeCommands2#143
xform 0 2176 1792
use tcsMechProbeCommands1 1912 1880 100 0 tcsMechProbeCommands1#142
xform 0 2176 2000
use outhier 2968 2056 100 0 MESS
xform 0 2960 2096
use outhier 2968 2136 100 0 VAL
xform 0 2960 2176
use inhier 392 1896 100 0 ICID
xform 0 384 1936
use inhier 392 2136 100 0 DIR
xform 0 384 2176
use eapply 1048 1544 -100 0 apply85
xform 0 1216 1904
p 1164 1588 100 0 0 DESC:Top TCS command Apply
p 1136 1536 100 1024 -1 name:$(top)apply$(appnum)
use bc200tr 32 -120 -100 0 frame
xform 0 1712 1184
[comments]
