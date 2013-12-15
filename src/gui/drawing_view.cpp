#include <QPainter>

#include "drawing/drawing.h"

#include "drawing_view.h"


DrawingView::DrawingView( const Drawing* drawing )
    : m_drawing( drawing )
{
    connect( drawing, &Drawing::changed, this, static_cast< void ( DrawingView::* )() >( &DrawingView::update ) );
}

void DrawingView::paintEvent( QPaintEvent* /*ev*/ )
{
    QPainter painter( this );
    painter.drawImage( 0, 0, m_drawing->currentImage() );
}
