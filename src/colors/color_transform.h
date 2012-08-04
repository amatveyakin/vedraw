#ifndef COLOR_TRANSFORM_H
#define COLOR_TRANSFORM_H


#include <QtGui/QColor>


class ColorTransform
{
public:
    virtual ~ColorTransform() { }

    virtual QColor mapForward( QColor oldColor ) = 0;
    virtual QColor mapBackward( QColor newColor ) = 0;
};


#endif
