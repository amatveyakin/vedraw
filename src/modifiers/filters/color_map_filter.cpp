#include <opencv2/opencv.hpp>

#include "color_map_filter.h"

#include "basic/image.h"
#include "colors/color_transform.h"
#include "colors/simple_color_transforms.h"
#include "utils/cartesian_call.h"
#include "utils/error_handling.h"
#include "utils/opencv_type_traits.h"
#include "utils/qt_extensions.h"


template< typename ThisTransformT, bool isColorful, bool hasAlpha, ColorDepth depth >
static bool colorMapImplementation( ColorTransform< ThisTransformT > transform, cv::Mat& mat )
{
    constexpr int nChannels = colorSpaceChannels( isColorful ? ColorSpace::RGB : ColorSpace::Gray, hasAlpha );
    CHECK( mat.depth() == toCvDepth( depth ) );
    CHECK( mat.channels() == nChannels );

    // TODO: Can we use OpenCV's parallel for here?
    typedef typename OpenCvVector< nChannels, depth >::Type ScalarT;
    for( auto it = mat.begin< ScalarT >(); it != mat.end< ScalarT >(); ++it)
        *it = transform.mapForward( makeColor< isColorful, hasAlpha, depth >( *it ) ).cvVec();
    return true;
}

template< typename ThisTransformT >
ColorMapFilter< ThisTransformT >::ColorMapFilter( const ThisTransformT& transform_ )
{
    m_transform = transform_;
}

template< typename ThisTransformT >
ColorMapFilter< ThisTransformT >::~ColorMapFilter()
{
}

template< typename ThisTransformT >
bool ColorMapFilter< ThisTransformT >::apply( Image& image ) const
{
    return CARTESIAN_CALL( colorMapImplementation,
                           ( ThisTransformT ),
                           ( bool )( image.isColorful() ),
//                            ( bool )( image.hasAlpha() ),   // TODO
                           ( false ),
                           ( ColorDepth )( image.colorDepth() )
                         )( transform(),
                            image.cvMat() );
}

template< typename ThisTransformT >
QString ColorMapFilter< ThisTransformT >::name( bool translate ) const
{
    return args( trMaybe( "ColorMap_%1", translate ), transform().name() );
}


template class ColorMapFilter< InverseColorTransform >;
// template class ColorMapFilter< InverseLightnessColorTransform >;
