[schematic2]
uniq 1
[tools]
[detail]
s 1632 1488 100 0 TCS Status Alarm Database
s 1664 1536 200 0 Gemini TCS
s 1600 1424 100 0 21 Jun 96
s 1376 1408 100 0 Chris Mayer
s 1552 2384 100 0 tcsSad.tcs
[cell use]
use ba200tr 528 1272 -100 0 frame
xform 0 1328 1896
use tcsSadTcs 1048 1768 100 0 tcsSadTcs#0
xform 0 1344 1920
p 1280 1982 100 0 -1 seta:top ${tcs}
p 1280 1950 100 0 -1 setb:sad ${sad}
[comments]
