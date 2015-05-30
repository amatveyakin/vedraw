#pragma once

#include <exception>

#include <QString>

#include "color.h"

#include "utils/error_handling.h"
#include "utils/qt_extensions.h"


template< typename ThisTransformT >
class ColorTransform
{
public:
    constexpr static bool supportsMapBackward()     { return thisTransform()->supportsMapBackwardImpl; }
    constexpr static bool supportsColorful()        { return thisTransform()->supportsColorfulImpl; }
    constexpr static bool supportsGray()            { return thisTransform()->supportsGrayImpl; }

//     template< ColorDepth depth > ColorGray< depth >  mapForward( ColorGray< depth >  color ) const   { return thisTransform()->mapForwardImpl( color ); }
//     template< ColorDepth depth > ColorGrayA< depth > mapForward( ColorGrayA< depth >  color ) const  { return thisTransform()->mapForwardImpl( color ); }
//     template< ColorDepth depth > ColorRGB< depth >   mapForward( ColorRGB< depth >   color ) const   { return thisTransform()->mapForwardImpl( color ); }
//     template< ColorDepth depth > ColorRGBA< depth >  mapForward( ColorRGBA< depth >   color ) const  { return thisTransform()->mapForwardImpl( color ); }
//
//     template< ColorDepth depth > ColorGray< depth >  mapBackward( ColorGray< depth > color ) const   { return thisTransform()->mapBackwardImpl( color ); }
//     template< ColorDepth depth > ColorGrayA< depth > mapBackward( ColorGrayA< depth > color ) const  { return thisTransform()->mapBackwardImpl( color ); }
//     template< ColorDepth depth > ColorRGB< depth >   mapBackward( ColorRGB< depth >  color ) const   { return thisTransform()->mapBackwardImpl( color ); }
//     template< ColorDepth depth > ColorRGBA< depth >  mapBackward( ColorRGBA< depth >  color ) const  { return thisTransform()->mapBackwardImpl( color ); }

    template< ColorDepth depth > ColorGray< depth >  mapForward( ColorGray< depth >  color ) const  { ERROR(); }
    template< ColorDepth depth > ColorGrayA< depth > mapForward( ColorGrayA< depth >  color ) const { ERROR(); }
    template< ColorDepth depth > ColorRGB< depth >   mapForward( ColorRGB< depth >   color ) const  { ERROR(); }
    template< ColorDepth depth > ColorRGBA< depth >  mapForward( ColorRGBA< depth >   color ) const { ERROR(); }

    template< ColorDepth depth > ColorGray< depth >  mapBackward( ColorGray< depth > color ) const  { ERROR(); }
    template< ColorDepth depth > ColorGrayA< depth > mapBackward( ColorGrayA< depth > color ) const { ERROR(); }
    template< ColorDepth depth > ColorRGB< depth >   mapBackward( ColorRGB< depth >  color ) const  { ERROR(); }
    template< ColorDepth depth > ColorRGBA< depth >  mapBackward( ColorRGBA< depth >  color ) const { ERROR(); }

    QString name() const                            { return thisTransform()->nameImpl(); }

protected:
    void illegalMapBackwardCall() const             { throw EXCEPTION( IllegalArgument ) << args( "The '%1' color transform cannot map backwards", name() ); }
    void illegalMapColorful() const                 { throw EXCEPTION( IllegalArgument ) << args( "The '%1' color transform supports only gray colos", name() ); }
    void illegalMapGray() const                     { throw EXCEPTION( IllegalArgument ) << args( "The '%1' color transform doesn't support gray colors", name() ); }

private:
    const ThisTransformT* thisTransform() const     { return static_cast< const ThisTransformT* >( this ); }
};


template< bool supportsGray >
class ColorTransformBaseGraySupport {};

template<>
class ColorTransformBaseGraySupport< false >
{
    constexpr static const bool supportsGrayImpl = false;

    template< ColorDepth depth > ColorGray< depth > mapForwardImpl( ColorGray< depth > color ) const    { ERROR(); }
    template< ColorDepth depth > ColorGrayA< depth > mapForwardImpl( ColorGrayA< depth > color ) const  { ERROR(); }
    template< ColorDepth depth > ColorGray< depth > mapBackwardImpl( ColorGray< depth > color ) const   { ERROR(); }
    template< ColorDepth depth > ColorGrayA< depth > mapBackwardImpl( ColorGrayA< depth > color ) const { ERROR(); }
};

template<>
class ColorTransformBaseGraySupport< true >
{
    constexpr static const bool supportsGrayImpl = true;
};


template< bool supportsMapBackward >
class ColorTransformBaseMapBackwardSupport {};

template<>
class ColorTransformBaseMapBackwardSupport< false >
{
    constexpr static const bool supportsMapBackwardImpl = false;

    template< ColorDepth depth > ColorGray< depth >  mapBackwardImpl( ColorGray< depth > color ) const  { ERROR(); }
    template< ColorDepth depth > ColorGrayA< depth > mapBackwardImpl( ColorGrayA< depth > color ) const { ERROR(); }
    template< ColorDepth depth > ColorRGB< depth >   mapBackwardImpl( ColorRGB< depth >  color ) const  { ERROR(); }
    template< ColorDepth depth > ColorRGBA< depth >  mapBackwardImpl( ColorRGBA< depth >  color ) const { ERROR(); }
};

template<>
class ColorTransformBaseMapBackwardSupport< true >
{
    constexpr static const bool supportsMapBackwardImpl = true;
};


template< bool dependsOnAlpha >
class ColorTransformBaseDependsOnAlpha {};

template<>
class ColorTransformBaseDependsOnAlpha< false >
{
    constexpr static const bool dependsOnAlphaImpl = false;

    template< ColorDepth depth > ColorGrayA< depth > mapForward( ColorGrayA< depth >  color ) const { mapForward(); }
    template< ColorDepth depth > ColorRGBA< depth >  mapForward( ColorRGBA< depth >   color ) const { mapForward(); }
    template< ColorDepth depth > ColorGrayA< depth > mapBackward( ColorGrayA< depth > color ) const { mapBackward(); }
    template< ColorDepth depth > ColorRGBA< depth >  mapBackward( ColorRGBA< depth >  color ) const { mapBackward(); }
};

template<>
class ColorTransformBaseDependsOnAlpha< true >
{
    constexpr static const bool supportsMapBackwardImpl = true;
};


template< typename ThisTransformT, bool supportsGray, bool supportsMapBackward, bool dependsOnAlpha >
class ColorTransformBase :
    ColorTransformBaseGraySupport< supportsGray >,
    ColorTransformBaseMapBackwardSupport< supportsMapBackward >,
{

};
