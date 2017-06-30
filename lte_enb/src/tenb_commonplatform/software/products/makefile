
###############################################################################
#
# The uber makefile.  Makes all products.
#
# Copyright � 3Way Networks Ltd
#
###############################################################################

# List of directories to run 'make'.


DIRS = \
  products/fap/dbx/test \
  products/fap/hbs2/hbs2-iu \
  products/fap/hbs2/hbs2-sip \
  products/fap/hbs2/hbs2-handbag \
  products/fap/hbs2/hbs2-rrc \
  products/fap/hbs2/hbs2-bae \
  products/fap/hbs2/hbs2-factory

# Path to 'software' directory.
TOP = $(shell pwd)/..

DIRS_BUILD = $(DIRS:%=$(TOP)/%.build)
DIRS_CLEAN = $(DIRS:%=$(TOP)/%.clean)

.PHONY : build clean \
         $(DIRS_BUILD) $(DIRS_CLEAN)

build: $(DIRS_BUILD)
clean: $(DIRS_CLEAN)

update:
	@echo "######## updating from SVN #########"
	@cd $(TOP) && svn update
	
$(DIRS_BUILD):
	@echo "######## Building $(subst .build,,$@) #########"
	@cd $(subst .build,,$@) && $(MAKE)
	@echo "######## Completed $(subst .build,,$@) #########"
	@echo ""

$(DIRS_CLEAN):
	@echo "######## Cleaning $(subst .clean,,$@) #########"
	@cd $(subst .clean,,$@) && $(MAKE) clean
	@echo "######## Completed $(subst .clean,,$@) #########"
	@echo ""
