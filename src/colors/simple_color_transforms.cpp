#include "simple_color_transforms.h"

#include "utils/qt_extensions.h"


QString InverseColorTransform::name() const
{
    return trNoop( "InverseColor" );
}

QString InverseLightnessColorTransform::name() const
{
    return trNoop( "InverseLightness" );
}
