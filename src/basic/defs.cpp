#include <opencv2/opencv.hpp>

#include "defs.h"

#include "utils/debug_utils.h"


int cvType( ImageFormat format, ColorDepth depth )
{
    bool p16bit = (depth == ColorDepth::Int16);
    switch ( format ) {
        case ImageFormat::Gray:   return p16bit ? CV_16UC1 : CV_8UC1;
        case ImageFormat::RGB:    return p16bit ? CV_16UC3 : CV_8UC3;
        case ImageFormat::RGBA:   return p16bit ? CV_16UC4 : CV_8UC4;
    }
    ERROR_RETURN_X( -1 );
}
