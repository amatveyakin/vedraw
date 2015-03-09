#pragma once

#include "utils/cartesian_call.h"


enum class ColorSpace
{
    Gray,
    RGB,
    HSV,
    HSL,
    Lab,
    // IDEA: What about the other formats (XYZ, YCrCb, Luv, CMYK, ...)
};
#define CARTESIAN_CALL_TYPE_ColorSpace  ColorSpace::Gray, ColorSpace::RGB, ColorSpace::HSV, ColorSpace::HSL, ColorSpace::Lab
CARTESIAN_CALL_CHECK_VALUE_LIST_COMPLETNESS( ColorSpace )


enum class ColorDepth
{
    Int8,
    Int16,
    // IDEA: Int32, Real32, Real64
};
#define CARTESIAN_CALL_TYPE_ColorDepth  ColorDepth::Int8, ColorDepth::Int16
CARTESIAN_CALL_CHECK_VALUE_LIST_COMPLETNESS( ColorDepth )


int toCvDepth( ColorDepth depth );
ColorDepth formCvDepth( int depth );

int toCvType( int nChannels, ColorDepth depth );
void fromCvType( int cvType, int& nChannels, ColorDepth& depth );

constexpr int colorSpaceChannels( ColorSpace space, bool hasAlpha = false )
{
    return ( space == ColorSpace::Gray ? 1 : 3 ) + hasAlpha;
}
