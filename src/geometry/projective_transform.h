#ifndef PROJECTIVE_TRANSFORM_H
#define PROJECTIVE_TRANSFORM_H

#include <QTransform>

#include "geometric_transform.h"


class ProjectiveTransform : public GeometricTransform
{
public:
    ProjectiveTransform( const QTransform& forwadTransform );
    virtual ~ProjectiveTransform();

    virtual QPointF mapForward( QPointF coordinates ) const override;
    virtual QPointF mapBackward( QPointF coordinates ) const override;

    static ProjectiveTransform translation( QPointF shift );
//     static ProjectiveTransform horizontalFlip();
//     static ProjectiveTransform verticalFlip();
    static ProjectiveTransform rotation( qreal radians );
    static ProjectiveTransform scaling( qreal factor );
    static ProjectiveTransform scaling( qreal factorX, qreal factorY );
    static ProjectiveTransform shear( qreal shearX, qreal shearY );

protected:
    QTransform m_forwadTransform;
    QTransform m_backwadTransform;
};

#endif
