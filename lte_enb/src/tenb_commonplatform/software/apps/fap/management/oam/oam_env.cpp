///////////////////////////////////////////////////////////////////////////////
//
// oam_env.cpp
//
// Software build types and general environment type stuff
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <system/Trace.h>
#include <system/StringUtils.h>
#include <system/FapHardwareConfig.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "oam_env.h"

bool oamEnv_isProductHbs2Rrc()
{
#ifdef PRODUCT_hbs2_rrc
    return true;
#else
    return false;
#endif
}

bool oamEnv_isProductHbs2Iu()
{
#ifdef PRODUCT_hbs2_iu
    return true;
#else
    return false;
#endif
}

bool oamEnv_isProductHbs2Sip()
{
#ifdef PRODUCT_hbs2_sip
    return true;
#else
    return false;
#endif
}

bool oamEnv_isProductHbs2Factory()
{
#ifdef PRODUCT_hbs2_factory
    return true;
#else
    return false;
#endif
}

bool oamEnv_isProductGeneric()
{
#ifdef PRODUCT_generic
    return true;
#else
    return false;
#endif
}
