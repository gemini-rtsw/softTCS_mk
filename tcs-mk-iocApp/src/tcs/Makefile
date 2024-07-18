TOP=../../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

LIBRARY_IOC = tcs

# tcs.dbd will be created and installed
DBD += tcs.dbd
DBD += tcsFunc.dbd

# tcs.dbd will be made up from these files:
tcs_DBD += base.dbd
tcs_DBD += geminiRecords.dbd        
tcs_DBD += pvload.dbd   
tcs_DBD += timelibSupp.dbd 
tcs_DBD += slalib.dbd 
tcs_DBD += tcslibSupp.dbd 
#tcs_DBD += tptlib.dbd 
#tcs_DBD += astlib.dbd 
tcs_DBD += listAlarmRecords.dbd 
#tcs_DBD += menuScan.dbd 
tcs_DBD += timeProbeSupp.dbd 

# tcs_registerRecordDeviceDriver.cpp derives from tcs.dbd
tcs_SRCS += tcs_registerRecordDeviceDriver.cpp

tcs_SRCS += tcsAdjustCads.c
tcs_SRCS += tcsAoMechCommands.c
tcs_SRCS += tcsChopControl.c
tcs_SRCS += tcsCombine.c
tcs_SRCS += tcsCommands.c
tcs_SRCS += tcsConfig.c
tcs_SRCS += tcsCotran.c
tcs_SRCS += tcsDisplay.c
tcs_SRCS += tcsEcsLib.c
tcs_SRCS += tcsEnvCommands.c
tcs_SRCS += tcsEphemeris.c
tcs_SRCS += tcsGuide.c
tcs_SRCS += tcsGuideCad.c
tcs_SRCS += tcsHandset.c
tcs_SRCS += tcsHandsetCads.c
tcs_SRCS += tcsInterlocks.c
tcs_SRCS += tcsLimits.c
tcs_SRCS += tcsMechCommands.c
tcs_SRCS += tcsOffsetCad.c
tcs_SRCS += tcsOptics.c
tcs_SRCS += tcsPointing.c
tcs_SRCS += tcsProbeLib.c
tcs_SRCS += tcsReadCadInfo.c
tcs_SRCS += tcsReadCarInfo.c
tcs_SRCS += tcsSaveLoadCad.c
tcs_SRCS += tcsSeqCommands.c
tcs_SRCS += tcsSlewCad.c
tcs_SRCS += tcsVtCads.c
tcs_SRCS += tcsSaveModel.c

INC += tcsCadInfo.h
INC += tcsCommands.h
INC += tcsConfig.h
INC += tcsCotran.h
INC += tcsDisplay.h
INC += tcsEcsLib.h
INC += tcsEphemeris.h
INC += tcsGlobal.h
INC += tcsGuide.h
INC += tcsInPosition.h
INC += tcsInterlocks.h
INC += tcsLimits.h
INC += tcsOptics.h
INC += tcsPointing.h
INC += tcsProbeLib.h
INC += tcsReadCarInfo.h
INC += tcsSeqCommands.h
INC += tcsTcb.h

LIBRARY_IOC += tcsSupport
tcsSupport_LIBS += seq pv
tcsSupport_LIBS += timeProbe
tcsSupport_LIBS += $(EPICS_BASE_IOC_LIBS)
tcsSupport_SRCS += tcsSeqInit.st
tcsSupport_SRCS += tcsReadHrwfs.st

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

