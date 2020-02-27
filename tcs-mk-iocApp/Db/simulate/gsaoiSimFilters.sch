[schematic2]
uniq 25
[tools]
[detail]
w 1010 354 100 0 n#1 estringins.estringins#4.FLNK 1000 344 1088 344 1088 248 664 248 664 168 744 168 eais.eais#1.SLNK
w 1010 194 100 0 n#2 eais.eais#1.FLNK 1000 184 1080 184 1080 80 672 80 672 -8 744 -8 eais.eais#2.SLNK
w 1010 18 100 0 n#3 eais.eais#2.FLNK 1000 8 1080 8 1080 -96 696 -96 696 -176 744 -176 eais.eais#3.SLNK
w -366 698 100 0 n#4 gsaoiSimFilter.gsaoiSimFilter#13.LUTFLNK -432 688 -272 688 -272 1136 -184 1136 estringouts.estringouts#98.SLNK
w 82 1162 100 0 n#5 estringouts.estringouts#98.FLNK 72 1152 144 1152 144 1032 -232 1032 -232 944 -192 944 eaos.eaos#87.SLNK
w 74 986 100 0 n#6 eaos.eaos#87.FLNK 64 976 160 976 160 840 -224 840 -224 744 -192 744 eaos.eaos#91.SLNK
w 74 786 100 0 n#7 eaos.eaos#91.FLNK 64 776 160 776 160 656 -232 656 -232 544 -192 544 eaos.eaos#95.SLNK
w -358 826 100 0 n#8 gsaoiSimFilter.gsaoiSimFilter#13.Fname -424 816 -288 816 -288 1168 -184 1168 estringouts.estringouts#98.DOL
w -358 730 100 0 n#9 gsaoiSimFilter.gsaoiSimFilter#13.Xoff -424 720 -248 720 -248 976 -192 976 eaos.eaos#87.DOL
w -358 762 100 0 n#10 gsaoiSimFilter.gsaoiSimFilter#13.Yoff -424 752 -208 752 -208 776 -192 776 eaos.eaos#91.DOL
w -358 890 100 0 n#11 gsaoiSimFilter.gsaoiSimFilter#13.Zoff -424 880 -312 880 -312 576 -192 576 eaos.eaos#95.DOL
w 58 -430 100 0 n#12 eaos.eaos#122.FLNK 48 -440 144 -440 144 -576 -240 -576 -240 -672 -208 -672 eaos.eaos#124.SLNK
w -374 -710 100 0 n#13 gsaoiSimFilter.gsaoiSimFilter#19.LUTFLNK -424 -720 -320 -720 -320 -280 -200 -280 estringouts.estringouts#128.SLNK
w 66 -254 100 0 n#14 estringouts.estringouts#128.FLNK 56 -264 136 -264 136 -352 -248 -352 -248 -472 -208 -472 eaos.eaos#122.SLNK
w 58 -630 100 0 n#15 eaos.eaos#124.FLNK 48 -640 136 -640 136 -768 -264 -768 -264 -872 -216 -872 -216 -872 -208 -872 eaos.eaos#126.SLNK
w -366 -582 100 0 n#16 gsaoiSimFilter.gsaoiSimFilter#19.Fname -416 -592 -288 -592 -288 -248 -200 -248 estringouts.estringouts#128.DOL
w -366 -678 100 0 n#17 gsaoiSimFilter.gsaoiSimFilter#19.Xoff -416 -688 -304 -688 -304 -440 -208 -440 eaos.eaos#122.DOL
w -366 -646 100 0 n#18 gsaoiSimFilter.gsaoiSimFilter#19.Yoff -416 -656 -264 -656 -264 -640 -208 -640 eaos.eaos#124.DOL
w -366 -518 100 0 n#19 gsaoiSimFilter.gsaoiSimFilter#19.Zoff -416 -528 -344 -528 -344 -840 -208 -840 eaos.eaos#126.DOL
w -358 858 100 0 n#20 gsaoiSimFilter.gsaoiSimFilter#13.VAL -424 848 -368 848 -368 296 -208 296 esels.esels#139.INPA
w -366 -550 100 0 n#21 gsaoiSimFilter.gsaoiSimFilter#19.VAL -416 -560 -328 -560 -328 272 -208 272 -208 264 esels.esels#139.INPB
w -414 794 100 0 n#22 gsaoiSimFilter.gsaoiSimFilter#13.FLNK -424 784 -376 784 -376 -88 -208 -88 esels.esels#139.SLNK
w -406 -614 100 0 n#22 gsaoiSimFilter.gsaoiSimFilter#19.FLNK -416 -624 -360 -624 -360 -88 junction
w 90 162 100 0 n#23 esels.esels#139.FLNK 80 152 128 152 128 176 208 176 outhier.FLNK.p
w 90 130 100 0 n#24 esels.esels#139.VAL 80 120 144 120 144 88 208 88 outhier.VAL.p
[cell use]
use bc200tr -1408 -1184 100 0 bc200tr#99
xform 0 272 96
use eais 744 120 100 0 eais#1
xform 0 872 168
p 856 88 100 1024 1 name:$(sadtop)defocusX
use eais 744 -56 100 0 eais#2
xform 0 872 -8
p 856 -88 100 1024 1 name:$(sadtop)defocusY
use eais 744 -224 100 0 eais#3
xform 0 872 -176
p 856 -256 100 1024 1 name:$(sadtop)defocusZ
use estringins 744 296 100 0 estringins#4
xform 0 872 344
p 856 264 100 1024 1 name:$(sadtop)vfiltName
p 744 438 100 0 0 VAL:
use gsaoiSimFilter -712 656 100 0 gsaoiSimFilter#13
xform 0 -600 752
p -704 816 100 0 0 set1:ftva STRING
p -704 784 100 0 0 set2:ftvb STRING
p -704 752 100 0 0 set3:ftvc STRING
p -704 720 100 0 0 set4:ftvd STRING
use gsaoiSimFilter -704 -752 100 0 gsaoiSimFilter#19
xform 0 -592 -656
p -669 -721 100 0 1 setb:filtname vfilt2
p -653 -590 100 0 0 seta:
p -696 -592 100 0 0 set1:ftva STRING
p -696 -624 100 0 0 set2:ftvb STRING
p -696 -656 100 0 0 set3:ftvc STRING
p -696 -688 100 0 0 set4:ftvd STRING
use eaos -192 880 100 0 eaos#87
xform 0 -64 944
p -124 1017 100 0 1 OMSL:closed_loop
p -80 848 100 1024 1 name:$(prefix)filt1Xoffset
p 56 889 100 0 1 def(OUT):$(sadtop)defocusX.VAL
p 72 920 75 768 -1 pproc(OUT):PP
use eaos -192 680 100 0 eaos#91
xform 0 -64 744
p -124 817 100 0 1 OMSL:closed_loop
p -80 648 100 1024 1 name:$(prefix)filt1Yoffset
p 69 692 100 0 1 def(OUT):$(sadtop)defocusY.VAL
p 72 720 75 768 -1 pproc(OUT):PP
use eaos -192 480 100 0 eaos#95
xform 0 -64 544
p -124 617 100 0 1 OMSL:closed_loop
p -80 448 100 1024 1 name:$(prefix)filt1Zoffset
p 71 489 100 0 1 def(OUT):$(sadtop)defocusZ.VAL
p 72 520 75 768 -1 pproc(OUT):PP
use estringouts -184 1088 100 0 estringouts#98
xform 0 -56 1136
p -111 1197 100 0 1 OMSL:closed_loop
p -72 1056 100 1024 1 name:$(prefix)filt1Name
p 80 1105 100 0 1 def(OUT):$(sadtop)vfiltName.VAL
p 80 1128 75 768 -1 pproc(OUT):PP
use eaos -208 -536 100 0 eaos#122
xform 0 -80 -472
p -140 -399 100 0 1 OMSL:closed_loop
p -96 -568 100 1024 1 name:$(prefix)filt2Xoffset
p 40 -527 100 0 1 def(OUT):$(sadtop)defocusX.VAL
p 56 -496 75 768 -1 pproc(OUT):PP
use eaos -208 -736 100 0 eaos#124
xform 0 -80 -672
p -140 -599 100 0 1 OMSL:closed_loop
p -96 -768 100 1024 1 name:$(prefix)filt2Yoffset
p 53 -724 100 0 1 def(OUT):$(sadtop)defocusY.VAL
p 56 -696 75 768 -1 pproc(OUT):PP
use eaos -208 -936 100 0 eaos#126
xform 0 -80 -872
p -140 -799 100 0 1 OMSL:closed_loop
p -96 -968 100 1024 1 name:$(prefix)filt2Zoffset
p 55 -927 100 0 1 def(OUT):$(sadtop)defocusZ.VAL
p 56 -896 75 768 -1 pproc(OUT):PP
use estringouts -200 -328 100 0 estringouts#128
xform 0 -72 -280
p -127 -219 100 0 1 OMSL:closed_loop
p -88 -360 100 1024 1 name:$(prefix)filt2Name
p 64 -311 100 0 1 def(OUT):$(sadtop)vfiltName.VAL
p 64 -288 75 768 -1 pproc(OUT):PP
use esels -208 -136 100 0 esels#139
xform 0 -64 104
p -124 -137 100 1024 1 name:$(prefix)gsSFiltSel
p -150 168 100 0 1 SELM:High Signal
use outhier 173 137 100 0 FLNK
xform 0 192 176
use outhier 176 46 100 0 VAL
xform 0 192 88
[comments]
