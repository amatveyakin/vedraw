#pragma once

#include "basic/defs.h"
#include "utils/opencv_type_traits.h"


//==============================================================================================================================================================
// Color depth

namespace _private
{
template< ColorDepth depth > struct CommonDepthTraits
{
    typedef typename OpenCvScalar< depth >::Type Type;
    constexpr static const std::size_t bytes = sizeof( Type );
};

template< ColorDepth depth > struct CommonIntDepthTraits : public CommonDepthTraits< depth >
{
private:
    typedef CommonDepthTraits< depth > ParentT;
public:
    constexpr static const bool isInt = true;
    constexpr static const typename ParentT::Type max = std::numeric_limits< typename ParentT::Type >::max();
};
}

template< ColorDepth depth > struct DepthTraits { };

template<> struct DepthTraits< ColorDepth::Int8  > : public _private::CommonIntDepthTraits< ColorDepth::Int8  > {};
template<> struct DepthTraits< ColorDepth::Int16 > : public _private::CommonIntDepthTraits< ColorDepth::Int16 > {};

typedef DepthTraits< ColorDepth::Int8 >  DepthTraits_Int8;
typedef DepthTraits< ColorDepth::Int16 > DepthTraits_Int16;


//==============================================================================================================================================================
// Colors

template< ColorDepth depth >
class ColorGray
{
    typedef typename DepthTraits< depth >::Type     ComponentType;
    typedef ComponentType                           WholeType;

public:
    ColorGray( ComponentType v_ ) : data( v_ ) {}

    ComponentType v() const                     { return data; }
    ComponentType& v()                          { return data; }

    const WholeType& cvVec() const              { return data; }
    WholeType& cvVec()                          { return data; }

private:
    WholeType data;
};

typedef ColorGray< ColorDepth::Int8  > ColorGray_Int8;
typedef ColorGray< ColorDepth::Int16 > ColorGray_Int16;


template< ColorDepth depth >
class ColorGrayA
{
};

typedef ColorGrayA< ColorDepth::Int8  > ColorGrayA_Int8;
typedef ColorGrayA< ColorDepth::Int16 > ColorGrayA_Int16;


template< ColorDepth depth >
class ColorRGB
{
    typedef typename DepthTraits< depth >::Type     ComponentType;
    typedef typename cv::Vec< ComponentType, 3 >    WholeType;

public:
    ColorRGB( WholeType cvVec_ ) : data( cvVec_ ) {}
    ColorRGB( ComponentType r_, ComponentType g_, ComponentType b_ ) { data[0] = r_; data[1] = g_; data[2] = b_; }
    static ColorRGB fromGray( ComponentType v_ ) { return ColorRGB( v_, v_, v_ ); }
    static ColorRGB fromGray( ColorGray< depth > gray ) { return fromGray( gray.v() ); }

    ComponentType r() const                     { return data[0]; }
    ComponentType& r()                          { return data[0]; }
    ComponentType g() const                     { return data[1]; }
    ComponentType& g()                          { return data[1]; }
    ComponentType b() const                     { return data[2]; }
    ComponentType& b()                          { return data[2]; }

    const WholeType& cvVec() const              { return data; }
    WholeType& cvVec()                          { return data; }

private:
    WholeType data;
};

typedef ColorRGB< ColorDepth::Int8  > ColorRGB_Int8;
typedef ColorRGB< ColorDepth::Int16 > ColorRGB_Int16;


template< ColorDepth depth >
class ColorRGBA
{
};

typedef ColorRGBA< ColorDepth::Int8  > ColorRGBA_Int8;
typedef ColorRGBA< ColorDepth::Int16 > ColorRGBA_Int16;


//==============================================================================================================================================================
// Helper funcitons

// TODO
// template< bool isColorful, bool hasAlpha, ColorDepth depth >
// makeColor
template< bool isColorful, bool hasAlpha, ColorDepth depth >
ColorRGB< depth > makeColor( cv::Vec< typename DepthTraits< depth >::Type, 3 > cvVec )
{
    return ColorRGB< depth >( cvVec );
}
