// TODO: RGB or Rgb?  RGBA, RgbA or Rgba?
// TODO: enum for colorful (?)
// TODO: enum for has_alpha (?)

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

//TODO:
// template< ColorDepth depthFrom, ColorDepth depthTo >
// typename DepthTraits< depthTo >::Type convertDepth( typename DepthTraits< depthTo >::Type v );
// template<> typename DepthTraits< ColorDepth::Int8 >::Type  convertDepth( typename DepthTraits< ColorDepth::Int8 >::Type v )     { return v; }
// template<> typename DepthTraits< ColorDepth::Int8 >::Type  convertDepth( typename DepthTraits< ColorDepth::Int16 >::Type v )    { return v / 0x101; }  // TODO: optimize and (?) make more precise
// template<> typename DepthTraits< ColorDepth::Int16 >::Type convertDepth( typename DepthTraits< ColorDepth::Int8 >::Type v )     { return v * 0x101; }
// template<> typename DepthTraits< ColorDepth::Int16 >::Type convertDepth( typename DepthTraits< ColorDepth::Int16 >::Type v )    { return v; }


//==============================================================================================================================================================
// Colors

template< ColorDepth depth >
class ColorGray
{
public:
    enum { nComponents = 1 };
    typedef typename DepthTraits< depth >::Type                 ComponentType;
    typedef typename cv::Vec< ComponentType, nComponents >      WholeType;

    explicit ColorGray( WholeType cvVec_ ) : data( cvVec_ ) {}
    explicit ColorGray( ComponentType v_ ) : data( v_ ) {}

    ComponentType v() const                     { return data[0]; }
    ComponentType& v()                          { return data[0]; }

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
public:
    enum { nComponents = 3 };
    typedef typename DepthTraits< depth >::Type                 ComponentType;
    typedef typename cv::Vec< ComponentType, nComponents >      WholeType;

    explicit ColorRGB( WholeType cvVec_ ) : data( cvVec_ ) {}
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
    // TODO
};

typedef ColorRGBA< ColorDepth::Int8  > ColorRGBA_Int8;
typedef ColorRGBA< ColorDepth::Int16 > ColorRGBA_Int16;


namespace _private
{
    template< bool isColorful, bool hasAlpha, ColorDepth depth >
    class ColorHelper {};
    template< ColorDepth depth >  class ColorHelper< false, false, depth >  { public: using Type = ColorGray< depth >; };
    template< ColorDepth depth >  class ColorHelper< false, true, depth >   { public: using Type = ColorGrayA< depth >; };
    template< ColorDepth depth >  class ColorHelper< true, false, depth >   { public: using Type = ColorRGB< depth >; };
    template< ColorDepth depth >  class ColorHelper< true, true, depth >    { public: using Type = ColorRGBA< depth >; };
};

template< bool isColorful, bool hasAlpha, ColorDepth depth >
using Color = typename _private::ColorHelper< isColorful, hasAlpha, depth >::Type;


//==============================================================================================================================================================
// Helper funcitons

template< bool isColorful, bool hasAlpha, ColorDepth depth >
Color< isColorful, hasAlpha, depth > makeColor( typename Color< isColorful, hasAlpha, depth >::WholeType cvVec )
{
    return Color< isColorful, hasAlpha, depth >( cvVec );
}
