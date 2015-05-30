#include <opencv2/opencv.hpp>

#include "defs.h"

#include "utils/error_handling.h"


int toCvDepth( ColorDepth depth )
{
    switch ( depth ) {
        case ColorDepth::Int8:      return CV_8U;
        case ColorDepth::Int16:     return CV_16U;
    }
    ERROR();
}

ColorDepth formCvDepth( int depth )
{
    switch ( depth ) {
        case CV_8U:                 return ColorDepth::Int8;
        case CV_16U:                return ColorDepth::Int16;
    }
    ERROR();
}


int toCvType( int nChannels, ColorDepth depth )
{
    return CV_MAKETYPE( toCvDepth( depth ), nChannels );
}

void fromCvType( int cvType, int& nChannels, ColorDepth& depth )
{
    nChannels = CV_MAT_CN( cvType );
    depth = formCvDepth( CV_MAT_TYPE( cvType ) );
}
