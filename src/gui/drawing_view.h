#ifndef DRAWING_VIEW_H
#define DRAWING_VIEW_H

#include <QWidget>

class Drawing;


class DrawingView : public QWidget
{
public:
    DrawingView( const Drawing* drawing );

protected:
    virtual void paintEvent( QPaintEvent* ev ) override;

private:
    const Drawing *m_drawing;
    // TODO: Add scale, shift, etc.
};

#endif // DRAWING_VIEW_H
