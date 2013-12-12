#ifndef DEFS_H
#define DEFS_H

enum class ColorSpace
{
    RGB,
    HSV,
    HSL,
    Lab,
    // IDEA: What about the other formats (XYZ, YCrCb, Luv, CMYK, ...)
};

enum class ImageFormat
{
    Gray,
    RGB,
    RGBA,
};

enum class ColorDepth
{
    IntSingle,
    IntDouble,
    // IDEA:
//     IntQuadro,
//     RealSingle,
//     RealDouble,
};


int cvType( ImageFormat format, ColorDepth depth );

#endif // DEFS_H
