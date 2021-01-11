TOP = ../..
include $(TOP)/configure/CONFIG

SCRIPTS =sttcs-mk-ioc.boot
SCRIPTS+=stsim1-mk-ioc.boot
SCRIPTS+=stsim2-mk-ioc.boot

sttcs-mk-ioc.boot: ../sttcs-mk-ioc.src ../common.src $(wildcard $(TOP)/configure/RELEASE $(TOP)/configure/RELEASE.private)
	$(MSI3_15) $(SYS_BOOT_FLAGS) $(USR_BOOT_FLAGS) $< > $@
	chmod +x $@

stsim%-mk-ioc.boot: ../stsim-mk-ioc.src ../common.src $(wildcard $(TOP)/configure/RELEASE $(TOP)/configure/RELEASE.private)
	$(MSI3_15) $(SYS_BOOT_FLAGS) $(USR_BOOT_FLAGS) -MSIMTOP=$(shell echo $@ | sed -e 's/.*\([0-9]\).*/tc\1/') $< > $@
	chmod +x $@

include $(TOP)/configure/RULES
