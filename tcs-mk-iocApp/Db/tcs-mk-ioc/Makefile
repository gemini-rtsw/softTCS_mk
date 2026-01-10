TOP=../../..
include $(TOP)/configure/CONFIG

#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

# Search for .db files in $SYS_DB_PATHS, the list 
# of paths output by "convertGemRelease.pl dbPaths"
vpath %.db $(SYS_DB_PATHS)

#TDCT_CFG = ../tdct.cfg

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this

DB += tcsNirsgOutputs.db
DB += tcsAogOutputs.db

#DB_INSTALLS += iocAdminRTEMS.db
#DB_INSTALLS += iocAdminSoft.db
#DB_INSTALLS += timeProbe.db


include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
$(COMMON_DIR)/%.db: %.db
	cp $< $@

clean:
	$(RM) *.bak *.dat
