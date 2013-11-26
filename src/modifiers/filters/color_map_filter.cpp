#include <QImage>

#include "color_map_filter.h"

#include "colors/color_transform.h"


ColorMapFilter::ColorMapFilter( std::unique_ptr<ColorTransform> transform )
{
    m_transform.swap( transform );
}

ColorMapFilter::~ColorMapFilter()
{
}

bool ColorMapFilter::apply( QImage& image ) const
{
    // TODO: Check image format
    QRgb* begin = reinterpret_cast< QRgb* >( image.bits() );
    QRgb* end = reinterpret_cast< QRgb* >( image.bits() + image.byteCount() );
    for ( QRgb* pixel = begin; pixel < end; ++pixel )
        *pixel = m_transform->mapRgbForward( *pixel );
    return true;
}
