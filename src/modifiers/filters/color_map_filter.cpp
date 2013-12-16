#include "color_map_filter.h"

#include "basic/image.h"
#include "colors/color_transform.h"
#include "utils/qt_extensions.h"


ColorMapFilter::ColorMapFilter( std::unique_ptr< ColorTransform > transform )
{
    m_transform.swap( transform );
}

ColorMapFilter::~ColorMapFilter()
{
}

bool ColorMapFilter::apply( Image& /*image*/ ) const
{
    // TODO FIXME
    return false;
//     QRgb* begin = reinterpret_cast< QRgb* >( image.bits() );
//     QRgb* end = reinterpret_cast< QRgb* >( image.bits() + image.byteCount() );
//     for ( QRgb* pixel = begin; pixel < end; ++pixel )
//         *pixel = m_transform->mapRgbForward( *pixel );
//     return true;
}

QString ColorMapFilter::name( bool translate ) const
{
    return args( trMaybe( "ColorMap_%1", translate ), m_transform->name() );
}
