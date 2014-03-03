#include <opencv2/opencv.hpp>

#include "color_map_filter.h"

#include "basic/image.h"
#include "colors/color_transform.h"
#include "colors/simple_color_transforms.h"
#include "utils/debug_utils.h"
#include "utils/opencv_type_traits.h"
#include "utils/qt_extensions.h"


template< typename ThisTransformT, bool isColorful, bool hasAlpha, ColorDepth depth > static
bool colorMapImplementation( ColorTransform< ThisTransformT > transform, cv::Mat& mat )
{
    constexpr int nChannels = colorSpaceChannels( isColorful ? ColorSpace::RGB : ColorSpace::Gray, hasAlpha );
    ASSERT_THROW_STD( mat.depth() == toCvDepth( depth ) );
    ASSERT_THROW_STD( mat.channels() == nChannels );

//     switch(channels)
//     {
//     case 1:
//         {
//             MatIterator_<uchar> it, end;
//             for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
//                 *it = table[*it];
//             break;
//         }
//     case 3:
//         {
//             MatIterator_<Vec3b> it, end;
//             for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
//             {
//                 (*it)[0] = table[(*it)[0]];
//                 (*it)[1] = table[(*it)[1]];
//                 (*it)[2] = table[(*it)[2]];
//             }
//         }
//     }

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
    // TODO FIXME
    ASSERT_THROW_STD( image.colorSpace() == ColorSpace::RGB || image.colorSpace() == ColorSpace::Gray );  // TODO: Support all color spaces
//     colorMapImplementation< ThisTransformT, image.isColorful(), image.hasAlpha(), image.colorDepth() >( transform(), image.cvMat() ); // TODO
    return colorMapImplementation< ThisTransformT, true, false, ColorDepth::Int8 >( transform(), image.cvMat() ); // TODO FIXME
}

template< typename ThisTransformT >
QString ColorMapFilter< ThisTransformT >::name( bool translate ) const
{
    return args( trMaybe( "ColorMap_%1", translate ), transform().name() );
}


template class ColorMapFilter< InverseColorTransform >;
// template class ColorMapFilter< InverseLightnessColorTransform >;
