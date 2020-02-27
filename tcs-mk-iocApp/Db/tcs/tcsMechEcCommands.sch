[schematic2]
uniq 128
[tools]
[detail]
w 1536 1988 100 0 n#99 eapply.apply82.OCLB 1408 1984 1712 1984 1712 1760 1888 1760 tcsMechEcCommands2.tcsMechEcCommands2#125.ICID
w 1568 2020 100 0 n#97 eapply.apply82.OUTB 1408 2016 1776 2016 1776 1856 1888 1856 tcsMechEcCommands2.tcsMechEcCommands2#125.DIR
w 1672 306 100 0 n#96 tcsMechEcCommands2.tcsMechEcCommands2#125.MESS 2464 1760 2704 1760 2704 304 688 304 688 1984 1024 1984 eapply.apply82.INMB
w 1672 290 100 0 n#95 tcsMechEcCommands2.tcsMechEcCommands2#125.VAL 2464 1856 2720 1856 2720 288 672 288 672 2016 1024 2016 eapply.apply82.INPB
w 1672 274 100 0 n#71 tcsMechEcCommands1.tcsMechEcCommands1#124.MESS 2464 1968 2736 1968 2736 272 656 272 656 2048 1024 2048 eapply.apply82.INMA
w 2088 2146 100 0 n#46 eapply.apply82.MESS 1408 2144 2816 2144 2816 2096 2976 2096 outhier.MESS.p
w 1592 2050 100 0 n#45 eapply.apply82.OCLA 1408 2048 1824 2048 1824 1968 1888 1968 tcsMechEcCommands1.tcsMechEcCommands1#124.ICID
w 1600 2082 100 0 n#44 eapply.apply82.OUTA 1408 2080 1840 2080 1840 2064 1888 2064 tcsMechEcCommands1.tcsMechEcCommands1#124.DIR
w 1672 260 100 0 n#39 tcsMechEcCommands1.tcsMechEcCommands1#124.VAL 2464 2064 2752 2064 2752 256 640 256 640 2080 1024 2080 eapply.apply82.INPA
w 2168 2178 100 0 n#22 eapply.apply82.VAL 1408 2176 2976 2176 outhier.VAL.p
w 744 2146 100 0 n#21 inhier.ICID.P 384 1936 512 1936 512 2144 1024 2144 eapply.apply82.CLID
w 680 2178 100 0 n#20 inhier.DIR.P 384 2176 1024 2176 eapply.apply82.DIR
s 2608 2352 100 0 $id$
s 2944 152 200 0 Gemini TCS
s 2840 32 100 0 C
s 2848 112 100 0 TCS commands
[cell use]
use tcsMechEcCommands2 1912 1672 100 0 tcsMechEcCommands2#125
xform 0 2176 1792
use tcsMechEcCommands1 1912 1880 100 0 tcsMechEcCommands1#124
xform 0 2176 2000
use outhier 2968 2056 100 0 MESS
xform 0 2960 2096
use outhier 2968 2136 100 0 VAL
xform 0 2960 2176
use inhier 392 1896 100 0 ICID
xform 0 384 1936
use inhier 392 2136 100 0 DIR
xform 0 384 2176
use eapply 1048 1544 100 0 apply82
xform 0 1216 1904
p 1164 1588 100 0 0 DESC:Top TCS command Apply
use bc200tr 32 -120 -100 0 frame
xform 0 1712 1184
[comments]
