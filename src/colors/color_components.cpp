#include <QHash>
#include <QVector>

#include "color_components.h"

#include "utils/debug_utils.h"


class ColorComponentsPrivate
{
public:
    struct ComponentProperties
    {
        QString fullName;
        QString shortName;

        const QString& name( bool full ) const      { return full ? fullName : shortName; }
    };

    ColorComponentsPrivate();

    QList< ComponentProperties > components;
    QHash< QString, ColorComponent > nameToComponent;
    QVector< QVector< ColorComponent > > specComponents;

private:
    // temporary
    ColorComponent nextComponentToAdd;

    void addComponent( ColorComponent component, const QList< QColor::Spec >& specs, const QString& shortName, const QString& fullName);
};

ColorComponentsPrivate::ColorComponentsPrivate()
{
    typedef QColor Q;
    typedef ColorComponent C;
    specComponents.resize( LastColorSpec + 1 );
    nextComponentToAdd = ColorComponent( 0 );

    addComponent( C::Red        , { Q::Rgb         } , "r", "red"        );
    addComponent( C::Green      , { Q::Rgb         } , "g", "green"      );
    addComponent( C::Blue       , { Q::Rgb         } , "b", "blue"       );
    addComponent( C::Cyan       , { Q::Cmyk        } , "c", "cyan"       );
    addComponent( C::Magenta    , { Q::Cmyk        } , "m", "magenta"    );
    addComponent( C::Yellow     , { Q::Cmyk        } , "y", "yellow"     );
    addComponent( C::Black      , { Q::Cmyk        } , "k", "black"      );
    addComponent( C::Hue        , { Q::Hsv, Q::Hsl } , "h", "hue"        );
    addComponent( C::Saturation , { Q::Hsv, Q::Hsl } , "s", "saturation" );
    addComponent( C::Value      , { Q::Hsv         } , "v", "value"      );
    addComponent( C::Lightness  , { Q::Hsl         } , "l", "lightness"  );

    ASSERT( nextComponentToAdd == ColorComponent::ComponentCount );
}

void ColorComponentsPrivate::addComponent( ColorComponent component, const QList< QColor::Spec >& specs, const QString& shortName, const QString& fullName )
{
    ASSERT( component == nextComponentToAdd );
    ASSERT( !nameToComponent.contains( fullName ) );
    ASSERT( !nameToComponent.contains( shortName ) );

    components.append({ fullName, shortName });
    for ( auto s : specs )
        specComponents[ s ].append( component );
    nameToComponent[ fullName  ] = component;
    nameToComponent[ shortName ] = component;

    nextComponentToAdd = ColorComponent( int( nextComponentToAdd ) + 1 );
}

ColorComponentsPrivate priv;


int colorComponentCount( QColor::Spec spec )
{
    return priv.specComponents.value( spec ).size();
}

QString colorComponentName( ColorComponent component, bool full )
{
    return priv.components[ int( component ) ].name( full );
}

ColorComponent colorComponentFromName( const QString& name )
{
    return priv.nameToComponent.value( name, ColorComponent::Invalid );
}


QList< qreal > colorComponentListF( QColor::Spec spec, QColor color )
{
    QList< qreal > result;
    int nComponents = colorComponentCount( spec );
    for ( int i = 0; i < nComponents; ++i )
        result.append( colorComponentF( ColorComponent (i), color ) );
    return result;
}

qreal colorComponentF( ColorComponent component, QColor color )
{
    switch ( component ) {
        case ColorComponent::Red:           return color.redF();
        case ColorComponent::Green:         return color.greenF();
        case ColorComponent::Blue:          return color.blueF();
        case ColorComponent::Cyan:          return color.cyanF();
        case ColorComponent::Magenta:       return color.magentaF();
        case ColorComponent::Yellow:        return color.yellowF();
        case ColorComponent::Black:         return color.blackF();
        case ColorComponent::Hue:           return color.hueF();
        case ColorComponent::Saturation:    return color.saturationF();
        case ColorComponent::Value:         return color.valueF();
        case ColorComponent::Lightness:     return color.lightnessF();
        case ColorComponent::Invalid:       break;
    }
    ERROR_RETURN_V( 0 );
}

qreal colorComponentF( const QString& componentName, QColor color )
{
    return colorComponentF( colorComponentFromName( componentName ), color );
}


QColor colorByComponentsF( QColor::Spec spec, const QList< qreal >& components )
{
    ASSERT_RETURN_V( components.size() == colorComponentCount( spec ), QColor() );
    switch ( spec ) {
        case QColor::Rgb:   return QColor::fromRgbF ( components[ 0 ], components[ 1 ], components[ 2 ] );
        case QColor::Cmyk:  return QColor::fromCmykF( components[ 0 ], components[ 1 ], components[ 2 ], components[ 3 ] );
        case QColor::Hsv:   return QColor::fromHsvF ( components[ 0 ], components[ 1 ], components[ 2 ] );
        case QColor::Hsl:   return QColor::fromHslF ( components[ 0 ], components[ 1 ], components[ 2 ] );
        case QColor::Invalid: break;
    }
    ERROR_RETURN_V( QColor() );
}
