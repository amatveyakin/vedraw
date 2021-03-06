#pragma once

#include <QtCore/QPointF>


class GeometricTransform
{
public:
    virtual ~GeometricTransform() { }

    virtual QPointF mapForward( QPointF coordinates ) const = 0;
    virtual QPointF mapBackward( QPointF coordinates ) const = 0;
};
