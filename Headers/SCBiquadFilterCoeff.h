/*
  ==============================================================================

    SCBiquadFilterCoeff.h
    Created: 9 Nov 2021 10:54:22am
    Author:  dspra

  ==============================================================================
*/

#pragma once

namespace SCDsp
{
    struct SCBiquadFilterCoeff
    {
        float a0;
        float a1;
        float a2;
        float b1;
        float b2;
    };
}