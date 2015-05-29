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

    template< ColorDepth depth > ColorGray< depth > mapForward( ColorGray< depth >  color ) const   { return thisTransform()->mapForwardImpl( color ); }
    template< ColorDepth depth > ColorRGB< depth >  mapForward( ColorRGB< depth >   color ) const   { return thisTransform()->mapForwardImpl( color ); }
    template< ColorDepth depth > ColorGray< depth > mapBackward( ColorGray< depth > color ) const   { return thisTransform()->mapBackwardImpl( color ); }
    template< ColorDepth depth > ColorRGB< depth >  mapBackward( ColorRGB< depth >  color ) const   { return thisTransform()->mapBackwardImpl( color ); }

    QString name() const                            { return thisTransform()->nameImpl(); }

protected:
    void illegalMapBackwardCall() const             { ERROR_THROW( qMakeException< std::logic_error >( "The '%1' color transform cannot map backwards", name() ) ); }
    void illegalMapColorful() const                 { ERROR_THROW( qMakeException< std::logic_error >( "The '%1' color transform supports only gray colos", name() ) ); }
    void illegalMapGray() const                     { ERROR_THROW( qMakeException< std::logic_error >( "The '%1' color transform doesn't support gray colors", name() ) ); }

private:
    const ThisTransformT* thisTransform() const     { return static_cast< const ThisTransformT* >( this ); }
};
