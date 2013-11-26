#ifndef MODIFIERS_APPLIER_H
#define MODIFIERS_APPLIER_H

#include <QObject>

class Drawing;
class DrawingView;


class ModifiersApplier : public QObject
{
    Q_OBJECT
public:
    ModifiersApplier( Drawing* drawing, DrawingView* canvasWidget );
    ~ModifiersApplier();

public slots:
    void invertColors();
    void invertLightness();

private:
    Drawing* m_drawing;
    DrawingView* m_canvasWidget;
};

#endif // MODIFIERS_APPLIER_H
