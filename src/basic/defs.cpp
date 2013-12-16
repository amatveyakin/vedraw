#include <opencv2/opencv.hpp>

#include "defs.h"

#include "utils/debug_utils.h"


int toCvDepth( ColorDepth depth )
{
    switch ( depth ) {
        case ColorDepth::Int8:      return CV_8U;
        case ColorDepth::Int16:     return CV_16U;
    }
    ERROR_THROW_STD();
}

ColorDepth formCvDepth( int depth )
{
    switch ( depth ) {
        case CV_8U:                 return ColorDepth::Int8;
        case CV_16U:                return ColorDepth::Int16;
    }
    ERROR_THROW_STD();
}

int channelsFromColors( ImageColors colorFormat )
{
    switch ( colorFormat ) {
        case ImageColors::Gray:     return 1;
        case ImageColors::RGB:      return 3;
        case ImageColors::RGBA:     return 4;
    }
    ERROR_THROW_STD();
}

ImageColors channelsToColors( int channels )
{
    switch ( channels ) {
        case 1:                     return ImageColors::Gray;
        case 3:                     return ImageColors::RGB;
        case 4:                     return ImageColors::RGBA;
    }
    ERROR_THROW_STD();
}


int toCvType( ImageColors colorFormat, ColorDepth depth )
{
    return CV_MAKETYPE( toCvDepth( depth ), channelsFromColors( colorFormat ) );
}

void fromCvType( int cvType, ImageColors& colorFormat, ColorDepth& depth )
{
    colorFormat = channelsToColors( CV_MAT_CN( cvType ) );
    depth = formCvDepth( CV_MAT_TYPE( cvType ) );
}
