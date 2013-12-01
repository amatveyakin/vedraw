#ifndef SIMPLE_COLOR_TRANSFORMS_H
#define SIMPLE_COLOR_TRANSFORMS_H

#include "color_transform.h"


class InverseColorTransform : public ColorTransform
{
public:
    virtual bool supportsMapBackward() const override           { return true; }
    virtual QColor mapForward( QColor color ) const override    { return QColor::fromRgbF( 1. - color.redF(), 1. - color.greenF(), 1. - color.blueF(), color.alphaF() ); }
    virtual QColor mapBackward( QColor color ) const override   { return mapForward( color ); }
    virtual QString name() const override;
};

// CLEAN-UP: Do we need this?
class InverseLightnessColorTransform : public ColorTransform
{
public:
    virtual bool supportsMapBackward() const override           { return true; }
    virtual QColor mapForward( QColor color ) const override    { return QColor::fromHslF( color.hueF(), color.saturationF(), 1. - color.lightnessF(), color.alphaF() ); }
    virtual QColor mapBackward( QColor color ) const override   { return mapForward( color ); }
    virtual QString name() const override;
};

#endif // SIMPLE_COLOR_TRANSFORMS_H
