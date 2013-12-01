#ifndef COLOR_TRANSFORM_H
#define COLOR_TRANSFORM_H

#include <QColor>


class ColorTransform
{
public:
    virtual ~ColorTransform() { }

    virtual bool supportsMapBackward() const = 0;
    virtual QColor mapForward( QColor color ) const = 0;
    virtual QColor mapBackward( QColor color ) const = 0;

    // TODO: optimize
    QRgb mapRgbForward( QRgb color ) const          { return mapForward( color ).rgba(); }
    QRgb mapRgbBackward( QRgb color ) const         { return mapBackward( color ).rgba(); }

    virtual QString name() const = 0;
};

#endif
