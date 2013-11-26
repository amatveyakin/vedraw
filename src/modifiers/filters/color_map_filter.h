#ifndef COLOR_MAP_FILTER_H
#define COLOR_MAP_FILTER_H

#include <memory>

#include "filter.h"

class ColorTransform;


class ColorMapFilter : public Filter
{
public:
    ColorMapFilter( std::unique_ptr< ColorTransform > transform );
    ~ColorMapFilter();

    virtual bool affectsColors() const override     { return true; }

    virtual bool apply( QImage& image ) const override;

private:
    std::unique_ptr< ColorTransform > m_transform;
};

#endif // COLOR_MAP_FILTER_H
