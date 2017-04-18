#/********************************************************************16**
#
#            (c) Copyright 2012 by RadiSys Corporation. All rights reserved.
##
#     This software is confidential and proprietary to RadiSys Corporation.
#     No part of this software may be reproduced, stored, transmitted, 
#     disclosed or used in any form or by any means other than as expressly
#     provided by the written Software License Agreement between Radisys 
#     and its licensee.
#
#     Radisys warrants that for a period, as provided by the written
#     Software License Agreement between Radisys and its licensee, this
#     software will perform substantially to Radisys specifications as
#     published at the time of shipment, exclusive of any updates or 
#     upgrades, and the media used for delivery of this software will be 
#     free from defects in materials and workmanship.  Radisys also warrants 
#     that has the corporate authority to enter into and perform under the 
#     Software License Agreement and it is the copyright owner of the software 
#     as originally delivered to its licensee.
#
#     RADISYS MAKES NO OTHER WARRANTIES, EXPRESS OR IMPLIED, INCLUDING
#     WITHOUT LIMITATION WARRANTIES OF MERCHANTABILITY OR FITNESS FOR
#     A PARTICULAR PURPOSE WITH REGARD TO THIS SOFTWARE, SERVICE OR ANY RELATED
#     MATERIALS.
#
#     IN NO EVENT SHALL RADISYS BE LIABLE FOR ANY INDIRECT, SPECIAL,
#     CONSEQUENTIAL DAMAGES, OR PUNITIVE DAMAGES IN CONNECTION WITH OR ARISING
#     OUT OF THE USE OF, OR INABILITY TO USE, THIS SOFTWARE, WHETHER BASED
#     ON BREACH OF CONTRACT, TORT (INCLUDING NEGLIGENCE), PRODUCT
#     LIABILITY, OR OTHERWISE, AND WHETHER OR NOT IT HAS BEEN ADVISED
#     OF THE POSSIBILITY OF SUCH DAMAGE.
#
#                       Restricted Rights Legend:
#
#     This software and all related materials licensed hereby are
#     classified as "restricted computer software" as defined in clause
#     52.227-19 of the Federal Acquisition Regulation ("FAR") and were
#     developed entirely at private expense for nongovernmental purposes,
#     are commercial in nature and have been regularly used for
#     nongovernmental purposes, and, to the extent not published and
#     copyrighted, are trade secrets and confidential and are provided
#     with all rights reserved under the copyright laws of the United
#     States.  The government's rights to the software and related
#     materials are limited and restricted as provided in clause
#     52.227-19 of the FAR.
#
#                    IMPORTANT LIMITATION(S) ON USE
#
#     The use of this software is limited to the use set
##     forth in the written Software License Agreement between Radisys and
#     its Licensee. Among other things, the use of this software
#     may be limited to a particular type of Designated Equipment, as 
#     defined in such Software License Agreement.
#     Before any installation, use or transfer of this software, please
#     consult the written Software License Agreement or contact Radisys at
#     the location set forth below in order to confirm that you are
#     engaging in a permissible use of the software.
#
#                    RadiSys Corporation
#                    Tel: +1 (858) 882 8800
#                    Fax: +1 (858) 777 3388
#                    Email: support@trillium.com
#                    Web: http://www.radisys.com 
# 
#*********************************************************************17*/
#
################################################################################
#
# Makefile Options:
#
#  make [clean] PRODUCT=<product> [BUILD=<build>]
#
# Copyright radisys Limited
#
###############################################################################


CWD:= $(shell pwd)
TOP = $(shell pwd)/../../../..
#include $(TOP)/makefrags/products.mk

TARGET_NAME = sm

LIB_DEPS = \
  $(TOP)/libs/messaging/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libthreeway-messaging \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/$(HARDWARE)/$(BUILD)/libRadisys-mib-common \
  $(TOP)/libs/common/mobnet/obj/$(HARDWARE)/$(BUILD)/libthreeway-mobnet \
  $(TOP)/libs/common/comms/obj/$(HARDWARE)/$(BUILD)/libthreeway-comms \
  $(TOP)/libs/common/system/obj/$(HARDWARE)/$(BUILD)/libthreeway-system \
  #$(TOP)/libs/common/clog/obj/$(HARDWARE)/$(BUILD)/libRadisys-clog \

# We only have OSS libs for BF533+2006 and BF537+2008 (and i686)
# but we wing it when doing 3.1+2008 by using the BF537 versions...
#LIB_DEPS_PREBUILT = $(TOP)/thirdparty/oss/libs/$(BUILD)/libasn1code
SYSTEM_LIBS = pthread

ifneq ($(findstring bfin-uclinux-2008,$(BUILD)),bfin-uclinux-2008)
  # Need this for normal linux builds otherwise linker fails.
  # Seems bfin linker knows about this inherently.
  SYSTEM_LIBS := $(SYSTEM_LIBS) dl
endif

ifeq ($(TIP), YES)
CPPFLAGS = -DSMM_DATATYPE -DDYNUPDATE -Werror -DLTE_ADV -DLTE_ADV_UECAP -DTIP_OAM
CFLAGS = -DSMM_DATATYPE -DDYNUPDATE -DLTE_ADV -DLTE_ADV_UECAP -DTIP_OAM
else
CPPFLAGS = -DSMM_DATATYPE -DDYNUPDATE -Werror -DLTE_ADV -DLTE_ADV_UECAP
CFLAGS = -DSMM_DATATYPE -DDYNUPDATE -DLTE_ADV -DLTE_ADV_UECAP
endif

INCLUDE_PATHS = \
  $(TOP)/apps/fap/management/oam \
  $(TOP)/libs/common/include \
  $(TOP)/libs/common/system \
  $(TOP)/libs/common/ \
  $(TOP)/libs/ \
  $(TOP)/libs/common/mib-common/obj/$(PRODUCT)/generic/generic/ \
  $(TOP)/libs/messaging/transport \
  $(TOP)/thirdparty/encodix/Common \
  $(TOP)/../../enbapp/wr \
  $(TOP)/../../enbapp/

BFIN_UCLINUX_APP_STACK_SIZE = 0x80000

#include $(TOP)/makefrags/application.mk
ifeq ($(STATICALLY_LINKED),yes)
  include $(TOP)/makefrags/staticlibrary.mk
else
  include $(TOP)/makefrags/sharedlibrary.mk
endif
