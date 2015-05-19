#pragma once

#include "filter.h"

#include "colors/color_transform.h"


template< typename ThisTransformT >
class ColorMapFilter : public Filter
{
public:
    ColorMapFilter( const ThisTransformT& transform );
    ~ColorMapFilter();

    bool affectsColors() const override         { return true; }

    bool apply( Image& image ) const override;

    QString name( bool translate ) const override;
    ColorTransform< ThisTransformT > transform() const  { return m_transform; }

private:
    ThisTransformT m_transform;
};
