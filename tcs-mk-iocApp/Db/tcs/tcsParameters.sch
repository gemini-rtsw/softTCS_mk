[schematic2]
uniq 3
[tools]
[detail]
w 718 1931 100 0 n#2 estringouts.name.FLNK 608 1920 864 1920 864 1232 1088 1232 egenSub.storeTelIndex.SLNK
s 2624 2288 100 0 $Id: tcsParameters.sch,v 1.2 2009/12/01 14:00:06 cjm Exp $
s 2848 32 100 0 Gemini Telescope Control System
s 1264 2144 200 0 TCS Parameters
[cell use]
use egenSub 1088 1143 100 0 storeTelIndex
xform 0 1232 1568
p 1120 2000 100 0 -1 DESC:Set telescope index
p 865 917 100 0 0 FTA:STRING
p 865 917 100 0 0 FTVA:STRING
p 865 917 100 0 0 FTVB:LONG
p 865 885 100 0 0 FTVC:STRING
p 1152 1088 100 0 1 SNAM:tcsProbeSetTelescope
p 880 1904 100 0 -1 def(INPA):$(tcs)name
use estringouts 376 1832 100 0 name
xform 0 480 1904
p 400 1998 100 0 -1 DESC:Name of telescope
p 288 1870 100 0 0 VAL:Gemini
p 688 1870 100 0 -1 def(OUT):$(sad)name
p 608 1888 75 768 -1 pproc(OUT):PP
use bc200tr 32 -184 -100 0 frame
xform 0 1712 1120
[comments]
