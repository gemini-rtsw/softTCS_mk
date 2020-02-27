[schematic2]
uniq 1
[tools]
[detail]
s 912 1072 100 0 tcsSimulations.sch
s 1088 256 100 0 Gemini Telescope Control System
[cell use]
use ba200tr 0 -24 -100 0 frame
xform 0 800 600
use simulations 520 504 100 0 simulations#0
xform 0 752 656
p 352 750 100 0 -1 seta:top ${tcs}
p 352 718 100 0 -1 setb:mc ${mc}
p 352 686 100 0 -1 setc:ec ${ec}
p 352 654 100 0 -1 setd:cr ${cr}
p 352 622 100 0 -1 sete:m2 ${m2}
p 352 590 100 0 -1 setf:ag ${ag}
p 352 558 100 0 -1 setg:ao ${ao}
p 352 526 100 0 -1 seth:m1 ${m1}
p 352 494 100 0 -1 seti:ws ${ws}
p 352 462 100 0 -1 setj:tcs ${tcs}
p 352 432 100 0 -1 setk:gi ${gi}
p 352 384 100 0 -1 setl:gp ${gp}
p 1024 750 100 0 -1 setm:CAD_MARK 0
p 1024 718 100 0 -1 setn:CAD_START 3
p 1024 686 100 0 -1 seto:CAR_IDLE 0
p 1024 654 100 0 -1 setp:CAR_BUSY 2
p 1024 622 100 0 -1 setq:CAR_ERROR 3
p 352 352 100 0 -1 setr:pwfs1 ${pwfs1}
p 352 320 100 0 -1 sets:pwfs2 ${pwfs2}
p 352 288 100 0 -1 sett:oiwfs ${oiwfs}
p 352 256 100 0 -1 setu:nici ${nici}
p 352 224 100 0 -1 setv:aom ${aom}
p 352 192 100 0 -1 setw:gsaoi ${gsaoi}
p 352 160 100 0 -1 setx:gems ${gems}
[comments]
