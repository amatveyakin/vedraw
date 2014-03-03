#pragma once

#include "filter.h"

#include "colors/color_transform.h"


template< typename ThisTransformT >
class ColorMapFilter : public Filter
{
public:
    ColorMapFilter( const ThisTransformT& transform );
    ~ColorMapFilter();

    virtual bool affectsColors() const override         { return true; }

    virtual bool apply( Image& image ) const override;

    QString name( bool translate ) const override;
    ColorTransform< ThisTransformT > transform() const  { return m_transform; }

private:
    ThisTransformT m_transform;
};
