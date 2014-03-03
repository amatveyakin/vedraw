#pragma once

enum class ColorSpace
{
    Gray,
    RGB,
    HSV,
    HSL,
    Lab,
    // IDEA: What about the other formats (XYZ, YCrCb, Luv, CMYK, ...)
};

enum class ColorDepth
{
    Int8,
    Int16,
    // IDEA: Int32, Real32, Real64
};


int toCvDepth( ColorDepth depth );
ColorDepth formCvDepth( int depth );

int toCvType( int nChannels, ColorDepth depth );
void fromCvType( int cvType, int& nChannels, ColorDepth& depth );

constexpr int colorSpaceChannels( ColorSpace space, bool hasAlpha = false )
{
    return ( space == ColorSpace::Gray ? 1 : 3 ) + hasAlpha;
}
