#include "drawing_view.h"
#include "modifiers_applier.h"
#include "utils/gui_error_handling.h"

#include "colors/simple_color_transforms.h"
#include "drawing/drawing.h"
#include "modifiers/filters/color_map_filter.h"


ModifiersApplier::ModifiersApplier( Drawing* drawing )
    : m_drawing( drawing )
{
}

ModifiersApplier::~ModifiersApplier()
{
}

void ModifiersApplier::invertColors()
TRY
{
    auto filter = std::make_unique< ColorMapFilter< InverseColorTransform > >( InverseColorTransform() );
    m_drawing->addModifier( std::move( filter ) );
}
CATCH_SHOW_ERROR

// void ModifiersApplier::invertLightness()
// TRY
// {
//     auto filter = std::make_unique< ColorMapFilter< InverseLightnessColorTransform > >( InverseLightnessColorTransform() );
//     m_drawing->addModifier( std::move( filter ) );
// }
// CATCH_SHOW_ERROR
