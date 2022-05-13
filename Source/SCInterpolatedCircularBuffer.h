/*
  ==============================================================================

    SCInterpolatedCircularBuffer.h
    Created: 13 May 2022 5:49:52pm
    Author:  Davis

  ==============================================================================
*/

#pragma once
#include "SCCircularBuffer.h"

namespace SCDsp
{
template <int pwr2DelayLen> class SCInterpolatedCircularBuffer : public SCCircularBuffer
{
public:
    SCInterpolatedCircularBuffer(float * memory) : SCCircularBuffer(memory)
    {
        
    }
    
    // override base class to provide fractional delay time functionality
    virtual float Read(float delayTime) override
    {
        uint32_t delayTimeInt = static_cast<uint32_t>(delayTime);
        float frac = delayTime - static_cast<float>(delayTimeInt);
        
        uint32_t readIndex = static_cast<uint32_t>(m_fReadIndex) - delayTimeInt;
        uint32_t readIndex_1 = readIndex + 1;
        
        float sample1 = m_fMemory[readIndex % DelayMask];
        float sample2 = m_fMemory[readIndex_1 % DelayMask];
        
        return sample1 * (1.f - frac) + sample2 * frac;
    }
};
}
