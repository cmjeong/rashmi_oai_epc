##############################################################################
#
# Makefile fragment for building a product.
#
# This simply calls other makefiles to build the required libraries and
# applications.
#
# Has the following targets:
#
#   build (default) - Builds all the code.
#   clean           - Cleans out all files created during the build.
#   uberclean       - Delete the following:
#                       *all* obj dirs anywhere under apps + libs + test/unittest
#                       *all* distro directories for all products
#                       test/unittest-libs dir
#                       libs/bin/threeway dir
#   cleantarget     - Cleans the final target only.
#   rmobjdirs       - Forcibly remove all obj dirs... makes an assumption that
#                     that makefile in each of DIRS actually puts its objects
#                     in an obj subdir.
#   distro          - Calls the script do-distro in the directory where make
#                     is being run.  This is intended to then create a
#                     'distro' sub-directory containing everything required
#                     for deployment on the target platform.
#   download        - FTP distro to a FAP with FAPIP=<ip-address> parameter.
#                     Doesn't transfer any config files.
#   downloadconfig  - FTP distro config files to a FAP with FAPIP=<ip-address> parameter.
#                     Only transfers config files.
#   downloadzip     - FTP distro tarball to a FAP with FAPIP=<ip-address> parameter.
#                     Puts file in /mnt for later unzipping.
#   reboot          - Sync and reboot the FAP with FAPIP=<ip-address> parameter.
#   release         - Does update, clean, distro (with gdbs) then packages distro
#                     along with release notes.  LASTREV must be specified.
#   unittests       - Build all the unittests for each directory.
#   cleanunittests  - Clean out all files created during unittests build.
#   rununittests    - Run all the unittests.
#
# And expects the following to be set:
#
#   TOP     - Path to top level 'software' directory.
#   DIRS    - List of directories relative to TOP to go into and run 'make'.
#   PRODUCT - Name of the product.  Gets converted to a define for use in
#             code.  E.g. PRODUCT = hbs2-iu will result in PRODUCT_hbs2_iu.
#             BUT, #ifdef's should be used sparingly.
#   BUILD   - Type of processor and OS e.g. i686-linux, bfin-uclinux-2006,
#             bfin-uclinux-2008 or bfin-uclinux-2008-mf
#
##############################################################################

# Check TOP is set.
ifeq ($(TOP),)
  $(error TOP must be set and reference the top level 'software' directory)
endif

include $(TOP)/makefrags/products.mk

ifndef RANDOMISE_COMPILE_ORDER
DIRS_BUILD = $(DIRS:%=$(TOP)/%.build)
else
DIRS_BUILD = $(shell $(TOP)/makefrags/randomise $(DIRS:%=$(TOP)/%.build))
endif
DIRS_DEPS = $(DIRS:%=$(TOP)/%.deps)
DIRS_CLEAN = $(DIRS:%=$(TOP)/%.clean)
DIRS_RMOBJDIRS = $(DIRS:%=$(TOP)/%.rmobjdirs)
DIRS_CLEANTARGET = $(DIRS:%=$(TOP)/%.cleantarget)
DIRS_UNITTESTS = $(DIRS:%=$(TOP)/%.unittests)
DIRS_CLEANUNITTESTS = $(DIRS:%=$(TOP)/%.cleanunittests)

.PHONY : all build distro clean release unittests cleanunittests rununittests coverage done \
	 uberclean $(DIRS_BUILD) $(DIRS_DEPS) $(DIRS_CLEAN) $(DIRS_RMOBJDIRS) $(DIRS_LOG) \
	 $(DIRS_UNITTESTS) $(DIRS_CLEANUNITTESTS)

.NOTPARALLEL:
# If mib-common included, build it first!
$(filter-out %mib-common.build,$(DIRS_BUILD) ): $(filter %mib-common.build,$(DIRS_BUILD))

build: done
done: $(DIRS_BUILD)

deps: donedeps
donedeps: $(DIRS_DEPS)

clean: doneclean
doneclean: $(DIRS_CLEAN) cleandirs

cleandirs:
	@echo "#################Removing 'obj' directories########################"
	cd $(TOP)/libs/common/mib-common && find . -name obj | xargs -i -r rm -r '{}'
	cd $(TOP)/apps/fap && find . -name obj | xargs -i -r rm -r '{}'
	cd $(TOP)/test/unittest && find . -name obj | xargs -i -r rm -r '{}'
	rm -rf $(TOP)/thirdparty/kb_getc/obj
	rm -rf $(TOP)/libs/common/obj
	rm -rf $(TOP)/libs/common/comms/obj
	rm -rf $(TOP)/libs/common/system/obj
	rm -rf $(TOP)/libs/common/system/obj
	rm -rf $(TOP)/libs/common/mobnet/obj
	rm -rf $(TOP)/libs/mib-core/obj
	rm -rf $(TOP)/libs/messaging/obj
	rm -rf $(TOP)/apps/utilities/cli/obj
	rm -rf $(TOP)/thirdparty/md5/obj
	rm -rf $(TOP)/libs/bin/threeway/hbs2-iu
	@echo "################Cleaning Directories completed Successfully#########"

uberclean:
	cd $(TOP)/libs && find . -name obj | xargs -i -r rm -r '{}'
	cd $(TOP)/apps && find . -name obj | xargs -i -r rm -r '{}'
	cd $(TOP)/test/unittest && find . -name obj | xargs -i -r rm -r '{}'
	cd $(TOP)/products && find . -name distro | xargs -r rm -r
	rm -rf $(TOP)/test/unittest/unittest-libs
	rm -rf $(TOP)/libs/bin/threeway

rmobjdirs: donermobjdirs
donermobjdirs: $(DIRS_RMOBJDIRS)

cleantarget: donecleantarget
donecleantarget: $(DIRS_CLEANTARGET)

unittests: unittestsdone
unittestsdone: $(DIRS_UNITTESTS)

cleanunittests: $(DIRS_CLEANUNITTESTS)
	rm -rf $(TOP)/test/unittest/unittest-libs
	rm -rf $(TOP)/test/unittest/unittest-runner/obj

distro: build
	#chmod +x ./do-distro
#	./do-distro

# specify the following as commands rather than dependencies to ensure they are executed
# sequentially when doing a multithreaded build.
release:
	$(MAKE) clean
	$(MAKE) distro WITH_GDBS=y
	chmod +x $(TOP)/makefrags/release
	LASTREV=$(LASTREV) TOP=$(TOP) $(TOP)/makefrags/release

download:
	chmod +x $(TOP)/products/fap/hbs2/etc/download-distro
	FAPIP=$(FAPIP) TOP=$(TOP) APP=$(APP) $(TOP)/products/fap/hbs2/etc/download-distro
	@date

downloadconfig:
	chmod +x $(TOP)/products/fap/hbs2/etc/download-distro
	FAPIP=$(FAPIP) TOP=$(TOP) $(TOP)/products/fap/hbs2/etc/download-distro -config
	@date

downloadzip:
	chmod +x $(TOP)/products/fap/hbs2/etc/download-distro
	FAPIP=$(FAPIP) TOP=$(TOP) $(TOP)/products/fap/hbs2/etc/download-distro -zip
	@date

ifdef FAPIP
reboot:
	@echo "Sync and rebooting FAP at $(FAPIP)..."
	@(sleep 1; echo -e "echo Remote reboot by `whoami`@`hostname` on `date`. > /dev/console; sync; reboot\r\n"; sleep 1) | nc -t $(FAPIP) 23 > /dev/null
else
reboot:
	@echo "FAPIP not defined, cannot reboot FAP"
endif

$(DIRS_DEPS):
	@echo "##################################################################"
	@echo "#"
	@echo "# Building dependency files $(subst .deps,,$@) for $(PRODUCT) on $(HARDWARE) with $(BUILD)"
	@echo "#"
	@echo "##################################################################"
	@cd $(subst .deps,,$@) && $(MAKE) deps PRODUCT=$(PRODUCT)
	@echo "######## Completed $(subst .deps,,$@) #########"
	@echo ""

$(DIRS_CLEAN):
	@echo "##################################################################"
	@echo "#"
	@echo "# Cleaning $(subst .clean,,$@) for $(PRODUCT) on $(HARDWARE) with $(BUILD)"
	@echo "#"
	@echo "##################################################################"
	@cd $(subst .clean,,$@) && $(MAKE) clean PRODUCT=$(PRODUCT)
	@echo "######## Completed $(subst .clean,,$@) #########"
	@echo ""

$(DIRS_RMOBJDIRS):
	@echo "##################################################################"
	@echo "#"
	@echo "# Removing 'obj' dir $(subst .rmobjdirs,,$@) for $(PRODUCT) on $(HARDWARE) with $(BUILD)"
	@echo "#"
	@echo "##################################################################"
	cd $(subst .rmobjdirs,,$@) && rm -rf obj
	@echo "######## Completed $(subst .rmobjdirs,,$@) #########"
	@echo ""

$(DIRS_CLEANTARGET):
	@echo "##################################################################"
	@echo "#"
	@echo "# Cleaning target $(notdir $(subst .cleantarget,,$@)) for $(PRODUCT) on $(HARDWARE) with $(BUILD)"
	@echo "#"
	@echo "##################################################################"
	@cd $(subst .cleantarget,,$@) && $(MAKE) -s cleantarget PRODUCT=$(PRODUCT)
	@echo "######## Completed $(notdir $(subst .cleantarget,,$@)) #########"
	@echo ""

$(DIRS_BUILD):
	@echo "##################################################################"
	@echo "#"
	@echo "# Building $(notdir $(subst .build,,$@)) for $(PRODUCT) on $(HARDWARE) with $(BUILD)"
	@echo "#"
	@echo "##################################################################"
	@cd $(subst .build,,$@) && $(MAKE) --no-print-directory PRODUCT=$(PRODUCT)
	@echo "######## Completed $(notdir $(subst .build,,$@)) #########"
	@echo ""

$(DIRS_UNITTESTS):
	@echo "##################################################################"
	@echo "#"
	@echo "# Building Unit Tests for $(notdir $(subst .unittests,,$@)) for $(PRODUCT) on $(HARDWARE) with $(BUILD)"
	@echo "#"
	@echo "##################################################################"
	@cd $(subst .unittests,,$@)/unittest && $(MAKE) PRODUCT=$(PRODUCT)
	@echo "######## Completed $(subst .unittests,,$@) #########"
	@echo ""

$(DIRS_CLEANUNITTESTS):
	@echo "##################################################################"
	@echo "#"
	@echo "# Cleaning Unit Tests for $(notdir $(subst .cleanunittests,,$@)) for $(PRODUCT) on $(HARDWARE) with $(BUILD)"
	@echo "#"
	@echo "##################################################################"
	@cd $(subst .cleanunittests,,$@)/unittest && $(MAKE) clean PRODUCT=$(PRODUCT)
	@echo "######## Completed $(subst .cleanunittests,,$@) #########"
	@echo ""

coverage:
	if [ ! -d $(TOP)/test/cpp_coverage ]; then mkdir -p $(TOP)/test/cpp_coverage; fi
	rm -rf $(TOP)/test/cpp_coverage/*
	rm -rf $(TOP)/products/unittests/*.info
	@echo "Coverage Report for mib-common"
	lcov -b $(TOP)/libs/common/mib-common -o mib-common.info -c -d $(TOP)/libs/common/mib-common/obj/test/generic/i686-linux
	cp $(TOP)/products/unittests/mib-common.info $(TOP)/test/cpp_coverage
	@echo "Coverage Report for messaging"
	lcov -b $(TOP)/libs/messaging -o messaging.info -c -d $(TOP)/libs/messaging/obj/test/generic/i686-linux
	cp $(TOP)/products/unittests/messaging.info $(TOP)/test/cpp_coverage
	@echo "Coverage Report for comms"
	lcov -b $(TOP)/libs/common/comms -o comms.info -c -d $(TOP)/libs/common/comms/obj/generic/i686-linux
	cp $(TOP)/products/unittests/comms.info $(TOP)/test/cpp_coverage
	@echo "Coverage Report for system"
	lcov -b $(TOP)/libs/common/system -o system.info -c -d $(TOP)/libs/common/system/obj/generic/i686-linux
	cp $(TOP)/products/unittests/system.info $(TOP)/test/cpp_coverage
	@echo "Coverage Report for mib-core"
	lcov -b $(TOP)/libs/mib-core -o mib-core.info -c -d $(TOP)/libs/mib-core/obj/test/generic/i686-linux
	cp $(TOP)/products/unittests/mib-core.info $(TOP)/test/cpp_coverage
	cd $(TOP)/test/cpp_coverage && \
	lcov -a mib-common.info -a messaging.info -a comms.info -a system.info -a mib-core.info -o totalcoverage.info 
	lcov --remove $(TOP)/test/cpp_coverage/totalcoverage.info  /usr/include/c++/4.6/i686-linux-gnu/bits/* /usr/include/c++/4.6/* /usr/include/c++/4.6/ext/* /usr/include/c++/4.6/bits/* /common/include/boost/detail/* /common/include/boost/* /messaging/messages/carb/* /messaging/messages/cli/* /messaging/messages/fntp/* /messaging/messages/cphy/* /messaging/messages/ike/* /messaging/messages/oam/* /messaging/messages/rem/* /messaging/messages/tenpin/* /messaging/messages/up-mgmt/* /messaging/messages/watchdog/* /platform/* -o codecoverage.info 
	genhtml -o result1 codecoverage.info

rununittests:
	# The libs are per product, hardware and build and the unittest-runner is per
	# hardware and build, even though this makefile will probably only ever be
	# called on an i686-linux host.
	cd $(TOP)/test/unittest/unittest-runner && \
	  $(MAKE) && \
	  LD_LIBRARY_PATH=../../../libs/bin/threeway/generic/i686-linux:../../../libs/bin/threeway/test/generic/i686-linux:../../../thirdparty/oss/libs/i686-linux \
	  obj/$(HARDWARE)/$(BUILD)/unittest-runner \
	  ../unittest-libs/$(HARDWARE)/$(BUILD)/

# These targets let autobuild script check for successful completion
# so don't change the text without consulting the person who looks
# after that.
unittestsdone:
	@echo "-----------------------------"
	@echo "BUILD COMPLETED SUCCESSFULLY!"
	@echo "-----------------------------"

done:
	@date
	@echo "-----------------------------"
	@echo "BUILD COMPLETED SUCCESSFULLY!"
	@echo "-----------------------------"

doneclean:
	@echo "-----------------------------"
	@echo "CLEAN COMPLETED SUCCESSFULLY!"
	@echo "-----------------------------"

donedeps:
	@echo "----------------------------------------"
	@echo "DEPENDENCY FILES GENERATED SUCCESSFULLY!"
	@echo "----------------------------------------"
