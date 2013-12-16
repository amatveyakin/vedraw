#include <QPainter>

#include "drawing_view.h"

#include "basic/image.h"
#include "drawing/drawing.h"


DrawingView::DrawingView( const Drawing* drawing )
    : m_drawing( drawing )
{
    connect( drawing, &Drawing::changed, this, static_cast< void ( DrawingView::* )() >( &DrawingView::update ) );
}

void DrawingView::paintEvent( QPaintEvent* /*ev*/ )
{
    QPainter painter( this );
    painter.drawImage( 0, 0, m_drawing->currentImage()->toQImage() );
}
