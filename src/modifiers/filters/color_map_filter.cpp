#include <QImage>

#include "color_map_filter.h"

#include "colors/color_transform.h"
#include "utils/qt_extensions.h"


ColorMapFilter::ColorMapFilter( std::unique_ptr< ColorTransform > transform )
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

QString ColorMapFilter::name() const
{
    return trNoop( "ColorMap_%1" ).arg( m_transform->name() );
}
