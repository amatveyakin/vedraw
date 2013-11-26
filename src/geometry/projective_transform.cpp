#include <stdexcept>

#include "projective_transform.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public

ProjectiveTransform::ProjectiveTransform( const QTransform& forwadTransform )
{
    bool isInvertible;
    m_forwadTransform = forwadTransform;
    m_backwadTransform = forwadTransform.inverted( &isInvertible );
    if ( !isInvertible )
        throw std::logic_error( "Unable to construct ProjectiveTransform instance from an noninvertible matrix!" );
}

ProjectiveTransform::~ProjectiveTransform()
{
}


QPointF ProjectiveTransform::mapForward( QPointF coordinates ) const
{
    return m_forwadTransform.map( coordinates );
}

QPointF ProjectiveTransform::mapBackward( QPointF coordinates ) const
{
    return m_backwadTransform.map( coordinates );
}


ProjectiveTransform ProjectiveTransform::translation( QPointF shift )
{
    return ProjectiveTransform( QTransform::fromTranslate( shift.x(), shift.y() ) );
}

// ProjectiveTransform ProjectiveTransform::horizontalFlip()
// {
//
// }
//
// ProjectiveTransform ProjectiveTransform::verticalFlip()
// {
//
// }

ProjectiveTransform ProjectiveTransform::rotation( qreal radians )
{
    QTransform transform;
    transform.rotateRadians( radians );
    return ProjectiveTransform( transform );
}

ProjectiveTransform ProjectiveTransform::scaling( qreal factor )
{
    return scaling( factor, factor );
}

ProjectiveTransform ProjectiveTransform::scaling( qreal factorX, qreal factorY )
{
    return ProjectiveTransform( QTransform::fromScale( factorX, factorY ) );
}

ProjectiveTransform ProjectiveTransform::shear( qreal shearX, qreal shearY )
{
    QTransform transform;
    transform.shear( shearX, shearY );
    return ProjectiveTransform( transform );
}
