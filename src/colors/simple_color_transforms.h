#pragma once

#include "color_transform.h"

#include "utils/qt_extensions.h"


class InverseColorTransform : public ColorTransform< InverseColorTransform >
{
public:
    constexpr static const bool supportsMapBackwardImpl = true;
    constexpr static const bool supportsColorfulImpl = true;
    constexpr static const bool supportsGrayImpl = true;

    template< ColorDepth depth > ColorGray< depth > mapForwardImpl( ColorGray< depth > color ) const
    {
        auto max = DepthTraits< depth >::max;
        return ColorGray< depth >( max - color.v() );
    }
    template< ColorDepth depth > ColorRGB< depth >  mapForwardImpl( ColorRGB< depth > color ) const
    {
        auto max = DepthTraits< depth >::max;
        return ColorRGB< depth >( max - color.r(), max - color.g(), max - color.b() );
    }

    template< ColorDepth depth > ColorGray< depth > mapBackwardImpl( ColorGray< depth > color ) const   { return mapForwardImpl( color ); }
    template< ColorDepth depth > ColorRGB< depth >  mapBackwardImpl( ColorRGB< depth >  color ) const   { return mapForwardImpl( color ); }

    QString nameImpl() const        { return trNoop( "InverseColor" ); }
};

// // CLEAN-UP: Do we need this?
// class InverseLightnessColorTransform : public ColorTransform
// {
// public:
//     virtual bool supportsMapBackward() const override           { return true; }
//     virtual QColor mapForward( QColor color ) const override    { return QColor::fromHslF( color.hueF(), color.saturationF(), 1. - color.lightnessF(), color.alphaF() ); }
//     virtual QColor mapBackward( QColor color ) const override   { return mapForward( color ); }
//     virtual QString name() const override;
// };
// QString InverseLightnessColorTransform::name() const
// {
//     return trNoop( "InverseLightness" );
// }
