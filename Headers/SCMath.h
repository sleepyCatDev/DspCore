/*
  ==============================================================================

    SCMath.h
    Created: 9 Nov 2021 10:54:49am
    Author:  dspra

  ==============================================================================
*/

#pragma once
#include <cmath>
#include <cstdint>

namespace SCMath
{
#define PI 3.14159265358979323846
#define HALF_PI 1.57079632679489661923

    inline float clip(float value, float min, float max)
    {
        value = (value < min) ? min : value;
        return (value > max) ? max : value;
    }
}