#pragma once

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
