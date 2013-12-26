#pragma once

#include <memory>

#include "filter.h"

class ColorTransform;


class ColorMapFilter : public Filter
{
public:
    ColorMapFilter( std::unique_ptr< ColorTransform > transform );
    ~ColorMapFilter();

    virtual bool affectsColors() const override     { return true; }

    virtual bool apply( Image& image ) const override;

    QString name( bool translate ) const override;

private:
    std::unique_ptr< ColorTransform > m_transform;
};
