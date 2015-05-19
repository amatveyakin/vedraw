#pragma once

#include <QWidget>

class Drawing;


class DrawingView : public QWidget
{
public:
    DrawingView( const Drawing* drawing );

protected:
    void paintEvent( QPaintEvent* ev ) override;

private:
    const Drawing *m_drawing;
    // TODO: Add scale, shift, etc.
};
