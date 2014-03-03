#pragma once

#include <opencv2/core/core.hpp>

#include "basic/defs.h"


template< ColorDepth depth >
struct OpenCvScalar { };

template<> struct OpenCvScalar< ColorDepth::Int8 >           { typedef uchar     Type; };
template<> struct OpenCvScalar< ColorDepth::Int16 >          { typedef ushort    Type; };


template< int channels, ColorDepth depth >
struct OpenCvVector
{
    typedef cv::Vec< typename OpenCvScalar< depth >::Type, channels >  Type;
};
