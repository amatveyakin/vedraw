#pragma once

enum class ColorSpace
{
    None,  // for grayscale
    RGB,
    HSV,
    HSL,
    Lab,
    // IDEA: What about the other formats (XYZ, YCrCb, Luv, CMYK, ...)
};

enum class ImageColors
{
    Gray,
    RGB,
    RGBA,
};

enum class ColorDepth
{
    Int8,
    Int16,
    // IDEA: Int32, Real32, Real64
};


int toCvDepth( ColorDepth depth );
ColorDepth formCvDepth( int depth );

int channelsFromColors( ImageColors colorFormat );
ImageColors channelsToColors( int channels );

int toCvType( ImageColors colorFormat, ColorDepth depth );
void fromCvType( int cvType, ImageColors& colorFormat, ColorDepth& depth );
