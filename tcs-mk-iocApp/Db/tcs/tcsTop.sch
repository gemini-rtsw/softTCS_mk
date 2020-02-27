[schematic2]
uniq 1
[tools]
[detail]
s 2672 1536 100 0 21 Jun 96
s 2960 1632 200 0 Gemini TCS
s 2896 1584 100 0 Gemini Telescope Control System
s 2848 2880 100 0 tcstop.sch
s 1008 2848 100 0 top is used to generate unique databases
s 1488 2848 100 0 for the TCS
s 1008 2768 100 0 The variables m2, ag etc. are used to generate
s 1008 2736 100 0 connections to either the real subsystem or
s 1008 2704 100 0 the TCS's own internal simulations. For
s 1008 2672 100 0 example to connect to the real m2 subsystem then you would
s 1008 2640 100 0 set variable m2 to M2. To connect to the TCS's own 
s 1008 2608 100 0 internal simulation you would set m2 to tcs:m2:
s 1760 1840 100 0 N.B. Due to the length of the names of commands
s 1760 1808 100 0 in the WFS, the macros for PWFS1, PWFS2 and OIWFS
s 1760 1776 100 0 when using the simulators must be tpwfs1:, tpwfs2: and toiwfs:
s 1760 1744 100 0 rather than tcs:pwfs1: etc.
[cell use]
use bb200tr 848 1368 -100 0 frame
xform 0 2128 2192
use tcs 1992 2056 100 0 tcs#0
xform 0 2096 2256
p 1968 2446 100 0 -1 seta:top ${tcs}
p 2032 2032 100 0 -1 setaa:gems ${gems}
p 1760 2398 100 0 -1 setb:m2 ${m2}
p 1760 2366 100 0 -1 setc:ag ${ag}
p 1760 2334 100 0 -1 setd:mc ${mc}
p 1760 2302 100 0 -1 sete:cr ${cr}
p 1760 2270 100 0 -1 setf:ao ${ao}
p 1760 2238 100 0 -1 setg:m1 ${m1}
p 1760 2206 100 0 -1 seth:ec ${ec}
p 1760 2174 100 0 -1 seti:ws ${ws}
p 1760 2142 100 0 -1 setj:gp ${gp}
p 1760 2110 100 0 -1 setk:sad ${sad}
p 2128 2448 100 0 -1 setl:tcs ${tcs}
p 2288 2398 100 0 -1 setm:CAD_MARK 0
p 2288 2366 100 0 -1 setn:CAD_START 3
p 2288 2304 100 0 -1 seto:CAR_IDLE 0
p 2288 2272 100 0 -1 setp:CAR_BUSY 2
p 2288 2240 100 0 -1 setq:CAR_ERROR 3
p 2288 2336 100 0 -1 setr:CAD_STOP 4
p 1760 2080 100 0 -1 sets:pwfs1 ${pwfs1}
p 1760 2048 100 0 -1 sett:pwfs2 ${pwfs2}
p 1760 2016 100 0 -1 setu:hrwfs ${hrwfs}
p 1760 1984 100 0 -1 setv:oiwfs ${oiwfs}
p 1760 1952 100 0 -1 setx:nici ${nici}
p 1760 1920 100 0 -1 sety:aom ${aom}
p 1760 1888 100 0 -1 setz:gsaoi ${gsaoi}
[comments]
