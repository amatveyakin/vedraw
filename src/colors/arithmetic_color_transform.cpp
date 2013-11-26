#include "arithmetic_color_transform.h"


ArithmeticColorTransform::ArithmeticColorTransform()
{
}

ArithmeticColorTransform::~ArithmeticColorTransform()
{
}



QColor ArithmeticColorTransform::mapForward( QColor color ) const
{
    return color;  // TODO FIXME
}

QColor ArithmeticColorTransform::mapBackward( QColor /*color*/ ) const
{
    return QColor();
}
