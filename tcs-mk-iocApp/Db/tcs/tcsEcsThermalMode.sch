[schematic2]
uniq 31
[tools]
[detail]
w 984 306 100 0 n#23 estringouts.ecThermalMode.FLNK 1152 624 1200 624 1200 304 816 304 816 160 880 160 eais.ecWind.SLNK
s 736 960 100 0 schematic.
s 736 992 100 0 made to the ECS. It probably no longer needs to be a separate
s 736 1024 100 0 This schematic has been simplified considerably by changes
s 1920 -96 100 0 Generate thermal mode string
s 1888 -32 100 0 Gemini Telescope Control System
s 1664 1200 100 0 $Id: tcsEcsThermalMode.sch,v 1.1.1.1 1998/11/08 00:20:35 epics Exp $
s 448 1088 200 0 Provide TCS versions of Enclosure thermal mode parameters
[cell use]
use estringouts 920 536 100 0 ecThermalMode
xform 0 1024 608
p 864 702 100 0 -1 DESC:Current thermal mode of ECS
p 976 574 100 0 0 VAL:Passive
p 928 494 100 0 1 SCAN:1 second
p 656 638 100 0 -1 def(DOL):$(ec)thermalM
p 832 414 100 0 0 OMSL:closed_loop
use eais 904 88 100 0 ecWind
xform 0 1008 160
p 624 -290 100 0 0 ADEL:0.05
p 928 270 100 0 -1 DESC:Wind speed set point
p 944 14 100 0 1 EGU:km/h
p 624 -322 100 0 0 MDEL:0.05
p 624 -2 100 0 0 PREC:1
p 496 190 100 0 -1 def(INP):$(ec)thermalwindSetPoint
use bb200tr -128 -312 -100 0 frame
xform 0 1152 512
[comments]
