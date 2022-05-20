/*
  ==============================================================================

    SCCircularBuffer.h
    Simple, non-interpolating circular buffer to build others off of
    Does not manage its own memory
    Created: 13 May 2022 5:03:57pm
    Author:  Davis

  ==============================================================================
*/

#pragma once
#include <stdint.h>
#include <cstring>

namespace SCDsp
{
template <int pwr2DelayLen> class SCCircularBuffer
{
public:
    enum
    {
        DelaySize = 1 << pwr2DelayLen,
        DelayMask = DelaySize - 1,
    };
    
    SCCircularBuffer(float * memory):
    m_fMemory(memory),
    m_nWriteIndex(0),
    m_fReadIndex(0),
    m_fReadIncrement(1)
    {
        Reset();
    }
    
    virtual ~SCCircularBuffer()
    {}
    
    virtual void Read(float delay)
    {
        // non interpolating
        uint32_t truncatedDelay = static_cast<uint32_t>(delay);
        int readIndex = static_cast<uint32_t>(m_fReadIndex) - truncatedDelay;
        return m_fMemory[readIndex % DelayMask];
    }
    
    virtual void Write(float input)
    {
        m_fMemory[m_nWriteIndex % DelayMask] = input;
    }
    
    virtual float Process(float input, float delay)
    {
        Write(input);
        float result = Read(delay);
        IncrementWriteIndex();
        IncrementReadIndex();
        return result;
    }
    
    virtual void IncrementWriteIndex()
    {
        m_nWriteIndex++;
    }
    
    virtual void IncrementReadIndex()
    {
        m_fReadIndex += m_fReadIncrement;
    }
    
    virtual void Reset()
    {
        m_nWriteIndex = 0;
        m_fReadIndex = 0;
        std::memset(m_fMemory, 0, sizeof(float) * DelaySize);
    }
    
    void SetReadIncrement(float increment)
    {
        m_fReadIncrement = increment;
    }
private:
    float * m_fMemory;
    uint32_t m_nWriteIndex;
    float m_fReadIndex;
    float m_fReadIncrement;
};
}
