#ifndef MODIFIERS_APPLIER_H
#define MODIFIERS_APPLIER_H

#include <QObject>

class Drawing;


class ModifiersApplier : public QObject
{
    Q_OBJECT
public:
    ModifiersApplier( Drawing* drawing );
    ~ModifiersApplier();

public slots:
    void invertColors();
    void invertLightness();

private:
    Drawing* m_drawing = 0;
};

#endif // MODIFIERS_APPLIER_H
