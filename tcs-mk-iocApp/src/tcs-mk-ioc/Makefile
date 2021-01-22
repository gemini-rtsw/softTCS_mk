TOP=../../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = tcs-mk-ioc
# tcs-mk-ioc.dbd will be created and installed
DBD += tcs-mk-ioc.dbd

# tcs-mk-ioc.dbd will be made up from these files:
tcs-mk-ioc_DBD += base.dbd
tcs-mk-ioc_DBD += tcsFunc.dbd
tcs-mk-ioc_DBD += tcsSimFunc.dbd
tcs-mk-ioc_DBD += iocAdmin.dbd
tcs-mk-ioc_DBD += devIocStats.dbd
tcs-mk-ioc_DBD += geminiRecords.dbd
tcs-mk-ioc_DBD += pvload.dbd
tcs-mk-ioc_DBD += timelibSupp.dbd
tcs-mk-ioc_DBD += tcslibSupp.dbd
tcs-mk-ioc_DBD += slalib.dbd
#tcs-mk-ioc_DBD += tptlib.dbd
#tcs-mk-ioc_DBD += astlib.dbd
tcs-mk-ioc_DBD += listAlarmRecords.dbd
tcs-mk-ioc_DBD += menuScan.dbd
tcs-mk-ioc_DBD += iocInit.dbd

# tcs-mk-ioc_registerRecordDeviceDriver.cpp derives from tcs-mk-ioc.dbd
tcs-mk-ioc_SRCS += tcs-mk-ioc_registerRecordDeviceDriver.cpp
tcs-mk-ioc_SRCS += initTrace.c

# Build the main IOC entry point on workstation OSs.
tcs-mk-ioc_SRCS_DEFAULT += tcs-mk-iocMain.cpp

# Add all the support libraries used by this IOC
# tcs-mk-ioc_LIBS += xxx
tcs-mk-ioc_LIBS += devIocStats
tcs-mk-ioc_LIBS += geminiRecords
tcs-mk-ioc_LIBS += listAlarmRecords
tcs-mk-ioc_LIBS += tcs
tcs-mk-ioc_LIBS += tcsSim
tcs-mk-ioc_LIBS += tcsSupport
tcs-mk-ioc_LIBS += tcsSimSupport
tcs-mk-ioc_LIBS += timelib
tcs-mk-ioc_LIBS += astlib
tcs-mk-ioc_LIBS += tcslib
tcs-mk-ioc_LIBS += slalib
tcs-mk-ioc_LIBS += tptlib
tcs-mk-ioc_LIBS += pvload
tcs-mk-ioc_LIBS += seq pv

# Finally link to the EPICS Base libraries
tcs-mk-ioc_LIBS += $(EPICS_BASE_IOC_LIBS)

# PROD_IOC_linux = tcs-linux-mk-ioc

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

