[schematic2]
uniq 4
[tools]
[detail]
w 166 907 100 0 Period#1 inhier.Period.P 48 896 320 896 eaos.period.SLNK
w 174 1259 100 0 Y#2 inhier.Y.P 48 1248 336 1248 eaos.d_gdr_winYo.SLNK
w 166 1515 100 0 X#3 inhier.X.P 48 1504 320 1504 eaos.d_gdr_winXo.SLNK
s 2032 2064 100 0 $Id: gsaoiProbe.sch,v 1.4 2010/06/15 14:08:59 cjm Exp $
s 2016 -128 100 0 Copyright
s 2016 -160 100 0 Observatory
s 2016 -192 100 0 Sciences Ltd.
s 656 1872 200 0 Records to hold ODGW parameters
[cell use]
use bc200tr -560 -408 -100 0 frame
xform 0 1120 896
use inhier 32 1463 100 0 X
xform 0 48 1504
use inhier 32 1207 100 0 Y
xform 0 48 1248
use inhier 32 855 100 0 Period
xform 0 48 896
use eaos 320 1415 100 0 d_gdr_winXo
xform 0 448 1504
p 320 1600 100 0 -1 DESC:X ordinate of left of window
p 288 1230 100 0 0 EGU:pixels
p 432 1408 100 1024 0 name:$(top)$(I)$(window)
use eaos 336 1159 100 0 d_gdr_winYo
xform 0 464 1248
p 336 1344 100 0 -1 DESC:Y ordinate of top of window
p 304 974 100 0 0 EGU:pixels
p 448 1152 100 1024 0 name:$(top)$(I)$(window)
use eaos 320 807 100 0 period
xform 0 448 896
p 320 992 100 0 -1 DESC:Window period
p 288 622 100 0 0 EGU:secs
p 432 800 100 1024 0 name:$(top)$(window)$(I)
use esirs 296 344 100 0 esirs#1
xform 0 480 496
p 223 240 100 0 0 DESC:AOM health record in simulation
p 223 224 100 0 0 FDSC:AOM health (simulation)
p 408 408 100 0 1 FTVL:STRING
p 323 325 100 1024 1 name:$(prefix)odgw$(window)followS
[comments]
