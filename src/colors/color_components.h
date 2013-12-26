#pragma once

#include <QColor>


enum class ColorComponent
{
    Red,
    Green,
    Blue,

    Cyan,
    Magenta,
    Yellow,
    Black,

    Hue,
    Saturation,
    Value,
    Lightness,

    ComponentCount,
    Invalid = ComponentCount

    // IDEA: Add some read-only components, such as luma (obtained by qGray) (?)
    // IDEA: Do we need alpha here?
};

constexpr const int ColorSpecCount = 4;
constexpr const int LastColorSpec = ColorSpecCount;  // `Invalid' is the first one


int colorComponentCount( QColor::Spec spec );
QString colorComponentName( ColorComponent component, bool full );
ColorComponent colorComponentFromName( const QString& name );

QList< qreal > colorComponentListF( QColor::Spec spec, QColor color );
qreal colorComponentF( ColorComponent component, QColor color );
qreal colorComponentF( const QString& componentName, QColor color );

QColor colorByComponentsF( QColor::Spec spec, const QList< qreal >& components );
