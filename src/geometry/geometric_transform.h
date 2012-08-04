#ifndef GEOMETRIC_TRANSFORM_H
#define GEOMETRIC_TRANSFORM_H


#include <QtCore/QPointF>


class GeometricTransform
{
public:
    virtual ~GeometricTransform() { }

    virtual QPointF mapForward( QPointF oldCoordinates ) = 0;
    virtual QPointF mapBackward( QPointF newCoordinates ) = 0;
};


#endif
