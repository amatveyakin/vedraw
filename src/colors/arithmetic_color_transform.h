#pragma once

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
