TOP=../../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

LIBRARY_IOC = tcsSim
# tcsSim.dbd will be created and installed
DBD += tcsSim.dbd
DBD += tcsSimFunc.dbd 

# tcs-cp-ioc.dbd will be made up from these files:
tcsSim_DBD += base.dbd
tcsSim_DBD += geminiRecords.dbd        
tcsSim_DBD += pvload.dbd   
tcsSim_DBD += timelib.dbd 
tcsSim_DBD += slalib.dbd 
tcsSim_DBD += tcslib.dbd 
#tcsSim_DBD += tptlib.dbd 
#tcsSim_DBD += astlib.dbd 
#tcsSim_DBD += menuScan.dbd 

# Add all the support libraries used by tcsSim
# tcsSim_LIBS += xxx
tcsSim_LIBS += tcslib
tcsSim_LIBS += astlib

# tcsSim_registerRecordDeviceDriver.cpp derives from tcsSim.dbd
tcsSim_SRCS += tcsSim_registerRecordDeviceDriver.cpp

tcsSim_SRCS += tcsAgsSimulation.c
tcsSim_SRCS += tcsAomSimulation.c
tcsSim_SRCS += tcsAosSimulation.c
tcsSim_SRCS += tcsCrsSimulation.c
tcsSim_SRCS += tcsEcsSimulation.c
tcsSim_SRCS += tcsGpSimulation.c
tcsSim_SRCS += tcsGsaoiSimulation.c
tcsSim_SRCS += tcsM1sSimulation.c
tcsSim_SRCS += tcsM2sSimulation.c
tcsSim_SRCS += tcsMcsSimulation.c
tcsSim_SRCS += tcsNiciSimulation.c
tcsSim_SRCS += tcsOpticsSimulation.c
tcsSim_SRCS += tcsSimSimulation.c
tcsSim_SRCS += tcsSkySimulation.c

INC += tcsAgs.h
INC += tcsAom.h
INC += tcsAos.h
INC += tcsCrs.h
INC += tcsEcs.h
INC += tcsGsaoi.h
INC += tcsM1s.h
INC += tcsM2s.h
INC += tcsMcs.h
INC += tcsSimSimulation.h

LIBRARY_IOC += tcsSimSupport
tcsSimSupport_LIBS += seq pv
tcsSimSupport_LIBS += $(EPICS_BASE_IOC_LIBS)
tcsSimSupport_SRCS += tcsSeqSysSimulate.st
tcsSimSupport_SRCS += tcsSeqGsaoiSimulate.st

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

