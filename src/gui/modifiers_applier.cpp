#include "drawing_view.h"
#include "modifiers_applier.h"

#include "colors/simple_color_transforms.h"
#include "drawing/drawing.h"
#include "modifiers/filters/color_map_filter.h"
#include "utils/cpp_extensions.h"


ModifiersApplier::ModifiersApplier( Drawing* drawing, DrawingView* canvasWidget )
    : m_drawing( drawing )
    , m_canvasWidget( canvasWidget )
{
}

ModifiersApplier::~ModifiersApplier()
{
}

void ModifiersApplier::invertColors()
{
    auto filter = std::make_unique< ColorMapFilter >( std::make_unique< InverseColorTransform >() );
    m_drawing->addModifier( std::move( filter ) );
    m_canvasWidget->update();
}

void ModifiersApplier::invertLightness()
{
    auto filter = std::make_unique< ColorMapFilter >( std::make_unique< InverseLightnessColorTransform >() );
    m_drawing->addModifier( std::move( filter ) );
    m_canvasWidget->update();
}
