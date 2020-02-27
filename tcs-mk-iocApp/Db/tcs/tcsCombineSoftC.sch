[schematic2]
uniq 43
[tools]
[detail]
w 2424 939 100 0 FLNK ecars.softC.FLNK 2368 928 2528 928 outhier.FLNK.p
w 2424 1099 100 0 OMSS ecars.softC.OMSS 2368 1088 2528 1088 outhier.OMSS.p
w 920 11 100 0 VAL egenSubC.valCombine.INPT -400 672 -512 672 -512 0 2400 0 2400 1152 2368 1152 ecars.softC.VAL
w 2446 1163 100 0 VAL junction 2400 1152 2528 1152 outhier.VAL.p
w 1512 1611 100 0 n#31 eaos.busy.OUT 1120 1600 1952 1600 1952 1152 2048 1152 ecars.softC.IVAL
w 1956 603 100 0 n#31 eaos.eaos#12.OUT 1120 64 1952 64 1952 1152 junction
w 100 651 100 0 n#39 egenSubC.valCombine.VALD -112 1184 96 1184 96 128 864 128 eaos.eaos#12.DOL
w 612 539 100 0 n#38 efanouts.fan2.FLNK 480 992 608 992 608 96 864 96 eaos.eaos#12.SLNK
w 256 1227 100 0 n#37 egenSubC.valCombine.VALC -112 1216 672 1216 672 480 864 480 egenSubD.messCombine.INPT
w 1192 1355 100 0 n#35 estringouts.nullString.OUT 1120 1344 1312 1344 1312 1264 1440 1264 estringouts.imss.SLNK
w 1316 1155 100 0 n#35 egenSubD.messCombine.OUTA 1152 1056 1312 1056 1312 1264 junction
w 644 635 100 0 n#36 efanouts.fan2.LNK3 480 896 640 896 640 384 864 384 egenSubD.messCombine.SLNK
w 1496 1867 100 0 n#30 estringouts.estringouts#9.OUT 1120 1856 1920 1856 1920 1088 2048 1088 ecars.softC.IMSS
w 1784 1259 100 0 n#30 estringouts.imss.OUT 1696 1248 1920 1248 junction
w 644 1155 100 0 n#34 efanouts.fan2.LNK1 480 960 640 960 640 1360 864 1360 estringouts.nullString.SLNK
w 536 939 100 0 n#34 efanouts.fan2.LNK2 480 928 640 928 640 960 junction
w 164 1099 100 0 n#33 egenSubC.valCombine.VALB -112 1248 160 1248 160 960 288 960 efanouts.fan2.SELL
w 132 1187 100 0 n#32 efanouts.fan1.FLNK 480 1856 576 1856 576 1504 128 1504 128 880 240 880 efanouts.fan2.SLNK
w 568 1835 100 0 n#29 efanouts.fan1.LNK1 480 1824 704 1824 704 1872 864 1872 estringouts.estringouts#9.SLNK
w 100 1547 100 0 n#28 egenSubC.valCombine.VALA -112 1280 96 1280 96 1824 288 1824 efanouts.fan1.SELL
w 68 1139 100 0 n#27 egenSubC.valCombine.FLNK -112 544 64 544 64 1744 240 1744 efanouts.fan1.SLNK
w 808 1675 100 0 n#24 hwin.hwin#11.in 800 1664 864 1664 eaos.busy.DOL
w 1000 1787 100 0 n#23 estringouts.estringouts#9.FLNK 1120 1888 1216 1888 1216 1776 832 1776 832 1632 864 1632 eaos.busy.SLNK
s 2224 -192 100 0 generate softC CAR value
s 2224 -144 200 0 Gemini TCS
s 1904 2064 100 0 $Id: tcsCombineSoftC.sch,v 1.2 2002/04/16 16:10:15 cjm Exp $
s -512 1568 100 0 This record processes every time it is written
s -512 1536 100 0 to by an internal CAR record e.g. xconfigC,
s -512 1504 100 0 xxCommsentC etc.
s 256 2016 100 0 This fanout record will be triggerred only if the 
s 256 1984 100 0 current value of softC is IDLE and it is going to
s 256 1952 100 0 be set to ERR.  This is because a CAR can't be 
s 256 1920 100 0 set directly from IDLE to ERR.
[cell use]
use outhier 2496 1111 100 0 VAL
xform 0 2512 1152
use outhier 2496 1047 100 0 OMSS
xform 0 2512 1088
use outhier 2496 887 100 0 FLNK
xform 0 2512 928
use ecars 2048 871 100 0 softC
xform 0 2208 1040
p 2096 1216 100 0 -1 DESC:TCS softC CAR record
p 2160 864 100 1024 0 name:$(tcs)$(I)
use eaos 864 7 100 0 eaos#12
xform 0 992 96
p 848 192 100 0 -1 DESC:Computed softC CAR value
p 832 -178 100 0 0 EGU:none
p 608 78 100 0 0 OMSL:closed_loop
p 1120 64 75 768 -1 pproc(OUT):PP
use eaos 864 1543 100 0 busy
xform 0 992 1632
p 896 1728 100 0 -1 DESC:Output BUSY status
p 832 1358 100 0 0 EGU:none
p 608 1614 100 0 0 OMSL:closed_loop
p 1120 1600 75 768 -1 pproc(OUT):PP
use hwin 608 1623 100 0 hwin#11
xform 0 704 1664
p 611 1656 100 0 -1 val(in):$(CAR_BUSY)
use estringouts 864 1799 100 0 estringouts#9
xform 0 992 1872
p 912 1952 100 0 -1 DESC:Empty string
p 800 1838 100 0 0 VAL:
use estringouts 1440 1191 100 0 imss
xform 0 1568 1264
p 1467 1304 100 0 0 DESC:softC message
p 1376 1230 100 0 0 VAL:
p 1696 1248 75 768 -1 pproc(OUT):NPP
use estringouts 864 1287 100 0 nullString
xform 0 992 1360
p 928 1440 100 0 -1 DESC:Empty string
p 800 1326 100 0 0 VAL:
p 1120 1344 75 768 -1 pproc(OUT):PP
use efanouts 240 1607 100 0 fan1
xform 0 360 1760
p 96 1726 100 0 0 SELM:Specified
use efanouts 240 743 100 0 fan2
xform 0 360 896
p 96 862 100 0 0 SELM:Specified
use egenSubD 864 295 100 0 messCombine
xform 0 1008 720
p 880 1152 100 0 -1 DESC:Generate softC message
p 641 69 100 0 0 FTA:STRING
p 641 69 100 0 0 FTB:STRING
p 641 37 100 0 0 FTC:STRING
p 641 5 100 0 0 FTD:STRING
p 641 -27 100 0 0 FTE:STRING
p 641 -91 100 0 0 FTF:STRING
p 641 -91 100 0 0 FTG:STRING
p 641 -123 100 0 0 FTH:STRING
p 641 -155 100 0 0 FTI:STRING
p 641 -187 100 0 0 FTJ:STRING
p 641 69 100 0 0 FTK:STRING
p 641 69 100 0 0 FTL:STRING
p 641 37 100 0 0 FTM:STRING
p 641 5 100 0 0 FTN:STRING
p 641 -27 100 0 0 FTO:STRING
p 641 -91 100 0 0 FTP:STRING
p 641 -91 100 0 0 FTQ:STRING
p 641 -123 100 0 0 FTR:STRING
p 641 -155 100 0 0 FTS:STRING
p 944 480 100 0 1 FTT:LONG
p 944 1072 100 0 1 FTVA:STRING
p 1104 288 100 0 1 SNAM:tcsCombineMessSoftC
p 580 1098 100 0 0 def(INPA):$(tcs)xconfigC.OMSS
p 580 1066 100 0 0 def(INPB):$(tcs)aoCommSentC.OMSS
p 580 1034 100 0 0 def(INPC):$(tcs)agCommSentC.OMSS
p 580 1002 100 0 0 def(INPD):$(tcs)crCommSentC.OMSS
p 580 970 100 0 0 def(INPE):$(tcs)ecCommSentC.OMSS
p 580 938 100 0 0 def(INPF):$(tcs)m1CommSentC.OMSS
p 580 906 100 0 0 def(INPG):$(tcs)m2CommSentC.OMSS
p 580 874 100 0 0 def(INPH):$(tcs)mcCommSentC.OMSS
p 580 842 100 0 0 def(INPI):$(tcs)kernelC.OMSS
p 580 810 100 0 0 def(INPJ):$(tcs)loadC.OMSS
p 580 778 100 0 0 def(INPK):$(tcs)saveC.OMSS
p 580 746 100 0 0 def(INPL):$(tcs)gpCommSentC.OMSS
p 1152 1066 75 0 -1 pproc(OUTA):PP
use egenSubC -400 487 100 0 valCombine
xform 0 -256 912
p -384 1344 100 0 -1 DESC:Generate softC CAR value
p -623 261 100 0 0 FTA:LONG
p -623 261 100 0 0 FTB:LONG
p -623 229 100 0 0 FTC:LONG
p -623 197 100 0 0 FTD:LONG
p -623 165 100 0 0 FTE:LONG
p -623 101 100 0 0 FTF:LONG
p -623 101 100 0 0 FTG:LONG
p -623 69 100 0 0 FTH:LONG
p -623 37 100 0 0 FTI:LONG
p -623 5 100 0 0 FTJ:LONG
p -623 5 100 0 0 FTK:LONG
p -623 5 100 0 0 FTL:LONG
p -623 5 100 0 0 FTM:LONG
p -623 5 100 0 0 FTN:LONG
p -623 5 100 0 0 FTO:LONG
p -623 5 100 0 0 FTP:LONG
p -623 5 100 0 0 FTQ:LONG
p -623 5 100 0 0 FTR:LONG
p -623 5 100 0 0 FTS:LONG
p -623 5 100 0 0 FTT:LONG
p -623 5 100 0 0 FTU:LONG
p -288 1280 100 0 1 FTVA:LONG
p -288 1248 100 0 1 FTVB:LONG
p -288 1216 100 0 1 FTVC:LONG
p -288 1184 100 0 1 FTVD:LONG
p -623 165 100 0 0 FTVE:LONG
p -176 480 100 0 1 SNAM:tcsCombineSoftC
use bc200tr -672 -408 -100 0 frame
xform 0 1008 896
[comments]
