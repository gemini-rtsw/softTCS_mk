[schematic2]
uniq 9
[tools]
[detail]
w 2600 1971 100 0 n#1 tcsMechOiProbeCommands1.tcsMechOiProbeCommands1#145.MESS 2464 1968 2736 1968 2736 272 656 272 656 2048 1024 2048 eapply.apply85.INMA
w 2112 2147 100 0 n#2 eapply.apply85.MESS 1408 2144 2816 2144 2816 2096 2976 2096 outhier.MESS.p
w 1616 2051 100 0 n#3 eapply.apply85.OCLA 1408 2048 1824 2048 1824 1968 1888 1968 tcsMechOiProbeCommands1.tcsMechOiProbeCommands1#145.ICID
w 1624 2083 100 0 n#4 eapply.apply85.OUTA 1408 2080 1840 2080 1840 2064 1888 2064 tcsMechOiProbeCommands1.tcsMechOiProbeCommands1#145.DIR
w 2608 2067 100 0 n#5 tcsMechOiProbeCommands1.tcsMechOiProbeCommands1#145.VAL 2464 2064 2752 2064 2752 256 640 256 640 2080 1024 2080 eapply.apply85.INPA
w 2192 2179 100 0 n#6 eapply.apply85.VAL 1408 2176 2976 2176 outhier.VAL.p
w 448 1939 100 0 n#7 inhier.ICID.P 384 1936 512 1936 512 2144 1024 2144 eapply.apply85.CLID
w 704 2179 100 0 n#8 inhier.DIR.P 384 2176 1024 2176 eapply.apply85.DIR
s 2944 152 200 0 Gemini TCS
s 2840 32 100 0 C
s 2704 2320 100 0 $Id: tcsMechProbeCommands.sch,v 1.1.1.1 1998/11/08 00:20:42 epics Exp $
s 2848 112 100 0 TCS commands
[cell use]
use bc200tr 32 -120 -100 0 frame
xform 0 1712 1184
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
use tcsMechOiProbeCommands1 1888 1904 100 0 tcsMechOiProbeCommands1#145
xform 0 2176 2000
[comments]
