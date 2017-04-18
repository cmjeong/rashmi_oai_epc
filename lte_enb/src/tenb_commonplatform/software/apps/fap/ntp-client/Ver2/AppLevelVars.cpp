/*
 * AppLevelVars.cpp
 *
 *  Created on: 10-Sep-2009
 *      Author: jouroussoff
 */

#include "AppLevelVars.h"

u32 tAppLevelVars::m_numInBurst;
u32 tAppLevelVars::m_debugLevel;
long double tAppLevelVars::m_delayIgnoreThreshold;
long double tAppLevelVars::m_massiveStep;
bool tAppLevelVars::m_correctStepChangeResult;
u32 tAppLevelVars::m_sdCalcLength;

void tAppLevelVars::InitVars()
{
    m_debugLevel = DEFAULT_DEBUG_LEVEL;
    m_delayIgnoreThreshold = DEFAULT_DELAY_THRESHOLD;
    m_massiveStep = DEFAULT_MASSIVE_STEP;
    m_correctStepChangeResult = DEFAULT_CORRECT_STEP_CHANGE_RESULT;
    m_sdCalcLength = DEFAULT_SD_CALC_LENGTH;
}

void tAppLevelVars::SetNumInBurst(u32 inNumInBurst)
{
    m_numInBurst = inNumInBurst;
}
u32 tAppLevelVars::GetNumInBurst(void)
{
    return (m_numInBurst);
}
void tAppLevelVars::SetDebugLevel(u32 inDebugLevel)
{
    m_debugLevel = inDebugLevel;
}
u32 tAppLevelVars::GetDebugLevel(void)
{
    return (m_debugLevel);
}

long double tAppLevelVars::GetdelayIgnoreThreshold(void)
{
    return (m_delayIgnoreThreshold);
}

void tAppLevelVars::SetdelayIgnoreThreshold(long double inDelayThreshold)
{
    m_delayIgnoreThreshold = inDelayThreshold;
}
