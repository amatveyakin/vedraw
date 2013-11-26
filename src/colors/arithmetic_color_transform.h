#ifndef ARITHMETIC_COLOR_TRANSFORM_H
#define ARITHMETIC_COLOR_TRANSFORM_H

#include "color_transform.h"


class ArithmeticColorTransform : ColorTransform
{
public:
    ArithmeticColorTransform();
    ~ArithmeticColorTransform();

    virtual bool supportsMapBackward() const override               { return false; }
    virtual QColor mapForward( QColor color ) const override;
    virtual QColor mapBackward( QColor color ) const override;

private:
//     QColor::Spec m_colorSpec;
};

#endif // ARITHMETIC_COLOR_TRANSFORM_H
